/**
 * @file preprocessing.c
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief 
 * @version 0.1
 * @date 2024-04-18
 */

#include "preprocessing.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

void * safe_alloc(size_t element_size, size_t num_elements)
{
    void * ptr = malloc(element_size * num_elements);

    if (!ptr) 
    {
        printf("Memory allocation failed for %zu elements\n", num_elements);
    }

    return ptr;
}

int count_files_in_folder(const char *folder_path)
{
    DIR *dir;
    struct dirent *ent;
    int file_count = 0;

    if ((dir = opendir(folder_path)) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG)
            {
                file_count++;
            }
        }

        closedir(dir);
    }

    return file_count;
}

void count_files_in_main_folder(dataset_t * dataset)
{
    dataset->nb_samples = 0;

    for (int i = 0; i < NB_CLASSES; i++)
    {
        dataset->folders[i].nb_files_contained = count_files_in_folder(dataset->folders[i].path);
        dataset->nb_samples += dataset->folders[i].nb_files_contained;
    }
}

void init_data_location(dataset_t * dataset)
{
    dataset->class_labels[0] = "daisy";
    dataset->class_labels[1] = "dandelion";
    dataset->class_labels[2] = "rose";
    dataset->class_labels[3] = "sunflower";
    dataset->class_labels[4] = "tulip";

    strcpy(dataset->main_folder_path, "../flowers/");

    for (int i = 0; i < NB_CLASSES; i++)
    {
        char path[MAX_STR_LENGTH];
        strcpy(path, dataset->main_folder_path);
        strcat(path, dataset->class_labels[i]);
        strcat(path, "/");
        strcpy(dataset->folders[i].path, path);
    }
}

void set_all_image_paths(dataset_t * dataset)
{
    DIR *dir;
    struct dirent *ent;
    int file_index = 0;
    char file_path[256];

    for (int i = 0; i < NB_CLASSES; i++)
    {
        if ((dir = opendir(dataset->folders[i].path)) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                if (ent->d_type == DT_REG)
                {
                    strcpy(file_path, dataset->folders[i].path);
                    //printf("%s\n", dataset->folders[i].path);
                    strcat(file_path, ent->d_name);
                    //printf("%s\n", ent->d_name);
                    strcpy(dataset->images[file_index].path, file_path);
                    
                    file_index++;
                }
                
            }
            closedir(dir);
        }
    }
}

void map_images_to_class(dataset_t * dataset)
{
    unsigned int image_index = 0;
    for (int i = 0; i < NB_CLASSES; i++)
    {
        for (int j = 0; j < dataset->folders[i].nb_files_contained; j++)
        {
            strcpy(dataset->images[image_index].class_label, dataset->class_labels[i]);
            image_index++;
        }
    }
}

void load_all_images(dataset_t * dataset)
{
    for (int i = 0; i < dataset->nb_samples; i++)
    {
        load_jpeg_image_file(&dataset->images[i]);

        //printf("50th pixel, %d\n", dataset->images[i].pixels[49]);
    }
}

void load_jpeg_image_file(image_t * loaded_image)
{
    struct jpeg_decompress_struct info;
    struct jpeg_error_mgr err;

    // raw_image_t new_im = {0, 0, 0, NULL, NULL};
    // new_image->num_components = 0;
    // new_image->width = 0;
    // new_image->height = 0;
    loaded_image->width = 0;
    loaded_image->height = 0;
    loaded_image->num_components = 0;
    loaded_image->pixels = NULL;

    unsigned long int new_image_width, new_image_height;
    int new_image_num_components;

    unsigned long int dw_buffer_bytes;
    unsigned char * new_image_data;

    unsigned char * row_buffer[1];

    FILE *fp = fopen(loaded_image->path, "rb");
    if (fp)
    {
        info.err = jpeg_std_error(&err);
        jpeg_create_decompress(&info);

        jpeg_stdio_src(&info, fp);
        jpeg_read_header(&info, TRUE);

        jpeg_start_decompress(&info);
        new_image_width = info.output_width;
        new_image_height = info.output_height;
        new_image_num_components = info.num_components;

        dw_buffer_bytes = new_image_width * new_image_height * NB_CHANNELS;
        //new_image_data = (unsigned char *) malloc(dw_buffer_bytes * sizeof(unsigned char));
        new_image_data = alloc_array(unsigned char, dw_buffer_bytes);

        loaded_image->num_components = new_image_num_components;
        loaded_image->width = new_image_width;
        loaded_image->height = new_image_height;
        loaded_image->pixels = new_image_data;

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
        printf("Error opening file %s\n", loaded_image->path);
    }

    //return new_image;
}

void resize_all_images(dataset_t * initial_dataset, dataset_t * processed_dataset)
{
    processed_dataset->images = alloc_array(image_t, initial_dataset->nb_samples);
    for (int i = 0; i < initial_dataset->nb_samples; i++)
    {
        //printf("i: %d\n", i);
        processed_dataset->images[i].pixels = alloc_array(unsigned char, RESIZED_IMG_SIZE * RESIZED_IMG_SIZE * NB_CHANNELS);
        stbir_resize_uint8_linear(initial_dataset->images[i].pixels, initial_dataset->images[i].width, initial_dataset->images[i].height, 0, processed_dataset->images[i].pixels, RESIZED_IMG_SIZE, RESIZED_IMG_SIZE, 0, STBIR_RGB);
    }

    processed_dataset->nb_samples = initial_dataset->nb_samples;
}

void train_test_split(dataset_t * dataset, double test_size)
{
    dataset->test_train_separation = &(dataset->images[(int) ((double) dataset->nb_samples * test_size)]);
}

// void bind_image_to_class(char *class_labels[], int *files_in_subfolders, raw_image_t **resized_image_array)
// {
//     int index = 0;
//     for (int i = 0; i < NB_CLASSES; i++)
//     {
//         for (int j = 0; j < files_in_subfolders[i]; j++)
//         {
//             (*resized_image_array)[index].class = (char *) calloc(MAX_STR_LENGTH, sizeof(char));
//             strcpy((*resized_image_array)[index].class, class_labels[i]);
//             index++;
//         }
//     }
// }

// void random_shuffle(raw_image_t *samples, int nb_samples, unsigned int seed)
// {
//     srand(seed);
//     int j;
//     raw_image_t temp_sample;
    
//     for (int i = nb_samples - 1; i > 0; i--)
//     {
//         j = rand() % (i + 1);
        
//         memcpy(&temp_sample, &samples[i], sizeof(raw_image_t));
//         memcpy(&samples[i], &samples[j], sizeof(raw_image_t));
//         memcpy(&samples[j], &temp_sample, sizeof(raw_image_t));
//     }
// }

// void train_test_split(double test_size, int nb_samples, raw_image_t **train_image_array, raw_image_t **test_image_array, raw_image_t **resized_image_array, int *nb_test_samples, int *nb_train_samples)
// {
//     *nb_test_samples = (int) ((double) nb_samples * test_size);
//     *nb_train_samples = nb_samples - *nb_test_samples;

//     *train_image_array = (raw_image_t *) calloc(*nb_train_samples, sizeof(raw_image_t));
//     *test_image_array = (raw_image_t *) calloc(*nb_test_samples, sizeof(raw_image_t));

//     int index = 0;

//     for (int j = 0; j < *nb_train_samples; j++)
//     {
//         (*train_image_array)[index] = (*resized_image_array)[index];
//         index++;
//     }
    
//     int second_index = 0;

//     for (int j = 0; j < *nb_test_samples; j++)
//     {
//         (*test_image_array)[second_index] = (*resized_image_array)[index];
        
//         index++;
//         second_index++;
//     }
// }

// void save_jpeg_image_file(raw_image_t *image, char *file_path)
// {
//     struct jpeg_compress_struct info;
//     struct jpeg_error_mgr err;

//     unsigned char *row_buffer[1];

//     FILE *fp = fopen(file_path, "wb");
//     if (fp)
//     {
//         info.err = jpeg_std_error(&err);
//         jpeg_create_compress(&info);
//         jpeg_stdio_dest(&info, fp);
        
//         info.image_width = image->width;
//         info.image_height = image->height;
//         info.input_components = NB_CHANNELS;
//         info.in_color_space = JCS_RGB;

//         jpeg_set_defaults(&info);
//         jpeg_set_quality(&info, IMG_QUALITY, TRUE);
//         jpeg_start_compress(&info, TRUE);

//         while (info.next_scanline < info.image_height)
//         {
//             row_buffer[0] = &(image->image_data[info.next_scanline * (image->width * NB_CHANNELS)]);
//             jpeg_write_scanlines(&info, row_buffer, 1);
//         }

//         jpeg_finish_compress(&info);
//         fclose(fp);
//         jpeg_destroy_compress(&info);
//     }
//     else
//     {
//         printf("Error opening file %s for writing\n", file_path);
//     }
// }

void shuffle_from_index_list(dataset_t * dataset)
{
    const char * file_name = "../shuffled_indexes.txt";

    FILE * fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("Error opening file\n");
    }
    else
    {
        int index_array_size;
        int result = fscanf(fp, "%d", &index_array_size);

        int * index_array = alloc_array(int, index_array_size);

        for (int i = 0; i < index_array_size; i++)
        {
            result = fscanf(fp, "%d", &index_array[i]);
        }

        image_t * new_sample_array = alloc_array(image_t, dataset->nb_samples);

        for (int i = 0; i < index_array_size; i++)
        {
            memcpy(&new_sample_array[i], &dataset->images[index_array[i]], sizeof(image_t));
        }

        for (int i = 0; i < dataset->nb_samples; i++)
        {
            memcpy(&dataset->images[i], &new_sample_array[i], sizeof(image_t));
        }

        fclose(fp);
    }
}