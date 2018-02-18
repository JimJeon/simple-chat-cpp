#include "sysmsg.h"

void DieWithErrorMsg(const char* errmsg) {
    fputs(errmsg, stderr);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}
