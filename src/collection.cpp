/*!
 \file collection.cpp
 \author Norberto Madueño Galán
 \date 2012-2013
 */
#include "collection.h"

using namespace collections;

Collection::Collection()
{
    setName("");
    setDetectorDescriptor("");
    setMatcher("");
    setCluster(0);

}
Collection::~Collection()
{
   _items.clear();
}

string Collection::getName(){return _name;}
string Collection::getDetectorDescriptor(){return _detectorDescriptor;}
string Collection::getMatcher(){return _matcher;}
Mat Collection::getVocabulary(){return _vocabulary;}
string Collection::getItems(int nItem){return _items[nItem];}
int Collection::getCluster(){return _cluster;}
int Collection::getNitems(){return _items.size();}

void Collection::setName(string name){_name=name;}
void Collection::setDetectorDescriptor(string detectorDescriptor){_detectorDescriptor=detectorDescriptor;}
void Collection::setMatcher(string matcher){_matcher=matcher;}
void Collection::setCluster(int n){_cluster=n;}
void Collection::setVocabulary(Mat vocabulary){_vocabulary=vocabulary;}

void Collection::addItems(string item){_items.push_back(item);}

bool Collection::deleteItem(int position)
{
    bool deleted=false;
    int j;
    //Si la posición es la última se quita
    if(position==(_items.size()-1))
    {
        _items.pop_back();
        deleted=true;
    }
    else
    {
        //Desplazamos los nombres una posición anterior y elimamos la última posición
        for(j=position;j<_items.size()-1;j++)
        {
            _items[j]=_items[j+1];
        }
        _items.pop_back();
        deleted=true;
     }

    return deleted;
}


bool Collection::createVocabulary(const std::vector<string> & paths)
{

   //Declaraciones
    Mat imgData;

    Ptr<FeatureDetector> detector;
    detector =  FeatureDetector::create(getDetectorDescriptor().c_str());
    if(detector==NULL)
        return false;

    vector<KeyPoint> keypoints_imgData;

    BOWKMeansTrainer bowtrainer(getCluster());

    Ptr<DescriptorExtractor> extractor;
    extractor=DescriptorExtractor::create(getDetectorDescriptor().c_str());
    if(extractor==NULL)
        return false;

    Mat descriptors_imgData;
    Item aux;


    for(int i=0;i<getNitems();i++){
       //Carga de imagen
       imgData = imread( paths[i].c_str(), CV_LOAD_IMAGE_GRAYSCALE );
       if(!imgData.data)
       {
           cout<<"Error open path: "<<paths[i]<<endl;
           return false;
       }
       //Detección de puntos claves
       detector->detect(imgData,keypoints_imgData);
       //Descripción de puntos claves de la imagen
       extractor->compute( imgData,keypoints_imgData, descriptors_imgData);
       //Añadimos al entrenador de la bolsa de palabras
       bowtrainer.add(descriptors_imgData);
       cout<<"Added: "<<paths[i]<<endl;
    }
    //Clusterizando vocabulario
    setVocabulary(bowtrainer.cluster());
    cout<<"Vocabulary complete."<<endl;
    return true;
 }
bool  Collection::createHistogramItem( string pathImage, vector<int> & histogram)
{
    //Inicialización de histograma de frecuencias
    for( unsigned int i = 0; i < getCluster(); i++ )
    {
        histogram.push_back(0);
    }
    //Carga de imagen
    Mat img_object = imread(pathImage.c_str(), CV_LOAD_IMAGE_GRAYSCALE );
    if(!img_object.data)
    {
        cout<<"Error open path: "<<pathImage<<endl;
        return false;
    }
    //Declaraciones
    Ptr<FeatureDetector> detector;
    detector=FeatureDetector::create(getDetectorDescriptor().c_str());
    if(detector==NULL)
        return false;

    std::vector<KeyPoint> keypoints_object;

    Ptr<DescriptorExtractor> extractor;
    extractor=DescriptorExtractor::create(getDetectorDescriptor().c_str());
    if(extractor==NULL)
        return false;

    Mat descriptors_object;

    Ptr<DescriptorMatcher> matcher;
    matcher= DescriptorMatcher::create(getMatcher().c_str());
    if(matcher==NULL)
        return false;

    std::vector< DMatch > matches;
     //Detección de puntos claves
    detector->detect( img_object, keypoints_object );
    //Descripción de puntos claves de la imagen
    extractor->compute( img_object, keypoints_object, descriptors_object );
    //Emparejamiento de puntos clave de la imagen con el vocabulario
    matcher->match( descriptors_object, getVocabulary(), matches );



    //Introdución de frecuencias en histograma
    for( unsigned int i = 0; i < matches.size(); i++ )
    {

      histogram[matches[i].trainIdx]++;
    }
    return true;

}
bool Collection::saveFileCollection(string pathCol)
{
    string filename;
    filename=pathCol+BAR+getName()+BAR+getName()+".xml";
    FileStorage fs;

    //Apertura de fichero XML
    fs.open(filename.c_str(), FileStorage::WRITE);
    if (!fs.isOpened()){cout<<"File no open"<<endl;return true;}

    //Escritura de fichero XML
    fs<<"Name"<<getName().c_str();
    fs<<"Detector-Descriptor"<<getDetectorDescriptor().c_str();
    fs<<"Matcher"<<getMatcher().c_str();
    fs<<"Cluster"<<getCluster();

    fs <<"Items" << "[" ;
    for(int i=0;i<getNitems();i++)
    {
        fs << getItems(i).c_str();
    }
    fs <<"]";
    fs <<"Vocabulary"<<getVocabulary();

    //Cierre de fichero XML
    fs.release();

    return false;
}
bool Collection::loadFileCollection(string pathCol)
{
    string filename;
    filename=pathCol+BAR+getName()+BAR+getName()+".xml";
    FileStorage fs;
     //Apertura de fichero XML
    fs.open(filename.c_str(), FileStorage::READ);
    if (!fs.isOpened()){return true;}

    //Carga de datos del fichero XML
    FileNode m= fs["Name"];
    if(m.empty()){return true;}
    FileNodeIterator it = m.begin(), it_end = m.end();
    string path = (string)*it;
    setName(path);

    m= fs["Detector-Descriptor"];
    if(m.empty()){return true;}
    it = m.begin();
    path = (string)*it;
    setDetectorDescriptor(path);

    m= fs["Matcher"];
    if(m.empty()){return true;}
    it = m.begin();
    path = (string)*it;
    setMatcher(path);

    m= fs["Cluster"];
    if(m.empty()){return true;}
    it = m.begin();
    setCluster((int)*it);

    m = fs["Items"];

    it = m.begin(), it_end = m.end();
    for (; it != it_end; ++it)
        addItems((string)*it);
    Mat vocabulary;
    fs["Vocabulary"]>>vocabulary;

    setVocabulary(vocabulary);

    fs.release();

    return false;
}
double Collection::getMatches(vector<int> histogramObject,vector<int> histogramCol)
{
    int totalObject=0;
    int totalCol=0;
    long double total=0.0;
    float * histogramNorObject;
    histogramNorObject=new float[getCluster()];
    float *histogramNorCol;
    histogramNorCol=new float[getCluster()];

    //Obtención del total de coincidencias
    for(int i=0;i<getCluster();i++)
    {
        totalObject+=histogramObject[i];
        totalCol+=histogramCol[i];
    }
    //Obtención de histogramas normalizados
    for(int i=0;i<getCluster();i++)
        {
            histogramNorObject[i]=(float)histogramObject[i]/(float)totalObject;
            histogramNorCol[i]=(float)histogramCol[i]/(float)totalCol;
        }
    //Obtención del grado de similitud entre los dos histogramas
    for(int i=0;i<getCluster();i++)
            {
                total+=pow((histogramNorObject[i]-histogramNorCol[i]),2);
            }
    total=sqrt(total);
    //Liberación de memoria
    delete[]histogramNorObject;
    delete[]histogramNorCol;

    return (double)total;
}
int Collection::getMachesAdvanced(string pathCol,string pathObject)
{
    //Carga de imágenes
    Mat img_object = imread(pathObject, CV_LOAD_IMAGE_GRAYSCALE );
    if(!img_object.data)
    {
        cout<<"Error open path: "<<pathObject<<endl;
        return 0;
    }
    Mat img_scene = imread(pathCol, CV_LOAD_IMAGE_GRAYSCALE );
    if(!img_scene.data)
    {
        cout<<"Error open path: "<<pathCol<<endl;
        return 0;
    }
    //Declaraciones
    Ptr<FeatureDetector> detector;
    detector= FeatureDetector::create(getDetectorDescriptor().c_str());;
    if(detector==NULL)
        return false;
    std::vector<KeyPoint> keypoints_object, keypoints_scene;//Variables con los puntos clave
    Ptr<DescriptorExtractor> extractor;
    extractor=DescriptorExtractor::create(getDetectorDescriptor().c_str());
    if(extractor==NULL)
        return false;
    Mat descriptors_object, descriptors_scene;//Matrices con la descripción de los puntos clave
    Ptr<DescriptorMatcher> matcher;
    matcher=DescriptorMatcher::create(getMatcher().c_str());
    if(matcher==NULL)
        return false;
    std::vector< DMatch > matches;//Vector con los emparejamientos


    //Detección de puntos claves
    detector->detect( img_object, keypoints_object );
    detector->detect( img_scene, keypoints_scene );
    //Descripción de puntos claves
    extractor->compute( img_object, keypoints_object, descriptors_object );
    extractor->compute( img_scene, keypoints_scene, descriptors_scene );
    //Emparejamiento de puntos claves entre las dos imágenes
    matcher->match( descriptors_object, descriptors_scene, matches );


    //Declaraciones de vectores de coordenadas de puntos
    std::vector<Point2f> obj;
    std::vector<Point2f> scene;

    //Relleno de vectores con las coordenadas de los puntos clave
    for( unsigned int i = 0; i < matches.size(); i++ )
          {
            obj.push_back( keypoints_object[ matches[i].queryIdx ].pt );
            scene.push_back( keypoints_scene[ matches[i].trainIdx ].pt );
          }
    //Obtención de matriz de homografía utilizando el algoritmo RANSAC
    Mat H = findHomography( obj, scene, CV_RANSAC );

    int matches_total=0;//variable para almacenar coincidencias totales

    double auxX,auxY,Error;

    //Obtención del error espacial y descarte de los punto no válidos
    for( unsigned int i=0;i<obj.size();i++)
    {
          auxX=(H.at<double>(0,0)*obj[i].x + H.at<double>(0,1)*obj[i].y + H.at<double>(0,2));
          auxX=auxX/(H.at<double>(2,0)*obj[i].x + H.at<double>(2,1)*obj[i].y + H.at<double>(2,2));
          auxX=scene[i].x-auxX;
          auxX=pow(auxX,2);
          auxY=(H.at<double>(1,0)*obj[i].x + H.at<double>(1,1)*obj[i].y + H.at<double>(1,2));
          auxY=auxY/(H.at<double>(2,0)*obj[i].x + H.at<double>(2,1)*obj[i].y + H.at<double>(2,2));
          auxY=scene[i].y-auxY;
          auxY=pow(auxY,2);
          Error=auxX+auxY;
          if(Error<=50){
              matches_total++;
          }
    }
    return(matches_total);
}
bool Collection::createDirectories(string pathCollections)
{
    string path="mkdir "+pathCollections+BAR+getName();
    string pathItem;
    bool error=false;
    if(getName().empty()||_items.empty())
       error=true;
    else
    {
        //Creación de carpeta con el nombre de la colección
        system(path.c_str());

        for(int i=0;i<getNitems();i++)
        {
            pathItem=path+BAR+getItems(i);
            //Creación de la carpeta con el nombre del elemento de la colección
            system(pathItem.c_str());
        }

    }
    return error;
}

