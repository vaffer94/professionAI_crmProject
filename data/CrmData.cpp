#include "data/CrmData.h"

CrmData::CrmData()
    : clients(),
      interactions() {}

// Mock: return nullptr (no duplicates found)
Client *CrmData::searchClient(const std::string &name, const std::string &surname)
{
    return nullptr;
}
