#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/times.h>


#ifndef ERR
#ifndef SILENT
#ifdef UBUNTU
#define ERR(fmt, args...) \
    do { \
        fprintf(stderr, "[Error at file %s, line %d, function: %s] "fmt, \
                        __FILE__, __LINE__, __func__, ##args); \
    } while(0)
#else    
#define ERR(fmt, args...) \
    do { \
        FILE *f = fopen("/dev/console", "a+"); \
        fprintf(f, "[Error at file %s, line %d, function: %s] "fmt, \
                        __FILE__, __LINE__, __func__, ##args); \
        fflush(f); \
        fclose(f); \
    } while(0)
#endif    
#else
#define ERR(fmt, args...) \
	do { } while(0)
#endif
#endif

#ifndef PRT
#ifdef DEBUG
#ifdef UBUNTU
#define PRT(fmt, args...) \
        do { \
            fprintf(stderr, "[Debug at file %s, line %d, function: %s] "fmt, \
                            __FILE__, __LINE__, __func__, ##args); \
    } while(0)
#else    
#define PRT(fmt, args...) \
        do { \
            FILE *f = fopen("/dev/console", "a+"); \
            fprintf(f, "[Debug at file %s, line %d, function: %s] "fmt, \
                            __FILE__, __LINE__, __func__, ##args); \
            fflush(f); \
            fclose(f); \
    } while(0)
#endif
#else
#define PRT(fmt, args...) \
        do { } while(0)
#endif
#endif

#endif // COMMON_H_
