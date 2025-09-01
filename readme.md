# 🏢 InsuraPro CRM Console App

Welcome to **InsuraPro Solutions CRM** 🎉  
This is a simple **console-based Customer Relationship Management system** written in **C++**.  
It helps insurance companies manage **clients** 👤 and their **interactions** 🤝 (appointments, contracts, etc.).

## ✨ Features

- 👤 **Clients**

  - Add new clients ➕
  - View all clients 📋
  - Edit client info ✏️
  - Delete clients 🗑️
  - Search clients 🔎

- 🤝 **Interactions**

  - Add an interaction (appointment or contract) ➕
  - View interactions for a client 📅
  - Search interactions 🔎
  - Status tracking: ✅ Done, 🔄 In Progress, ❌ Cancelled, 🕒 To Do

- 💾 **Data persistence**
  - Save all data to **CSV files**
  - Load data automatically at startup

## 🛠️ Requirements

- A **C++17** compiler (tested with `g++`/`clang++`).
- Makefile support (`make` command).

## 🚀 How to Build

```bash
# Clone the repo
git clone https://github.com/yourname/insurapro-crm.git
cd insurapro-crm

# Build and run the app
make run


fast-cpp-csv-parser
```

The binary will be created in build/insurapro

## 📂 Project Structure

```bash
.
├── main.cpp             # Entry point
├── data/
│   ├── Client.h         # Client class
│   ├── Interaction.h    # Interaction class
│   ├── CrmData.h/.cpp   # Manages all clients & interactions
├── ui/
│   ├── ui.h/.cpp        # User interface (menus, input/output)
├── third_party/
│   └── csv.h            # CSV parser library
├── Makefile             # Build system
└── README.md            # This file 📖

```

## 📊 Data Files

Data is stored in CSV files:

clients.csv

```
id,name,surname,birthDate,email,phone
101,Mario,Rossi,1980-05-22,mario.rossi@email.com,3331234567
```

interactions.csv

```
id,clientId,type,status,date,responsible,note
201,101,1,4,2025-08-30,Giuseppe,"Appuntamento confermato"
```

👉 clientId links an interaction to its client.

## 🤝 Credits

Built with ❤️ and ☕ in C++.

CSV parsing powered by [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser)
.
