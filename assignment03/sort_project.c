#include <stdio.h>

int *generate_input(int size_of_inputs);

int *bubble_sort(int *input_data, int *running_time_of_sort);
int *insertion_sort(int *input_data, int *running_time_of_sort);
int *merge_sort(int *input_data, int *running_time_of_sort);
int *quick_sort(int *input_data, int *running_time_of_sort);
int *radix_sort(int *input_data, int *running_time_of_sort);
int *bucket_sort(int *input_data, int *running_time_of_sort);

void generate_table(int *running_time_of_sorts);
