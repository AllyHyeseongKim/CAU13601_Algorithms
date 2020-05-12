#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

int bucket_queue[10][1000];
int *front;
int *rear;
void put(int num_bucket, int input)
{
        bucket_queue[num_bucket][++rear[num_bucket]] = input;
}
int get(int num_bucket)
{
        return bucket_queue[num_bucket][front[num_bucket]++];
}

int trial = 0;

void generate_input(int *, int);
void merge(Inputs *, int, int, int);
void merge_sorting(Inputs *, int, int);
int partition(Inputs *, int, int);
void quick_sorting(Inputs *, int, int);
void put_bucket(int *, int);

void bubble_sort(Inputs *);
void insertion_sort(Inputs *);
void merge_sort(Inputs *, int, int);
void quick_sort(Inputs *, int, int);
void radix_sort(Inputs *);
void bucket_sort(Inputs *);

void print_table(Inputs *input_data);

int main(void)
{
        Inputs input_data[3];

        input_data[0].key = 10;
        input_data[0].data = malloc(sizeof(int) * input_data[0].key);
        generate_input(input_data[0].data, input_data[0].key);

        printf("-------------------------------------------------------------------------------------\n");
        printf("[INPUTS]      ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");
        printf("-------------------------------------------------------------------------------------\n");
        /*
        input_data[1].key = 100;
        input_data[1].data = malloc(sizeof(int) * input_data[1].key);
        generate_input(input_data[1].data, input_data[1].key);

        input_data[2].key = 1000;
        input_data[2].data = malloc(sizeof(int) * input_data[2].key);
        generate_input(input_data[2].data, input_data[2].key);
*/
        printf("-------------------------------------------------------------------------------------\n");
        printf("                                       BUBBLE SORT\n");
        printf("-------------------------------------------------------------------------------------\n");
        printf("[INPUTS]       ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");

        bubble_sort(&input_data[0]);
        printf("[OUTPUTS]      ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");
        //        bubble_sort(&input_data[1]);
        //        bubble_sort(&input_data[2]);

        generate_input(input_data[0].data, input_data[0].key);
        //generate_input(input_data[1].data, input_data[1].key);
        //generate_input(input_data[2].data, input_data[2].key);
        printf("-------------------------------------------------------------------------------------\n");
        printf("                                     INSERTION SORT\n");
        printf("-------------------------------------------------------------------------------------\n");
        printf("[INPUTS]       ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");

        insertion_sort(&input_data[0]);
        printf("[OUTPUTS]      ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");

        //        insertion_sort(&input_data[1]);
        //        insertion_sort(&input_data[2]);

        generate_input(input_data[0].data, input_data[0].key);
        //generate_input(input_data[1].data, input_data[1].key);
        //generate_input(input_data[2].data, input_data[2].key);
        printf("-------------------------------------------------------------------------------------\n");
        printf("                                       MERGE SORT\n");
        printf("-------------------------------------------------------------------------------------\n");
        printf("[INPUTS]       ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");

        merge_sort(&input_data[0], 0, input_data[0].key - 1);
        printf("[OUTPUTS]      ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");
        //        merge_sort(&input_data[1], 0, input_data[1].key - 1);
        //        merge_sort(&input_data[2], 0, input_data[2].key - 1);

        generate_input(input_data[0].data, input_data[0].key);
        //generate_input(input_data[1].data, input_data[1].key);
        //generate_input(input_data[2].data, input_data[2].key);
        printf("-------------------------------------------------------------------------------------\n");
        printf("                                       QUICK SORT\n");
        printf("-------------------------------------------------------------------------------------\n");
        printf("[INPUTS]       ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");

        quick_sort(&input_data[0], 0, input_data[0].key - 1);
        printf("[OUTPUTS]      ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");
        //        quick_sort(&input_data[1], 0, input_data[1].key - 1);
        //        quick_sort(&input_data[2], 0, input_data[2].key - 1);

        generate_input(input_data[0].data, input_data[0].key);
        //generate_input(input_data[1].data, input_data[1].key);
        //generate_input(input_data[2].data, input_data[2].key);
        printf("-------------------------------------------------------------------------------------\n");
        printf("                                       RADIX SORT\n");
        printf("-------------------------------------------------------------------------------------\n");
        printf("[INPUTS]       ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");
        radix_sort(&input_data[0]);
        printf("[OUTPUTS]      ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");
        //        radix_sort(&input_data[1]);
        //        radix_sort(&input_data[2]);

        generate_input(input_data[0].data, input_data[0].key);
        //generate_input(input_data[1].data, input_data[1].key);
        //generate_input(input_data[2].data, input_data[2].key);
        printf("-------------------------------------------------------------------------------------\n");
        printf("                                       BUCKET SORT\n");
        printf("-------------------------------------------------------------------------------------\n");
        printf("[INPUTS]       ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");
        bucket_sort(&input_data[0]);
        printf("[OUTPUTS]      ");
        for (int i = 0; i < input_data[0].key; i++)
                printf("%2d    ", input_data[0].data[i]);
        printf("\n");
        //        bucket_sort(&input_data[1]);
        //        bucket_sort(&input_data[2]);

        print_table(input_data);

        free(input_data[0].data);
        //        free(input_data[1].data);
        //        free(input_data[2].data);

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
        trial = 0;

        start = clock();

        for (int i = input_data->key - 1; i > 0; i--)
        {
                for (int j = 0; j < i; j++)
                {
                        if (input_data->data[j] > input_data->data[j + 1])
                        {
                                swap(&input_data->data[j], &input_data->data[j + 1]);
                                printf("[TRIAL%2d]      ", trial++);
                                for (int k = 0; k < input_data->key; k++)
                                        printf("%2d    ", input_data->data[k]);
                                printf("\n");
                        }
                }
        }

        end = clock();
        input_data->running_time[0] = (double)(end - start) / CLOCKS_PER_SEC;
}
void insertion_sort(Inputs *input_data)
{
        clock_t start;
        clock_t end;
        trial = 0;
        int key = 0;

        start = clock();

        for (int i = 1; i < input_data->key; i++)
        {
                key = input_data->data[i];
                for (int j = i - 1; j >= 0 && input_data->data[j] > key; j--)
                {
                        input_data->data[j + 1] = input_data->data[j];
                        input_data->data[j] = key;
                        printf("[TRIAL%2d]      ", trial++);
                        for (int k = 0; k < input_data->key; k++)
                                printf("%2d    ", input_data->data[k]);
                        printf("\n");
                }
        }

        end = clock();
        input_data->running_time[1] = (double)(end - start) / CLOCKS_PER_SEC;
}
void merge(Inputs *input_data, int left_point, int middle_point, int right_point)
{
        int left_sorted[middle_point - left_point + 1];
        int right_sorted[right_point - middle_point];

        for (int i = 0; i < middle_point - left_point + 1; i++)
                left_sorted[i] = input_data->data[left_point + i];
        for (int i = 0; i < right_point - middle_point; i++)
                right_sorted[i] = input_data->data[middle_point + 1 + i];

        int i = 0;
        int j = 0;
        int k = left_point;
        for (; i < middle_point - left_point + 1 && j < right_point - middle_point;)
        {
                if (left_sorted[i] <= right_sorted[j])
                        input_data->data[k++] = left_sorted[i++];
                else
                        input_data->data[k++] = right_sorted[j++];
        }

        for (; i < middle_point - left_point + 1;)
                input_data->data[k++] = left_sorted[i++];

        for (; j < right_point - middle_point;)
                input_data->data[k++] = right_sorted[j++];
        printf("[TRIAL%2d]      ", trial++);
        for (int l = 0; l < input_data->key; l++)
                printf("%2d    ", input_data->data[l]);
        printf("\n");
}
void merge_sorting(Inputs *input_data, int left_point, int right_point)
{
        if (left_point < right_point)
        {
                int middle_point = (left_point + right_point) / 2;

                merge_sorting(input_data, left_point, middle_point);
                merge_sorting(input_data, middle_point + 1, right_point);
                merge(input_data, left_point, middle_point, right_point);
        }
}
void merge_sort(Inputs *input_data, int left_point, int right_point)
{
        clock_t start;
        clock_t end;
        trial = 0;

        start = clock();

        merge_sorting(input_data, left_point, right_point);

        end = clock();
        input_data->running_time[2] = (double)(end - start) / CLOCKS_PER_SEC;
}
int partition(Inputs *input_data, int left_point, int right_point)
{
        int pivot = input_data->data[right_point];
        int i = left_point - 1;

        for (int j = left_point; j <= right_point - 1; j++)
        {
                if (input_data->data[j] < pivot)
                {
                        swap(&input_data->data[++i], &input_data->data[j]);
                        printf("[TRIAL%2d]      ", trial++);
                        for (int l = 0; l < input_data->key; l++)
                                printf("%2d    ", input_data->data[l]);
                        printf("\n");
                }
        }

        swap(&input_data->data[i + 1], &input_data->data[right_point]);
        printf("[TRIAL%2d]      ", trial++);
        for (int l = 0; l < input_data->key; l++)
                printf("%2d    ", input_data->data[l]);
        printf("\n");

        return i + 1;
}
void quick_sorting(Inputs *input_data, int left_point, int right_point)
{
        if (left_point < right_point)
        {
                int part = partition(input_data, left_point, right_point);

                quick_sorting(input_data, left_point, part - 1);
                quick_sorting(input_data, part + 1, right_point);
        }
}
void quick_sort(Inputs *input_data, int left_point, int right_point)
{
        clock_t start;
        clock_t end;
        trial = 0;

        start = clock();

        quick_sorting(input_data, left_point, right_point);

        end = clock();
        input_data->running_time[3] = (double)(end - start) / CLOCKS_PER_SEC;
}
void radix_sort(Inputs *input_data)
{
        clock_t start;
        clock_t end;
        trial = 0;
        int count[10];
        int bucket_num;
        int bucket[10][input_data->key];
        for (int i = 0; i < 10; i++)
        {
                for (int j = 0; j < input_data->key; j++)
                        bucket[i][j] = 0;
        }

        int max_digit = 0;
        for (int i = input_data->data[0]; i > 0; i /= 10)
        {
                max_digit++;
        }

        start = clock();

        for (int digit = 1; digit <= pow(10, max_digit - 1); digit *= 10)
        {
                for (int i = 0; i < 10; i++)
                        count[i] = 0;
                for (int i = 0; i < input_data->key; i++)
                {
                        bucket_num = (input_data->data[i] / digit) % 10;
                        bucket[bucket_num][count[bucket_num]++] = input_data->data[i];
                }
                int k = 0;
                for (int i = 0; i < 10; i++)
                {
                        for (int j = 0; j < count[i]; j++)
                                input_data->data[k++] = bucket[i][j];
                }
                printf("[TRIAL%2d]      ", trial++);
                for (int l = 0; l < input_data->key; l++)
                        printf("%2d    ", input_data->data[l]);
                printf("\n");
        }

        end = clock();
        input_data->running_time[4] = (double)(end - start) / CLOCKS_PER_SEC;
}
void put_bucket(int *bucket, int data)
{
        int point = 0;
        int j = 0;

        for (j = 0; bucket[j] > 0; j++)
        {
                if (bucket[j] < data)
                        point = j + 1;
        }
        int top = j + 1;

        for (int i = top; i > point; i--)
        {
                bucket[i] = bucket[i - 1];
        }
        bucket[point] = data;
}
void bucket_sort(Inputs *input_data)
{
        clock_t start;
        clock_t end;
        int num;
        int num_buckets;
        int size_buckets;
        int **bucket;
        int bucket_num;

        switch (input_data->key / 10)
        {
        case 1:
                num = 2;
                num_buckets = 5;
                size_buckets = input_data->key / num_buckets;
                bucket = (int **)malloc(sizeof(int *) * num_buckets);
                for (int i = 0; i < num_buckets; i++)
                        bucket[i] = (int *)malloc(sizeof(int) * size_buckets);
                break;
        case 2:
                num = 10;
                num_buckets = 10;
                size_buckets = input_data->key / num_buckets;
                bucket = (int **)malloc(sizeof(int *) * num_buckets);
                for (int i = 0; i < num_buckets; i++)
                        bucket[i] = (int *)malloc(sizeof(int) * size_buckets);
                break;
        case 3:
                num = 20;
                num_buckets = 20;
                size_buckets = input_data->key / num_buckets;
                bucket = (int **)malloc(sizeof(int *) * num_buckets);
                for (int i = 0; i < num_buckets; i++)
                        bucket[i] = (int *)malloc(sizeof(int) * size_buckets);
                break;
        }

        start = clock();

        for (int i = 0; i < input_data->key; i++)
        {
                if (input_data->data[i] % num == 0)
                        bucket_num = input_data->data[i] / num - 1;
                else
                        bucket_num = input_data->data[i] / num;
                put_bucket(bucket[bucket_num], *input_data->data);
        }
        int k = 0;
        for (int i = 0; i < num_buckets; i++)
        {
                for (int j = 0; j < size_buckets; j++)
                        input_data->data[k++] = bucket[i][j];
        }
        printf("[TRIAL%2d]      ", trial++);
        for (int l = 0; l < input_data->key; l++)
                printf("%2d    ", input_data->data[l]);
        printf("\n");

        end = clock();
        input_data->running_time[5] = (double)(end - start) / CLOCKS_PER_SEC;

        for (int i = 0; i < num_buckets; i++)
                free(bucket[i]);
        free(bucket);
}

void print_table(Inputs *input_data)
{
        printf("-------------------------------------------------------------------------------------\n");
        printf("                                Result table\n");
        printf("-------------------------------------------------------------------------------------\n");
        printf("                   BUBBLE   INSERTION       MERGE       QUICK       RADIX      BUCKET\n");
        printf("[10   inputs]    %lf    %lf    %lf    %lf    %lf    %lf\n", input_data[0].running_time[0], input_data[0].running_time[1], input_data[0].running_time[2], input_data[0].running_time[3], input_data[0].running_time[4], input_data[0].running_time[5]);
        //        printf("[100  inputs]    %lf    %lf    %lf    %lf    %lf    %lf\n", input_data[1].running_time[0], input_data[1].running_time[1], input_data[1].running_time[2], input_data[1].running_time[3], input_data[1].running_time[4], input_data[1].running_time[5]);
        //        printf("[1000 inputs]    %lf    %lf    %lf    %lf    %lf    %lf\n", input_data[2].running_time[0], input_data[2].running_time[1], input_data[2].running_time[2], input_data[2].running_time[3], input_data[2].running_time[4], input_data[2].running_time[5]);
        printf("-------------------------------------------------------------------------------------\n");
}
