/*--------------------------------------------------/
Filename: ./algo_search/linear.c
  Auther: NekoMimi (Nekomimi-Cateye)
    Date: 2022/05/17

[Discription]
  This file is for Linear-Search-Algorithm.
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
int liner_num_search_first(int*, int, int);


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


// This is search (first idx / int) function (Algorithm: Linear-Search)
//        argument: p, length
//         p: array which need to be sorted
//    length: length of p
//  returned value: idx
//      idx: (no discription)
int liner_num_search_first(int* p, int length, int key)
{
  int idx = 0;
  while(idx < length)
  {
    if (*(p+idx) == key)
      return idx;
    idx ++;
  }
  return -1;
}

// This is main function
//       argument: None
// returned value: 0
int main(void)
{
  /* Decline length of array (user input) */
  int L;
  printf("Array Length >>> ");
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
  int* arr = (int*)malloc(sizeof(int)*L);

  for(int i=0; i<L; i++)
  {
    *(arr+i) = random_num(&seed, -L*L, L*L);
  }

  /* Display array */
  display_list(arr, L, 0, 1);

  /* search number */
  int idx, query;
  for(int i=0; i<10; i++)
  {
    query = *(arr+random_num(&seed, 0, L));
    idx = liner_num_search_first(arr, L, query);
    printf("NO.%d query %d -> idx %d\n", i, query, idx);
  }

  /* Free memory */
  free(arr);

  /* Return code */
  return 0;
}