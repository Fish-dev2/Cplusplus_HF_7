

#include <iostream>
#include "cphonelist.h"
#include "cphoneitername.h"

int main()
{
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

    Record* p = nullptr;
    for (p = it.begin(); p != nullptr; p = it.next())
    {
		std::cout << p->name << std::endl;
    }
	std::cout << (it.next() == nullptr);
}

