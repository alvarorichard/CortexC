#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#define int long long




int *pc, *bp, *sp, ax, cycle;



struct identifier {
  int token;
  int hash;
  char * name;
  int class;
  int type;
  int value;
  int Bclass;
  int Btype;
  int Bvalue;
};

enum { LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };

enum {
  Num = 128, Fun, Sys, Glo, Loc, Id,
  Char, Else, Enum, If, Int, Return, Sizeof, While,
  Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};


int token;
char *src, *old_src;
int poolsize;
int line;

int *text,
    *old_text,
    *stack;
char *data;

int token_val;
int *current_id,
    *symbols;

enum {Token, Hash, Name, Type, Class, Value, BType, BClass, BValue, IdSize};

void next() {
    char token;
    char *last_pos;
    int hash;
    while ((token = *src)) {
        ++src;

        if (token == '\n') {
            ++line;
        } else if (token == '#') {
            while (*src != 0 && *src != '\n') {
                src++;
            }
        } else if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token == '_')) {
            last_pos = src - 1;
            hash = token;
            while ((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z') || (*src >= '0' && *src <= '9') || (*src == '_')) {
                hash = hash * 147 + *src;
                src++;
            }
            current_id = symbols;
            while (current_id[Token]) {
                if (current_id[Hash] == hash && !memcmp((char *)current_id[Name], last_pos, src - last_pos)) {
                    token = current_id[Token];
                    return;
                }
                current_id = current_id + IdSize;
            }
            current_id[Name] = (int)last_pos;
            current_id[Hash] = hash;
            token = current_id[Token] = Id;
            return;
        }
   
else if (token >= '0' && token <= '9') {
            // Analisar número, três tipos: dec(123) hex(0x123) oct(017)
            token_val = token - '0';
            if (token_val > 0) {
                // dec, começa com [1-9]
                while (*src >= '0' && *src <= '9') {
                    token_val = token_val*10 + *src++ - '0';
                }
            } else {
                // inicia com numero 0
                if (*src == 'x' || *src == 'X') {
                    //hex
                    token = *++src;
                    while ((token >= '0' && token <= '9') || (token >= 'a' && token <= 'f') || (token >= 'A' && token <= 'F')) {
                        token_val = token_val * 16 + (token & 15) + (token >= 'A' ? 9 : 0);
                        token = *++src;
                    }
                } else {
                    // oct
                    while (*src >= '0' && *src <= '7') {
                        token_val = token_val*8 + *src++ - '0';
                    }
                }
            }
            token = Num;
            return;
        }
        else if (token == '"' || token == '\'') {
            last_pos = data;
            while (*src != 0 && *src != token){
                token_val = *src++;
                if (token_val == '\\') {
                    token_val = *src++;
                    if (token_val == 'n') {
                        token_val = '\n';
                    }
                }
                if (token == '"') {
                    *data++ = token_val;
                }
            }
            src++;
            if (token == '"') {
                token_val = (int)last_pos;
            } else {
                token = Num;
            }
            return;
        
        }
        else if (token == '/') {
            if ( *src == '/') {
                while (*src != 0 && *src != '\n') {
                    ++src;
                }
            } else {
                token = Div;
                return;
            }
           
        
        }
        else if (token == '=') {
            if(*src == '=') {
                src++;
                token = Eq;
            } else {
                token = Assign;
            }
            return;

        
        }
        else if(token == '+'){
            if(*src == '+') {
                src++;
                token = Inc;
            } else {
                token = Add;
            }
            return;
        }
        else if (token == '-'){
            if(*src == '-') {
                src++;
                token = Dec;
            } else {
                token = Sub;
            }
            return;
        }
        else if(token == '!'){
            if(*src == '='){
                src++;
                token = Ne;


            }
            return;
        }
        else if(token == '<'){
            if (*src == '=')
            {
                src++;
                token = Le;
            }else if (*src == '<') {
                src ++;
                token = Shl;
             
            } else {
                token = Lt;
            }
            return;
            
        }
        else if(token == '>'){
            if (*src == '=')
            {
                src++;
                token = Ge;
            }else if (*src == '>') {
                src ++;
                token = Shr;
             
            } else {
                token = Gt;
            }
            return;
            
        }
        else if (token == '&') {
            // parse '&' and '&&'
            if (*src == '&') {
                src ++;
                token = Lan;
            } else {
                token = And;
            }
            return;
        }
        else if (token == '^') {
            token = Xor;
            return;
        }
        else if (token == '%') {
            token = Mod;
            return;
        }
        else if (token == '*') {
            token = Mul;
            return;
        }
        else if (token == '[') {
            token = Brak;
            return;
        }
        else if (token == '?') {
            token = Cond;
            return;
        }
        else if (token == '~' || token == ';' || token == '{' || token == '}' || token == '(' || token == ')' || token == ']' || token == ',' || token == ':') {
            // directly return the character as token;
            return;
        }




            

    }
}


//teste commit new machine 

void expression(int level){

}

void program(){
  next();

  while (token > 0 ) {
    printf("token é: %c\n", token);
    next();
  }
}
#undef int

int callee(int a, int b, int c){
  return a + b + c;
}

int caller(void)
{
        int i, ret;

        ret = callee(1, 2, 3);
        ret += 5;
        return ret;
}

//assembly

int eval() {
    int op, *tmp;
    while (1) {
        op = *pc++; // gera o proximo codigo
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
        else if (op == ADJ)  {sp = sp + *pc++;}
        else if (op == LEV)  {sp = bp; bp = (int *)*sp++; pc = (int *)*sp++;}  // restore call frame and PC
        else if (op == LEA)  {ax =(int)(bp + *pc++);}
        else if (op == OR)  ax = *sp++ | ax;
        else if (op == XOR) ax = *sp++ ^ ax;
        else if (op == AND) ax = *sp++ & ax;
        else if (op == EQ)  ax = *sp++ == ax;
        else if (op == NE)  ax = *sp++ != ax;
        else if (op == LT)  ax = *sp++ < ax;
        else if (op == LE)  ax = *sp++ <= ax;
        else if (op == GT)  ax = *sp++ >  ax;
        else if (op == GE)  ax = *sp++ >= ax;
        else if (op == SHL) ax = *sp++ << ax;
        else if (op == SHR) ax = *sp++ >> ax;
        else if (op == ADD) ax = *sp++ + ax;
        else if (op == SUB) ax = *sp++ - ax;
        else if (op == MUL) ax = *sp++ * ax;
        else if (op == DIV) ax = *sp++ / ax;
        else if (op == MOD) ax = *sp++ % ax;
   
      // built-in instructions

       else if (op == EXIT) { printf("exit(%d)", *sp); return *sp;}
       else if (op == OPEN) { ax = open((char *)sp[1], sp[0]); }
       else if (op == CLOS) { ax = close(*sp);}
       else if (op == READ) { ax = read(sp[2], (char *)sp[1], *sp); }
       else if (op == PRTF) { tmp = sp + pc[1]; ax = printf((char *)tmp[-1], tmp[-2], tmp[-3], tmp[-4], tmp[-5], tmp[-6]); }
       else if (op == MALC) { ax = (int)malloc(*sp);}
       else if (op == MSET) { ax = (int)memset((char *)sp[2], sp[1], *sp);}
       else if (op == MCMP) { ax = memcmp((char *)sp[2], (char *)sp[1], *sp);}
    else {
      printf("Instrucao Desconhecida:%d\n",op);
        return -1;
       
        }
    }

    
    return 0;
}

#undef int

int main(int argc, char *argv[])
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
        printf("Não foi possível alocar (%d) para a área de origem\n", poolsize);
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
  i = 0;
 // comentario para teste compilador 
    text[i++] = IMM;
    text[i++] = 10;
    text[i++] = PUSH;
    text[i++] = IMM;
    text[i++] = 20;
    text[i++] = ADD;
    text[i++] = PUSH;
    text[i++] = EXIT;
    pc = text;
  src[i] = 0;
  close(fd);
  program();
  return eval();
  }

