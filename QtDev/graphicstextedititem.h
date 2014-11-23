#ifndef GRAPHICSTEXTEDITITEM_H
#define GRAPHICSTEXTEDITITEM_H

#include <QGraphicsTextItem>

class graphicsTextEditItem : public QGraphicsTextItem
{
  Q_OBJECT
public:
  graphicsTextEditItem      (QGraphicsItem * parent = 0);
  graphicsTextEditItem      (const QString & text, QGraphicsItem * parent = 0);
signals:
  void editStarted();
  void editEnded();
protected:
  virtual void focusInEvent (QFocusEvent* event);
  virtual void focusOutEvent(QFocusEvent* event);
};

#endif // GRAPHICSTEXTEDITITEM_H
