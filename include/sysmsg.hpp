#ifndef CPP_CHAT_SYSMSG_H
#define CPP_CHAT_SYSMSG_H

#include <cstdio>
#include <cstdlib>

void DieWithErrorMsg(const char* errmsg) {
    fputs(errmsg, stderr);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}

#endif//CPP_CHAT_SYSMSG_H
