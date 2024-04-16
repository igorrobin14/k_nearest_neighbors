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

void allocate_points_infos(point_info_t **points_infos, int nb_train_samples)
{
    *points_infos = (point_info_t *) calloc(nb_train_samples, sizeof(point_info_t));
}

void allocate_test_images(raw_image_t **test_images, int nb_test_samples)
{
    *test_images = (raw_image_t *) calloc(nb_test_samples, sizeof(raw_image_t));
    for (int j = 0; j < nb_test_samples; j++)
    {
        (*test_images)[j].image_data = (unsigned char *) calloc(RESIZED_IMG_SIZE * RESIZED_IMG_SIZE * NB_CHANNELS, sizeof(unsigned char));
    }
    
}

void allocate_knns(point_info_t **k_nearest_neighbors, int k)
{
    *k_nearest_neighbors = (point_info_t *) calloc(k, sizeof(point_info_t));
}

void allocate_file_paths(int **files_per_subfolder, char ****file_paths)
{
    *file_paths = (char ***) calloc(NB_CLASSES, sizeof(char **));

    for (int i = 0; i < NB_CLASSES; i++)
    {
        (*file_paths)[i] = (char **) calloc((*files_per_subfolder)[i], sizeof(char *));
        for (int j = 0; j < (*files_per_subfolder)[i]; j++)
        {
            (*file_paths)[i][j] = (char *) calloc(MAX_PATH_LENGTH, sizeof(char));
        }
        
    }
}

void allocate_votes_counts_ans(char ***votes, double **counts, char **ans, int k, int number_of_classes, char *class_labels[], raw_image_t **samples_train, point_info_t **k_nearest_neighbors)
{
    *votes = (char **) calloc(k, sizeof(char *));
    for (int l = 0; l < k; l++)
    {
        (*votes)[l] = calloc(MAX_STR_LENGTH, sizeof(char));
    }

    for (int l = 0; l < k; l++)
    {
        strcpy((*votes)[l], (*samples_train)[(*k_nearest_neighbors)[l].index].class);
    }

    *counts = (double *) calloc(NB_CLASSES, sizeof(double));
    *ans = (char *) calloc(MAX_STR_LENGTH, sizeof(char));

    for (int l = 0; l < number_of_classes; l++)
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

void allocate_all_images(raw_image_t **image_array, int nb_samples, int **files_per_subfolder, char ****file_paths)
{
    int index = 0;
    *image_array = (raw_image_t *) calloc(nb_samples, sizeof(raw_image_t));
    for (int i = 0; i < NB_CLASSES; i++)
    {
        for (int j = 0; j < (*files_per_subfolder)[i]; j++)
        {
            (*image_array)[index] = load_jpeg_image_file((*file_paths)[i][j]);
            index++;
        }
    }
}

void allocate_preditions_and_results(char ***predictions, bool **results, int nb_test_samples)
{
    *predictions = (char **) calloc(nb_test_samples, sizeof(char *));
 
    for (int i = 0; i < nb_test_samples; i++)
    {
        (*predictions)[i] = (char *) calloc(MAX_STR_LENGTH, sizeof(char));
    }

    *results = (bool *) calloc(nb_test_samples, sizeof(bool));
}

void free_loop_data(point_info_t **points_infos, point_info_t **k_nearest_neighbors, char ***votes, double **counts, char **ans, int k)
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
    *true_positives = (double *) calloc(nb_test_samples, sizeof(double));
    *false_positives = (double *) calloc(nb_test_samples, sizeof(double));
    *false_negatives = (double *) calloc(nb_test_samples, sizeof(double));
}