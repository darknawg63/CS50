/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
  // ensure proper usage
  if (argc != 2)
    {
      printf("Usage: fifteen d\n");
      return 1;
    }

  // ensure valid dimensions
  d = atoi(argv[1]);
  if (d < DIM_MIN || d > DIM_MAX)
    {
      printf("Board must be between %i x %i and %i x %i, inclusive.\n",
             DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
      return 2;
    }

  // open log
  FILE* file = fopen("log.txt", "w");
  if (file == NULL)
    {
      return 3;
    }

  // greet user with instructions
  //greet();

  // initialize the board
  init();

  // draw the current state of the board
  draw();
  // close log
  fclose(file);

  // success
  return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
  printf("\033[2J");
  printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
  clear();
  printf("WELCOME TO GAME OF FIFTEEN\n");
  usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
  // TODO
  int i, j, count = d * d;

  for (i = 0; i < d; i++)
    for (j = 0; j < d; j++)
      {
        if (count - 1 == 2 && d % 2 == 0)
          board[i][j] = count - 1 - 1;
        else if (count - 1 == 1 && d % 2 == 0)
          board[i][j] = count - 1 + 1;
        else
          board[i][j] = count - 1;
        count -= 1;
      }
  return;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
  // TODO
  puts("");
  int i, j;

  for (i = 0; i < d; i++)
    {
      for (j = 0; j < d; j++)
        {
          // where ever the value is 0, show an underscore :)
          if (board[i][j] == 0)
            printf("  _ ");
          else
            printf(" %2d  ", board[i][j]);
        }
      printf("\n\n");
    }
  return;

}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
  // TODO
  return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
  // TODO
  return false;
}
