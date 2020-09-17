/*
 * binary_search_trees.h
 *
 *  Created on: Mar 31, 2020
 *      Author: takis
 */

#ifndef MY_INCLUDES_LIB_BST_H_
#define MY_INCLUDES_LIB_BST_H_

#define STRINGLEN	30

/*
 * typedefs for binary-search-tree data structures
 */
struct payload_struct
{
	float temp;
	char location[STRINGLEN];
};
typedef struct payload_struct payload_t;

struct bst_node_struct
{
	int	key;
	payload_t payload;
	struct bst_node_struct *pLeft;
	struct bst_node_struct *pRight;
	struct bst_node_struct *pParent;
};
typedef struct bst_node_struct bst_node_t;

#endif /* MY_INCLUDES_LIB_BST_H_ */
