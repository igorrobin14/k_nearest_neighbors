/**
 * @file results.c
 * @author Igor Robin (Igor.ROBIN@etu.isima.fr)
 * @brief Definition of functions managing results
 * @version 0.1
 * @date 2024-04-14
 */

#include "results.h"

double compute_accuracy(result_t *r, int nb_test_samples, char ***predictions, raw_image_t **samples_test, bool **is_right_class, int *nb_trues, int *nb_falses)
{
    for (int i = 0; i < nb_test_samples; i++)
    {
        strcmp((*predictions)[i], (*samples_test)[i].class) == 0 ? ((*is_right_class)[i] = true) : ((*is_right_class)[i] = false);
        (*is_right_class)[i] == true ? ((*nb_trues)++) : ((*nb_falses)++);
    }
    r->accuracy = (double) (*nb_trues) / (double) nb_test_samples;
}

void compute_true_positives(char ***predictions, raw_image_t **samples_test, char *class_labels[], int nb_test_samples, double **true_positives)
{
    for (int i = 0; i < NB_CLASSES; i++)
    {
        for (int j = 0; j < nb_test_samples; j++)
        {
            if ((strcmp((*predictions)[j], class_labels[i]) == 0) && (strcmp((*samples_test)[j].class, class_labels[i]) == 0))
            {
                (*true_positives)[i] += 1.0;
            }
        }
    }
}

void compute_false_positives(char ***predictions, raw_image_t **samples_test, char *class_labels[], int nb_test_samples, double **false_positives) // Here
{
    for (int i = 0; i < NB_CLASSES; i++)
    {
        for (int j = 0; j < nb_test_samples; j++)
        {
            if ((strcmp((*predictions)[j], class_labels[i]) == 0) && (strcmp((*samples_test)[j].class, class_labels[i]) != 0))
            {
                (*false_positives)[i] += 1.0;
            }
        }
    }
}

void compute_false_negatives(char ***predictions, raw_image_t **samples_test, char *class_labels[], int nb_test_samples, double **false_negatives)
{
    for (int i = 0; i < NB_CLASSES; i++)
    {
        for (int j = 0; j < nb_test_samples; j++)
        {
            if ((strcmp((*predictions)[j], class_labels[i]) != 0) && (strcmp((*samples_test)[j].class, class_labels[i]) == 0))
            {
                (*false_negatives)[i] += 1.0;
            }
        }
    }
}

void compute_supports(result_t *r, char *class_labels[], raw_image_t **samples_test, int nb_test_samples)
{
    for (int i = 0; i < NB_CLASSES; i++)
    {
        for (int j = 0; j < nb_test_samples; j++)
        {
            if (strcmp((*samples_test)[j].class, class_labels[i]) == 0)
            {
                (r->supports)[i] += 1.0;
            } 
        }
    }
}

void compute_results(result_t *r, double **true_positives, double **false_positives, double **false_negatives, char *class_labels[], raw_image_t **samples_test, int nb_test_samples)
{
    double precision_mavg = 0;
    double recall_mavg = 0;
    double precision_wavg = 0;
    double recall_wavg = 0;

    compute_supports(r, class_labels, samples_test, nb_test_samples);
    for (int i = 0; i < NB_CLASSES; i++)
    {
        (r->precisions)[i] = (*true_positives)[i] / ((*true_positives)[i] + (*false_positives)[i]);
        (r->recalls)[i] = (*true_positives)[i] / ((*true_positives)[i] + (*false_negatives)[i]);
        (r->f1_scores)[i] = 2 * (r->precisions)[i] * (r->recalls)[i] / ((r->precisions)[i] + (r->recalls)[i]);
        r->precision_mavg += (r->precisions)[i];
        r->recall_mavg += (r->recalls)[i];
        r->precision_wavg += ((r->precisions)[i] * (r->supports)[i]);
        r->recall_wavg += ((r->recalls)[i] * (r->supports)[i]);
        r->f1_score_mavg += (r->f1_scores[i]);
        r->f1_score_wavg += ((r->f1_scores)[i] * (r->supports)[i]);
    }

    r->recall_mavg /= NB_CLASSES;
    r->recall_wavg /= nb_test_samples;
    r->precision_mavg /= NB_CLASSES;
    r->precision_wavg /= nb_test_samples;
    r->f1_score_mavg /= NB_CLASSES;
    r->f1_score_wavg /= nb_test_samples;
}

void display_results(result_t *r, char *class_labels[])
{
    printf("\n");
    printf("\033[1mClass label     Precision       Recall          F1-Score        Support\033[0m\n");

    for (int i = 0; i < NB_CLASSES; i++)
    {
        printf("%-15s %-15lf %-15lf %-15lf %-15d\n", class_labels[i], (r->precisions)[i], (r->recalls)[i], (r->f1_scores)[i], (int) (r->supports)[i]);
    }

    printf("\n");
    printf("Macro average:\n                %lf        %lf        %lf\n", r->precision_mavg, r->recall_mavg, r->f1_score_mavg);
    printf("Weighted average:\n                %lf        %lf        %lf\n", r->precision_wavg, r->recall_wavg, r->f1_score_wavg);
    printf("\n");
    printf("\033[1mAccuracy: %lf\033[0m\n", r->accuracy);
}