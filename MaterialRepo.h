#pragma once
#include "Material.h"
#include "DynamicArray.h"

typedef struct
{
	DynamicArray* array;
} MaterialRepo;

/// <summary>
/// Creates a MaterialRepo.
/// </summary>
MaterialRepo* createRepo(int maxLength);

/// <summary>
/// Destroys a given Material repository. The memory is freed.
/// </summary>
void destroyRepo(MaterialRepo* v);

/// <summary>
/// Finds theMaterial with the given name.
/// </summary>
/// <param name="v">Pointer to the MaterialRepo.</param>
/// <param name = "name">A string, the name to search for.</param>
/// <returns>pos - the position on which the material with the given name is in theMaterialRepo; -1 - if the Material does not exist.</returns>
int find (MaterialRepo* v, char name[], char supplier[], int day, int month, int year);

/*
	Adds a Material to the repository of Material.
	Input:	- v - pointer to the MaterialRepo
			- p - Material
	Output: 1 - if the Material was sucessfully added
			0 - if the Material could not be added, as anotherMaterial with the same name,supplier and expriration date already exists in the MaterialRepo.
*/
int add(MaterialRepo* v, Material* p);

/// <summary>
///  the length of the repo
/// </summary>
/// <param name="v">a pointer to the repo</param>
/// <returns>an integer, the length</returns>
int getLength(MaterialRepo* v);


/*
	Returns the material on the given position in the material vector.
	Input:	v - the material repository;
			pos - integer, the position;
	Output: the material on the given potision, or an "empty" material.
*/
Material* getMaterialOnPos(MaterialRepo* v, int pos);

/// <summary>
/// updates an existing material with another consisying of new attributes
/// </summary>
/// <param name="v">pointer to the repo</param>
/// <param name="index">the position of the elem in the repo</param>
/// <param name="p">the new material</param>
/// <returns>1 if the material was updated, 0 otherwise</returns>
int update(MaterialRepo* v, int index, Material* p);

/// <summary>
/// deletes an existing material 
/// </summary>
/// <param name="v">pointer to the repo</param>
/// <param name="index">the position of the elem in the repo</param>
/// <returns>1 if the material was deleted, 0 otherwise</returns>
int delete(MaterialRepo* v, int index);

MaterialRepo* copyRepo(MaterialRepo* sourceRepo);



/// <summary>
/// includes all the test functions for the repo
/// </summary>
void testsMaterialRepo();

