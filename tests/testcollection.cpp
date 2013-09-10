#include <iostream>
#include <fstream>
#include "collection.h"
#include "matches.h"

using namespace std;
using namespace collections;
using namespace items;
using namespace matches;


int main(int argc, char *argv[])
{
    if(argc==3)
    {
        cout<<"TEST EXAMPLE COLLECTION."<<endl<<endl<<endl;

        Collection newcol;
        ifstream in;


        vector<int> histogramObject;
        vector<int> histogramCol;
        double aux;
        string path,namecol;
        in.open(argv[2]);
        if(!in.is_open())
        {
            cout<<"ERROR: File object is not openned."<<endl;
            return 0;
        }
        in>>namecol>>path;
        cout<<"Name collection to search: "<<namecol<<endl<<"Path image scene: "<<path<<endl;
        newcol.setName(namecol);
        if(newcol.loadFileCollection(argv[1]))
        {
            cout<<"ERROR: Collection is not loaded."<<endl;
            return 0;
        }
        Vectormatches score(newcol.getNitems());

        if(!newcol.createHistogramItem(path,histogramObject))
            return 0;
        for (std::vector<int>::iterator it = histogramObject.begin() ; it != histogramObject.end(); ++it)
        {
            cout<<(int)*it<<" ";
        }
        cout<<endl<<"Histogram object created."<<endl;

        Item auxItem;
       for(int i=0;i<newcol.getNitems();i++)
       {
           auxItem.setName(newcol.getItems(i));
           if(auxItem.loadFile(newcol.getName(),argv[1]))
           {
               cout<<"ERROR: Item "<<newcol.getItems(i)<<" is not loaded."<<endl;
               return 0;
           }

           for(int j=0;j<auxItem.getNwords();j++)
            histogramCol.push_back(auxItem.getNHistogram(j));

           aux=newcol.getMatches(histogramObject,histogramCol);
           histogramCol.clear();
           auxItem.clearHistogram();
           score[i].setName(newcol.getItems(i));
           score[i].setTotal(aux);
       }
       score.orderAscending();
       cout<<endl<<"Score:"<<endl;
       for(int i=0;i<newcol.getNitems();i++)
       {
           cout<<i+1<<"."<<score[i].getName()<<"->"<<score[i].getTotal()<<endl;
       }

       cout<<"Pulse una tecla para continuar..."<<endl;
       getchar();


       cout<<endl<<endl<<"TEST SPACIAL MATCHES"<<endl;

       int valueMatch;


       for(int i=0;i<newcol.getNitems();i++)
       {
           auxItem.setName(newcol.getItems(i));
           if(auxItem.loadFile(newcol.getName(),argv[1]))
           {
               cout<<"ERROR: Item "<<newcol.getItems(i)<<" is not loaded."<<endl;
               return 0;
           }
           valueMatch=newcol.getMachesAdvanced(auxItem.getPathImage(),path);
           score[i].setName(newcol.getItems(i));
           score[i].setTotal((double)valueMatch);
       }
       score.orderDescending();
       cout<<endl<<endl<<"Score:"<<endl;
       for(int i=0;i<newcol.getNitems();i++)
       {
           cout<<i+1<<"."<<score[i].getName()<<"->"<<score[i].getTotal()<<endl;
       }
   }
   else
        cout<<"Please, insert testcollection.exe <path collection> <path file object>"<<endl;
   return 0;
}
