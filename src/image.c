/**
 * @file image.c
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Definition of functions for image processing and path management
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright 
 * 
 */
#include "image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

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

void count_files_per_subfolder_and_nb_samples(int **files_per_subfolder, char *flower_folder_paths[], int *nb_samples)
{
    *files_per_subfolder = (int *) calloc(NB_CLASSES, sizeof(int));

    for (int i = 0; i < NB_CLASSES; i++)
    {
        (*files_per_subfolder)[i] = count_files_in_folder(flower_folder_paths[i]);
        *nb_samples += (*files_per_subfolder)[i];
    }
}

void fill_file_paths(char ****folder_array, char *flower_folder_paths[])
{
    DIR *dir;
    struct dirent *ent;
    int file_index = 0;
    char file_path[256];

    for (int i = 0; i < NB_CLASSES; i++)
    {
        if ((dir = opendir(flower_folder_paths[i])) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                if (ent->d_type == DT_REG)
                {
                    strcpy(file_path, flower_folder_paths[i]);
                    strcat(file_path, ent->d_name);
                    strcpy((*folder_array)[i][file_index], file_path);
                    file_index++;
                }
                
            }
            closedir(dir);
        }
        file_index = 0;
    }
}

void fill_test_file_paths(char **test_file_paths, char *test_folder_path)
{
    DIR *dir;
    struct dirent *ent;
    int file_index = 0;
    char file_path[256];

    if ((dir = opendir(test_folder_path)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG)
            {
                strcpy(file_path, test_folder_path);
                strcat(file_path, ent->d_name);
                strcpy(test_file_paths[file_index], file_path);
                file_index++;
            }
            
        }
        closedir(dir);
    }
}

void resize_all_images(raw_image_t **image_array, int nb_samples, int **files_per_subfolder, raw_image_t **resized_image_array)
{
    *resized_image_array = (raw_image_t *) calloc(nb_samples, sizeof(raw_image_t));
    raw_image_t resized_image = {NB_CHANNELS, RESIZED_IMG_SIZE, RESIZED_IMG_SIZE, NULL, NULL};
    int index = 0;
    for (int i = 0; i < NB_CLASSES; i++)
    {
        for (int j = 0; j < (*files_per_subfolder)[i]; j++)
        {
            resized_image.image_data = (unsigned char *) calloc(RESIZED_IMG_SIZE * RESIZED_IMG_SIZE * NB_CHANNELS, sizeof(unsigned char));
            stbir_resize_uint8_linear((*image_array)[index].image_data, (*image_array)[index].width, (*image_array)[index].height, 0, resized_image.image_data, resized_image.width, resized_image.height, 0, STBIR_RGB);
            (*resized_image_array)[index] = resized_image;
            index++;
        }
    }
}

void map_image_to_class(char *class_labels[], int *files_per_subfolder, raw_image_t **train_images)
{
    int index = 0;
    for (int i = 0; i < NB_CLASSES; i++)
    {
        for (int j = 0; j < files_per_subfolder[i]; j++)
        {
            (*train_images)[index].class = (char *) calloc(MAX_STR_LENGTH, sizeof(char));
            strcpy((*train_images)[index].class, class_labels[i]);
            index++;
        }
    }
}

void save_jpeg_image_file(raw_image_t *image, char *file_path)
{
    struct jpeg_compress_struct info;
    struct jpeg_error_mgr err;

    unsigned char *row_buffer[1];

    FILE *fp = fopen(file_path, "wb");
    if (fp)
    {
        info.err = jpeg_std_error(&err);
        jpeg_create_compress(&info);
        jpeg_stdio_dest(&info, fp);
        
        info.image_width = image->width;
        info.image_height = image->height;
        info.input_components = NB_CHANNELS;
        info.in_color_space = JCS_RGB;

        jpeg_set_defaults(&info);
        jpeg_set_quality(&info, IMG_QUALITY, TRUE);
        jpeg_start_compress(&info, TRUE);

        while (info.next_scanline < info.image_height)
        {
            row_buffer[0] = &(image->image_data[info.next_scanline * (image->width * NB_CHANNELS)]);
            jpeg_write_scanlines(&info, row_buffer, 1);
        }

        jpeg_finish_compress(&info);
        fclose(fp);
        jpeg_destroy_compress(&info);
    }
    else
    {
        printf("Error opening file %s for writing\n", file_path);
    }
}