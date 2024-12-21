#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "types_constants.h"

void * safe_alloc(size_t element_size, size_t num_elements);
#define alloc_array(type, size) ((type *)safe_alloc(sizeof(type), (size)))

void init_data_location(dataset_t * dataset);

/**
 * @brief Counts the number of files in a given folder
 * 
 * @param folder_path The path to the folder
 * @return The number of files in the folder
 */


int count_files_in_subfolder(const char * folder_path);


/**
 * @brief Counts the number of files per subfolder (number of samples per class) and computes the total number of samples (sum)
 * 
 * @param files_in_subfolders Array where i-th element is the number of files in the i-th folder (gives the number of samples for the i-th class)
 * @param flower_folder_paths Array where the i-th element is the path to the i-th folder (1 folder per class)
 * @param nb_samples The total number of samples (train + test), so the sum of all elements in files_in_subfolders
 */
void count_files_in_main_folder(dataset_t * dataset);


/**
 * @brief Fills all_image_paths with the paths to all images
 * 
 * @param all_image_paths An array where each element is an array of strings representing the paths to the images
 * (1 element = 1 folder and each folder has its array of string for the paths to the files it contains)
 * @param flower_folder_paths Array where the i-th element is the path to the i-th folder (1 folder per class)
 */
void set_all_image_paths(dataset_t * dataset);

void load_all_images(dataset_t * dataset);

void load_jpeg_image_file(image_t * loaded_image);

void map_images_to_class(dataset_t * dataset);

/**
 * @brief Resizes all images contained in the array of images
 * 
 * @param image_array The original image array (train + test)
 * @param nb_samples The total number of images (= number of samples, = test + train)
 * @param files_in_subfolders Array where i-th element is the number of files in the i-th folder (gives the number of samples for the i-th class)
 * @param resized_image_array The array containing all resized images
 */
void resize_all_images(dataset_t * initial_dataset, dataset_t * processed_dataset);

void launch_multithreaded_processing(thread_t threads[NB_THREADS], knn_classifier_t * knn_classifier, dataset_t * dataset);

void * process_part(void * arg);

// /**
//  * @brief Binds each image to its class by putting in the "class" field its class
//  * 
//  * @param class_labels The class labels
//  * @param files_in_subfolders Array where i-th element is the number of files in the i-th folder (gives the number of samples for the i-th class)
//  * @param resized_image_array Array of all resized images
//  */
// void bind_image_to_class(char **class_labels, int *files_in_subfolders, raw_image_t **resized_image_array);

// /**
//  * @brief Random shuffles all the samples
//  * 
//  * @param samples All samples
//  * @param nb_samples The total number of samples
//  * @param seed The seed for random shuffling
//  */
// void random_shuffle(raw_image_t *samples, int nb_samples, unsigned int seed);

// /**
//  * @brief Splits the samples into a training a dataset and a test dataset
//  * 
//  * @param test_size The size of the test dataset (choose between 0 and 1)
//  * @param nb_samples The total number of samples
//  * @param train_image_array The array containing all training images (samples)
//  * @param test_image_array The array containing all test images (samples)
//  * @param resized_image_array The array containing all images (samples)
//  * @param nb_test_samples The total number of test samples
//  * @param nb_train_samples The total number of training samples
//  */
void train_test_split(dataset_t * dataset, double test_size);

void shuffle_from_index_list(dataset_t * dataset);

#endif