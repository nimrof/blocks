#include "graphicstextedititem.h"

graphicsTextEditItem::graphicsTextEditItem(QGraphicsItem* parent) : QGraphicsTextItem(parent)
{

}

graphicsTextEditItem::graphicsTextEditItem(const QString & text, QGraphicsItem * parent)  : QGraphicsTextItem(text, parent)
{

}
void graphicsTextEditItem::focusInEvent(QFocusEvent* event)
{
  QGraphicsTextItem::focusInEvent(event);
  emit editStarted();
}

void graphicsTextEditItem::focusOutEvent(QFocusEvent* event)
{
  QGraphicsTextItem::focusOutEvent(event);
  emit editEnded();
}
