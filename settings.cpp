#include "settings.h"

Settings::Settings(int framesMEI, int framesMHI, int Var, int Ord , bool isMethode1 , bool isMEI , bool isMHI, bool isprioMEI)
{

    this->framesMEI = framesMEI;
    this->framesMHI = framesMHI;

    this->Var = Var;

    this->Ord = Ord;

    this->isMethode1 = isMethode1;

    this->isMEI = isMEI;

    this->isMHI = isMHI;

    this->isprioMEI = isprioMEI;

}
