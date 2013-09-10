/*!
 \file item.h
 \author Norberto Madueño Galán
 \date 2012-2013
 */
#ifndef ITEM_H
#define ITEM_H

#include <export.h>

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


/*! \namespace std
\brief Espacio de nombres para uso de la clase string
*/
using namespace std;
/*! \namespace cv
\brief Espacio de nombres para uso de la clases y funciones de vision artifical de openCV
*/
using namespace cv;
/*! \namespace items
\brief Espacio de nombres para uso de la clase Item.
*/
namespace items{
/*!
* \class Item.
* \brief Clase Item.
* \details Esta clase se usa para describir un ítem de una colección temática
*/
class SIBOW_EXPORT Item
{
public:
    //! Constructor.
    /*!
      Constructor vacío de la clase.
    */
    Item();
    //!  Constructor parametrizado de la clase.
    /*!
      \param name Instancia de la clase string con el nombre del ítem.
      \param pathImage Instancia de la clase string con la ruta de la imagen del ítem.
      \param pathDescription Instancia de la clase string con la ruta del archivo de texto de descripción del ítem.
      \param nWords Entero con el tamaño del histograma del ítem.
    */
    Item(string name,string pathImage,string pathDescription,int nWords); //! Destructor.
    //! Destructor.
    /*!
      Destructor de la clase.
    */
    ~Item();
    //! Método para liberar la memoria del vector de enteros que representa el histograma.
     void clearHistogram();
     //! Método para devolver el nombre del ítem.
     /*!
       \return Instancia de la clase string con el nombre del ítem.
     */
    string getName();
    //! Método para devolver la ruta de la imagen del ítem.
    /*!
      \return Instancia de la clase string con la ruta de la imagen del ítem.
    */
    string getPathImage();
    //! Método para devolver la ruta del archivo de texto con la descripción del ítem.
    /*!
      \return Instancia de la clase string con la ruta del archivo de texto con la descripción del ítem.
    */
    string getPathDescription();
    //! Método para devolver el tamaño del histograma de frecuencias.
    /*!
      \return Entero que representa el tamaño del historgrama.
    */
    int getNwords();
    //! Método para devolver la frecuencia dada una posición del histograma.
    /*!
      \param n Entero con la posición del histograma.
      \return Entero que representa la frecuencia.
    */
    int getNHistogram(int n);
    //! Método para introducir el nombre del ítem.
    /*!
      \param name Instacia del clase string con el nombre del ítem.
    */
    void setName(string name);
    //! Método para introducir la ruta de la imagen del ítem.
    /*!
      \param path Instacia del clase string con la ruta.
    */
    void setPathImage(string path);
    //! Método para introducir la ruta del archivo de texto con la descripción del ítem.
    /*!
      \param path Instacia del clase string con la ruta.
    */
    void setPathDescription(string path);
    //! Método para introducir el tamaño del histograma.
    /*!
      \param nWords Entero con el valor del tamaño del histograma.
    */
    void setNwords(int nWords);
    //! Método para añadir una frecuencia en el histograma.
    /*!
      \param value Entero con el valor de la frecuencia.
    */
    void addHistogram(int value);
    //! Método para copiar un histograma.
    /*!
      \param histogram Vector de enteros que representa un histograma de frecuencias.
    */
    void copyHistogram( vector<int> histogram);
    //! Método para cargar los datos de una ítem desde un fichero XML.
    /*!
      \pre Haber introducido el nombre del ítem.
      \param collectionName Instancia de la clase string con el nombre de la colección al que pertenece el ítem.
      \param pathCol Instancia de la clase string con la ruta raíz donde se encuentran las colecciones.
      \return Boleano confirmando que existe un error(true) o no (false) en la carga del fichero.
    */
    bool loadFile(string collectionName,string pathCol);
    //! Método para cargar los datos de una ítem desde un fichero XML.
    /*!
      \pre Haber introducido el nombre del ítem.
      \param collectionName Instancia de la clase string con el nombre de la colección al que pertenece el ítem.
      \param pathCol Instancia de la clase string con la ruta raíz donde se encuentran las colecciones.
      \return Boleano confirmando que existe un error(true) o no (false) en la escritura del fichero.
    */
    bool writeFile(string collectionName,string pathCol);


private:
    //! Variable privada con el nombre del ítem.
    string _name;
    //! Variable privada con la ruta donde se encuentra la imagen del ítem.
    string _pathImage;
    //! Variable privada con la ruta donde se encuentra el archivo de texto con la descripción del ítem.
    string _pathDescription;
     //! Variable privada con el tamaño del histograma de frecuencias.
    int _nWords;
    //! Variable privada con el histograma de frecuencias.
    vector<int> _histogram;



};
}
#endif // ITEM_H
