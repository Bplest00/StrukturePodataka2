#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_BROJ 40

struct _stackElement;
typedef struct _stackElement* Position;
typedef struct _stackElement {
	double number;
	Position next;
}stackElement;


Position CreateElement(double number) {
	Position newElement = NULL; 
	newElement = (Position)malloc(sizeof(stackElement));
	if (!newElement) {
		perror("Can't allocate memory");
		return NULL;   //MOZEMO LI VRACAT EXIT_FAILURE? ILI TO KAD VRACAMO INT? 
	}
	newElement->number = number;
	return newElement;

}
 //Dodajemo na vrh, potom potrebno slat samo head
int Push(Position head, double number) { //Prima adresu heada 
	Position newElement = CreateElement(number);
	if (!newElement) { return EXIT_FAILURE; }
	newElement = head->next;
	head->next = newElement;
	return EXIT_SUCCESS;
	}
int DeleteAfter(Position position) {
	Position ZaObrisat = position->next;
	if (!ZaObrisat) { // Ako element za obrisat ne postoji
		return EXIT_SUCCESS; 
	}
	position->next = ZaObrisat->next;
	free(ZaObrisat);
	return EXIT_SUCCESS;
}
int Pop(double* RezultatAdr, Position head) {
	Position first = head->next;
	if (!first) {
		printf("Error, please check postfix file");
		return -1;
	}
	*RezultatAdr = first->number;
	DeleteAfter(head);
	return 0;
	
}
FILE* OpenFile(char* filename) {
	FILE* in = NULL; 
	in = fopen(filename, "rb");
	if (!in) {
		printf("Error opening file, please check filename");
		return -1;
	}
	return in;
}

int DeleteAll(Position head)
{
	while (head->next)
	{
		DeleteAfter(head);
	}

	return EXIT_SUCCESS;
}

int Calculate(char operator, Position head) { //saljemo odma head jer nakon operacije racunamo
	double operand1;
	double operand2; 
	double result;
	int status1 = 0;
	int status2 = 0;
	status1 = Pop(&operand1, head);
	if (status1 != 0) {
		return -1;
	}
	status2 = Pop(&operand2, head);
	if (status2 != 0) {
		return -2;
	}
	switch (operator) {
	case '+':
		result = operand2 + operand1;
		break;
	case '-':
		result = operand2 - operand1;
		break;
	case '*':
		result = operand2 * operand1;
		break;
	case '/':
		if (operand1 == 0) {
			printf("Cant divide with zero");
			return -3;
		}
		result = operand2 / operand1;
		break;
	default:
		printf("Unsupported operation");
		return -4;
	}
	return Push(head, result);

}
 //  Razmislja san da odvojin funkciju citanja fajla i racunanja --> to bi kompliciralo stvar na stacku
int PostfixFromFile(FILE* in) {
	char* buffer = NULL;
	char* cbuffer = NULL;
	int numbytes = 0;
	char operator='h';
	double number;
	int status = EXIT_SUCCESS;
	int filelen = 0;
	stackElement head = { .next = NULL , .number = 0 };
	fseek(in, 0, SEEK_END); //--> prvo s fseek idemo na kraj fajla
	filelen = ftell(in); //---> onda s ftell vracamo poziciju u fajlu
	buffer = (char*)malloc(filelen + 1, sizeof(char));
	if (!buffer) {
		printf("Cant allocate memory");
		return -1;

	}
	rewind(in);
	fread(buffer, sizeof(char), filelen + 1, in);
	cbuffer = buffer;
	while (strlen(cbuffer) > 0) {
		status = sscanf(cbuffer, "%d %n", &number, &numbytes);
		if (status) {
			status = Push(&head, number);
			if (!status) {
				DeleteAll(&head);
				return -2;
			}
			cbuffer = cbuffer + numbytes;
		}
		else {
			status = sscanf(cbuffer, "%c %n", operator,&numbytes);
			if (!status) {
				printf("FILE NOT VALID");
				DeleteAll(&head);
				return -3;
			}
			status = Calculate(operator,&head);
			if (status == -1 || status == -2) {
				printf("FILE NOT VALID");
				DeleteAll(&head);
				return -3;

			}
			cbuffer = cbuffer + numbytes;
		}

	}

	free(buffer);
	/*if (head.next->next->number) {
		printf("Postfix incomplete");
	}*/
	printf("%lf", head.next->number);
	return EXIT_SUCCESS;
}

int main() {
	FILE* in;
	char filename[MAX_BROJ];
	scanf("%s", filename);
	OpenFile(in);
	PostfixFromFile(in);
	return 0;
}

