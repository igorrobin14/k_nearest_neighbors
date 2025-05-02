/**
 * @file algorithm.c
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Central functions in the k-NN algorithm
 * @version 0.1
 * @date 2024-04-18
 */

#include "algorithm.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION

void *process_part(void *arg)
{
    thread_data_t *data = (thread_data_t *) arg;
    int start = data->start_index;
    int end = data->end_index;

    point_data_t **points_data = data->points_data;
    int nb_train_samples = data->nb_train_samples;
    raw_image_t **samples_test = data->samples_test;
    raw_image_t **samples_train = data->samples_train;
    int p = data->p;
    bool weighted_knn = data->weighted_knn;
    metric m = data->m;


    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < nb_train_samples; j++)
        {
            points_data[i][j].distance = m(&(*samples_train)[j], &(*samples_test)[i], p);
            points_data[i][j].index = j;
            weighted_knn == true ? (points_data[i][j].weight = 1.0 / points_data[i][j].distance) : (points_data[i][j].weight = 1.0);
        }
        // printf("i: %d\n", i);

        qsort(points_data[i], nb_train_samples, sizeof(point_data_t), compare_samples);
    }
}


void compute_points_data(point_data_t **points_data, int nb_train_samples, int nb_test_samples, raw_image_t **samples_train, raw_image_t **samples_test, bool weighted_knn, metric m, double p)
{
    for (int i = 0; i < nb_test_samples; i++)
    {
        for (int j = 0; j < nb_train_samples; j++)
        {
            points_data[i][j].distance = m(&(*samples_train)[j], &(*samples_test)[i], p);
            points_data[i][j].index = j;
            weighted_knn == true ? (points_data[i][j].weight = 1.0 / points_data[i][j].distance) : (points_data[i][j].weight = 1.0);
        }
        // printf("i: %d\n", i);

        qsort(points_data[i], nb_train_samples, sizeof(point_data_t), compare_samples);
    }
}

void compute_points_data_rest(point_data_t **points_data, int nb_train_samples, int nb_test_samples, raw_image_t **samples_train, raw_image_t **samples_test, bool weighted_knn, metric m, double p)
{
    for (int i = nb_test_samples - (nb_test_samples % NB_THREADS); i < nb_test_samples; i++)
    {
        for (int j = 0; j < nb_train_samples; j++)
        {
            points_data[i][j].distance = m(&(*samples_train)[j], &(*samples_test)[i], p);
            points_data[i][j].index = j;
            weighted_knn == true ? (points_data[i][j].weight = 1.0 / points_data[i][j].distance) : (points_data[i][j].weight = 1.0);
        }
        // printf("i: %d\n", i);

        qsort(points_data[i], nb_train_samples, sizeof(point_data_t), compare_samples);
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

void isolate_knns(point_data_t **k_nearest_neighbors, int k, int nb_test_samples, point_data_t **points_infos)
{
    for (int i = 0; i < nb_test_samples; i++)
    {
        for (int l = 0; l < k; l++)
        {
            k_nearest_neighbors[i][l] = points_infos[i][l];
        }
    }

}

void compute_weighted_counts(char ****votes, int k, char *class_labels[], double ***counts, point_data_t ***k_nearest_neighbors, int nb_test_samples)
{
    for (int i = 0; i < nb_test_samples; i++)
    {
        for (int l = 0; l < NB_CLASSES; l++)
        {
            for (int m = 0; m < k; m++)
            {
                if (strcmp((*votes)[i][m], class_labels[l]) == 0)
                {
                    (*counts)[i][l] += (1.0 * (*k_nearest_neighbors)[i][m].weight);
                }
            }
        } 
    }
}


void find_prediction(int *max_votes, int *max_votes_index, double ***counts, char ***ans, char *class_labels[], char ***predictions, int nb_test_samples)
{
    for (int i = 0; i < nb_test_samples; i++)
    {
        *max_votes = (*counts)[i][0];
        *max_votes_index = 0;
        for (int l = 1; l < NB_CLASSES; l++)
        {
            if ((*counts)[i][l] > *max_votes)
            {
                *max_votes = (*counts)[i][l];
                *max_votes_index = l;
            }
        }
        strcpy((*ans)[i], class_labels[*max_votes_index]);
        strcpy((*predictions)[i], (*ans)[i]);
    }
}