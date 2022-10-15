#ifndef SETTINGS_H
#define SETTINGS_H


class Settings
{
public:

    Settings(int framesMEI, int framesMHI, int Var, int Ord , bool isMethode1 , bool isMEI , bool isMHI, bool isprioMEI);

    int framesMEI;
    int framesMHI;
    int Var;
    int Ord;

    bool isMethode1;
    bool isMEI;
    bool isMHI;

    bool isprioMEI;

};

#endif // SETTINGS_H
