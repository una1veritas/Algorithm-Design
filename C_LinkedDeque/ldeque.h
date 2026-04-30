/*
 * linkedlist.h
 *
 *  Created on: 2026/04/28
 *      Author: sin
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdbool.h>

typedef struct DequeNode {
	const char * datastr;
	struct DequeNode * prev, * next;
} DequeNode;

typedef struct LinkedDeque {
	DequeNode * head;
	DequeNode * tail;
	unsigned int elemcount;
} LinkedDeque;

bool LinkedDeque_append(LinkedDeque * ldequep, const char * datastr);
bool LinkedDeque_prepend(LinkedDeque * ldequep, const char * datastr);
bool LinkedDeque_remove_last(LinkedDeque * ldequep);
bool LinkedDeque_remove_front(LinkedDeque * ldequep);
bool LinkedDeque_remove_node(LinkedDeque * ldequep, DequeNode * nodep);
void LinkedDeque_free(LinkedDeque * ldequep);

#endif /* LINKEDLIST_H_ */
