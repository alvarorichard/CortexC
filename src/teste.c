#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>


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

int callee (int,int,int);

int caller(void){

int i, ret;

  ret = calle (1,2,3);
  ret += 5;

  return ret;


}

void eval() {
    int op, *tmp;
    while (1) {
        op = *pc++; // get next operation code
        if (op == IMM)       {ax = *pc++;}                                     // load immediate value to ax
        else if (op == LC)   {ax = *(char *)ax;}                               // load character to ax, address in ax
        else if (op == LI)   {ax = *(int *)ax;}                                // load integer to ax, address in ax
        else if (op == SC)   {ax = *(char *)*sp++ = ax;}                       // save character to address, value in ax, address on stack
        else if (op == SI)   {*(int *)*sp++ = ax;}    // save integer to address, value in ax, address on stack
        else if (op == PUSH) {*--sp = ax;}
        else if (op == JMP)  {pc = (int *)*pc;}
        else if (op == JZ )  {pc = ax ? pc + 1 : (int *)*pc;}
        else if (op == JNZ)  {pc = ax ? (int *)*pc : pc + 1;}
        else if (op == CALL) {*--sp = (int)(pc+1); pc = (int *)*pc;}

    }

    
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
        perror("Error opening file");
        return -1;
    }

    if (!(src = old_src = malloc(poolsize))) {
        printf("could not malloc(%d) for source area\n", poolsize);
        return -1;
    }

    if (!(text = malloc(poolsize)) || !(data = malloc(poolsize)) || !(stack = malloc(poolsize))) {
        printf("could not malloc(%d) for text/data/stack area\n", poolsize);
        return -1;
    }

    if ((i = read(fd, src, poolsize-1)) <= 0) {
        printf("read() returned %d\n", i);
        return -1;
    }

    memset(text, 0, poolsize);
    memset(data, 0, poolsize);
    memset(stack, 0, poolsize);

    bp = sp = (int *)((int)stack + poolsize);
    ax = 0;

    src[i] = 0;
    close(fd);

    program();
    return eval();
}

