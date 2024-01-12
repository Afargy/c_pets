#include <math.h>

#include "calc.h"
// ============================initialization block=============================
static int calcTkls(node_t** tkls);
static int binaryOper(int type);
static int calcStk(node_t** numStk, node_t** oprStk, int listPri);
static int getResBin(node_t** numStk, node_t** oprStk);
static int getResUnary(node_t** numStk, node_t** oprStk);
// =============================================================================

/* This is the general function */
int calculate(char* expr, double value, double* result) {
  int err = NO;
  node_t* tkls = NULL;
  err = parseExpr(expr, &tkls, value);
  if (tkls != NULL && !err) {
    err += calcTkls(&tkls);
  }

  if (!err) *result = tkls->val;

  freeList(&tkls);
  return err;
}

/* Calculate expression which writen in the token list */
static int calcTkls(node_t** tkls) {
  int err = NO, type = TNTY;
  node_t *numStk = NULL, *oprStk = NULL;
  while (*tkls != NULL && !err) {
    type = (*tkls)->type;
    if (type == TNUM) {
      moveNode(tkls, &numStk);
    } else if (type == TRBR || type == TLBR) {
      freeHead(tkls);
    } else if (oprStk == NULL) {
      moveNode(tkls, &oprStk);
    } else if ((type == TMNS || type == TPLS) &&
               ((*tkls)->type == TMNS || (*tkls)->type == TPLS)) {
      moveNode(tkls, &oprStk);
    } else if (type == TPOW && (oprStk->tail->type == TPOW)) {
      moveNode(tkls, &oprStk);
    } else {
      int stkPri = oprStk->tail->priority, listPri = (*tkls)->priority;
      if (listPri <= stkPri) err = calcStk(&numStk, &oprStk, listPri);
      moveNode(tkls, &oprStk);
    }
  }
  err += calcStk(&numStk, &oprStk, 0);
  moveNode(&numStk, tkls);
  freeList(&numStk);
  freeList(&oprStk);
  if (err) freeList(tkls);
  return err;
}

/* Calculate operations written in the two stacks (number and operator). Stops
 * when operator list is empty or when the incommig elem has the bigger
 * priority value. The result of done operations returns to the number stack*/
static int calcStk(node_t** numStk, node_t** oprStk, int listPri) {
  int err = NO;
  while ((*oprStk) != NULL && (*oprStk)->tail->priority >= listPri) {
    int type = (*oprStk)->tail->type;
    if (binaryOper(type)) {
      err += getResBin(numStk, oprStk);
    } else {
      err += getResUnary(numStk, oprStk);
    }
  }
  return err;
}

/* Get result for the using binaty operator operation */
static int getResBin(node_t** numStk, node_t** oprStk) {
  int err = NO, type = (*oprStk)->tail->type;
  double res = (*numStk)->tail->prev->val, val = (*numStk)->tail->val;
  if (type == TADD) {
    res = res + val;
  } else if (type == TSUB) {
    res = res - val;
  } else if (type == TMUL) {
    res = res * val;
  } else if (type == TDIV) {
    if (val != 0) {
      res = res / val;
    } else {
      err = YES;
    }
  } else if (type == TMOD) {
    if (val != 0) {
      res = fmod(res, val);
    } else {
      err = YES;
    }
  } else if (type == TPOW) {
    res = pow(res, val);
  }
  (*numStk)->tail->prev->val = res;
  freeTail(oprStk);
  freeTail(numStk);
  return err;
}

/* Get result for the using unaty operator operation */
static int getResUnary(node_t** numStk, node_t** oprStk) {
  int err = NO, type = (*oprStk)->tail->type;
  double res = (*numStk)->tail->val;
  if (type == TMNS) {
    res = -res;
  } else if (type == TSIN) {
    res = sin(res);
  } else if (type == TCOS) {
    res = cos(res);
  } else if (type == TTAN) {
    res = tan(res);
  } else if (type == TASN) {
    res = asin(res);
  } else if (type == TACS) {
    res = acos(res);
  } else if (type == TATN) {
    res = atan(res);
  } else if (type == TSRT) {
    res = sqrt(res);
  } else if (type == TDLN) {
    res = log(res);
  } else if (type == TLOG) {
    res = log10(res);
  }
  (*numStk)->tail->val = res;
  freeTail(oprStk);
  return err;
}

/* Check the operator or function in stack is binary */
static int binaryOper(int type) {
  int res = NO;
  if (type == TADD || type == TSUB || type == TPOW)
    res = YES;
  else if (type == TMUL || type == TDIV || type == TMOD)
    res = YES;
  return res;
}
