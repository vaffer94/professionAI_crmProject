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
    Client();

    // Value constructor (generates ID automatically)
    Client(const string &n,
           const string &s,
           const string &b,
           const string &e,
           const string &p);

private:
    static int generateUniqueId();
};

#endif
