#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
using std::string;

enum class InteractionType {
    Unknown = 0,
    Appointment,
    Contract
};

class Interaction {
public:
    // Fields
    int id;
    int clientId;
    InteractionType type;
    string date;        // e.g. "YYYY-MM-DD"
    string responsible; // employee handling the interaction
    string note;

    // Default constructor
    Interaction()
        : id(0),
          clientId(0),
          type(InteractionType::Unknown),
          date(""),
          responsible(""),
          note("") {}
};

#endif
