# k-Nearest Neighbors classification in C on a dataset of flower images

## Igor Robin

## Image classification
The purpose of this program is to classify images using the k-Nearest Neighbors (k-NN) algorithm in the C language.
The program uses a free dataset of flower images that can be found on Kaggle. 

As you will notice, the accuracy obtained with this algorithm for image classification is quite low (around 32%, which is a bit better than random guessing for this dataset: 20%). This is not surprising because we know that for high dimensional datasets like the ones made of images, the k-NN algorithm fails to achieve decent accuracy.
However, the implementation of the program can be modified easily to process datasets with lower dimensionality (for example the Iris dataset)

The goal here was to understand a bit better how the k-NN algorithm works. In fact, before programming it, I had studied it in class and had used it with Python via scikit-learn, but I was kind of frustrated to see that everything was already done for me and could be written with 10 lines of code. I wanted to truly dive in the algorithm by programming it in C.

To summarize, the algorithm works like this :
```
- Load the dataset and store it in a an array of samples (which can be images)
(- In the case of images, resize them so that they all have the same reasonable size)
- Split the dataset into a training dataset and a testing dataset

- For each test sample
    - Compute its distance to every training sample using a metric
    - Select the k nearest neighbors of the currently processed sample
    - Choose the class that has the highest number of nearest neighbors as the predicted class

- Compute the results such as accuracy, F1-score and recall based on the number of true 
positives, false positives and false negatives
```

## What can you do to experiment ?
- You can change the metric used for computing distances: the available ones are Manhattan, euclidean and Minkowski (a high p order can result in a longer computation)
- You can change the p order if using the Minkowski metric
- You can use the weighted version (inverse of distances)
- You can use a different dataset, but you will have to modify some code because the file structure will be different

## What happens next ?
- In the future, my goal would be to have more features available is this program, for example by increasing the number of available metrics
- The idea would be to implement what is available in the KNeighborsClassifier object in scikit-learn, so even to implement the Ball-Tree or KD-Tree search for the k nearest neighbors
- The program still being in development, I would like to add a menu for choosing the metric, the number of neighbors (k), and whether the k-NN algorithm is weighted or not, and also maybe a menu for selecting the dataset to load

## To do
- Code all other neighbor search algorithms (ball-tree, kd-tree)
- Check if the weighted version works
- Optimize the algorithms/the code and refactor by putting variables into structs
- Maybe add a GUI
- Compare the obtained performance with Python


