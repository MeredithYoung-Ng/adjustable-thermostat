#ifndef _SEG_LIB_H_
#define _SEG_LIB_H_

#include "fsl_debug_console.h"
#include "board.h"


extern int * digit;
extern unsigned int segments[8];

void set_display(void);

void resetDigit(void);

void setZero(void);

void setOne(void);

void setTwo(void);

void setThree(void);

void setFour(void);

void setFive(void);

void setSix(void);

void setSeven(void);

void setEight(void);

void setNine(void);

#endif /* _SEG_LIB_H_ */

