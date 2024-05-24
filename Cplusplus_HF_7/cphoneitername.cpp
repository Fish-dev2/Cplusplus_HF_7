#include "cphoneitername.h"
#include <algorithm>

CPhoneIterName::CPhoneIterName(CPhoneList& list) : m_cpList(&list), m_iCurrIndex(0) 
{
    orderNames();
}

CPhoneIterName::~CPhoneIterName() {}

Record* CPhoneIterName::begin() {
    if (m_cpList->m_iFirstEmpty > 0) {
        m_iCurrIndex = 0;
        return &(m_cpList->m_rArray[m_iArray[0]]);
    }
    else
        return nullptr;
}

Record* CPhoneIterName::prev() {
    if (m_iCurrIndex > 0)
        return &(m_cpList->m_rArray[m_iArray[--m_iCurrIndex]]);
    else
        return nullptr;
}

Record* CPhoneIterName::next() {
    m_iCurrIndex++;
    if (m_iCurrIndex < m_cpList->m_iFirstEmpty - 1)
        return &(m_cpList->m_rArray[m_iArray[m_iCurrIndex]]);
    else
        return nullptr;
}

Record* CPhoneIterName::operator++() {
    return next();
}


Record* CPhoneIterName::end() {
    if (m_cpList->m_iFirstEmpty > 0)
        return &(m_cpList->m_rArray[m_iArray[m_cpList->m_iFirstEmpty - 1]]);
    else
        return nullptr;
}

int CPhoneIterName::size() {
    return m_cpList->m_iFirstEmpty;
}

Record* CPhoneIterName::search(const char* key) {
    Record* p = nullptr;
    if (key == nullptr)
    {
        return nullptr;
    }
    for (p = begin(); p != nullptr; p = next())
    {
        if (std::strcmp(p->name, key) == 0)
            return p;
    }
    return nullptr;
}


void CPhoneIterName::orderNames() {

    for (size_t i = 0; i < m_cpList->m_iFirstEmpty; i++)
    {
        m_iArray[i] = i;
    }


   std::stable_sort(m_iArray, m_iArray + m_cpList->m_iFirstEmpty, [&](int i, int j) 
       {
        return caseInsensitiveCompare(m_cpList->m_rArray[i].name, m_cpList->m_rArray[j].name);
       });
}

bool CPhoneIterName::caseInsensitiveCompare(const std::string& str1, const std::string& str2) {
    std::string upperStr1 = str1;
    std::transform(upperStr1.begin(), upperStr1.end(), upperStr1.begin(), ::toupper);

    std::string upperStr2 = str2;
    std::transform(upperStr2.begin(), upperStr2.end(), upperStr2.begin(), ::toupper);

    return upperStr1 < upperStr2;
}