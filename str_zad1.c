#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 0. Definicija strukture

typedef struct studenti {
	char ime[20];
	char prezime[20];
	double bodovi;

}student;

// 1. Broj redova
int BrojStud(FILE* in) {
	int br=0;
	char tmp;
	while(!feof(in)){
		tmp = fgetc(in);
		if (tmp== '\n') { br++; }
	}
	return br;
}
// 2. Alokacija
student* Alociraj(student* pstudent,int n) {
	pstudent = (student *)malloc(n * sizeof(student));
	return pstudent;
}


//3. Citanje iz fajla + 4. Ispis
void Ispis(FILE* in, student* pstudent, int n) {
	int i;
	double max = 0;
	for (i = 0;i < n;i++)
	{
		fscanf(in, "%s %s %lf", pstudent[i].ime, pstudent[i].prezime, &pstudent[i].bodovi);
		if (pstudent[i].bodovi > max) { max = pstudent[i].bodovi; }
	}
	for (i = 0;i < n;i++) {
	printf("%s %s %lf %lf\n", pstudent[i].ime, pstudent[i].prezime, pstudent[i].bodovi, (pstudent[i].bodovi/max)*100);}
}



int main() {
	FILE* in;
	int n,max;
	student* pstudent=NULL;
	in = fopen("studenti.txt", "r");
	if (in == NULL) { printf("Neuspjesno otvaranje datoteke"); }
	n = BrojStud(in);
	rewind(in);
	pstudent=Alociraj(pstudent, n);
	Ispis(in, pstudent, n);
	fclose(in);
	free(pstudent);
	return 1; }