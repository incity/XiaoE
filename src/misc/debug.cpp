#include "debug.h"

void hexdump(void *_data, unsigned len)
{
    unsigned char *data = (unsigned char *)_data;
    unsigned count;

    for (count = 0; count < len; count++) {
        if ((count & 15) == 0)
            fprintf(stderr,"%04x:", count);
        fprintf(stderr," %02x %c", *data,
                (*data < 32) || (*data > 126) ? '.' : *data);
        data++;
        if ((count & 15) == 15)
            fprintf(stderr,"\n");
    }
    if ((count & 15) != 0)
        fprintf(stderr,"\n");
}

