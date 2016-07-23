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
#define RIGHT 1
#define LEFT 3
#define UP 2
#define DOWN 4
#define VACANT 0


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
void locate(int* y, int* x, int n);
bool shift(int* y, int* x, int vector);

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
  greet();

  // initialize the board
  init();

  // accept moves until game is won
  while (true)
    {
      // clear the screen
      clear();

      // draw the current state of the board
      draw();

      // log the current state of the board (for testing)
      for (int i = 0; i < d; i++)
        {
          for (int j = 0; j < d; j++)
            {
              fprintf(file, "%i", board[i][j]);
              if (j < d - 1)
                {
                  fprintf(file, "|");
                }
            }
          fprintf(file, "\n");
        }
      fflush(file);

      // check for win
      if (won())
        {
          printf("ftw!\n");
          break;
        }

      // prompt for move
      printf("Tile to move: ");
      int tile = GetInt();

      // quit if user inputs 0 (for testing)
      if (tile == 0)
        {
          break;
        }

      // log move (for testing)
      fprintf(file, "%i\n", tile);
      fflush(file);

      // move if possible, else report illegality
      if (!move(tile))
        {
          printf("\nIllegal move.\n");
          usleep(500000);
        }

      // sleep thread for animation's sake
      usleep(500000);
    }

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
        // We want to switch the order of number 1 and 2 when there
        // is an odd number of tiles (when d is even)
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
            printf("  _  ");
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
  int i, j;

  locate(&i, &j, tile);

  if(shift(&i, &j, RIGHT))
    return true;
  if(shift(&i, &j, LEFT))
    return true;
  if(shift(&i, &j, UP))
    return true;
  if(shift(&i, &j, DOWN))
    return true;

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

void
locate (int* y, int* x, int n)
{
  for (int i = 0; i < d; i++)
    for (int j = 0; j < d; j++)
      if (board[i][j] == n)
        {
          *y = i;
          *x = j;
        }
  return;
}

bool
shift (int* y, int* x, int vector)
{
  switch (vector)
    {
      case RIGHT :
        // Go right
        if (*x + 1 < d  && board[*y][*x + 1] == 0)
          {
            board[*y][*x + 1] = board[*y][*x];
            board[*y][*x] = VACANT;
            return true;
          }
        else
          return false;
      case LEFT :
        // Go left
        if (*x - 1 >= d - d && board[*y][*x - 1] == 0)
          {
            board[*y][*x - 1] = board[*y][*x];
            board[*y][*x] = VACANT;
            return true;
          }
        else
          return false;
      case UP :
        // Go up
        if (*y - 1 >= d - d && board[*y - 1][*x] == 0)
          {
            board[*y - 1][*x] = board[*y][*x];
            board[*y][*x] = VACANT;
            return true;
          }
        else
          return false;
      case DOWN :
        // Go down
        if (*y + 1 < d && board[*y + 1][*x] == 0)
          {
            board[*y + 1][*x] = board[*y][*x];
            board[*y][*x] = VACANT;
            return true;
          }
        else
          return false;
    }

  return false;
}
