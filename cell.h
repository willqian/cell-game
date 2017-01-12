#ifndef cell_h
#define cell_h

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MARGIN_SIZE 1
#define CELL_WORLD_SIZE 32 /* ((MARGIN_SIZE) * 2 + 30) */

/********************************************************
 *  
 * cellObject
 *
 ********************************************************/
typedef enum eCellStatus {
    DEAD = 0,
    ALIVE = 1,
} eCellStatus;

typedef struct postion {
    int x;
    int y;
} postion;

typedef void (*aliveRuleFunc)(void *o, void *w);

typedef struct cellObject {
    eCellStatus status;
    postion pos;
    aliveRuleFunc aliveRule;
} cellObject;

cellObject *initCellObject(postion pos, aliveRuleFunc aliveRule);
void uninitCellObject(cellObject **po);
void setCellInitStatus(cellObject *o);
void setCellObjectPostion(cellObject *o, postion pos);
eCellStatus beCellObjectAlive(cellObject *o);
void setCellObjectAlive(cellObject *o);
void setCellObjectDead(cellObject *o);


/********************************************************
 *  
 * cellWorld
 *
 ********************************************************/
typedef enum eWorldStatus {
    STOP = 0,
    RUN = 1,
} eWorldStatus;

/* Thread function type */
typedef void *(*runThreadFunc)(void *arg);

/* The thread object */
typedef struct threadObject {
    pthread_t id;
    runThreadFunc runThread;
    void *returnStatus;
} threadObject;  

typedef struct cellWorld {
    cellObject* cell[CELL_WORLD_SIZE][CELL_WORLD_SIZE];
    eWorldStatus running;  
    threadObject mainloop;
} cellWorld;

cellWorld *initCellWorld();
void uninitCellWorld(cellWorld **pw);
void startCellWorld(cellWorld *w);
void stopCellWorld(cellWorld *w);
int beCellAlive(cellWorld *w, postion pos);
int updateCellWorld(cellWorld *w);
void *cellWorldMainLoop(void *w);

#endif /* cell_h */
