#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define M 40

struct _Dir;
typedef struct _Dir* position;
typedef struct _Dir {
	char name[M];
	position sibling;
	position child;

}Dir;

struct _Stack;
typedef struct _Stack* stack_pos; 
typedef struct _Stack {
	stack_pos next;
	position lastdir;
}Stack; 


position CreateNew(char* name) {
	position new_adress = (position)malloc(sizeof(Dir));
	if (!new_adress) {
		printf("Nemoguce stvoriti novi direktorij");
		return NULL;
	}
	strcpy(new_adress->name, name);
	new_adress->child = NULL;
	new_adress->sibling = NULL;
	return new_adress;
}

/* REKURZIVNI INSERT--> insert(C-POINTER NAADRESU NA KOJU SPREMAMO, G-ADRESA KOJU SPREMAMO)
*					3 provjere: 
								1. AKO C==NULL, VRATI G || -> POTOM JE C=G
*								2. AKO STRCMP(C-NAME,G-NAME)>0 ||-> G JE PRIJE PO ABECEDI --> G-sibling=C;
*								3. AKO /___________________/<0 || -> G JE IZA C PO ABECEDI --> c-sibling=insert(c-sibling,g) --> saljemo siblinga od c i vrsimo iste provjere.	
							Zakljucak: Ili ce doci do kraja pa ce C==NULL, ili ce pronaci element kojem prethodi te g-sibling=C;
									PS+: Ako su jednaki free(g), jer unosenje istih direktorija nije dopustenp */
position insert(position current, position new_adress) {
	if (current == NULL) {
		return new_adress;
	}
	else if (strcmp(current->name, new_adress->name) > 0) {
		new_adress->sibling = current;
		return new_adress;
	}
	else if (strcmp(current->name, new_adress->name) < 0) {
		current->sibling = insert(current->sibling, new_adress);
	}
	else {
		free(new_adress);
		printf("Name taken");
		return NULL;
	}
	
}

position FindByName(position current,char* g) {  //g pointer na trazeno ime... trazenje po podirektoriju ....current smatraj firstchild
	position temp = current;
	if (!temp) {
		printf("Empty directory,nothing found");
		return NULL;
	}
	while (temp->sibling != NULL) {
		if (strcmp(temp->name, g) == 0)
			{
			printf("Element pronaden");
				return temp;
			}
		
		else {
			temp = current->sibling;}	
			}
	printf("Element nije pronaden");
	return NULL;
}

int DeleteAfter(stack_pos before) {
	stack_pos ToDelete = before->next;
	if (!ToDelete) { // Ako element za obrisat ne postoji
		return EXIT_SUCCESS;
	}
	before->next = ToDelete->next;
	free(ToDelete);
	return EXIT_SUCCESS;
}

 int PushToStack(stack_pos head, position last) {
	stack_pos temp = (stack_pos)malloc(sizeof(Stack));
	if (!temp) { return EXIT_FAILURE; }
	temp->next = head->next;
	head->next = temp;
	temp->lastdir = last;
	return EXIT_SUCCESS;
 }
 
 int PopFromStack(stack_pos head, position current) // u current saljemo Pop sa stacka
 {
	 stack_pos first = head->next; //temp na first
	 current = first->lastdir;
	 DeleteAfter(head);
	 return EXIT_SUCCESS;
	}


 // Koristit stog za vracanje nazad, popat zadnju adresu sa stoga 
position GoBack(stack_pos head,position current) { //current ce predstavljat pokazivac na trenutni dir
	PopFromStack(head,current);
	if (current != NULL) { printf("\nIn root"); }
	else printf("\n%s",current->name);

	}


int DeleteDir(position parent, char* name) {
	position ToDelete = NULL;
	position tempchild = parent->child; //postavljamo na first child
	char tempname[M];
	if (!tempchild) {
		printf("Empty directory, nothing to delete");
		return EXIT_SUCCESS;
	}
	ToDelete = FindByName(tempchild, name);
	if (!ToDelete) {
		printf("No dir found");
	}
	else {
		while (tempchild->sibling != ToDelete) {
			tempchild = tempchild->sibling;
		}
		tempchild->sibling = ToDelete->sibling;
		strcpy(tempname, ToDelete->name);
		free(ToDelete);
		printf("%s dir succesfully deleted",tempname);
	}
	return EXIT_SUCCESS;
	}

int DeleteFirstChild(position parent) {
	position temp = parent;
	position ToDelete = parent->child;
	if (temp->child) {
		return EXIT_SUCCESS;
	}
	temp->child = ToDelete->sibling;
	free(ToDelete);
	return EXIT_SUCCESS;

}

int DeleteAll(position root) { // REKURZIVNO --> DOK IMAS DJECE BRISI DJECU, KAD NEMAS DJECE BRISI SEBE 
	position firstchild = root->child; //postavljen na first child
	position parent= root;

	if (!firstchild) {
		 //printf("C is empty, no subdirectories found"); 
		return EXIT_SUCCESS;
	}

	if (firstchild->child) {
		DeleteAll(firstchild->child);
	}
	else {
		DeleteFirstChild(parent);
		DeleteAll(parent);
	}
}



