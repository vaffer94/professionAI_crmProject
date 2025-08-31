#include <iostream>
#include <string>
#include <limits>
#include "ui.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

void showSplashScreen()
{
    std::cout << "=====================================\n";
    std::cout << "  Benvenuto in InsuraPro Solutions\n";
    std::cout << "  Sistema CRM - Applicazione Console\n";
    std::cout << "=====================================\n\n";
}

void showMainMenu(CrmData &crm)
{
    int choice = -1;
    do
    {
        cout << "\nSeleziona un'opzione (inserire il numero corrispondente):\n";
        cout << "1️⃣  Creare un cliente 👤➕\n";
        cout << "2️⃣  Visualizzare tutti i clienti 📋\n";
        cout << "3️⃣  Modificare un cliente  ✏️\n";
        cout << "4️⃣  Eliminare un cliente 🗑️\n";
        cout << "5️⃣  Ricercare un cliente 🔎\n";
        cout << "6️⃣  Gestire le interazioni del cliente 🤝\n";
        cout << "0️⃣  Uscire\n";
        cout << "> ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            uiCreateClient(crm);
            break;
        case 2:
            uiViewClients(crm);
            break;
        case 3:
            uiEditClient(crm);
            break;
        case 4:
            uiDeleteClient(crm);
            break;
        case 5:
            uiSearchClient(crm);
            break;
        case 6:
            uiManageInteractions(crm);
            break;
        case 0:
            cout << "👋 Uscita dal programma...\n";
            break;
        default:
            cout << "❌ Scelta non valida. Riprova.\n";
            break;
        }
    } while (choice != 0);
}

void uiCreateClient(CrmData &crm)
{
    string name, surname, birthDate, email, phone;

    cout << "Inserisci nome: ";
    getline(cin >> std::ws, name);

    cout << "Inserisci cognome: ";
    getline(cin, surname);

    cout << "Inserisci data di nascita (YYYY-MM-DD): ";
    cin >> birthDate;

    // 🔎 check duplicates by name+surname+birthDate
    Client *existing = crm.searchClient(name, surname, birthDate);
    if (existing != nullptr)
    {
        cout << "⚠️  Cliente '" << name << " " << surname
             << " " << birthDate << "' già presente (ID " << existing->id << ").\n";
        return;
    }

    cout << "Inserisci email: ";
    cin >> email;

    cout << "Inserisci telefono: ";
    cin >> phone;

    Client c(name, surname, birthDate, email, phone);
    crm.clients.push_back(c);

    cout << "✅ Cliente creato con ID " << c.id << "\n";
}

void uiViewClients(const CrmData &crm)
{
    cout << "📋 Lista clienti (" << crm.clients.size() << "):" << endl;

    if (crm.clients.empty())
    {
        cout << "   (nessun cliente registrato)\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(crm.clients.size()); i++)
    {
        const Client &c = crm.clients[i]; // take element by index
        cout << " 👤 ID: " << c.id
             << " | Nome e Cognome: " << c.name << " " << c.surname
             << " | Email: " << c.email
             << " | Telefono: " << c.phone
             << "\n";
    }
}

void uiEditClient(CrmData &crm)
{
    cout << "✏️  Modifica cliente\n";

    // 1) Find the client (reuses your helper; prints the found record)
    Client *found = uiSearchClient(crm);
    if (!found)
        return;

    // 2) Confirm
    cout << "Confermi modifica di questo cliente? [Y/N]: ";
    string answer;
    std::getline(cin, answer);
    char ch = answer.length() == 1 ? (std::toupper(answer[0])) : 'N';

    if (ch != 'Y')
    {
        cout << "↩️  Nessuna modifica.\n";
        return;
    }

    // 3) Prompt new values; Enter keeps old
    string name, surname, birthDate, email, phone;

    cout << "Inserisci nuovi valori (premi ENTER per mantenere il valore attuale):\n";
    cout << "Nome [" << found->name << "]: ";
    std::getline(cin >> std::ws, name);
    if (name.empty())
        name = found->name;

    cout << "Cognome [" << found->surname << "]: ";
    std::getline(cin, surname);
    if (surname.empty())
        surname = found->surname;

    cout << "Data di nascita (YYYY-MM-DD) [" << found->birthDate << "]: ";
    std::getline(cin, birthDate);
    if (birthDate.empty())
        birthDate = found->birthDate;

    cout << "Email [" << found->email << "]: ";
    std::getline(cin, email);
    if (email.empty())
        email = found->email;

    cout << "Telefono [" << found->phone << "]: ";
    std::getline(cin, phone);
    if (phone.empty())
        phone = found->phone;

    // 4) Apply update through CrmData (by ID)
    const int id = found->id; // cache before any potential vector reallocation
    const bool ok = crm.updateClientById(id, name, surname, birthDate, email, phone);

    if (ok)
    {
        cout << "✅ Cliente aggiornato: ID=" << id
             << " | " << name << " " << surname
             << " | Email=" << email
             << " | Telefono=" << phone << "\n";
    }
    else
    {
        cout << "⚠️  Aggiornamento fallito: cliente non trovato.\n";
    }
}

void uiDeleteClient(CrmData &crm)
{
    string answer;
    bool removed = false;

    cout << "👉 Eliminazione cliente...\n";
    Client *found = uiSearchClient(crm);
    if (!found)
        return; // nothing to delete

    cout << "Confermi eliminazione? [Y/N]: ";
    getline(cin, answer);
    char ch = answer.length() == 1 ? (std::toupper(answer[0])) : 'N';

    if (ch != 'Y')
    {
        cout << "↩️  Nessuna modifica.\n";
        return;
    }

    // Keep IDs/names before erasing (pointer will be invalidated after erase)
    const int targetId = found->id;
    const string fullName = found->name + " " + found->surname;

    removed = crm.deleteClientAndCascade(targetId);

    if (removed)
    {
        cout << "✅ Cliente \"" << fullName << "\" (ID " << targetId << ") eliminato insieme alle sue interazioni.\n";
    }
    else
    {
        cout << "⚠️  Qualcosa è andato storto: cliente non trovato al momento dell’eliminazione.\n";
    }
}

Client *uiSearchClient(CrmData &crm)
{
    cout << "🔎 Ricerca cliente\n";

    string name, surname, birthDate;

    cout << "Nome: ";
    getline(cin >> std::ws, name); // Use std::ws to consume any leftover newline

    cout << "Cognome: ";
    getline(cin, surname);

    cout << "Data di nascita (YYYY-MM-DD): ";
    getline(cin, birthDate);

    Client *found = crm.searchClient(name, surname, birthDate);
    if (found)
    {
        cout << "✅ Trovato: ID=" << found->id
             << " | Nome=" << found->name << " " << found->surname
             << " | Email=" << found->email
             << " | Telefono=" << found->phone << "\n";
    }
    else
    {
        cout << "❌ Nessun cliente trovato con: "
             << name << " " << surname << " " << birthDate << "\n";
    }

    return found;
}
void uiManageInteractions(CrmData &) { cout << "👉 [Mock] Gestione interazioni...\n"; }