#include "pch.h"
#include "CppUnitTest.h"
#include "cphonelist.h"
#include "cphoneitername.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(Iterator_Size_Test)
		{
			Record records[] = {
				  Record {"Harvey", "+36200010101"},
				  Record {"Donna", "+36200020101"},
				  Record {"Dana", "+36200030101"},
				  Record {"Jessica", "+36200040101"},
				  Record {"Mike", "+36200050101"},
				  Record {"Rachel", "+36200060101"},
				  Record {"Louis", "+36200070101"},
				  Record {"Katrina", "+36200080101"},
				  Record {"Dana", "+36200031101"},
			};
			CPhoneList list;
			for (const auto& r : records)
				list.append(r);
			CPhoneIterName it = list;
			Assert::AreEqual(9, it.size());
		}

		TEST_METHOD(Iterator_Begin_Test)
		{
			Record records[] = {
				  Record {"Harvey", "+36200010101"},
				  Record {"Donna", "+36200020101"},
				  Record {"Dana", "+36200030101"},
				  Record {"Jessica", "+36200040101"},
				  Record {"Mike", "+36200050101"},
				  Record {"Rachel", "+36200060101"},
				  Record {"Louis", "+36200070101"},
				  Record {"Katrina", "+36200080101"},
			};
			CPhoneList list;
			for (const auto& r : records)
				list.append(r);
			CPhoneIterName it = list;
			auto first = it.begin();
			if (first == nullptr)
				Assert::Fail();
			Assert::AreEqual("Dana", (const char*)first->name);
			Assert::AreEqual("+36200030101", (const char*)first->number);
		}


		TEST_METHOD(Iterator_Begin_Test_Empty)
		{
			CPhoneList list;
			CPhoneIterName it = list;
			auto first = it.begin();
			if (first != nullptr)
				Assert::Fail();
		}

		TEST_METHOD(Iterator_End_Test)
		{
			Record records[] = {
				  Record {"Harvey", "+36200010101"},
				  Record {"Donna", "+36200020101"},
				  Record {"Dana", "+36200030101"},
				  Record {"Jessica", "+36200040101"},
				  Record {"Mike", "+36200050101"},
				  Record {"Rachel", "+36200060101"},
				  Record {"Louis", "+36200070101"},
				  Record {"Katrina", "+36200080101"},
			};
			CPhoneList list;
			for (const auto& r : records)
				list.append(r);
			CPhoneIterName it = list;
			auto last = it.end();
			if (last == nullptr)
				Assert::Fail();
			Assert::AreEqual("Rachel", (const char*)last->name);
			Assert::AreEqual("+36200060101", (const char*)last->number);

		}


		TEST_METHOD(Iterator_End_Test_Empty)
		{
			CPhoneList list;
			CPhoneIterName it = list;
			auto end = it.end();
			if (end != nullptr)
				Assert::Fail();
		}

		TEST_METHOD(Iterator_Test_Sort) {
			Record records[] = {
				  Record {"Harvey", "+36200010101"},
				  Record {"Donna", "+36200020101"},
				  Record {"Dana", "+36200030101"},
				  Record {"Jessica", "+36200040101"},
				  Record {"Mike", "+36200050101"},
				  Record {"Rachel", "+36200060101"},
				  Record {"Louis", "+36200070101"},
				  Record {"Katrina", "+36200080101"},
				  Record {"Dana", "+36200100101"}
			};
			CPhoneList list;
			for (const auto& r : records)
				list.append(r);
			CPhoneIterName it = list;
			Record* element = nullptr;
			int i = 0;
			Record sortedRecords[] = {
				Record {"Dana", ""},
				Record {"Dana", ""},
				Record {"Donna", ""},
				Record {"Harvey", ""},
				Record {"Jessica", ""},
				Record {"Katrina", ""},
				Record {"Louis", ""},
				Record {"Mike", ""},
				Record {"Rachel", ""}
			};
			for (element = it.begin(); element != nullptr; element = ++it) {
				Assert::AreEqual(sortedRecords[i].name, element->name);
				++i;
			}

		}

		TEST_METHOD(Iterator_Test_Prev) {
			Record records[] = {
				  Record {"Harvey", "+36200010101"},
				  Record {"Donna", "+36200020101"},
				  Record {"Dana", "+36200030101"},
				  Record {"Jessica", "+36200040101"},
				  Record {"Mike", "+36200050101"},
				  Record {"Rachel", "+36200060101"},
				  Record {"Louis", "+36200070101"},
				  Record {"Katrina", "+36200080101"},
				  Record {"Dana", "+36200100101"}
			};
			CPhoneList list;
			for (const auto& r : records)
				list.append(r);
			CPhoneIterName it = list;
			Record* element = nullptr;
			int i = it.size() - 1;
			Record sortedRecords[] = {
				Record {"Dana", ""},
				Record {"Dana", ""},
				Record {"Donna", ""},
				Record {"Harvey", ""},
				Record {"Jessica", ""},
				Record {"Katrina", ""},
				Record {"Louis", ""},
				Record {"Mike", ""},
				Record {"Rachel", ""}
			};
			for (element = it.end(); element != nullptr; element = it.prev()) {
				Assert::AreEqual(sortedRecords[i].name, element->name);
				--i;
			}

		}

		TEST_METHOD(Iterator_Test_Prev_NullPtr) {
			Record records[] = {
				  Record {"Harvey", "+36200010101"},
				  Record {"Donna", "+36200020101"},
				  Record {"Dana", "+36200030101"},
				  Record {"Jessica", "+36200040101"},
				  Record {"Mike", "+36200050101"},
				  Record {"Rachel", "+36200060101"},
				  Record {"Louis", "+36200070101"},
				  Record {"Katrina", "+36200080101"},
				  Record {"Dana", "+36200100101"}
			};
			CPhoneList list;
			for (const auto& r : records)
				list.append(r);
			CPhoneIterName it = list;
			Record* element = nullptr;
			int i = it.size() - 1;
			Record sortedRecords[] = {
				Record {"Dana", ""},
				Record {"Dana", ""},
				Record {"Donna", ""},
				Record {"Harvey", ""},
				Record {"Jessica", ""},
				Record {"Katrina", ""},
				Record {"Louis", ""},
				Record {"Mike", ""},
				Record {"Rachel", ""}
			};
			for (element = it.end(); element != nullptr; element = it.prev()) {
				Assert::AreEqual(sortedRecords[i].name, element->name);
				--i;
			}
			for (int i = 0; i < 3; ++i) {
				if (it.prev() != nullptr)
					Assert::Fail();
			}
			element = it.next();
			Assert::AreEqual("Dana", element->name);

		}

		TEST_METHOD(Iterator_Next_Test_NullPtr) {
			Record records[] = {
				  Record {"katrina", "+362010101"},
				  Record {"Donna", "+36200020101"},
				  Record {"dana", "+36200030101"},
				  Record {"Jessica", "+36200040101"},
				  Record {"aBc", "+36200011239"},
				  Record {"Mike", "+36200050101"},
				  Record {"Rachel", "+36200060101"},
				  Record {"Katrina", "+36200080101"},
				  Record {"abc", "+36200011234"},
				  Record {"danA", "+36200100101"}
			};
			CPhoneList list;
			for (const auto& r : records)
				list.append(r);
			CPhoneIterName it = list;
			Record* element = nullptr;
			int i = 0;
			Record sortedRecords[] = {
				Record {"aBc", ""},
				Record {"abc", ""},
				Record {"dana", ""},
				Record {"danA", ""},
				Record {"Donna", ""},
				Record {"Jessica", ""},
				Record {"katrina", ""},
				Record {"Katrina", ""},
				Record {"Mike", ""},
				Record {"Rachel", ""}
			};
			for (element = it.begin(); element != nullptr; element = it.next()) {
				Assert::AreEqual(sortedRecords[i].name, element->name);
				++i;
			}
			element = it.prev();
			Assert::AreEqual("Mike", element->name);
			element = it.next();
			Assert::IsTrue(it.end() != nullptr);
			for (int i = 0; i < 3; ++i) {
				Assert::IsTrue(it.next() == nullptr);
			}
			element = it.prev();
			Assert::AreEqual("Mike", element->name);
		}

		TEST_METHOD(Iterator_Search_Test) {
			Record records[] = {
			  Record {"Harvey", "+36200010101"},
			  Record {"katrina", "+362010101"},
			  Record {"Donna", "+36200020101"},
			  Record {"Dana", "+36200030101"},
			  Record {"Jessica", "+36200040101"},
			  Record {"Mike", "+36200050101"},
			  Record {"Rachel", "+36200060101"},
			  Record {"Louis", "+36200070101"},
			  Record {"Katrina", "+36200080101"},
			  Record {"Dana", "+36200100101"}
			};
			CPhoneList list;
			for (const auto& r : records)
				list.append(r);
			CPhoneIterName it = list;
			Assert::AreEqual("Katrina", it.search("Katrina")->name);
			Assert::AreEqual("Rachel", it.search("Rachel")->name);
			Assert::AreEqual("Dana", it.search("Dana")->name);
			Assert::AreEqual("katrina", it.search("katrina")->name);
			auto donnaTypo = it.search("Dona");
			if (nullptr != donnaTypo)
				Assert::Fail();
			auto nullPtrString = it.search(nullptr);
			if (nullPtrString != nullptr)
				Assert::Fail();
		}


	};
}