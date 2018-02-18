#ifndef CPP_CHAT_CLIENT_H
#define CPP_CHAT_CLIENT_H

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cstdio>
#include <string>

#include "sysmsg.hpp"

using namespace std;

class Client {
protected:
    void ConnectServer(const string ip, const int port);
    void CloseSocket();

public:
    Client(const string name, const string ip, const int port);
    virtual ~Client();

    void SendMsg(const string& msg) const;
    string RecvServerMsg();

private:
    int socket_;
    string username_;

    const int BUFSIZE;
};

#endif//CPP_CHAT_CLIENT_H
