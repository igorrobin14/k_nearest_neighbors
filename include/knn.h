/**
 * @file knn.h
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Main functions at the heart of the k-NN algorithm
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright 
 * 
 */
#ifndef KNN_H
#define KNN_H

#include "types.h"

/**
 * @brief Shuffles the array of given images randomly
 * 
 * @param samples The array of images
 * @param nb_samples The number of images in the array
 * @param seed The random shuffling seed
 */
void random_shuffle(raw_image_t *samples, int nb_samples, unsigned int seed);

/**
 * @brief Splits the array of all images into a test and a train set
 * 
 * @param test_size The proportion of images to be put in the test set
 * @param nb_samples The total number of images (test + train)
 * @param train_image_array The array of train images
 * @param test_image_array The array of test images
 * @param resized_image_array The array of all resized images
 * @param nb_test_samples The number of test images
 * @param nb_train_samples The number of train images
 */
void train_test_split(double test_size, int nb_samples, raw_image_t **train_image_array, raw_image_t **test_image_array, raw_image_t **resized_image_array, int *nb_test_samples, int *nb_train_samples);

/**
 * @brief Computes for each train sample information such as its distance, weight, and index with respect to the currently processed test image
 * 
 * @param points_infos Array containing the information mentionned above for the train images
 * @param nb_train_samples The total number of train samples
 * @param samples_train The array of train images
 * @param samples_test The array of test images
 * @param i The index of the currently processed image
 * @param weighted_knn Whether the k-NN algorithm is weighted or not
 * @param m The metric used for computing distances
 * @param p The order of the Minkowski metric
 */
void compute_points_infos(point_info_t **points_infos, int nb_train_samples, raw_image_t **samples_train, raw_image_t **samples_test, int i, bool weighted_knn, metric m, double p);

/**
 * @brief Compares two samples based on their distance
 * 
 * @param a The first sample
 * @param b The second sample
 * @return The comparison between the two samples
 */
int compare_samples(const void *a, const void *b);

/**
 * @brief Isolates the k nearest points from all the other ones
 * 
 * @param k_nearest_neighbors The k nearest points from the currently processed test sample
 * @param k The number of neigbors considered in the k-NN algorithm
 * @param points_infos All the points considered for the currently processed sample
 */
void isolate_knns(point_info_t **k_nearest_neighbors, int k, point_info_t **points_infos);

/**
 * @brief Finds the predicted class for a sample
 * 
 * @param max_votes The maximum number of votes in the counts array
 * @param max_votes_index The index in the array with each class label of the class with the maximum number of votes
 * @param number_of_classes The total number of classes
 * @param counts Array with the number of votes for each class
 * @param ans The predicted class
 * @param class_labels The class labels
 * @param predictions // TO DO
 * @param i The index of the currently processed image
 */
void find_prediction(int *max_votes, int *max_votes_index, int number_of_classes, double **counts, char **ans, char *class_labels[], char ***predictions, int i);
void predictions_vs_expected(int nb_test_samples, char ***predictions, raw_image_t **samples_test, bool **results, int *nb_trues, int *nb_falses);


#endif