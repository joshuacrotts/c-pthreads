#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static void *
print_str( void *data ) {
  printf("Hello from the second thread! Your long is %ld.\n", *( long * ) data );

  return NULL;
}

int
main( int argc, char *argv[] ) {
  if ( argc != 2 ) {
    fprintf( stderr, "Please, enter a number alongside the command!\n" );
    exit( EXIT_FAILURE );
  }

  pthread_t       pid;
  pthread_attr_t  p_attr;

  long number = atoll( argv[1] );

  printf("Hello from the main thread! This should print before the second thread starts.\n");

  /* Initialize the pthread attributes and pthread. */
  pthread_attr_init( &p_attr );
  pthread_create( &pid, &p_attr, print_str, ( void * ) &number );

  printf( "Starting the sum of the digits.\n" );
  long long sum = 0;
  for ( long i = 0; i < number; i++ ) {
    sum += i;
  }
  /* Depending on how large the input number is, this may print after the child thread finishes. */
  printf( "Finishing the sum of the digits from 0 to %ld: %lld.\n", number, sum );
  
  pthread_join( pid, NULL );
  printf( "Hello again from the main thread! This should print after the second thread finishes.\n" );


  return 0;
}