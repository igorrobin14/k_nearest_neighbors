/**
 * @file results.h
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief 
 * @version 0.1
 * @date 2024-04-14
 */

#ifndef RESULTS_H
#define RESULTS_H

#include "types_constants.h"

/**
 * @brief Computes the accuracy of the k-NN classification
 * 
 * @param nb_trues The number of correctly predicted samples
 * @param nb_test_samples The number of test samples
 * @return double 
 */
double compute_accuracy(result_t *r, int nb_test_samples, char ***predictions, raw_image_t **samples_test, bool **is_right_class, int *nb_trues, int *nb_falses);

/**
 * @brief Computes the true positives in the preditions
 * 
 * @param predictions The array of predictions
 * @param samples_test The array of test images (samples)
 * @param class_labels The class labels
 * @param nb_samples_test The number of test samples
 * @param true_positives TO DO
 */
void compute_true_positives(char ***predictions, raw_image_t **samples_test, char *class_labels[], int nb_samples_test, double **true_positives);

/**
 * @brief Computes the false positives in the preditions
 * 
 * @param predictions The array of predictions
 * @param samples_test The array of test images (samples)
 * @param class_labels The class labels
 * @param nb_samples_test The number of test samples
 * @param true_positives TO DO
 */
void compute_false_positives(char ***predictions, raw_image_t **samples_test, char *class_labels[], int nb_test_samples, double **false_positives);

/**
 * @brief Computes the false negatives in the preditions
 * 
 * @param predictions The array of predictions
 * @param samples_test The array of test images (samples)
 * @param class_labels The class labels
 * @param nb_samples_test The number of test samples
 * @param true_positives The number of false negatives
 */
void compute_false_negatives(char ***predictions, raw_image_t **samples_test, char *class_labels[], int nb_test_samples, double **false_negatives);

/**
 * @brief Computes all the results for the k-NN classification
 * 
 * @param r The results structure
 * @param true_positives TO DO
 * @param false_positives TO DO
 * @param false_negatives TO DO
 * @param class_labels The class labels
 * @param samples_test The array of test images (samples)
 * @param nb_test_samples The number of test images
 */
void compute_results(result_t *r, double **true_positives, double **false_positives, double **false_negatives, char *class_labels[], raw_image_t **samples_test, int nb_test_samples);

/**
 * @brief Computes the support for each class (the number of test images for each class)
 * 
 * @param r The results structure
 * @param class_labels The class labels
 * @param samples_test The array of test images (samples)
 * @param nb_test_samples The number of test images
 */
void compute_supports(result_t *r, char *class_labels[], raw_image_t **samples_test, int nb_test_samples);



/**
 * @brief Displays all the results in a clear way
 * 
 * @param r The results structure
 * @param class_labels The class labels
 */
void display_results(result_t *r, char *class_labels[]);

#endif