#include <stdio.h>
#include <time.h>

/*
typedef struct dictionary
{
        char *key;
        double value;
} Dictionary;

int key_to_value(Dictionary *dictionary, char *key)
{
        double value;

        for (int i = 0; i < sizeof(dictionary) / sizeof(dictionary[0]); i++)
        {
                if (dictionary[i].key == key)
                {
                        value = dictionary[i].value;
                }
                else
                        ;
        }

        return value;
}
*/

typedef struct inputs
{
        int key;
        int *data;
        double running_time[6];
} Inputs;

void swap(int *a, int *b)
{
        int temp = 0;
        temp = *a;
        *a = *b;
        *b = temp;
}

int sorted_inputs[1000];

void generate_input(int *, int);
void merge_result(Inputs *input_data, int left_point, int middle_point, int right_point);

void bubble_sort(Inputs *);
void insertion_sort(Inputs *);
void merge_sort(Inputs *input_data, int left_point, int right_point);
void quick_sort(int *input_data, int *running_time_of_sort);
void radix_sort(int *input_data, int *running_time_of_sort);
void bucket_sort(int *input_data, int *running_time_of_sort);

void print_table(Inputs *input_data);

int main(void)
{
        Inputs input_data[3];

        input_data[0].key = 10;
        input_data[0].data = malloc(sizeof(int) * input_data[0].key);
        generate_input(input_data[0].data, input_data[0].key);
        /*
        input_data[0].running_time[0].key = "Bubble Sort";
        input_data[0].running_time[1].key = "Insertion Sort";
        input_data[0].running_time[2].key = "Merge Sort";
        input_data[0].running_time[3].key = "Quick Sort";
        input_data[0].running_time[4].key = "Radix Sort";
        input_data[0].running_time[5].key = "Bucket Sort";
        */

        input_data[1].key = 100;
        input_data[1].data = malloc(sizeof(int) * input_data[1].key);
        generate_input(input_data[1].data, input_data[1].key);
        /*
        input_data[1].running_time[0].key = "Bubble Sort";
        input_data[1].running_time[1].key = "Insertion Sort";
        input_data[1].running_time[2].key = "Merge Sort";
        input_data[1].running_time[3].key = "Quick Sort";
        input_data[1].running_time[4].key = "Radix Sort";
        input_data[1].running_time[5].key = "Bucket Sort";
        */

        input_data[2].key = 1000;
        input_data[2].data = malloc(sizeof(int) * input_data[2].key);
        generate_input(input_data[2].data, input_data[2].key);
        /*
        input_data[2].running_time[0].key = "Bubble Sort";
        input_data[2].running_time[1].key = "Insertion Sort";
        input_data[2].running_time[2].key = "Merge Sort";
        input_data[2].running_time[3].key = "Quick Sort";
        input_data[2].running_time[4].key = "Radix Sort";
        input_data[2].running_time[5].key = "Bucket Sort";
        */

        bubble_sort(&input_data[0]);
        bubble_sort(&input_data[1]);
        bubble_sort(&input_data[2]);
        insertion_sort(&input_data[0]);
        insertion_sort(&input_data[1]);
        insertion_sort(&input_data[2]);
        merge_sort(&input_data[0], 0, input_data[0].key - 1);
        merge_sort(&input_data[1], 0, input_data[1].key - 1);
        merge_sort(&input_data[2], 0, input_data[2].key - 1);
        quick_sort(input_data[0].data, &input_data[0].running_time[3].value);
        quick_sort(input_data[1].data, &input_data[1].running_time[3].value);
        quick_sort(input_data[2].data, &input_data[2].running_time[3].value);
        radix_sort(input_data[0].data, &input_data[0].running_time[4].value);
        radix_sort(input_data[1].data, &input_data[1].running_time[4].value);
        radix_sort(input_data[2].data, &input_data[2].running_time[4].value);
        bucket_sort(input_data[0].data, &input_data[0].running_time[5].value);
        bucket_sort(input_data[1].data, &input_data[1].running_time[5].value);
        bucket_sort(input_data[2].data, &input_data[2].running_time[5].value);

        print_table(input_data);

        free(input_data[0].data);
        free(input_data[1].data);
        free(input_data[2].data);

        return 0;
}

void generate_input(int *input_data, int size_of_input)
{
        for (int i = 0; i < size_of_input; i++)
        {
                input_data[i] = size_of_input - i;
        }
}

void bubble_sort(Inputs *input_data)
{
        clock_t start;
        clock_t end;

        start = clock();

        for (int i = input_data->key - 1; i > 0; i--)
        {
                for (int j = 0; j < i; j++)
                {
                        if (input_data->data[j] > input_data->data[j + 1])
                                swap(&input_data->data[j], &input_data->data[j]);
                }
        }

        end = clock();
        input_data->running_time[0] = (double)(end - start);
}
void insertion_sort(Inputs *input_data)
{
        clock_t start;
        clock_t end;
        int key = 0;

        start = clock();

        for (int i = 1; i < input_data->key; i++)
        {
                key = input_data->data[i];
                int j = i - 1;
                for (; j > 0 && input_data->data[i] > key; j--)
                {
                        input_data->data[j + 1] = input_data->data[j];
                }
                input_data->data[j + 1] = key;
        }

        end = clock();
        input_data->running_time[0] = (double)(end - start);
}
void merge_result(Inputs *input_data, int left_point, int middle_point, int right_point)
{
        int i = left_point;
        int j = middle_point;
        int k = left_point;

        for (; i <= middle_point && j <= right_point;)
        {
                if (input_data->data[i] <= input_data->data[j])
                        sorted_inputs[k++] = input_data->data[i++];
                else
                        sorted_inputs[k++] = input_data->data[j++];
        }

        if (i < middle_point)
        {
                for (int l = j; l <= right_point; l++)
                        sorted_inputs[k++] = input_data->data[l];
        }
        else
        {
                for (int l = i; l <= middle_point; l++)
                        sorted_inputs[k++] = input_data->data[l];
        }

        for (int l = left_point; l <= right_point; l++)
                input_data->data[l] = sorted_inputs[l];
}
void merge_sort(Inputs *input_data, int left_point, int right_point)
{
        clock_t start;
        clock_t end;
        int middle_point = (left_point + right_point) / 2;

        start = clock();

        if (left_point < right_point)
        {
                merge_sort(&input_data, left_point, middle_point);
                merge_sort(&input_data, middle_point + 1, right_point);
                merge_result(&input_data, left_point, middle_point, right_point);
        }
        end = clock();
        input_data->running_time[0] = (double)(end - start);
}
void quick_sort(int *input_data, int *running_time_of_sort)
{
        clock_t start;
        clock_t end;

        start = clock();

        end = clock();
        input_data->running_time[0] = (double)(end - start);
}
void radix_sort(int *input_data, int *running_time_of_sort)
{
        clock_t start;
        clock_t end;

        start = clock();

        end = clock();
        input_data->running_time[0] = (double)(end - start);
}
void bucket_sort(int *input_data, int *running_time_of_sort)
{
        clock_t start;
        clock_t end;

        start = clock();

        end = clock();
        input_data->running_time[0] = (double)(end - start);
}

void print_table(Inputs *input_data){};
