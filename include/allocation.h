// /**
//  * @file allocation.h
//  * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
//  * @brief Memory allocation and image loading functions
//  * @version 0.1
//  * @date 2024-04-14
//  */

// #ifndef ALLOCATION_H
// #define ALLOCATION_H

// #include "types_constants.h"

// /**
//  * @brief Opens, loads, and returns a .jpg image by decompressing it using the STB library
//  * 
//  * @param image_path The path to the image
//  * @return The open and loaded image 
//  */
// raw_image_t *load_jpeg_image_file(char *image_path, raw_image_t *new_image);

// /**
//  * @brief Allocates an array where each element is an array of strings representing the paths to all the images
//  * 
//  * @param files_in_subfolders Array where i-th element is the number of files in the i-th folder (gives the number of samples for the i-th class)
//  * @param all_image_paths An array where each element is an array of strings representing the paths to the images
//  * (1 element = 1 folder and each folder has its array of string for the paths to the files it contains)
//  */
// void allocate_file_paths(int **files_in_subfolders, char ****all_image_paths);

// /**
//  * @brief Allocates all the necessary memory for storing the images
//  * 
//  * @param image_array The array of all images (test + train)
//  * @param nb_samples The total number of images (samples)
//  * @param files_in_subfolders Array where i-th element is the number of files in the i-th folder (gives the number of samples for the i-th class)
//  * @param all_image_paths An array where each element is an array of strings representing the paths to the images
//  * (1 element = 1 folder and each folder has its array of string for the files it contains)
//  */
// void allocate_all_images(raw_image_t **image_array, int nb_samples, int **files_in_subfolders, char ****all_image_paths);

// //void fill_votes(char ****votes, raw_image_t **samples_train, point_data_t ***k_nearest_neighbors, int k, int nb_test_samples);

// /**
//  * @brief Allocates the predictions and the is_right_class array
//  * 
//  * @param predictions An array of strings where the i-th element is the prediceted class (string) for the i-th image (sample)
//  * @param nb_test_samples The total number of test images (samples)
//  */
// void allocate_predicted_classes(char ***predictions, int nb_test_samples);

// /**
//  * @brief Allocates the is_right_class array
//  * 
//  * @param is_right_class An array of booleans where the i-th boolean is true if the i-th prediction matches the true class label
//  * @param nb_test_samples The total number of test images (samples)
//  */
// void allocate_is_right_class(bool ** is_right_class, int nb_test_samples);

// /**
//  * @brief Allocates the points_infos array
//  * 
//  * @param points_infos An array containing for every sample its distance, weight and index with respect to the currently processed test image
//  * @param nb_train_samples The total number of train images (samples)
//  * @param nb_test_samples The total number of test images (samples)
//  */
// void allocate_points_data(point_data_t ***points_infos, int nb_train_samples, int nb_test_samples);

// /**
//  * @brief Allocates an array for the k nearest neighbors
//  * 
//  * @param k_nearest_neighbors The k nearest neighbors in the points_infos array (the ones with minimal distance)
//  * @param k The number of neighbors to consider
//  * @param nb_test_samples The total number of test images (samples)
//  */
// void allocate_knns(point_data_t ***k_nearest_neighbors, int k, int nb_test_samples);

// /**
//  * @brief Allocates the votes array
//  * 
//  * @param votes An array where the i-th element is the number of votes for the i-th class label
//  * @param k The number of neighbors considered
//  */
// void allocate_votes(char ****votes, int k, int nb_test_samples);

// /**
//  * @brief Allocates the counts array
//  * 
//  * @param counts An array where the i-th element is the weighted sum of votes for the i-th class label
//  */
// void allocate_counts(double ***counts, int nb_test_samples);

// /**
//  * @brief Allocates the ans string
//  * 
//  * @param ans The predicted class for the currently processed test image (sample)
//  */
// void allocate_ans(char ***ans, int nb_test_samples);

// /**
//  * @brief Frees the memory allocated at every main loop iteration
//  * 
//  * @param points_infos The array containing for every sample its distance, weight and index with respect to the currently processed test image
//  * @param k_nearest_neighbors The k nearest neighbors with respect to the curretly processed test image (sample)
//  * @param votes The array where the i-th element is the number of votes for the i-th class label
//  * @param counts The array where the i-th element is the weighted sum of votes for the i-th class label
//  * @param ans The predicted class for the currently processed test image (sample)
//  * @param k The number of neighbors for the k-NN algorithm
//  */
// void free_data(point_data_t ***points_infos, point_data_t ***k_nearest_neighbors, char ****votes, double ***counts, char ***ans, raw_image_t **image_array, raw_image_t **resized_image_array, raw_image_t **train_image_array, raw_image_t **test_image_array, int **files_in_subfolders, char ***predictions, bool **is_right_class, char ****all_image_paths, int k, int nb_test_samples);

// /**
//  * @brief Allocates the memory for the results of the k-NN classification
//  * 
//  * @param r The structure containing the results
//  * @param true_positives An array where the i-th element is the number of true positives for the i-th class
//  * @param false_positives An array where the i-th element is the number of false positives for the i-th class
//  * @param false_negatives An array where the i-th element is the number of false negatives for the i-th class
//  * @param nb_test_samples The total number of test images (samples)
//  */
// void allocate_results(result_t *r, double **true_positives, double **false_positives, double **false_negatives, int nb_test_samples);

// void free_results(double **true_positives, double **false_positives, double **false_negatives, result_t *r);

// #endif