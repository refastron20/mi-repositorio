/*!
   \file  operadoresExternosMonomios.cpp
	\brief Ficheros con el código de los operadores externos de la clase Monomio
*/


//  Ficheros de cabecera
#include <iostream>

#include "operadoresExternosMonomios.hpp"


//  Se incluyen los operadores sobrecargados dentro del espacio de nombres ed
namespace ed
{
	// Operadores de igualdad

	bool operator==(ed::Monomio const & m1, ed::Monomio const & m2)
	{
		if((m1.getCoeficiente()==m2.getCoeficiente())&&(m1.getGrado()==m2.getGrado())){
			#ifndef NDEBUG
				assert(m1.getCoeficiente()==m2.getCoeficiente());
				assert(m1.getGrado()==m2.getGrado());
				assert(std::abs(m1.getCoeficiente()-m2.getCoeficiente())<COTA_ERROR);
			#endif
			return true;
		}else{
			#ifndef NDEBUG
				assert((m1.getCoeficiente()!=m2.getCoeficiente()||(m1.getGrado()!=m2.getGrado())));
			#endif
			return false;
		}
	}

	bool operator==(ed::Monomio const & m1, double const &x)
	{
		if ((m1.getCoeficiente()==x)&&(m1.getGrado()==0)) {
			#ifndef NDEBUG
				assert(m1.getCoeficiente()==x);
				assert(m1.getGrado()==0);
				assert(std::abs(m1.getCoeficiente()-x)<COTA_ERROR);
			#endif
			return true;
		}else{
			#ifndef NDEBUG
				assert((m1.getCoeficiente()!=x)||(m1.getGrado()!=0));
			#endif
			return false;
		}
	}

	bool operator==(double const &x, ed::Monomio const & m1)
	{
		return (m1==x);
	}

	// Operadores de desigualdad

	// COMPLETAR
	bool operator!=(ed::Monomio const & m1, ed::Monomio const & m2)
	{
		if ((m1.getCoeficiente()==m2.getCoeficiente())&&(m1.getGrado()==m2.getGrado())) {
			#ifndef NDEBUG
				assert(m1.getCoeficiente()==m2.getCoeficiente());
				assert(m1.getGrado()==m2.getGrado());
				assert(std::abs(m1.getCoeficiente()-m2.getCoeficiente())<COTA_ERROR);
			#endif
			return false;
		}else{
			#ifndef NDEBUG
				assert((m1.getCoeficiente()!=m2.getCoeficiente()||(m1.getGrado()!=m2.getGrado())));
			#endif
			return true;
		}
	}

	bool operator!=(ed::Monomio const & m1, double const &x)
	{
		if ((m1.getCoeficiente()==x)&&(m1.getGrado()==0)) {
			#ifndef NDEBUG
				assert(m1.getCoeficiente()==x);
				assert(m1.getGrado()==0);
				assert(std::abs(m1.getCoeficiente()-x)<COTA_ERROR);
			#endif
			return false;
		}else{
			#ifndef NDEBUG
				assert((m1.getCoeficiente()!=x)||(m1.getGrado()!=0));
			#endif
			return true;
		}
	}

	bool operator!=(double const &x, ed::Monomio const & m1)
	{
		return (m1!=x);
	}

	////////////////////////////////////////////////////////////

	// Operadores unarios prefijos

	// COMPLETAR
	ed::Monomio & operator+(ed::Monomio const & m)
	{
		ed::Monomio *nuevo = new ed::Monomio();
		*nuevo=m;
		#ifndef NDEBUG
			assert(std::abs(m.getCoeficiente()-nuevo->getCoeficiente())<COTA_ERROR);
			assert((m.getCoeficiente()==nuevo->getCoeficiente())&&(m.getGrado()==nuevo->getGrado()));
		#endif
		return *nuevo;
	}

	ed::Monomio & operator-(ed::Monomio const & m){
			ed::Monomio *nuevo = new ed::Monomio();
			nuevo->setGrado(m.getGrado());
			nuevo->setCoeficiente(-(m.getCoeficiente()));
			#ifndef NDEBUG
				assert(std::abs(m.getCoeficiente()+nuevo->getCoeficiente())<COTA_ERROR);
				assert((m.getCoeficiente()==-(nuevo->getCoeficiente()))&&(m.getGrado()==nuevo->getGrado()));
			#endif
			return *nuevo;
		}

	////////////////////////////////////////////////////////////
	// Operadores aritméticos binarios

	// Suma
	ed::Monomio & operator+ (ed::Monomio const &m1, ed::Monomio const &m2)
	{
		#ifndef NDEBUG
			assert(m1.getGrado()==m2.getGrado());
		#endif
		ed::Monomio *nuevo = new ed::Monomio();
		nuevo->setCoeficiente(m1.getCoeficiente()+m2.getCoeficiente());
		nuevo->setGrado(m1.getGrado());
		#ifndef NDEBUG
			assert(std::abs(nuevo->getCoeficiente()-(m1.getCoeficiente()+m2.getCoeficiente()))<COTA_ERROR);
			assert(nuevo->getCoeficiente()==(m1.getCoeficiente()+m2.getCoeficiente()));
			assert((nuevo->getGrado()==m1.getGrado())&&(nuevo->getGrado()==m2.getGrado()));
		#endif
		return *nuevo;
	}


	////////////
	// Resta

	ed::Monomio & operator- (ed::Monomio const &m1, ed::Monomio const &m2)
	{
		#ifndef NDEBUG
			assert(m1.getGrado()==m2.getGrado());
		#endif
		ed::Monomio *nuevo = new ed::Monomio();
		nuevo->setCoeficiente(m1.getCoeficiente()-m2.getCoeficiente());
		nuevo->setGrado(m1.getGrado());
		#ifndef NDEBUG
			assert(std::abs(nuevo->getCoeficiente()-(m1.getCoeficiente()-m2.getCoeficiente()))<COTA_ERROR);
			assert(nuevo->getCoeficiente()==(m1.getCoeficiente()-m2.getCoeficiente()));
			assert((nuevo->getGrado()==m1.getGrado())&&(nuevo->getGrado()==m2.getGrado()));
		#endif
		return *nuevo;
	}


	//////////////////
	// Multiplicación

	ed::Monomio & operator* (ed::Monomio const &m1, ed::Monomio const &m2)
	{
		ed::Monomio *nuevo = new ed::Monomio();
		nuevo->setCoeficiente(m1.getCoeficiente()*m2.getCoeficiente());
		nuevo->setGrado(m1.getGrado()+m2.getGrado());
		#ifndef NDEBUG
			assert(std::abs(nuevo->getCoeficiente()-(m1.getCoeficiente()*m2.getCoeficiente()))<COTA_ERROR);
			assert(nuevo->getCoeficiente()==(m1.getCoeficiente()*m2.getCoeficiente()));
			assert(nuevo->getGrado()==(m1.getGrado()+m2.getGrado()));
		#endif
		return *nuevo;
	}

	ed::Monomio & operator* (ed::Monomio const &m, double const &x)
	{
		ed::Monomio aux;
		aux=x;
		return m*aux;
	}

	ed::Monomio & operator* (double const &x, ed::Monomio const &m)
	{
		ed::Monomio aux;
		aux=x;
		return m*aux;
	}

	////////////
	// División


		ed::Monomio & operator/ (ed::Monomio const &m1, ed::Monomio const &m2)
		{
			#ifndef NDEBUG
				assert(m2.getGrado()<=m1.getGrado());
				assert(m2.getCoeficiente()!=0.0);
			#endif
			ed::Monomio *nuevo = new ed::Monomio();
			nuevo->setCoeficiente(m1.getCoeficiente()/m2.getCoeficiente());
			nuevo->setGrado(m1.getGrado()-m2.getGrado());
			#ifndef NDEBUG
				assert(std::abs(nuevo->getCoeficiente()-(m1.getCoeficiente()/m2.getCoeficiente()))<COTA_ERROR);
				assert(nuevo->getCoeficiente()==(m1.getCoeficiente()/m2.getCoeficiente()));
				assert(nuevo->getGrado()==(m1.getGrado()-m2.getGrado()));
			#endif
			return *nuevo;
		}

		ed::Monomio & operator/ (ed::Monomio const &m, double const &x)
		{
			ed::Monomio aux;
			aux=x;
			return m/aux;
		}

		ed::Monomio & operator/ (double const &x, ed::Monomio const &m)
		{
			ed::Monomio aux;
			aux=x;
			return aux/m;
		}


	/////////////////////////////////////////////////////////////////////////////

	//  Sobrecarga del operador de entrada
	istream &operator>>(istream &stream, ed::Monomio &m)
	{
		double coeficiente;
		int grado;
		stream>>coeficiente>>grado;
		m.setGrado(grado);
		m.setCoeficiente(coeficiente);
		return stream;
	}


	//  Sobrecarga del operador de salida
	ostream &operator<<(ostream &stream, ed::Monomio const &m)
	{
		stream<<m.getCoeficiente()<<" "<<m.getGrado();
		return stream;
	}


}  // namespace ed
