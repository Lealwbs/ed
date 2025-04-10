//---------------------------------------------------------------------
// Arquivo      : evalenum.c
// Conteudo     : avaliacao de desempenho de algoritmos de ordenacao
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br) + implementacoes adicionais
// Historico    : 2023-11-04 - arquivo criado
//                2025-04-?? - implementacoes completas
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define ALGINSERTION 1
#define ALGSELECTION 2
#define ALGQSORT     3
#define ALGQSORT3    4
#define ALGQSORTINS  5
#define ALGQSORT3INS 6
#define ALGSHELLSORT 7
#define ALGRECSEL    8

typedef struct alg{
  int num;
  char * name;
} alg_t;

alg_t algvet[]={
  {ALGINSERTION,"i"},
  {ALGSELECTION,"s"},
  {ALGQSORT,"q"},
  {ALGQSORT3,"q3"},
  {ALGQSORTINS,"qi"},
  {ALGQSORT3INS,"q3i"},
  {ALGSHELLSORT,"h"},
  {ALGRECSEL,"rs"},
  {0,0}
};

int name2num(char * name){
  int i=0;
  while (algvet[i].num){
    if (!strcmp(algvet[i].name,name)) return algvet[i].num;
    i++;
  }
  return 0;
}

char * num2name(int num){
  int i=0;
  while (algvet[i].num){
    if (algvet[i].num==num) return algvet[i].name;
    i++;
  }
  return 0;
}

typedef struct opt{
  int size;
  int seed;
  int alg;
} opt_t;

typedef struct sortperf{
  int cmp;
  int move;
  int calls;
} sortperf_t;

void resetcounter(sortperf_t * s){
  s->cmp = 0;
  s->move = 0;
  s->calls = 0;
}

void inccmp(sortperf_t * s, int num){ s->cmp += num; }
void incmove(sortperf_t * s, int num){ s->move += num; }
void inccalls(sortperf_t * s, int num){ s->calls += num; }

char * printsortperf(sortperf_t * s, char * str, char * pref){
  sprintf(str,"%s cmp %d move %d calls %d", pref, s->cmp, s->move, s->calls);
  return str;
}

void initVector(int * vet, int size){
  for (int i=0; i<size; i++){
    vet[i] = (int)(drand48()*size);
  }
}

void printVector(int * vet, int size){
  for (int i=0; i<size; i++) printf("%d ",vet[i]);
  printf("\n");
}

void swap(int *xp, int *yp, sortperf_t *s){
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
  incmove(s,3);
}

// shellsort
void shellSort(int *A, int n, sortperf_t * s) {
  inccalls(s,1);
  int gap = n/2;
  while (gap > 0) {
    for (int i = gap; i < n; i++) {
      int temp = A[i];
      incmove(s,1);
      int j = i;
      // first comparison
      while (j >= gap) {
        inccmp(s,1);
        if (A[j-gap] > temp) {
          A[j] = A[j-gap]; incmove(s,1);
          j -= gap;
        } else break;
      }
      A[j] = temp; incmove(s,1);
    }
    gap /= 2;
  }
}

// recursive selection sort
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t * s)
{
    inccalls(s,1);
    int min = l;
    for (int j = l + 1; j <= r; j++){
      inccmp(s,1);
      if (arr[j] < arr[min]) min = j;
    }
    if (min != l) swap(&arr[min], &arr[l], s);
    if (l + 1 < r) recursiveSelectionSort(arr, l + 1, r, s);
}

// selection sort
void selectionSort(int arr[], int l, int r, sortperf_t * s) {
  inccalls(s,1);
  for (int i = l; i < r; i++){
    int min = i;
    for (int j = i+1; j <= r; j++){
      inccmp(s,1);
      if (arr[j] < arr[min]) min = j;
    }
    if (min != i) swap(&arr[min], &arr[i], s);
  }
}

// insertion sort
void insertionSort(int v[], int l, int r, sortperf_t * s) {
  inccalls(s,1);
  for (int i = l+1; i <= r; i++){
    int key = v[i]; incmove(s,1);
    int j = i - 1;
    
    while (j >= l) {
      inccmp(s,1);
      if (v[j] > key) {
        v[j+1] = v[j]; incmove(s,1);
        j--;
      } else break;
    }
    v[j+1] = key; incmove(s,1);
  }
}

// median of 3 integers
int median (int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;
    if ((a <= c) && (c <= b)) return c;
    if ((b <= a) && (a <= c)) return a;
    if ((b <= c) && (c <= a)) return c;
    if ((c <= a) && (a <= b)) return a;
    return b;
}

// standard quicksort partition
void partition(int * A, int l, int r, int *i, int *j, sortperf_t *s) {
  int pivot = A[(l+r)/2];
  *i = l; *j = r;
  while (*i <= *j) {
    while (1) {
      inccmp(s,1);
      if (A[*i] < pivot) (*i)++;
      else break;
    }
    while (1) {
      inccmp(s,1);
      if (A[*j] > pivot) (*j)--;
      else break;
    }
    if (*i <= *j) {
      swap(&A[*i], &A[*j], s);
      (*i)++; (*j)--;
    }
  }
}

// quicksort using standard partition
void quickSort(int * A, int l, int r, sortperf_t *s) {
  inccalls(s,1);
  if (l < r) {
    int i, j;
    partition(A, l, r, &i, &j, s);
    if (l < j) quickSort(A, l, j, s);
    if (i < r) quickSort(A, i, r, s);
  }
}

// partition with median of 3
void partition3(int * A, int l, int r, int *i, int *j, sortperf_t *s) {
  int mid = (l+r)/2;
  int pivotVal = median(A[l], A[mid], A[r]);
  // move pivot to middle
  if (pivotVal == A[l]) swap(&A[l], &A[mid], s);
  else if (pivotVal == A[r]) swap(&A[r], &A[mid], s);
  // now pivot at mid
  pivotVal = A[mid];
  *i = l; *j = r;
  while (*i <= *j) {
    while (1) {
      inccmp(s,1);
      if (A[*i] < pivotVal) (*i)++;
      else break;
    }
    while (1) {
      inccmp(s,1);
      if (A[*j] > pivotVal) (*j)--;
      else break;
    }
    if (*i <= *j) {
      swap(&A[*i], &A[*j], s);
      (*i)++; (*j)--;
    }
  }
}

// quicksort with median of 3
void quickSort3(int * A, int l, int r, sortperf_t *s) {
  inccalls(s,1);
  if (l < r) {
    int i, j;
    partition3(A, l, r, &i, &j, s);
    if (l < j) quickSort3(A, l, j, s);
    if (i < r) quickSort3(A, i, r, s);
  }
}

// quicksort with insertion for small partitions
void quickSortIns(int * A, int l, int r, sortperf_t *s) {
  inccalls(s,1);
  int threshold = 50;
  if (r - l + 1 <= threshold) {
    insertionSort(A, l, r, s);
  } else if (l < r) {
    int i, j;
    partition(A, l, r, &i, &j, s);
    if (l < j) quickSortIns(A, l, j, s);
    if (i < r) quickSortIns(A, i, r, s);
  }
}

// quicksort with insertion and median of 3
void quickSort3Ins(int * A, int l, int r, sortperf_t *s) {
  inccalls(s,1);
  int threshold = 50;
  if (r - l + 1 <= threshold) {
    insertionSort(A, l, r, s);
  } else if (l < r) {
    int i, j;
    partition3(A, l, r, &i, &j, s);
    if (l < j) quickSort3Ins(A, l, j, s);
    if (i < r) quickSort3Ins(A, i, r, s);
  }
}

void uso() {
  fprintf(stderr,"sortperf\n");
  fprintf(stderr,"\t-z <int>\t(vector size)\n");
  fprintf(stderr,"\t-s <int>\t(initialization seed)\n");
  fprintf(stderr,"\t-a <s|i|q|q3|qi|q3i|h|rs>\t(algorithm)\n");
  fprintf(stderr,"\t    s\tselection\n");
  fprintf(stderr,"\t    i\tinsertion\n");
  fprintf(stderr,"\t    q\tquicksort\n");
  fprintf(stderr,"\t    q3\tquicksort+median3\n");
  fprintf(stderr,"\t    qi\tquicksort+insertion\n");
  fprintf(stderr,"\t    q3i\tquicksort+median3+insertion\n");
  fprintf(stderr,"\t    h\thellsort\n");
  fprintf(stderr,"\t    rs\trecursive selection\n");
}

void parse_args(int argc, char ** argv, opt_t * opt) {
  extern char * optarg;
  extern int optind;
  int c;
  opt->seed = 1; opt->size = 10; opt->alg = 1;
  while ((c = getopt(argc, argv, "z:s:a:h")) != EOF) {
    switch(c) {
      case 'z': opt->size = atoi(optarg); break;
      case 's': opt->seed = atoi(optarg); break;
      case 'a': opt->alg = name2num(optarg); break;
      case 'h':
      default: uso(); exit(1);
    }
  }
  if (!opt->alg) { uso(); exit(1); }
}

void clkDiff(struct timespec t1, struct timespec t2, struct timespec * res) {
  if (t2.tv_nsec < t1.tv_nsec) {
    res->tv_nsec = 1000000000 + t2.tv_nsec - t1.tv_nsec;
    res->tv_sec = t2.tv_sec - t1.tv_sec - 1;
  } else {
    res->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    res->tv_sec = t2.tv_sec - t1.tv_sec;
  }
}

int main (int argc, char ** argv){
  sortperf_t s;
  int * vet;
  char buf[200];
  char pref[100];
  opt_t opt;
  struct timespec inittp, endtp, restp;
//  int retp;

  parse_args(argc,argv,&opt);

  vet = (int *) malloc((opt.size+1)*sizeof(int));
  resetcounter(&s);
  srand48(opt.seed);
  initVector(vet, opt.size);
  vet[opt.size] = vet[0];

  clock_gettime(CLOCK_MONOTONIC, &inittp);
  switch (opt.alg){
    case ALGINSERTION: insertionSort(vet, 0, opt.size-1, &s); break;
    case ALGSELECTION: selectionSort(vet, 0, opt.size-1, &s); break;
    case ALGQSORT:     quickSort(vet, 0, opt.size-1, &s); break;
    case ALGQSORT3:    quickSort3(vet, 0, opt.size-1, &s); break;
    case ALGQSORTINS:  quickSortIns(vet, 0, opt.size-1, &s); break;
    case ALGQSORT3INS: quickSort3Ins(vet, 0, opt.size-1, &s); break;
    case ALGSHELLSORT: shellSort(vet, opt.size, &s); break;
    case ALGRECSEL:    recursiveSelectionSort(vet, 0, opt.size-1, &s); break;
  }
  clock_gettime(CLOCK_MONOTONIC, &endtp);
  clkDiff(inittp, endtp, &restp);

  sprintf(pref,"alg %s seed %d size %d time %ld.%.9ld",
          num2name(opt.alg), opt.seed,opt.size,restp.tv_sec,restp.tv_nsec);
  printsortperf(&s,buf,pref);
  printf("%s\n",buf);

  free(vet);
  return 0;
}
