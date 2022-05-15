/*--------------------------------------------------/
Filename: ./algosort/shell.c
  Auther: NekoMimi (Nekomimi-Cateye)
    Date: 2022/05/15

[Discription]
  This file is for Shell-Sort-Algorithm.
/--------------------------------------------------*/

// include stds
#include <stdio.h>  // standard I/O funcs
#include <stdlib.h> // standard funcs library
#include <time.h>   // use if random seed.

// constants
#define SEED_INIT 0 // default initial seed value

// functions
int random_num(unsigned int*, int, int);
void display_list(int*, int, int, int);
void shell_sort_asc(int*, int);


// This is random function (Algorithm: Xorshift32)
//        argument: seed, range_min, range_max
//         seed: seed value (Don't change this value @ main, but decline there.)
//    range_min: (No discription)
//    range_max: (No discription)
//  returned value: val =[range_min, range_max)
int random_num(unsigned int* seed, int range_min, int range_max)
{
  /* Decline valiables */
  int delta, val;

  /* Update seed value */
  *seed ^= (*seed << 13);
  *seed ^= (*seed >> 17);
  *seed ^= (*seed << 15);

  /* Calc value */
  delta = range_max - range_min;
  val = range_min + (*seed % delta);

  /* Return number */
  return val;
}


// This is display function; print list to stdout
void display_list(int* p, int length, int flag_rv, int flag_nl)
{
  if (flag_rv == 1)
    putchar('\r');
  for (int i=0; i<length; i++)
    printf("%+4d ", *(p+i));
  if (flag_nl == 1)
    putchar('\n');
  fflush(stdout);
}


// This is sort (asc) function (Algorithm: Shell-Sort)
//        argument: p, length
//         p: array which need to be sorted
//    length: length of p
//  returned value: None
void shell_sort_asc(int* p, int length)
{
  /* decide initial distance */
  int dist = 1;
  int dtmp = 0;
  while(1)
  {
    dtmp = 3*dist + 1;
    if (dtmp > length)
      break;
    else
      dist = dtmp;
  }

  int tmp;
  int i, j, k;
  /* if dist_i=1 ... dist_i+1=(1-1)/3 = 0; false */
  while(dist)
  {
    for (i=dist; i<length; i++)
    {
      tmp = *(p+i);

      /* search position to insertion */
      for (j=(i%dist); j<i; j+=dist)
        if (*(p+j) > tmp)
          break;

      /* slide numbers to right */
      for (k=i; k>j; k-=dist)
      {
        *(p+k) = *(p+k-dist);
      }

      /* insertion */
      *(p+j) = tmp;
    }

    /* update dist */
    dist = (dist - 1) / 3;
  }
}

// This is main function
//       argument: None
// returned value: 0
int main(void)
{
  /* Decline length of array (user input) */
  int L;
  printf("Sort Length >>> ");
  scanf("%d", &L);

  /* Define random seed value */
  unsigned int seed;
  int seed_flag = 0;
  printf("random seed? (random: 1 / constant: other) >>> ");
  scanf("%d", &seed_flag);
  if (seed_flag == 1)
    seed = time(NULL);
  else
    seed = SEED_INIT;
  /* Create array */
  int* arr_org = (int*)malloc(sizeof(int)*L);
  int* arr_sort = (int*)malloc(sizeof(int)*L);

  for(int i=0; i<L; i++)
  {
    *(arr_org+i) = random_num(&seed, -L*L, L*L);
    *(arr_sort+i) = *(arr_org+i);
  }

  /* Display orginal */
  display_list(arr_org, L, 0, 1);

  /* Sort array */
  shell_sort_asc(arr_sort, L);

  /* Display result */
  display_list(arr_sort, L, 1, 1);

  /* Free memory */
  free(arr_org);
  free(arr_sort);
  /* Return code */
  return 0;
}