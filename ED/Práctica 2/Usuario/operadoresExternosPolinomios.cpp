/*!
   \file operadoresExternosPolinomios.cpp
   \brief Fichero que contiene el código de las funciones de la clase Polinomio
*/


// Ficheros de cabecera
#include <iostream>

#include "operadoresExternosPolinomios.hpp"

#include "operadoresExternosMonomios.hpp"

// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed
{

bool operator==(ed::Polinomio const & p1, ed::Polinomio const & p2)
{
		if (p1.esNulo() and p2.esNulo())
			return true;

		if (p1.getGrado()!=p2.getGrado())
			return false;

		for (int i = 0; i < p1.getGrado(); i++) {
			if(p1.existeMonomio(i) and not p2.existeMonomio(i)){
				if (p1.getMonomio(i).getCoeficiente()>0)
					return false;
			}else if(p2.existeMonomio(i) and not p1.existeMonomio(i))
				return false;
			else if(p1.getMonomio(i)!=p2.getMonomio(i))
				return false;
		}
		return true;
}



////////////////////////////////////////////////////////////////////////////

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, Polinomio &p)
{
	int nPolinomios;
	Monomio m;
	stream>>nPolinomios;
	for (int i = 0; i < nPolinomios; i++) {
		stream>>m;
		if (m.getGrado()!=0 and m.getCoeficiente()!=0)
			p.insertarMonomio(m);
		i++;
	}
  return stream;
}



// Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, Polinomio const &p)
{
	if (p.esNulo()) {
		stream<<0;
	}else{
		stream<<p.getMonomio(p.getGrado());
		for (int i = p.getGrado()-1; i >=0; i--) {
			if (p.existeMonomio(i)) {
				if (p.getMonomio(i).getCoeficiente()>0) {
					stream<<"+"<<p.getMonomio(i);
				}else if(p.getMonomio(i).getGrado()>0 or p.getMonomio(i).getCoeficiente()!=0){
					stream<<p.getMonomio(i);
				}
			}
		}
	}
  return stream;
}


} // Fin del espacio de nombres ed
