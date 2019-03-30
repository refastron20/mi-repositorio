/*!
  \file   funcionesExtra.hpp
  \brief  Funciones extra para el programa principal de la práctica 1
	\author   Rafael Hormigo
	\date     23/02/2019
*/
#ifndef FUNCIONESEXTRA_H
#define FUNCIONESEXTRA_H

#include "Monomio.hpp"

namespace ed{
  /*!
    \brief función que concatena monomios para mostrar un polinomio
    \param m1: monomio 1
    \param m2: monomio 2
    \param m3: monomio 3
    \sa calcularPolinomio2()
  */
  void concatenar(ed::Monomio &m1,ed::Monomio &m2,ed::Monomio &m3);

  /*!
    \brief función que calcula un polinomio de segundo grado y lo muestra por pantalla
    \note función sobrecargada
    \param m1: monomio 1 "a"
    \param m2: monomio 2 "b"
    \param x: real "c"
    \pre se tienen que pasar obligatoriamente un monomio de segundo grado y otro de primer grado
    \sa concatenar()
  */
  void calcularPolinomio2(ed::Monomio const &m1, ed::Monomio const &m2, double const &x);

  /*!
    \brief función que calcula un polinomio de segundo o prmer grado con solo una variable
    \note función sobrecargada
    \param m1: monomio 1 "a"
    \param m2: monomio 2 "b"
    \param x: real "c"
    \pre el monomio no pueder tener grado mayor que dos
    \sa concatenar()
  */
  void calcularPolinomio2(ed::Monomio const &m1, double const &x);
}
#endif
