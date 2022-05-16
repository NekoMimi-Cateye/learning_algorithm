/*--------------------------------------------------/
Filename: ./algosort/heap.c
  Auther: NekoMimi (Nekomimi-Cateye)
    Date: 2022/05/16

[Discription]
  This file is for Heap-Sort-Algorithm.
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
void swap_heap(int*, int, int);
void heap_sort_asc(int*, int);

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


//This is swap_heap function
//        argument: p
//        p: array sorting
//       idx: idx of number swapping
//    length: length of p
//  returned value: new pointer of swapping number
void swap_heap(int* p, int idx, int length)
{
  if(2*idx < length)
  {
    if (*(p+idx) < *(p+2*idx))
    {
      swap(p+idx, p+2*idx);
      swap_heap(p, 2*idx, length);
    }
    if (2*idx+1 < length)
    {
      if (*(p+idx) < *(p+2*idx+1))
      {
        swap(p+idx, p+2*idx+1);
        swap_heap(p, 2*idx+1, length);
      }
    }
  }
}


// This is sort (asc) function (Algorithm: Heap-Sort)
//        argument: p, length
//         p: array which need to be sorted
//    length: length of p
//  returned value: None
void heap_sort_asc(int* p, int length)
{
  int i=0;
  int tmp;
  int child_r, child_l;
  for (int i=length/2; i>=0; i--)
  {
    swap_heap(p, i, length);
    display_list(p, length, 0, 1);
  }
  for (int i=length-1; i>0; i--)
  {
    swap(p+i, p);
    swap_heap(p, 0, i);
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
  heap_sort_asc(arr_sort, L);

  /* Display result */
  display_list(arr_sort, L, 1, 1);

  /* Free memory */
  free(arr_org);
  free(arr_sort);
  /* Return code */
  return 0;
}