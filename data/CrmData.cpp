#include "data/CrmData.h"

CrmData::CrmData()
    : clients(),
      interactions() {}

Client *CrmData::searchClient(const string &name,
                              const string &surname,
                              const string &birthDate)
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        Client &c = clients[i];
        if (toLower(c.name) == toLower(name) &&
            toLower(c.surname) == toLower(surname) &&
            c.birthDate == birthDate) // birthDate stays case-sensitive
        {
            return &c;
        }
    }
    return nullptr;
}

bool CrmData::deleteClientAndCascade(int clientId)
{
    // 1) Remove all interactions linked to this client
    for (size_t i = 0; i < interactions.size(); /* no i++ here */)
    {
        if (interactions[i].clientId == clientId)
        {
            interactions.erase(interactions.begin() + i);
        }
        else
        {
            i++;
        }
    }

    // 2) Remove the client itself
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i].id == clientId)
        {
            clients.erase(clients.begin() + i);
            return true; // removed successfully
        }
    }

    return false; // no client with that ID
}

bool CrmData::updateClientById(int clientId,
                               const string &name,
                               const string &surname,
                               const string &birthDate,
                               const string &email,
                               const string &phone)
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        Client &c = clients[i];
        if (c.id == clientId)
        {
            c.name = name;
            c.surname = surname;
            c.birthDate = birthDate;
            c.email = email;
            c.phone = phone;
            return true;
        }
    }
    return false;
}

/*******************
 * HELPER FUNCTIONS
 *******************/

std::string toLower(const std::string &s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char ch)
                   { return std::tolower(ch); });
    return result;
}
