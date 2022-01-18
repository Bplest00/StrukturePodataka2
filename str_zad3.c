#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BROJ (40)

struct _Osoba;
typedef struct _Osoba* Pozicija;
typedef struct _Osoba {
	char ime[MAX_BROJ];
	char prezime[MAX_BROJ];
	int god_rod;
	Pozicija next;
}Osoba;

Pozicija StvoriOsobu(char* ime, char* prezime, int godrod) { // OVA FUNKCIJA SAMO ALOCIRA MEMORIJU I VRACA ADRESU --> pitaj profesora zasto smo slali parametre u nju?--> Sad nije vise, bilo mi je logicnije ovako
	Pozicija nova_adresa = NULL;
	nova_adresa = (Pozicija)malloc(sizeof(Osoba));
	if (!nova_adresa) {
		printf("Neuspjesna alokacija memorije, nije vracena nikakva adresa");
		return NULL;
	}
	strcpy(nova_adresa->ime, ime);
	strcpy(nova_adresa->prezime, prezime);
	nova_adresa->god_rod = godrod;

	return nova_adresa;
}
Pozicija DodajNaPocetak(Pozicija head, char* ime, char* prezime, int godrod) { //Jeli ovo mogla biti void funkcija?
	Pozicija nova_adresa = NULL;
	nova_adresa = StvoriOsobu(ime, prezime, godrod);  //sada imamo adresu nove osobe --> potrebno je unit vrijednosti i povezat s headom
	nova_adresa->next = head->next;
	head->next = nova_adresa; // Sada je head povezan s novom osobom, a nova osoba next pokazuje ka sljedecoj osobi
}


Pozicija DodajIza(Pozicija pozicija, char* ime, char* prezime, int godrod) { //Isto pitanje kao za proslu funkciju, s obzirom da smo "call by reference" zar funkcija nebi trebalo samo prominit adrese
	Pozicija nova_adresa = NULL;
	nova_adresa = StvoriOsobu(ime, prezime, godrod);
	nova_adresa->next = pozicija->next;
	pozicija->next = nova_adresa;
}

Pozicija DodajNaKraj(Pozicija head, char* ime, char* prezime, int godrod) { //head jer lista moze bit prazna
	Pozicija temp = head;
	Pozicija nova_adresa;
	nova_adresa = StvoriOsobu(ime, prezime, godrod);


	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = nova_adresa;
}
Pozicija IzbrisiNakon(Pozicija head, Pozicija misto) { //Nakon misto brisemo sljedeceg
	Pozicija temp = head->next;
	Pozicija veza = NULL;
	while (temp != misto) {
		temp = temp->next;
	} //sada temp je na prethodniku onog kojeg brisemo
	temp->next = (misto->next)->next;
	free(misto->next);
}
Pozicija IzbrisiPoPoziciji(Pozicija head, int n) { // koristit cu head jer ce mi tad N-ta pozicija bit ona koju brisen, ne N-1
	int i;
	Pozicija misto = head->next;
	if (misto == NULL) {
		printf("Lista je prazna");
	}
	for (i = 0;i < n - 1;i++) { // IDEMO DO PRETHODNIKA (da bi koristili IzbrisiNakon)
		misto = misto->next;
		if (misto == NULL) {
			printf("%d element je prazan, %d je posljedni element liste", i + 1, i);
			break;
		}
	}
	if (i == n - 2) {
		IzbrisiNakon(head, misto);
	}
	else if (i < n - 2) {
		printf("Element na poziciji %d ne postoji", n);
	}


}

Pozicija DodajIspred(Pozicija head, Pozicija misto, char* ime, char* prezime, int godrod) {
	Pozicija temp = head->next;
	Pozicija nova_adresa = NULL;
	Pozicija veza = NULL;
	while (temp != NULL || temp->next != misto) {
		temp = temp->next;
	}
	if (temp->next == misto) {
		veza = (temp->next)->next;
		nova_adresa = StvoriOsobu(ime, prezime, godrod);
		temp->next = nova_adresa;
		nova_adresa->next = veza;

	}
	else {
		printf("Trazeno mjesto ne postoji");
		return NULL;
	}

}

// DODAJ ISPRED + IZBRISI ISPRED + PRONADI PO PREZIMENU + UPISUJE LISTU U DATOTEKU + CITA LISTU + PRINTA LISTU
int BrisiListu(Pozicija head) {
	Pozicija temp = head->next;
	Pozicija temp2 = NULL;
	if (!temp) {
		return EXIT_SUCCESS;
	}
	while (temp != NULL) {
		temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
	//if (temp != NULL) { free(temp); }

}
int PronadiPrezime(Pozicija head, char* trazenoprezime) {
	Pozicija temp = head->next;
	int i;
	if (!temp)
	{
		printf("Lista je prazna");
		return EXIT_SUCCESS;
	}
	i = 1;
	while (temp != NULL) {
		if (strcmp(temp->prezime, trazenoprezime) == 0)
		{
			printf("\nTrazeni element se nalazi na poziciji %d", i);
			return EXIT_SUCCESS;
		}
		temp = temp->next;
		i++;
	}
	return EXIT_SUCCESS;

}
int PrintajListu(Pozicija head) {
	Pozicija temp = head->next;
	if (!temp)
	{
		printf("\nLista je prazna");
		return EXIT_SUCCESS;
	}
	while (temp != NULL) {
		printf("%s %s %d\n", temp->ime, temp->prezime, temp->god_rod);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int SpremiUFajl(FILE* out, Pozicija head) { // pitaj profesora kako otvorit fajl unutar funkcije, odnosno kako path mu poslat? Moze li char* 
	Pozicija temp = NULL;
	temp = head->next;
	while (temp != NULL)
	{
		fprintf(out, "%s %s %d", temp->ime, temp->prezime, temp->god_rod);
		temp = temp->next;
	}

	return 0;
}

int CitajIzFajla(FILE* in, Pozicija head){
	if (head->next) {
		BrisiListu(head);
	}
	Pozicija temp = NULL;
	char temp_ime[MAX_BROJ];
	char temp_prezime[MAX_BROJ];
	int temp_godrod;
	int status = 1;
	int numbyte = 0;
	int filelen = 0; 
	char* buffer, * cbuffer;
	fseek(in, 0, SEEK_END);
	filelen = ftell(in);
	buffer = (char*)malloc(filelen+1, sizeof(char));
	if (!buffer) {
		printf("Can't allocate memory");
		return -1;
	}
	rewind(in);
	fread(buffer, sizeof(char), filelen + 1,in);
	cbuffer = buffer;
	while (strlen(cbuffer) > 0) {
		status = sscanf("%s %s %d %n", temp_ime, temp_prezime, &temp_godrod, &numbyte);
		if (!status) {
			printf("Unsupported document format");
			return -2;
		}
		DodajSortirano(head, temp_ime, temp_prezime, temp_godrod);
		cbuffer = cbuffer + numbyte;
	}
	free(buffer);
	return EXIT_SUCCESS;


}
int DodajSortirano(Pozicija head, char* ime, char* prezime, int godrod) {
	Pozicija nova_osoba = StvoriOsobu(ime, prezime, godrod);
	Pozicija temp = head->next;
	if (!temp) {
		head->next = nova_osoba;
		return EXIT_SUCCESS;
	}
	while (temp->next != NULL)
		{
		if (strcmp(prezime, temp->prezime) > 0)  //prezime>temp->prezime ---> prezime iza po abece
			{
			temp = temp->next;
			}
		else if (strcmp(prezime, temp->prezime) < 0) 
			{
			nova_osoba->next = temp;
			return EXIT_SUCCESS;
			}
		}
	temp->next = nova_osoba;
	return EXIT_SUCCESS;
	

}

int SortirajListu(Pozicija head)
{
	Pozicija temp0 = head;
	Pozicija temp = head->next;
	Pozicija temp2 = temp->next;
	while (temp != NULL) 
	{
		while (temp2 != NULL) 
		{
			if (strcmp(temp->prezime, temp2->prezime) > 0)
			{
				temp2 = temp2->next;
			}
			if (strcmp(temp->prezime, temp2->prezime) < 0) 
				{
				DodajIspred(head, temp2, temp->ime, temp->prezime, temp->god_rod);
				IzbrisiNakon(head,temp0);
				}
			if (temp2->next = NULL) {
				DodajIza(temp2, temp->ime, temp->prezime, temp->god_rod);
				IzbrisiNakon(head, temp0);
			}
		}
		temp0 = temp;
		temp = temp->next;
		temp2 = temp->next;
	}
	return EXIT_SUCCESS;
}




int main() {
	Osoba head = { .next = NULL, .ime = {0}, .prezime = {0}, .god_rod = 0 };
	FILE* in, * out;
	in = fopen("lista.txt", "r");
	out = fopen("lista_ispis.txt", "w");
	Pozicija pocetak = &head;
	int provjera, index;
	provjera = 1;
	char izbor;
	izbor = 'a';
	char ime[MAX_BROJ];
	char prezime[MAX_BROJ];
	int godrod;
	while (provjera != -1) {
		printf("Unesite izbor:\n");
		printf("A-dodaj element na pocetak\nB-printaj listu\nC-dodaj na kraj\nD-pronadi po prezimenu:\nE-Brisi element na mistu:\nF-Spremi u file\nG-Citaj iz fajla\nH-Dodaj sortirano\nS-Sortiraj listu\n X-Brisi listu, izlaz\n");
		scanf(" %c", &izbor);
		switch (izbor) {
		case 'A':
			scanf(" %s %s %d", ime, prezime, &godrod);
			DodajNaPocetak(pocetak, ime, prezime, godrod);
			break;

		case 'B':
			PrintajListu(&head);
			break;

		case 'C':
			scanf(" %s %s %d", ime, prezime, &godrod);
			DodajNaKraj(pocetak, ime, prezime, godrod);
			break;
		case 'D':
			scanf("%s", prezime);
			PronadiPrezime(&head, prezime);

		case 'E':
			printf("\n Unesite koji element zelite izbrisat:\t");
			scanf(" %d", &index);
			IzbrisiPoPoziciji(pocetak, index);
			break;
		case 'F':
			SpremiUFajl(out, &head);
			break;
		case 'G':
			CitajIzFajla(in, &head);
			break;
		case 'H':
			scanf(" %s %s %d", ime, prezime, &godrod);
			DodajSortirano(&head, ime, prezime, godrod);
			break;

		case 'X':
			BrisiListu(pocetak);
			provjera = -1;
			return provjera; 

		default:
			continue;

		}
	}

	return 0;



