#include "3d_viewer.h"

static int countVariables(FILE* file, obj_t* obj);
static int readFile(FILE* file, obj_t* obj);
static int initObject(obj_t* obj);
static int parseVertex(char* str, obj_t* obj, int* curV);
static int parceFacet(char* str, obj_t* obj, int* curF, int countV);
static void countFacets(FILE* file, obj_t* obj, char* nowChar, char* lastChar);
static void findMax(obj_t* obj);
static void putAtCenter(obj_t* obj);
static void makeStep(obj_t* obj, int* curF, int num);
static void makeShoter(int* isFirst, int* first, obj_t* obj, int* curF,
                       int num);

int parseFile(char* fileName, obj_t* obj) {
  freeObject(obj);
  int err = NO;
  FILE* file = fopen(fileName, "r");
  if (file == NULL) {
    err = NO_FILE;
    printf("error: %d", err);
  }
  if (!err) {
    countVariables(file, obj);
    fclose(file);
  }
  if (!err) err = initObject(obj);
  // err = NO_SPACE;

  if (!err) {
    file = fopen(fileName, "r");
    readFile(file, obj);
    fclose(file);
    findMax(obj);
    putAtCenter(obj);
    findMax(obj);
  }

  if (err) freeObject(obj);
  return err;
}

void freeObject(obj_t* obj) {
  obj->dotsNum = 0;
  obj->facetsNum = 0;
  obj->vertsNum = 0;
  obj->maxVal = 0;
  if (obj->verts != NULL) free(obj->verts);
  if (obj->facets != NULL) free(obj->facets);
  obj->verts = NULL;
  obj->facets = NULL;
}

static int countVariables(FILE* file, obj_t* obj) {
  int err = NO;
  char nowChar, lastChar = '\n';
  while ((nowChar = fgetc(file)) != EOF) {
    if (nowChar == 'v' && lastChar == '\n') {
      if ((nowChar = fgetc(file)) == ' ') obj->vertsNum++;
    } else if (nowChar == 'f' && lastChar == '\n') {
      countFacets(file, obj, &nowChar, &lastChar);
    }
    lastChar = nowChar;
  }
  return err;
}

static void countFacets(FILE* file, obj_t* obj, char* nowChar, char* lastChar) {
  obj->facetsNum += 1;
  while ((*nowChar = fgetc(file)) != '\n' && *nowChar != EOF) {
    if ((isdigit(*nowChar) || *nowChar == '-' || *nowChar == '.') &&
        *lastChar == ' ') {
      obj->dotsNum++;
    }
    *lastChar = *nowChar;
  }
}

static int initObject(obj_t* obj) {
  int err = NO;
  int size = obj->vertsNum;
  obj->verts = calloc(sizeof(double), size * 3);
  obj->facets = calloc((sizeof(int)), obj->dotsNum * 2);
  if (obj->verts == NULL || obj->facets == NULL) {
    err = NO_SPACE;
  }
  if (err) {
    freeObject(obj);
    printf("error: %d", err);
  }
  return err;
}

static int readFile(FILE* file, obj_t* obj) {
  int err = NO;
  char str[4096] = {0};
  int curV = 0, curF = 0;  // current vertex and facet
  int countV = 0;
  while (fgets(str, 4096, file) && !err) {
    if (str[0] == 'v' && str[1] == ' ') {
      countV++;
      parseVertex(str + 2, obj, &curV);
    } else if (str[0] == 'f' && str[1] == ' ') {
      parceFacet(str + 2, obj, &curF, countV);
    }
  }
  return err;
}

static int parseVertex(char* str, obj_t* obj, int* curV) {
  int err = NO, counter = 0;
  char origin[4096] = {0};
  strcpy(origin, str);
  char* token = strtok(str, " ");
  while (token != NULL && counter < 3) {
    double num = 0;
    int res = sscanf(token, "%lf", &num);
    if (res == 1) counter++;
    token = strtok(NULL, " ");
  }
  if (counter > 1) {
    token = strtok(origin, " ");
    counter = 0;
    while (token != NULL && counter < 3) {
      double num = 0;
      int res = sscanf(token, "%lf", &num);
      if (res == 1) {
        obj->verts[*curV] = num;
        (*curV)++;
        counter++;
      }
      token = strtok(NULL, " ");
    }
  }
  if (counter != 3) err = WRONG_VERTEX;
  return err;
}

static int parceFacet(char* str, obj_t* obj, int* curF, int countV) {
  int err = NO, isFirst = YES, first = 0, haveDots = NO;
  char origin[4096] = {0};
  strcpy(origin, str);
  char* token = strtok(str, " ");
  while (token != NULL && !haveDots) {
    int num = 0;
    int res = sscanf(token, "%d", &num);
    if (res == 1) haveDots = YES;
    token = strtok(NULL, " ");
  }
  if (haveDots) {
    token = strtok(origin, " ");
    while (token != NULL) {
      int num = 0;
      int res = sscanf(token, "%d", &num);
      if (num < 0) num = countV + num + 1;
      if (res == 1) {
        makeShoter(&isFirst, &first, obj, curF, num);
      }
      token = strtok(NULL, " ");
    }
    obj->facets[*curF] = first - 1;
    (*curF)++;
  }
  return err;
}

static void makeShoter(int* isFirst, int* first, obj_t* obj, int* curF,
                       int num) {
  if (*isFirst) {
    *first = num;
    *isFirst = NO;
    makeStep(obj, curF, num);
  } else {
    makeStep(obj, curF, num);
    makeStep(obj, curF, num);
  }
}

static void makeStep(obj_t* obj, int* curF, int num) {
  obj->facets[*curF] = num - 1;
  (*curF)++;
}

static void findMax(obj_t* obj) {
  double maxVal = 0;
  for (int i = 0; i < obj->vertsNum * 3; ++i) {
    if (abs(obj->verts[i] > maxVal)) maxVal = fabs(obj->verts[i]);
  }
  obj->maxVal = maxVal;
}

static void putAtCenter(obj_t* obj) {
  double max_x = 0, max_y = 0, max_z = 0;
  double min_x = 0, min_y = 0, min_z = 0;
  for (int i = 0; i < obj->vertsNum; ++i) {
    if (obj->verts[i * 3] > max_x) max_x = obj->verts[i * 3];
    if (obj->verts[i * 3 + 1] > max_y) max_y = obj->verts[i * 3 + 1];
    if (obj->verts[i * 3 + 2] > max_z) max_z = obj->verts[i * 3 + 2];
    if (obj->verts[i * 3] < min_x) min_x = obj->verts[i * 3];
    if (obj->verts[i * 3 + 1] < min_y) min_y = obj->verts[i * 3 + 1];
    if (obj->verts[i * 3 + 2] < min_z) min_z = obj->verts[i * 3 + 2];
  }
  double mid_x = (max_x + min_x) / 2;
  double mid_y = (max_y + min_y) / 2;
  double mid_z = (max_z + min_z) / 2;
  for (int i = 0; i < obj->vertsNum; ++i) {
    obj->verts[i * 3] -= mid_x;
    obj->verts[i * 3 + 1] -= mid_y;
    obj->verts[i * 3 + 2] -= mid_z;
  }
}
