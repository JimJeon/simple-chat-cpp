#ifndef CPP_CHAT_SYSMSG_H
#define CPP_CHAT_SYSMSG_H

#include <cstdio>
#include <cstdlib>

void DieWithErrorMsg(const char* errmsg) {
    fprintf(stderr, "%s", errmsg);
    fprintf(stderr, "\n");

    exit(EXIT_FAILURE);
}

#endif//CPP_CHAT_SYSMSG_H
