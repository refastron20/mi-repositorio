/*!
   \file  Monomio.cpp
   \brief Fichero que contiene el código de las funciones de la clase Monomio
*/


//  Ficheros de cabecera
#include <iostream>

#include "Monomio.hpp"

// Operadores de asignación

ed::Monomio & ed::Monomio::operator=(ed::Monomio const &m)
{
	this->setGrado(m.getGrado());
	this->setCoeficiente(m.getCoeficiente());
	#ifndef NDEBUG
		assert(std::abs(this->getCoeficiente()-m.getCoeficiente())< COTA_ERROR);
		assert(this->getCoeficiente()==m.getCoeficiente());
		assert(this->getGrado()==m.getGrado());
	#endif
	return *this;
}


ed::Monomio & ed::Monomio::operator=(double const &x)
{
	this->setGrado(0);
	this->setCoeficiente(x);
	#ifndef NDEBUG
		assert(std::abs(this->getCoeficiente()-x)< COTA_ERROR);
		assert(this->getCoeficiente()==x);
		assert(this->getGrado()==0);
	#endif
	return *this;
}



//////////////////////////////////////////////////////////////

// Operadores aritméticos y asignación

// COMPLETAR

ed::Monomio & ed::Monomio::operator+=(ed::Monomio const &m)
{
	#ifndef NDEBUG
		assert(this->getGrado()==m.getGrado());
		double auxc=this->getCoeficiente();
		int auxg=this->getGrado();
	#endif
	double suma=(this->getCoeficiente())+m.getCoeficiente();
	this->setCoeficiente(suma);
	#ifndef NDEBUG
		assert((auxc+m.getCoeficiente())==this->getCoeficiente());
		assert(std::abs((auxc+m.getCoeficiente())-this->getCoeficiente())< COTA_ERROR);
		assert(auxg==this->getGrado());
	#endif
	return *this;
}



ed:: Monomio & ed::Monomio::operator-=(ed::Monomio const &m){
	#ifndef NDEBUG
		assert(this->getGrado()==m.getGrado());
		double auxc=this->getCoeficiente();
		int auxg=this->getGrado();
	#endif
	double resta=(this->getCoeficiente())-m.getCoeficiente();
	this->setCoeficiente(resta);
	#ifndef NDEBUG
		assert((auxc-m.getCoeficiente())==this->getCoeficiente());
		assert(std::abs((auxc-m.getCoeficiente())-this->getCoeficiente())< COTA_ERROR);
		assert(auxg==this->getGrado());
	#endif
	return *this;
}

ed:: Monomio & ed::Monomio::operator*=(ed::Monomio const &m){
	#ifndef NDEBUG
		double auxc=this->getCoeficiente();
		int auxg=this->getGrado();
	#endif
	double mulcoe=(this->getCoeficiente())*m.getCoeficiente();
	int mulgr=(this->getGrado())+m.getGrado();
	this->setCoeficiente(mulcoe);
	this->setGrado(mulgr);
	#ifndef NDEBUG
		assert((auxc*m.getCoeficiente())==this->getCoeficiente());
		assert(std::abs((auxc*m.getCoeficiente())-this->getCoeficiente())< COTA_ERROR);
		assert(auxg+m.getGrado()==this->getGrado());
	#endif
	return *this;
}

ed:: Monomio & ed::Monomio::operator*=(double const &x){
	#ifndef NDEBUG
		double auxc=this->getCoeficiente();
		int auxg=this->getGrado();
	#endif
	double mulcoe=(this->getCoeficiente())*x;
	this->setCoeficiente(mulcoe);
	#ifndef NDEBUG
		assert((auxc*x)==this->getCoeficiente());
		assert(std::abs((auxc*x)-this->getCoeficiente())< COTA_ERROR);
		assert(auxg==this->getGrado());
	#endif
	return *this;
}

ed:: Monomio & ed::Monomio::operator/=(ed::Monomio const &m){
	#ifndef NDEBUG
		double auxc=this->getCoeficiente();
		int auxg=this->getGrado();
		assert(m.getCoeficiente()>0);
		assert(m.getGrado()<=this->getGrado());
	#endif
	double divcoe=(this->getCoeficiente())/m.getCoeficiente();
	int divgr=(this->getGrado())-m.getGrado();
	this->setCoeficiente(divcoe);
	this->setGrado(divgr);
	#ifndef NDEBUG
		assert((auxc/m.getCoeficiente())==this->getCoeficiente());
		assert(std::abs((auxc/m.getCoeficiente())-this->getCoeficiente())< COTA_ERROR);
		assert(auxg-m.getGrado()==this->getGrado());
	#endif
	return *this;
}

ed:: Monomio & ed::Monomio::operator/=(double const &x){
	#ifndef NDEBUG
		double auxc=this->getCoeficiente();
		int auxg=this->getGrado();
		assert(x>0);
	#endif
	double divcoe=(this->getCoeficiente())/x;
	this->setCoeficiente(divcoe);
	#ifndef NDEBUG
		assert((auxc/x)==this->getCoeficiente());
		assert(std::abs((auxc/x)-this->getCoeficiente())< COTA_ERROR);
		assert(auxg==this->getGrado());
	#endif
	return *this;
}




///////////////////////////////////////////////////////////////////////

// Funciones lectura y escritura de la clase Monomio

void ed::Monomio::leerMonomio(){
	int grado;
	double coeficiente;
	std::cout << "introduzca el coeficiente del monomio" << '\n';
	std::cin >> coeficiente;
	this->setCoeficiente(coeficiente);
	do{
		std::cout << "Escriba el grado del monomio" << '\n';
		std::cin >> grado;
		if (grado<0) {
			std::cout << "El grado debe ser mayor que 0" << '\n';
		}
	}while(grado<0);
	this->setGrado(grado);
	#ifndef NDEBUG
	assert(this->getGrado()>=0);
	#endif
}

void ed::Monomio::escribirMonomio(){
	if (this->getCoeficiente()==-1)
		std::cout << "-";
	else if(this->getCoeficiente()!=1)
		std::cout <<this->getCoeficiente();

	if (this->getGrado()>1)
		std::cout << "X^" << this->getGrado();
	else if(this->getGrado()==1)
		std::cout << "X";
	if ((this->getGrado()==0)&&(this->getCoeficiente()==1||this->getCoeficiente()==-1))
		std::cout <<std::abs(this->getCoeficiente());
}



///////////////////////////////////////////////////////////////////////

// Funciones auxiliares de la clase Monomio

double ed::Monomio::calcularValor(double const &x){
	if (this->getGrado()==0)
		return this->getCoeficiente();
	double resultado=1;
	for (int i = 0; i < this->getGrado(); i++) {
		resultado*=x;
	}
	resultado*=this->getCoeficiente();
	return resultado;
}


void ed::Monomio::derivar(){
	int gradoDerivado;
	double coeficienteDerivado;
	gradoDerivado=this->getGrado()-1;
	coeficienteDerivado=this->getCoeficiente()*this->getGrado();
	this->setGrado(gradoDerivado);
	this->setCoeficiente(coeficienteDerivado);
}

void ed::Monomio::integrar(){
	int gradoIntegrado;
	double coeficienteIntegrado;
	gradoIntegrado=this->getGrado()+1;
	coeficienteIntegrado=this->getCoeficiente()/gradoIntegrado;
	this->setGrado(gradoIntegrado);
	this->setCoeficiente(coeficienteIntegrado);
}

void ed::Monomio::potencia(int const &x){
	int gradoPotencia;
	double coeficientePotencia=1.0;
	gradoPotencia=this->getGrado()+x;
	for (int i = 0; i < x; i++) {
		coeficientePotencia*=this->getCoeficiente();
	}
	this->setGrado(gradoPotencia);
	this->setCoeficiente(coeficientePotencia);
}
