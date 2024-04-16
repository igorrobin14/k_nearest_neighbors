/**
 * @file allocation.h
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Header for memory allocation and image loading functions
 * @version 0.1
 * @date 2024-04-14
 */

#ifndef ALLOCATION_H
#define ALLOCATION_H

#include "types.h"

/**
 * @brief Opens, loads, and returns a .jpg image by decompressing it using the STB library
 * 
 * @param image_path The path to the image
 * @return The open and loaded image 
 */
raw_image_t load_jpeg_image_file(char *image_path);

/**
 * @brief Allocates an array of arrays of strings which are the paths to all images
 * 
 * @param files_per_subfolder An array of integers representing the number of files per subfolder (number of samples per class)
 * @param file_paths The paths to all images
 */
void allocate_file_paths(int **files_per_subfolder, char ****file_paths);

/**
 * @brief Allocates all the necessary memory for storing the images
 * 
 * @param image_array The array of all images
 * @param nb_samples The total number of images (samples)
 * @param files_per_subfolder An array of integers representing the number of files per subfolder (number of samples per class)
 * @param file_paths The paths to all images
 */
void allocate_all_images(raw_image_t **image_array, int nb_samples, int **files_per_subfolder, char ****file_paths);

/**
 * @brief Allocates the predictions and the results
 * 
 * @param predictions An array of strings representing the predicted classes for the test samples
 * @param results A array of booleans representing if the prediction matches the true class
 * @param nb_test_samples The total number of test images (samples)
 */
void allocate_preditions_and_results(char ***predictions, bool **results, int nb_test_samples);

/**
 * @brief Allocates an array that represents for each train sample its distance, weight, and index with respect to the currently processed test image
 * 
 * @param points_infos The point infos array
 * @param nb_train_samples The total number of train images (samples)
 */
void allocate_points_infos(point_info_t **points_infos, int nb_train_samples);

/**
 * @brief Allocates an array for the k nearest point in the array mentionned above
 * 
 * @param k_nearest_neighbors The k nearest points
 * @param k The number of neighbors to consider
 */
void allocate_knns(point_info_t **k_nearest_neighbors, int k);

/**
 * @brief Allocates the array of votes for each test sample, the array of the number of votes for each class and the string representing the predicted class
 * 
 * @param votes The array of votes for each class (class labels : strings)
 * @param counts The array of the number of votes for each class
 * @param ans The predicted class (string)
 * @param k The number of neighbors considered in the k-NN algorithm
 * @param number_of_classes The total number of classes
 * @param class_labels The class labels
 * @param samples_train The array of train images
 * @param k_nearest_neighbors The k nearest points mentionned in the function above
 */
void allocate_votes_counts_ans(char ***votes, double **counts, char **ans, int k, int number_of_classes, char *class_labels[], raw_image_t **samples_train, point_info_t **k_nearest_neighbors);

/**
 * @brief Allocates the memory for the results of the k-NN classification
 * 
 * @param r The structure containing the results
 * @param true_positives The number of true positives 
 * @param false_positives The number of false positives
 * @param false_negatives The number of false negatives
 * @param nb_test_samples The total number of test images (samples)
 */
void allocate_results(result_t *r, double **true_positives, double **false_positives, double **false_negatives, int nb_test_samples);

/**
 * @brief Frees the memory allocated at every main loop iteration
 * 
 * @param points_infos The point infos array
 * @param k_nearest_neighbors The k nearest points
 * @param votes The votes array
 * @param counts The counts array
 * @param ans The predicted class string
 * @param k The number of neighbors for the k-NN algorithm
 */
void free_loop_data(point_info_t **points_infos, point_info_t **k_nearest_neighbors, char ***votes, double **counts, char **ans, int k);
//void allocate_test_images(raw_image_t **test_images, int nb_test_samples);

#endif