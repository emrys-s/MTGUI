#include "configuration.h"

int getIp();
int getPort(int*);
int getUsername(char*);

int connectionData::importFromFile()
{
    return 0;
}

int connectionData::exportToFile()
{
    return 0;
}

int connectionData::setIp(char* newIp)
{
    //here should be some check
    //and strcpy to Ip string after that
    return 0;
}

int connectionData::setPort(int newPort)
{
    port = newPort;
    return 0;
}

int connectionData::setUsername(char* newUsername)
{
    //here should be some check
    //and strcpy to Ip string after that
    return 0;
}

int connectionData::getIp(char* currentIp)
{
    //again some checks and then strcpy from ip to currentIp
    return 0;
}

int connectionData::getPort(int * pPort)
{
    *pPort = port;
    return 0;
}

int connectionData::getUsername(char* currentUsername)
{
    //again some checks and then strcpy from username to currentUsername
    return 0;
}
