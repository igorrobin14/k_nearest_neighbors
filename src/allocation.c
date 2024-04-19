/**
 * @file allocation.c
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Functions definitions for memory allocations for k-NN classification
 * @version 0.1
 * @date 2024-04-14
 */

#include "allocation.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION

raw_image_t load_jpeg_image_file(char *image_path)
{
    struct jpeg_decompress_struct info;
    struct jpeg_error_mgr err;

    raw_image_t new_image = {0, 0, 0, NULL, NULL};

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

        new_image.num_components = num_components;
        new_image.width = new_image_width;
        new_image.height = new_image_height;
        new_image.image_data = new_image_data;

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
            (*image_array)[index] = load_jpeg_image_file((*all_image_paths)[i][j]);
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



void allocate_points_data(point_data_t **points_infos, int nb_train_samples)
{
    *points_infos = (point_data_t *) calloc(nb_train_samples, sizeof(point_data_t));
}

void allocate_knns(point_data_t **k_nearest_neighbors, int k)
{
    *k_nearest_neighbors = (point_data_t *) calloc(k, sizeof(point_data_t));
}

void allocate_votes(char ***votes, int k)
{
    *votes = (char **) calloc(k, sizeof(char *));
    for (int l = 0; l < k; l++)
    {
        (*votes)[l] = calloc(MAX_STR_LENGTH, sizeof(char));
    }
}

void allocate_counts(double **counts)
{
    *counts = (double *) calloc(NB_CLASSES, sizeof(double));
}

void allocate_ans(char **ans)
{
    *ans = (char *) calloc(MAX_STR_LENGTH, sizeof(char));
}

void fill_votes(char ***votes, raw_image_t **samples_train, point_data_t **k_nearest_neighbors, int k)
{
    for (int l = 0; l < k; l++)
    {
        strcpy((*votes)[l], (*samples_train)[(*k_nearest_neighbors)[l].index].class);
    }
}



void free_loop_data(point_data_t **points_infos, point_data_t **k_nearest_neighbors, char ***votes, double **counts, char **ans, int k)
{
    free(*points_infos);
    free(*k_nearest_neighbors);
    for (int l = 0; l < k; l++)
    {
        free((*votes)[l]);
    }
    free(*votes);
    free(*counts);
    free(*ans);
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