#include "converter.h"
#include "init.h"

/* returns: [raw_to_temp] is [raw] converted to Fahrenheit
 * requires: [raw] is the unconverted ADC value */
int raw_to_temp(int raw) {
	if (raw <= 16400) {
		return ((0.0053527 * raw) - 4.88423);
	} else {
		return ((0.00465517 * raw) + 6.55517);
	}
	
}

/* returns: [removeMinMax] is a pointer to an array with the min and max removed
 * requires: 
 * 		- [list] is an array
 * 		- [size] is the size of [list], and is greater or equal to 3 */
int removeMinMax(int * list, int size) {
	// Find index of minimum and maximum in [list]
	int min = list[0];
	int max = list[0];
	int minIdx = 0;
	int maxIdx = 0;

	for(int i = 1; i < size; i++) {
		if (list[i] < min) {
			min = list[i];
			minIdx = i;
		}
		if (list[i] > max) {
			max = list[i];
			maxIdx = i;
		}
	}
	
	// Find average of list array, excluding min and max
	int sum = 0;
	for (int j = 0; j < size; j++) {
		if (j != minIdx && j != maxIdx) {
			sum += list[j];
		}
	}
	
	// Return average
	return sum/(size-2);

}
