/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

// the recursive implementation seems to run out of stack :(
// so we'll use iteration
bool
search (int value, int values[], int n)
{
  int low = n - n, high = n - 1;

  while (low <= high)
    {
      int mid = low + (high - low) / 2;

      // edge case found value
      if (values[mid] == value)
        return true;
      else if (values[mid] < value)
        low = mid + 1;
      else
        high = mid - 1;
    }

  return false;
}

/**
 * Sorts array of n values.
 */
void
sort (int* values, int n)
{
  int i = 0, j = 0;

  while (i < n - 1.)
    {
      // set index of smallest element. on the first
      // iteration we just pick element at index 0.
      // min keeps track of the index of smallest
      // element we've seen so far.
      int min = i;
      // set current index of inner loop to one past
      // current index of outer loop
      j = i + 1;
      while (j < n)
        {
          // if value of index j is smaller than value
          // of index min then set index min to j
          if (values[j] < values[min])
            min = j;
          // go to next index
          j++;
        }
      // now that inner loop has passed over all elements
      // if index min is not index i, then swap elements
      if (min != i)
        {
          int tmp = values[i];
          values[i] = values[min];
          values[min] = tmp;
        }
      i++;
    }
  return;
}
