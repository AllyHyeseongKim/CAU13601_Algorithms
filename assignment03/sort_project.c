#include <stdio.h>


typedef struct dictionary{
	char *key;
	int value;
}Dictionary;

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


int *generate_input(int size_of_inputs);

int *bubble_sort(int *input_data, int *running_time_of_sort);
int *insertion_sort(int *input_data, int *running_time_of_sort);
int *merge_sort(int *input_data, int *running_time_of_sort);
int *quick_sort(int *input_data, int *running_time_of_sort);
int *radix_sort(int *input_data, int *running_time_of_sort);
int *bucket_sort(int *input_data, int *running_time_of_sort);

void generate_table(int *running_time_of_sorts);
void print_table(int *running_time_of_sorts);


int main(void){
	
	return 0;
}
