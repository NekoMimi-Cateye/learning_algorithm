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
void display_cost(float*, int);
void path_search_dijkstra(int*, float*, float*, int, int, int);

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

// This is display function; print list to stdout
void display_cost(float* p, int num_node)
{
  printf("x |    ");
  for (int h=0; h<num_node; h++)
    printf("%c    ", 'a'+h);
  printf("\n\n");
  for (int h=0; h<num_node; h++)
  {
    printf("%c | ", 'a'+h);
    for (int w=0; w<num_node; w++)
      if (*(p+num_node*h+w) != 0)
        printf("%4.2f ", *(p+num_node*h+w));
      else
        printf("     ");
    putchar('\n');
  }
  putchar('\n');
  fflush(stdout);
}



void path_search_dijkstra(int* rep_mat, float* cst_mat, float* mem_mat, int num_node, int start, int goal)
{
  float dst;
  int* flag = (int*)malloc(sizeof(int)*num_node);
  int* next_flag = (int*)malloc(sizeof(int)*num_node);
  int num_flag = 1;
  int ret_flag;
  for (int i=0; i<num_node; i++)
  {
    *(flag+i) = 0;
    *(next_flag+i) = 0;
  }
  *(flag+start) = 1;
  while(num_flag)
  {
    num_flag = 0;
    for (int i=0; i<num_node; i++)
    {
      dst = *(mem_mat+i);
      if (*(flag+i) == 1)
      {
        for (int j=0; j<num_node; j++)
        {
          if (*(rep_mat+num_node*i+j) == 1)
          {
            if (dst + *(cst_mat+num_node*i+j) < *(mem_mat+j))
            {
              *(mem_mat+j) = dst + *(cst_mat+num_node*i+j);
              if (*(next_flag+j) == 0)
              {
                *(next_flag+j) = 1;
                num_flag ++;
              }
            }
          }
        }
      }
    }
    for (int i=0; i<num_node; i++)
    {
      *(flag+i) = *(next_flag+i);
      *(next_flag+i) = 0;
    }
  }
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
    if(*(adj_arr+i))
      *(cst_arr+i) = 0.01 * random_num(&seed, 1, 1001);
  
  /* Create Memory-array */ 
  float* mem_arr = (float*)malloc(sizeof(float)*L);
  for(int i=0; i<L; i++)
    *(mem_arr+i) = 10000000;
  *(mem_arr) = 0;

  /* Display array */
  display_graph(adj_arr, L);
  display_cost(cst_arr, L);

  /* Search path */
  path_search_dijkstra(adj_arr, cst_arr, mem_arr, L, 0, L-1);

  printf("shortest:: %4.2lf", *(mem_arr+L-1));

  /* Free memory */
  free(adj_arr);
  free(cst_arr);

  /* Return code */
  return 0;
}