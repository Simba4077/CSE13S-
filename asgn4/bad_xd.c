#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define B 16
int main(int c, char **v) {
    int x = 0, s = 0, d;
    ssize_t r;
    char b[B];
    if (c > 2)
        exit(1);
    char *f = c == 2 ? v[1] : 0;
    d = (f != 0) ? open(f, O_RDONLY) : 0;
    if (d == -1)
        exit(1);
    do {
        while (x < B && (r = read(d, b + x, (size_t) (B - x))) != 0)
            x += r;
        if (x <= 0)
            break;
        printf("%08x: ", s);
        for (int i = 0; i < B; i++) {
            (i < x) ? printf("%02x", (unsigned char) b[i]) : printf("  ");
            (i & 1) == 1 ? printf(" ") : 0;
        }
        printf(" ");
        for (int i = 0; i < x; i++)
            printf("%c", isprint(b[i]) ? b[i] : '.');
        printf("\n");
        for (int i = 0; i < B - x; i++)
            b[i] = b[x + i];
        x -= B;
        s += B;
    } while (r != 0);
    close(d);
    return 0;
}
