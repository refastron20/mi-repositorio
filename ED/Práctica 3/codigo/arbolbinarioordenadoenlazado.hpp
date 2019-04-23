#ifndef __ARBOLBINARIOORDENADO_HPP__
#define __ARBOLBINARIOORDENADOENLAZADO_HPP__

#include <iostream>
#include <cassert>
#include "arbolbinarioordenado.hpp"
#include "operadornodo.hpp"

using namespace std;
/*!
\brief Espacio de nombres para la asignatura Estructura de datos.
*/
namespace ed
{
	/*!\brief Interfaz para definir un ArbolBinario ordenado.

	Define una interfaz para definir un ArbolBinarioOrdenado.

	\arg G define el campo de información a contener en el arbol.
	\pre G debe tener definidos los operadores < y ==.
	*/
	template<class G>
	class ArbolBinarioOrdenadoEnlazado:public ArbolBinarioOrdenado<G>
	{
	private:

		/*!\brief Define un nodo del arbol binario.*/
		class NodoArbolBinario
		{
		private:
			G _info;  //Valor informativo almacenado en el nodo
			NodoArbolBinario * _izquierdo;  //Puntero al hijo izquierdo
			NodoArbolBinario * _derecho;  //Puntero al hijo derecho

		public:
			NodoArbolBinario (const G &info)
			{
				this->setInfo(info);

				#ifndef NDEBUG
					assert(this->getIzquierdo()==NULL);
					assert(this->getDerecho()==NULL);
				#endif
			}

			NodoArbolBinario (const NodoArbolBinario &n)
			{
				*this=n;

				#ifndef NDEBUG
					assert(this->getInfo()==n.getInfo());
					assert(this->getDerecho()==n.getDerecho());
					assert(this->getIzquierdo()==n.getIzquierdo());
				#endif
			}

			/*!\brief Observadores.*/
			const G & getInfo() const
			{
				return _info;
			}

			NodoArbolBinario *getIzquierdo() const
			{
				return _izquierdo;
			}

			NodoArbolBinario *getDerecho() const
			{
				return _derecho;
			}

			bool esHoja() const
			{
				if (this->getDerecho()==NULL and this->getIzquierdo()==NULL) {
					return true;
				}else{
					return false;
				}
			}

			void recorridoPreOrden (OperadorNodo<G> &operador) const
			{
				this->getInfo().aplicar();
				if (not this->esHoja()){
					recorridoPreOrden(this->getIzquierdo());
					recorridoPreOrden(this->getDerecho());
				}
			}

			void recorridoPostOrden (OperadorNodo<G> &operador) const
			{
				if (not this->esHoja()) {
					recorridoPostOrden(this->getIzquierdo());
					recorridoPostOrden(this->getDerecho());
					this->getInfo().aplicar();
				}else{
					this->aplicar();
				}
			}

			void recorridoInOrden (OperadorNodo<G> &operador) const
			{
				if (not this->esHoja()) {
					recorridoInOrden(this->getIzquierdo());
					this->getInfo().aplicar();
					recorridoInOrden(this->getDerecho());
				}else{
					this->aplicar();
				}
			}

			/*!\brief Modificadores. */
			void setInfo(const G &info)
			{
				_info=info;

				#ifndef NDEBUG
					assert(_info==info);
				#endif
			}

			void setIzquierdo(NodoArbolBinario *n)
			{
				_izquierdo=&n;

				#ifndef NDEBUG
					assert(_izquierdo==&n);
				#endif
			}

			void setDerecho(NodoArbolBinario *n)
			{
				_derecho=&n;

				#ifndef NDEBUG
					assert(_derecho==&n);
				#endif
			}

			NodoArbolBinario & operator=(const NodoArbolBinario &n)
			{
				#ifndef NDEBUG
					assert(this->getInfo()!=n.getInfo());
					assert(this->getIzquierdo()!=n.getIzquierdo());
					assert(this->getDerecho()!=n.getDerecho());
				#endif

				this->setInfo(n.getInfo());
				this->setIzquierdo(n.getIzquierdo());
				this->setDerecho(n.getDerecho());

				#ifndef NDEBUG
					assert(this->getInfo()==n.getInfo());
					assert(this->getIzquierdo()==n.getIzquierdo());
					assert(this->getDerecho()==n.getDerecho());
				#endif

				return *this;
			}

		}; //Fin clase NodoArbolBinario

		//Implementación de la raíz
		NodoArbolBinario * _raiz; /*!<La raiz del árbol*/
		NodoArbolBinario * _actual; /*!<Cursor al nodo actual*/
		NodoArbolBinario * _padre; /*!<Cursor al nodo padre de actual*/

		void setRaiz(NodoArbolBinario *raiz){
			_raiz=raiz;
		}

		NodoArbolBinario *getRaiz() const {
			return _raiz;
		}

		void setActual(NodoArbolBinario *actual){
			_actual=actual;
		}

		NodoArbolBinario *getActual() const {
			return _actual;
		}

		void setPadre(NodoArbolBinario *padre){
			_padre=padre;
		}

		NodoArbolBinario *getPadre() const {
			return _padre;
		}

	public:

		ArbolBinarioOrdenadoEnlazado ()
		{
			this->setRaiz(NULL);
			this->setActual(NULL);
			this->setPadre(NULL);

			#ifndef NDEBUG
				assert(this->estaVacio());
			#endif
		}

		ArbolBinarioOrdenadoEnlazado (const ArbolBinarioOrdenadoEnlazado<G>& a)
		{
			*this==a;
			#ifndef NDEBUG
				assert(a.getRaiz()==this->getRaiz() and a.getActual()==this->getActual() and a.getPadre()==this->getPadre());
			#endif
		}

		~ArbolBinarioOrdenadoEnlazado ()
		{
			if (not this->estaVacio())
			borrarArbol();
			cout << "Destructor Usado \n";
		}

		ArbolBinarioOrdenadoEnlazado &operator=(const ArbolBinarioOrdenadoEnlazado& a)
		{
			this->setRaiz(a.getRaiz());
			this->setActual(a.getActual());
			this->setPadre(a.getPadre());
			#ifndef NDEBUG
				assert(a.getRaiz()==this->getRaiz() and a.getActual()==this->getActual() and a.getPadre()==this->getPadre());
			#endif
		}

		bool insertar(const G &x)
		{
			if (this->buscar(x)) {
				return true;
			}

			this->setPadre(NULL);
			this->setActual(this->getRaiz());
			while(!(this->getActual().esHoja()){
				
			}
		}

		void borrarArbol()
		{
			this->setRaiz(NULL);
			this->setActual(NULL);
			this->setPadre(NULL);
		}

		bool borrar()
		{
			// TODO
			return false;
		}

		void recorridoPreOrden (OperadorNodo<G> &operador) const
		{
			// TODO
		}

		void recorridoPostOrden (OperadorNodo<G> &operador) const
		{
			// TODO
		}

		void recorridoInOrden (OperadorNodo<G> &operador) const
		{
			// TODO
		}

		bool buscar(const G& x) const
		{
			this->setPadre(NULL);
			this->setActual(this->getRaiz());
			while(1){
				if (x==this->actual()) {
					#ifndef NDEBUG
						assert(x==this->actual());
					#endif
					return true;
				}else if(x>*(this->getActual())){
					if (this->getActual().getDerecho()==NULL) {
						return false;
					}else{
						this->setPadre(this->getActual());
						this->setActual(this->getActual().getDerecho());
					}
				}else{
					if (this->getActual().getIzquierdo()==NULL) {
						return false;
					}else{
						this->setPadre(this->getActual());
						this->setActual(this->getActual().getIzquierdo());
					}
				}
			}
		}

		bool estaVacio() const
		{
			if (this->getRaiz()==NULL and this->getActual()==NULL and this->getPadre()==NULL) {
				return true;
			}
			return false;
		}

		G raiz() const
		{
			#ifndef NDEBUG
				assert(not this->estaVacio());
			#endif
			return *_raiz;
		}

		bool existeActual() const
		{
			#ifndef NDEBUG
				assert(!(this->estaVacio()));
			#endif
			if (this->getActual()==NULL)
				return false;

			return true;
		}

		G actual() const
		{
			#ifndef NDEBUG
				assert(this->getActual()==NULL);
			#endif
			return *(this->getActual());
		}

		/*!@}*/
	};

} //namespace ed

#endif //__ARBOLORDENADO_HPP__
