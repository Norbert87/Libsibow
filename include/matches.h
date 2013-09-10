/*!
 \file matches.h
 \author Norberto Madueño Galán
 \date 2012-2013
 */
#ifndef MATCHES_H
#define MATCHES_H

#include <string>
#include <cstdlib>

#include <export.h>

/*! \namespace std
\brief Espacio de nombres para uso de la clase string
*/
using namespace std;

/*! \namespace matches
\brief Espacio de nombres para uso de la clase Match y vectorMatches
*/
namespace matches
{


/*!
* \class Match.
* \brief Clase Match.
* \details Esta clase se usa para describir la coincidencia con un objeto de la escena.
*/
class SIBOW_EXPORT Match
{
public:
    //! Constructor.
    /*!
      Constructor vacío de la clase.
    */
    Match();
    //!  Constructor parametrizado de la clase.
    /*!
      \param name Instancia de la clase string con el nombre del ítem.
      \param total Real con el grado de similitud.
    */
    Match(string name,double total);
    //! Método para introducir el nombre ítem.
    /*!
      \param name Instacia del clase string con el nombre del ítem.
    */
    void setName(string name);
    //! Método para introducir el grado de similitud del objeto de la escena.
    /*!
      \param total Real con el grado de similitud.
    */
    void setTotal(double total);
    //! Método para devolver el nombre del ítem.
    /*!
      \return Instancia de la clase string con el nombre del ítem.
    */
    string getName();
    //! Método para devolver el grado de similitud con el objeto de la escena.
    /*!
      \return Real con el valor del grado de similitud.
    */
    double getTotal();
    //! Sobrecarga del operador = para asignar los atributos de un elemento de la clase Match.
    /*!
      \param I Instancia de la clase Match del cuál se copiarán sus atributos.
      \return Referencia a un elemento de la clase Match.
    */
    Match & operator=(const Match & I);

private:
    //! Variable privada con el nombre del ítem.
    string _name;
    //! Variable privada que representa grado de similitud con el objeto de la escena.
    double _total;
};
/*!
* \class vectorMatches.
* \brief Clase vectorMatches.
* \details Esta clase se usa para describir  un vector de coincidencias con el objeto de la escena.
*/
class SIBOW_EXPORT Vectormatches
{
public:
    //! Constructor.
    /*!
      Constructor vacío de la clase.
    */
    Vectormatches();
    //!  Constructor parametrizado de la clase.
    /*!
      \param n Entero con el tamaño del vector de instancias de la clase Match.
    */
    Vectormatches(int n);
    //! Destructor.
    /*!
      Destructor de la clase.
    */
    ~Vectormatches();
    //! Sobrecarga del operador [] para devolver un elemento de la clase Match dentro del vector.
    /*!
      \param i Posición del vector.
      \return Referencia a un elemento de la clase Match.
    */
    Match & operator[](int i);
    //! Método para introducir los atributos de un elemento del vector.
    /*!
      \param name Instancia de la clase string con el nombre del ítem.
      \param pos Entero con la posición del vector.
      \param value Real con el grado de similitud.
    */
    void setElement(int pos,double value,string name);
    //! Método para devolver el tamaño del vector.
    /*!
      \return Entero con el tamaño del vector.
    */
    int getTotal();
    //! Método para Ordenar de manera ascendente según el grado de similitud con el objeto de la escena los elementos del vector.
    void orderAscending();
    //! Método para Ordenar de manera descendente según el grado de similitud con el objeto de la escena los elementos del vector.
    void orderDescending();

private:
    //! Variable privada que apunta al primer elemento del vector.
    Match *_data;
    //! Variable privada con el tamaño del vector.
    int _nTotal;
};
}
#endif // MATCHES_H
