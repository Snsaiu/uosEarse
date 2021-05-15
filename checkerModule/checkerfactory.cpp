#include "checkerfactory.h"


CheckerFactory::CheckerFactory()
{
}

CheckerFactory::~CheckerFactory()
{
}

CheckerDiskAbstraction* CheckerFactory::CreateHardDiskChecker()
{
     HardDiskChecker* hdc =new HardDiskChecker () ;
     return hdc;
}

CheckerDiskAbstraction* CheckerFactory::CreateUsbChecker()
{
    UsbChecker *usb=new UsbChecker();
    return usb;
}
