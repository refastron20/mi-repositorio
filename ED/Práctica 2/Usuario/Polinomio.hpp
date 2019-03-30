/*!
   \file Polinomio.hpp
   \brief Definición de la clase Polinomio
*/

#ifndef _POLINOMIO_HPP_
#define _POLINOMIO_HPP_

// Control de asertos
#include <cassert>

// Lista de STL
#include <list>

// Para usar la función abs
#include <cmath>

#include "PolinomioInterfaz.hpp"
#include "Monomio.hpp"
#include "operadoresExternosMonomios.hpp"


using namespace std;

// Se incluye la clase Polinomio dentro del espacio de nombre de la asigantura: ed
namespace ed {

//!  Definición de la clase Polinomio que hereda de PolinomioInterfaz
class Polinomio: public ed::PolinomioInterfaz
{

  //! \name Atributos y operaciones privados de la clase Polinomio
   private:

     list <Monomio> Polinomio_;

     //! \name Observadores: función de consulta de la clase Polinomio

    inline list <Monomio> getPolinomio() const {return Polinomio_;}

    /*! \name Función de modificación de la clase Polinomio
        \note función sobrecargada
    */
    inline void setPolinomio(list <Monomio> polinomio){Polinomio_=polinomio;};
    /*! \name Función de modificación de la clase Polinomio
        \note función sobrecargada
    */
    inline void setPolinomio(Polinomio const &p){Polinomio_=p.getPolinomio();};
   //! \name Funciones o métodos públicos de la clase Polinomio
   public:

	//! \name Constructores de la clase Polinomio

  /*!
    \brief Constructor de la clase Polinomio
    \attention función sobrecargada
    \note función inline
    \post el polinomio es nulo
    \note se debe usar una cota de error para controlar la precisión de los números reales
  */
  inline Polinomio(){
    Monomio m;
    Polinomio_.push_back(m);
    #ifndef NDEBUG
      assert(this->esNulo());
      assert(abs((this->getPolinomio().front()).getCoeficiente()-0.0)<COTA_ERROR);
    #endif
  };

  /*!
    \brief Constructor de copia de la clase Polinomio
    \attention función sobrecargada
    \note función inline
    \param p: polinomio a copiar
    \post el polinomio es igual al polinomio pasado
  */
  inline Polinomio(Polinomio const &p){
    this->setPolinomio(p.getPolinomio());

  };

  //! \name observadores públicos de la clase monomio

  /*!
    \brief Observador de la clase polinomio que indica si es nulo
    \note función inline
  */
  inline bool esNulo() const {
    if(this->getGrado()==0){
      if (this->existeMonomio(0)) {
        if(this->getMonomio(0).getCoeficiente()==0)
          return true;
      }
    }
    return false;
  };

  /*!
    \brief Observador de la clase polinomio que devuelve el grado
    \note función inline
    \pre los monomios dentro del polinomio deben estar ordenados
  */
  inline int getGrado() const {
    return this->getPolinomio().front().getGrado();
  };

  /*!
    \brief Observador de la clase polinomio que devuelve el grado
    \note función inline
  */
  inline int getNumeroMonomios() const {
    if (this->getPolinomio().back().getCoeficiente()==0.0&&(this->getPolinomio().back()).getGrado()==0){
      #ifndef NDEBUG
        std::abs((this->getPolinomio().back()).getCoeficiente()-0.0)<COTA_ERROR||((this->getPolinomio().back()).getGrado()==0);
      #endif
      return this->getPolinomio().size()-1;
    }else
      return this->getPolinomio().size();
  }

  /*!
    \brief Observador de la clase polinomio que devuelve si existe el monomio del grado indicado
    \note función inline
    \param n: entero que indica el grado del monomio a buscar
    \pre el polinomio debe existir
  */
  inline bool existeMonomio(int const &n) const {
    list <Monomio> aux=this->getPolinomio();
    list <Monomio> :: iterator i=aux.begin();
    while (i!=aux.end()) {
      if((*i).getGrado()==n)
        return true;
      i++;
    }
    return false;
  }

  /*!
    \brief Observador de la clase polinomio que devuelve, si existe, el monomio del grado indicado
    \note función inline
    \param n: entero que indica el grado del monomio a buscar
    \pre el polinomio debe existir
  */
  inline Monomio getMonomio(int const &n) const {
    Monomio m;
    list <Monomio> aux=this->getPolinomio();
    list <Monomio> :: iterator i=aux.begin();
    while (i!=aux.end()) {
      if((*i).getGrado()==n)
        return (m=(*i));
      i++;
    }
    return m;
  }
 	////////////////////////////////////////////////////////////////

   //! \name Operadores de la clase Polinomio

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	Polinomio & operator=(Polinomio const &p);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	Polinomio & operator=(Monomio const &m);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	Polinomio & operator=(double const &x);

  // Operadores aritméticos y asignación

		// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	Polinomio & operator+=(Polinomio const &p);

  Polinomio & operator+=(ed::Monomio const &m){
  	Polinomio p;
  	p=m;
  	*this+=p;
  	return *this;
  }

  Polinomio & operator+=(double const &x){
  	Monomio m(x);
  	Polinomio p;
  	p=m;
  	*this+=p;
  	return *this;
  }

  Polinomio & operator-=(Polinomio const &p);

  Polinomio & operator-=(ed::Monomio const &m){
  	Polinomio p;
  	p=m;
  	*this-=p;
  	return *this;
  }

  Polinomio & operator-=(double const &x){
  	Monomio m(x);
  	Polinomio p;
  	p=m;
  	*this-=p;
  	return *this;
  }

  Polinomio & operator*=(Polinomio const &p);

  Polinomio & operator*=(Monomio const &m);

  Polinomio & operator*=(double const &x);

  Polinomio & operator/=(Polinomio const &p);

  Polinomio & operator/=(Monomio const &m);

  Polinomio & operator/=(double const &x);


  /////////////////////////////////////////////////////////////////////////////////////

	//! \name Funciones lectura y escritura de la clase Polinomio

	void leerPolinomio();

  void escribirPolinomio();


	///////////////////////////////////////////////////////////////////////

	//! \name Funciones auxiliares de la clase Polinomio

  void insertarMonomio(Monomio const &m);

  double calcularValor(double const &x){
    Monomio aux;
    double a=0;
    for (int i = 0; i <= this->getGrado(); i++) {
      if (this->existeMonomio(i)) {
        aux=this->getMonomio(i);
        a+=aux.calcularValor(x);
      }
    }
    return a;
  }
}; // Fin de la definición de la clase Polinomio




} // \brief Fin de namespace ed.

//  _POLINOMIO_HPP_
#endif
