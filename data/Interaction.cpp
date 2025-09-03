#include "Interaction.h"
#include <ctime>

int Interaction::generateUniqueId()
{
    return static_cast<int>(std::time(nullptr));
}

Interaction::Interaction()
    : id(0),
      clientId(0),
      type(InteractionType::Unknown),
      status(InteractionStatus::ToDo),
      date(""),
      responsible(""),
      note("") {}

Interaction::Interaction(int clientId_, InteractionType type_, InteractionStatus status_,
                         const string &date_, const string &responsible_, const string &note_)
    : id(generateUniqueId()),
      clientId(clientId_),
      type(type_),
      status(status_),
      date(date_),
      responsible(responsible_),
      note(note_) {}
