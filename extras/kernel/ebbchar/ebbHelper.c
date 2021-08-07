#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "ebbchar.h"

int openEbbchar(int* fd)
{
   *fd = open("/dev/ebbchar", O_RDWR); // Open the device with read/write access
   if (*fd < 0)
   {
      perror("Failed to open the device...");
      return errno;
   }

   return 0;
}

int kSeek(int fd, size_t dst)
{
   size_t seekBuf[2] = {0};
   size_t setState = SEEK_OP;

   seekBuf[0] = setState;
   seekBuf[1] = dst;

   write(fd, seekBuf, sizeof(seekBuf));
   return 0;
}

int kRead(int fd, void* buf, size_t len, size_t offset)
{
   void* newBuf = 0;
   opVals_t setState = SEEK_OP;

   // newBuf = calloc(len + sizeof(opVals_t), sizeof(char));
   kSeek(fd, offset);
   // write(fd, )
   read(fd, buf, len);
   return 0;
}

void dumpMem(unsigned char* base, size_t len)
{
   size_t i = 0;
   printf("UD: ");
   for (i = 0; i < len; i+=4)
   {
      if (((i % 0x10) == 0) && (i != 0))
      {
         printf("\n");
      }
      printf("0x%08lx ", *((unsigned int*)&base[i]));
   }
}
