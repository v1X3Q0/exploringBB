#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "ebbchar.h"
#include "krw.h"

int getStartEnd(size_t* start, size_t* end)
{
    char readBuf[0x100] = {0};
    char addrAscii[0x10] = {0};
    FILE* kallsymFd = 0;
    int result = -1;

    *start = 0;
    *end = 0;

    kallsymFd = fopen("/proc/kallsyms", "r"); // Open the device with read/write access
    FAIL_IF(kallsymFd < 0);
    // if (kallsymFd < 0)
    // {
    //     perror("Failed to open kallsyms...");
    //     return errno;
    // }

    while (fgets(readBuf, sizeof(readBuf), kallsymFd))
    {
        // printf("%s", readBuf);
        if (strstr(readBuf, " _stext\n"))
        {
            memcpy(addrAscii, readBuf, 8);
            *start = strtoul(addrAscii, NULL, 0x10);
            // printf("found start 0x%08lx", *start);
        }
        else if (strstr(readBuf, " _etext\n"))
        {
            memcpy(addrAscii, readBuf, 8);
            *end = strtoul(addrAscii, NULL, 0x10);            
            // printf("found end 0x%08lx", *end);
        }
        if ((*start != 0) && (*end != 0))
        {
            break;
        }
    }
    result = 0;
fail:
    SAFE_FCLOSE(kallsymFd);

    return result;
}

int main(int argc, char** argv)
{
    char readBuf[KBUF_SIZE] = {0};
    int fd = 0;
    size_t start = 0;
    size_t end = 0;
    size_t i = 0;
    char* vmlinuxBuf = 0;
    int result = -1;
    FILE* outFIle = 0;

    if (argc < 2)
    {
        printf("usage: %s outFilePath", argv[0]);
        goto fail;
    }

    outFIle = fopen(argv[1], "w");
    FAIL_IF(outFIle == 0);

    FAIL_IF(openEbbchar(&fd) != 0);

    printf("beginning fetch\n");
    FAIL_IF(getStartEnd(&start, &end) != 0);

    printf("found start at 0x%08lx end at 0x%08lx\n", start, end);
    vmlinuxBuf = (char*)calloc(end - start, 1);
    FAIL_IF(vmlinuxBuf == 0);

    for (i = start; i < end; i+=KBUF_SIZE)
    {
        printf("getting offset 0x%08lx\n", i);
        kRead(fd, readBuf, KBUF_SIZE, i);
        memcpy(&vmlinuxBuf[i - start], readBuf, KBUF_SIZE);
        
        // sleep(1);
    }

    printf("finished reading\n");
    fwrite(vmlinuxBuf, 1, end - start, outFIle);

    result = 0;
fail:
    SAFE_FCLOSE(outFIle);
    SAFE_FREE(vmlinuxBuf);
    return result;
}