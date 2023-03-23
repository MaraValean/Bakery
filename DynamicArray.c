#include "DynamicArray.h"
#include "Material.h"
#include <stdlib.h>
#include <stdio.h>


DynamicArray* createDynamicArray(int capacity, DestroyElementFunction destroyFunction, CopyElementFunction copyFunction)
{
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (arr == NULL) {
        return NULL;
    }

    arr->capacity = capacity;
    arr->length = 0;
    arr->elements = (TElem*)malloc(sizeof(TElem) * capacity);
    if (arr->elements == NULL) {
        return NULL;
    }
    arr->destroyFunction = destroyFunction;
    arr->copyFunction = copyFunction;

    return arr;
}

void destroyDynamicArray(DynamicArray* arr)
{
    if (arr == NULL) {
        return;
    }

    for (int i = 0; i < arr->length; i++) {
        arr->destroyFunction(arr->elements[i]);
    }
    free(arr->elements);
    arr->elements = NULL;

    free(arr);
    arr = NULL;
}

void resize(DynamicArray* arr)
{
    if (arr == NULL) {
        return;
    }

    arr->capacity *= 2;
    void** auxArr = realloc(arr->elements, sizeof(void*) * arr->capacity);
    if (auxArr == NULL) {
        return;
    }
    arr->elements = auxArr;
}

void addElement(DynamicArray* arr, TElem element)
{
    if (arr == NULL) {
        return;
    }
    if (arr->elements == NULL) {
        return;
    }
    if (arr->length == arr->capacity) {
        resize(arr);
    }
    arr->elements[arr->length] = element;
    arr->length++;
}

void deleteElement(DynamicArray* arr, int position)
{
    if (arr == NULL) {
        return;
    }
    if (arr->elements == NULL) {
        return;
    }
    if (position < 0 || position >= arr->length) {
        return;
    }
    arr->destroyFunction(arr->elements[position]);
    for (int i = position; i < arr->length - 1; i++) {
        arr->elements[i] = *(arr->elements + i + 1);
    }
    arr->length--;
}

void* getElementAtIndex(DynamicArray* arr, int index)
{
    if (arr == NULL)
    {
        return NULL;
    }

    int count = getArrayLength(arr);
    if (index < 0 || index >= count)
    {
        return NULL;
    }

    return arr->elements[index];
}

int getArrayLength(DynamicArray* arr)
{
    if (arr == NULL)
    {
        return -1;
    }

    return arr->length;
}

TElem* getArrayElements(DynamicArray* arr)
{
    if (arr == NULL)
    {
        return NULL;
    }
    if (arr->elements == NULL)
    {
        return NULL;
    }
    return arr->elements;
}

DynamicArray* copyDynamicArray(DynamicArray* arr)
{
    DynamicArray* newArr = createDynamicArray(arr->capacity, arr->destroyFunction, arr->copyFunction);
    for (int i = 0; i < arr->length; i++)
    {
        addElement(newArr, arr->copyFunction(getElementAtIndex(arr, i)));
    }
    return newArr;
}

