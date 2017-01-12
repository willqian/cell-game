#include "cell.h"
#include "drawer.h"
#include "common.h"
#include <pthread.h>


/********************************************************
 *  
 * cellObject
 *
 ********************************************************/
cellObject *initCellObject(postion pos, aliveRuleFunc aliveRule)
{
    cellObject *o = (cellObject *)malloc(sizeof(*o));
    if (NULL == o) {
        ERR("malloc error\n");
        goto error;
    }
    setCellObjectPostion(o, pos);
    setCellInitStatus(o);
    o->aliveRule = aliveRule;
    
    return o;

error:
    return NULL;
}

void uninitCellObject(cellObject **po)
{
    free(*po);
    *po = NULL;
}

void setCellInitStatus(cellObject *o)
{
    int r = rand();
    if ((r % 10) >= 5) {
        o->status = ALIVE;
    } else {
        o->status = DEAD;
    }
}

void setCellObjectPostion(cellObject *o, postion pos)
{
    o->pos.x = pos.x;
    o->pos.y = pos.y;
}

eCellStatus beCellObjectAlive(cellObject *o)
{
    return o->status;
}

void setCellObjectAlive(cellObject *o)
{
    o->status = ALIVE;
}

void setCellObjectDead(cellObject *o)
{
    o->status = DEAD;
}

/********************************************************
 *  
 * cellWorld
 *
 ********************************************************/
cellWorld *initCellWorld(aliveRuleFunc aliveRule)
{
    int x = 0, y = 0;
    postion pos;
    cellWorld *w = (cellWorld *)malloc(sizeof(*w));
    if (NULL == w) {
        ERR("malloc error\n");
        goto error;
    }
    w->running = STOP;
    for (x = 0; x < (int)CELL_WORLD_SIZE; x ++) {
        for (y = 0; y < (int)CELL_WORLD_SIZE; y ++) {
            if ((x >= 0 && x < (int)MARGIN_SIZE)  
                || (y >= 0 && y < (int)MARGIN_SIZE) 
                || (x > (int)(CELL_WORLD_SIZE - MARGIN_SIZE - 1) 
                    && x < (int)CELL_WORLD_SIZE) 
                || (y > (int)(CELL_WORLD_SIZE - MARGIN_SIZE - 1) 
                    && y < (int)CELL_WORLD_SIZE)) {
                w->cell[x][y] = NULL;
                //PRT("NULL cell, [%d, %d]\n", x, y);
            } else {
                pos.x = x;
                pos.y = y;
                w->cell[x][y] = initCellObject(pos, aliveRule);
                //PRT("cell object, [%d, %d] %s\n", x, y, w->cell[x][y]->status ? "ALIVE" : "DEAD");
                if (NULL == w->cell[x][y]) {
                    ERR("malloc error\n");
                    uninitCellWorld(&w);
                    goto error;
                }
            }
        }
    }
    PRT("initCellWorld OK\n");
    return w;

error:
    return NULL;
}

void uninitCellWorld(cellWorld **pw)
{
    int x = 0, y = 0;

    for (x = 0; x < (int)CELL_WORLD_SIZE; x ++) {
        for (y = 0; y < (int)CELL_WORLD_SIZE; y ++) {
            if (NULL != (*pw)->cell[x][y]) {
                uninitCellObject(&((*pw)->cell[x][y]));
            }
        }
    }
    free(*pw);
    *pw = NULL;
    return;
}

void runThread(cellWorld *w, threadObject *o)
{
    pthread_create(&(o->id), NULL, cellWorldMainLoop, (void *)w);
}

void joinThread(cellWorld *w, threadObject *o)
{
    pthread_join(o->id, &(o->returnStatus));
    PRT("Return value is %d\n", (int)(o->returnStatus));
}

void startCellWorld(cellWorld *w)
{
    w->running = RUN;
    runThread(w, &(w->mainloop));
    return;    
}

void stopCellWorld(cellWorld *w)
{
    w->running = STOP;
    joinThread(w, &(w->mainloop));
    return;
}

int beCellAlive(cellWorld *w, postion pos)
{
    PRT("Check postion [%d, %d]\n", pos.x, pos.y);
    if (NULL == w->cell[pos.x][pos.y]) {
        return -1;
    }
    return beCellObjectAlive(w->cell[pos.x][pos.y]);
}

int updateCellWorld(cellWorld *w)
{
    int x = 0, y = 0;
    for (x = 0; x < (int)CELL_WORLD_SIZE; x ++) {
        for (y = 0; y < (int)CELL_WORLD_SIZE; y ++) {
            if (NULL != w->cell[x][y]) {
                //PRT("update cell [%d, %d]\n", x, y);
                w->cell[x][y]->aliveRule(w->cell[x][y], w);
            }
        }
    }
    return 0;
}

static int cellWorldGetPixel(void *w, int x, int y)
{
    cellWorld *cw = (cellWorld *)w;
    if (NULL == cw->cell[x][y]) {
        return -1;
    }
    return (int)(cw->cell[x][y]->status);
}

void *cellWorldMainLoop(void *w)
{
    cellWorld *cw = (cellWorld *)w;
    while (RUN == cw->running) {
        //PRT("Running!\n");
        drawMap((void *)cw, CELL_WORLD_SIZE, CELL_WORLD_SIZE, cellWorldGetPixel);
        updateCellWorld(cw);
        sleep(2);
        RESET_DRAWER(CELL_WORLD_SIZE, CELL_WORLD_SIZE);
    }
    OUT_DRAWER(CELL_WORLD_SIZE, CELL_WORLD_SIZE);
    PRT("Stop now!\n");
    return 0;
}
