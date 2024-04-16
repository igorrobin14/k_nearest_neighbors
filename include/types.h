/**
 * @file types.h
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Type definitions for the k-NN classification
 * @version 0.1
 * @date 2024-04-14
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include <jpeglib.h>
#include <jerror.h>

#include "constants.h"

#define _USE_MISC
#include <dirent.h>

/**
 * @brief An image structure
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
 * @brief For each train sample, its distance, weight and index with respect to the currently processed test image
 */
typedef struct point_info
{
    double distance;
    double weight;
    int index;
}
point_info_t;

/**
 * @brief The results structure
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

/**
 * @brief A metric typedef
 */
typedef double (*metric) (raw_image_t *, raw_image_t *, double);

#endif