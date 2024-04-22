#include "cphoneitername.h"

CPhoneIterName::CPhoneIterName(CPhoneList& list) : m_cpList(&list), m_iCurrIndex(0) 
{
    orderNames();
}

CPhoneIterName::~CPhoneIterName() {}

Record* CPhoneIterName::begin() {
    if (m_cpList->m_iFirstEmpty > 0)
        return &(m_cpList->m_rArray[0]);
    else
        return nullptr;
}

Record* CPhoneIterName::prev() {
    if (m_iCurrIndex > 0)
        return &(m_cpList->m_rArray[--m_iCurrIndex]);
    else
        return nullptr;
}

Record* CPhoneIterName::next() {
    if (m_iCurrIndex < m_cpList->m_iFirstEmpty - 1)
        return &(m_cpList->m_rArray[++m_iCurrIndex]);
    else
        return nullptr;
}

Record* CPhoneIterName::operator++() {
    return next();
}


Record* CPhoneIterName::end() {
    if (m_cpList->m_iFirstEmpty > 0)
        return &(m_cpList->m_rArray[m_cpList->m_iFirstEmpty - 1]);
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

        p = next();
    }
    return nullptr;
}

void CPhoneIterName::orderNames() {
    for (size_t i = 0; i < m_cpList->m_iFirstEmpty; i++)
    {
        m_iArray[i] = i;
    }
    for (size_t i = 0; i < m_cpList->m_iFirstEmpty; i++)
    {
        for (size_t j = i+1; j < m_cpList->m_iFirstEmpty; j++)
        {
            std::string tempI(m_cpList->m_rArray[i].name);
            std::string tempJ(m_cpList->m_rArray[j].name);
            if (tempI>tempJ)
            {
                m_iArray[i] = j;
                m_iArray[j] = i;
            }
        }
    }
}