/*
 * llist.c
 *
 *  Created on: 2026/04/28
 *      Author: sin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ldeque.h"

unsigned int LinkedDeque_size(LinkedDeque * ldequep) {
	return ldequep->elemcount;
}

bool LinkedDeque_append(LinkedDeque * ldequep, const data * datap) {
	DequeNode * nodep = (DequeNode *) malloc(sizeof(DequeNode));
	if ( nodep == NULL )
		return false;
	if ( ldequep->tail == NULL ) {
		// リストがカラ
		ldequep->head = nodep;
		ldequep->tail = nodep;
		nodep->prev = NULL;
		nodep->next = NULL;
	} else {
		nodep->prev = ldequep->tail;
		nodep->next = NULL;
		nodep->prev->next = nodep;
		ldequep->tail = nodep;
	}
	memcpy(&nodep->node_data, datap, sizeof(data));

	ldequep->elemcount += 1;
	return true;
}

bool LinkedDeque_prepend(LinkedDeque * ldequep, const data * datap) {
	DequeNode * nodep = (DequeNode *) malloc(sizeof(DequeNode));
	if ( nodep == NULL ) {
		// malloc エラー
		return false;
	}
	if ( ldequep->tail == NULL ) {
		// リストがカラ
		ldequep->head = nodep;
		ldequep->tail = nodep;
		nodep->prev = NULL;
		nodep->next = NULL;
	} else {
		// 先頭に追加
		nodep->next = ldequep->head;
		nodep->prev = NULL;
		nodep->next->prev = nodep;
		ldequep->head = nodep;
	}
	//printf("datap %s* %s, \n", datap->id, datap->name);
	memcpy(&nodep->node_data, datap, sizeof(data));
	//printf("node_data %s* %s, \n", nodep->node_data.id, nodep->node_data.name);

	ldequep->elemcount += 1;
	return true;
}

bool LinkedDeque_remove_back(LinkedDeque * ldequep) {
	DequeNode * nodep = ldequep->tail;
	if ( nodep == NULL ) {
		// no nodes
		return false;
	}
	if ( nodep->prev == NULL ) {
		free(nodep);
		ldequep->head = NULL;
		ldequep->tail = NULL;
		ldequep->elemcount = 0;
	} else {
		ldequep->tail = nodep->prev;
		ldequep->tail->next = NULL;
		free(nodep);
		nodep->next = NULL;
		ldequep->elemcount -= 1;
	}
	return true;
}

bool LinkedDeque_remove_front(LinkedDeque * ldequep) {
	DequeNode * nodep = ldequep->head;
	if ( nodep == NULL ) {
		// no nodes
		return false;
	}
	if ( nodep->next == NULL ) {
		// nodep points the last node
		free(nodep);
		ldequep->head = NULL;
		ldequep->tail = NULL;
		ldequep->elemcount = 0;
	} else {
		ldequep->head = nodep->next;
		ldequep->head->prev = NULL;
		free(nodep);
		ldequep->elemcount -= 1;
	}
	return true;
}

bool LinkedDeque_remove_node(LinkedDeque * ldequep, DequeNode * nodep) {
	if ( nodep == NULL ) {
		// do nothing
		return false;
	}
	if ( nodep->next == NULL ) {
		// nodep points the last node
		LinkedDeque_remove_back(ldequep);
	} else if ( nodep->prev == NULL) {
		// nodep points the first node
		LinkedDeque_remove_front(ldequep);
	} else {
		// nodep points a node in the middle
		nodep->prev->next = nodep->next;
		nodep->next->prev = nodep->prev;
		free(nodep);
		ldequep->elemcount -= 1;
	}
	return true;
}

void LinkedDeque_free(LinkedDeque * ldequep) {
	while ( LinkedDeque_remove_back(ldequep) ) {}
}
