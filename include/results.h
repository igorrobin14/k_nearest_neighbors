// /**
//  * @file results.h
//  * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
//  * @brief 
//  * @version 0.1
//  * @date 2024-04-18
//  */

// #ifndef RESULTS_H
// #define RESULTS_H

// #include "types_constants.h"

// /**
//  * @brief Computes the accuracy of the k-NN classification
//  * 
//  * @param nb_trues The number of correctly predicted samples
//  * @param nb_test_samples The total number of test images (samples)
//  * @return The accuracy of the k-NN classification
//  */
// double compute_accuracy(result_t *r, int nb_test_samples, char ***predictions, raw_image_t **samples_test, bool **is_right_class, int *nb_trues, int *nb_falses);

// /**
//  * @brief Computes the true positives regarding predictions
//  * 
//  * @param predictions An array of strings where the i-th element is the prediceted class (string) for the i-th image (sample)
//  * @param samples_test The array of all test images (samples)
//  * @param class_labels All the class labels
//  * @param nb_samples_test The number of test images (samples)
//  * @param true_positives Array where the i-th element if the number of true positives for the i-th class
//  */
// void compute_true_positives(char ***predictions, raw_image_t **samples_test, char *class_labels[], int nb_samples_test, double **true_positives);

// /**
//  * @brief Computes the false positives regarding predictions
//  * 
//  * @param predictions An array of strings where the i-th element is the prediceted class (string) for the i-th image (sample)
//  * @param samples_test The array of all test images (samples)
//  * @param class_labels All the class labels
//  * @param nb_samples_test The number of test images (samples)
//  * @param false_positives Array where the i-th element if the number of false positives for the i-th class
//  */
// void compute_false_positives(char ***predictions, raw_image_t **samples_test, char *class_labels[], int nb_test_samples, double **false_positives);

// /**
//  * @brief Computes the false negatives regarding predictions
//  * 
//  * @param predictions An array of strings where the i-th element is the prediceted class (string) for the i-th image (sample)
//  * @param samples_test The array of all test images (samples)
//  * @param class_labels All the class labels
//  * @param nb_samples_test The number of test images (samples)
//  * @param false_negatives Array where the i-th element if the number of false negatives for the i-th class
//  */
// void compute_false_negatives(char ***predictions, raw_image_t **samples_test, char *class_labels[], int nb_test_samples, double **false_negatives);

// /**
//  * @brief Computes all the results for the k-NN classification
//  * 
//  * @param r The results structure
//  * @param true_positives Array where the i-th element if the number of true positives for the i-th class
//  * @param false_positives Array where the i-th element if the number of false positives for the i-th class
//  * @param false_negatives Array where the i-th element if the number of false negatives for the i-th class
//  * @param class_labels The class labels
//  * @param samples_test The array of test images (samples)
//  * @param nb_test_samples The number of test images
//  */
// void compute_results(result_t *r, double **true_positives, double **false_positives, double **false_negatives, char *class_labels[], raw_image_t **samples_test, int nb_test_samples);

// /**
//  * @brief Computes the support for each class (the number of test images for each class)
//  * 
//  * @param r The results structure
//  * @param class_labels All the class labels
//  * @param samples_test The array of all test images (samples)
//  * @param nb_test_samples The number of test images (samples)
//  */
// void compute_supports(result_t *r, char *class_labels[], raw_image_t **samples_test, int nb_test_samples);

// /**
//  * @brief Displays all the results in a clear way
//  * 
//  * @param r The results structure
//  * @param class_labels All the class labels
//  */
// void display_results(result_t *r, char *class_labels[]);

// #endif