import warnings
warnings.filterwarnings("ignore", message="A NumPy version >=1.16.5 and <1.23.0 is required for this version of SciPy")

import PIL
import cv2
import pathlib
import matplotlib.pyplot as plt
import random

import time

import numpy as np

from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report, ConfusionMatrixDisplay, confusion_matrix, accuracy_score

start_time = time.time()

random.seed(14)

dataset_url = "flowers/train"
datadir = pathlib.Path(dataset_url)

# Definition des categories et des labels pour les fleurs
flowers = {'daisy': list(datadir.glob("daisy/*")),
           'dandelion': list(datadir.glob("dandelion/*")),
           'rose': list(datadir.glob("rose/*")),
           'sunflower': list(datadir.glob("sunflower/*")),
           'tulip': list(datadir.glob("tulip/*"))}

labels = {
    'daisy': 0,
    'dandelion': 1,
    'rose': 2,
    'sunflower': 3,
    'tulip': 4
}

# Creation des matrices x (images) et y (labels)
x = []
y = []

# La dimension des images est a ajuster pour ne pas consommer 
# trop de ressources
dim_images = 128

# On parcourt tous les dossiers et on concatene chaque fleur
# au tableau et on fait la meme chose pour les labels
for image_name, image in flowers.items():
    for img in image:
        img = cv2.imread(str(img))
        resized = cv2.resize(img, (dim_images, dim_images), interpolation=cv2.INTER_LINEAR) 
        x.append(resized)
        y.append(labels[image_name])

x = np.array(x)
x_flowers = x.reshape((x.shape[0], -1))
y_flowers = np.array(y)

print("Forme de la matrice des fleurs :", x_flowers.shape, ", Forme de la matrice des labels :", y_flowers.shape)
print("Il y a", y_flowers.shape[0], "images en tout")

# On melange les images et les labels dans un ordre aleatoire pour les presenter comme ceci au modele
ind_list = [i for i in range(x_flowers.shape[0])]
random.shuffle(ind_list)
x_shuffled = x_flowers[ind_list,:]
y_shuffled = y_flowers[ind_list]

# File to save the array
file_name = "shuffled_indexes.txt"

# Write to the file (not to be done when comparing performance between C and Python)
with open(file_name, "w") as file:
    file.write(f"{len(ind_list)} ")  # Write the size of the array
    file.write(" ".join(map(str, ind_list)))  # Write the array elements separated by space

print(f"Data written to {file_name}")

# Separation des donnees en une partie entrainement et une partie test
taille_test = 0.2
x_train, x_test, y_train, y_test = train_test_split(x_shuffled, y_shuffled, test_size=taille_test, stratify=y_shuffled, random_state=14)

print("Nombre de fleurs dans la partie test :", y_test.shape[0])
print("Nombre de fleurs dans la partie entrainement :", y_train.shape[0])

# On normalise les donnees
x_train_normalized = x_train #/255
x_test_normalized = x_test #/255

# On applique la methode des k-NN (on entraine le modele)
n_voisins = 10
#metrique = 'euclidian'
knn = KNeighborsClassifier(n_neighbors=n_voisins, metric='euclidean', algorithm='brute', n_jobs=26)

# On entraine le modele
knn.fit(x_train_normalized, y_train)

# On realise une prediction avec le modele entraine
y_pred_knn = knn.predict(x_test_normalized)

# On affiche les resultats et performances de la classification
fig, ax = plt.subplots(figsize=(10, 5))
ConfusionMatrixDisplay.from_predictions(y_test, y_pred_knn, ax=ax)
titre = ax.set_title("Tableau de contingence obtenu avec le KNeighborsClassifier sur les fleurs")

# On affiche les performances de la classification
print(classification_report(y_test, y_pred_knn))

end_time = time.time()

elapsed_time = end_time - start_time
print(f"Elapsed time: {elapsed_time:.4f} seconds")