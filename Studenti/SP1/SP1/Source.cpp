#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROGRAM_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define max_br_bodova 80
 

typedef struct {
	char ime[MAX_LINE];
	char prez[MAX_LINE];
	float rez;
}Student;

int countStudentsFromFile(char* filename);
int ispisStudenata(int count, char* filename , Student* studenti);

int main(void) {
	char filename[MAX_FILE_NAME] = { 0 };
	int count = 0;

	Student* studenti = NULL;

	printf("Unesite ime .txt dokumenta: ");
	scanf(" %s", &filename);					//samo upisat ime datoteke bez .txt
	strcat(filename, ".txt");

	count = countStudentsFromFile(filename);
	studenti = (Student*)malloc(count * sizeof(Student));
	
	if (studenti == NULL){
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");       //dodana provjera alociranja
		return PROGRAM_ERROR;
	}
	
	if (count != PROGRAM_ERROR) {
	printf("Broj studenata u datoteci %s je %d.\r\n", filename, count);
	}

	ispisStudenata(count, filename, studenti);

	return EXIT_SUCCESS;
}

int countStudentsFromFile(char* filename) {
	FILE* fp = NULL;
	int count = 0;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(filename, "r");
	if (NULL == fp) {
		printf("Doslo je do pogreske, dokument %s se nije otvorio!\r\n", filename);
		return PROGRAM_ERROR;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		if (strcmp("\n", buffer) != 0) {
			count++;							//sad broji dbr
		}
	}
	fclose(fp);
	return count;
}

int ispisStudenata(int count, char* filename, Student* studenti) {
	FILE* fp = NULL;
	int i=0;

	fp = fopen(filename, "r");
	if (NULL == fp) {
		printf("Doslo je do pogreske, dokument %s se nije otvorio!\r\n", filename);
		return PROGRAM_ERROR;
	}

	printf("\nIme\t\tPrezime\t\tRezultat\t\tPostotak prolaznost(max broj bodova 80)\n");
	while (!feof(fp)) {
		for (i = 0; i < count; i++) {
			fscanf(fp, "%s %s %f", studenti[i].ime, studenti[i].prez, &studenti[i].rez);
			printf("%s\t\t%s\t\t%d\t\t%f\n", studenti[i].ime, studenti[i].prez, int(studenti[i].rez), float((studenti[i].rez/max_br_bodova)*100));
		}							//skenira iz filea i ispisuje ime, prezime, broj bodova i postotnu rijesenost
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
