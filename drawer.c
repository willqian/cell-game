#include "drawer.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void drawMap(void *p, int sizeX, int sizeY, getPixelFunc getPixel)
{
    int i = 0;
    int j = 0;
    int pixel = -1;
    for (i = 0; i < sizeX; i ++) {
        for (j = 0; j < sizeY; j ++) {
            pixel = getPixel(p, i, j);
            if (-1 == pixel) {
                printf("#");
            } else if (0 == pixel) {
                printf(" ");
            } else if (1 == pixel) {
                printf("*");
            } else {
                PRT("Undefined pixel\n");    
            }
        }    
        printf("\n");
    }
}    