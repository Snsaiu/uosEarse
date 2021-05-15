#include "checkerfacade.h"
#include "checkerfactory.h"
#include "checkerdiskabstraction.h"
#include "filterharddiskproxy.h"
CheckerFacade::CheckerFacade()
{
    this->Add();
}

vector<HardDiskModel> CheckerFacade::Check()
{
   return this->checkerStrategy.Perform();
}

void CheckerFacade::Add()
{
    CheckerFactory cf;


//    this->checkerStrategy.AddChecker(cf.CreateUsbChecker());
    this->checkerStrategy.AddChecker(cf.CreateHardDiskChecker());
    //todo add other checker
}
