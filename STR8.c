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
			return new_element;
			}
		new_element = insert(root->rchild, new_element);
		return new_element;
		}
	else if (new_element->value < root->value)
		{
		if (!root->lchild)
			{
			root->lchild = new_element;
			return new_element;
			}
			new_element = insert(root->lchild, new_element);
			return new_element;
			}
		printf("No duplicates allowed in binary tree\n");
		free(new_element);
		return NULL;
										
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

int PrintPostorder(position root) {
	position temp = root;
	if (temp == NULL) {
		return;
	}
	PrintPostorder(root->lchild);
	PrintPostoder(root->rchild);
	printf("%d", root->value);

}
int PrintInorder(position root) {
	if (root == NULL) {
		return;
	}
	PrintInorder(root->lchild);
	printf("%d", root->value);
	PrintInoder(root->rchild);
}

int PrintPreorder(position root) {
	if (root == NULL) {
		return;
	}
	printf("%d", root->value);
	PrintPreorder(root->lchild);
	PrintPreoder(root->rchild);
}

int DubinaStabla(position root) {
	if (!root) {
		return 0;
	}
	else {
		int ldubina = DubinaStabla(root->lchild);
		int rdubina = DubinaStabla(root->rchild);

		if (ldubina > rdubina) { return ldubina + 1; }
		else if (rdubina >= ldubina) { return rdubina + 1;}
		}

}
int PrintRazina(position root,int razina) {
	if (!root) {
		return;
	}
	if (razina == 1) { printf("%d", root->value); }
	else if (razina > 1) {
		PrintRazina(root->lchild, razina - 1);
		PrintRazina(root->rchild, razina - 1);
	}
}

int PrintLevelOrder(position root) {
	int h = DubinaStabla(root);
	for (int i = 1;i <= h;i++) {
		PrintRazina(root, i);
	}
	return EXIT_SUCCESS;
}

position FindRoot(position root) 
{
	position temp = root;
	if (root->lchild)
	{
		temp = root->lchild;
		while (temp->rchild != NULL)
		{
			temp = temp->rchild;
		}
		return temp;
	}
	else if (root->rchild)
	{
		temp = root->rchild;
		while (temp->lchild != NULL)
		{
			temp = temp->lchild;
		}
		return temp;
	}
	return temp;
}

int ReplaceRoot(position root, position newroot)
	{
	newroot->lchild = root->lchild;
	newroot->rchild = root->rchild;
	free(root);
	return EXIT_SUCCESS;
	}

int DeleteAll(position root)   // Iskomplicira jer sam mislia da triba zaminit s novim elementom root... ako brises cili tree nebitno je sadrzavanje logike  --- pravo rjesenje je brisi brisi djecu brisi sebe rekurzivno...jednostavna funkcija.. 
{	
	position newroot = NULL;
	position temp=CreateNew(0);
	temp->rchild = root->rchild;
	temp->lchild = root->lchild;
	while (temp->lchild || temp->rchild) 
		{
		newroot = FindRoot(root);
		ReplaceRoot(root, newroot);
		}
	free(temp);
	printf("Tree deleted");
	return EXIT_SUCCESS;
}

