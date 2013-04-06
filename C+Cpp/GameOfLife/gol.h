#ifndef GOL_H
#define GOL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>     /* sleep */

/* grid member define */
typedef struct {
  /* alive or not */
  int alive;
  /* number of neighbours */
  int no_of_neighbours;
} GridMember;

/* config game options */
void configGame(int* select);
/* display game title */
void displayTitle();
/* display end */
void displayEnd();
/* create grid list */
GridMember **createGridList();
/* create game grid members */
void createRandGridMembers(GridMember** memberList);
/* create special pattern */
int createGridMembers(GridMember** memberList, int select);
/* update status of grid members based on special rules */
void updateGrid(GridMember** memberList);
/* count neighbour of grid member */
void countNeighbours(GridMember** memberList);
/* time tick */
void timeTick();
/* generate random 0 or 1 */
int myRand();
/* display testing grid table on screen */
void showGrid(GridMember** memberList);
/* clear screen */
int clear();
/* free grid list */
void freeGridList(GridMember** memberList);
/* meet error and stop */
void errorAndStop(const char* err);

#endif