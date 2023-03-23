#include "Service.h"
#include <stdlib.h>
#include <assert.h>


	Service* createService(MaterialRepo* r)
	{
		Service* s = malloc(sizeof(Service));
		if (s == NULL)
			return NULL;
		s->repo = r;
		s->undoStack = createDynamicArray(10, destroyRepo, copyRepo);
		addElement(s->undoStack, copyRepo(s->repo));
		s->undoPointer = -1;
		return s;
	}

	void destroyService(Service* s)
	{
		if (s == NULL)
			return 0;

		// first destroy the repository inside
		destroyRepo(s->repo);
		destroyDynamicArray(s->undoStack);
		// then free the memory
		free(s);
	}

	int addMaterial(Service* s, char* name, char* supplier, int quantity, int day, int month, int year)
	{	
		Material* p = createMaterial(name, supplier, quantity, day, month, year);
		int ok = add(s->repo, p);
		if (ok == 0 || ok ==2)
			destroyMaterial(p);
		return ok;
	}

	MaterialRepo* getRepo(Service* s)
	{
		return s->repo;
	}
	
	MaterialRepo* filterByStringService(MaterialRepo* exp, char* string)
	{
		MaterialRepo* filtered = createRepo(10);
		for (int i = 0; i < exp->array->length; i++)
			if (strstr(getName(exp->array->elements[i]), string) != NULL || strstr(getSupplier(exp->array->elements[i]), string) != NULL)
			{
				add(filtered, copyMaterial(exp->array->elements[i]));
			}
		return filtered;
	}
	
	MaterialRepo* filterBySupplier(MaterialRepo* shortSupply, char* string)
	{
		MaterialRepo* supplier = createRepo(10);
		for (int i = 0; i < shortSupply->array->length; i++)
			if (strcmp(getSupplier(shortSupply->array->elements[i]), string) ==0)
			{
				add(supplier, copyMaterial(shortSupply->array->elements[i]));
			}
		return supplier;
	}
	

	MaterialRepo* filterShortSupply(Service* s, int quantity)
	{
		MaterialRepo* shortSupply = createRepo(10);
		for (int i = 0; i < s->repo->array->length; i++)
			if (getQuantity(s->repo->array->elements[i]) < quantity)
				add(shortSupply,copyMaterial( s->repo->array->elements[i]));
			
		return shortSupply;

	}

	MaterialRepo* sortRepoByQuantity(MaterialRepo* repo)
	{
		MaterialRepo* sorted = createRepo(10);
		for (int i = 0; i < repo->array->length; i++)
			add(sorted,copyMaterial( repo->array->elements[i]));
		for (int i = 0; i < repo->array->length; i++)
			for(int j = i+1; j < repo->array->length; j++)
				if (getQuantity(sorted->array->elements[i]) > getQuantity(sorted->array->elements[j]) )
				{
					void* a = sorted->array->elements[i];
					sorted->array->elements[i] = sorted->array->elements[j];
					sorted->array->elements[j] = a;
				}
		return sorted;
	}

	MaterialRepo* filterExpired(Service* s, int day, int month,int year)
	{
		MaterialRepo* exp = createRepo(10);
		for (int i = 0; i < s->repo->array->length; i++)
			if (getYear(s->repo->array->elements[i]) < year)
				add(exp, copyMaterial(s->repo->array->elements[i]));
			else if(getYear(s->repo->array->elements[i]) == year && getMonth(s->repo->array->elements[i]) < month)
				add(exp, copyMaterial( s->repo->array->elements[i]));
			else if(getYear(s->repo->array->elements[i]) == year && getMonth(s->repo->array->elements[i]) == month && getDay(s->repo->array->elements[i]) < day)
				add(exp, copyMaterial(s->repo->array->elements[i]));
		return exp;
	}
	
	int updateMaterial(Service* s, char* name, char* supplier,int quantity,int day, int month,int year,int index)
	{
		Material* p = createMaterial(name, supplier, quantity, day, month, year);
		int ok = update(s->repo, index, p);
		if (ok == 0 )
			destroyMaterial(p);
		return ok;
	}

	int deleteMaterial(Service* s, int index)
	{
		return delete(s->repo, index);
	}


	void correctUndoPointer(Service* serv)
	{
		while (getArrayLength(serv->undoStack) - 2 != serv->undoPointer)
			deleteElement(serv->undoStack, getArrayLength(serv->undoStack) - 1);
	}

	void addToUndoList(Service* serv)
	{
		correctUndoPointer(serv);
		addElement(serv->undoStack, copyRepo(serv->repo));
		serv->undoPointer++;
	}

	int undo(Service* serv)
	{
		int undoStackLength = getArrayLength(serv->undoStack);
		if (undoStackLength <= 1 || serv->undoPointer < 0)
		{
			return 0;
		}
		else
		{
			destroyRepo(serv->repo);
			serv->repo = copyRepo(getElementAtIndex(serv->undoStack, serv->undoPointer));
			serv->undoPointer--;
			return 1;
		}
	}

	int redo(Service* serv)
	{
		int undoStackLength = getArrayLength(serv->undoStack);
		if (serv->undoPointer == undoStackLength - 2 || serv->undoPointer < -1)
		{
			return 0;
		}
		else
		{
			destroyRepo(serv->repo);
			serv->repo = copyRepo(getElementAtIndex(serv->undoStack, serv->undoPointer + 2));
			serv->undoPointer++;
			return 1;
		}
	}




	//tests


	void testAdd()
	{
		MaterialRepo* r = createRepo(3);
		Service* s = createService(r);
		

		assert(addMaterial(s, "milk", "Profi", 4, 1, 2, 2022) == 1);
		assert(getLength(r) == 1);

		assert(addMaterial(s, "milk", "Profi", 4, 1, 2, 2022) == 2);

		destroyService(s);
	
	}


	void testDelete()
	{
		MaterialRepo* r = createRepo(3);
		Service* s = createService(r);


		assert(addMaterial(s, "milk", "Profi", 4, 1, 2, 2022) == 1);
		assert(getLength(r) == 1);

		assert(deleteMaterial(s, 0) == 1);

		assert(deleteMaterial(s, 0) == 0);
		destroyService(s);

	}
	
	void testUpdate()
	{
		MaterialRepo* r = createRepo(3);
		Service* s = createService(r);


		assert(addMaterial(s, "milk", "Profi", 4, 1, 2, 2022) == 1);
		assert(getLength(r) == 1);
        
		assert(updateMaterial(s, "cocoa", "Profi", 4, 1, 2, 2022,0) == 1);

		assert(updateMaterial(s, "cocoa", "Profi", 4, 1, 2, 2022, 5) == 0);

		destroyService(s);

	}
	
	void testFilterExpired()
	{
		MaterialRepo* r = createRepo(3);
		Service* s = createService(r);


		assert(addMaterial(s, "milk", "Profi", 4, 1, 2, 2022) == 1);
		assert(getLength(r) == 1);
		
		assert( addMaterial(s, "cocoa", "Profi", 4, 1, 2, 2023 ) == 1);

		MaterialRepo* exp = filterExpired(s, 5, 12, 2022);
		assert(getLength(exp) == 1);

		MaterialRepo* exp2 = filterExpired(s, 5, 12, 2027);
		assert(getLength(exp2) == 2);

		MaterialRepo* exp3 = filterExpired(s, 5, 12, 2020);
		assert(getLength(exp3) == 0);

		destroyService(s);
		destroyRepo(exp);
		destroyRepo(exp2);
		destroyRepo(exp3);
	}

	void testFilterByStringService()
	{
		MaterialRepo* r = createRepo(3);
		Service* s = createService(r);


		assert(addMaterial(s, "milk", "Profi", 4, 1, 2, 2022) == 1);
		assert(getLength(r) == 1);

		assert(addMaterial(s, "cocoa", "Profi", 4, 1, 2, 2023) == 1);

		MaterialRepo* exp = filterExpired(s, 5, 12, 2022);
		assert(getLength(exp) == 1);

		MaterialRepo* filtered = filterByStringService(exp, "oa");
		assert(getLength(filtered) == 0);

		MaterialRepo* filtered2 = filterByStringService(exp, "lk");
		assert(getLength(filtered2) == 1);

		destroyRepo(exp);
		destroyRepo(filtered);
		destroyRepo(filtered2);
		destroyService(s);
	}

	void testUndo()
	{
		MaterialRepo* r = createRepo(3);
		Service* s = createService(r);

		assert(undo(s) == 0);
		assert(addMaterial(s, "milk", "Profi", 4, 1, 2, 2022) == 1);
		addToUndoList(s);
		assert(getLength(r) == 1);


		assert(addMaterial(s, "cocoa", "Kaufland", 7, 1, 2, 2022) == 1);
		addToUndoList(s);

		assert(getLength(r) == 2);
		
		undo(s);
		assert(getLength(s->repo)== 1);
		
		undo(s);
		assert(getLength(s->repo) == 0);
		
		assert(undo(s) == 0);
		

	
		destroyService(s);
	}

	void testRedo()
	{
		MaterialRepo* r = createRepo(3);
		Service* s = createService(r);

		assert(undo(s) == 0);
		assert(addMaterial(s, "milk", "Profi", 4, 1, 2, 2022) == 1);
		addToUndoList(s);
		assert(getLength(r) == 1);


		assert(addMaterial(s, "cocoa", "Kaufland", 7, 1, 2, 2022) == 1);
		addToUndoList(s);

		assert(getLength(r) == 2);

		undo(s);
		assert(getLength(s->repo) == 1);

		redo(s);
		assert(getLength(s->repo) == 2);

		assert(redo(s) == 0);

		destroyService(s);
	}
	
	void testService()
	{

		printf("Starting service tests..\n");
		testAdd();
		testDelete();
		testUpdate();
		testFilterByStringService();
		testFilterExpired();
		testUndo();
		testRedo();
		printf("Tests have passed successfully!\n");
	}
