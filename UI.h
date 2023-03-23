#pragma once
#include "Service.h"
#include "MaterialRepo.h"
#define _CRT_SECURE_NO_WARNINGS
typedef struct
{
	Service* serv;
	

}UI;

UI* createUI(Service* s);
void destroyUI(UI* ui);

void startUI(UI* ui);