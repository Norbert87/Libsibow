/*!
 \file item.h
 \author Norberto Madue�o Gal�n
 \date 2012-2013
 */
#ifndef ITEM_H
#define ITEM_H

#include <export.h>

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
* \details Esta clase se usa para describir un �tem de una colecci�n tem�tica
*/
class SIBOW_EXPORT Item
{
public:
    //! Constructor.
    /*!
      Constructor vac�o de la clase.
    */
    Item();
    //!  Constructor parametrizado de la clase.
    /*!
      \param name Instancia de la clase string con el nombre del �tem.
      \param pathImage Instancia de la clase string con la ruta de la imagen del �tem.
      \param pathDescription Instancia de la clase string con la ruta del archivo de texto de descripci�n del �tem.
      \param nWords Entero con el tama�o del histograma del �tem.
    */
    Item(string name,string pathImage,string pathDescription,int nWords); //! Destructor.
    //! Destructor.
    /*!
      Destructor de la clase.
    */
    ~Item();
    //! M�todo para liberar la memoria del vector de enteros que representa el histograma.
     void clearHistogram();
     //! M�todo para devolver el nombre del �tem.
     /*!
       \return Instancia de la clase string con el nombre del �tem.
     */
    string getName();
    //! M�todo para devolver la ruta de la imagen del �tem.
    /*!
      \return Instancia de la clase string con la ruta de la imagen del �tem.
    */
    string getPathImage();
    //! M�todo para devolver la ruta del archivo de texto con la descripci�n del �tem.
    /*!
      \return Instancia de la clase string con la ruta del archivo de texto con la descripci�n del �tem.
    */
    string getPathDescription();
    //! M�todo para devolver el tama�o del histograma de frecuencias.
    /*!
      \return Entero que representa el tama�o del historgrama.
    */
    int getNwords();
    //! M�todo para devolver la frecuencia dada una posici�n del histograma.
    /*!
      \param n Entero con la posici�n del histograma.
      \return Entero que representa la frecuencia.
    */
    int getNHistogram(int n);
    //! M�todo para introducir el nombre del �tem.
    /*!
      \param name Instacia del clase string con el nombre del �tem.
    */
    void setName(string name);
    //! M�todo para introducir la ruta de la imagen del �tem.
    /*!
      \param path Instacia del clase string con la ruta.
    */
    void setPathImage(string path);
    //! M�todo para introducir la ruta del archivo de texto con la descripci�n del �tem.
    /*!
      \param path Instacia del clase string con la ruta.
    */
    void setPathDescription(string path);
    //! M�todo para introducir el tama�o del histograma.
    /*!
      \param nWords Entero con el valor del tama�o del histograma.
    */
    void setNwords(int nWords);
    //! M�todo para a�adir una frecuencia en el histograma.
    /*!
      \param value Entero con el valor de la frecuencia.
    */
    void addHistogram(int value);
    //! M�todo para copiar un histograma.
    /*!
      \param histogram Vector de enteros que representa un histograma de frecuencias.
    */
    void copyHistogram( vector<int> histogram);
    //! M�todo para cargar los datos de una �tem desde un fichero XML.
    /*!
      \pre Haber introducido el nombre del �tem.
      \param collectionName Instancia de la clase string con el nombre de la colecci�n al que pertenece el �tem.
      \param pathCol Instancia de la clase string con la ruta ra�z donde se encuentran las colecciones.
      \return Boleano confirmando que existe un error(true) o no (false) en la carga del fichero.
    */
    bool loadFile(string collectionName,string pathCol);
    //! M�todo para cargar los datos de una �tem desde un fichero XML.
    /*!
      \pre Haber introducido el nombre del �tem.
      \param collectionName Instancia de la clase string con el nombre de la colecci�n al que pertenece el �tem.
      \param pathCol Instancia de la clase string con la ruta ra�z donde se encuentran las colecciones.
      \return Boleano confirmando que existe un error(true) o no (false) en la escritura del fichero.
    */
    bool writeFile(string collectionName,string pathCol);


private:
    //! Variable privada con el nombre del �tem.
    string _name;
    //! Variable privada con la ruta donde se encuentra la imagen del �tem.
    string _pathImage;
    //! Variable privada con la ruta donde se encuentra el archivo de texto con la descripci�n del �tem.
    string _pathDescription;
     //! Variable privada con el tama�o del histograma de frecuencias.
    int _nWords;
    //! Variable privada con el histograma de frecuencias.
    vector<int> _histogram;



};
}
#endif // ITEM_H
