#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget{parent} {}

GLWidget::~GLWidget() { freeObject(&obj); }

void GLWidget::fileOpener(QString file) {
  parseFile(file.toLocal8Bit().data(), &obj);
  isOpened = YES;
  update();
}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLWidget::paintGL() {
  if (obj.facets != NULL) {
    glClearColor(backColor.redF(), backColor.greenF(), backColor.blueF(), 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (projection == CENTRAL_PROJECTION) {
      drawCentralProjection(obj);
    } else if (projection == PARALLEL_PROJECTION) {
      drawParallelProjection(obj);
    }
    drawByArray();
    glReadPixels(hsize, hsize, size, size, GL_RGBA, GL_UNSIGNED_BYTE, image);
  }
}

void GLWidget::drawByArray() {
  if (obj.facets != NULL) {
    if (linesMode == SOLID_LINES) {
      glDisable(GL_LINE_STIPPLE);
    } else {
      glEnable(GL_LINE_STIPPLE);
      if (linesMode == DASHED_LINES) {
        glLineStipple(1, 0x000F);
      } else if (linesMode == DOTTED_LINES) {
        glLineStipple(1, 0x0101);
      }
    }

    glLineWidth(linesSize);
    glColor3f(linesColor.redF(), linesColor.greenF(), linesColor.blueF());
    glVertexPointer(3, GL_DOUBLE, 0, obj.verts);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_LINES, obj.dotsNum * 2, GL_UNSIGNED_INT, &obj.facets[0]);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPointSize(vertsSize);

    if (vertsMode != HIDDEN_VERTS) {
      if (linesMode == SQUARE_VERTS) {
        glDisable(GL_POINT_SMOOTH);
      } else if (linesMode == CIRCLE_VERTS) {
        glEnable(GL_POINT_SMOOTH);
      }
      glLineWidth(linesSize);
      glColor3f(vertsColor.redF(), vertsColor.greenF(), vertsColor.blueF());
      glVertexPointer(3, GL_DOUBLE, 0, obj.verts);
      glEnableClientState(GL_VERTEX_ARRAY);
      glDrawElements(GL_POINTS, obj.dotsNum * 2, GL_UNSIGNED_INT,
                     &obj.facets[0]);
      glDisableClientState(GL_VERTEX_ARRAY);
    }
  }
}

void GLWidget::drawParallelProjection(obj_t obj) {
  double maxVal = obj.maxVal * 2.5;
  glOrtho(-maxVal, maxVal, -maxVal, maxVal, -maxVal * 1.5, maxVal * 1.5);
}

void GLWidget::drawCentralProjection(obj_t obj) {
  double maxVal = obj.maxVal * 1.75;
  glFrustum(-maxVal, maxVal, -maxVal, maxVal, maxVal, maxVal * 1000);
  glTranslatef(0, 0, -maxVal * 2);
}

void GLWidget::setColor(int mode) {
  if (mode == LINE_COLOR) {
    linesColor = QColorDialog::getColor(Qt::white, this, "Set lines color");
  } else if (mode == VERT_COLOR) {
    vertsColor = QColorDialog::getColor(Qt::white, this, "Set verts color");
  } else if (mode == BACK_COLOR) {
    backColor = QColorDialog::getColor(Qt::white, this, "Set back color");
  }
}

void GLWidget::setDrawingMode(int val) {
  if (val == SOLID_LINES || val == DASHED_LINES || val == DOTTED_LINES) {
    linesMode = val;
  } else if (val == SQUARE_VERTS || val == CIRCLE_VERTS ||
             val == HIDDEN_VERTS) {
    vertsMode = val;
  } else if (val == PARALLEL_PROJECTION || val == CENTRAL_PROJECTION) {
    projection = val;
  }
}

void GLWidget::setSize(int mode, int val) {
  if (mode == LINES_MODE) {
    linesSize = val;
  } else if (mode == VERTS_MODE) {
    vertsSize = val;
  }
}

void GLWidget::saveGif() {
  QDateTime curTime = QDateTime::currentDateTime();
  QString time = curTime.toString("yyyy-MM-dd-hh-mm-ss");
  QString fileName = time + ".gif";  // Путь к файлу
  int delay = 100;
  GifWriter g;
  GifBegin(&g, fileName.toStdString().c_str(), size, size, delay);
  for (int timer = 0; timer <= 5000; timer += delay) {
    GifWriteFrame(&g, image, size, size, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
  qDebug() << "Gif is ready";
  GifEnd(&g);
}
