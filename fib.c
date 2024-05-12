#include <stdio.h>
#include <stdlib.h>

int fib(int n) {
  if(n<2) return n;
  else return fib(n-1)+fib(n-2);
}

int main(int argc, char *argv[])
{
    if (argc != 2){
        return 0;
    }

    // fib(20);
    printf("fib(%d) == %d\n",atoi(argv[1]),fib(atoi(argv[1])));

    return 0;
}
