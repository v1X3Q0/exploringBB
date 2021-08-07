#include <stdlib.h>

int openEbbchar(int* fd);
int meatyEbbchar(int fd);
int kSeek(int fd, size_t dst);
int kRead(int fd, void* buf, size_t len, size_t offset);
void dumpMem(unsigned char* base, size_t len);
