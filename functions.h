#ifndef functions
#define functions

//This function makes a random seed
void generate_seed();

//Geter setter for seed
int get_seed();
void set_seed(int);

//This function takes the size of an array and produces an array with random numbers
int* generate_array(int);

//Takes an array with its size and prints all of it's elements , indexed
void print_array(int*, size_t);

//Insertion sort algorithm
void insertion_sort(int*, int, int);

//Quick sort algorithm
void quick_sort(int*, int, int);

//Display Time
void display_time(double);

//Quick sort with random pivot
void quick_sort_random_pivot(int*, int, int);

//This function returns the total swaps, if 0 is passed as a parameter it will not clear
//The swap counter if 1 is passed it will clear it.
long long get_total_swaps(int);

//This function uses quick sort to order the array until a threshold of 10 in the subproblem is reached and then uses insertion sort for those sub problems
void quick_insert_sort_sub(int*, int, int) ;

//This function is the same as quick_insert_sort_sub but when one of the subproblems reaches 10 the quicksort in all the subproblems stops and insertion sort
//Is is used in the whole array
void start_quick_sort_total_insertion(int*, int, int);

void quick_sort_median(int*,int, int);

//Only verifies accending order arrays
void verify_sorted(int*, size_t);

//Starts and stops the clock, When the clock stops the time elapsed is returned
void start_clock();
double stop_clock();

#endif
