/*
 * RedBlack234Tree.h
 *
 *  Created on: 2026/07/07
 *      Author: sin
 */

#ifndef REDBLACK234TREE_H_
#define REDBLACK234TREE_H_

#include <cstdint>
#include "datatype.h"

class RedBlack234Node {
	Data data[3];
	uint8_t first; 		// the start offset position and the sign of the order of data in the node
	int8_t direction; 	// 1 for ascending order, -1 for descending order
	uint8_t number; 	// 1 to 3, the number of data in the node
	RedBlack234Node * children[4];

	void reverse() {
		direction = -direction;

	}

};



#endif /* REDBLACK234TREE_H_ */
