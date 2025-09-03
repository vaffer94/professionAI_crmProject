#ifndef UI_H
#define UI_H

#include "../data/CrmData.h"

// Show the splash screen
void showSplashScreen();

// Show the menu
void showMainMenu(CrmData &crm);

void uiCreateClient(CrmData &crm);
void uiViewClients(const CrmData &crm);
void uiEditClient(CrmData &crm);
void uiDeleteClient(CrmData &crm);
Client *uiSearchClient(CrmData &crm);
void uiManageInteractions(CrmData &crm);
void uiAddInteraction(CrmData &crm, Client &client);
void uiViewInteractionsForClient(const CrmData &crm, const Client &client);
void uiSearchInteractionsForClient(const CrmData &crm, const Client &client);
void uiLoadData(CrmData &crm);
void uiSaveData(const CrmData &crm);

#endif
