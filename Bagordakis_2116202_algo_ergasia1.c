#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

//For test purposes (This numbers can be changed, it will result in different arrays)
//For this example Arrays of different sizes will have a different seed as well.
//The results in the excel are for the Seeds provided
#define DEFAULT_SEED_0 57422
#define DEFAULT_SEED_1 123381
#define DEFAULT_SEED_2 60312

//Array Sizes
#define ARRAY_SIZE_0 1000
#define ARRAY_SIZE_1 10000
#define ARRAY_SIZE_2 100000


int main(int argc, char *argv[]){
	//Sizes and seeds for all the arrays
	size_t array_size[3] = {ARRAY_SIZE_0, ARRAY_SIZE_1, ARRAY_SIZE_2};
	int array_seed[3] = {DEFAULT_SEED_0, DEFAULT_SEED_1, DEFAULT_SEED_2};
	
	int i;
	int* array;
	
	printf("Algorithmoi\t-Filippos Bagordakis.");
	for (i = 0; i < 3; i++){
		printf("\n------------------------------------\nResults for array length : %d", array_size[i]);
		//Set the seed to the correct seed for the array length
		set_seed(array_seed[i]);
		//Uncomment this to get a random array
		//generate_seed();
		printf("\nSeed : %d\n", get_seed());
		
		//Generate the array for Test number 1. Insertion Sort
		array = generate_array(array_size[i]);
		printf("\n\n-Insertion sort-");
		start_clock();
		insertion_sort(array, 0, array_size[i]);
		display_time(stop_clock());
		printf("\nTotal Swaps : %lld", get_total_swaps(1));
		verify_sorted(array, array_size[i]);
		free(array);
		
		//Generate Results for Test number 2. Quick sort
		array = generate_array(array_size[i]);
		printf("\n\n-Quick sort-");
		start_clock();
		quick_sort(array, 0, array_size[i]-1);
		display_time(stop_clock());
		printf("\nTotal Swaps : %lld", get_total_swaps(1));
		verify_sorted(array, array_size[i]);
		free(array);
		
		//Generate Results for Test number 3. Quick sort Random Pivot (case 1)
		array = generate_array(array_size[i]);
		printf("\n\n-Quick sort random pivot-");
		start_clock();
		quick_sort_random_pivot(array, 0, array_size[i]-1);
		display_time(stop_clock());
		printf("\nTotal Swaps : %lld", get_total_swaps(1));
		verify_sorted(array, array_size[i]);
		free(array);
		
		//Generate Results for Test number 4. Quick sort Median Pivot (case 2)
		array = generate_array(array_size[i]);
		printf("\n\n-Quick sort median pivot-");
		start_clock();
		quick_sort_median(array, 0, array_size[i]);
		display_time(stop_clock());
		printf("\nTotal Swaps : %lld", get_total_swaps(1));
		verify_sorted(array, array_size[i]);
		free(array);
		
		//Generate Results for Test number 5. Quick sort with Insertion short in the subproblems (case 3)
		array = generate_array(array_size[i]);
		printf("\n\n-Quick sort with insertion sort in chuncks-");
		start_clock();
		quick_insert_sort_sub(array, 0, array_size[i]-1);
		display_time(stop_clock());
		printf("\nTotal Swaps : %lld", get_total_swaps(1));
		verify_sorted(array, array_size[i]);
		free(array);
		
		//Generate Results for Test number 6. Quick sort with Insertion sort in the whole array (case 4)
		array = generate_array(array_size[i]);
		printf("\n\n-Quick sort with insertion sort in total-");
		start_clock();
		start_quick_sort_total_insertion(array, 0, array_size[i]-1);
		display_time(stop_clock());
		printf("\nTotal Swaps : %lld", get_total_swaps(1));
		verify_sorted(array, array_size[i]);
		free(array);
	}

	
	return 0;
}
