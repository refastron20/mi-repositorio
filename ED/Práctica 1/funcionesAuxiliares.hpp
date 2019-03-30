/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 1
	\author   Rafael Hormigo
	\date     23/02/2019
*/


#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

namespace ed
{
	/*!
		\brief   Muestra el menú del programa principal
		\return  Devuelve el número de opción elegido
	*/
	int menu();

	/*!
		\brief Realiza un test sobre los operadores principales de la clase monomio además de las operaciones de lectura y escritura
	*/
	void testMonomio();


	/*!
		\brief Realiza un test sobre los operadores externos de la clase monomio
	*/
	void operadoresExternosMonomios();

	/*!
		\brief Realiza un test sobre las funciones añadidas por el alumno
	*/
	void testExtra();
} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif
