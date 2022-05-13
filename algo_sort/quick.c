/*--------------------------------------------------/
Filename: ./algosort/quick.c
  Auther: NekoMimi (Nekomimi-Cateye)
    Date: 2022/05/13

[Discription]
  This file is for Quick-Sort-Algorithm.
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
void swap(int*, int*);
void quick_sort_asc(int*, int, int*);

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


//This is swap function
//        argument: p1, p2
//    p1: (element)
//    p2: (element)
//  returned value: None
void swap(int* p1, int* p2)
{
  int tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}

// This is sort (asc) function (Algorithm: Quick-Sort)
//        argument: p, length
//         p: array which need to be sorted
//    length: length of p
//  returned value: None
void quick_sort_asc(int* p, int length, int* seed)
{
  int piv = random_num(seed, 0, length);
  swap(p+piv, p);
  int num_r = 0;
  int num_n = 1;
  int num_l = 0;
  for(int i=1; i<length; i++)
  {
    if (*(p+i)==*(p))
    {
      swap(p+num_n, p+i);
      num_n++;
    }
  }
  while(num_l+num_n+num_r < length)
  {
    if (*(p+num_n+num_l)<*(p))
    {
      num_l++;
    }
    else
    {
      swap(p+length-num_r-1, p+num_n+num_l);
      num_r++;
    }
  }
  for(int i=0; i<num_n; i++)
  {
    swap(p+num_n+num_l-1-i, p+i);
  }
  if (num_l > 1)
  {
    quick_sort_asc(p, num_l, seed);
  }
  if (num_r > 1)
  {
    quick_sort_asc(p+num_l+num_n, num_r, seed);
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
  quick_sort_asc(arr_sort, L, &seed);

  /* Display result */
  display_list(arr_sort, L, 1, 1);

  /* Free memory */
  free(arr_org);
  free(arr_sort);
  /* Return code */
  return 0;
}