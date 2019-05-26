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
	ListNode * head;
	ListNode * tail;
	unsigned int elemcount;

public:
	struct Iterator {
		ListNode * ptr;

		Iterator(ListNode * p) { ptr = p; }
		const void * operator*() { return data(); }
		const ListNode * nodeptr() { return ptr->next; }
		const void * data() {
			if ( ptr->next == NULL) {
				std::cerr << "LinkedList::Iterator::data() accessed NULL ptr." << std::endl;
			}
			return ptr->next->data;
		}
		Iterator & operator++() { ptr = ptr->next; return *this; }
		Iterator & operator+=(int offset) {
			while ( offset-- ) {
				if ( ptr->next == NULL) {
					std::cerr << "LinkedList::Iterator::data() accessed NULL ptr." << std::endl;
					break;
				}
				ptr = ptr->next;
			}
			return *this;
		}
		const bool operator!=(const LinkedList::Iterator & itr) const {
			return ptr != itr.ptr;
		}
		const bool operator==(const LinkedList::Iterator & itr) const {
			return ptr == itr.ptr;
		}
	};

public:
	LinkedList();
	~LinkedList();
	unsigned int size() const { return elemcount; }

	ListNode * append(const void* dataptr);
	ListNode * push(const void* dataptr);
	const void * pop();

	Iterator begin() { return Iterator(head); }
	Iterator end() { return Iterator(tail); }
	ListNode * make_tail_loop(unsigned int ith);

	friend std::ostream & operator<<(std::ostream & out, const LinkedList & list) {
		ListNode * ptr = list.head->next;
		while ( ptr != NULL ) {
			out << reinterpret_cast<unsigned long long>(ptr->data) << ' ';
			if ( ptr == list.tail )
				break;
			ptr = ptr->next;
		}
		return out;
	}

};

#endif /* LINKEDLIST_H_ */
