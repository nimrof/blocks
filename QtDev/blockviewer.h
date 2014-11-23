#ifndef BLOCKVIEWER_H
#define BLOCKVIEWER_H

#include <QGraphicsView>
#include "graphicsblockitem.h"

#include "blocks.h"

class BlockViewer : public QGraphicsView
{
  Q_OBJECT
public:
  explicit BlockViewer(QWidget *parent = 0);
  void setCallBlock   (blocks::callDefinition& definition);
protected:
  void dragEnterEvent (QDragEnterEvent *event);
  void dragMoveEvent  (QDragMoveEvent *event);
  void dropEvent      (QDropEvent *event);
  void mousePressEvent(QMouseEvent *event);
private:
  QGraphicsScene     scene;
  graphicsBlockItem* block;
  QString            stringDefinition;
signals:
  
public slots:
  
};

#endif // BLOCKVIEWER_H
