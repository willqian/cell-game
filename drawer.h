#ifndef drawer_h
#define drawer_h

#define BLACK_STR "\033[22;30m"
#define RED_STR "\033[22;31m"
#define GREEN_STR "\033[22;32m"
#define BROWN_STR "\033[22;33m"
#define BLUE_STR "\033[22;34m"
#define MAGENTA_STR "\033[22;35m"
#define CYAN_STR "\033[22;36m"
#define GRAY_STR "\033[22;37m"
#define DARK_STR "\033[01;30m"
#define L_RED_STR "\033[01;31m"
#define L_GREEN_STR "\033[01;32m"
#define YELLOW_STR "\033[01;33m"
#define L_BLUE_STR "\033[01;34m"
#define L_MAGENTA_STR "\033[01;35m"
#define L_CYAN_STR "\033[01;36m"
#define WHITE_STR "\033[01;37m"
#define DEFAULT_STR "\033[0m"

#define DMOVE(dir, n) \
    do { \
        printf("\033["#n#dir); \
    } while (0)
    
#define up(n)       DMOVE(A, n)
#define down(n)     DMOVE(B, n)
#define right(n)    DMOVE(C, n)
#define left(n)     DMOVE(D, n)

#define RESET_DRAWER(sizeX, sizeY) \
    do { \
        left(sizeX); \
        up(sizeY); \
    } while (0)

#define OUT_DRAWER(sizeX, sizeY) \
    do { \
        left(sizeX); \
        down(sizeY); \
    } while (0)

typedef int (*getPixelFunc)(void *o, int x, int y);

void drawMap(void *p, int sizeX, int sizeY, getPixelFunc getPixel);

#endif /* drawer_h */
