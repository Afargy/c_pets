#ifndef SRC_CALC_H_
#define SRC_CALC_H_

// MBDIFV
// means Must Be Deleted In Final Version // MBDIFV

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXPMAX 4096

typedef struct nodeStruct {
  struct nodeStruct* tail;  // link to the last node in the list,
  struct nodeStruct* prev;  // link to the previous node in the list
  struct nodeStruct* next;  // link to the next elem in the list
  double val;  // stored value, used only for number type, others types are NAN
  int type;  // type of token stored in the node, use names from enum tokenType
  int priority;  // heigher value is more priority
  unsigned pos;  // position in the list, when init equals 1;
} node_t;

enum answer { NO, YES };  // shot answers list

enum tokenTypes {  // token types list first T means type
  TNTY = 0,        // no type
  TLBR = '(',      // left bracket
  TRBR = ')',      // right bracket
  TADD = '+',      // binary plus, eg: 1+1
  TSUB = '-',      // binary minus, eg: 1-1
  TMUL = '*',      // multiply
  TDIV = '/',      // division
  TPOW = '^',      // raising to the power
  TMOD = 'M',      // taking reminder of division
  TPLS = 'p',      // unary plus, eg: +1
  TMNS = 'm',      // unary minus, eg: 1-1
  TSIN = 's',      // sinus
  TCOS = 'c',      // cosinus
  TTAN = 't',      // tangens
  TASN = 'S',      // arcsinus
  TACS = 'C',      // arccosinus
  TATN = 'T',      // arcatangens
  TSRT = 'r',      // taking square root
  TDLN = 'l',      // natural logorithm
  TLOG = 'L',      // decimal logorithm
  TNUM = 'n'       // number :)
};

// functions for working with nodes

int initNode(node_t** node, int type);
void pushTail(node_t** list, node_t** node);
void freeHead(node_t** list);
void freeTail(node_t** list);
void freeList(node_t** list);
void moveNode(node_t** from, node_t** to);

// functions for working with expression

int parseExpr(char* expr, node_t** tkls, double value);
int calculate(char* expr, double value, double* result);

void replace(char* str, char* nStr, double num);

#endif  // SRC_CALC_H_
