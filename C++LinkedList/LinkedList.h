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
	ListNode(const void* d, ListNode * nodeptr = NULL) {
		data = d;
		next = nodeptr;
	}
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
		const void * operator*() { return data(); }
		const ListNode * nodeptr() { return preptr->next; }
		const void * data() const;
		Iterator & operator++();
		Iterator & operator+=(int offset);
		const bool operator==(const Iterator & itr) const;
		const bool operator!=(const Iterator & itr) const;
	};

public:
	LinkedList();
	~LinkedList();
	unsigned int size() const { return elemcount; }

	ListNode * append(const void* dataptr);
	ListNode * push(const void* dataptr);
	const void * pop();

	Iterator begin() { return Iterator(&head); }
	Iterator end() { return Iterator(tailptr); }

	ListNode * make_tail_loop(unsigned int ith);

	friend std::ostream & operator<<(std::ostream & out, LinkedList & list) {
		ListNode * ptr = &list.head;
		while ( ptr != NULL ) {
			out << reinterpret_cast<unsigned long long>( ptr->data) << ' ';
			if ( ptr == list.tailptr )
				break;
			ptr = ptr->next;
		}
		return out;
	}

};

#endif /* LINKEDLIST_H_ */
