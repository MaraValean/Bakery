#define _CRT_SECURE_NO_WARNINGS
#include "UI.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

UI* createUI(Service* s)
{
	UI* ui = malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;
	ui->serv = s;
	return ui;
}

void destroyUI(UI* ui)
{
	if (ui == NULL)
		return;

	// first destroy the Service
	destroyService(ui->serv);
	// free the UI memory
	free(ui);
}

/*
	Prints the available menu for the problem
	Input: -
	Output: the menu is printed at the console
*/
void printMenu()
{
	printf("\n	 Welcome to ~Bread'n Bagel~ bakery\n");
	printf("1 - add a material.\n");
	printf("2 - list all materials.\n");
	printf("3 - delete a material.\n");
	printf("4 - update material.\n");
	printf("5 - filter materials past their expiration date, containing a given string (if the string is empty, all materials past their expiration date will be considered).\n");
	printf("6 _ Display all materials from a given supplier, which are in short supply sorted ascending by their quantities.\n");
	printf("7 - Undo last operation.\n");
	printf("8 - Redo last operation.\n");

	printf("0 - to exit.\n");
	//printf("**********************************************************\n");
}

/*
	Verifies if the given command is valid (is either 1, 2 or 0)
	Input: command - integer
	Output: 1 - if the command is valid
	0 - otherwise
*/
int validCommand(int command)
{
	if (command >= 0 && command <= 8)
		return 1;
	return 0;
}

/*
	Reads an integer number from the keyboard. Asks for number while read errors encoutered.
	Input: the message to be displayed when asking the user for input.
	Returns the number.
*/
int readIntegerNumber(const char* message)
{
	char s[16] = { 0 };
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		int scanf_result = scanf("%15s", s);

		r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}

int addMaterialUI(UI* ui)
{
	// read the material's data
	char name[50], supplier[50];
	int quantity = 0, day = 0, month = 0, year = 0;

	printf("Please input the name: ");
	scanf("%s", name);
	printf("Please input the supplier: ");
	scanf("%s", supplier);
	printf("Please input the quantity ");
	scanf("%d", &quantity);
	printf("Please input the expiration day: ");
	scanf("%d", &day);
	printf("Please input the month: ");
	scanf("%d", &month);
	printf("Please input the year: ");
	scanf("%d", &year);

	return addMaterial(ui->serv, name, supplier, quantity,day,month,year);
}
void listAllMaterials(UI* ui)
{
	if (ui == NULL)
		return;
	MaterialRepo* repo = getRepo(ui->serv);
	if (repo == NULL)
		return;

	for (int i = 0; i < getLength(repo); i++)
	{
		Material* material = getMaterialOnPos(repo, i);
		char materialString[200];
		toString(material, materialString);
		printf("%d. %s\n",i, materialString);
	}
}

int deleteMaterialUi(UI* ui)
{
	int index = readIntegerNumber("Please enter the index of the element you want to delete: ");
	return deleteMaterial(ui->serv, index);
}

int updateMaterialUi(UI* ui)
	{
	char name[50], supplier[50];
	int quantity, day, month, year;
	int index = readIntegerNumber("Please input the index of the element you want to update: ");
	printf("Please enter the name of the material: ");
	scanf("%s", name);
	printf("Please enter the new supplier: ");
	scanf("%s", supplier);
	quantity = readIntegerNumber("Please input the new quantity of the material: ");
	day = readIntegerNumber("Please input the new day of expiration of the material: ");
	month = readIntegerNumber("Please input the new month of the material: ");
	year = readIntegerNumber("Please input the new year of the material: ");
	return updateMaterial(ui->serv, name, supplier,quantity,day,month,year,index);
}

void filterExpiredWithString(UI* ui)
{
	char word[50], materialString[1000];
	int day, month, year;
	day = readIntegerNumber("Please input the current day : ");
	month = readIntegerNumber("Please input the  month: ");
	year = readIntegerNumber("Please input the year: ");
	printf("Insert the string to look for into the materials: ");
	scanf("%s", word);
	MaterialRepo* exp = filterExpired(ui->serv, day, month, year);
	if (strcmp(word, "null") == 0)
	{
		for (int i = 0; i < exp->array->length; i++)
		{
			toString(exp->array->elements[i], materialString);
			printf("%d. %s\n", i, materialString);
		}

	}
	else
	{
		MaterialRepo* filtered = filterByStringService(exp, word);
		for (int i = 0; i < filtered->array->length; i++)
		{
			toString(filtered->array->elements[i], materialString);
			printf("%d. %s\n", i, materialString);
		}

		destroyRepo(filtered);
		
	}
	destroyRepo(exp);
	

}

void filterShortSupplier(UI* ui)
{
	char word[50], materialString[1000];
	int quantity;
	quantity = readIntegerNumber("Please input the quantity : ");
	printf("Please enter the supplier: ");
	scanf("%s", word);
	MaterialRepo* shortSupply = filterShortSupply(ui->serv, quantity);
	MaterialRepo* supplier = filterBySupplier(shortSupply, word);
	MaterialRepo* sorted = sortRepoByQuantity(supplier);
	for (int i = 0; i < sorted->array->length; i++)
	{
		toString(sorted->array->elements[i], materialString);
		printf("%d. %s\n", i, materialString);
	}

	
	destroyRepo(supplier);
	destroyRepo(shortSupply);
	destroyRepo(sorted);


}

int undoUI(UI* ui)
{
	return undo(ui->serv);
}

int redoUI(UI* ui)
{
	return redo(ui->serv);
}

void startUI(UI* ui)
{
	while (1)
	{
		printMenu();
		int command = readIntegerNumber("	Input command: ");
		while (validCommand(command) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("	Input command: ");
		}
		if (command == 0)
			break;
		switch (command)
		{
		case 1:
		{
			int res = addMaterialUI(ui);
			if (res == 1)
			{
				printf("Material successfully added.\n");
				addToUndoList(ui->serv);

			}
			else if (res == 2)
			{
				printf("That material already existed, so the quantity was added to the existing one.\n");
				addToUndoList(ui->serv);
			}
			else
				printf("Error! Material could not be added, as there is another Material with the same name!\n");
			break;
		}
		case 2:
		{
			listAllMaterials(ui);
			break;
		}
		case 3:
		{
			int res = deleteMaterialUi(ui);
			if (res == 1) {
				printf("Material successfully deleted.\n");
				addToUndoList(ui->serv);
			}
			else
				printf("Error! Material could not be deleted (element with that index doesn't exist)\n");
			break;
		}
		case 4:
		{
			int res = updateMaterialUi(ui);
			if (res == 1)
			{
				printf("Material successfully updated.\n");
				addToUndoList(ui->serv);
			}
			else
				printf("Error! Material could not be updated\n");
			break;

		}

		case 5:
		{
			filterExpiredWithString(ui);
			break;
		}
		case 6:
		{
			filterShortSupplier(ui);
			break;
		}
		case 7:
		{

			int undoResult = undoUI(ui);
			if (undoResult == 1)
			{
				printf("Operation successfully undone ! \n");
			}
			else
			{
				printf("Operation cannot be undone ! \n");
			}
			break;
		}
		case 8:
		{ int redoResult = redoUI(ui);
		if (redoResult == 1)
		{
			printf("Operation successfully redone ! \n");
		}
		else
		{
			printf("Operation cannot be redone ! \n");
			break;
		}


		}
		}
	}

}
