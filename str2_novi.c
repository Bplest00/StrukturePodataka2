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

// DODAJ ISPRED + IZBRISI ISPRED + PRONADI PO PREZIMENU + UPISUJE LISTU U DATOTEKU + CITA LISTU + PRINTA LISTU
int BrisiListu(Pozicija head) { 
	Pozicija temp = head->next;
	Pozicija temp2 = NULL;
	if (!temp) {
		return EXIT_SUCCESS;
	}
	while (temp!= NULL) {
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




int main() {
	Osoba head = { .next = NULL, .ime = {0}, .prezime = {0}, .god_rod = 0 }; // definitivno prepisa s primjera, nisam dosad ovako strukturu inicializira
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
		printf("A-dodaj element na pocetak\nB-printaj listu\nC-dodaj na kraj\nD-pronadi po prezimenu:\nE-Brisi element na mistu:\nF-Brisi listu, izlaz\n");
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
			BrisiListu(pocetak);
			provjera = -1;
			return provjera; //neznam jeli se ovako moze koristit return

		default:
			continue;

		}
	}

	return 0;
}