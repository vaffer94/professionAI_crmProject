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
    string phone;
    std::vector<int> interactionIds; // IDs of this client's interactions

    // Default constructor
    Client();

    // Customized constructor
    Client(const string &n,
           const string &s,
           const string &b,
           const string &e,
           const string &p);

private:
    static int generateUniqueId();
};

#endif
