#include "server/server.h"
#include "sysmsg.hpp"

int main(int argc, char *argv[]) {
    Server s;

    s.RunServer();

    return 0;
}
