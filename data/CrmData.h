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
    // Fields
    std::vector<Client> clients;
    std::vector<Interaction> interactions;

    // Constructor
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

    // Save all clients and interactions to CSV files. Returns true on success.
    bool saveToCsv(const string &clientsPath,
                   const string &interactionsPath) const;

    // Load all clients and interactions from CSV files. Returns true on success.
    // Keeps IDs from file, and rebuilds Client::interactionIds from interactions.
    bool loadFromCsv(const string &clientsPath,
                     const string &interactionsPath);
};

/*******************
 * HELPER FUNCTIONS
 *******************/
std::string toLower(const std::string &s);

#endif
