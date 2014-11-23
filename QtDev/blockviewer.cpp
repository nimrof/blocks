#include <algorithm>

#include <QRectF>
#include <QSizeF>
#include <QPainter>
#include <QGraphicsSimpleTextItem>
#include <QPixmap>
#include <QStyleOptionGraphicsItem>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>

#include "graphicscallitem.h"
#include "calldefinition.h"

#include "blockviewer.h"

BlockViewer::BlockViewer(QWidget *parent) : QGraphicsView(parent)
{
  block = NULL;
  setScene(&scene);
  setRenderHint(QPainter::Antialiasing,true);
}
void BlockViewer::setCallBlock(blocks::callDefinition& definition)
{
  if(block != NULL)
  {
    delete block;
  }
  scene.clear();

  block = new graphicsCallItem(&definition);
  stringDefinition = definition.getFullName();
  scene.addItem( block );
}
void BlockViewer::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasFormat("application/x-blocks"))
  {
    if (event->source() == this)
    {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    }
    else
    {
      event->acceptProposedAction();
    }
  }
  else
  {
    event->ignore();
  }
}
void BlockViewer::dragMoveEvent(QDragMoveEvent *event)
{
  if (event->mimeData()->hasFormat("application/x-blocks/call/link"))
  {
    if (event->source() == this)
    {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    }
    else
    {
      event->acceptProposedAction();
    }
  } else
  {
    event->ignore();
  }
}
void BlockViewer::dropEvent(QDropEvent *event)
{





  event->accept();
}
void BlockViewer::mousePressEvent(QMouseEvent* event)
{
  if(block == NULL)
  {
    return;
  }

  QPixmap* pixmap = new QPixmap(500,500);

  QStyleOptionGraphicsItem pixmapStyle;
  QPainter painter(pixmap);
  painter.translate(event->pos());
  painter.setRenderHint(QPainter::Antialiasing);
  block->paint(&painter, &pixmapStyle, 0);
  QList<QGraphicsItem *> children = block->childItems();
  for (int i = 0; i < children.size(); ++i)
  {
    QGraphicsItem* child = children.at(i);
    QPointF pos = child->pos() + event->pos();
    painter.translate(pos);
    (*child).paint(&painter, &pixmapStyle, 0);
    painter.resetTransform();
  }

  painter.end();

  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  dataStream << stringDefinition;

  QMimeData *mimeData = new QMimeData;
  mimeData->setData("application/x-blocks/call/link", itemData);

  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setPixmap(*pixmap);
  drag->setHotSpot(event->pos());

  drag->exec(Qt::CopyAction);
}
