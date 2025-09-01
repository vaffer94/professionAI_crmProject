#include "Client.h"
#include <ctime> // for std::time

// Default constructor
Client::Client()
    : id(0),
      name(""),
      surname(""),
      birthDate(""),
      email(""),
      phone(""),
      interactionIds() {}

// Value constructor
Client::Client(const string &n,
               const string &s,
               const string &b,
               const string &e,
               const string &p)
    : id(generateUniqueId()),
      name(n),
      surname(s),
      birthDate(b),
      email(e),
      phone(p),
      interactionIds() {}

// Private helper
int Client::generateUniqueId()
{
    return static_cast<int>(std::time(nullptr));
}
