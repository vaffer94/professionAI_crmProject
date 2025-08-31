#ifndef CRMDATA_H
#define CRMDATA_H

#include <vector>
#include <string>
#include "Client.h"
#include "Interaction.h"

class CrmData
{
public:
    // Fields (public for now, per your preference)
    std::vector<Client> clients;
    std::vector<Interaction> interactions;

    // Constructor (declared; defined in .cpp)
    CrmData();

    // Search by name+surname (overloads: mutable and const)
    Client *searchClient(const std::string &name, const std::string &surname);
};

#endif
