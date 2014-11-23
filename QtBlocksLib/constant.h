#ifndef CONSTANT_H
#define CONSTANT_H

#include <QString>

#include "blockvariable.h"
#include "block.h"

namespace blocks
{

class constant : public block
{
public:
  constant               (const itemID ID);
  constant               (const itemID ID, const QString type, const QString value);
  constant               (const itemID ID, const blockVariable& constantValue);
  const blockVariable& constObj(void) const;
  blockVariable&      Obj(void);
signals:
  void constantChange    (const constant* const c);
  void valueChange       (const constant* const c);
private:
  blockVariable constantValue;
};

}
#endif // CONSTANT_H
