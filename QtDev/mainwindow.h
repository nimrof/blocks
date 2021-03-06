#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QModelIndex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
    
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    
private slots:
  void on_actionTest_triggered();

  void on_treeView_clicked(const QModelIndex &index);

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
