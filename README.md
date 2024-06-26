# k-Nearest Neighbors classification in C on a dataset of flower images

## Igor Robin - Student at ISIMA in Clermont-Ferrand, France

## Image classification
The purpose of this program is to classify images using the k-Nearest Neighbors (k-NN) algorithm in the C language.
The program is using a free dataset of flower images that can be found on Kaggle. 

As you will notice, the accuracy obtained with this algorithm for image classification is quite low (around 32%, which is a bit better than random guessing for this dataset: 20%). This is not surprising because we know that for high dimensional datasets like the ones made of images, the k-NN algorithm fails to achieve decent accuracy compared to other methods such as neural networks.
However, the implementation of the program can be modified easily to process datasets with lower dimensionality.
There is a famous dataset called the Iris dataset which can be found on the scikit-learn website. With this dataset, this same algorithm achieves 90% accuracy.
Link to the scikit-learn documentation and the Iris dataset: 
https://scikit-learn.org/stable/auto_examples/datasets/plot_iris_dataset.html

The goal here was to understand a bit better how the k-NN algorithm works. In fact, before programming it, I had studied it in class and had used it with Python via scikit-learn, but I was kind of frustrated to see that everything was already done for me and could be written with 10 lines of code. I wanted to truly dive in the algorithm, and what could be better than programming it ?

To summarize, the algorithm works like this :
```
- Load the dataset and store it in a an array of samples (which can be images)
(- In the case of images, resize them so that they all have the same reasonable size)
- Random shuffle all the samples
- Split the dataset into a training dataset and a testing dataset

- For each test sample
    - Compute its distance to every training sample using a metric
    - Select the k nearest neighbors of the currently processed sample
    - Choose the class that has the highest number of nearest neighbors as the predicted class

- Compute the results such as accuracy, F1-score and recall based on the number of true 
positives, false positives and false negatives
```

## What's in this repository ?
- include : all the .h header files
- src : all .c files
- A CMakeLists.txt
- Extra files (license, this README.md and .gitignore)

## How to use it ?
- Clone the repository
- Go on Kaggle.com and download the flowers dataset used here, the link is here: https://www.kaggle.com/datasets/imsparsh/flowers-dataset
- Extract the .zip archive, go inside it and put the "flowers" folder at the root of this repository
- Install CMake, installation instructions can be found here: https://cmake.org
- Run the following commands at the root of the repository:
```
mkdir build
cd build
cmake ..
make
./knn_images
```
- After waiting a few seconds until processing reaches 100%, you should be able to see the results in the terminal

## What can you do to experiment ?
- You can change the metric used for computing distances: the available ones are Manhattan, euclidean and Minkowski (a high p order can result in long computation)
- You can change the p order for the Minkowski metric
- You can use the weighted version (inverse of distances)
- You can use a different dataset, but you will have to modify some code because the file structure will be different

## What will be next ?
- In the future, my goal would be to have more features available is this program, for example by increasing the number of available metrics (like adding cosine similarity)
- The idea would be to implement what is available in the KNeighborsClassifier object in scikit-learn, so even to implement the Ball-Tree or KD-Tree search for the k nearest neighbors
- The softare still being in development, I would like to add a menu for choosing the metric, the number of neighbors (k), and whether the k-NN algorithm is wieghted or not

## Acknowledgements
This program uses a single file C library for .jpg image decompression and resizing called stb_resize_image2 (.h) which was written by Jeff Roberts and Jorge L Rodriguez. I want to thank them for putting this library in the public domain and thus letting people use it. The library can be found here on Sean Barrett's GitHub:

https://github.com/nothings/stb/blob/master/stb_image_resize2.h

Finally, I also want to thank Sparsh Gupta, a Kaggler, for providing the flower dataset used here.

Any demand, remark, or desire of contribution regarding this project would be welcomed ! You can send me an email at Igor.ROBIN@etu.isima.fr

## Work in progress
This program is still in development


