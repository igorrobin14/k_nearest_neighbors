/**
 * @file allocation.c
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Functions definitions for memory allocations for k-NN classification
 * @version 0.1
 * @date 2024-04-14
 */

#include "allocation.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION

raw_image_t *load_jpeg_image_file(char *image_path, raw_image_t *new_image)
{
    struct jpeg_decompress_struct info;
    struct jpeg_error_mgr err;

    raw_image_t new_im = {0, 0, 0, NULL, NULL};
    new_image->num_components = 0;
    new_image->width = 0;
    new_image->height = 0;

    unsigned long int new_image_width, new_image_height;
    int num_components;

    unsigned long int dw_buffer_bytes;
    unsigned char *new_image_data;

    unsigned char *row_buffer[1];

    FILE *fp = fopen(image_path, "rb");
    if (fp)
    {
        info.err = jpeg_std_error(&err);
        jpeg_create_decompress(&info);

        jpeg_stdio_src(&info, fp);
        jpeg_read_header(&info, TRUE);

        jpeg_start_decompress(&info);
        new_image_width = info.output_width;
        new_image_height = info.output_height;
        num_components = info.num_components;

        dw_buffer_bytes = new_image_width * new_image_height * NB_CHANNELS;
        new_image_data = (unsigned char *) malloc(dw_buffer_bytes * sizeof(unsigned char));

        new_image->num_components = num_components;
        new_image->width = new_image_width;
        new_image->height = new_image_height;
        new_image->image_data = new_image_data;

        while (info.output_scanline < info.output_height)
        {
            row_buffer[0] = (unsigned char *)(&new_image_data[NB_CHANNELS * info.output_width * info.output_scanline]);
            jpeg_read_scanlines(&info, row_buffer, 1);
        }

        jpeg_finish_decompress(&info);
        jpeg_destroy_decompress(&info);
        fclose(fp);
    }
    else
    {
        printf("Error opening file %s\n", image_path);
    }

    return new_image;
}

void allocate_file_paths(int **files_in_subfolders, char ****all_image_paths)
{
    *all_image_paths = (char ***) calloc(NB_CLASSES, sizeof(char **));

    for (int i = 0; i < NB_CLASSES; i++)
    {
        (*all_image_paths)[i] = (char **) calloc((*files_in_subfolders)[i], sizeof(char *));
        for (int j = 0; j < (*files_in_subfolders)[i]; j++)
        {
            (*all_image_paths)[i][j] = (char *) calloc(MAX_STR_LENGTH, sizeof(char));
        }
        
    }
}

void allocate_all_images(raw_image_t **image_array, int nb_samples, int **files_in_subfolders, char ****all_image_paths)
{
    int index = 0;
    *image_array = (raw_image_t *) calloc(nb_samples, sizeof(raw_image_t));
    for (int i = 0; i < NB_CLASSES; i++)
    {
        for (int j = 0; j < (*files_in_subfolders)[i]; j++)
        {
            raw_image_t new_im = {0, 0, 0, NULL, NULL};
            (*image_array)[index] = *load_jpeg_image_file((*all_image_paths)[i][j], &new_im);
            index++;
        }
    }
}

void allocate_predicted_classes(char ***predictions, int nb_test_samples)
{
    *predictions = (char **) calloc(nb_test_samples, sizeof(char *));
 
    for (int i = 0; i < nb_test_samples; i++)
    {
        (*predictions)[i] = (char *) calloc(MAX_STR_LENGTH, sizeof(char));
    }
}

void allocate_is_right_class(bool **is_right_class, int nb_test_samples)
{
    *is_right_class = (bool *) calloc(nb_test_samples, sizeof(bool));
}

void allocate_points_data(point_data_t ***points_infos, int nb_train_samples, int nb_test_samples)
{
    *points_infos = (point_data_t **) calloc(nb_test_samples, sizeof(point_data_t *));
    for (int i = 0; i < nb_test_samples; i++)
    {
        (*points_infos)[i] = (point_data_t *) calloc(nb_train_samples, sizeof(point_data_t));
    }
}

void allocate_knns(point_data_t ***k_nearest_neighbors, int k, int nb_test_samples)
{
    *k_nearest_neighbors = (point_data_t **) calloc(nb_test_samples, sizeof(point_data_t *));
    
    for (int i = 0; i < nb_test_samples; i++)
    {
        (*k_nearest_neighbors)[i] = (point_data_t *) calloc(k, sizeof(point_data_t));
    }
}

void allocate_votes(char ****votes, int k, int nb_test_samples)
{
    *votes = (char ***) calloc(nb_test_samples, sizeof(char **));
    for (int i = 0; i < nb_test_samples; i++)
    {
        (*votes)[i] = (char **) calloc(k, sizeof(char *));
        for (int l = 0; l < k; l++)
        {
            (*votes)[i][l] = (char *) calloc(MAX_STR_LENGTH, sizeof(char));
        }
    }
}

void allocate_counts(double ***counts, int nb_test_samples)
{
    *counts = (double **) calloc (nb_test_samples, sizeof(double *));

    for (int i = 0; i < nb_test_samples; i++)
    {
        (*counts)[i] = (double *) calloc(NB_CLASSES, sizeof(double));
    }
}

void allocate_ans(char ***ans, int nb_test_samples)
{
    *ans = (char **) calloc (nb_test_samples, sizeof(char *));

    for (int i = 0; i < nb_test_samples; i++)
    {
        (*ans)[i] = (char *) calloc(MAX_STR_LENGTH, sizeof(char));
    }
}

void fill_votes(char ****votes, raw_image_t **samples_train, point_data_t ***k_nearest_neighbors, int k, int nb_test_samples)
{
    for (int i = 0; i < nb_test_samples; i++)
    {
        for (int l = 0; l < k; l++)
        {
            strcpy((*votes)[i][l], (*samples_train)[(*k_nearest_neighbors)[i][l].index].class);
        }
    }
}

void allocate_results(result_t *r, double **true_positives, double **false_positives, double **false_negatives, int nb_test_samples)
{
    r->f1_scores = (double *) calloc(NB_CLASSES, sizeof(double));
    r->precisions = (double *) calloc(NB_CLASSES, sizeof(double));
    r->recalls = (double *) calloc(NB_CLASSES, sizeof(double));
    r->supports = (double *) calloc(NB_CLASSES, sizeof(double));
    *true_positives = (double *) calloc(NB_CLASSES, sizeof(double));
    *false_positives = (double *) calloc(NB_CLASSES, sizeof(double));
    *false_negatives = (double *) calloc(NB_CLASSES, sizeof(double));
}

void free_results(double **true_positives, double **false_positives, double **false_negatives, result_t *r)
{
    free(r->f1_scores);
    free(r->precisions);
    free(r->recalls);
    free(r->supports);

    free(*true_positives);
    free(*false_positives);
    free(*false_negatives);
}

void free_data(point_data_t ***points_infos, point_data_t ***k_nearest_neighbors, char ****votes, double ***counts, char ***ans, raw_image_t **image_array, raw_image_t **resized_image_array, raw_image_t **train_image_array, raw_image_t **test_image_array, int **files_in_subfolders, char ***predictions, bool **is_right_class, char ****all_image_paths, int k, int nb_test_samples)
{
    for (int i = 0; i < NB_CLASSES; i++)
    {
        for (int j = 0; j < (*files_in_subfolders)[i]; j++)
        {
            free((*all_image_paths)[i][j]);
        }
        free((*all_image_paths)[i]);
    }
    free(*all_image_paths);

    int index = 0;
    for (int i = 0; i < NB_CLASSES; i++)
    {
        for (int j = 0; j < (*files_in_subfolders)[i]; j++)
        {
            free((*image_array)[index].image_data);
            free((*resized_image_array)[index].image_data);
            free((*resized_image_array)[index].class);
            index++;
        }
    }

    free(*image_array);
    free(*resized_image_array);
    free(*train_image_array);
    free(*test_image_array);
    free(*is_right_class);

    for (int i = 0; i < nb_test_samples; i++)
    {
        free((*predictions)[i]);
        free((*points_infos)[i]);
        free((*k_nearest_neighbors)[i]);
        for (int l = 0; l < k; l++)
        {
            free((*votes)[i][l]);
        }
        free((*votes)[i]);
        free((*counts)[i]);
        free((*ans)[i]);
    }

    free(*points_infos);
    free(*k_nearest_neighbors);
    free(*predictions);
    free(*votes);
    free(*counts);
    free(*ans);
    free(*files_in_subfolders);
}

