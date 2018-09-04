#ifndef _CONVERTER_H_
#define _CONVERTER_H_

/* returns: [raw_to_temp] is [raw] converted to Fahrenheit
 * requires: [raw] is the unconverted ADC value */
int raw_to_temp(int raw);

/* returns: [removeMinMax] is a pointer to an array with the min and max removed
 * requires: 
 * 		- [list] is an array
 * 		- [size] is the size of [list], and is greater or equal to 3 */
int removeMinMax(int *list, int size);

#endif /* _CONVERTER_H_ */
