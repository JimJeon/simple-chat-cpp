#include "client/client.h"
#include "sysmsg.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        DieWithErrorMsg("Usage: <ip> <port>");
    }

    string name;

    cout << "Input username: ";
    cin >> name;

    Client client(name, string(argv[1]), atoi(argv[2]));

    char buf[200];
    while(1) {
        scanf("%s", buf);

        printf("msg: %s\n", buf);
        client.SendMsg(string(buf));
        printf("msg sent\n");
    }
    return 0;
}
