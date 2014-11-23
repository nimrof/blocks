#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include <QPoint>
#include <QObject>

#include "blocks.h"
#include "pindefinition.h"

namespace blocks
{

class block : public QObject
{
  Q_OBJECT
public:
  enum Type
  {
    callBlock,
    constantBlock
  };

  block                        (const itemID ID);
  unsigned int getNumPinsOfType(const pinType pt)                        const;
  pin*         getPinAt        (const itemID index, const pinType type);
  const pin*   getPinAt        (const itemID index, const pinType type)  const;
  size_t       getPinIndex     (const pin* p,const pinType type);
  void         setPos          (QPoint newPosition);
  QPoint       pos             ()                                        const;
  Type         type            ()                                        const;
  itemID       getID           ()                                        const;
signals:
  void blockMoved(const itemID blockID, const QPoint newPositon, const QPoint movement);
protected:
  std::vector<pin*> inputPins;
  std::vector<pin*> outputPins;
  QPoint            position;
  Type              bType;
private:
  itemID            ID;
};

}
#endif // BLOCK_H
