#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
using std::string;

class Client
{
public:
    // Fields
    int id;
    string name;
    string surname;
    string birthDate; // e.g. "YYYY-MM-DD"
    string email;
    string phone;                    // phone as string (not int!)
    std::vector<int> interactionIds; // IDs of this client's interactions

    // Default constructor
    Client()
        : id(0),
          name(""),
          surname(""),
          birthDate(""),
          email(""),
          phone(""),
          interactionIds() {}

    // Value constructor (generates ID automatically)
    Client(const string &n, const string &s, const string &b, const string &e, const string &p)
        : id(generateUniqueId()), name(n), surname(s), birthDate(b), email(e), phone(p), interactionIds() {}

private:
    static int generateUniqueId()
    {
        static int counter = 0;
        long t = static_cast<long>(std::time(nullptr)); // seconds since epoch
        return static_cast<int>(t % 1000000000) * 100 + (counter++ % 100);
    }
};

#endif
