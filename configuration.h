#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define IP_LENGTH 15
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define INTERFACE_LENGTH 50

class connectionData
{
public:
    int importFromFile();
    int exportToFile();
    int setIp(char*);
    int setPort(int);
    int setUsername(char*);
    int getIp(char*);
    int getPort(int*);
    int getUsername(char*);

private:
    char ip[IP_LENGTH];
    int port;
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char interface[INTERFACE_LENGTH];
};

#endif // CONFIGURATION_H
