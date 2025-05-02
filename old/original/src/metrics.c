/**
 * @file metrics.c
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Definitions of metrics for calculating distances between samples
 * @version 0.1
 * @date 2024-04-14
 */

#include "metrics.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION

double euclidean_distance(raw_image_t * a, raw_image_t * b, int p)
{
    double sum_squares = 0;
    //p = 2;
    for (int i = 0; i < RESIZED_IMG_SIZE * RESIZED_IMG_SIZE * NB_CHANNELS; i++)
    {
        sum_squares += pow(a->image_data[i] - b->image_data[i], 2);
    }    

    return sqrt(sum_squares);
}

double manhattan_distance(raw_image_t *a, raw_image_t *b, int p)
{
    double sum = 0;
    p = 1;
    for (int i = 0; i < RESIZED_IMG_SIZE * RESIZED_IMG_SIZE * NB_CHANNELS; i++)
    {
        sum += fabs(a->image_data[i] - b->image_data[i]);
    }

    return sum;
}

double minkowski_distance(raw_image_t * a, raw_image_t * b, int p)
{
    double sum = 0;
    for (int i = 0; i < RESIZED_IMG_SIZE * RESIZED_IMG_SIZE * NB_CHANNELS; i++)
    {
        sum += pow(abs(a->image_data[i] - b->image_data[i]), p);
    }

    return pow(sum, (1.0 / p));
}