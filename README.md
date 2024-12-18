# k-Nearest Neighbors classification in C on a dataset of flower images

## Igor Robin - Student at ISIMA in Clermont-Ferrand, France

## Image classification
The purpose of this program is to classify images using the k-Nearest Neighbors (k-NN) algorithm in the C language.
The program uses a free dataset of flower images that can be found on Kaggle. 

As you will notice, the accuracy obtained with this algorithm for image classification is quite low (around 32%, which is a bit better than random guessing for this dataset: 20%). This is not surprising because we know that for high dimensional datasets like the ones made of images, the k-NN algorithm fails to achieve decent accuracy compared to other methods such as neural networks.
However, the implementation of the program can be modified easily to process datasets with lower dimensionality.

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

