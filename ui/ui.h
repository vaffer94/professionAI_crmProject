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
void uiSearchClient(const CrmData &crm);
void uiManageInteractions(CrmData &crm);

#endif
