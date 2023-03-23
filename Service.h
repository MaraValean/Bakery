#pragma once
#include "MaterialRepo.h"


typedef struct
{
	MaterialRepo* repo;
	DynamicArray* undoStack;
	int undoPointer;

} Service;

/// <summary>
/// creates the service
/// </summary>
/// <param name="r">pointer to the repo</param>
/// <returns>a pointer to the created service</returns>
Service* createService(MaterialRepo* r);

/// <summary>
/// destroys the service
/// </summary>
/// <param name="s">pointer to the service</param>
void destroyService(Service* s);

/// <summary>
/// Adds a Material to the repository of Materials.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "name">A string, the name of the Material.</param>
/// <param name = "supplier">A string, the Material's supplier.</param>
/// <param name = "quantity">int, the quantity of the Material.</param>
/// <returns>1 - if the planet was sucessfully added; 0 - if the planet could not be added, as another material with the same name already exists.</returns>
int addMaterial(Service* s, char* name, char* supplier, int quantity, int day, int month, int year);

MaterialRepo* getRepo(Service* s);

/// <summary>
/// Searches for the planets containing a given type.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "symbols">A string, the searched type; "null" - for all the planets.</param>
/// <returns>A pointer to a repository of planets, that have the given type.</returns>
MaterialRepo* filterByType(Service* s, char type[]);

/// <summary>
/// Updates an existing material with the new data given by the user
/// </summary>
/// <param name="s">pointer to the service</param> 
/// <param name="name">new name</param>
/// <param name="supplier">new supplier</param>
/// <param name="quantity">new quantity</param>
/// <param name="day">new expiration day</param>
/// <param name="month">new month</param>
/// <param name="year">new year</param>
/// <param name="index">the index of the elem to be updated</param>
/// <returns>1 if the material was updated, 0 otherwise</returns>
int updateMaterial(Service* s, char* name, char* supplier, int quantity, int day, int month, int year, int index);

/// <summary>
/// Deletes an existing material 
/// </summary>
/// <param name="s">pointer to the service</param> 
/// /// <returns>1 if the material was deleted, 0 otherwise</returns>
int deleteMaterial(Service* s, int index);

/// <summary>
/// creates a new repo with the materials which contain the given string
/// </summary>
/// <param name="exp">pointer to the repo with the expired materials</param>
/// <param name="string">the given string</param>
/// <returns>a repo </returns>
MaterialRepo* filterByStringService(MaterialRepo* exp, char* string);

/// <summary>
///  creates a new repo with the materials which are expired
/// <param name="s">pointer to service</param>
/// <param name="day"></param>
/// <param name="month"></param>
/// <param name="year"></param>
/// <returns>a new repo</returns>
MaterialRepo* filterExpired(Service* s, int day, int month, int year);

/// <summary>
/// creates a new repo with the materials which have the given supplier
/// </summary>
/// <param name="shortSupply">pointer to the short supply repo</param>
/// <param name="string">name of the supplier</param>
/// <returns>new repo</returns>
MaterialRepo* filterBySupplier(MaterialRepo* shortSupply, char* string);

/// <summary>
/// creates a new repo with the materials which are in short supply
/// </summary>
/// <param name="s">pointer to the service</param>
/// <param name="quantity"></param>
/// <returns>a new repo</returns>
MaterialRepo* filterShortSupply(Service* s, int quantity);

/// <summary>
/// sorts the repo by quantity ascending
/// </summary>
/// <param name="repo"></param>
/// <returns>a new repo</returns>
MaterialRepo* sortRepoByQuantity(MaterialRepo* repo);

void addToUndoList(Service* serv);

/// <summary>
/// This function undoes the last operation
/// </summary>
/// <returns> 1 if the operation was successfully undone, else 0</returns>
int undo(Service* serv);

/// <summary>
/// This function redoes the last operation
/// </summary>
/// <returns> 1 if the operation was successfully redone, else 0</returns>
int redo(Service* serv);

/// <summary>
///contains all the test functions for the service
/// <summary>
void testService();