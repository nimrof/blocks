#ifndef CALL_H
#define CALL_H

#include <QObject>
#include <QPoint>

#include "blocks.h"
#include "block.h"

namespace blocks
{

class call : public block
{
public:
  call                             (const itemID ID, callDefinition *callDef);
  callDefinition* getcallDefinition()                                               const;
signals:
  void pinConnetionChanged         (const pin* const p);
private slots:
  void updateDefinitionChanged     (void);
  void pinConnetionChanged         (const pin* const p,const pinType type);
private:
  callDefinition* definition;
};

}

#endif // CALL_H
