#include "pch.h"
#include "Logic.h"
#include "DataManager.h"

int main()
{
	DataManager::Get();
	Logic::Get()->Init();

	wcin.imbue(locale("kor"));
	wcout.imbue(locale("kor"));

	DataManager::Get()->Load();
	
	while (true)
	{
		system("cls");

		Logic::Get()->Run();

		if (Logic::Get()->GetIsClose() == true)
			break;
	}

	Logic::Delete();
	DataManager::Delete();

}
