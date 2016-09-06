#include <stdlib.h>
#include <assert.h>

/* Returns an integer in ther range [0, n).
 *
 * Uses rand(), and so is affected by/affects the same seed.
 */

int randint (int n)
{
  if((n-1) == RAND_MAX)
  {
    return rand();
  }
  else
  {
    long end = RAND_MAX/n;
    assert(end>0L);
    end *= n;

    int r;
    while((r = rand())>= end);
    return r%n;
  }
}
