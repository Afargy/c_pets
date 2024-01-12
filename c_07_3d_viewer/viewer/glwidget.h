#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QColorDialog>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <thread>

#ifdef __cplusplus
extern "C" {
#include "../3d_viewer.h"
}
#endif

#include "gif.h"
#include "mainwindow.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  friend class MainWindow;

 public:
  explicit GLWidget(QWidget *parent = Q_NULLPTR);
  ~GLWidget();
  obj_t obj = {0, 0, 0, NULL, NULL, 0};
  bool isOpened = NO;
  void fileOpener(QString file);
  void setColor(int mode);
  void setDrawingMode(int val);
  void setSize(int mode, int val);
  void setProjection(int val);
  void saveGif();

 private:
  void showObj(obj_t obj);
  virtual void initializeGL() override;
  virtual void resizeGL(int w, int h) override;
  virtual void paintGL() override;
  void drawCentralProjection(obj_t obj);
  void drawParallelProjection(obj_t obj);
  void drawByArray();
  int projection = PARALLEL_PROJECTION;
  QColor backColor = Qt::black;
  QColor vertsColor = Qt::white;
  QColor linesColor = Qt::white;
  int linesMode = SOLID_LINES;
  int vertsMode = HIDDEN_VERTS;
  GLfloat vertsSize = 1;
  GLfloat linesSize = 1;
  int size = 800;
  int hsize = 400;
  uint8_t image[800 * 800 * 4];
};

#endif  // GLWIDGET_H
