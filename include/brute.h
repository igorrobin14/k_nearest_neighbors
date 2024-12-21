/**
 * @file algorithm.h
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Central functions in the k-NN algorithm
 * @version 0.1
 * @date 2024-04-18
 */

#ifndef BRUTE_H
#define BRUTE_H

#include "types_constants.h"

// /**
//  * @brief Computes for each train sample its distance, weight, and index with respect to the currently processed test image
//  * 
//  * @param points_infos An array containing for every sample its distance, weight and index with respect to the currently processed test image
//  * @param nb_train_samples The total number of train images (samples)
//  * @param samples_train The array of all train images (samples)
//  * @param samples_test The array of all test images (samples)
//  * @param i The currently processed image is the i-th test image (sample)
//  * @param weighted_knn Whether the k-NN algorithm is weighted or not
//  * @param m The metric used for computing distances
//  * @param p The order of the Minkowski metric
//  */
// void compute_points_data(point_data_t **points_data, int nb_train_samples, int nb_test_samples, raw_image_t **samples_train, raw_image_t **samples_test, bool weighted_knn, metric m, double p);

// void compute_points_data_rest(point_data_t **points_data, int nb_train_samples, int nb_test_samples, raw_image_t **samples_train, raw_image_t **samples_test, bool weighted_knn, metric m, double p);

void *process_part(void *arg);

// /**
//  * @brief Compares two samples based on their distance
//  * 
//  * @param a The first sample
//  * @param b The second sample
//  * @return The comparison between the two samples
//  */
// int compare_samples(const void *a, const void *b);

// /**
//  * @brief Isolates the k nearest points from all the other ones
//  * 
//  * @param k_nearest_neighbors The k nearest neighbors in the points_infos array (the ones with minimal distance)
//  * @param k The number of neigbors considered in the k-NN algorithm
//  * @param points_infos An array containing for every sample its distance, weight and index with respect to the currently processed test image
//  */
// void isolate_knns(point_data_t **k_nearest_neighbors, int k, int nb_test_samples, point_data_t **points_infos);

// /**
//  * @brief Finds the predicted class for a sample
//  * 
//  * @param max_votes The maximum number of votes among all classes
//  * @param max_votes_index The index of the class whose number of votes is the highest among all classes
//  * @param number_of_classes The total number of classes
//  * @param counts An array where the i-th element is the weighted sum of votes for the i-th class label
//  * @param ans The predicted class for the currently processed test image (sample)
//  * @param class_labels All the class labels
//  * @param predictions An array of strings where the i-th element is the prediceted class (string) for the i-th image (sample)
//  * @param i The currently processed image is the i-th test image (sample)
//  */
// void find_prediction(int *max_votes, int *max_votes_index, double ***counts, char ***ans, char *class_labels[], char ***predictions, int nb_test_samples);

// /**
//  * @brief Fills the votes array with all the class labels corresponding to the k nearest neighbors
//  * 
//  * @param votes An array where the i-th element is the number of votes for the i-th class label
//  * @param samples_train The array containing all test images (samples)
//  * @param k_nearest_neighbors The k nearest neighbors in the points_infos array (the ones with minimal distance)
//  * @param k The number of neighbors considered
//  */
// void fill_votes(char ****votes, raw_image_t **samples_train, point_data_t ***k_nearest_neighbors, int k, int nb_test_samples);

// /**
//  * @brief Computes the number of votes for each class by summing all votes for each class and weighting them by inverse distance if desired
//  * 
//  * @param votes An array where the i-th element is the number of votes for the i-th class label
//  * @param k The number of neighbors considered
//  * @param class_labels All the class labels
//  * @param counts An array where the i-th element is the weighted sum of votes for the i-th class label
//  * @param k_nearest_neighbors The k nearest neighbors in the points_infos array (the ones with minimal distance)
//  */
// void compute_weighted_counts(char ****votes, int k, char *class_labels[], double ***counts, point_data_t ***k_nearest_neighbors, int nb_test_samples);

#endif