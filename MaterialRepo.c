#define _CRT_SECURE_NO_WARNINGS
#include "MaterialRepo.h"
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include <stdio.h>
#include <assert.h>

MaterialRepo* createRepo(int maxLength)
{
	MaterialRepo* v =(MaterialRepo*) malloc(sizeof(MaterialRepo));
	if (v == NULL)
		return NULL;

	v->array = createDynamicArray(maxLength,destroyMaterial,copyMaterial);
	if (v->array == NULL)
		return NULL;

	return v;
}

void destroyRepo(MaterialRepo* v)
{
	if (v == NULL)
		return 0;

	
	// destroy all the materials in the repository
	destroyDynamicArray(v->array);
	v->array = NULL;

	free(v);
}

int find(MaterialRepo* v, char name[],char supplier[],int day,int month,int year)
{
	if (v == NULL)
		return -1;
	
	for (int i = 0; i < v->array->length; i++) {
		if (strcmp(getName(v->array->elements[i]), name) == 0 && strcmp(getSupplier(v->array->elements[i]), supplier) == 0
			&& getDay(v->array->elements[i]) == day && getMonth(v->array->elements[i]) == month && getYear(v->array->elements[i]) == year) {
			return i;
		}
	}
		return -1;
}

int add(MaterialRepo* v, Material* p)
{
	int index = find(v, p->name, p->supplier, p->day, p->month, p->year);
	if (index == -1)
	{
		
		addElement(v->array, p);
		return 1;
	}
	else
	{
		setQuantity(v->array->elements[index], getQuantity(v->array->elements[index]) + p->quantity);
		//destroyMaterial(p);
		return 2;
	}

	return 0;
}

int getLength(MaterialRepo* v)
{
	return v->array->length;
}

Material* getMaterialOnPos(MaterialRepo* v, int pos)
{
	if (v == NULL)
		return NULL;
	if (pos < 0 || pos >= v->array->length)
		return NULL;
	return v->array->elements[pos];
}

int update(MaterialRepo* v, int index, Material* p)
{
	int pos = find(v, getName(p), getSupplier(p), getDay(p), getMonth(p), getYear(p));
	if (index != -1 && pos == -1 && strlen(getName(p)) && strlen(getSupplier(p)) && index>=0 && index<v->array->length)
	{
		//destroyMaterial(v->array->elements[index]);
		deleteElement(v->array, index);

		//v->array->elements[index] = p;
		addElement(v->array, p);
		return 1;
	}
	return 0;
}

int delete(MaterialRepo* v, int index)
{
	if (index < v->array->length && index >= 0)
	{   /*
		destroyMaterial(v->array->elements[index]);
		for (int i = index; i < v->array->length; i++)
			v->array->elements[i] = v->array->elements[i + 1];
		v->array->length--;
		*/
		deleteElement(v->array, index);
	
		
		return 1;
	}
	return 0;
}

MaterialRepo* copyRepo(MaterialRepo* sourceRepo)
{
	MaterialRepo* newRepo = createRepo(sourceRepo->array->length);
	destroyDynamicArray(newRepo->array);
	newRepo->array = copyDynamicArray(sourceRepo->array);
	return newRepo;
}




// tests


void TestGetLength()
{
	MaterialRepo* v = createRepo(3);

	Material* p = createMaterial("milk", "Profi", 4, 1, 2, 2022);
	assert(add(v, p) == 1);
	assert(getLength(v) == 1);

	destroyRepo(v);
}

void testMaterialAdd()
{
	MaterialRepo* v = createRepo(3);

	Material* p = createMaterial("milk", "Profi", 4, 1,2,2022);
	assert(add(v, p) == 1);
	assert(getLength(v) == 1);

	// now try to add the same Material again -> add must return 0 (! the check must be implemented in the add function)

	assert(add(v, p) == 2);

	// destroy the test repository
	destroyRepo(v);
}
 

 
void testMaterialDelete()
{
	MaterialRepo* v = createRepo(3);
	
	Material* p = createMaterial("milk", "Profi", 4, 1, 2, 2022);
	assert(add(v, p) == 1);
	assert(getLength(v) == 1);
 
	assert(delete(v, 0)==1);
	assert(getLength(v) == 0);

	assert(delete(v, 1) == 0);
	destroyRepo(v);
	
}

void testMaterialUpdate()
{
	MaterialRepo* v = createRepo(3);


	Material* p = createMaterial("milk", "Profi", 4, 1, 2, 2022);
	assert(add(v, p) == 1);
	assert(getLength(v) == 1);
    
	Material* n = createMaterial("cocoa", "Profi", 4, 1, 2, 2022);
	assert(update(v, 0, n) == 1);

	assert(update(v, 3, n) == 0);
	destroyRepo(v);
}

void testFind()
{
	MaterialRepo* v = createRepo(3);


	Material* p = createMaterial("milk", "Profi", 4, 1, 2, 2022);
	assert(add(v, p) == 1);
	assert(getLength(v) == 1);

	assert(find(v, "milk", "Profi", 1, 2, 2022) == 0);

	assert(find(v, "blabla", "Profi", 1, 2, 2022) == -1);

	destroyRepo(v);
}

void testMaterialRepo()
{
	printf("Starting repo tests..\n");
	TestGetLength();
	testMaterialAdd();
	testMaterialDelete();
	testMaterialUpdate();
	testFind();
	printf("Tests have passed successfully!\n");
}