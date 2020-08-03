#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

/* Sums from 0 to n. */
struct sum_limit {
  long n;
  long long sum;
};

/* Callback function for pthread use. */
static void *
sum_values( void *data ) {
  struct sum_limit *s = ( struct sum_limit* ) ( data );
  long long sum = 0;

  for ( long i = 0; i <= s->n; i++ ) {
    sum += i;
  }
  s->sum = sum;

  pthread_exit( 0 );

  return NULL;
}

int 
main( int argc, char *argv[] ) {
  if ( argc < 2 ) {
    fprintf( stderr, "Error, your arguments must be in the form: <n_0> <n_1> ... <n_n>.\n" );
    exit( EXIT_FAILURE );
  }
  
  /* First argument is the execution command. */
  int num_args = argc - 1;

  /* Create argc - 1 pthreads and sum structs. */
  struct sum_limit sums[num_args];
  pthread_t        pid[num_args];

  /* Create the threads and sum_limit structs, pass the callback fn. */
  for ( int i = 0; i < num_args; i++ ) {
    long long n = atoll( argv[i + 1] );
    sums[i].n = n;

    /* Initialize the default attributes for pthread. */
    pthread_attr_t   pid_attr;
    pthread_attr_init(&pid_attr);
    pthread_create( &pid[i], &pid_attr, sum_values, ( void * ) &sums[i] );
  }

  /* Join the threads to make sure they aren't prematurely
     printing data, then print out the results. */
  for ( int i = 0; i < num_args; i++ ) {
    pthread_join( pid[i], NULL );
    printf( "Thread %d sum from 0 to %ld: %lld.\n", i, sums[i].n, sums[i].sum );
  }

  return 0;
}