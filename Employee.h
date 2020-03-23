#ifndef Employee_h
#define Employee_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>

using namespace std;

class Employee
{
    int empID;
    int totalnum;
    int posfb;
    int negfb;
    int score() {return (2 * totalnum) + posfb - negfb;};
public:
    void getID(string x){empID=stoi(x);};
    void gettotal(string x){totalnum=stoi(x);};
    void getpos(string x){posfb = stoi(x);};
    void getneg(string x){negfb=stoi(x);};
    
    Employee operator=( Employee&) ;
    
    int empidout(){return empID;};
    int totnumout(){return totalnum;};
    int posfbout(){return posfb;};
    int negfbout(){return negfb;};
    int scoreout(){return score();};
    
    Employee(){};
    Employee(int x, int y, int z, int k){empID=x;totalnum=y;posfb=z;negfb=k;};
};

#endif