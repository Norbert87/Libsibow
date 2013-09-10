/*!
 \file collection.h
 \author Norberto Madueño Galán
 \date 2012-2013
 */
#ifndef COLLECTION_H
#define COLLECTION_H

/*! \def BAR
\brief Constante para definir la barra inclinada.
La barra estará inclinada hacia la izquierda si estamos en un sistema operativo Windows
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
* \details Esta clase se usa para describir una colección temática.
*/
class SIBOW_EXPORT Collection
{
public:
    //! Constructor.
    /*!
      Constructor vacío de la clase.
    */
    Collection();
    //! Destructor.
    /*!
      Destructor de la clase.
    */
    ~Collection();

    //! Método para devolver el nombre de la colección.
    /*!
      \return Instancia de la clase string con el nombre de la colección
    */
    string getName();
    //! Método para devolver el nombre del detector/descriptor que utiliza la colección.
    /*!
      \return Instancia de la clase string con el nombre del Detector/Descriptor
    */
    string getDetectorDescriptor();
    //! Método para devolver el nombre del Matcher de la colección.
    /*!
      \return Instancia de la clase string con el nombre del Matcher
    */
    string getMatcher();
    //! Método para devolver el vocabulario de la colección.
    /*!
      \return Instancia de la clase Mat que contiene el vocabulario
    */
    Mat getVocabulary();
    //! Método para devolver el nombre de la elemento de la colección.
    /*!
      \param nItem Entero que indica la posición del item del que se obtiene su nombre
      \return Instancia de la clase string con el nombre de un elemento de la colección
    */
    string getItems(int nItem);
    //! Método para devolver el número de palabras del vocabulario.
    /*!
      \return Entero con el numero de palabras.
    */
    int getCluster();
    //! Método para devolver el número de elementos de la colección.
    /*!
      \return Entero con el numero de elementos.
    */
    int getNitems();
    //! Método para introducir el nombre de la colección.
    /*!
      \param name Instancia de la clase string con el nombre de la colección.
    */
    void setName(string name);
    //! Método para introducir el nombre del detector/descriptor que usa la colección.
    /*!
      \param detectorDescriptor Instancia de la clase string con el nombre del detector/descriptor.
    */
    void setDetectorDescriptor(string detectorDescriptor);
    //! Método para introducir el nombre del matcher que usa la colección.
    /*!
      \param matcher Instancia de la clase string con el nombre del matcher.
    */
    void setMatcher(string matcher);
    //! Método para introducir el número de palabras de la colección.
    /*!
      \param n Entero con el número de palabras.
    */
    void setCluster(int n);
    //! Método para introducir el vocabulario de la colección.
    /*!
      \param vocabulary Instancia de la clase Mat que contiene el vocabulario.
    */
    void setVocabulary(Mat vocabulary);
    //! Método para añadir elementos a la colección.
    /*!
      \param item Instancia  de la clase string que contiene el nombre del elemento.
    */
    void addItems(string item);

    //! Método para eliminar elementos a la colección dada la posición.
    /*!
      \param position Entero con el número de posición que se desea eliminar.
      \return Boleano que confirma si se ha eliminado(true) o no(false).
    */
    bool deleteItem(int position);
    //! Método para crear histograma de frecuencias .
    /*!
      \param pathImage Instancia de la clase string con la ruta de la imagen.
      \return Vector de enteros con el numero de frecuencias.
    */
    bool createHistogramItem( string pathImage, vector<int> &histogram);
    //! Método para crear vocabulario de la colección .
    /*!
      \param paths Vector de instancias de la clase string con las rutas de las imágenes.
      \return Boleano confirmando si se ha creado correctamente (true) o no (false)
    */
    bool createVocabulary(const vector<string> &paths);
    //! Método para crear el árbol de carpetas.
    /*!
      \param pathCollections Instancia de la clase string con la ruta raíz donde se encuentran las colecciones.
      \return Boleano confirmando que existe un error(true) o no (false) en la creación.
    */
    bool createDirectories(string pathCollections);
    //! Método para comparar dos historgramas de frecuencias .
    /*!
      \param histogramObject Vector de enteros con el numero de frecuencias.
      \param histogramCol Vector de enteros con el numero de frecuencias.
      \return Real con el valor de coincidencia.
    */
    double getMatches(vector<int> histogramObject,vector<int> histogramCol);
    //! Método para conseguir coincidencias entre dos imágenes.
    /*!
      \param pathObject Instancia de la clase string con la ruta de la imagen.
      \param pathCol Instancia de la clase string con la ruta de la imagen.
      \return Entero con el número de coincidencias espaciales.
    */
    int getMachesAdvanced(string pathCol,string pathObject);
    //! Método para cargar los datos de una colección desde un fichero XML.
    /*!
      \pre Haber introducido el nombre de la colección.
      \param pathCol Instancia de la clase string con la ruta raíz donde se encuentran las colecciones.
      \return Boleano confirmando que existe un error(true) o no (false) en la carga del fichero.
    */
    bool loadFileCollection(string pathCol);
    //! Método para guardar los datos de una colección desde un fichero XML.
    /*!
      \pre Haber introducido el nombre de la colección.
      \param pathCol Instancia de la clase string con la ruta raíz donde se encuentran las colecciones.
      \return Boleano confirmando que existe un error(true) o no (false) al salvar el fichero.
    */
    bool saveFileCollection(string pathCol);
//! \privatesection
private:
    //! Variable privada con el nombre de la colección.
    string _name;
    //! Variable privada con el nombre del detector/descriptor.
    string _detectorDescriptor;
    //! Variable privada con el nombre del matcher.
    string _matcher;
    //! Variable privada con el vocabulario.
    Mat _vocabulary;
    //! Variable privada con número de palabras del vocabulario.
    int _cluster;
    //! Variable privada con los nombres de los elementos de la colección.
    vector<string> _items;

};
}
#endif // COLLECTION_H
