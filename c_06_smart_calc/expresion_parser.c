#include "calc.h"
// ============================initialization block=============================
static int scanTokens(char* expr, node_t** tkls, double value);
static int numSymb(char sym);
static int funcSymb(char sym);
static int operSymb(char sym);
static int scanNum(char* expr, node_t** tkls, int* pos);
static int scanFunc(char* expr, node_t** tkls, int* pos);
static int getFuncType(int i);
static void scanOper(char* expr, node_t** tkls);
static int setPriority(node_t** tkls, int* extraPrior);
static int funcType(int type);
static int checkPrevType(node_t** tkls);
static int scanX(node_t** tkls, double value);
// =============================================================================

/* Check expression syntax and set tokens in the ToKen LiSt. Return ERRor
 * value. If there is an error, token list will be deleted.*/
int parseExpr(char* expr, node_t** tkls, double value) {
  int err = NO;
  err = scanTokens(expr, tkls, value);
  // showList(*tkls);
  return err;
}

/* Scan tokens from the expression to the token list. Error value returns yes if
 * there is a wrong symbol.*/
static int scanTokens(char* expr, node_t** tkls, double value) {
  int err = NO, extraPrior = 0;
  for (int i = 0; expr[i] && !err; i++) {
    if (numSymb(expr[i])) {
      err = scanNum(expr + i, tkls, &i);
    } else if (funcSymb(expr[i])) {
      err = scanFunc(expr + i, tkls, &i);
    } else if (operSymb(expr[i])) {
      scanOper(expr + i, tkls);
    } else if (expr[i] == 'X') {
      scanX(tkls, value);
    } else {
      err = YES;
    }
    if (!err) err = checkPrevType(&(*tkls)->tail);
    if (!err) err = setPriority(&(*tkls)->tail, &extraPrior);
  }
  if (*tkls != NULL)
    if ((*tkls)->tail->type != TNUM && (*tkls)->tail->type != TRBR) err = YES;
  if (extraPrior) err = YES;
  if (err) freeList(tkls);
  return err;
}

/* Replace X with value */
static int scanX(node_t** tkls, double value) {
  int err = NO;
  node_t* node = NULL;
  initNode(&node, TNUM);
  node->val = value;
  pushTail(tkls, &node);
  return err;
}

/* Check the type of previous token */
static int checkPrevType(node_t** tkls) {
  int err = NO, prev = TNTY, cur = (*tkls)->type;
  if ((*tkls)->prev != NULL) {
    prev = (*tkls)->prev->type;
  }
  if ((cur == TLBR || funcType(cur)) && (prev == TRBR || prev == TNUM)) {
    err = YES;
  } else if (cur == TRBR && (prev != TNUM && prev != TRBR)) {
    err = YES;
  } else if ((cur == TADD || cur == TSUB) && (prev != TRBR && prev != TNUM)) {
    if (cur == TADD)
      (*tkls)->type = TPLS;
    else
      (*tkls)->type = TMNS;
  } else if (cur == TMUL || cur == TDIV || cur == TMOD || cur == TPOW) {
    if (prev != TRBR && prev != TNUM) err = YES;
  } else if (cur == TNUM && (prev == TRBR || prev == TNUM)) {
    err = YES;
  }
  return err;
}

/* Set priority for the token*/
static int setPriority(node_t** tkls, int* extraPrior) {
  int err = NO, type = TNTY, prior = 0, addtion = 10;
  type = (*tkls)->type;
  if (type == TLBR) {
    *extraPrior += addtion;
  } else if (type == TRBR) {
    *extraPrior -= addtion;
  } else if (type == TADD || type == TSUB) {
    prior += *extraPrior;
  } else if (type == TPLS || type == TMNS) {
    prior = *extraPrior + 1;
  } else if (type == TMUL || type == TDIV || type == TMOD) {
    prior = *extraPrior + 2;
  } else if (type == TPOW) {
    prior = *extraPrior + 3;
  } else if (funcType(type)) {
    prior = *extraPrior + 4;
    *extraPrior += addtion;
  }
  (*tkls)->priority = prior;
  if (*extraPrior < 0) err = YES;
  return err;
}

/* Check the type is function type */
static int funcType(int type) {
  int res = NO;
  if (type == TDLN || type == TLOG || type == TSRT) {
    res = YES;
  } else if (type == TSIN || type == TCOS || type == TTAN) {
    res = YES;
  } else if (type == TASN || type == TACS || type == TATN) {
    res = YES;
  }
  return res;
}

/* Scan operators to the token list.*/
static void scanOper(char* expr, node_t** tkls) {
  int type = TNTY;
  if (expr[0] == '+') {
    type = TADD;
  } else if (expr[0] == '-') {
    type = TSUB;
  } else if (expr[0] == '*') {
    type = TMUL;
  } else if (expr[0] == '/') {
    type = TDIV;
  } else if (expr[0] == '^') {
    type = TPOW;
  } else if (expr[0] == '(') {
    type = TLBR;
  } else if (expr[0] == ')') {
    type = TRBR;
  }
  node_t* node = NULL;
  initNode(&node, type);
  pushTail(tkls, &node);
}

/* Scan functions from the expreesion to the token list.*/
static int scanFunc(char* expr, node_t** tkls, int* pos) {
  int err = NO, type = TNTY;
  /* Add new function only to the end of the array! */
  char funcs[10][5] = {"ln(",   "log(",  "sin(",  "cos(",  "tan(",
                       "asin(", "acos(", "atan(", "sqrt(", "mod"};
  for (int i = 0; i < 10 && !err; i++) {
    if ((i == 0 || i == 9) && !strncmp(expr, funcs[i], 3)) {
      *pos += 2;
      type = getFuncType(i);
    } else if ((i >= 1 && i <= 4) && !strncmp(expr, funcs[i], 4)) {
      *pos += 3;
      type = getFuncType(i);
    } else if ((i >= 5 && i <= 8) && !strncmp(expr, funcs[i], 5)) {
      *pos += 4;
      type = getFuncType(i);
    }
  }
  if (type == TNTY) err = YES;
  if (!err) {
    node_t* node = NULL;
    initNode(&node, type);
    pushTail(tkls, &node);
  }
  return err;
}

/* Return type of function. Special for scanFunc*/
static int getFuncType(int i) {
  int type = TNTY;
  if (i == 0) {
    type = TDLN;
  } else if (i == 1) {
    type = TLOG;
  } else if (i == 2) {
    type = TSIN;
  } else if (i == 3) {
    type = TCOS;
  } else if (i == 4) {
    type = TTAN;
  } else if (i == 5) {
    type = TASN;
  } else if (i == 6) {
    type = TACS;
  } else if (i == 7) {
    type = TATN;
  } else if (i == 8) {
    type = TSRT;
  } else if (i == 9) {
    type = TMOD;
  }
  return type;
}

/* Scan number from expression to the token list. Return error if meets double
 * dot or if the number ends with dot. Pos shows current reading possion in
 * the expression string. In the end pos must show to the last symb of the
 * number.*/
static int scanNum(char* expr, node_t** tkls, int* pos) {
  int err = NO, avlbSymb = YES, hasDot = NO, lastDot = NO;
  double ipart = 0, fpart = 0, *cpart = &ipart;
  for (int j = 0; !err && avlbSymb; j++, ++*pos) {
    if (expr[j] >= '0' && expr[j] <= '9') {
      *cpart *= 10;
      *cpart += expr[j] - 48;
      lastDot = NO;
    } else if (expr[j] == '.') {
      if (hasDot) {
        err = YES;
      } else {
        cpart = &fpart;
        hasDot = YES;
      }
      lastDot = YES;
    } else {
      avlbSymb = NO;
    }
  }
  if (lastDot) err = YES;
  if (!err) {
    node_t* node = NULL;
    initNode(&node, TNUM);
    while (fpart > 1) fpart /= 10;
    node->val = ipart + fpart;
    pushTail(tkls, &node);
  }
  *pos -= 2;
  return err;
}

/* Checks the symbol is siutable for operators and brackets. (Except mod
 * operator, which are checked in funcSymb function).*/
static int operSymb(char sym) {
  int suitable = NO;
  if (sym == '+' || sym == '-')
    suitable = YES;
  else if (sym == '*' || sym == '/' || sym == '^')
    suitable = YES;
  else if (sym == '(' || sym == ')')
    suitable = YES;
  return suitable;
}

/* Checks the symbol is siutable for the function first letter. (Include mod
 * operator. All functions must be followd with '(' symbol and they are equal
 * to opening bracket.*/
static int funcSymb(char sym) {
  int suitable = NO;
  if (sym == 'l' || sym == 'm' || sym == 'a')  // ln, log, mod, asin, acos, atan
    suitable = YES;
  else if (sym == 's' || sym == 'c' || sym == 't')  // sin, cos, tan
    suitable = YES;
  return suitable;
}

/* Checks the symbol is siutable for number type. (Digit or dot).*/
static int numSymb(char sym) {
  return ((sym >= '0' && sym <= '9') || sym == '.') ? YES : NO;
}
