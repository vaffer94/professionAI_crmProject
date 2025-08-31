#include <iostream>
#include <string>
#include <limits>
#include "ui.h"

using std::cin;
using std::cout;
using std::endl;
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
    cout << "👉 [Mock] Creazione cliente...\n";
    string name, surname, birthDate, email, phone;

    cout << "Inserisci nome: ";
    cin >> name;

    cout << "Inserisci cognome: ";
    cin >> surname;

    // 🔎 Call CrmData search here
    Client *existing = crm.searchClient(name, surname);
    if (existing != nullptr)
    {
        cout << "⚠️  Cliente con cognome e nome '" << surname << " " << name
             << "' già presente (ID " << existing->id << ").\n";
        return;
    }

    // Continue asking fields only if not found
    cout << "Inserisci data di nascita (YYYY-MM-DD): ";
    cin >> birthDate;
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
    cout << "👉 [Mock] Lista clienti...\n";
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
void uiEditClient(CrmData &) { cout << "👉 [Mock] Modifica cliente...\n"; }
void uiDeleteClient(CrmData &) { cout << "👉 [Mock] Eliminazione cliente...\n"; }
void uiSearchClient(const CrmData &) { cout << "👉 [Mock] Ricerca cliente...\n"; }
void uiManageInteractions(CrmData &) { cout << "👉 [Mock] Gestione interazioni...\n"; }