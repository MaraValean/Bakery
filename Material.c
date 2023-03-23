#define _CRT_SECURE_NO_WARNINGS
#include "Material.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



Material* createMaterial(char* name, char* supplier, int quantity, int day, int month, int year)
{
	Material* p = malloc(sizeof(Material));
	if (p == NULL)
		return NULL;
	p->name = malloc(sizeof(char) * (strlen(name) + 1));
	if (p->name != NULL)
		strcpy(p->name, name);
	p->supplier = malloc(sizeof(char) * (strlen(supplier) + 1));
	if (p->supplier != NULL)
		strcpy(p->supplier, supplier);

	p->quantity = quantity;
	p->day = day;
	p->month = month;
	p->year = year;
	return p;
   
}

void destroyMaterial(Material* p)
{
	if (p == NULL)
		return;

	// free the memory which was allocated for the component fields
	
	free(p->name);
	free(p->supplier);
	

	// free the memory which was allocated for the planet structure
	free(p);
	//p = NULL;
}

Material* copyMaterial(Material* p)
{
	if (p == NULL) {
		return NULL;
	}
	Material* p1 = createMaterial(p->name, p->supplier, p->quantity, p->day,p->month,p->year);
	return p1;
}


char* getName(Material* p)
{
	if (p == NULL)
		return NULL;

	return p->name;
}

char* getSupplier(Material* p)
{
	if (p == NULL)
		return NULL;

	return p->supplier;

}

int getQuantity(Material* p)
{
	if (p == NULL)
		return -1;
	return p->quantity;
}

int getDay(Material* p)
{
	if (p == NULL)
		return -1;
	return p->day;
}

int getMonth(Material* p)
{
	if (p == NULL)
		return -1;
	return p->month;
}

int getYear(Material* p)
{
	if (p == NULL)
		return -1;
	return p->year;
}

void toString(Material* p, char str[])
{
	if (p == NULL)
		return;
	sprintf(str, "Material %s is supplied by %s ,its quantity is  %d and its expriration date is %d - %d -%d ", p->name, p->supplier, p->quantity,p->day,p->month,p->year);
}

void setName(Material* p, char* newName)
{
	if (p == NULL)
		return NULL;
	strcpy(p->name,newName);

}

void setQuantity(Material* p, int newQuantity)
{
	if (p == NULL)
		return NULL;
	p->quantity = newQuantity;
}

void Assign(Material* source, Material* destination)
{
	if (source == NULL)
		return NULL;
	if (destination == NULL)
		return NULL;
	strcpy(destination->name, source->name);
	strcpy(destination->supplier, source->supplier);
	destination->quantity = source->quantity;
	destination->day = source->day;
	destination->month = source->month;
	destination->year = source->year;
}