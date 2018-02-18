#ifndef CPP_CHAT_SERVER_H
#define CPP_CHAT_SERVER_H

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <string>
#include <cstring>

#include "sysmsg.hpp"

using namespace std;

class Server {
protected:
    void HandleTCPClient(int socket);

public:
    Server();
    virtual ~Server();

    void RunServer();

private:
    int socket_;
    const int MAXPENDING;
    const int BUFSIZE;
};

#endif//CPP_CHAT_SERVER_H
