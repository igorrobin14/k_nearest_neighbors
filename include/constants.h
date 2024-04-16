/**
 * @file constants.h
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Main constants for k-NN classification and image processing
 * @version 0.1
 * @date 2024-04-14
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @brief The total number of classes
 */
#define NB_CLASSES 5

/**
 * @brief The maximum length of a string containing an image path
 */
#define MAX_PATH_LENGTH 256

/**
 * @brief The maximum length of a string containing other information such as class labels
 */
#define MAX_STR_LENGTH 128

/**
 * @brief The size of the resized images
 */
#define RESIZED_IMG_SIZE 128

/**
 * @brief The number of channels for images (RGB)
 */
#define NB_CHANNELS 3

/**
 * @brief The quality of .jpg image decompression
 */
#define IMG_QUALITY 100

#endif