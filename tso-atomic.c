#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <stdatomic.h>
 
atomic_int x, y, tmp1, tmp2;
 
void *t0 (void *arg)
{
  x = 1;
  tmp1 = y;
  return 0;
}
 
void *t1 (void *arg)
{
  y = 1;
  tmp2 = x;
  return 0;
}
 
int main (void)
{
  while (1) {
    int res;
    pthread_t thread0, thread1;
    x = y = tmp1 = tmp2 = 0;
    res = pthread_create (&thread0, NULL, t0, NULL);
    assert (res==0);
    res = pthread_create (&thread1, NULL, t1, NULL);
    assert (res==0);
    res = pthread_join (thread0, NULL);
    assert (res==0);
    res = pthread_join (thread1, NULL);
    assert (res==0);
    printf ("%d %d\n", tmp1, tmp2);
    if (tmp1==0 && tmp2==0) break;
  }
  return 0;
}
