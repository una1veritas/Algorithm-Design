/*
 * mt19937ar.h
 *
 *  Created on: Apr 26, 2019
 *      Author: sin
 */

#ifndef MT19937AR_H_
#define MT19937AR_H_

void init_genrand(unsigned long s);
void init_by_array(unsigned long init_key[], int key_length);
unsigned long genrand_int32(void);
long genrand_int31(void);

#endif /* MT19937AR_H_ */
