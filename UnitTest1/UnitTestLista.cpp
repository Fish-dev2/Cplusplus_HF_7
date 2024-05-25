#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>
#include <iostream>
#include <string>


	#include "CPhoneList.h"
	#include "CPhoneIterName.h"


	

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



#define ARE_EQUAL(expVal, actVal) Assert::AreEqual(expVal, actVal, L"-", LINE_INFO())
#define ARE_EQUALSTR(expVal, actVal) Assert::AreEqual( (const char*)expVal, (const char*)actVal, L"-", LINE_INFO())
#define ARE_EQUALPTR(expVal, actVal) Assert::AreEqual( (char *) expVal, (char*)actVal, L"-", LINE_INFO())
#define WRITE(s) Logger::WriteMessage((const char*)s)


/*******************

TESZTHEZ BE KELL ÁLLÍTANI! -> ppt-phonelist_test.h -> testadatok generálása miatt
TESTITEMS -> 10 !!!!!
MAXLENGTH -> 10 !!!!! 

*******************/
#define TESTITEMS 10
#define BUFSIZE 256

#if MAXLENGTH != 10
#error MAXLENGTH nem 10!
#endif


namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TM_Empty)
		{
			try {
				WRITE("\n\t** TM_Empty**");

				CPhoneList ListName;
				CPhoneIterName IterName(ListName);

				WRITE("** IterName empty **");
				Assert::IsTrue(IterName.begin() == nullptr);
				Assert::IsTrue(IterName.end() == nullptr);
				Assert::IsTrue(IterName.prev() == nullptr);
				Assert::IsTrue(IterName.next() == nullptr);
				Assert::IsTrue(IterName.size() == 0);
				Assert::IsTrue(IterName.search("alma") == nullptr);
				Assert::IsTrue(IterName.search(nullptr) == nullptr);

				//Assert::IsTrue(IterName++ == nullptr);

				Assert::IsTrue(++IterName == nullptr);

				WRITE("\t** done **");
			}
			catch (...) {WRITE("** catch (...) **"); Assert::IsTrue(false);}
		}


		TEST_METHOD(TM_IterName)
		{
			try {

				WRITE("\n\t** TM_IterName **");
				int i;
				Record* pRec;
				Record Rec;
				char s1[BUFSIZE];
				char s2[BUFSIZE];
				char s3[] = "Ilyen név biztos nincs";

				CPhoneList List;
				
				WRITE("** Append **");
				for (i = 0; i < TESTITEMS; i++)
				{//0...9 ! 
					//Tesztadatok generálása, késõbb is így!

					//Növekvõ sorrendben generál
					//sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", i);
					//sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", i, i);
					//Csökkenõ sorrendben generál
					sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", TESTITEMS-i-1);
					sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", TESTITEMS-i-1 , TESTITEMS-i-1);


					if (i == (TESTITEMS - 2))
					{//kereséshez tesztadat
						strcpy_s(s1, BUFSIZE, Rec.name);    // név -> OK
						strcpy_s(s2, BUFSIZE, Rec.number);  // telszám keresés a névben -> NOK
					}
					//cout << endl << "Name:" << Rec.name << "\tNumber:" << Rec.number;
					WRITE(Rec.name);
					Assert::IsTrue(List.append(Rec) == 0);  //OK
				}


				List.displayname();


				//betelt, hiba!
				WRITE("** Full **");
				Assert::IsTrue(List.append(Rec) != 0);

				//Append után, csak feltöltés után lehet feladat szerint
				//Ha létrehozás után (buildindex) van Append, újra kell építeni!
				//Névsor szerint csökkenõ vagy növekvõ sorrendben rendez a name alapján!
				CPhoneIterName IterName(List);

				//search
				WRITE("** Search **");
				pRec = IterName.search(s1); // name - OK
				ARE_EQUALSTR(s1, pRec->name);
				ARE_EQUALSTR(s2, pRec->number);
				pRec = IterName.search(s2); // number - NOK, számot keres a name mezõben
				Assert::IsTrue(nullptr == pRec);
				pRec = IterName.search(s3); // name - NOK, olyat neve keres, ami nincs benne
				Assert::IsTrue(nullptr == pRec);
				pRec = IterName.search(nullptr); // name - NOK, nullptr
				Assert::IsTrue(nullptr == pRec);

				WRITE("** Next **");
				//Csökkenõ
				//for (i = TESTITEMS - 1/*0*/, pRec = IterName.begin(); pRec != nullptr; pRec = IterName.next(), /*i++*/i--)
				//Növekvõ
				for (i = 0, pRec = IterName.begin(); pRec != nullptr; pRec = IterName.next(), i++)
				{
					sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", i);
					sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", i, i);
					WRITE(Rec.name);
					ARE_EQUALSTR(Rec.name, pRec->name);
					ARE_EQUALSTR(Rec.number, pRec->number);
				}

				//Visszaadja az utolsó elemet, majd mozgatja az iterátort (?!) -> m_iCurrIndex végére áll!
				//Csökkenõ
				//ARE_EQUALSTR("Kis0 Pista", (IterName++)->name);
				//Növekvõ
					//ARE_EQUALSTR("Kis9 Pista", (IterName++)->name);
				//Mozgatja az iterátort, majd visszaadja az értékét. m_iCurrIndex a végén áll már!
				Assert::IsTrue(++IterName == nullptr);

				WRITE("** Prev **");
				
				//Csökkenõ
				//for (i = 0 /*TESTITEMS - 1*/, pRec = IterName.end(); pRec != nullptr; pRec = IterName.prev(), /*i--*/i++)
				//Növekvõ
				for (i = TESTITEMS - 1, pRec = IterName.end(); pRec != nullptr; pRec = IterName.prev(), i--)
				{
					sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", i);
					sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", i, i);
					WRITE(Rec.name);
					ARE_EQUALSTR(Rec.name, pRec->name);
					ARE_EQUALSTR(Rec.number, pRec->number);
				}

				WRITE("** begin, prev **");
				Assert::IsTrue(IterName.begin() != nullptr);
				Assert::IsTrue(IterName.prev() == nullptr); // nem lehet visszalépni
				Assert::IsTrue(IterName.prev() == nullptr); // nem lehet visszalépni
				Assert::IsTrue(IterName.prev() == nullptr); // nem lehet visszalépni

				WRITE("** prev, dec **");
				/*Ha elõbb van a prevben a csökkentés (többször is , elõbb kód!), és utána a next.
				* Ilyen esetben, mivel az m_iCurrIndex hibás értéket vesz fel,
				* ez hibás mûködést eredményez, többször csökkenti az indexet*/
				pRec = IterName.next();
				Assert::IsTrue(pRec != nullptr);

				//Csökkenõ
				//ARE_EQUALSTR("Kis8 Pista", pRec->name);
				//Növekvõ
				ARE_EQUALSTR("Kis1 Pista", pRec->name);

				WRITE("** end, next **");
				Assert::IsTrue(IterName.end() != nullptr);
				Assert::IsTrue(IterName.next() == nullptr);
				
				
				Assert::IsTrue(IterName.next() == nullptr);
				Assert::IsTrue(IterName.next() == nullptr);

				WRITE("** end, prev **");
				Assert::IsTrue(IterName.end() != nullptr);
				pRec = IterName.prev();
				Assert::IsTrue(pRec != nullptr);
				//Csökkenõ
				//ARE_EQUALSTR( "Kis1 Pista", pRec->name);
				//Növekvõ
				ARE_EQUALSTR("Kis8 Pista", pRec->name);


				WRITE("** next, inc**");
				/*mint a prev dec-ben !*/
				Assert::IsTrue(IterName.end() != nullptr);
				Assert::IsTrue(IterName.next() == nullptr);
				Assert::IsTrue(IterName.next() == nullptr);

				pRec = IterName.prev();
				Assert::IsTrue(pRec != nullptr);
				//Csökkenõ
				//ARE_EQUALSTR("Kis1 Pista", pRec->name); //Kis8 Pista utolsó elõtti elem
				//Növekvõ
				ARE_EQUALSTR("Kis8 Pista", pRec->name); //Kis8 Pista utolsó elõtti elem

				pRec = IterName.begin();
				ARE_EQUALSTR("Kis0 Pista", pRec->name);
				pRec = IterName.next();
				ARE_EQUALSTR("Kis1 Pista", pRec->name);
				pRec = IterName.end();
				ARE_EQUALSTR("Kis9 Pista", pRec->name);
				pRec = IterName.prev();
				ARE_EQUALSTR("Kis8 Pista", pRec->name);


				WRITE("\t** done **");
			}
			catch (...) {WRITE("** catch (...) **"); Assert::IsTrue(false);}

		}

		TEST_METHOD(TM_IterInc)
		{
			try {

				WRITE("\n\t** TM_IterInc **");
				int i;
				Record* pRec;
				Record Rec;
				char s1[BUFSIZE];
				char s2[BUFSIZE];
				
				CPhoneList List;

				WRITE("** Append **");
				for (i = 0; i < TESTITEMS; i++)
				{//0...9 ! 
					//Tesztadatok generálása, késõbb is így!
					//Csökkenõ
					//sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", i);
					//sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", i, i);
					//Növekvõ
					sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", TESTITEMS-i-1);
					sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", TESTITEMS-i-1, TESTITEMS-i-1);

					if (i == (TESTITEMS - 2))
					{//kereséshez tesztadat
						strcpy_s(s1, BUFSIZE, Rec.name);    // név -> OK
						strcpy_s(s2, BUFSIZE, Rec.number);  // telszám keresés a névben -> NOK
					}
					//cout << endl << "Name:" << Rec.name << "\tNumber:" << Rec.number;
					WRITE(Rec.name);
					Assert::IsTrue(List.append(Rec) == 0);  //OK
				}
				//betelt, hiba!
				WRITE("** Full **");
				Assert::IsTrue(List.append(Rec) != 0);

				
				CPhoneIterName IterName(List);

				WRITE("** ++IterName **"); 
				//Name szerint csökkenõ: i = TESTITEMS - 1
				//for (i = TESTITEMS - 1, pRec = IterName.begin(); pRec != nullptr; pRec = ++IterName, i--)
				//Növekvõ
				for (i = 0, pRec = IterName.begin(); pRec != nullptr; pRec = ++IterName, i++)
				{
					sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", i);
					sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", i, i);
					WRITE(Rec.name);
					ARE_EQUALSTR(Rec.name, pRec->name);
					ARE_EQUALSTR(Rec.number, pRec->number);
				}


				WRITE("** end, next **");
				Assert::IsTrue(IterName.end() != nullptr);
				//y=++x ! -> növeli x-t, majd azt adja vissza. end() -> végén áll, nullptr!
				Assert::IsTrue(++IterName == nullptr);
				Assert::IsTrue(++IterName == nullptr);
				Assert::IsTrue(++IterName == nullptr);

				Assert::IsTrue(IterName.end() != nullptr);
				
				WRITE("\t** done **");
			}
			catch (...) { WRITE("** catch (...) **"); Assert::IsTrue(false); }

		}

		TEST_METHOD(TM_Display)
		{
			
			try {

				WRITE("\n\t** TM_Display **");
				int i;
				Record Rec;
				
				CPhoneList List;
				static char buf[1024];
				
				memset(buf, 0, sizeof(buf));

				WRITE("\n** displayname **");
				CPhoneList ListName;
				memset(buf, 0, sizeof(buf));

				WRITE("** Append **");
				for (i = 0; i < TESTITEMS; i++)
				{//0...9 ! 
					//Tesztadatok generálása, késõbb is így!
					//Csökkenõ
					//sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", i);
					//sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", i, i);
					//Növekvõ 
					sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", TESTITEMS-i-1);
					sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", TESTITEMS-i-1, TESTITEMS-i-1);

					//cout << endl << "Name:" << Rec.name << "\tNumber:" << Rec.number;
					WRITE(Rec.name);
					Assert::IsTrue(ListName.append(Rec) == 0);  //OK
				}

				//Csökkenõ
				//for (i = TESTITEMS - 1; i>=0; i--)
				//Növekvõ
				for (i = 0; i < TESTITEMS; i++)
				{
					sprintf_s( buf + strlen(buf), sizeof(buf) - strlen(buf), "\nKis%d Pista;%03d-%03d", i,i,i);
					//WRITE(buf);
				}
				
				
				WRITE("\nbuf: ");
				WRITE(buf);
				WRITE("\ncout: ");
				//----------------
				{
					std::stringstream buffer;
					std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

					buffer = std::stringstream();
					
					ListName.displayname();

					std::string d = buffer.str();
					WRITE(d.c_str());
					Assert::IsTrue(!d.compare(buf));

					std::cout.rdbuf(prevcoutbuf);
				}
				//-------------
				WRITE("\t** done **");
			}
			catch (...) { WRITE("** catch (...) **"); Assert::IsTrue(false); }
			

		}


	};
}

