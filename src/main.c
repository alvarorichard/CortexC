#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>


int *pc, *bp, *sp, ax, cycle;

enum { LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };

int token;
char *src, *old_src;
int poolsize;
int line;

int *text,
    *old_text,
    *stack;
char *data;

void next(){
  token = *src++;
  return;
}

void expression(int level){

}

void program(){
  next();

  while (token > 0 ) {
    printf("token é: %c\n", token);
    next();
  }
}

int eval(){
  return 0;
}

int main(int argc, char **argv)
{

int i, fd;

argc--;
  argv++;

  poolsize = 256 * 1024;
    line = 1;

  if ((fd = open(*argv, 0)) < 0) {
    printf("nao pode abrir(%s)\n",*argv);
    return -1;
  }

   if (!(src = old_src = malloc(poolsize))) {
        printf("could not malloc(%d) for source area\n", poolsize);
        return -1;
    }

    if ((i = read(fd, src, poolsize-1)) <= 0) {
        printf("leu() returnou %d\n", i);
        return -1;
    }

  memset(text,0,poolsize);
  memset(data,0,poolsize);
  memset(stack,0,poolsize);

  bp = sp = (int *)((int)stack + poolsize);
  ax = 0;

  src[i] = 0;
  close(fd);
  program();
  return eval();
  }

