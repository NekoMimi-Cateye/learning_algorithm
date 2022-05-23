/*--------------------------------------------------/
Filename: ./algo_graph/dijkstra_norm.c
  Auther: NekoMimi (Nekomimi-Cateye)
    Date: 2022/05/23

[Discription]
  This file is for Dijkstra-Search-Algorithm for General Graph.
/--------------------------------------------------*/

// include stds
#include <stdio.h>  // standard I/O funcs
#include <stdlib.h> // standard funcs library
#include <time.h>   // use if random seed.

// constants
#define SEED_INIT 0 // default initial seed value


// functions
int random_num(unsigned int*, int, int);
void display_graph(int*, int);


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
void display_graph(int* p, int num_node)
{
  printf("x | ");
  for (int h=0; h<num_node; h++)
    printf("%c ", 'a'+h);
  printf("\n\n");
  for (int h=0; h<num_node; h++)
  {
    printf("%c | ", 'a'+h);
    for (int w=0; w<num_node; w++)
      printf("%d ", *(p+num_node*h+w));
    putchar('\n');
  }
  putchar('\n');
  fflush(stdout);
}


// This is main function
//       argument: None
// returned value: 0
int main(void)
{
  /* Decline number of nodes (user input) */
  int L;
  printf("number of nodes >>> ");
  scanf("%d", &L);

  /* Define random Graph */
  unsigned int seed;
  int seed_flag = 0;
  printf("random seed? (random: 1 / constant: other) >>> ");
  scanf("%d", &seed_flag);
  if (seed_flag == 1)
    seed = time(NULL);
  else
    seed = SEED_INIT;

  /* Create Adjacency-Matrix */
  int* adj_arr = (int*)malloc(sizeof(int)*L*L);
  for(int i=0; i<L*L; i++)
    *(adj_arr+i) = random_num(&seed, 0, 2);

  /* Create Cost-Information */
  float* cst_arr = (float*)malloc(sizeof(float)*L*L);
  for(int i=0; i<L*L; i++)
    *(cst_arr+i) = 0.01 * random_num(&seed, 1, 1001);

  /* Display array */
  display_graph(adj_arr, L);

  /* Free memory */
  free(adj_arr);
  free(cst_arr);

  /* Return code */
  return 0;
}