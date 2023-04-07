#include<stdio.h>//Standard Input/Output functions
#include<conio.h>
#include<process.h>
#include<string.h>
#include<ctype.h>
#pragma warning(disable:4996)
typedef const char FILES[50];
typedef int ID;
typedef char Function[30];
typedef int NrCurse;
typedef int EmploymentDate;
typedef char Adress[30];
typedef char NameSurname[35];
typedef struct employee {
	ID ID;
	Function Function;
	NrCurse nrcurse;
	EmploymentDate EmploymentDate;
	Adress Adress;
	NameSurname NameSurname;
} EMPLOYEE;
void Create(const char* nume) {
	FILES* flux;
	EMPLOYEE c;

	char car;
	if ((flux = fopen(nume, "wb")) == NULL) {//Open for writing in binary mode.
		printf("Cannot open for writing FILE %s\n", nume);
		return;
	}
	printf("Enter a record? (Y/N)");
	fflush(stdin);//sterge fluxul anterior din buffer
	scanf("%c", &car);
	while (toupper(car) == 'Y') {//converteste in majuscula
		printf("Enter ID: ");
		scanf("%d", &c.ID);
		printf("Enter the function of Emplyee: ");
		scanf("%s", &c.Function);
		printf("Enter the number of courses: ");
		scanf_s("%d", &c.nrcurse);
		printf("Enter the date of emplyment: ");
		scanf("%d", &c.EmploymentDate);
		printf("Enter Adress: ");
		scanf("%s", &c.Adress);
		printf("Enter name and surname: ");
		scanf("%s", &c.NameSurname);
		if (fwrite(&c, sizeof(EMPLOYEE), 1, flux) != 1) {
			printf("Error writing the file: %s\n", nume);
			return;
		}
		printf("Enter a record?? (Y/N)");
		fflush(stdin);
		scanf("%c", &car);
	}
	fclose(flux);
}//create
void Display(const char* nume) {
	FILES* flux;
	EMPLOYEE c;
	if ((flux = fopen(nume, "rb")) == NULL) {//Open for reading in binary mode.	
		printf("Cannot open for writing FILE %s\n", nume);
		return;
	}

	if (fread(&c, sizeof(EMPLOYEE), 1, flux) != 1)
		if (ferror(flux)) {
			printf("Error reading the file: %s\n", nume);
			return;
		}
	while (!feof(flux)) {
		if (c.ID > 0)
			printf("%4d %4d %4d %30s %30s\n ", c.ID, c.nrcurse, c.EmploymentDate, c.Adress, c.NameSurname);
		if (fread(&c, sizeof(EMPLOYEE), 1, flux) != 1)
			if (ferror(flux)) {
				printf("Error reading the file: %s\n", nume);
				return;
			}
	}
	return;

}//display
void Modify(const char* nume, ID k) {
	FILES* flux;
	EMPLOYEE c;
	int i;
	if ((flux = fopen(nume, "rb+")) == NULL) {//Open for both reading and writing in binary mode.
		printf("Cannot open for writing FILE %s\n", nume);
		return;
	}
	if (fread(&c, sizeof(EMPLOYEE), 1, flux) != 1)
		if (ferror(flux)) {
			printf("Error reading the file : % s\n", nume);
			return;
		}
	i = 1;
	while (!feof(flux)) {
		if (c.ID == k) {
			printf("Enter the function: ");
			scanf("%s", c.Function);
			printf("Enter the  number of courses: ");
			scanf("%d", c.nrcurse);
			fseek(flux, (i - 1) * sizeof(EMPLOYEE), SEEK_SET);
			if (fwrite(&c, sizeof(EMPLOYEE), 1, flux) != 1) {
				printf("Error writing to the file:%s\n", nume);
				return;
			}
			break;
		}
		if (fread(&c, sizeof(EMPLOYEE), 1, flux) != 1)
			if (ferror(flux)) {
				printf("Error reading the file: %s\n", nume);
				return;
			}
		i++;
	}
	fclose(flux);
	return;
}//Modify
void SortNameSurname(const char* nume) {
	FILES* flux;
	EMPLOYEE c[100];
	int i, j, n = 0;
	if ((flux = fopen(nume, "rb")) == NULL) {
		printf("Cannot open for writing FILE %s\n", nume);
		return;
	}

	while (fread(&c[n], sizeof(EMPLOYEE), 1, flux) == 1) {
		n++;
	}

	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (strcmp(c[i].NameSurname, c[j].NameSurname) > 0) {//compara fiecare structura din FILES
				EMPLOYEE temp = c[i];
				c[i] = c[j];
				c[j] = temp;
			}
		}
	}

	for (i = 0; i < n; i++) {
		printf("%4d %4d %4d %30s %30s\n ", c[i].ID, c[i].nrcurse, c[i].EmploymentDate, c[i].Adress, c[i].NameSurname);
	}

	fclose(flux);
}
//Sort

void Delete(const char* nume, ID k) {
	FILES* flux;
	EMPLOYEE c;
	int i;
	if ((flux = fopen(nume, "rb+")) == NULL) {
		printf("Cannot open for reading FILE: %s\n", nume);
		return;
	}
	if (fread(&c, sizeof(EMPLOYEE), 1, flux) != 1)
		if (ferror(flux)) {
			printf("Error reading the file: %s\n", nume);
			return;
		}
	i = 1;
	while (!feof(flux)) {// returneaza valori non zero daca indicat. sf. FILES e setat catre flux
		if (c.ID == k) {
			c.ID = -c.ID;
			fseek(flux, (i - 1) * sizeof(EMPLOYEE), SEEK_SET);
			if (fwrite(&c, sizeof(EMPLOYEE), 1, flux) != 1) {// bloc de date de marimea EMPLOYEE din c in flux
				printf("Error writing to the file: %s\n", nume);
				return;
			}
			break;
		}
		if (fread(&c, sizeof(EMPLOYEE), 1, flux) != 1)
			if (ferror(flux)) {
				printf("Error reading the file: %s\n", nume);
				return;
			}
		i++;
	}
	fclose(flux);
	return;
}//deleting





