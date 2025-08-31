#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
using std::string;

enum class InteractionType
{
    Unknown = 0,
    Appointment,
    Contract
};

enum class InteractionStatus
{
    ToDo = 0,
    InProgress,
    Done,
    Cancelled
};

class Interaction
{
public:
    // Fields
    int id;
    int clientId;
    InteractionType type;
    InteractionStatus status;
    string date;        // "YYYY-MM-DD"
    string responsible; // employee handling the interaction
    string note;

    // Constructors (declared; defined in .cpp)
    Interaction(); // default
    Interaction(int clientId, InteractionType type, InteractionStatus status,
                const string &date,
                const string &responsible,
                const string &note); // value ctor

private:
    static int generateUniqueId(); // timestamp + counter
};

#endif
