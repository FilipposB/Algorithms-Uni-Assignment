#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

//Most functions have been described in the functions.h file

//Random seed that is used to produce similar random arrays, if this is less than 0 it means a seed hasn't been generated
int seed = -1;
//This checks if rand_time has been set
int time_initialised = 0;
//This holds the rand time to make sure the generate_seed() works as intended
int rand_time;

//Threshold is used to stop the quicksort algorithm when a subproblem reaches 10
int threshold = 0;

//Used instead of clock, Seems to be more accurate
struct timeval  start, stop;

//This "boolean" checks to see if the clock has started counting
int clock_started = 0;

//Swap counter
long long total_swaps = 0;

void generate_seed(){
	//This part makes sure every time this is called the results are different
	if (time_initialised == 0){
		rand_time = time(NULL);
		time_initialised = 1;
	}
	else{
		rand_time += rand()%100 + 1;
	}
	srand(rand_time);
	seed = rand();
}

int* generate_array(int size){
	//If a seed hasn't been generated, generate a random one
	if (seed < 0){
		generate_seed();
	}
	
	//Reset random to the seed
	srand(seed);
	
	int i;
	int* array;
	array = (int*)malloc(size * sizeof(int));
	
	for (i = 0; i < size; i++){
		array[i] = rand();
	}
	
	return array;
}

void print_array(int* array, size_t size){
	int i;
	for(i = 0; i < size; i++){
		printf("%d: %d\n", i, array[i]);
	}
}

int get_seed(){
	return seed;
}

void set_seed(int new_seed){
	seed = new_seed;
}

void insertion_sort(int* array,int start, int finish){
	int i, j;
	int temp;
	
	for(i=start + 1; i<finish;i++){
		
	temp=array[i];
	j=i-1;
	while((temp<array[j])&&(j>=start)){
		array[j+1]=array[j];
		
		//Comment this part out if testing for time
		total_swaps++;
		
		j=j-1;
	}
	array[j+1]=temp;
	//Comment this part out if testing for time
	total_swaps++;
   }
}

void start_clock(){
	gettimeofday(&start, NULL);
	clock_started = 1;
}

double stop_clock(){
	//Clock stops here so the results will be more accurate
	gettimeofday(&stop, NULL);

	if (clock_started == 0){
		printf("\n-Clock hasn't started !-\n");
		return 0;
	}
	
	//Clock stoped
	clock_started = 0;
	return(double) (stop.tv_usec - start.tv_usec) / 1000000 + (double) (stop.tv_sec - start.tv_sec);
}

//Swaps two elemets
void swap(int* element_0, int* element_1) 
{ 
    int temp = *element_0; 
    *element_0 = *element_1; 
    *element_1 = temp;
    //Comment this part out if testing for time
    total_swaps+=2;
} 

int partition(int* array, int low, int high) 
{ 
    int pivot = array[high]; 
    int i = (low - 1);
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (array[j] < pivot) 
        { 
            i++; 
            swap(&array[i], &array[j]); 
        } 
    } 
    swap(&array[i + 1], &array[high]); 
    return (i + 1); 
} 

void quick_sort(int* array, int low, int high) 
{ 
    if (low < high) 
    { 
        int partition_index = partition(array, low, high); 
        quick_sort(array, low, partition_index - 1); 
        quick_sort(array, partition_index + 1, high); 
    } 
}

int random_partition(int* array, int low, int high) 
{ 
    //Random pivot between low and high
    srand(time(NULL)); 
    int random = low + rand() % (high - low); 
  
    // Swap A[random] with A[high] 
    swap(&array[random], &array[low]); 
  
    return partition(array, low, high); 
}

void quick_sort_random_pivot(int* array, int low, int high) 
{ 
    if (low < high) 
    { 
        int partition_index = random_partition(array, low, high); 
        quick_sort(array, low, partition_index - 1); 
        quick_sort(array, partition_index + 1, high); 
    } 
}

int median_partition(int* array,int low, int high) {
    int left=array[low];
	int middle=array[(high-low)/2+low];
	int right=array[high-1];
	int i=low-1;
	int j=high;
	
    if ((middle>left && middle<right) || (middle>right && middle<left)){
    	left=middle;
	}
    else if ((right>left && right<middle) || (right>middle && right<left)){
    	left=right;
	}
    while (1) {
        do {
			j--;
		}while (array[j] > left);
		
        do {
			i++;
		}while (array[i] < left);
		
        if  (i < j){
        	swap(&array[i],&array[j]);
		}
        else return j+1;
    }
}

void quick_sort_median(int* array,int low, int high) {
    if (high-low<2) return;
    int partition_index=median_partition(array,low,high);
    quick_sort_median(array,low,partition_index);
    quick_sort_median(array,partition_index,high);
}

void quick_insert_sort_sub(int* array, int low, int high) 
{
	if (low < high){
		if (high - low < 10){
			insertion_sort(array, low, high+1);
		}
		else{ 
	        int partition_index = partition(array, low, high);
            quick_insert_sort_sub(array, low, partition_index - 1);
            quick_insert_sort_sub(array, partition_index + 1, high);
    	} 
	}
    
}

void quick_sort_total_insertion(int* array, int low, int high) 
{ 
    if (low < high && threshold == 0) 
    { 
    	if (high - low < 10){
    		threshold = 1;
		}
		else{
			int partition_index = partition(array, low, high); 
	        quick_sort(array, low, partition_index - 1);
	        if (threshold == 0)
	        	quick_sort(array, partition_index + 1, high); 	
		}
    } 
}

void start_quick_sort_total_insertion(int* array, int low, int high){
	//Reset the threshold
	//When this turns to 1 all the other quicksorts will be canceled
	threshold = 0;
	quick_sort_total_insertion(array, low, high);
	insertion_sort(array, low, high);
}

void display_time(double time){
	printf("\nTime elapsed : ");
	if (time == 0){
			printf("less than 0.000000 seconds");
	}
	else{
		printf("%lf seconds", time);
	}
}

long long get_total_swaps(int clear){
	long long temp = total_swaps;
	if (clear)
		total_swaps = 0;
	//Because Insertion sort doesn't use swap, each swap coutns as 2 in total swap
	//Dividing it with 2 should give a good estimate of the amount of swaps required
	return temp / 2 + temp % 2;
}

void verify_sorted(int* array, size_t length){
	int i;

	for (i = 1; i < length; i++){
		if (array[i] < array[i-1]){
			printf("\nArray wasn't sorted succesfuly :(");
			return;
		}
	}
	printf("\nArray was succesfuly sorted !");
}



  


