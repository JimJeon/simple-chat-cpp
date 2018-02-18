#include "server/server.h"

#include <cstdio>

Server::Server()
  : MAXPENDING(5),
    BUFSIZE(200)
{
    socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_ < 0) {
        DieWithErrorMsg("socket() failed");
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8888); // echo protocol

    if (bind(socket_, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        DieWithErrorMsg("bind() failed");
    }

    if (listen(socket_, MAXPENDING) < 0) {
        DieWithErrorMsg("listen() failed");
    }

    char serv_name[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr.s_addr, serv_name, sizeof(serv_name));
    printf("Server opened at %s/%d\n", serv_name, ntohs(addr.sin_port));
}

Server::~Server() = default;

void Server::RunServer() {
    while(1) {
        struct sockaddr_in c_addr;
        socklen_t c_addr_len = sizeof(c_addr);

        int c_sock = accept(socket_, (struct sockaddr*) &c_addr, &c_addr_len);
        if (c_sock < 0) {
            DieWithErrorMsg("accept() failed");
        }

        // connected to client
        char c_name[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &c_addr.sin_addr.s_addr, c_name, sizeof(c_name)) != NULL)
            printf("Handling client %s/%d\n", c_name, ntohs(c_addr.sin_port));
        else
            puts("Unable to get client address");

        HandleTCPClient(c_sock);
    }
}

void Server::HandleTCPClient(int socket) {
    char buf[BUFSIZE];

    ssize_t num_bytes_rcvd = recv(socket, buf, BUFSIZE, 0);
    if (num_bytes_rcvd < 0) {
        DieWithErrorMsg("recv() failed");
    }

    while (num_bytes_rcvd > 0) {
        for (int i = 0; i < num_bytes_rcvd; i++) {
            printf("%c", buf[i]);
        }
        printf("\n");
        ssize_t num_bytes_sent = send(socket, buf, num_bytes_rcvd, 0);
        if (num_bytes_sent < 0) {
            DieWithErrorMsg("send() failed");
        }

        num_bytes_rcvd = recv(socket, buf, BUFSIZE, 0);
        if (num_bytes_rcvd < 0) {
            DieWithErrorMsg("recv() failed");
        }
    }
    close(socket);
}
