/*!
	\file Monomio.hpp
	\brief Definición de la clase Monomio
*/

#ifndef _MONOMIO_HPP_
#define _MONOMIO_HPP_

// Para usar la funciones pow y std::abs
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>

#define COTA_ERROR 1.0e-6  //!< Cota de error para la comparación números reales

// Se incluye la clase Monomio dentro del espacio de nombre de la asigantura: ed
namespace ed
{
//!  Definición de la clase Monomio:  \f$ coeficiente \hspace{1ex} X^{grado} \f$
class Monomio
{
	//! \name Atributos privados de la clase Monomio
	private:

	//coeficiente del monomio
	double coeficiente_;
	//grado del monomio
	int grado_;


	//! \name Funciones o métodos públicos de la clase Monomio
	public:

	//! \name Constructores de la clase Monomio

	/*!
		\brief Constructor de la clase Monomio
		\attention función sobrecargada
		\note función inline
		\param coeficiente: coeficiente del monomio
		\param grado: grado del monomio
		\pre el grado debe ser mayor que 0
		\post el coeficiente final debe ser igual al parámetro "coeficiente" pasado
		\post el grado final debe ser igual al parámetro "grado" pasado
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\sa setCoeficiente(), setGrado()
	*/
	inline Monomio(double coeficiente=0.0, int grado=0){
		#ifndef NDEBUG
			assert(grado>=0);
		#endif
		this->setCoeficiente(coeficiente);
		this->setGrado(grado);
		#ifndef NDEBUG
			assert(std::abs(this->getCoeficiente()-coeficiente)< COTA_ERROR);
			assert(this->getCoeficiente()==coeficiente);
			assert(this->getGrado()==grado);
		#endif
	};

	/*!
		\brief Constructor de copia de la clase Monomio
		\attention función sobrecargada
		\note función inline
		\param m: monomio a copiar para crear el nuevo monomio
		\post El coeficiente del monomio creado es igual al coeficiente del monomio “m”.
		\post grado del monomio creado es igual al grado del monomio “m”.
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\sa setCoeficiente(), setGrado(), getCoeficiente(), getGrado()
	*/
	inline Monomio(Monomio &m){
				this->setCoeficiente(m.getCoeficiente());
				this->setGrado(m.getGrado());
		#ifndef NDEBUG
			assert(std::abs(this->getCoeficiente()-(m.getCoeficiente()))< COTA_ERROR);
			assert(this->getCoeficiente()==m.getCoeficiente());
			assert(this->getGrado()==m.getGrado());
		#endif
	};



	//! \name Observadores: funciones de consulta de la clase Monomio

	/*!
		\brief Observador del coeficiente del monomio
		\note función inline
		\return coeficiente del monomio
		\sa getGrado()
	*/
	inline double getCoeficiente() const {return coeficiente_;};

	/*!
		\brief Observador del grado del monomio
		\note función inline
		\return grado del monomio
		\sa getCoeficiente()
	*/
	inline int getGrado() const {return grado_;};



	//! \name Funciones de modificación de la clase Monomio

	/*!
		\brief Modificador del coeficiente del monomio
		\note función inline
		\param coeficiente: número real que representa el coeficiente del monomio
		\post El coeficiente del monomio es igual al número real “x”.
		\sa setGrado()
	*/
	inline void setCoeficiente(double coeficiente){coeficiente_=coeficiente;};

	/*!
		\brief Modificador del grado del monomio
		\note función inline
		\param grado: número entero que representa el grado del monomio
		\pre El número entero “n” es mayor o igual que 0.
		\post El grado del monomio es igual al número entero “n”.
		\sa setCoeficiente()
	*/
	inline void setGrado(int grado){grado_=grado;};



	/////////////////////////////////////////////////

	//! \name Operadores de la clase Monomio

	// Operadores de asignación

	/*!
		\brief operador de asignación de un monomio a otro
		\attention función sobrecargada
		\param m: monomio a asignar en el monomio actual
		\post El coeficiente del monomio creado es igual al coeficiente del monomio “m”
		\post grado del monomio creado es igual al grado del monomio “m”
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return el propio monomio
		\sa setCoeficiente(), setGrado(), getCoeficiente(), getGrado()
	*/
		Monomio & operator=(Monomio const &m);

	/*!
		\brief operador de asignación de un real a un monomio
		\attention función sobrecargada
		\param x: real a asignar en el monomio actual
		\post El coeficiente del monomio creado es igual al número real x
		\post grado del monomio creado es igual a 0
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return el propio monomio
		\sa setCoeficiente(), setGrado()
	*/
		Monomio & operator=(double const &x);


	// Operadores aritméticos y asignación

	/*!
		\brief operador de asignación y suma de un real a un monomio
		\param m: monomio con el cual se sumará el monomio actual
		\pre El monomio “m” tiene el mismo grado que el monomio actual
		\post El coeficiente del monomio actual se ha incrementado con el coeficiente del monomio “m”
		\post El grado del monomio actual no ha sido modificado
		\note se debe usar una cota de error para controlar la precisión de los números reales
		\return el propio monomio
		\sa setCoeficiente(), setGrado(), operator-=(), operator*=(), operator/=()
	*/
		Monomio & operator+=(Monomio const &m);
		/*!
			\brief operador de asignación y resta de un real a un monomio
			\param m: monomio con el cual se restará el monomio actual
			\pre El monomio “m” tiene el mismo grado que el monomio actual
			\post El coeficiente del monomio actual se ha decrementado con el coeficiente del monomio “m”
			\post El grado del monomio actual no ha sido modificado
			\note se debe usar una cota de error para controlar la precisión de los números reales
			\return el propio monomio
			\sa setCoeficiente(), setGrado(), operator+=(), operator*=(), operator/=()
		*/
		Monomio & operator-=(Monomio const &m);

		/*!
			\brief operador de asignación y multiplicación de un monomio a otro monomio
			\note función sobrecargada
			\param m: monomio con el cual se multiplicará el monomio actual
			\post El coeficiente del monomio actual se ha multiplicado por el coeficiente del monomio “m”
			\post El grado del monomio actual se ha incrementado con el grado del monomio “m”
			\note se debe usar una cota de error para controlar la precisión de los números reales
			\return el propio monomio
			\sa setCoeficiente(), setGrado(), operator-=(), operator+=(), operator/=()
		*/
		Monomio & operator*=(Monomio const &m);
		/*!
			\brief operador de asignación y multiplicación de un real a un monomio
			\note función sobrecargada
			\param x: real con el cual se multiplicará el monomio actual
			\post El coeficiente del monomio actual se ha multiplicado por el coeficiente del monomio “m”
			\post El grado del monomio actual no ha sido modificado
			\note se debe usar una cota de error para controlar la precisión de los números reales
			\return el propio monomio
			\sa setCoeficiente(), setGrado(), operator-=(), operator+=(), operator/=()
		*/
		Monomio & operator*=(double const &x);
		/*!
			\brief operador de asignación y división de un monomio a otro monomio
			\note función sobrecargada
			\param m: monomio con el cual se dividirá el monomio actual
			\pre El grado del monomio “m” es igual o inferior al grado del monomio actual
			\pre El coeficiente del monomios “m” no es 0.0
			\post El coeficiente del monomio actual se ha dividido por el coeficiente del monomio “m”
			\post El grado del monomio actual se ha decrementado con el grado del monomio “m”
			\note se debe usar una cota de error para controlar la precisión de los números reales
			\return el propio monomio
			\sa setCoeficiente(), setGrado(), operator-=(), operator+=(), operator*=()
		*/

		Monomio & operator/=(Monomio const &m);
		/*!
			\brief operador de asignación y división de un real a un monomio
			\note función sobrecargada
			\param x: real con el cual se dividirá el monomio actual
			\pre El número real “x” no es 0.0
			\post El coeficiente del monomio actual se ha dividido por el número real “x”.
			\post El grado del monomio actual no ha sido modificado
			\note se debe usar una cota de error para controlar la precisión de los números reales
			\return el propio monomio
			\sa setCoeficiente(), setGrado(), operator-=(), operator+=(), operator*=()
		*/
		Monomio & operator/=(double const &x);



	/////////////////////////////////////////////////////////////////////////////////////

	//! \name Funciones lectura y escritura de la clase Monomio

	/*!
		\brief función para leer el monomio por teclado
		\sa setGrado(), setCoeficiente(), escribirMonomio()
	*/
	void leerMonomio();

	/*!
		\brief función para escribir el monomio por pantalla
		\sa getGrado(), getCoeficiente(), leerMonomio()
	*/
	void escribirMonomio();


	///////////////////////////////////////////////////////////////////////

	//! \name Funciones auxiliares de la clase Monomio

	/*!
		\brief función para calcular el valor del monomio para un valor de x
		\param x: real que representa el valor de "x" del monomio
		\sa getGrado(), getCoeficiente(), setGrado(), setCoeficiente()
		\return el resultado del monomio para un valor de x
	*/
	double calcularValor(double const &x);

	/*!
		\brief función para derivar un monomio
		\sa getGrado(), getCoeficiente(), setGrado(), setCoeficiente(), derivar(), integrar()
	*/
	void integrar();

	/*!
		\brief función para integrar un monomio
		\sa getGrado(), getCoeficiente(), setGrado(), setCoeficiente(), derivar(), integrar()
	*/
	void derivar();
	/*!
		\brief función para calcular la potencia de un monomio
		\pre El número a elevar debe ser un entero
		\sa getGrado(), getCoeficiente(), setGrado(), setCoeficiente(), derivar(), integrar()
	*/

	void potencia(int const &x);

};  // Fin de la definición de la clase Monomio

}  //  Fin de namespace ed.

// _MONOMIO_HPP_
#endif
