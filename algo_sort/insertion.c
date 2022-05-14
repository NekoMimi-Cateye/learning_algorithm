/*--------------------------------------------------/
Filename: ./algosort/insertion.c
  Auther: NekoMimi (Nekomimi-Cateye)
    Date: 2022/05/14

[Discription]
  This file is for Insertion-Sort-Algorithm.
/--------------------------------------------------*/

// include stds
#include <stdio.h>  // standard I/O funcs
#include <stdlib.h> // standard funcs library
#include <time.h>   // use if random seed.

// constants
#define SEED_INIT 0 // default initial seed value

// Node for List structure
//  elements: number, next
//  number(int): number
//  after(p-node): next node
typedef struct node {
  int number;
  struct node *next; 
}node;

// functions
node* list_append(struct node*, int);

int random_num(unsigned int*, int, int);
void display_list(node*, int, int, int);
void insertion_sort_asc(/* arguments */);


// This is connection function (for list structure)
//        argument: p, number
//         p: pointer of list which'll appended element
//    number: number for save at new elements
//  returned value: (n or p)
//    (n or p): first element of list (pointer-style)
node* list_append(node* p, int number)
{
  /* Create new element */
  node* n = (node*)malloc(sizeof(node));
  n->number = number;

  /* This is last so next is NULL */
  n->next = NULL;

  /* return : first element (pointer) */
  if (p == NULL)
    return n;
  else
  {
    /* Search last element */
    node* tmp = p;
    while (tmp->next != NULL)
      tmp = tmp->next;

    /* connect last element to new element */
    tmp->next = n;
    return p;
  }
}

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
void display_list(node* p, int length, int flag_rv, int flag_nl)
{
  node *curt = p;
  if (flag_rv == 1)
    putchar('\r');
  while(curt != NULL)
  {
    printf("%+4d ", curt->number);
    curt = curt->next;
  }
  if (flag_nl == 1)
    putchar('\n');
  fflush(stdout);
}


// (TODO) This is sort (asc) function (Algorithm: Insertion-Sort)
void insertion_sort_asc(/* arguments */)
{
  /* code here */
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

  /* Create list */
  node* list = NULL;

  for(int i=0; i<L; i++)
  {
    list = list_append(list, random_num(&seed, -L*L, L*L));
  }

  /* Display orginal */
  display_list(list, L, 0, 1);

  /* (TODO) Sort array */

  /* Display result */
  display_list(list, L, 1, 1);

  /* Free memory */
  free(list);
  /* Return code */
  return 0;
}