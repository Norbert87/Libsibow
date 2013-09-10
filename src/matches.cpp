/*!
 \file matches.cpp
 \author Norberto Madueño Galán
 \date 2012-2013
 */
#include "matches.h"


using namespace matches;

Match::Match()
{
    setName("noname");
    setTotal(0);
}
Match::Match(string name,double total)
{
    setName(name);
    setTotal(total);
}

void Match::setName(string name)
{
    _name=name;
}
void Match::setTotal(double total)
{
    _total=total;
}

string Match::getName(){return _name;}
double Match::getTotal(){return _total;}

Match & Match::operator =(const Match & I)
{
    _name=I._name;
    _total=I._total;
    return *this;
}

Vectormatches::Vectormatches(){_data=NULL;_nTotal=0;}
Vectormatches::Vectormatches(int n)
{
    _nTotal=n;
    _data=new Match[n];
}
Vectormatches::~Vectormatches()
{
    if(_data!=NULL)
        delete []_data;
}
Match & Vectormatches::operator[](int i)
{

    return _data[i];

}
void Vectormatches::setElement(int pos,double value,string name)
{
    if(pos<_nTotal)
    {
        _data[pos].setName(name);
        _data[pos].setTotal(value);
    }
}
int Vectormatches::getTotal()
{
    return _nTotal;
}
void Vectormatches::orderAscending()
{
    //Algoritmo burbuja

    Match aux;
    for(int i=1;i<_nTotal;i++)
        for(int j=_nTotal-1;j>=i;j--)
        {
            if(_data[j-1].getTotal()>_data[j].getTotal())
            {
                aux=_data[j-1];
                _data[j-1]=_data[j];
                _data[j]=aux;
            }
        }
}
void Vectormatches::orderDescending()
    {
        //Algoritmo burbuja

        Match aux;
        for(int i=1;i<_nTotal;i++)
            for(int j=_nTotal-1;j>=i;j--)
            {
                if(_data[j-1].getTotal()<_data[j].getTotal())
                {
                    aux=_data[j-1];
                    _data[j-1]=_data[j];
                    _data[j]=aux;
                }
            }
    }
