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
 * @brief The quality of .jpg image decompression
 */
#define IMG_QUALITY 100

#define RESIZED_IMG_SIZE 128

#define NB_CHANNELS 3

/**
 * @struct A structure for images
 */
typedef struct image
{
    unsigned int num_components;
    unsigned int height;
    unsigned int width;
    unsigned char * pixels;
    char path[512];
    char class_label[MAX_STR_LENGTH];
}
image_t;

typedef struct folder
{
    char path[MAX_STR_LENGTH];
    unsigned int nb_files_contained;
    char ** file_paths;
}
folder_t;

typedef struct dataset
{
    unsigned int nb_samples;
    image_t * images;
    //image_t * first_image;
    //image_t * last_image;
    image_t * test_train_separation;
    char main_folder_path[MAX_STR_LENGTH];
    folder_t folders[NB_CLASSES];
    char * class_labels[NB_CLASSES];
}
dataset_t;

typedef struct thread_info
{
    unsigned int start_data_index;
    unsigned int end_data_index;
}
thread_info_t;

typedef struct query_point
{
    unsigned char * pixels;
    double * distances_to_all_points;
    image_t * k_nearest_neighbors;
}
query_point_t;

typedef double (*metric) (image_t *, image_t *, int);

typedef struct knn_classifier
{
    metric m;
    unsigned int p;
    unsigned int k;
    // algorithm algo;
    unsigned int n_jobs;
    bool weighted;
}
knn_classifier_t;

/*
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
*/

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