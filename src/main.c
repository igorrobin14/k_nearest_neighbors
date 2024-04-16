/**
 * @file main.c
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief The k-Nearest-Neighbors classification and algorithm applied to a dataset of images of flowers
 * Every header is commented with the purpose of the functions, the meaning of the function parameters and returns
 * @version 0.1
 * @date 2024-04-14
 */

#include "knn.h"
#include "allocation.h"
#include "metrics.h"
#include "image.h"
#include "constants.h"
#include "types.h"
#include "results.h"

int main(void)
{
    int k = 10;
    bool weighted_knn = false;

    metric m = euclidean_distance;
    double p = 2;

    unsigned int seed = time(NULL);

    char *class_labels[NB_CLASSES] = {"daisy", "dandelion", "rose", "sunflower", "tulip"};

    char *flower_folder_paths[NB_CLASSES] = 
    {
        "../flowers/train/daisy/", 
        "../flowers/train/dandelion/", 
        "../flowers/train/rose/", 
        "../flowers/train/sunflower/", 
        "../flowers/train/tulip/"
    };

    char ***file_paths = NULL; 
 
    int *files_per_subfolder;
    int nb_samples = 0;

    double test_size = 0.2;
    int nb_test_samples;
    int nb_train_samples;

    raw_image_t *image_array = NULL;
    raw_image_t *resized_image_array = NULL;
    raw_image_t *test_image_array = NULL;
    raw_image_t *train_image_array = NULL;

    point_info_t *points_infos;
    point_info_t *k_nearest_neighbors;

    char **votes;
    double *counts;
    char *ans;
    int max_votes, max_votes_index;
    int nb_trues = 0, nb_falses = 0;

    char **predictions = NULL;
    bool *results = NULL;

    result_t r;
    double *true_positives = NULL;
    double *false_positives = NULL;
    double *false_negatives = NULL;
    double *supports = NULL;

    count_files_per_subfolder_and_nb_samples(&files_per_subfolder, flower_folder_paths, &nb_samples);
    allocate_file_paths(&files_per_subfolder, &file_paths);
    fill_file_paths(&file_paths, flower_folder_paths);

    allocate_all_images(&image_array, nb_samples, &files_per_subfolder, &file_paths);
    resize_all_images(&image_array, nb_samples, &files_per_subfolder, &resized_image_array);
    
    map_image_to_class(class_labels, files_per_subfolder, &resized_image_array);
    random_shuffle(resized_image_array, nb_samples, seed);
    train_test_split(test_size, nb_samples, &train_image_array, &test_image_array, &resized_image_array, &nb_test_samples, &nb_train_samples);

    allocate_preditions_and_results(&predictions, &results, nb_test_samples);

    for (int i = 0; i < nb_test_samples; i++)
    {
        allocate_points_infos(&points_infos, nb_train_samples);
        compute_points_infos(&points_infos, nb_train_samples, &train_image_array, &test_image_array, i, weighted_knn, m, p);

        qsort(points_infos, nb_train_samples, sizeof(point_info_t), compare_samples);
        allocate_knns(&k_nearest_neighbors, k);
        isolate_knns(&k_nearest_neighbors, k, &points_infos);

        allocate_votes_counts_ans(&votes, &counts, &ans, k, NB_CLASSES, class_labels, &train_image_array, &k_nearest_neighbors);

        find_prediction(&max_votes, &max_votes_index, NB_CLASSES, &counts, &ans, class_labels, &predictions, i);

        free_loop_data(&points_infos, &k_nearest_neighbors, &votes, &counts, &ans, k);
        printf("Percentage done : %lf \n", (double) i / (double) nb_test_samples * 100);
    }

    predictions_vs_expected(nb_test_samples, &predictions, &test_image_array, &results, &nb_trues, &nb_falses);
    allocate_results(&r, &true_positives, &false_positives, &false_negatives, nb_test_samples);
    compute_true_positives(&predictions, &test_image_array, class_labels, nb_test_samples, &true_positives);
    compute_false_positives(&predictions, &test_image_array, class_labels, nb_test_samples, &false_positives);
    compute_false_negatives(&predictions, &test_image_array, class_labels, nb_test_samples, &false_negatives);
    compute_results(&r, &true_positives, &false_positives, &false_negatives, class_labels, &test_image_array, nb_test_samples);
    r.accuracy = compute_accuracy(nb_trues, nb_test_samples);
    
    display_results(&r, class_labels);

    return 0;
}