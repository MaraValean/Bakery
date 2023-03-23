#pragma once
//Each Material used in the bakery must have: a name, a supplier, a quantity and the expiration date
typedef struct
{
	char* name;
	char* supplier;
	int quantity;
	int day;
	int month;
	int year;
	

} Material;

Material* createMaterial(char* name, char* supplier, int quantity, int day, int month, int year);

void destroyMaterial(Material* p);

Material* copyMaterial(Material* p);

char* getName(Material* p);

char* getSupplier(Material* p);

int getQuantity(Material* p);

int getDay(Material* p);

int getMonth(Material* p);

int getYear(Material* p);

void toString(Material* p, char str[]);

void setName(Material* p, char* newName);

void setQuantity(Material* p, int newQuantity);

void Assign(Material* source, Material* destination);