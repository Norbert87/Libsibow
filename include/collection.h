/*!
 \file collection.h
 \author Norberto Madue�o Gal�n
 \date 2012-2013
 */
#ifndef COLLECTION_H
#define COLLECTION_H

/*! \def BAR
\brief Constante para definir la barra inclinada.
La barra estar� inclinada hacia la izquierda si estamos en un sistema operativo Windows
o hacia la derecha si estamos en otro sistema operativo diferente.
*/
#ifdef _WIN32
#define BAR "\\"
#else
#define BAR "/"
#endif

#include <string>
#include <vector>
#include <iostream>


#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"



#include "item.h"


/*! \namespace std
\brief Espacio de nombres para uso de la clase string
*/
using namespace std;
/*! \namespace cv
\brief Espacio de nombres para uso de la clases y funciones de vision artifical de openCV
*/
using namespace cv;
/*! \namespace items
\brief Espacio de nombres para uso de la clase Item
*/
using namespace items;

/*! \namespace collections
\brief Espacio de nombres para uso de la clase Collection
*/
namespace collections{
/*!
* \class Collection
* \brief Clase Collection.
* \details Esta clase se usa para describir una colecci�n tem�tica.
*/
class SIBOW_EXPORT Collection
{
public:
    //! Constructor.
    /*!
      Constructor vac�o de la clase.
    */
    Collection();
    //! Destructor.
    /*!
      Destructor de la clase.
    */
    ~Collection();

    //! M�todo para devolver el nombre de la colecci�n.
    /*!
      \return Instancia de la clase string con el nombre de la colecci�n
    */
    string getName();
    //! M�todo para devolver el nombre del detector/descriptor que utiliza la colecci�n.
    /*!
      \return Instancia de la clase string con el nombre del Detector/Descriptor
    */
    string getDetectorDescriptor();
    //! M�todo para devolver el nombre del Matcher de la colecci�n.
    /*!
      \return Instancia de la clase string con el nombre del Matcher
    */
    string getMatcher();
    //! M�todo para devolver el vocabulario de la colecci�n.
    /*!
      \return Instancia de la clase Mat que contiene el vocabulario
    */
    Mat getVocabulary();
    //! M�todo para devolver el nombre de la elemento de la colecci�n.
    /*!
      \param nItem Entero que indica la posici�n del item del que se obtiene su nombre
      \return Instancia de la clase string con el nombre de un elemento de la colecci�n
    */
    string getItems(int nItem);
    //! M�todo para devolver el n�mero de palabras del vocabulario.
    /*!
      \return Entero con el numero de palabras.
    */
    int getCluster();
    //! M�todo para devolver el n�mero de elementos de la colecci�n.
    /*!
      \return Entero con el numero de elementos.
    */
    int getNitems();
    //! M�todo para introducir el nombre de la colecci�n.
    /*!
      \param name Instancia de la clase string con el nombre de la colecci�n.
    */
    void setName(string name);
    //! M�todo para introducir el nombre del detector/descriptor que usa la colecci�n.
    /*!
      \param detectorDescriptor Instancia de la clase string con el nombre del detector/descriptor.
    */
    void setDetectorDescriptor(string detectorDescriptor);
    //! M�todo para introducir el nombre del matcher que usa la colecci�n.
    /*!
      \param matcher Instancia de la clase string con el nombre del matcher.
    */
    void setMatcher(string matcher);
    //! M�todo para introducir el n�mero de palabras de la colecci�n.
    /*!
      \param n Entero con el n�mero de palabras.
    */
    void setCluster(int n);
    //! M�todo para introducir el vocabulario de la colecci�n.
    /*!
      \param vocabulary Instancia de la clase Mat que contiene el vocabulario.
    */
    void setVocabulary(Mat vocabulary);
    //! M�todo para a�adir elementos a la colecci�n.
    /*!
      \param item Instancia  de la clase string que contiene el nombre del elemento.
    */
    void addItems(string item);

    //! M�todo para eliminar elementos a la colecci�n dada la posici�n.
    /*!
      \param position Entero con el n�mero de posici�n que se desea eliminar.
      \return Boleano que confirma si se ha eliminado(true) o no(false).
    */
    bool deleteItem(int position);
    //! M�todo para crear histograma de frecuencias .
    /*!
      \param pathImage Instancia de la clase string con la ruta de la imagen.
      \return Vector de enteros con el numero de frecuencias.
    */
    bool createHistogramItem( string pathImage, vector<int> &histogram);
    //! M�todo para crear vocabulario de la colecci�n .
    /*!
      \param paths Vector de instancias de la clase string con las rutas de las im�genes.
      \return Boleano confirmando si se ha creado correctamente (true) o no (false)
    */
    bool createVocabulary(const vector<string> &paths);
    //! M�todo para crear el �rbol de carpetas.
    /*!
      \param pathCollections Instancia de la clase string con la ruta ra�z donde se encuentran las colecciones.
      \return Boleano confirmando que existe un error(true) o no (false) en la creaci�n.
    */
    bool createDirectories(string pathCollections);
    //! M�todo para comparar dos historgramas de frecuencias .
    /*!
      \param histogramObject Vector de enteros con el numero de frecuencias.
      \param histogramCol Vector de enteros con el numero de frecuencias.
      \return Real con el valor de coincidencia.
    */
    double getMatches(vector<int> histogramObject,vector<int> histogramCol);
    //! M�todo para conseguir coincidencias entre dos im�genes.
    /*!
      \param pathObject Instancia de la clase string con la ruta de la imagen.
      \param pathCol Instancia de la clase string con la ruta de la imagen.
      \return Entero con el n�mero de coincidencias espaciales.
    */
    int getMachesAdvanced(string pathCol,string pathObject);
    //! M�todo para cargar los datos de una colecci�n desde un fichero XML.
    /*!
      \pre Haber introducido el nombre de la colecci�n.
      \param pathCol Instancia de la clase string con la ruta ra�z donde se encuentran las colecciones.
      \return Boleano confirmando que existe un error(true) o no (false) en la carga del fichero.
    */
    bool loadFileCollection(string pathCol);
    //! M�todo para guardar los datos de una colecci�n desde un fichero XML.
    /*!
      \pre Haber introducido el nombre de la colecci�n.
      \param pathCol Instancia de la clase string con la ruta ra�z donde se encuentran las colecciones.
      \return Boleano confirmando que existe un error(true) o no (false) al salvar el fichero.
    */
    bool saveFileCollection(string pathCol);
//! \privatesection
private:
    //! Variable privada con el nombre de la colecci�n.
    string _name;
    //! Variable privada con el nombre del detector/descriptor.
    string _detectorDescriptor;
    //! Variable privada con el nombre del matcher.
    string _matcher;
    //! Variable privada con el vocabulario.
    Mat _vocabulary;
    //! Variable privada con n�mero de palabras del vocabulario.
    int _cluster;
    //! Variable privada con los nombres de los elementos de la colecci�n.
    vector<string> _items;

};
}
#endif // COLLECTION_H
