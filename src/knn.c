/**
 * @file knn.c
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Definition of functions at the heart of the k-NN algorithm
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright 
 * 
 */

#include "knn.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION

void random_shuffle(raw_image_t *samples, int nb_samples, unsigned int seed)
{
    srand(seed);
    int j;
    raw_image_t temp_sample;
    
    for (int i = nb_samples - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        
        memcpy(&temp_sample, &samples[i], sizeof(raw_image_t));
        memcpy(&samples[i], &samples[j], sizeof(raw_image_t));
        memcpy(&samples[j], &temp_sample, sizeof(raw_image_t));
    }
}

void compute_points_infos(point_info_t **points_infos, int nb_train_samples, raw_image_t **samples_train, raw_image_t **samples_test, int i, bool weighted_knn, metric m, double p)
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
    const point_info_t *p_a = (const point_info_t *)a;
    const point_info_t *p_b = (const point_info_t *)b;

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

void isolate_knns(point_info_t **k_nearest_neighbors, int k, point_info_t **points_infos)
{
    for (int l = 0; l < k; l++)
    {
        (*k_nearest_neighbors)[l] = (*points_infos)[l];
    }

}

void predictions_vs_expected(int nb_test_samples, char ***predictions, raw_image_t **samples_test, bool **results, int *nb_trues, int *nb_falses)
{
    for (int i = 0; i < nb_test_samples; i++)
    {
        strcmp((*predictions)[i], (*samples_test)[i].class) == 0 ? ((*results)[i] = true) : ((*results)[i] = false);
        (*results)[i] == true ? ((*nb_trues)++) : ((*nb_falses)++);
        printf("predictions[%d] : %s, samples_test[%d].class : %s\n", i, (*predictions)[i], i, (*samples_test)[i].class);
    }
}

void train_test_split(double test_size, int nb_samples, raw_image_t **train_image_array, raw_image_t **test_image_array, raw_image_t **resized_image_array, int *nb_test_samples, int *nb_train_samples)
{
    *nb_test_samples = (int) ((double) nb_samples * test_size);
    *nb_train_samples = nb_samples - *nb_test_samples;

    *train_image_array = (raw_image_t *) calloc(*nb_train_samples, sizeof(raw_image_t));
    *test_image_array = (raw_image_t *) calloc(*nb_test_samples, sizeof(raw_image_t));

    int index = 0;

    for (int j = 0; j < *nb_train_samples; j++)
    {
        (*train_image_array)[index] = (*resized_image_array)[index];
        index++;
    }
    
    int second_index = 0;

    for (int j = 0; j < *nb_test_samples; j++)
    {
        (*test_image_array)[second_index] = (*resized_image_array)[index];
        
        index++;
        second_index++;
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