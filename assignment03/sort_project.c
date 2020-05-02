#include <stdio.h>


typedef struct dictionary{
	char *key;
	int value;
} Dictionary;

int key_to_value(Dictionary *dictionary, char *key){
	int value;

	for(int i = 0; i < sizeof(dictionary) / sizeof(dictionary[0]); i++){
		if(dictionary[i].key == key){
			value = dictionary[i].value;
		}
		else;
	}

	return value;
}

void generate_input(int *input_data, int size_of_input);

void bubble_sort(int *input_data, int *running_time_of_sort);
void insertion_sort(int *input_data, int *running_time_of_sort);
void merge_sort(int *input_data, int *running_time_of_sort);
void quick_sort(int *input_data, int *running_time_of_sort);
void radix_sort(int *input_data, int *running_time_of_sort);
void bucket_sort(int *input_data, int *running_time_of_sort);

void print_table(Dictionary *running_time_of_sorts);


int main(void){
	Dictionary running_time_of_sorts[6];
	running_time_of_sorts[0].key = "Bubble Sort";
	running_time_of_sorts[1].key = "Insertion Sort";
        running_time_of_sorts[2].key = "Merge Sort";
        running_time_of_sorts[3].key = "Quick Sort";
        running_time_of_sorts[4].key = "Radix Sort";
        running_time_of_sorts[5].key = "Bucket Sort";

	int input_10[10];
	generate_input(input_10, 10);
	int input_100[100];
	generate_input(input_100, 100);
	int input_1000[1000];
	generate_input(input_1000, 1000);

	return 0;
}


void generate_input(int *input_data, int size_of_input){
	for(int i = 0; i < size_of_input; i++){
		input_data[i] = size_of_input - i;
	}
}


void bubble_sort(int *input_data, int *running_time_of_sort){
}
void insertion_sort(int *input_data, int *running_time_of_sort){
}
void merge_sort(int *input_data, int *running_time_of_sort){
}
void quick_sort(int *input_data, int *running_time_of_sort){
}
void radix_sort(int *input_data, int *running_time_of_sort){
}
void bucket_sort(int *input_data, int *running_time_of_sort){
}

void print_table(Dictionary *running_time_of_sorts){
};
