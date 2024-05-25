//JI9J9A Füzi Bálint FELADAT7V2
#include "cphonelist.h"
#include <iostream>
#include "cphoneitername.h"


CPhoneList::CPhoneList() : m_iFirstEmpty(0) {}

int CPhoneList::append(const Record& newrec) {
    if (m_iFirstEmpty < MAXLENGTH) {
        strcpy_s(m_rArray[m_iFirstEmpty].name, sizeof(m_rArray[m_iFirstEmpty].name), newrec.name);
        strcpy_s(m_rArray[m_iFirstEmpty].number, sizeof(m_rArray[m_iFirstEmpty].number), newrec.number);
        m_iFirstEmpty++;
        return 0;
    }
    return -1;
}
void CPhoneList::displayname() {
    CPhoneIterName listIterName(*this); 
    Record* p = nullptr;

    for (p = listIterName.begin(); p != nullptr; p = ++listIterName) {
        std::cout << *p;
    }
}

std::ostream& operator<<(std::ostream& os, Record& r)
{
    std::cout << std::endl << r.name << ";" << r.number;
    return os;
}
