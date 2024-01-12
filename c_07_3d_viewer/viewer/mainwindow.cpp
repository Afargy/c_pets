#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  loadSettings();
  // moving buttons
  connect(ui->xMoveButton, &QPushButton::clicked, this,
          [this] { mrzClicked(MOVE_X); });
  connect(ui->yMoveButton, &QPushButton::clicked, this,
          [this] { mrzClicked(MOVE_Y); });
  connect(ui->zMoveButton, &QPushButton::clicked, this,
          [this] { mrzClicked(MOVE_Z); });
  connect(ui->xRotateButton, &QPushButton::clicked, this,
          [this] { mrzClicked(ROTATE_X); });
  connect(ui->yRotateButton, &QPushButton::clicked, this,
          [this] { mrzClicked(ROTATE_Y); });
  connect(ui->zRotateButton, &QPushButton::clicked, this,
          [this] { mrzClicked(ROTATE_Z); });
  connect(ui->zoomButton, &QPushButton::clicked, this,
          [this] { mrzClicked(ZOOM); });
  // set color buttons
  connect(ui->setBackgroundColorButton, &QPushButton::clicked, this,
          [this] { setColorClicked(BACK_COLOR); });
  connect(ui->setLinesColorButton, &QPushButton::clicked, this,
          [this] { setColorClicked(LINE_COLOR); });
  connect(ui->setVertsColorButton, &QPushButton::clicked, this,
          [this] { setColorClicked(VERT_COLOR); });
  // projection
  connect(ui->parallelProjectionButton, &QPushButton::clicked, this,
          [this] { setDrawingModeClicked(PARALLEL_PROJECTION); });
  connect(ui->centralProjectionButton, &QPushButton::clicked, this,
          [this] { setDrawingModeClicked(CENTRAL_PROJECTION); });
  // drawing mode
  connect(ui->setSolidLineRadio, &QPushButton::clicked, this,
          [this] { setDrawingModeClicked(SOLID_LINES); });
  connect(ui->setDashedLineRadio, &QPushButton::clicked, this,
          [this] { setDrawingModeClicked(DASHED_LINES); });
  connect(ui->setDottedLineRadio, &QPushButton::clicked, this,
          [this] { setDrawingModeClicked(DOTTED_LINES); });
  connect(ui->setSquareVertsRadio, &QPushButton::clicked, this,
          [this] { setDrawingModeClicked(SQUARE_VERTS); });
  connect(ui->setCircleVertsRadio, &QPushButton::clicked, this,
          [this] { setDrawingModeClicked(CIRCLE_VERTS); });
  connect(ui->setHiddenVertsRadio, &QPushButton::clicked, this,
          [this] { setDrawingModeClicked(HIDDEN_VERTS); });
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::mrzClicked(int val) {
  if (val == MOVE_X) {
    moveX(&ui->scene->obj, ui->xMoveSpin->value());
  } else if (val == MOVE_Y) {
    moveY(&ui->scene->obj, ui->yMoveSpin->value());
  } else if (val == MOVE_Z) {
    moveZ(&ui->scene->obj, ui->zMoveSpin->value());
  } else if (val == ROTATE_X) {
    rotateX(&ui->scene->obj, ui->xRotateSpin->value());
  } else if (val == ROTATE_Y) {
    rotateY(&ui->scene->obj, ui->yRotateSpin->value());
  } else if (val == ROTATE_Z) {
    rotateZ(&ui->scene->obj, ui->zRotateSpin->value());
  } else if (val == ZOOM) {
    scale(&ui->scene->obj, ui->zoomSpin->value());
  }
  ui->scene->update();
}

void MainWindow::setColorClicked(int val) {
  if (val == BACK_COLOR) {
    ui->scene->setColor(val);
  } else if (val == LINE_COLOR) {
    ui->scene->setColor(val);
  } else if (val == VERT_COLOR) {
    ui->scene->setColor(val);
  }
  ui->scene->update();
}

void MainWindow::setDrawingModeClicked(int val) {
  ui->scene->setSize(LINES_MODE, ui->linesSizeSpin->value());
  ui->scene->setSize(VERTS_MODE, ui->vertsSizeSpin->value());
  if (val == PARALLEL_PROJECTION) {
    ui->scene->setDrawingMode(val);
  } else if (val == CENTRAL_PROJECTION) {
    ui->scene->setDrawingMode(val);
  } else if (val == SOLID_LINES) {
    ui->scene->setDrawingMode(val);
  } else if (val == DASHED_LINES) {
    ui->scene->setDrawingMode(val);
  } else if (val == DOTTED_LINES) {
    ui->scene->setDrawingMode(val);
  } else if (val == SQUARE_VERTS) {
    ui->scene->setDrawingMode(val);
  } else if (val == CIRCLE_VERTS) {
    ui->scene->setDrawingMode(val);
  } else if (val == HIDDEN_VERTS) {
    ui->scene->setDrawingMode(val);
  }
  ui->scene->update();
}

void MainWindow::on_savePictureButton_clicked() {
  if (ui->scene->isOpened) {
    QDateTime curTime = QDateTime::currentDateTime();
    QString time = curTime.toString("yyyy-MM-dd-hh-mm-ss");
    QString format = "jpeg";
    if (ui->bmpRadio->isChecked()) format = "bmp";
    QString name = "snap" + time + "." + format;
    QImage img = ui->scene->grabFramebuffer();
    img.save(name);
    QMessageBox messageBoxImage;
    messageBoxImage.information(0, "", "Screenshot saved successfully");
  } else {
    QMessageBox warning;
    warning.setWindowTitle("Error");
    warning.setText("Please open .obj file to take a screenshot");
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
  }
}

void MainWindow::on_saveGifButton_clicked() {
  std::thread gif_thread(&GLWidget::saveGif, ui->scene);
  gif_thread.detach();
}

void MainWindow::saveSettings() {
  QSettings settings("settings.conf", QSettings::IniFormat);
  settings.setValue("background", ui->scene->backColor);
  settings.setValue("linesColor", ui->scene->linesColor);
  settings.setValue("verticesColor", ui->scene->vertsColor);
  settings.setValue("linesSize", ui->scene->linesSize);
  settings.setValue("verticesSize", ui->scene->vertsSize);
  settings.setValue("projection", ui->scene->projection);
  settings.setValue("linesMode", ui->scene->linesMode);
  settings.setValue("vertsMode", ui->scene->vertsMode);
  settings.setValue("x_move", ui->xMoveSpin->value());
  settings.setValue("y_move", ui->yMoveSpin->value());
  settings.setValue("z_move", ui->zMoveSpin->value());
  settings.setValue("x_rotation", ui->xRotateSpin->value());
  settings.setValue("y_rotation", ui->yRotateSpin->value());
  settings.setValue("z_rotation", ui->zRotateSpin->value());
  settings.setValue("value_zoom", ui->zoomSpin->value());
}

void MainWindow::loadSettings() {
  QSettings settings("settings.conf", QSettings::IniFormat);
  int confExists = NO;
  if (FILE* file = fopen("settings.conf", "r")) {
    fclose(file);
    confExists = YES;
  }
  if (confExists) {
    ui->scene->backColor = settings.value("background").value<QColor>();
    ui->scene->vertsColor = settings.value("verticesColor").value<QColor>();
    ui->scene->linesColor = settings.value("linesColor").value<QColor>();
    ui->scene->linesSize = settings.value("linesSize").value<GLfloat>();
    ui->scene->vertsSize = settings.value("verticesSize").value<GLfloat>();
    ui->scene->projection = settings.value("projection").toInt();
    ui->scene->linesMode = settings.value("linesMode").toInt();
    ui->scene->vertsMode = settings.value("vertsMode").toInt();
    ui->xMoveSpin->setValue(settings.value("x_move", 1).toDouble());
    ui->yMoveSpin->setValue(settings.value("y_move", 1).toDouble());
    ui->zMoveSpin->setValue(settings.value("z_move", 1).toDouble());
    ui->xRotateSpin->setValue(settings.value("x_rotation", 30).toDouble());
    ui->yRotateSpin->setValue(settings.value("y_rotation", 30).toDouble());
    ui->zRotateSpin->setValue(settings.value("z_rotation", 30).toDouble());
    ui->zoomSpin->setValue(settings.value("value_zoom", 2).toDouble());
    ui->linesSizeSpin->setValue(ui->scene->linesSize);
    ui->vertsSizeSpin->setValue(ui->scene->vertsSize);
    int linesMode = ui->scene->linesMode;
    if (linesMode == SOLID_LINES) {
      ui->setSolidLineRadio->setChecked(YES);
    } else if (linesMode == DASHED_LINES) {
      ui->setDashedLineRadio->setChecked(YES);

    } else if (linesMode == DOTTED_LINES) {
      ui->setDottedLineRadio->setChecked(YES);
    }
    int vertsMode = ui->scene->vertsMode;
    if (vertsMode == SQUARE_VERTS) {
      ui->setSquareVertsRadio->setChecked(YES);
    } else if (vertsMode == CIRCLE_VERTS) {
      ui->setCircleVertsRadio->setChecked(YES);
    } else if (vertsMode == HIDDEN_VERTS) {
      ui->setHiddenVertsRadio->setChecked(YES);
    }
  }
}

void MainWindow::on_openFileButton_clicked() {
  QString file = QFileDialog::getOpenFileName(this, "Выберите файл", "",
                                              "Файлы OBJ (*.obj)");
  if (!file.isEmpty()) {
    ui->scene->fileOpener(file);
    ui->fileInfo->setText(file);
    ui->vertsInfo->setText(QString::number(ui->scene->obj.vertsNum));
    ui->linesInfo->setText(QString::number(ui->scene->obj.dotsNum / 2));
  }
}
