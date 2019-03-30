/*!
	\file operadoresExternosPolinomios.hpp
	\brief Ficheros con operadores de monomios y polinomios
*/

#ifndef _OperadoresPolinomios_HPP_
#define _OperadoresPolinomios_HPP_

// Facilita la entrada y salida
#include <iostream>

#include "Polinomio.hpp"

using std::istream;
using std::ostream;

// Espacio de nombre de la asigantura: ed
namespace ed
{

////////////////////////////////////////////////////////////////////////////
	// Funciones y operadores que no pertenecen a la clase Polinomio


	////////////////////////////////////////////////////////////
	//! \name Operadores de igualdad

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	bool operator==(ed::Polinomio const & p1, ed::Polinomio const & p2);

	inline bool operator==(ed::Polinomio const & p1, ed::Monomio const & m){
		Polinomio aux;
		aux=m;
		return p1==aux;
	}

	inline bool operator==(ed::Monomio const & m, ed::Polinomio const & p1){
		return p1==m;
	}

	inline bool operator==(ed::Polinomio const & p1, double const & x){
		Monomio m(x);
		Polinomio aux;
		aux=m;
		return p1==aux;
	}

	inline bool operator==(double const & x, ed::Polinomio const & p1){
		return p1==x;
	}


	////////////////////////////////////////////////////////////////////////////////////
	//! \name Operadores de desigualdad

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	inline bool operator!=(ed::Polinomio const & p1, ed::Polinomio const & p2){
		return !(p1==p2);
	}

	inline bool operator!=(ed::Polinomio const & p1, ed::Monomio const & m){
		return !(p1==m);
	}

	inline bool operator!=(ed::Monomio const & m, ed::Polinomio const & p1){
		return !(p1==m);
	}

	inline bool operator!=(ed::Polinomio const & p1, double const & x){
		return !(p1==x);
	}

	inline bool operator!=(double const &x, ed:: Polinomio const &p1){
		return !(p1==x);
	}


//////////////////////////////////////////////////////////////////////////////////////

	//! \name Operadores unarios

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	inline	ed::Polinomio & operator+(ed::Polinomio & p){
		Polinomio *nuevo = new ed::Polinomio(p);
		return *nuevo;
	}

	inline	ed::Polinomio & operator-(ed::Polinomio const & p){
		Polinomio aux;
		for (int i = 0; i <= p.getGrado(); i++) {
			if (p.existeMonomio(i)) {
				aux.insertarMonomio(-(p.getMonomio(i)));
			}
		}
		Polinomio *nuevo = new ed::Polinomio(aux);
		return *nuevo;
	}


//////////////////////////////////////////////////////////////////////////////////////

	//! \name Operadores binarios de la suma

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
		inline ed::Polinomio & operator+(ed::Polinomio const &p1,  ed::Polinomio const &p2){
			Polinomio aux(p1);
			aux+=p2;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator+(ed::Polinomio const &p, ed::Monomio const &m){
			Polinomio aux;
			aux=m;
			aux+=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator+(ed::Monomio const &m, ed::Polinomio const &p){
			Polinomio aux;
			aux=m;
			aux+=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator+(ed::Polinomio const &p, double const &x){
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux+=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator+(double const &x, ed::Polinomio const &p){
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux+=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator-(ed::Polinomio const &p1,  ed::Polinomio const &p2){
			Polinomio aux(p1);
			aux-=p2;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator-(ed::Polinomio const &p, ed::Monomio const &m){
			Polinomio aux;
			aux=m;
			aux-=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator-(ed::Monomio const &m, ed::Polinomio const &p){
			Polinomio aux;
			aux=m;
			aux-=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator-(ed::Polinomio const &p, double const &x){
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux-=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator-(double const &x, ed::Polinomio const &p){
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux-=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator*(ed::Polinomio const &p1,  ed::Polinomio const &p2){
			Polinomio aux(p1);
			aux*=p2;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator*(ed::Polinomio const &p, ed::Monomio const &m){
			Polinomio aux;
			aux=m;
			aux*=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator*(ed::Monomio const &m, ed::Polinomio const &p){
			Polinomio aux;
			aux=m;
			aux*=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator*(ed::Polinomio const &p, double const &x){
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux*=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator*(double const &x, ed::Polinomio const &p){
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux*=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator/(ed::Polinomio const &p1,  ed::Polinomio const &p2){
			#ifndef NDEBUG
				assert(!p2.esNulo() and (p2.getGrado()<=p1.getGrado()));
			#endif
			Polinomio aux(p1);
			aux/=p2;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator/(ed::Polinomio const &p, ed::Monomio const &m){
			#ifndef NDEBUG
				assert((m!=0.0) and (m.getGrado()<=p.getGrado()));
			#endif
			Polinomio aux(p);
			aux/=m;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator/(ed::Monomio const &m, ed::Polinomio const &p){
			#ifndef NDEBUG
				assert(!(p.esNulo()) and (m.getGrado()>=p.getGrado()));
			#endif
			Polinomio aux;
			aux=m;
			aux/=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator/(ed::Polinomio const &p, double const &x){
			#ifndef NDEBUG
				assert((x!=0.0));
			#endif
			Polinomio aux(p);
			aux/=x;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		inline ed::Polinomio & operator/(double const &x, ed::Polinomio const &p){
			#ifndef NDEBUG
				assert(!(p.esNulo()) and (p.getGrado()==0));
			#endif
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux/=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

	/////////////////////////////////////////////////////////////////////////////

   //! \name Sobrecarga de los operadores de flujo de la clase Polinomio.

    // COMPLETAR LOS COMENTARIOS DE DOXYGEN
    ostream &operator<<(ostream &stream, ed::Polinomio const &p);

    // COMPLETAR LOS COMENTARIOS DE DOXYGEN
    istream &operator>>(istream &stream, ed::Polinomio &p);

}  // Fin de namespace ed.

#endif // _OperadoresPolinomios_HPP_
