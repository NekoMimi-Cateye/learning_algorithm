/*--------------------------------------------------/
Filename: ./algosort/merge.c
  Auther: NekoMimi (Nekomimi-Cateye)
    Date: 2022/05/17

[Discription]
  This file is for Merge-Sort-Algorithm.
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
void merge_sort_asc(int*, int);


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


// This is sort (asc) function (Algorithm: Merge-Sort)
//        argument: p, length
//         p: array which need to be sorted
//    length: length of p
//  returned value: None
void merge_sort_asc(int* p, int length)
{
  /* Divide the array */
  int piv = length / 2;
  if (piv >= 2)
    merge_sort_asc(p, piv);
  if (length-piv >= 2)
    merge_sort_asc(p+piv, length-piv);

  /* Comparison 2 array */
  int* tmp_arr = (int *)malloc(sizeof(int)*length);
  int i = 0;
  int j = 0;
  while(i < piv && j < length-piv)
  {
    if(*(p+i) < *(p+piv+j))
    {
      *(tmp_arr+i+j) = *(p+i);
      i++;
    }
    else
    {
      *(tmp_arr+i+j) = *(p+piv+j);
      j++;
    }
  }

  /* Insert the remaining part to end of tmp */
  while (i < piv)
  {
    *(tmp_arr+i+j) = *(p+i);
    i++;
  }
  while (j < length-piv)
  {
    *(tmp_arr+i+j) = *(p+piv+j);
    j++;
  }

  /* update orginal array */
  for (i=0; i<length; i++)
    *(p+i) = *(tmp_arr+i);

  /* free tmp-array */
  free(tmp_arr);
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
  merge_sort_asc(arr_sort, L);

  /* Display result */
  display_list(arr_sort, L, 1, 1);

  /* Free memory */
  free(arr_org);
  free(arr_sort);
  /* Return code */
  return 0;
}