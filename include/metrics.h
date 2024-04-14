/**
 * @file metrics.h
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Metrics that can be used to compute distances between samples
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright 
 * 
 */

#ifndef METRCIS_H
#define METRICS_H

#include "types.h"

/**
 * @brief Euclidean distance between two samples (order 2 Minkowski distance)
 * 
 * @param a The first sample
 * @param b The second sample
 * @param p The order of the Mikowski metric (ignored is this case)
 * @return The computed euclidean distance
 */
double euclidean_distance(raw_image_t *a, raw_image_t *b, double p);

/**
 * @brief Manhattan distance between two samples also known as city-block distance (order 1 Minkowski distance)
 * 
 * @param a The first sample
 * @param b The second sample
 * @param p The order of the Minkowski metric (ignored in this case)
 * @return The computed Manhattan distance 
 */
double manhattan_distance(raw_image_t * a, raw_image_t *b, double p);

/**
 * @brief Minkowski distance between two samples
 * 
 * @param a The first sample
 * @param b The second sample
 * @param p The order of the Minkowski distance
 * @return The computer distance
 */
double minkowski_distance(raw_image_t * a, raw_image_t * b, double p);

#endif