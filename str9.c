#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct cvor; 
typedef struct cvor* position;
typedef struct cvor {
	int value;
	position lchild;
	position rchild;
}cvor;

position CreateNew(int setvalue) {
	position new_element;
	new_element= (position)malloc(sizeof(cvor));
	new_element->value = setvalue;
	new_element->lchild = NULL;
	new_element->rchild = NULL;
	return new_element;
}
int insert(position root, int setvalue) {
	position new_element = NULL;
	if (!root) {
		new_element = CreateNew(setvalue);
		if (!new_element) {
			printf("Can't allocate memory");
			return EXIT_FAILURE;
		}
		root = new_element;
		return;
	}
	if (setvalue >= root->value) {
		insert(root->lchild, setvalue);
		return;
	}
	else if (setvalue < root->value) {
		insert(root->rchild, setvalue);
		return;
	}
}

int PrintInOrder(position root) {
	if (root == NULL) {
		return;
	}
	PrintInOrder(root->lchild);
	printf("%d", root->value);
	PrintInOder(root->rchild);
}
position MakeTree(int a[], int n,position root) {
	for (int i = 0;i < n;i++) {
		insert(root, a[i]);
	}
	return root;
}
position replace(position root) {
	int sum=0;
	position templ, tempr;
	templ = root->lchild;
	tempr = root->rchild;
	if (!root) {
		return 0;
	}
	if (templ) {
		templ=replace(templ);
	}
	if (tempr) {
		tempr = replace(tempr);
	}
	root->value = templ->value + tempr->value;
	return root;
}



 
int main() {
	int a[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int n;
	position root = NULL;
	n = sizeof(a) % sizeof(int);
	root=MakeTree(a, n, root);
	replace(root);



}









