/*
 * University of Central Florida 
 * COP 3502C - Fall 2018 
 * Author: Jose Aguilar 
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct
typedef struct Node
{
	char name[25];
	struct Node* left;
	struct Node* right;
	struct Node* secTree;
}Node;

// prototypes
void getInput(Node*, Node*);
void getShops(Node*);
void getDough(Node*);
void inOrder(Node*);
Node* insert(Node*, char*);
Node* search(Node*, char*);
int numNodes(Node*);

int main(void)
{
	int userChoice = -1;
	Node* doughRoot = NULL;
	Node* shopRoot = NULL;
	
	
	while (userChoice != 0)
	{
		scanf("%d", &userChoice);
		
		if (userChoice == 1)
		{
			// get input from user
			getInput(doughRoot, shopRoot);
		}
		
		if (userChoice == 2)
		{
			// get shops
			getShops(doughRoot);
		}
		
		if (userChoice == 3)
		{
			// get doughnuts
			getDough(shopRoot);
		}
	}// end while loop for user choice 
	
	return EXIT_SUCCESS;
}

// functions

void getInput(Node* doughnuts, Node* shops)
{
	int numDoughnuts = 0, numShops = 0;
	char** doughArr;
	char** shopArr;
	
	scanf("%d", &numDoughnuts);
	scanf("%d", &numShops);
	
	doughArr = (char**)calloc(numDoughnuts, sizeof(char*));
	
	for (int i = 0; i < numDoughnuts; i++)
	{
		doughArr[i] = (char*)calloc(25, sizeof(char));
		scanf("%s", doughArr[i]);
	}
	
	shopArr = (char**)calloc(numShops, sizeof(char*));
	
	for (int i = 0; i < numShops; i++)
	{
		shopArr[i] = (char*)calloc(25, sizeof(char));
		scanf("%s", shopArr[i]);
	}
	// add doughnuts to BST
	for (int i = 0; i < numDoughnuts; i++)
	{
		doughnuts = insert(doughnuts, doughArr[i]);
		// add shops to each doughnuts secondary tree
		for (int j = 0; j < numShops; j++)
		{
			doughnuts->secTree = insert(doughnuts->secTree, shopArr[j]);
		}
	}
	// add shops to BST
	for (int i = 0; i < numShops; i++)
	{
		shops = insert(shops, shopArr[i]);
		// add doughnuts to shops secondary tree 
		for (int j = 0; j < numDoughnuts; j++)
		{
			shops->secTree = insert(shops->secTree, doughArr[j]);
		}
	}
	
	for (int i = 0; i < numDoughnuts; i++)
	{
		free(doughArr[i]);
	}
	
	for (int i = 0; i < numShops; i++)
	{
		free(shopArr[i]);
	}
	
	free(doughArr);
	free(shopArr);
}

void getShops(Node* curNode)
{
	Node* temp = curNode;
	Node* target = NULL;
	char targetDough[25];
	int count = 0;
	
	
	scanf("%s", targetDough);
	
	count = numNodes(curNode);
	
	printf("%d", count);
	
	target = search(temp, targetDough);
	
	inOrder(target->secTree);
	
}


void getDough(Node* curNode)
{
	Node* target = NULL;
	char targetShop[25];
	int count = 0;
	
	scanf("%s", targetShop);
	
	target = search(curNode, targetShop);
	
	count = numNodes(curNode);
	
	printf("%d", count);
	
	inOrder(target->secTree);
	
}


void inOrder(Node* root)
{
    if (root == NULL)
        return;
    
    inOrder(root->left);
    printf("%s\n", root->name);
    inOrder(root->right);
}


Node* insert(Node* curNode, char* str)
{
	if (curNode == NULL)
	{
		// create new node if tree is empty
		Node* newNode = (Node*)calloc(1, sizeof(Node));
		
		strcpy(newNode->name, str);
		newNode->left = NULL;
		newNode->right = NULL;
		
		return newNode;
	}
	
	while (strcmp(curNode->name, str) != 0)
	{
		if (strcmp(curNode->name, str) > 0)
		{
			// go left
			curNode->left = insert(curNode->left, str);
		}
		else
		{
			// go right
			curNode->right = insert(curNode->right, str);
		}
		
		return curNode;
	}// end while loop to check for duplicates
}

Node* search(Node* root, char* str)
{
	if (root == NULL)
		return root;
	
	if (strcmp(root->name, str) == 0)
		return root;
	
	else if (strcmp(root->name, str) > 0)
		return search(root->right, str);
	
	else
		return search(root->left, str);
}

int numNodes(Node* root)
{
	int count = 0;
	
	if (root == NULL)
		return 0;
	
	count += numNodes(root->left) + numNodes(root->right);
	
	return count;
    
}