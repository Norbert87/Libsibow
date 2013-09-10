/*!
 \file matches.h
 \author Norberto Madue�o Gal�n
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
      Constructor vac�o de la clase.
    */
    Match();
    //!  Constructor parametrizado de la clase.
    /*!
      \param name Instancia de la clase string con el nombre del �tem.
      \param total Real con el grado de similitud.
    */
    Match(string name,double total);
    //! M�todo para introducir el nombre �tem.
    /*!
      \param name Instacia del clase string con el nombre del �tem.
    */
    void setName(string name);
    //! M�todo para introducir el grado de similitud del objeto de la escena.
    /*!
      \param total Real con el grado de similitud.
    */
    void setTotal(double total);
    //! M�todo para devolver el nombre del �tem.
    /*!
      \return Instancia de la clase string con el nombre del �tem.
    */
    string getName();
    //! M�todo para devolver el grado de similitud con el objeto de la escena.
    /*!
      \return Real con el valor del grado de similitud.
    */
    double getTotal();
    //! Sobrecarga del operador = para asignar los atributos de un elemento de la clase Match.
    /*!
      \param I Instancia de la clase Match del cu�l se copiar�n sus atributos.
      \return Referencia a un elemento de la clase Match.
    */
    Match & operator=(const Match & I);

private:
    //! Variable privada con el nombre del �tem.
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
      Constructor vac�o de la clase.
    */
    Vectormatches();
    //!  Constructor parametrizado de la clase.
    /*!
      \param n Entero con el tama�o del vector de instancias de la clase Match.
    */
    Vectormatches(int n);
    //! Destructor.
    /*!
      Destructor de la clase.
    */
    ~Vectormatches();
    //! Sobrecarga del operador [] para devolver un elemento de la clase Match dentro del vector.
    /*!
      \param i Posici�n del vector.
      \return Referencia a un elemento de la clase Match.
    */
    Match & operator[](int i);
    //! M�todo para introducir los atributos de un elemento del vector.
    /*!
      \param name Instancia de la clase string con el nombre del �tem.
      \param pos Entero con la posici�n del vector.
      \param value Real con el grado de similitud.
    */
    void setElement(int pos,double value,string name);
    //! M�todo para devolver el tama�o del vector.
    /*!
      \return Entero con el tama�o del vector.
    */
    int getTotal();
    //! M�todo para Ordenar de manera ascendente seg�n el grado de similitud con el objeto de la escena los elementos del vector.
    void orderAscending();
    //! M�todo para Ordenar de manera descendente seg�n el grado de similitud con el objeto de la escena los elementos del vector.
    void orderDescending();

private:
    //! Variable privada que apunta al primer elemento del vector.
    Match *_data;
    //! Variable privada con el tama�o del vector.
    int _nTotal;
};
}
#endif // MATCHES_H
