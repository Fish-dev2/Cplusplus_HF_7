//JI9J9A Füzi Bálint FELADAT7V2
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
		
		TEST_METHOD(AppendTest)
		{
			CPhoneList phoneList;
			Record record = { "John", "1234567890" };
			Assert::AreEqual(phoneList.append(record), 0);
			Assert::AreEqual(CPhoneIterName(phoneList).size(), 1);
		}
        TEST_METHOD(BeginEndTest)
        {
            CPhoneList phoneList;
            Record record1 = { "Alice", "1111111111" };
            Record record2 = { "Bob", "2222222222" };
            phoneList.append(record1);
            phoneList.append(record2);

            CPhoneIterName iter(phoneList);


            Assert::IsNotNull(iter.begin());
            Assert::IsNotNull(iter.end());
        }

        TEST_METHOD(NextPrevTest)
        {
            CPhoneList phoneList;
            Record record1 = { "Alice", "1111111111" };
            Record record2 = { "Bob", "2222222222" };
            Record record3 = { "Charlie", "3333333333" };
            phoneList.append(record1);
            phoneList.append(record2);
            phoneList.append(record3);

            CPhoneIterName iter(phoneList);


            iter.begin();
            Assert::IsTrue(strcmp(iter.next()->name, "Bob") == 0);
            Assert::IsTrue(strcmp(iter.prev()->name, "Alice") == 0);
        }

        TEST_METHOD(SearchTest)
        {
            CPhoneList phoneList;
            Record record1 = { "Alice", "1111111111" };
            Record record2 = { "Bob", "2222222222" };
            Record record3 = { "Charlie", "3333333333" };
            phoneList.append(record1);
            phoneList.append(record2);
            phoneList.append(record3);

            CPhoneIterName iter(phoneList);


            Assert::IsNotNull(iter.search("Bob"));
            Assert::IsNull(iter.search("David"));
        }

        TEST_METHOD(SizeTest)
        {
            CPhoneList phoneList;
            Record record1 = { "Alice", "1111111111" };
            Record record2 = { "Bob", "2222222222" };
            Record record3 = { "Charlie", "3333333333" };
            phoneList.append(record1);
            phoneList.append(record2);
            phoneList.append(record3);

            CPhoneIterName iter(phoneList);

            Assert::AreEqual(iter.size(), 3);
        }

        TEST_METHOD(IncrementOperatorTest)
        {
            CPhoneList phoneList;
            Record record1 = { "Alice", "1111111111" };
            Record record2 = { "Bob", "2222222222" };
            Record record3 = { "Charlie", "3333333333" };
            phoneList.append(record1);
            phoneList.append(record2);
            phoneList.append(record3);

            CPhoneIterName iter(phoneList);


            Assert::IsNotNull(++iter);
        }


        TEST_METHOD(ConstructorDestructorTest)
        {

            CPhoneList phoneList;
            CPhoneIterName* iter = new CPhoneIterName(phoneList);
            delete iter;
        }

        

        TEST_METHOD(EmptyListTest)
        {

            CPhoneList phoneList;
            CPhoneIterName iter(phoneList);


            Assert::IsNull(iter.begin());
            Assert::IsNull(iter.end());
            Assert::IsNull(iter.next());
            Assert::IsNull(iter.prev());
            Assert::IsNull(iter.search("Alice"));
        }

        TEST_METHOD(OutOfBoundsTest)
        {

            CPhoneList phoneList;
            Record record = { "Alice", "1111111111" };
            phoneList.append(record);

            CPhoneIterName iter(phoneList);

            Assert::IsNull(iter.prev()); 
            Assert::IsNull(iter.next()); 
        }

        TEST_METHOD(IncrementOperatorNullTest)
        {

            CPhoneList phoneList;
            Record record = { "Alice", "1111111111" };
            phoneList.append(record);

            CPhoneIterName iter(phoneList);

            iter.next();

            Assert::IsNull(++iter);
        }
        TEST_METHOD(CaseSensitiveSearchTest)
        {
            CPhoneList phoneList;
            Record record1 = { "Alice", "1111111111" };
            Record record2 = { "alice", "2222222222" };
            phoneList.append(record1);
            phoneList.append(record2);

            CPhoneIterName iter(phoneList);

            
            Assert::IsNotNull(iter.search("Alice")); 
            Assert::IsNotNull(iter.search("alice"));
        }
	};
}
