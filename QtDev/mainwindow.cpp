#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "project.h"

#include "projecttreemodel.h"
#include "projecttreeitem.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  QString ipath = "../test.xml";
  QString opath = "../test_out.xml";
  QString errror;
  ui->setupUi(this);

  if( blocks::project::xsdValidateFile(ipath, errror) == true)
  {
    blocks::project*  test = blocks::project::loadFile(ipath);
//    test->saveFile(opath,90);
    projectTreeModel* gg = new projectTreeModel(*test,0);

    ui->treeView->setModel(gg);
    ui->treeView->show();
  }
}
MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::on_actionTest_triggered()
{
  //ui->blockViewer->
}
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
  projectTreeItem* treeItem = static_cast<projectTreeItem*>(index.internalPointer());

  itemType treeItemType = treeItem->getType();
  if(treeItemType == callDefinition)
  {
    blocks::callDefinition* bd = static_cast<blocks::callDefinition*>( treeItem->getRawData() );
    ui->blockViewer->setCallBlock(*bd);
  }
  else if(treeItemType == script)
  {
    blocks::script* bd = static_cast<blocks::script*>( treeItem->getRawData() );
    ui->scriptViewer->LoadScript(*bd);
  }
}
