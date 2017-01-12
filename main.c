#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "cell.h"
#include "common.h"

void aliveRule(void *o, void *w)
{
    cellObject *co = (cellObject *)o;
    cellWorld *cw = (cellWorld *)w;
    int count = 0;
    //PRT("Alive rule coming!\n");
    if (NULL != cw->cell[co->pos.x - 1][co->pos.y]
        && ALIVE == cw->cell[co->pos.x - 1][co->pos.y]->status) {
        count ++;
    }
    if (NULL != cw->cell[co->pos.x + 1][co->pos.y]
        && ALIVE == cw->cell[co->pos.x + 1][co->pos.y]->status) {
        count ++;
    }
    if (NULL != cw->cell[co->pos.x][co->pos.y - 1]
        && ALIVE == cw->cell[co->pos.x][co->pos.y - 1]->status) {
        count ++;
    }    
    if (NULL != cw->cell[co->pos.x][co->pos.y + 1]
        && ALIVE == cw->cell[co->pos.x][co->pos.y + 1]->status) {
        count ++;
    }  
    if (NULL != cw->cell[co->pos.x - 1][co->pos.y + 1]
        && ALIVE == cw->cell[co->pos.x - 1][co->pos.y + 1]->status) {
        count ++;
    }  
    if (NULL != cw->cell[co->pos.x + 1][co->pos.y + 1]
        && ALIVE == cw->cell[co->pos.x + 1][co->pos.y + 1]->status) {
        count ++;
    }  
    if (NULL != cw->cell[co->pos.x - 1][co->pos.y - 1]
        && ALIVE == cw->cell[co->pos.x - 1][co->pos.y - 1]->status) {
        count ++;
    }  
    if (NULL != cw->cell[co->pos.x + 1][co->pos.y - 1]
        && ALIVE == cw->cell[co->pos.x + 1][co->pos.y - 1]->status) {
        count ++;
    }      

    if (DEAD == co->status && 3 == count) {
        co->status = ALIVE;
    }
    if (ALIVE == co->status && count < 2) {
        co->status = DEAD;
    }
    if (ALIVE == co->status && (2 == count || 3 == count)) {
        co->status = ALIVE;
    }    
    if (ALIVE == co->status && count > 3) {
        co->status = DEAD;
    }
    //PRT("Alive rule out!\n");
}

int main(int argc, char *argv[])
{
    cellWorld *w = initCellWorld(aliveRule);
    if (NULL == w) {
        printf("Init cell world error\n");
        return -1;
    }
    startCellWorld(w);
    sleep(1000);
    stopCellWorld(w);
    uninitCellWorld(&w);
    return 0;
}