/*
 * LinkedList.h
 *
 *  Created on: 2019/05/23
 *      Author: sin
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include <cstddef>

#ifndef NULL
#define nullptr NULL
#endif

struct ListNode {
public:
	const void* data;
	ListNode * next;

public:
	ListNode(const void* d, ListNode * nodeptr = NULL) : data(d), next(nodeptr) { }
};


struct LinkedList {
public:
	ListNode head;
	ListNode * tailptr;
	unsigned int elemcount;

public:

	struct Iterator {
		ListNode * preptr;

		Iterator(ListNode * ptr) { preptr = ptr; }
		const ListNode & operator*() { return *(preptr->next); }
		Iterator & operator++();
		Iterator & operator+=(int offset);
		const bool operator==(const Iterator & itr) const {
			return preptr->next == itr.preptr->next;
		}
		const bool operator!=(const Iterator & itr) const {
			return preptr->next != itr.preptr->next;
		}
	};

public:
	LinkedList() : head(0, NULL), tailptr(&head), elemcount(0) { }
	~LinkedList();
	unsigned int size() const { return elemcount; }

	ListNode * append(const void* dataptr);
	ListNode * push(const void* dataptr);
	const void * pop();
	std::ostream & printOn(std::ostream & out) const;

	ListNode * begin() { return &head; }
	ListNode * end() { return tailptr; }

	ListNode * make_tail_loop(unsigned int ith);

	friend std::ostream & operator<<(std::ostream & out, LinkedList & list) {
		return list.printOn(out);
	}

};

#endif /* LINKEDLIST_H_ */
