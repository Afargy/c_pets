#ifndef PARSER_H
#define PARSER_H

#define M_PI 3.14159265358979323846

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ObjData {
  int vertsNum;      // verticies counter
  int facetsNum;     // facets counters
  int dotsNum;       // number of dots in all facets
  double *verts;     // array for verticies coordinates
  unsigned *facets;  // pointer to arrays of facets values
  double maxVal;     // max value in verts array
} obj_t;

enum answer { NO, YES };
enum errorCodes { NO_FILE = 1, NO_DATA, WRONG_VERTEX, WRONG_FACET, NO_SPACE };
enum moves { MOVE_X = 1, MOVE_Y, MOVE_Z, ROTATE_X, ROTATE_Y, ROTATE_Z, ZOOM };
enum settings {
  BACK_COLOR = 1,
  LINE_COLOR,
  VERT_COLOR,
  PARALLEL_PROJECTION,
  CENTRAL_PROJECTION,
  SOLID_LINES,
  DASHED_LINES,
  DOTTED_LINES,
  SQUARE_VERTS,
  CIRCLE_VERTS,
  HIDDEN_VERTS,
  LINES_MODE,
  VERTS_MODE,
  PROJECTION_MODE
};

int parseFile(char *fileName, obj_t *obj);
void freeObject(obj_t *obj);
void moveX(obj_t *obj, const double step);
void moveY(obj_t *obj, const double step);
void moveZ(obj_t *obj, const double step);
void rotateX(obj_t *obj, const double angle);
void rotateY(obj_t *obj, const double angle);
void rotateZ(obj_t *obj, const double angle);
void scale(obj_t *obj, const double zoom);

#endif  // PARSER_H
