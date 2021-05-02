/* B-Tree
 * Author:	Caleb Baker
 * Date:	10/8/17
 * Summary:	A B-Tree data structure.
 *			Most standard operations run in O(lg(n)) time.
 *			Uses O(n) memory.
 *			Where n is the number of items in the tree.
 * Repository: https://github.com/CalebLBaker/b-tree
 */


#ifndef BTREE_H
#define BTREE_H

#include <utility>
#include "ItemIndiceDireto.h"

#define NIL 0
#define SEARCH_KEY_NOT_FOUND 's'
#define REMOVE_KEY_NOT_FOUND 'r'

struct BNode
{
	BNode **child;
	ItemIndiceDireto *key;
	unsigned int size;
	bool leaf;
};

typedef char BTREE_EXCEPTION;

class BTree
{
public:
	// Constructor
	// Parameter is the minimum degree of the tree.
	// Constant time.
	BTree();

	// Destructor.
	// Linear time.
	~BTree();

	// Inserts a key into the tree.
	// Logorithmic time.
	void insert(ItemIndiceDireto);

	// Removes a key from the tree.
	// Throws a BTREE_EXCEPTION if no item was found to remove.
	// Logorithmic time.
	ItemIndiceDireto remove(ItemIndiceDireto);

	// Function to find a key in the tree.
	// returnValue.first is the node the item is in.
	// returnValue.second is the correct index in that node's key array
	// Logorithmic time.
	std::pair<BNode *, unsigned int> search(ItemIndiceDireto);

	// Uses search but just returns the key rather than the whole node.
	// Useful when ItemIndiceDireto is a key value pair and lessThan only looks at the key.
	// Throws a BTREE_EXCEPTION if no item matching the parameter is found
	// Logorithmic time.
	ItemIndiceDireto searchKey(ItemIndiceDireto);

	// Prints the tree.
	// Linear time
	void print();

private:
	// Used for initializing nodes.
	void initializeNode(BNode *);

	// Recursive function called by destructor.
	void freeNode(BNode *);

	// Finds the index of a key in a node.
	unsigned int findIndex(BNode *, ItemIndiceDireto);

	// Inserts a key into a node.
	unsigned int nodeInsert(BNode *, ItemIndiceDireto);

	// Deletes the key at a given index from a node.
	ItemIndiceDireto nodeDelete(BNode *, unsigned int);

	// Function for splitting nodes that are too full.
	void splitChild(BNode *, int);

	// Merges two children of a node at a given index into one child.
	char mergeChildren(BNode *, unsigned int);

	// Makes sure the child of a node at a specified index has >= minDegree items.
	char fixChildSize(BNode *, unsigned int);

	// Recursively prints a subtree.
	void printNode(BNode *, unsigned int);

	// Root node.
	BNode *root;

	// Minimum degree of the tree.
	unsigned int minDegree;
};

#endif // BTREE_H
