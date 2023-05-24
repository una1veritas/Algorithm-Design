/*
 * bucketsort.c
 */
#include <stdio.h>
#include <stdlib.h>

#include "datadef.h"
#include "llist.h"

/*
void bucketSort_list(LList * dlist, long m, long (*key)(const data)) {
	LList list[m];
	ListNode * node;
	for(int i = 0; i < m; ++i) {
		LList_init(&list[i]);
	}
	while ( !LList_is_empty(dlist) ) {
		node = LList_pop_node(dlist);
		LList_append_node(&list[key(node->dataptr)], node);
	}
	for(int i = 0; i < m; ++i) {
		while ( ! LList_is_empty(&list[i]) ) {
			node = LList_pop_node(&list[i]);
			LList_append_node(dlist, node);
		}
	}
}
*/

void bucket_sort(data * a[], long n, long index_begin, long index_end, int (*keyval)(const data * d)) {
	long range = index_end - index_begin;
	struct {
		data ** bucket;
		unsigned int count;
		unsigned int bucket_size;
	} buckets[range];
	for(long i = 0; i < range; ++i) {
		buckets[i].bucket_size = 4;
		buckets[i].bucket = (data **) malloc(sizeof(data *) * buckets[i].bucket_size);
		buckets[i].count = 0;
	}
	for(long i = 0; i < n; ++i) {
		long index = keyval(a[i]);
		if ( ! (buckets[index].count < buckets[index].bucket_size) ) {
			data ** newbucket = (data **) malloc(sizeof(data*) * (buckets[index].bucket_size << 1) );
			buckets[index].bucket_size <<= 1;
			for(long j = 0; j < buckets[index].bucket_size; ++j) {
				newbucket[j] = buckets[index].bucket[j];
			}
			free(buckets[index].bucket);
			buckets[index].bucket = newbucket;
		}
		buckets[index].bucket[buckets[index].count++] = a[i];
	}
	long dstindex = 0;
	for(long i = 0; i < range; ++i) {
		for(unsigned int j = 0; j < buckets[i].count; ++j) {
			a[dstindex] = buckets[i].bucket[j];
		}
		free(buckets[i].bucket);
	}

}

