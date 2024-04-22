#pragma once
#include "cphonelist.h"
class CPhoneIterName
{
public: 
	CPhoneIterName(CPhoneList& m); // elemeket tartalmazó osztály címe
	~CPhoneIterName(); Record * begin(); // első elem címe, hiba esetén nullptr,
	Record * prev(); // előző elem címe, hiba esetén nullptr
	Record * next(); // következő elem címe, hiba esetén nullptr
	Record * end(); // utolsó elem, hiba nullptr
	int size(); // listában levő elemek száma
	Record * search(const char * key); // első egyező name, különben nullptr vagy ha üres a tömb, // bejárás begin/end/next/prev fv. segítségével! 
	Record* operator++(); // következő elem címe, hiba esetén nullptr
private: 
	CPhoneList* const m_cpList; // elemeket tároló tömb címe
	int m_iCurrIndex; // aktuális index a bejárás során 
	void orderNames(); //nevek rendezése
	int m_iArray[MAXLENGTH]; //rendezett
	int indexOfName(int index); //adott index "rendezett indexe"
};

