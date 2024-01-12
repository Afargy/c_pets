#include "3d_viewer.h"

void moveX(obj_t *obj, const double step) {
  for (int i = 0; i < obj->vertsNum; i++) {
    obj->verts[i * 3] += step;
  }
}

void moveY(obj_t *obj, const double step) {
  for (int i = 0; i < obj->vertsNum; i++) {
    obj->verts[i * 3 + 1] += step;
  }
}

void moveZ(obj_t *obj, const double step) {
  for (int i = 0; i < obj->vertsNum; i++) {
    obj->verts[i * 3 + 2] += step;
  }
}

static double degToRad(const double angle) { return angle * M_PI / 180; }

void rotateX(obj_t *obj, const double angle) {
  double rad = degToRad(angle);
  for (int i = 0; i < obj->vertsNum; i++) {
    double y = obj->verts[i * 3 + 1];
    double z = obj->verts[i * 3 + 2];
    obj->verts[i * 3 + 1] = y * cos(rad) - z * sin(rad);
    obj->verts[i * 3 + 2] = y * sin(rad) + z * cos(rad);
  }
}

void rotateY(obj_t *obj, const double angle) {
  double rad = degToRad(angle);
  for (int i = 0; i < obj->vertsNum; i++) {
    double x = obj->verts[i * 3];
    double z = obj->verts[i * 3 + 2];
    obj->verts[i * 3] = x * cos(rad) + z * sin(rad);
    obj->verts[i * 3 + 2] = -x * sin(rad) + z * cos(rad);
  }
}

void rotateZ(obj_t *obj, const double angle) {
  double rad = degToRad(angle);
  for (int i = 0; i < obj->vertsNum; i++) {
    double x = obj->verts[i * 3];
    double y = obj->verts[i * 3 + 1];
    obj->verts[i * 3] = x * cos(rad) - y * sin(rad);
    obj->verts[i * 3 + 1] = x * sin(rad) + y * cos(rad);
  }
}

void scale(obj_t *obj, const double zoom) {
  if (zoom && zoom != 1)
    for (int i = 0; i < obj->vertsNum * 3; i++) {
      obj->verts[i] *= zoom;
    }
}
