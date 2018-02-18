#include "client/client.h"

#include <cstdio>

Client::Client(const string name, const string ip, const int port)
  : username_(name),
    BUFSIZE(200)
{
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0) {
        DieWithErrorMsg("socket() failed");
    }
    ConnectServer(ip, port);
}

Client::~Client() {
    CloseSocket();
}

void Client::CloseSocket() {
    close(socket_);
}

void Client::ConnectServer(const string ip, const int port) {
    struct sockaddr_in ip4addr;
    ip4addr.sin_family = AF_INET;
    ip4addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &ip4addr.sin_addr);

    if (connect(socket_, (struct sockaddr*)&ip4addr, sizeof(ip4addr)) < 0) {
        DieWithErrorMsg("connect() failed");
    }
    char serv_name[INET_ADDRSTRLEN];
    // TODO: error handling
    inet_ntop(AF_INET, &ip4addr.sin_addr.s_addr, serv_name, sizeof(serv_name));

    printf("Connected to %s/%d\n", serv_name, ntohs(ip4addr.sin_port));
}

void Client::SendMsg(const string& msg) const {
    if (send(socket_, msg.c_str(), msg.length(), 0) < 0) {
        DieWithErrorMsg("send() fail");
    }
}

string Client::RecvServerMsg() {
    char buf[BUFSIZE];
    ssize_t received = recv(socket_, buf, BUFSIZE, 0);
    if (received < 0) {
        DieWithErrorMsg("recv() failed");
    }

    return string(buf);
}
