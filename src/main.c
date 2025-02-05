/**
 * @file main.c
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief The k-Nearest-Neighbors algorithm applied to classification on a dataset of flower images
 * Every header is commented with the purpose of the functions and the meaning of the parameters
 * @version 0.1
 * @date 2024-04-14
 */

#include "algorithm.h"
#include "allocation.h"
#include "metrics.h"
#include "preprocessing.h"
#include "types_constants.h"
#include "results.h"

// new branch

int main(void)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int k = 10;
    bool weighted_knn = false;

    metric m = minkowski_distance;
    int p = 3;

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

    char ***all_image_paths = NULL; 
 
    int *files_in_subfolders = NULL;
    int nb_samples = 0;

    double test_size = 0.2;
    int nb_test_samples = 0;
    int nb_train_samples = 0;

    raw_image_t *image_array = NULL;
    raw_image_t *resized_image_array = NULL;
    raw_image_t *test_image_array = NULL;
    raw_image_t *train_image_array = NULL;

    point_data_t **points_data = NULL;
    point_data_t **k_nearest_neighbors = NULL;

    char ***votes = NULL;
    double **counts = NULL;
    char **ans = NULL;
    int max_votes = 0, max_votes_index = 0;
    int nb_trues = 0, nb_falses = 0;

    char **predictions = NULL;
    bool *is_right_class = NULL;

    result_t r;
    double *true_positives = NULL;
    double *false_positives = NULL;
    double *false_negatives = NULL;
    double *supports = NULL;

    count_files_in_subfolders_and_nb_samples(&files_in_subfolders, flower_folder_paths, &nb_samples);

    allocate_file_paths(&files_in_subfolders, &all_image_paths);
    fill_all_image_paths(&all_image_paths, flower_folder_paths);

    allocate_all_images(&image_array, nb_samples, &files_in_subfolders, &all_image_paths);
    resize_all_images(&image_array, nb_samples, &files_in_subfolders, &resized_image_array);
    
    bind_image_to_class(class_labels, files_in_subfolders, &resized_image_array);

    /**
     * @brief Here, either a random shuffle can be used for the images or a deterministic shuffle can be applied (a .txt file with the indexes is read)
     * Uncomment or comment the desired version
     */
    //random_shuffle(resized_image_array, nb_samples, seed);
    shuffle_from_index_list(resized_image_array, nb_samples);

    train_test_split(test_size, nb_samples, &train_image_array, &test_image_array, &resized_image_array, &nb_test_samples, &nb_train_samples);

    allocate_predicted_classes(&predictions, nb_test_samples);
    allocate_is_right_class(&is_right_class, nb_test_samples);

    allocate_points_data(&points_data, nb_train_samples, nb_test_samples);
    
    printf("nb test samples: %d\n", nb_test_samples);

    /**
     * @brief For multithreaded version
     */
    thread_data_t part_indexes[NB_THREADS];
    pthread_t threads[NB_THREADS];

    for (int i = 0; i < NB_THREADS; i++)
    {
        part_indexes[i].start_index = i * (nb_test_samples / NB_THREADS);
        part_indexes[i].end_index = (i + 1) * (nb_test_samples / NB_THREADS);
        part_indexes[i].points_data = points_data;
        part_indexes[i].nb_train_samples = nb_train_samples;
        part_indexes[i].samples_test = &test_image_array;
        part_indexes[i].samples_train = &train_image_array;
        part_indexes[i].m = m;
        part_indexes[i].p = p;
        part_indexes[i].weighted_knn = weighted_knn;
    }

    struct timespec start_compute_distances, end_compute_distances;
    clock_gettime(CLOCK_MONOTONIC, &start_compute_distances);

    for (int i = 0; i < NB_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, process_part, (void *)&part_indexes[i]);
    }

    for (int i = 0; i < NB_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    compute_points_data_rest(points_data, nb_train_samples, nb_test_samples, &train_image_array, &test_image_array, weighted_knn, m, p);

    clock_gettime(CLOCK_MONOTONIC, &end_compute_distances);

    double elapsed_compute_distances = (end_compute_distances.tv_sec - start_compute_distances.tv_sec) + (end_compute_distances.tv_nsec - start_compute_distances.tv_nsec) / 1e9;

    // Check is execution time measure is correct
    printf("Execution time to compute all distances: %.2f seconds\n", elapsed_compute_distances);

    /**
     * End of multithreaded version
     */
    
    /***
     * @brief To uncomment if using single threaded version or NB_THREADS can also be put to 1
     */
    //compute_points_data(points_data, nb_train_samples, nb_test_samples, &train_image_array, &test_image_array, weighted_knn, m, p);

    allocate_knns(&k_nearest_neighbors, k, nb_test_samples);
    isolate_knns(k_nearest_neighbors, k, nb_test_samples, points_data);

    allocate_votes(&votes, k, nb_test_samples);
    allocate_counts(&counts, nb_test_samples);
    allocate_ans(&ans, nb_test_samples);

    fill_votes(&votes, &train_image_array, &k_nearest_neighbors, k, nb_test_samples);
    compute_weighted_counts(&votes, k, class_labels, &counts, &k_nearest_neighbors, nb_test_samples);

    find_prediction(&max_votes, &max_votes_index, &counts, &ans, class_labels, &predictions, nb_test_samples);

    allocate_results(&r, &true_positives, &false_positives, &false_negatives, nb_test_samples);
    compute_accuracy(&r, nb_test_samples, &predictions, &test_image_array, &is_right_class, &nb_trues, &nb_falses);
    compute_true_positives(&predictions, &test_image_array, class_labels, nb_test_samples, &true_positives);
    compute_false_positives(&predictions, &test_image_array, class_labels, nb_test_samples, &false_positives);
    compute_false_negatives(&predictions, &test_image_array, class_labels, nb_test_samples, &false_negatives);
    compute_results(&r, &true_positives, &false_positives, &false_negatives, class_labels, &test_image_array, nb_test_samples);
    display_results(&r, class_labels);

    free_data(&points_data, &k_nearest_neighbors, &votes, &counts, &ans, &image_array, &resized_image_array, &train_image_array, &test_image_array, &files_in_subfolders, &predictions, &is_right_class, &all_image_paths, k, nb_test_samples);
    free_results(&true_positives, &false_positives, &false_negatives, &r);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Check is execution time measure is correct
    printf("Execution time: %.2f seconds\n", elapsed);

    return 0;
}