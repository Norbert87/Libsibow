#ifdef _WIN32
 #define WIN 1
#else
 #define WIN 0
#endif

#include <iostream>
#include <fstream>
#include "collection.h"


using namespace std;
using namespace collections;
using namespace items;




int main(int argc, char** argv)
{
    if(argc==4)
    {
        cout<<"TEST EXAMPLE TRAIN COLLECTION."<<endl<<endl<<endl;
        Collection newcol;
        string name,sdetectorDescriptor,smatcher;
        int cluster;
        ifstream in;

        in.open(argv[2]);
        if(!in.is_open())
        {
            cout<<"File colection is not openned."<<endl;
            return 0;
        }

        in >> name;
        in >> sdetectorDescriptor;
        in >> smatcher;
        in >> cluster;
        in.close();


        cout<<"Name: "<<name<<endl<<"Configuration:"<<endl<<" +Detector/Descriptor: "<<sdetectorDescriptor<<endl<<" +Matcher: "<<smatcher<<endl<<" +Cluster: "<<cluster<<endl<<endl;

        newcol.setName(name);
        newcol.setDetectorDescriptor(sdetectorDescriptor);
        newcol.setMatcher(smatcher);
        newcol.setCluster(cluster);

        in.open(argv[3]);
        if(!in.is_open())
        {
            cout<<"File path items is not openned."<<endl;
            return 0;
        }
        string auxName,auxPImage,auxPDescription;
        vector<string> namesItem,pathsImages,pathsDescription;
        do{
            in>>auxName>>auxPImage>>auxPDescription;
            if(!in.eof()||WIN)
            {
                namesItem.push_back(auxName);
                pathsImages.push_back(auxPImage);
                pathsDescription.push_back(auxPDescription);
                newcol.addItems(auxName);
            }

        }while(!in.eof());
        in.close();
        Item auxItem;
        cout<<"Items:"<<endl<<endl;
        for(int i=0;i<namesItem.size();i++)
            cout<<"Name item: "<<namesItem[i]<<endl<<"Path image: "<<pathsImages[i]<<endl<<"Path description: "<<pathsDescription[i]<<endl<<endl;

        string pathroot=argv[1];
        cout<<"Creating folders..,"<<endl;
        if(newcol.createDirectories(pathroot))
        {
            cout<<"Error creating folders..."<<endl;
        }
        vector<int> histogram;
        cout<<"Creating BOW..."<<endl;
        if(!newcol.createVocabulary(pathsImages))
        {
            return 0;
        }
        if(newcol.saveFileCollection(pathroot))
        {
            cout<<"File output collection is not written."<<endl;
            return 0;
        }
        auxItem.setNwords(newcol.getCluster());
        for(int i=0;i<namesItem.size();i++)
        {
            auxItem.setName(namesItem[i]);
            auxItem.setPathImage(pathsImages[i]);
            auxItem.setPathDescription(pathsDescription[i]);
            if(!newcol.createHistogramItem(pathsImages[i],histogram))
                return 0;
            cout<<"Histogram to "<<namesItem[i]<<endl;
            for (std::vector<int>::iterator it = histogram.begin() ; it != histogram.end(); ++it)
            {
                cout<<(int)*it<<" ";
            }
            cout<<endl;
            auxItem.copyHistogram(histogram);
            if(auxItem.writeFile(newcol.getName(),argv[1]))
            {
                cout<<"Item "<<auxItem.getName()<<" collection is not written."<<endl;
                return 0;
            }
            histogram.clear();
            auxItem.clearHistogram();
         }
    }
    else
        cout<<"Please insert traincollection.exe <path collection> <path file config collection> <file items>."<<endl;
    return 0;
}
