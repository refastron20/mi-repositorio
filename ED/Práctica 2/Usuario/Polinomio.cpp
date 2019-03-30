/*!
   \file Polinomio.cpp
   \brief Fichero que contiene el código de las funciones de la clase Polinomio
*/


// Ficheros de cabecera
#include <iostream>

#include "Polinomio.hpp"

#include "Monomio.hpp"


// Operadores de asignación

// COMPLETAR


/////////////////////////////////////////////////////////////

ed::Polinomio & ed::Polinomio::operator=(ed::Polinomio const &p)
{

	this->setPolinomio(p);

	return *this;
}


ed::Polinomio & ed::Polinomio::operator=(ed::Monomio const &m)
{
	list <Monomio> aux;
	aux.push_front(m);
	this->setPolinomio(aux);
	return *this;
	#ifndef NDEBUG
		assert(aux.front()==m);
	#endif
	return *this;
}


ed::Polinomio & ed::Polinomio::operator=(double const &x)
{
	Monomio m=x;
	list <Monomio> aux;
	aux.push_front(m);
	this->setPolinomio(aux);
	#ifndef NDEBUG
		assert((std::abs(aux.front().getCoeficiente()-x)<COTA_ERROR)&&(aux.front().getGrado()==0));
	#endif
	return *this;
}

//////////////////////////////////////////////////////////////

ed::Polinomio & ed::Polinomio::operator+=(ed::Polinomio const &p)
{
	Polinomio aux;
	if (this->getGrado()>=p.getGrado()) {
		for (int i = 0; i <= this->getGrado(); i++) {
			if (this->existeMonomio(i) and p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i)+p.getMonomio(i));
			else if (this->existeMonomio(i) and  not p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i));
			else if (not this->existeMonomio(i) and p.existeMonomio(i))
					aux.insertarMonomio(p.getMonomio(i));
		}
	}else if(this->getGrado()<p.getGrado()){
		for (int i = 0; i <= p.getGrado(); i++) {
			if (this->existeMonomio(i) and p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i)+p.getMonomio(i));
			else if (this->existeMonomio(i) and  not p.existeMonomio(i))
				aux.insertarMonomio(this->getMonomio(i));
			else if (not this->existeMonomio(i) and p.existeMonomio(i))
					aux.insertarMonomio(p.getMonomio(i));
		}
	}
	*this=aux;
	return *this;
}


ed::Polinomio & ed::Polinomio::operator-=(ed::Polinomio const &p){
	Polinomio aux;
	for (int i = 0; i <= p.getGrado(); i++) {
		if (p.existeMonomio(i)) {
			aux.insertarMonomio(-(p.getMonomio(i)));
		}
	}
	*this+=aux;
	return *this;
}

ed::Polinomio & ed::Polinomio::operator*=(Polinomio const &p){
	list <Monomio> aux;
	for (int j = 0; j <= p.getGrado(); j++) {
		if (p.existeMonomio(j)) {
			for (int i = 0; i <= this->getGrado(); i++) {
				if (this->existeMonomio(i)) {
					aux.push_front(this->getMonomio(i)*p.getMonomio(j));
				}
			}
		}
	}
	this->setPolinomio(aux);
	return *this;
}

ed::Polinomio & ed::Polinomio::operator*=(Monomio const &m){
	list <Monomio> aux;
	for (int i = 0; i <= this->getGrado(); i++) {
		if (this->existeMonomio(i)) {
			aux.push_front(this->getMonomio(i)*m);
		}
	}
	this->setPolinomio(aux);
	return *this;
}

ed::Polinomio & ed::Polinomio::operator*=(double const &x){
	Monomio m(x);
	*this*=m;
	return *this;
}

ed::Polinomio & ed::Polinomio::operator/=(Polinomio const &p){
	#ifndef NDEBUG
		assert((this->getGrado()>=p.getGrado()) && !(p.esNulo()));
	#endif
	Polinomio aux;
	for (int j = 0; j <= p.getGrado(); j++) {
		if (p.existeMonomio(j)) {
			for (int i = 0; i <= this->getGrado(); i++) {
				if (this->existeMonomio(i)) {
					if((this->getMonomio(i).getGrado()>=p.getMonomio(j).getGrado()) and p.getMonomio(j).getCoeficiente()>0){
						aux.insertarMonomio(this->getMonomio(i)/p.getMonomio(j));
					}
				}
			}
		}
	}
	*this=aux;
	return *this;
}

ed::Polinomio & ed::Polinomio::operator/=(Monomio const &m){
	list <Monomio> aux;
	for (int i = 0; i <= this->getGrado(); i++) {
		if (this->existeMonomio(i)) {
			aux.push_front(this->getMonomio(i)/m);
		}
	}
	this->setPolinomio(aux);
	return *this;
}

ed::Polinomio & ed::Polinomio::operator/=(double const &x){
	Monomio m(x);
	*this/=m;
	return *this;
}


///////////////////////////////////////////////////////////////////////

// Funciones lectura y escritura de la clase Polinomio

void ed::Polinomio::leerPolinomio(){
	int n, i=0, aux;
	Monomio m;
	Polinomio p;
	do{
		std::cout << "¿Cuantos Monomios va a introducir? Recuerde que la inserción es ordenada" << '\n';
		std::cin >> n;
		if (n<=0)
			std::cout << "Introduzca un número válido" << '\n';
	}while(n<0);

	do{
		std::cout << "Datos del monomio 1"<<'\n';
		m.leerMonomio();
		aux=m.getGrado();
		if (m.getGrado()<n-1)
			std::cout << "No puedes introducir ese grado" << '\n';
		else
			p.insertarMonomio(m);
	}while(m.getGrado()<n-1);

	while(i<n-1){
		std::cout << "Datos del monomio "<< i+2<< '\n';
		m.leerMonomio();
		if (m.getGrado()<aux){
			p.insertarMonomio(m);
			i++;
			aux=m.getGrado();
		}else
			std::cout << "La introducción es ordenada!!!" << '\n';
	}

	*this=p;
}

void ed::Polinomio::escribirPolinomio(){
	int i = this->getGrado();
	this->getMonomio(i).escribirMonomio();
	i--;
	for (; i >= 0; i--) {
		if (this->existeMonomio(i)) {
			if (this->getMonomio(i).getCoeficiente()>0) {
				std::cout << "+";
			}
			if (this->getMonomio(i).getCoeficiente()!=0)
				this->getMonomio(i).escribirMonomio();
		}
	}
}


///////////////////////////////////////////////////////////////////////

// Funciones auxiliares de la clase Polinomio

void ed::Polinomio::insertarMonomio(Monomio const &m){
	list <Monomio> aux;
	if (m.getGrado()>this->getGrado()) {
		for (int i = 0; i <= this->getGrado(); i++) {
			if (this->existeMonomio(i)) {
				aux.push_front(this->getMonomio(i));
			}
		}
		aux.push_front(m);
	}else{
		for (int i = 0; i <= this->getGrado(); i++) {
			if ((this->existeMonomio(i))&&(m.getGrado()==this->getMonomio(i).getGrado())){
				aux.push_front(this->getMonomio(i)+m);
				if (aux.front().getCoeficiente()==0.0) {
					aux.pop_front();
				}
			}else if((this->existeMonomio(i))&&!(m.getGrado()==this->getMonomio(i).getGrado()))
				aux.push_front(this->getMonomio(i));
			else if(!(this->existeMonomio(i))&&i==m.getGrado())
				aux.push_front(m);
		}
	}
	this->setPolinomio(aux);
}
