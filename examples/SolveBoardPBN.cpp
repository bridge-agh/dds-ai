#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dll.h"
#include "hands.h"


int main(int argc, char **argv)
{
  dealPBN dlPBN;
  futureTricks fut3;

  int target;
  int solutions;
  int mode;
  int threadIndex = 0;
  int res;
  char line[80];

  if (argc != 4)
  {
    printf("Usage: SolveBoardPBN TRUMP FIRST PBN\n");
    return 1;
  }

  const char *pbn_in = argv[3];
  int trump_in, first_in;

  if (!strcmp(argv[1], "S"))
    trump_in = 0;
  else if (!strcmp(argv[1], "H"))
    trump_in = 1;
  else if (!strcmp(argv[1], "D"))
    trump_in = 2;
  else if (!strcmp(argv[1], "C"))
    trump_in = 3;
  else if (!strcmp(argv[1], "N"))
    trump_in = 4;
  else
  {
    printf("ERR\nInvalid trump\n");
    return 1;
  }

  if (!strcmp(argv[2], "N"))
    first_in = 0;
  else if (!strcmp(argv[2], "E"))
    first_in = 1;
  else if (!strcmp(argv[2], "S"))
    first_in = 2;
  else if (!strcmp(argv[2], "W"))
    first_in = 3;
  else
  {
    printf("ERR\nInvalid first\n");
    return 1;
  }

#if defined(__linux) || defined(__APPLE__)
  SetMaxThreads(0);
#endif

  dlPBN.trump = trump_in;
  dlPBN.first = first_in;

  dlPBN.currentTrickSuit[0] = 0;
  dlPBN.currentTrickSuit[1] = 0;
  dlPBN.currentTrickSuit[2] = 0;

  dlPBN.currentTrickRank[0] = 0;
  dlPBN.currentTrickRank[1] = 0;
  dlPBN.currentTrickRank[2] = 0;

  strcpy(dlPBN.remainCards, pbn_in);

  target = -1;
  solutions = 3;
  mode = 0;
  res = SolveBoardPBN(dlPBN, target, solutions, mode, &fut3, 0);

  if (res != RETURN_NO_FAULT)
  {
    printf("ERR\n");
  }
  else
  {
    printf("OK\n");
    PrintFut(line, &fut3);
  }
}
