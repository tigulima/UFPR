#include "util.h"
#include <stdio.h>
#include <time.h>

void format_date(time_t t, char *buffer, int max) {
    struct tm *info = localtime(&t);
    strftime(buffer, max, "%d/%m/%Y %H:%M:%S", info);
}

