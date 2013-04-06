#include "gol.h"

int main()
{
  int select;
  int err=1;
  /* array of grid members */
  GridMember** memberList;
  memberList = createGridList();
  /* setting random generator */
  srand(time(NULL));
  /* create game grid members */
  while(err) {
    /* clear screen and always show title */
    displayTitle();
    /* config game options */
    configGame(&select);
    err = createGridMembers(memberList, select);
  }
  /* enter game loop */
  while(1) {
    /* clear screen and always show title */
    displayTitle();
    /* show game grid */
    showGrid(memberList);
    /* count neighbours */
    countNeighbours(memberList);
    /* update status */
    updateGrid(memberList);
    /* time tick */
    timeTick();
  }
  displayEnd();
  freeGridList(memberList);
  return 0;
}

GridMember **createGridList()
{
  int i;
  GridMember** memberList;
  memberList = (GridMember**) malloc(20*sizeof(GridMember*));
  for(i=0; i<20; i++) {
    memberList[i] = (GridMember*) malloc(20*sizeof(GridMember));
  }
  return memberList;
}

void createRandGridMembers(GridMember** memberList)
{
  int i, j;
  for(i=0; i<20; i++) {
    for(j=0; j<20; j++) {
      memberList[i][j].alive = myRand();
      memberList[i][j].no_of_neighbours = 0;
    }
  }
}

int createGridMembers(GridMember** memberList, int select)
{
  int i, j;
  for(i=0; i<20; i++) {
    for(j=0; j<20; j++) {
      memberList[i][j].alive = 0;
      memberList[i][j].no_of_neighbours = 0;
    }
  }
  switch(select)
  {
  case 0:
    createRandGridMembers(memberList);
    break;
  case 1:
    /* Blinker */
    memberList[1][3].alive = memberList[1][4].alive = memberList[1][5].alive = 1;
    break;
  case 2:
    /* Toad */
    memberList[1][3].alive = memberList[1][4].alive = memberList[1][5].alive = 1;
    memberList[2][4].alive = memberList[2][5].alive = memberList[2][6].alive = 1;
    break;
  case 3:
    /* Beacon */
    memberList[1][3].alive = memberList[1][4].alive = 1;
    memberList[2][3].alive = memberList[2][4].alive = 1;
    memberList[3][5].alive = memberList[3][6].alive = 1;
    memberList[4][5].alive = memberList[4][6].alive = 1;
    break;
  case 4:
    /* Glider */
    memberList[3][5].alive = memberList[4][5].alive = memberList[5][5].alive = 1;
    memberList[5][4].alive = 1;
    memberList[4][3].alive = 1;
    break;
  default:
    return 1;
  }
  return 0;
}

void updateGrid(GridMember** memberList)
{
  int i, j;
  int numOfNeighbours;
  int alive;
  for(i=0; i<20; i++) {
    for(j=0; j<20; j++) {
      numOfNeighbours = memberList[i][j].no_of_neighbours;
      alive = memberList[i][j].alive;
      /* rules here */
      /* 1. Each gridmember with zero or one living neighbour: dies */
      if(alive && numOfNeighbours <=1)
        memberList[i][j].alive = 0;
      /* 2. Each gridmember with two or three living neighbours: lives */
      else if(alive && (numOfNeighbours == 2 || numOfNeighbours == 3))
        memberList[i][j].alive = 1;
      /* 3. Each gridmember with four or more living neighbours: dies */
      else if(alive && numOfNeighbours >= 4)
        memberList[i][j].alive = 0;
      /* Each dead gridmember with three living neighbours becomes alive */
      else if(!alive && numOfNeighbours == 3)
        memberList[i][j].alive = 1;
      else
        ;
    }
  }
}

void countNeighbours(GridMember** memberList)
{
  int num=0;
  int row, col;
  int dr, dc;
  int n_row, n_col;
  for(row=0; row<20; row++) {
    for(col=0; col<20; col++) { 
      for(dr=-1; dr<2; dr++) {
        for(dc=-1; dc<2; dc++) {
          n_row = (row+dr+20)%20;
          n_col = (col+dc+20)%20;
          if(dr == 0 && dc == 0)
            continue;
          else if(memberList[n_row][n_col].alive) {
            num++;
          }
        }
      }
      memberList[row][col].no_of_neighbours = num;
      num=0;
    }
  }
}

void configGame(int* select)
{
  printf("Please select a pattern:\n\
      \t0. Random\n\
      \t1. Blinker\n\
      \t2. Toad\n\
      \t3. Beacon\n\
      \t4. Glider\n\n");
  printf("Selection: ");
  scanf("%d", select);
}

void displayTitle()
{
  int err;
  /* clean screen */
  err = clear();
  if(!err)
    printf("===== Game Of Life =====\n\n");
  else
    /* meet error and stop */
    errorAndStop(__FUNCTION__);
}

void displayEnd()
{
  printf("\n====== Game end, Thanks for playing ======\n\n");
}

void timeTick()
{
  sleep(1);
}

int myRand()
{
  double r;
  r = (double) rand()/RAND_MAX;
  return (r >= 0.5 ? 1 : 0);
}

void showGrid(GridMember** memberList)
{
  int i, j;
  for(i=0; i<20; i++) {
    for(j=0; j<20; j++) {
      if(memberList[i][j].alive)
        printf("* ");
      else
        printf("  ");
    }
    printf("\n");
  }
}

int clear()
{
  return system("clear");
}

void freeGridList(GridMember** memberList)
{
  int i;
  for(i=0; i<20; i++) {
    free(memberList[i]);
  }
  free(memberList);
}

void errorAndStop(const char* err)
{
  perror(err);
  exit(1);
}
