#include <iostream>
#include <stdio.h>

using namespace std;

int getCycleLength(int n, int *cache);

// The 3n+1 problem:
// Will be fed series of number in pairs i, j. The goal is to find the maximum
// cycle length in the range [i, j] where cycle length is the number of
// times that the algorithm below runs, including when it is equal to 1:
// if (n == 1)
// 		stop execution (termination condition)
// else if(n is odd)
// 		n = 3n+1
// else
//		n = n/2
//
int main(){

	int cache[10000] = {0};		// A cache to store results found during execution, to speed up further requests
								// Entry i contains the cycle length for i when input into the problem
								// Important note: only useful information if index is non-zero value (will always at least be 1)
	
	int i, j;					// The two input numbers
	bool swapped = false;		// A boolean to keep track of whether i and j got swapped
	int current;				// The current number being checked
	int maxCycleLength = 0;		// The maximum cycle length (so far) of the numbers between i and j
	int cycleLength;			// The cycle length of the latest value run between i and j
	
	// Read in an i, j pair while i, j pairs available
	while(scanf("%d %d", &i, &j) != EOF){
		swapped = false;		// Initialize swapped to false
		// No guarantee that i will be less than j (though it should be)
		if(i > j) {
			swap(i, j);			// If i > j, swap them
			swapped = true;		// Set swapped to true
		}
		
		current = i;			// Start from i, the lower value
		maxCycleLength = 0;		// Reset initial maxCycleLength
		
		/// For values in range [i, j]
		for(current; current<=j; current++){
			cycleLength = getCycleLength(current, cache);		// Get the cycle length of the current test value
			// If the new value greater than max found so far
			if(cycleLength > maxCycleLength){
				maxCycleLength = cycleLength;					// Set maxCycleLength to the new value
			}
		}
		
		// If i and j weren't swapped (they were initially in increasing order)
		if(!swapped){
			cout << i << " " << j << " " 
				<< maxCycleLength << endl;						// Output the results
		}
		else{
			cout << j << " " << i << " " 
				<< maxCycleLength << endl;						// Output the results
		}
	}
}

// A function to compute the cycle length from running the algorithm
// on a given value n, using information from the cached values in cache
int getCycleLength(int n, int *cache){
	int cycleLength = 1;
	int initialN = n;
	
	// While not at termination condition (n == 1)
	while(n != 1){
		// If the value is already cached (protect against index out of bounds)
		if(n < 10000 && cache[n] != 0){
			return cache[n] + cycleLength - 1;	// Return the value cached + number of cycles already completed
		}
		// If the value is odd and not cached
		else if( n % 2 > 0){
			n = 3*n+1;							// Perform n = 3n+1 operation
		}
		// Otherwise (value is even)
		else{
			n = n/2;							// Perform n = n/2 operation
		}
		cycleLength++;							// Increment cycleLength
	}
	cache[initialN] = cycleLength;				// Cache the cycleLength value, at index of initial n
	return cycleLength;							// Return the final value
}
