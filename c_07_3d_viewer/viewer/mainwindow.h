#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDateTime>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QString>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "gif.h"
#include "glwidget.h"

#ifdef __cplusplus
extern "C" {
#include "../3d_viewer.h"
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void saveSettings();
  void loadSettings();

 private slots:
  void mrzClicked(int val);
  void setColorClicked(int val);
  void setDrawingModeClicked(int val);
  void on_openFileButton_clicked();
  void on_savePictureButton_clicked();
  void on_saveGifButton_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
