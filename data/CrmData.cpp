#include "data/CrmData.h"
#include <fstream>
#include <sstream>
#include "third_party/csv.h"
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

// Escape a field for CSV (always quotes, "" for internal quotes)
static std::string csvEscape(const std::string &s)
{
    std::string out;
    out.reserve(s.size() + 2);
    out.push_back('"');
    for (char ch : s)
    {
        if (ch == '"')
            out.push_back('"'); // double quotes
        out.push_back(ch);
    }
    out.push_back('"');
    return out;
}

/*******************
 * PUBLIC FUNCTIONS
 *******************/

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

bool CrmData::loadFromCsv(const string &clientsPath,
                          const string &interactionsPath)
{
    try
    {
        clients.clear();
        interactions.clear();

        // --- clients.csv ---
        {
            // io::CSVReader<6> in(clientsPath);
            // in.read_header(io::ignore_extra_column,
            //                "id", "name", "surname", "birthDate", "email", "phone");
            io::CSVReader<6, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> in(clientsPath);
            in.read_header(io::ignore_extra_column,
                           "id", "name", "surname", "birthDate", "email", "phone");

            int id;
            string name, surname, birthDate, email, phone;

            while (in.read_row(id, name, surname, birthDate, email, phone))
            {
                Client c;
                c.id = id;
                c.name = name;
                c.surname = surname;
                c.birthDate = birthDate;
                c.email = email;
                c.phone = phone;
                c.interactionIds.clear();
                clients.push_back(c);
            }
        }

        // --- interactions.csv ---
        {
            // io::CSVReader<7> in(interactionsPath);
            // in.read_header(io::ignore_extra_column,
            //                "id", "clientId", "type", "status", "date", "responsible", "note");ù

            io::CSVReader<7, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> in(interactionsPath);
            in.read_header(io::ignore_extra_column,
                           "id", "clientId", "type", "status", "date", "responsible", "note");

            int id, clientId, typeVal, statusVal;
            string date, responsible, note;

            while (in.read_row(id, clientId, typeVal, statusVal, date, responsible, note))
            {
                Interaction it;
                it.id = id;
                it.clientId = clientId;
                it.type =
                    (typeVal == static_cast<int>(InteractionType::Appointment)) ? InteractionType::Appointment : (typeVal == static_cast<int>(InteractionType::Contract)) ? InteractionType::Contract
                                                                                                                                                                          : InteractionType::Unknown;

                it.status =
                    (statusVal == static_cast<int>(InteractionStatus::ToDo)) ? InteractionStatus::ToDo : (statusVal == static_cast<int>(InteractionStatus::InProgress)) ? InteractionStatus::InProgress
                                                                                                     : (statusVal == static_cast<int>(InteractionStatus::Done))         ? InteractionStatus::Done
                                                                                                                                                                        : InteractionStatus::Cancelled;

                it.date = date;
                it.responsible = responsible;
                it.note = note;

                interactions.push_back(it);
            }
        }

        // Rebuild client.interactionIds (no ID regeneration)
        for (auto &c : clients)
            c.interactionIds.clear();
        for (const auto &it : interactions)
        {
            for (auto &c : clients)
            {
                if (c.id == it.clientId)
                {
                    c.interactionIds.push_back(it.id);
                    break;
                }
            }
        }

        return true;
    }
    catch (const std::exception &)
    {
        // parser throws if files can't be opened or header mismatch
        return false;
    }
}

bool CrmData::saveToCsv(const string &clientsPath,
                        const string &interactionsPath) const
{
    std::ofstream fc(clientsPath, std::ios::trunc);
    std::ofstream fi(interactionsPath, std::ios::trunc);
    if (!fc || !fi)
        return false;

    // headers
    fc << "id,name,surname,birthDate,email,phone\n";
    fi << "id,clientId,type,status,date,responsible,note\n";

    // clients
    for (const auto &c : clients)
    {
        fc << c.id << ','
           << csvEscape(c.name) << ','
           << csvEscape(c.surname) << ','
           << csvEscape(c.birthDate) << ','
           << csvEscape(c.email) << ','
           << csvEscape(c.phone) << '\n';
    }

    // interactions
    for (const auto &it : interactions)
    {
        fi << it.id << ','
           << it.clientId << ','
           << static_cast<int>(it.type) << ','
           << static_cast<int>(it.status) << ','
           << csvEscape(it.date) << ','
           << csvEscape(it.responsible) << ','
           << csvEscape(it.note) << '\n';
    }

    return true;
}