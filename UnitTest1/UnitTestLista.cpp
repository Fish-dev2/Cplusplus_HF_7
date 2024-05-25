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

TESZTHEZ BE KELL �LL�TANI! -> ppt-phonelist_test.h -> testadatok gener�l�sa miatt
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
				char s3[] = "Ilyen n�v biztos nincs";

				CPhoneList List;
				
				WRITE("** Append **");
				for (i = 0; i < TESTITEMS; i++)
				{//0...9 ! 
					//Tesztadatok gener�l�sa, k�s�bb is �gy!

					//N�vekv� sorrendben gener�l
					//sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", i);
					//sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", i, i);
					//Cs�kken� sorrendben gener�l
					sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", TESTITEMS-i-1);
					sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", TESTITEMS-i-1 , TESTITEMS-i-1);


					if (i == (TESTITEMS - 2))
					{//keres�shez tesztadat
						strcpy_s(s1, BUFSIZE, Rec.name);    // n�v -> OK
						strcpy_s(s2, BUFSIZE, Rec.number);  // telsz�m keres�s a n�vben -> NOK
					}
					//cout << endl << "Name:" << Rec.name << "\tNumber:" << Rec.number;
					WRITE(Rec.name);
					Assert::IsTrue(List.append(Rec) == 0);  //OK
				}


				List.displayname();


				//betelt, hiba!
				WRITE("** Full **");
				Assert::IsTrue(List.append(Rec) != 0);

				//Append ut�n, csak felt�lt�s ut�n lehet feladat szerint
				//Ha l�trehoz�s ut�n (buildindex) van Append, �jra kell �p�teni!
				//N�vsor szerint cs�kken� vagy n�vekv� sorrendben rendez a name alapj�n!
				CPhoneIterName IterName(List);

				//search
				WRITE("** Search **");
				pRec = IterName.search(s1); // name - OK
				ARE_EQUALSTR(s1, pRec->name);
				ARE_EQUALSTR(s2, pRec->number);
				pRec = IterName.search(s2); // number - NOK, sz�mot keres a name mez�ben
				Assert::IsTrue(nullptr == pRec);
				pRec = IterName.search(s3); // name - NOK, olyat neve keres, ami nincs benne
				Assert::IsTrue(nullptr == pRec);
				pRec = IterName.search(nullptr); // name - NOK, nullptr
				Assert::IsTrue(nullptr == pRec);

				WRITE("** Next **");
				//Cs�kken�
				//for (i = TESTITEMS - 1/*0*/, pRec = IterName.begin(); pRec != nullptr; pRec = IterName.next(), /*i++*/i--)
				//N�vekv�
				for (i = 0, pRec = IterName.begin(); pRec != nullptr; pRec = IterName.next(), i++)
				{
					sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", i);
					sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", i, i);
					WRITE(Rec.name);
					ARE_EQUALSTR(Rec.name, pRec->name);
					ARE_EQUALSTR(Rec.number, pRec->number);
				}

				//Visszaadja az utols� elemet, majd mozgatja az iter�tort (?!) -> m_iCurrIndex v�g�re �ll!
				//Cs�kken�
				//ARE_EQUALSTR("Kis0 Pista", (IterName++)->name);
				//N�vekv�
					//ARE_EQUALSTR("Kis9 Pista", (IterName++)->name);
				//Mozgatja az iter�tort, majd visszaadja az �rt�k�t. m_iCurrIndex a v�g�n �ll m�r!
				Assert::IsTrue(++IterName == nullptr);

				WRITE("** Prev **");
				
				//Cs�kken�
				//for (i = 0 /*TESTITEMS - 1*/, pRec = IterName.end(); pRec != nullptr; pRec = IterName.prev(), /*i--*/i++)
				//N�vekv�
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
				Assert::IsTrue(IterName.prev() == nullptr); // nem lehet visszal�pni
				Assert::IsTrue(IterName.prev() == nullptr); // nem lehet visszal�pni
				Assert::IsTrue(IterName.prev() == nullptr); // nem lehet visszal�pni

				WRITE("** prev, dec **");
				/*Ha el�bb van a prevben a cs�kkent�s (t�bbsz�r is , el�bb k�d!), �s ut�na a next.
				* Ilyen esetben, mivel az m_iCurrIndex hib�s �rt�ket vesz fel,
				* ez hib�s m�k�d�st eredm�nyez, t�bbsz�r cs�kkenti az indexet*/
				pRec = IterName.next();
				Assert::IsTrue(pRec != nullptr);

				//Cs�kken�
				//ARE_EQUALSTR("Kis8 Pista", pRec->name);
				//N�vekv�
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
				//Cs�kken�
				//ARE_EQUALSTR( "Kis1 Pista", pRec->name);
				//N�vekv�
				ARE_EQUALSTR("Kis8 Pista", pRec->name);


				WRITE("** next, inc**");
				/*mint a prev dec-ben !*/
				Assert::IsTrue(IterName.end() != nullptr);
				Assert::IsTrue(IterName.next() == nullptr);
				Assert::IsTrue(IterName.next() == nullptr);

				pRec = IterName.prev();
				Assert::IsTrue(pRec != nullptr);
				//Cs�kken�
				//ARE_EQUALSTR("Kis1 Pista", pRec->name); //Kis8 Pista utols� el�tti elem
				//N�vekv�
				ARE_EQUALSTR("Kis8 Pista", pRec->name); //Kis8 Pista utols� el�tti elem

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
					//Tesztadatok gener�l�sa, k�s�bb is �gy!
					//Cs�kken�
					//sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", i);
					//sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", i, i);
					//N�vekv�
					sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", TESTITEMS-i-1);
					sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", TESTITEMS-i-1, TESTITEMS-i-1);

					if (i == (TESTITEMS - 2))
					{//keres�shez tesztadat
						strcpy_s(s1, BUFSIZE, Rec.name);    // n�v -> OK
						strcpy_s(s2, BUFSIZE, Rec.number);  // telsz�m keres�s a n�vben -> NOK
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
				//Name szerint cs�kken�: i = TESTITEMS - 1
				//for (i = TESTITEMS - 1, pRec = IterName.begin(); pRec != nullptr; pRec = ++IterName, i--)
				//N�vekv�
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
				//y=++x ! -> n�veli x-t, majd azt adja vissza. end() -> v�g�n �ll, nullptr!
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
					//Tesztadatok gener�l�sa, k�s�bb is �gy!
					//Cs�kken�
					//sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", i);
					//sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", i, i);
					//N�vekv� 
					sprintf_s(Rec.name, sizeof(Rec.name) - 1, "Kis%d Pista", TESTITEMS-i-1);
					sprintf_s(Rec.number, sizeof(Rec.number) - 1, "%03d-%03d", TESTITEMS-i-1, TESTITEMS-i-1);

					//cout << endl << "Name:" << Rec.name << "\tNumber:" << Rec.number;
					WRITE(Rec.name);
					Assert::IsTrue(ListName.append(Rec) == 0);  //OK
				}

				//Cs�kken�
				//for (i = TESTITEMS - 1; i>=0; i--)
				//N�vekv�
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

