#ifndef CRMDATA_H
#define CRMDATA_H

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "Client.h"
#include "Interaction.h"
using std::string;

class CrmData
{
public:
    // Fields (public for now, per your preference)
    std::vector<Client> clients;
    std::vector<Interaction> interactions;

    // Constructor (declared; defined in .cpp)
    CrmData();

    // Search by name+surname+birthDate
    Client *searchClient(const string &name, const string &surname, const string &birthDate);

    // Delete a client by ID and cascade-delete their interactions.
    // Returns true if a client with that ID was found and removed.
    bool deleteClientAndCascade(int clientId);

    // Update a client's fields by ID. Returns true if updated, false if not found.
    bool updateClientById(int clientId,
                          const string &name,
                          const string &surname,
                          const string &birthDate,
                          const string &email,
                          const string &phone);
};

/*******************
 * HELPER FUNCTIONS
 *******************/
std::string toLower(const std::string &s);

#endif
