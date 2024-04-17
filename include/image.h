/**
 * @file image.h
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Functions for image processing and path storage
 * @version 0.1
 * @date 2024-04-14
 */

#ifndef IMAGE_H
#define IMAGE_H

#include "types.h"

/**
 * @brief Counts the number of files per subfolder (number of samples per class) and computes the total number of samples (sum)
 * 
 * @param files_in_subfolders Array containing for each subfolder the number of files in it
 * @param flower_folder_paths The paths to all folders (each folder is for a class)
 * @param nb_samples The total number of samples (train + test)
 */
void count_files_in_subfolders_and_nb_samples(int **files_in_subfolders, char *flower_folder_paths[], int *nb_samples);

/**
 * @brief Counts the number of files in a given subfolder
 * 
 * @param folder_path The path to the subfolder
 * @return The number of files in the subfolder
 */
int count_files_in_folder(const char *folder_path);

/**
 * @brief Fils the array of array of strings representing the paths to the images with the paths to the images
 * 
 * @param all_image_paths An array where each element is an array of strings representing the paths to the images
 * (1 element = 1 folder and each folder has its array of string for the files it contains)
 * @param flower_folder_paths The paths to all folders (each folder is for a class)
 */
void fill_all_image_paths(char ****all_image_paths, char *flower_folder_paths[]);

/**
 * @brief Resizes all images contained in the array of images
 * 
 * @param image_array The original image array (train + test)
 * @param nb_samples The total number of images (= number of samples), test + train
 * @param files_in_subfolders The number of files per subfolder (number of images per class)
 * @param resized_image_array The processed resized image array
 */
void resize_all_images(raw_image_t **image_array, int nb_samples, int **files_in_subfolders, raw_image_t **resized_image_array);

/**
 * @brief Maps each image to its class by putting in the "class" field its class
 * 
 * @param class_labels The class labels
 * @param files_in_subfolders The number of files per subfolder
 * @param train_images TO MODIFY
 */
void bind_image_to_class(char **class_labels, int *files_in_subfolders, raw_image_t **train_images);

#endif