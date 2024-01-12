#include "calc.h"

/* allocate memory for node and set its type*/
int initNode(node_t** node, int type) {
  int err = YES;
  *node = (node_t*)malloc(sizeof(node_t));
  if (*node != NULL) {
    err = NO;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    (*node)->tail = *node;
    (*node)->type = type;
    (*node)->val = NAN;
    (*node)->priority = NO;
    (*node)->pos = 1;
  }
  return err;
}

/* release the first block of the list and set the list pointer to the next
 * block*/
void freeHead(node_t** list) {
  node_t* ptr = *list;
  if (ptr != NULL) {
    if (ptr->next != NULL) {
      *list = (*list)->next;
      (*list)->prev = NULL;
      (*list)->tail = ptr->tail;
      free(ptr);
    } else {
      free(ptr);
      ptr = NULL;
      *list = NULL;
    }
  }
}

/* release the last block of the list*/
void freeTail(node_t** list) {
  if (*list != NULL) {
    if ((*list)->tail != *list) {
      node_t* ptr = (*list)->tail;
      (*list)->tail = (*list)->tail->prev;
      (*list)->tail->next = NULL;
      free(ptr);
      ptr = NULL;
    } else {
      free(*list);
      *list = NULL;
    }
  }
}

/* set the node as a last elem of the list */
void pushTail(node_t** list, node_t** node) {
  if (*node != NULL) {
    if (*list != NULL) {
      (*node)->prev = (*list)->tail;
      (*node)->next = NULL;
      (*node)->tail = NULL;
      (*list)->tail->next = *node;
      (*list)->tail = *node;
      (*list)->tail->pos = (*node)->prev->pos + 1;
    } else {
      (*node)->prev = NULL;
      (*node)->next = NULL;
      (*node)->tail = *node;
      (*node)->pos = 1;
      *list = *node;
    }
    *node = NULL;
  }
}

/* release the list */
void freeList(node_t** list) {
  while (*list != NULL) freeHead(list);
}

/* Move the list head to another list tail */
void moveNode(node_t** from, node_t** to) {
  if (*from != NULL) {
    node_t* movingNode = *from;
    if ((*from)->next != NULL) {
      *from = (*from)->next;
      (*from)->prev = NULL;
      (*from)->tail = movingNode->tail;
    } else {
      *from = NULL;
    }
    if (*to != NULL) {
      movingNode->prev = (*to)->tail;
      movingNode->next = NULL;
      movingNode->tail = NULL;
      movingNode->pos = (*to)->tail->pos + 1;
      (*to)->tail->next = movingNode;
      (*to)->tail = movingNode;
    } else {
      movingNode->next = NULL;
      movingNode->prev = NULL;
      movingNode->tail = movingNode;
      movingNode->pos = 1;
      *to = movingNode;
    }
    movingNode = NULL;
  }
}
