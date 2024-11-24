#ifndef TYPES_CONSTANTS_H
#define TYPES_CONSTANTS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include <jpeglib.h>
#include <jerror.h>

#define _USE_MISC
#include <dirent.h>

#define NB_THREADS 26

/**
 * @brief The total number of classes
 */
#define NB_CLASSES 5

/**
 * @brief The maximum length of a string containing other information such as class labels
 */
#define MAX_STR_LENGTH 256

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

/**
 * @struct A structure for images
 */
typedef struct raw_image
{
    unsigned int num_components;
    unsigned int width;
    unsigned int height;

    unsigned char *image_data;

    char *class;
}
raw_image_t;

/**
 * @struct For each train sample, its distance, weight and index with respect to the currently processed test image
 */
typedef struct point_data
{
    double distance;
    double weight;
    int index;
}
point_data_t;

/**
 * @typedef A metric
 */
typedef double (*metric) (raw_image_t *, raw_image_t *, double);

typedef struct thread_data
{
    int start_index;
    int end_index;
    point_data_t **points_data;
    int nb_train_samples;
    raw_image_t **samples_train;
    raw_image_t **samples_test;
    bool weighted_knn;
    metric m;
    double p;
}
thread_data_t;

/**
 * @struct The results structure
 */
typedef struct result
{
    double *precisions;
    double *recalls;
    double *f1_scores;
    double *supports;
    double precision_mavg, precision_wavg;
    double recall_mavg, recall_wavg;
    double f1_score_mavg, f1_score_wavg;
    double accuracy;
}
result_t;

#endif