#ifndef DEVICECONNECTION_H
#define DEVICECONNECTION_H


#include <vector>
#include <QString>

enum VM_Commands
{
  VM_STOP,
  VM_START,
  VM_GET_INFO
};

class DeviceConnectionCallBackObject//For the dll to call program
{
  virtual std::vector<char> getsourceFileData (std::string path) = 0;
  virtual std::vector<char> getbinaryData     (std::string path) = 0;
  virtual void              reportError       (unsigned short)   = 0;
};

class DeviceConnection
{
public:
  virtual QString getShortName() = 0;
/*
  virtual void    prepare()                                                                        = 0;
  virtual void    init(std::string connectionstring)                                               = 0;
  virtual void    connect()                                                                        = 0;
  virtual void    isConnected()                                                              const = 0;
  virtual void    release()                                                                        = 0;

  virtual void              isPackageWaiting(unsigned int vm)                                const = 0;
  virtual std::vector<char> getPackage      (unsigned int vm)                                      = 0;
  virtual void              sendPackage     (unsigned int vm, std::vector<char> packageData)       = 0;
  virtual bool              packageWaiting  (unsigned int vm)                                      = 0;
*/
};

Q_DECLARE_INTERFACE( DeviceConnection, "com.blocks.DeviceConnection/0.1" )

#endif // DEVICECONNECTION_H
