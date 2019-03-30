/*!
	\file operadoresExternosMonomios.hpp
	\brief Ficheros con los prototipos de los operadores externos de la clase Monomio
*/

#ifndef _OperadoresExternosMonomios_HPP_
#define _OperadoresExternosMonomios_HPP_

// Facilita la entrada y salida
#include <iostream>

#include "Monomio.hpp"

// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

// Espacio de nombre de la asigantura: ed
namespace ed
{
//////////////////////////////////////////////////////////////////////////////////////
	// Operadores externos que no pertenecen a la clase Monomio

	//! \name Operadores de igualdad

	/*!
		\brief operador de Igualdad
		\note Función sobreacargada
		\param m1: monomio a comparar
		\param m2: monomio a comparar
		\post El valor devuelto es:
			✔ verdadero si los dos monomios tienen el mismo grado y el mismo coeficiente;
			✔ falso, en caso contrario.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return boolean
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator!=()
	*/
	bool operator==(ed::Monomio const & m1, ed::Monomio const & m2);

	/*!
		\brief operador de igualdad
		\note función sobrecargada
		\param m1: monomio a comparar con el real
		\param x: real a comparar con el monomio
		\post El valor devuelto es:
			✔ verdadero si el monomio tiene grado 0 y su coeficiente es igual al número “x”;
			✔ falso, en caso contrario.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return boolean
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator!=()
	*/
	bool operator==(ed::Monomio const & m1, double const & x);

	/*!
		\brief operador de igualdad
		\note función sobrecargada
		\param x: real a comparar con el monomio
		\param m2: monomio a comparar con el real
		\post El valor devuelto es:
			✔ verdadero si el monomio tiene grado 0 y su coeficiente es igual al número “x”;
			✔ falso, en caso contrario.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return boolean
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator!=()
	*/
	bool operator==(double const & x, ed::Monomio const & m2);

	//! \name Operadores de desigualdad

	/*!
		\brief operador de desigualdad
		\note Función sobreacargada
		\param m1: monomio a comparar
		\param m2: monomio a comparar
		\post El valor devuelto es
			✔ verdadero si los dos monomios no tienen el mismo grado o no tienen el mismo coeficiente;
			✔ falso, en caso contrario.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return boolean
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator==()
	*/
	bool operator!=(ed::Monomio const & m1, ed::Monomio const & m2);

	/*!
		\brief operador de desigualdad
		\note Función sobreacargada
		\param m1: monomio a comparar con el real
		\param x: real a comparar con el monomio
		\post El valor devuelto es
			✔ verdadero si el monomio no tiene grado 0 o si su coeficiente no es igual al número “x”;
			✔ falso, en caso contrario.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return boolean
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator==()
	*/
	bool operator!=(ed::Monomio const & m1, double const & x);
	/*!
		\brief operador de desigualdad
		\note Función sobreacargada
		\param x: real a comparar con el monomio
		\param m2: monomio a comparar con el real
		\post El valor devuelto es
			✔ verdadero si el monomio no tiene grado 0 o si su coeficiente no es igual al número “x”;
			✔ falso, en caso contrario.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return boolean
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator==()
	*/
	bool operator!=(double const & x, ed::Monomio const & m2);

	///////////////////////////////////////////////////

	//! \name Operadores unarios prefijos

	/*!
		\brief operador de signo positivo
		\note función sobrecargada
		\param m: monomio al que se le aplicará el signo
		\post El monomio devuelto es igual al monomio “m”, es decir, tiene el mismo grado y el mismo coeficiente.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return monomio
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator-()
	*/

	ed::Monomio & operator+(ed::Monomio const & m);

	/*!
		\brief operador de signo negativo
		\note función sobrecargada
		\param m: monomio al que se le aplicará el signo
		\post El monomio devuelto tiene el mismo grado que el monomio “m” pero su coeficiente es el opuesto.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return monomio
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator-()
	*/
	ed::Monomio & operator-(ed::Monomio const & m);

	//////////////////////////////////////////////////////////

	//! \name Operador binario de la suma

	/*!
		\brief operador de suma
		\note función sobrecargada
		\param m1: primer monomio a sumar
		\param m2: segundo monomio a sumar
		\pre Los monomios m1 y m2 tienen el mismo grado.
		\post El monomio devuelto tiene:
			✔ el mismo grado que los monomios m1 y m2,
			✔ y su coeficiente es la suma de los coeficientes de los monomios.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return monomio
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator-()
	*/
	 ed::Monomio & operator+ (ed::Monomio const &m1, ed::Monomio const &m2);


	//////////////////////////////////////////////////////////
	//! \name Operador binario de la resta
	/*!
		\brief operador de resta
		\note función sobrecargada
		\param m1: primer monomio a restar
		\param m2: segundo monomio a restar
		\pre Los monomios m1 y m2 tienen el mismo grado.
		\post El monomio devuelto tiene:
			✔ el mismo grado que los monomios m1 y m2,
			✔ y su coeficiente es la resta de los coeficientes de los monomios.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return monomio
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator-()
	*/
	ed::Monomio & operator- (ed::Monomio const &m1, ed::Monomio const &m2);


	///////////////////////////////////////////////////////////////////////////
	//! \name Operadores binarios de la multiplicación
	/*!
		\brief operador de multiplicación
		\note función sobrecargada
		\param m1: primer monomio a multiplicar
		\param m2: segundo monomio a multiplicar
		\post El monomio devuelto tiene un grado que es la suma de los grados de los monomios m1 y m2,
		\post y su coeficiente es el producto de los coeficientes de los monomios m1 y m2.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return monomio
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator-(), operator/()
	*/
	ed::Monomio & operator* (ed::Monomio const &m1, ed::Monomio const &m2);

	/*!
		\brief operador de multiplicación
		\note función sobrecargada
		\param x: real a multiplicar por el monomio
		\param m: monomio a multiplicar por el real
 		\post El monomio devuelto tiene el mismo grado que el monomio “m”,
		\post y su coeficiente es el producto del coeficiente del monomio “m” por el número “x”.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return monomio
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator-(), operator/()
	*/
	ed::Monomio & operator* (double const &x, ed::Monomio const &m);

	/*!
		\brief operador de multiplicación
		\note función sobrecargada
		\param m: monomio a multiplicar por el real
		\param x: real a multiplicar por el monomio
		\post El monomio devuelto tiene el mismo grado que el monomio “m”,
		\post y su coeficiente es el producto del coeficiente del monomio “m” por el número “x”.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return monomio
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator-(), operator/()
	*/

	ed::Monomio & operator* (ed::Monomio const &m, double const &x);

	///////////////////////////////////////////////////////////////////////////

	//! \name Operadores binarios de la división

	/*!
		\brief operador de división
		\note función sobrecargada
		\param m1: monomio divisor
		\param m2: monomio dividendo
		\pre El grado del monomio m2 es menor o igual que el grado del monomio m1.
 		\pre El coeficiente del monomio m2 no es 0.0.
		\post El monomio devuelto tiene un grado que es la suma de los grados de los monomios m1 y m2,
		\post y su coeficiente es el producto de los coeficientes de los monomios m1 y m2.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return monomio
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator-(), operator*()
	*/

	ed::Monomio & operator/ (ed::Monomio const &m1, ed::Monomio const &m2);

	/*!
		\brief operador de división
		\note función sobrecargada
		\param x: real dividendo
		\param m: monomio divisor
		\pre El grado del monomio es 0 y su coeficiente es distinto de 0.0.
 		\post El monomio devuelto tiene grado igual a 0
		\post y su coeficiente es la división del número “x” por el coeficiente del monomio “m”..
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return monomio
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator-(), operator/()
	*/
	ed::Monomio & operator/ (double const &x, ed::Monomio const &m);

	/*!
		\brief operador de división
		\note función sobrecargada
		\param m: monomio dividendo
		\param x: real divisor
		\pre El número “x” no es 0.0.
		\post El monomio devuelto tiene el mismo grado que el monomio “m”,
 		\post y su coeficiente es la división del coeficiente del monomio “m” por el número “x”.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return monomio
		\sa operator-=(), operator*=(), operator/=(), operator=(), operator+=(), operator-(), operator/()
	*/
	ed::Monomio & operator/ (ed::Monomio const &m, double const &x);


	/////////////////////////////////////////////////////////////////////////////

	//! \name Sobrecarga de los operadores de entrada y salida

	/*!
		\brief sobrecarga de operador de flujo de entrada
		\note función sobrecargada
		\param istream: flujo de entrada
		\param m: monomio sobre el que operar
		\return istream
		\sa operator<<()
	*/
		istream &operator>>(istream &stream, ed::Monomio &m);

		/*!
			\brief sobrecarga de operador de flujo de salida
			\note función sobrecargada
			\param istream: flujo de salida
			\param m: monomio sobre el que operar
			\return ostream
			\sa operator>>()
		*/
	 	ostream &operator<<(ostream &stream, ed::Monomio const &m);

}  // Fin de namespace ed.

#endif // _OperadoresExternosMonomios_HPP_
