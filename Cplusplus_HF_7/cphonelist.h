#pragma once
#include <ostream>

#define MAXLENGTH 10 // értéke változhat,ahogy a munka kívánja!
#define MAXNAME 32
#define MAXNUMBER 16
struct Record {
	char name[MAXNAME + 1];
	char number[MAXNUMBER + 1];
};
class CPhoneList {
	friend class CPhoneIterName; // növekvő sorrendben, name alapján
public:
	CPhoneList();
	int append(const Record& newrec); // tömbbe teszi, az első szabad/üres helyre // 0, ha ok, nem 0, ha nincs több hely
	void displayname(); // bejárás a name rendezettség (növekvő) szerint a // ++ operátorral, a kiírás << -! 
private:
	Record m_rArray[MAXLENGTH]; // adatok tárolása, fix méretű!
	int m_iFirstEmpty; // következő szabad/üres hely az m_rArray-ban
};
std::ostream& operator << (std::ostream& os, Record& r); // formátum: <std::endl>r.name<;>r.number

