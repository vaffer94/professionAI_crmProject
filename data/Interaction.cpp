#include "Interaction.h"
#include <ctime>

static int &interactionCounter()
{
    static int counter = 0;
    return counter;
}

int Interaction::generateUniqueId()
{
    long t = static_cast<long>(std::time(nullptr)); // seconds since epoch
    int c = (interactionCounter()++ % 100);         // 0..99 suffix
    return static_cast<int>(t % 1000000000) * 100 + c;
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
