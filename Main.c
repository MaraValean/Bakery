// bakery.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MaterialRepo.h"
#include "UI.h"
#include <crtdbg.h>
#include <string.h>
#include <stdio.h>


int main()
{
	// tests will not pass unless all functions are correctly implemented
	testMaterialRepo();
	testService();
	MaterialRepo* repo = createRepo(30);
	Service* serv = createService(repo);
	
	
	
	addMaterial(serv, "flour", "Carrefour", 7, 12,01,2022);
	addMaterial(serv, "eggs", "Carrefour", 5, 16, 01, 2022);
	addMaterial(serv, "flour", "Profi", 34, 12, 11, 2022);
	addMaterial(serv, "milk", "Carrefour", 5, 24, 10, 2022);
	addMaterial(serv, "chocolate", "Metro", 25, 21, 11, 2023);
	addMaterial(serv, "white chocolate", "Carrefour", 10, 12, 01, 2022);
	addMaterial(serv, "baking powder", "Profi", 5, 10, 04, 2022);
	addMaterial(serv, "sugar", "Metro", 25, 21, 11, 2023);
	addMaterial(serv, "vanilla extract", "Carrefour", 10, 12, 01, 2021);
	addMaterial(serv, "butter", "Profi", 25, 10, 04, 2021);
	
	addToUndoList(serv);

	UI* ui = createUI(serv,undo);

	startUI(ui);

	destroyUI(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}