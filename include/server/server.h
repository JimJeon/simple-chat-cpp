#ifndef CPP_CHAT_SERVER_H
#define CPP_CHAT_SERVER_H

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <thread>
#include <vector>

#include "sysmsg.h"

using namespace std;

class Server {
public:
    Server();
    virtual ~Server();

    void RunServer();
    void HandleClient(int clntsock);
    void HandlePackets();
    int Accept();

private:
    vector<int> clients_;
    int socket_;

    static const int MAXPENDING = 5;
    static const int BUFSIZE = 1024;
};

#endif//CPP_CHAT_SERVER_H
