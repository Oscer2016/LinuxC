#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    puts( "About to abort....\n" );
    abort();
  
    puts( "This will never be executed!\n" );
    exit(0);
}
