#include "client/client.h"

#include <cstdio>

Client::Client(const string name, const string ip, const int port)
  : username_(name),
    BUFSIZE(200)
{
    // TODO: error handling
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
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

    // TODO: error handling
    if (connect(socket_, (struct sockaddr*)&ip4addr, sizeof(ip4addr)) < 0) {
        fprintf(stderr, "connection failed\n");
    }
    char serv_name[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ip4addr.sin_addr.s_addr, serv_name, sizeof(serv_name));

    fprintf(stderr, "Connected to %s/%d\n", serv_name, ntohs(ip4addr.sin_port));
}

void Client::SendMsg(const string& msg) const {
    ssize_t num_bytes_sent = send(socket_, msg.c_str(), msg.length(), 0);
    if(num_bytes_sent < 0) {
        fprintf(stderr, "message send failed\n");
    }
}

string Client::RecvServerMsg() {
    ssize_t recieved;
    char buf[BUFSIZE];
    recieved = recv(socket_, buf, BUFSIZE, 0);

    return string(buf);
}
