// BST_2018.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
//
//  main.c
//  BST
//
//  Created by Yunhee on 4/17/13.
//  Copyright (c) 2013 Yunhee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

// 3 종류의 노드 선언
struct node {
	int data;
	struct node* left;
	struct node* right;
};

typedef int BTData;
  
typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode * left;
	struct _bTreeNode * right;
} BTreeNode;
 

/*
Helper function that allocates a new node
with the given data and NULL left and right
pointers.
*/
struct node* newNode(int data) {
	struct node* node = (struct node*)malloc(sizeof(struct node));    // "new" is like "malloc"
	
	 
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return(node);
}

BTreeNode* newNode1(int data) {
	 
	BTreeNode  * node = (BTreeNode*)malloc(sizeof(BTreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return(node);
}


// call newNode() three times
struct node* build123a() {

	struct node* root = newNode(2);
	struct node* lChild = newNode(1);
	struct node* rChild = newNode(3);

	root->left = lChild;
	root->right = rChild;

	return(root);
}
/*
Given a binary tree, return true if a node
with the target data is found in the tree. Recurs
down the tree, chooses the left or right
branch by comparing the target to each node.
*/

#define false 0
#define true 1
static int lookup(struct node* node, int target) {
	// 1. Base case == empty tree
	// in that case, the target is not found so return false
	if (node == NULL) {
		return(false);
	}
	else {
		// 2. see if found here
		if (target == node->data) return(true);
		else {
			// 3. otherwise recur down the correct subtree
			if (target < node->data) return(lookup(node->left, target));
			else return(lookup(node->right, target));
		}
	}
}

struct node* treeSearch(struct node* node, int target) {
	// 1. Base case == empty tree
	// in that case, the target is not found so return false
	if (node == NULL || target == node->data) {
		return(node);
	}
	else {
		 
			// 3. otherwise recur down the correct subtree
			if (target < node->data) return(treeSearch(node->left, target));
			else return(treeSearch(node->right, target));
	}
}
/*
Give a binary search tree and a number, inserts a new node
with the given number in the correct place in the tree.
Returns the new root pointer which the caller should
then use (the standard trick to avoid using reference
parameters).
*/
struct node* insert(struct node* node, int data) {
	// 1. If the tree is empty, return a new, single node
	if (node == NULL) {
		return(newNode(data));
	}
	else {
		// 2. Otherwise, recur down the tree
		if (data <= node->data) node->left = insert(node->left, data);
		else node->right = insert(node->right, data);

		return(node); // return the (unchanged) node pointer
	}
}

/*
Build 123 by calling insert() three times.
Note that the '2' must be inserted first.
*/
struct node* build123c() {
	struct node* root = NULL;
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 3);
	return(root);
}

struct node* build1234c() {
	struct node* root = NULL;
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 4);
	root = insert(root, 5);
	return(root);
}
/*
Given a non-empty binary search tree,
return the minimum data value found in that tree.
Note that the entire tree does not need to be searched.
*/
int minValue(struct node* node) {
	struct node* current = node;

	// loop down to find the leftmost leaf
	while (current->left != NULL) {
		current = current->left;
	}

	return(current->data);
}

struct node * minValueNode(struct node* node) {
	struct node* current = node;

	// loop down to find the leftmost leaf
	while (current->left != NULL) {
		current = current->left;
	}

	return(current);
}

int maxValue(struct node* node) {
	struct node* current = node;

	// loop down to find the leftmost leaf
	while (current->right != NULL) {
		current = current->right;
	}

	return(current->data);
}

/*
Given a binary search tree, print out
its data elements in increasing
sorted order.
*/
void printTree(struct node* node) {
	if (node == NULL) return;

	printTree(node->left);
	printf("%d ", node->data);
	printTree(node->right);
}

/*
Compute the "maxDepth" of a tree -- the number of nodes along
the longest path from the root node down to the farthest leaf node.
*/
int maxDepth(struct node* node) {
	if (node == NULL) {
		return(0);
	}
	else {
		// compute the depth of each subtree
		int lDepth = maxDepth(node->left);
		int rDepth = maxDepth(node->right);

		// use the larger one
		if (lDepth > rDepth)
			return(lDepth + 1);
		else
			return(rDepth + 1);
	}
}

/*
Compute the number of nodes in a tree.
*/
int size(struct node* node) {
	if (node == NULL) {
		return(0);
	}
	else {
		return(size(node->left) + 1 + size(node->right));
	}
}

/*
Given a tree and a sum, return true if there is a path from the root
down to a leaf, such that adding up all the values along the path
equals the given sum.

Strategy: subtract the node value from the sum when recurring down,
and check to see if the sum is 0 when you run out of tree.
*/
int hasPathSum(struct node* node, int sum) {
	// return true if we run out of tree and sum==0
	if (node == NULL) {
		return(sum == 0);
	}
	else {
		// otherwise check both subtrees
		int subSum = sum - node->data;
		return(hasPathSum(node->left, subSum) ||
			hasPathSum(node->right, subSum));
	}
}
struct node* deleteNode(struct node* root, int key)
{
	// base case 
	if (root == NULL) return root;

	// If the key to be deleted is smaller than the root's key, 
	// then it lies in left subtree 
	if (key < root->data)
		root->left = deleteNode(root->left, key);

	// If the key to be deleted is greater than the root's key, 
	// then it lies in right subtree 
	else if (key > root->data)
		root->right = deleteNode(root->right, key);

	// if key is same as root's key, then This is the node 
	// to be deleted 
	else
	{
		// node with only one child or no child 
		if (root->left == NULL)
		{
			struct node *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			struct node *temp = root->left;
			free(root);
			return temp;
		}

		// node with two children: Get the inorder successor (smallest 
		// in the right subtree) 
		struct node* temp = minValueNode(root->right);

		// Copy the inorder successor's content to this node 
		root->data = temp->data;

		// Delete the inorder successor 
		root->right = deleteNode(root->right, temp->data);
	}
	return root;
}
void mirror(struct node* node) {
	if (node == NULL) {
		return;
	}
	else {
		struct node* temp;

		// do the subtrees
		mirror(node->left);
		mirror(node->right);

		// swap the pointers in this node
		temp = node->left;
		node->left = node->right;
		node->right = temp;
	}
}

int main(int argc, const char * argv[])
{
	struct node * root, *t;
	int n;

	root = build123a();

	BTreeNode  * node1 = newNode1(10);

	printTree(root);
	printf("\n");
	t= treeSearch(root, 2);

	if (t != NULL)
		printf("found = %d\n", t->data);
	else
		printf("not found\n");

	getchar();
	getchar();
	


	//root = build1234c();
	printf("Enter number of keys\n");
	scanf_s("%d", &n);


	int key;
	int i;

	root = NULL;
	printf("Enter %d keys\n", n);
	for (i = 0; i < n; i++) {
		scanf_s("%d", &key);
		root = insert(root, key);
	}
	printTree(root);  printf("\n");

	printf("minimum value = %d\n", minValue(root));
	printf("maximum value = %d\n", maxValue(root));
	printf("Height value = %d\n", maxDepth(root) - 1);
	printf("size of tree = %d\n", size(root));
	printf("there is 10 = %d\n", lookup(root, 10));
	printf("Path  = %d\n", hasPathSum(root->left, 0));

	printf("\nDelete 20\n");
	root = deleteNode(root, 20);
	printf("Inorder traversal of the modified tree \n");
	printTree(root);  printf("\n");

	getchar();
	getchar();
	return 0;
}

 
