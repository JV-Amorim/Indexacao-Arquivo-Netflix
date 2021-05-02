/* B-Tree
 * Author:	            Caleb Baker
 * Date:	            10/8/17
 * Summary:	            A B-Tree data structure. Supports lg(n) time search, insert, and delete.
 * Repository:          https://github.com/CalebLBaker/b-tree
 */

#include <stdlib.h>
#include <utility>
#include <stdio.h>
#include <iostream>
#include "BTree.h"

using namespace std;

#define NEW_ROOT 2
#define MODIFIED_NOT_ROOT 1
#define NOT_MODIFIED 0

BTree::BTree()
{
	minDegree = 3;
	root = (BNode *)malloc(sizeof(BNode));
	initializeNode(root);
	root->leaf = true;
}

BTree::~BTree()
{
	freeNode(root);
}

void BTree::insert(ItemIndiceDireto k)
{
	if (root->size == 2 * minDegree - 1)
	{
		BNode *newRoot = (BNode *)malloc(sizeof(BNode));
		initializeNode(newRoot);
		newRoot->leaf = false;
		newRoot->child[0] = root;
		root = newRoot;
		splitChild(newRoot, 0);
	}

	BNode *curr = root;

	while (!curr->leaf)
	{
		int index = curr->size - 1;

		while (index >= 0 && k < curr->key[index])
		{
			index--;
		}

		index++;

		if (curr->child[index]->size == 2 * minDegree - 1)
		{
			splitChild(curr, index);

			if (curr->key[index] < k)
			{
				index++;
			}
		}
		curr = curr->child[index];
	}

	nodeInsert(curr, k);
}

ItemIndiceDireto BTree::remove(ItemIndiceDireto k)
{
	BNode *curr = root;
	while (true)
	{
		unsigned int i = findIndex(curr, k);

		if (i < curr->size && !(curr->key[i] < k || k < curr->key[i]))
		{
			ItemIndiceDireto toReturn = curr->key[i];

			if (curr->leaf)
			{
				nodeDelete(curr, i);
			}

			else
			{
				BNode *leftKid = curr->child[i];
				BNode *rightKid = curr->child[i + 1];

				if (leftKid->size >= minDegree)
				{
					while (!(leftKid->leaf))
					{
						fixChildSize(leftKid, leftKid->size);
						leftKid = leftKid->child[leftKid->size];
					}
					curr->key[i] = nodeDelete(leftKid, leftKid->size - 1);
				}
				else if (rightKid->size >= minDegree)
				{
					while (!(rightKid->leaf))
					{
						fixChildSize(rightKid, 0);
						rightKid = rightKid->child[0];
					}
					curr->key[i] = nodeDelete(rightKid, 0);
				}
				else
				{
					mergeChildren(curr, i);
					curr = leftKid;
					continue;
				}
			}
			return toReturn;
		}
		else
		{
			if (curr->leaf)
			{
				throw(BTREE_EXCEPTION) REMOVE_KEY_NOT_FOUND;
			}

			char result = fixChildSize(curr, i);
			if (result == NEW_ROOT)
			{
				curr = root;
			}
			else
			{
				curr = curr->child[findIndex(curr, k)];
			}
		}
	}
}

pair<BNode *, unsigned int> BTree::search(ItemIndiceDireto k)
{
	BNode *x = root;

	while (true)
	{
		unsigned int i = findIndex(x, k);

		if (i < x->size && !(k < x->key[i] || x->key[i] < k))
		{
			return pair<BNode *, unsigned int>(x, i);
		}
		else if (x->leaf)
		{
			return pair<BNode *, unsigned int>(NIL, 0);
		}
		else
		{
			x = x->child[i];
		}
	}
}

ItemIndiceDireto BTree::searchKey(ItemIndiceDireto k)
{
	pair<BNode *, unsigned int> node = search(k);
	if (node.first == NIL)
	{
		throw(BTREE_EXCEPTION) SEARCH_KEY_NOT_FOUND;
	}
	return node.first->key[node.second];
}

void BTree::print()
{
    cout << "B-TREE" << endl;
    printNode(root, 0);
    cout << endl;
}

void BTree::initializeNode(BNode *x)
{
	x->size = 0;
	x->key = (ItemIndiceDireto *)malloc((2 * minDegree - 1) * sizeof(ItemIndiceDireto));
	x->child = (BNode **)malloc(2 * minDegree * sizeof(BNode *));
}

void BTree::freeNode(BNode *x)
{
	if (!x->leaf)
	{
		for (unsigned int i = 0; i <= x->size; i++)
		{
			freeNode(x->child[i]);
		}
	}
	free(x->child);
	free(x->key);
	free(x);
}

unsigned int BTree::findIndex(BNode *x, ItemIndiceDireto k)
{
	unsigned int i = 0;
	while (i < x->size && x->key[i] < k)
	{
		i++;
	}
	return i;
}

unsigned int BTree::nodeInsert(BNode *x, ItemIndiceDireto k)
{
	int index;

	for (index = x->size; index > 0 && k < x->key[index - 1]; index--)
	{
		x->key[index] = x->key[index - 1];
		x->child[index + 1] = x->child[index];
	}

	x->child[index + 1] = x->child[index];
	x->key[index] = k;
	x->size++;

	return index;
}

ItemIndiceDireto BTree::nodeDelete(BNode *x, unsigned int index)
{
	ItemIndiceDireto toReturn = x->key[index];

	x->size--;
	while (index < x->size)
	{
		x->key[index] = x->key[index + 1];
		x->child[index + 1] = x->child[index + 2];
		index++;
	}
	return toReturn;
}

void BTree::splitChild(BNode *x, int i)
{
	BNode *toSplit = x->child[i];
	BNode *newNode = (BNode *)malloc(sizeof(BNode));
	initializeNode(newNode);
	newNode->leaf = toSplit->leaf;
	newNode->size = minDegree - 1;

	for (unsigned int j = 0; j < minDegree - 1; j++)
	{
		newNode->key[j] = toSplit->key[j + minDegree];
	}
	if (!toSplit->leaf)
	{
		for (unsigned int j = 0; j < minDegree; j++)
		{
			newNode->child[j] = toSplit->child[j + minDegree];
		}
	}
	toSplit->size = minDegree - 1;

	nodeInsert(x, toSplit->key[minDegree - 1]);
	x->child[i + 1] = newNode;
}

char BTree::mergeChildren(BNode *parent, unsigned int i)
{
	BNode *leftKid = parent->child[i];
	BNode *rightKid = parent->child[i + 1];

	leftKid->key[leftKid->size] = nodeDelete(parent, i);
	unsigned int j = ++(leftKid->size);

	for (unsigned int k = 0; k < rightKid->size; k++)
	{
		leftKid->key[j + k] = rightKid->key[k];
		leftKid->child[j + k] = rightKid->child[k];
	}
	leftKid->size += rightKid->size;
	leftKid->child[leftKid->size] = rightKid->child[rightKid->size];

	free(rightKid->child);
	free(rightKid->key);
	free(rightKid);

	if (parent->size == 0)
	{
		root = leftKid;
		free(parent->child);
		free(parent->key);
		free(parent);
		return NEW_ROOT;
	}

	return MODIFIED_NOT_ROOT;
}

char BTree::fixChildSize(BNode *parent, unsigned int index)
{
	BNode *kid = parent->child[index];

	if (kid->size < minDegree)
	{
		if (index != 0 && parent->child[index - 1]->size >= minDegree)
		{
			BNode *leftKid = parent->child[index - 1];
			for (unsigned int i = nodeInsert(kid, parent->key[index - 1]); i != 0; i--)
			{
				kid->child[i] = kid->child[i - 1];
			}
			kid->child[0] = leftKid->child[leftKid->size];
			parent->key[index - 1] = nodeDelete(leftKid, leftKid->size - 1);
		}
		else if (index != parent->size && parent->child[index + 1]->size >= minDegree)
		{
			BNode *rightKid = parent->child[index + 1];
			nodeInsert(kid, parent->key[index]);
			kid->child[kid->size] = rightKid->child[0];
			rightKid->child[0] = rightKid->child[1];
			parent->key[index] = nodeDelete(rightKid, 0);
		}
		else if (index != 0)
		{
			return mergeChildren(parent, index - 1);
		}
		else
		{
			return mergeChildren(parent, index);
		}
		return MODIFIED_NOT_ROOT;
	}

	return NOT_MODIFIED;
}

void BTree::printNode(BNode *node, unsigned int tab)
{
	for (unsigned int i = 0; i < tab; i++)
	{
		cout << '\t';
	}

	for (unsigned int i = 0; i < node->size; i++)
	{
		cout << node->key[i].idDoItemNetflix;
		cout << " ";
	}

	cout << endl;

	if (!node->leaf)
	{
		tab++;
		for (unsigned int i = 0; i <= node->size; i++)
		{
			printNode(node->child[i], tab);
		}
	}
}
