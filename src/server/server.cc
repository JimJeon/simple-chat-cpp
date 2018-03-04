#include "server/server.h"

Server::Server() {
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

Server::~Server() {
    close(socket_);
    for(auto& client : clients_) {
        close(client);
    }
}

void Server::RunServer() {
    vector<thread> threads;
    while(1) {
        Accept();
        // When a thread object goes out of scope and it is in joinable state,
        // the program is terminated with error message, terminate called without
        // an active exception.
        for (auto& client : clients_)
            threads.emplace_back(&Server::HandleClient, this, client);
    }
    for (auto& t : threads)
        t.join();
}

void Server::HandleClient(int clntsock) {
    char buf[BUFSIZE];
    ssize_t num_bytes_rcvd;
    do {
        num_bytes_rcvd = recv(clntsock, buf, BUFSIZE, 0);
        fputs("Debug point: msg received\n", stderr);
        if (num_bytes_rcvd < 0) {
            DieWithErrorMsg("recv() failed");
        }
        buf[num_bytes_rcvd] = '\0';

        // It is supposed to print string to stdout when thread is terminated.
        // It means when clients_ vector is empty.
        fputs(buf, stdout);

    } while (num_bytes_rcvd > 0);
    puts("");
}

void Server::HandlePackets() {
    char buf[BUFSIZE];
    if (clients_.empty()) return;
    for (auto& client : clients_) {
        ssize_t num_bytes_rcvd;
        do {
            num_bytes_rcvd = recv(client, buf, BUFSIZE, 0);
            fputs("Debug point: msg received\n", stderr);
            if (num_bytes_rcvd < 0) {
                DieWithErrorMsg("recv() failed");
            }
            buf[num_bytes_rcvd] = '\0';

            // It is supposed to print string to stdout when thread is terminated.
            // It means when clients_ vector is empty.
            fputs(buf, stdout);

        } while (num_bytes_rcvd > 0);
        puts("");
    }
}

int Server::Accept() {
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_len = sizeof(clnt_addr);

    int clnt_sock = accept(socket_, (struct sockaddr*) &clnt_addr, &clnt_addr_len);
    if (clnt_sock < 0) {
        DieWithErrorMsg("accept() failed");
    }

    char clnt_name[INET_ADDRSTRLEN];

    if (inet_ntop(AF_INET, &clnt_addr.sin_addr.s_addr, clnt_name, sizeof(clnt_name)) != NULL)
        printf("Handling client %s/%d\n", clnt_name, ntohs(clnt_addr.sin_port));
    else
        puts("Unable to get client address");

    clients_.emplace_back(clnt_sock);
    return 0;
}
