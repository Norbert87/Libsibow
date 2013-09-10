/*!
 \file item.cpp
 \author Norberto Madueño Galán
 \date 2012-2013
 */
#include "item.h"

using namespace items;

Item::Item()
{
    setName("");
    setPathImage("");
    setPathDescription("");
    setNwords(0);

}

Item::Item(string name,string pathImage,string pathDescription,int nWords)
{
    setName(name);
    setPathImage(pathImage);
    setPathDescription(pathDescription);
    setNwords(nWords);
}
Item::~Item(){
    _histogram.clear();}

void Item::clearHistogram(){
    if(!_histogram.empty())
        _histogram.clear();}

string Item::getName(){return _name;}
string Item::getPathImage(){return _pathImage;}
string Item::getPathDescription(){return _pathDescription;}
int Item::getNwords(){return _nWords;}
int Item::getNHistogram(int n){return _histogram.at(n);}

void Item::setName(string name){_name=name;}
void Item::setPathImage(string path){_pathImage=path;}
void Item::setPathDescription(string path){_pathDescription=path;}
void Item::setNwords(int nWords){_nWords=nWords;}
void Item::addHistogram(int value){_histogram.push_back(value);}

void Item::copyHistogram( vector<int> histogram)
{
    for (std::vector<int>::iterator it = histogram.begin() ; it != histogram.end(); ++it)
    {
        addHistogram((int)*it);
    }
}
bool Item::writeFile(string collectionName, string pathCol)
{
    string filename;
    filename=pathCol+BAR+collectionName+BAR+getName()+BAR+getName()+".xml";

    //Apertura del fichero XML
    FileStorage fs;
    fs.open(filename.c_str(),FileStorage::WRITE);
    if (!fs.isOpened()){return true;}
    //Escritura en el fichero XML
    fs<<"Name"<<getName().c_str();
    fs<<"PathImage"<<getPathImage().c_str();
    fs << "PathDescription" << getPathDescription().c_str();
    fs << "Words" << getNwords();
    fs << "Histogram" <<"[" ;
    for(int i=0;i<getNwords();i++)
    {
        fs << getNHistogram(i);
    }
    fs <<"]";
    fs.release();
    return false;

}

bool Item::loadFile(string collectionName, string pathCol)
{
    string filename;
    filename=pathCol+BAR+collectionName+BAR+getName()+BAR+getName()+".xml";
    //Apertura del fichero XML
    FileStorage fs;
    fs.open(filename.c_str(), FileStorage::READ);
    if (!fs.isOpened()){return true;}
    //Lectura del fichero XML
    FileNode m= fs["Name"];
    if(m.empty()){return true;}
    FileNodeIterator it = m.begin(), it_end = m.end();
    string path = (string)*it;
    setName(path);

    m= fs["PathImage"];
    if(m.empty()){return true;}
    it = m.begin(), it_end = m.end();
    path = (string)*it;
    setPathImage(path);

    m= fs["PathDescription"];
    if(m.empty()){return true;}
    it = m.begin();
    path = (string)*it;
    setPathDescription(path);

    m= fs["Words"];
    if(m.empty()){return true;}

    it = m.begin();
    int words=(int)*it;
    setNwords(words);

    m= fs["Histogram"];

    if(m.empty()){return true;}

    it = m.begin(), it_end = m.end();

    int j=0;
    for (; it != it_end; ++it){
        addHistogram((int)*it);
        j++;
    }

    fs.release();

    return false;
}

