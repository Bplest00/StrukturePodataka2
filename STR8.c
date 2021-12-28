#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct _element;
typedef struct _element* position; 
typedef struct _element {
	int value; 
	position lchild;
	position rchild;
}element;

position CreateNew(int set_value) {
	position new_element = (position)malloc(sizeof(element));
	if (!new_element) {
		printf("Cant create element\n");
		return NULL;
	}
	new_element->value = set_value;
	new_element->lchild = NULL;
	new_element->rchild = NULL; 
	return new_element; 
}

position insert(position root,position new_element)
{
	if (new_element->value > root->value)
		{
		if (!root->rchild)
			{
			root->rchild = new_element;
			}
		else 
			{
			new_element = insert(root->rchild, new_element);
			}
		}
	else if (new_element->value < root->value)
		{
		if (!root->lchild)
			{
			root->lchild = new_element;
			}
		else 
			{
			new_element = insert(root->lchild, new_element);
			}
		}
	else 
		{
		printf("No duplicates allowed in binary tree\n");
		free(new_element);
		return NULL;
		}
										
}

int AddToTree(position root,int value)
{
	position new_element = CreateNew(value);
	if (!new_element) 
		{
		return EXIT_FAILURE;
		}
	new_element = insert(root, new_element);
	if (new_element) 
		{
		printf("Value added to tree\n");
		return EXIT_SUCCESS;
		}
	else
		{
		printf("Something went wrong, value wasnt added\n"); 
		return EXIT_FAILURE;

		}
	
}

position FindInTree(position root, int searched) 
{
	position temp = NULL;
	if (!root) 
		{
		printf("No value found");
		return NULL;
		}
	if (root->value > searched)
	{
		temp = FindInTree(root->rchild, searched);
		return temp;
	}
	else if (root->value < searched) 
		{
		temp = FindInTree(root->lchild, searched);
		return temp;
		}
	else 
		{
		temp = root;
		printf("Value found");
		return temp;

		}
}

