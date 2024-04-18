/**
 * @file knn.c
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Definition of functions at the heart of the k-NN algorithm
 * @version 0.1
 * @date 2024-04-14
 */

#include "algorithm.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION

void compute_points_data(point_data_t **points_infos, int nb_train_samples, raw_image_t **samples_train, raw_image_t **samples_test, int i, bool weighted_knn, metric m, double p)
{
    for (int j = 0; j < nb_train_samples; j++)
    {
        (*points_infos)[j].distance = m(&(*samples_train)[j], &(*samples_test)[i], p);
        (*points_infos)[j].index = j;
        weighted_knn == true ? ((*points_infos)[j].weight = 1.0 / (*points_infos)[j].distance) : ((*points_infos)[j].weight = 1.0);
    }
}

int compare_samples(const void *a, const void *b)
{
    int result;
    const point_data_t *p_a = (const point_data_t *)a;
    const point_data_t *p_b = (const point_data_t *)b;

    if (p_a->distance < p_b->distance)
    {
        result = -1;
    }
    else if (p_a->distance > p_b->distance)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }

    return result;
}

void isolate_knns(point_data_t **k_nearest_neighbors, int k, point_data_t **points_infos)
{
    for (int l = 0; l < k; l++)
    {
        (*k_nearest_neighbors)[l] = (*points_infos)[l];
    }

}

void compute_weighted_counts(char ***votes, int k, char *class_labels[], double **counts, point_data_t **k_nearest_neighbors)
{
    for (int l = 0; l < NB_CLASSES; l++)
    {
        for (int m = 0; m < k; m++)
        {
            if (strcmp((*votes)[m], class_labels[l]) == 0)
            {
                (*counts)[l] += (1.0 * (*k_nearest_neighbors)[m].weight);
            }
        }
    } 
}


void find_prediction(int *max_votes, int *max_votes_index, int number_of_classes, double **counts, char **ans, char *class_labels[], char ***predictions, int i)
{
    *max_votes = (*counts)[0];
    *max_votes_index = 0;
    for (int l = 1; l < number_of_classes; l++)
    {
        if ((*counts)[l] > *max_votes)
        {
            *max_votes = (*counts)[l];
            *max_votes_index = l;
        }
    }
    strcpy(*ans, class_labels[*max_votes_index]);
    strcpy((*predictions)[i], *ans);
}