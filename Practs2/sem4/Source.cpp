/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no se tendr� en cuenta para la correcci�n.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
	Introduce aqu� los nombres de los componentes del grupo:

	Componente 1:Carlos Forriol Molina
	Componente 2:Daniel Garcia Arroyo
  */
  //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>

using namespace std;

// Puedes copiar aqu� algunas de las implementaciones de los TADs vistos esta semana:

// Pilas: https://github.com/manuelmontenegro/ED/blob/main/lineales/stack_linkedlist/stack_linkedlist.h
// Colas: https://github.com/manuelmontenegro/ED/blob/main/lineales/queue_linkedlist/queue_linkedlist.h
// Colas dobles: https://github.com/manuelmontenegro/ED/blob/main/lineales/deque/dequeue.h

// En caso de utilizar alguno de los TADs anteriores, ha de copiarse TAL CUAL, sin realizar ning�n cambio
// en sus implementaciones. Para facilitar la correcci�n, coloca la implementaci�n de estos TADs fuera
// de las etiquetas <answer> y </answer>. El profesor asumir� que tienen la misma implementaci�n que la
// vista en teor�a.

// Alternativamente, puedes utilizar las clases de la librer�a est�ndar de C++ (stack<T>, queue<T> y deque<T>).

/*
 * Implementaci�n del TAD Cola mediante listas enlazadas.
 */

#ifndef __QUEUE_LINKEDLIST_H
#define __QUEUE_LINKEDLIST_H

#include <cassert>
#include <iostream>

template <typename T> class QueueLinkedList {
public:
	QueueLinkedList() : front_node(nullptr), back_node(nullptr) {}
	QueueLinkedList(const QueueLinkedList& other) {
		copy_nodes_from(other.front_node);
	}

	~QueueLinkedList() { free_nodes_from(front_node); }

	QueueLinkedList& operator=(const QueueLinkedList& other) {
		if (this != &other) {
			free_nodes_from(front_node);
			copy_nodes_from(other.front_node);
		}
		return *this;
	}

	void push(const T& elem) {
		Node* new_node = new Node{ elem, nullptr };
		if (back_node == nullptr) {
			back_node = new_node;
			front_node = new_node;
		}
		else {
			back_node->next = new_node;
			back_node = new_node;
		}
	}

	void pop() {
		assert(front_node != nullptr);
		Node* target = front_node;
		front_node = front_node->next;
		if (back_node == target) {
			back_node = nullptr;
		}
		delete target;
	}

	T& front() {
		assert(front_node != nullptr);
		return front_node->value;
	}

	const T& front() const {
		assert(front_node != nullptr);
		return front_node->elem;
	}

	bool empty() const { return (front_node == nullptr); }

private:
	struct Node {
		T value;
		Node* next;
	};

	void copy_nodes_from(Node* other);
	void free_nodes_from(Node* other);

	Node* front_node;
	Node* back_node;
};

template <typename T> void QueueLinkedList<T>::copy_nodes_from(Node* other) {
	if (other == nullptr) {
		front_node = nullptr;
		back_node = nullptr;
	}
	else {
		front_node = new Node{ other->value, nullptr };
		back_node = front_node;
		Node* current = other->next;
		while (current != nullptr) {
			Node* new_node = new Node{ current->value, nullptr };
			back_node->next = new_node;
			current = current->next;
			back_node = new_node;
		}
	}
}

template <typename T> void QueueLinkedList<T>::free_nodes_from(Node* other) {
	Node* current = other;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

#endif



//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aqu�
// --------------------------------------------------------------
void resuelveCaso(QueueLinkedList<int>& hongo1, QueueLinkedList<int>& hongo2,int n,int m,int &contHongos) {
	int temp = 0,aux=0;
	temp = contHongos;
	
	for (int i = 0; i < temp; i++) {
		
		aux = hongo1.front() - 1;
		
		if (aux == 0) {
			if (i == 0) {
				hongo2.push(n);
			}
			else {
				hongo2.push(m);
			}
			contHongos++;
		}
		else {
			hongo2.push(aux);
		}
		hongo1.pop();

	}
}

int resolver(int n,int m,int t){	
	
	QueueLinkedList<int> adulto;
	QueueLinkedList<int>yema;
	int contTiempo = 0,contHongos=1,contAdulto=0,contYema=m-n;
	//Cola Adulto
	while (contAdulto < n-1) {
		adulto.push(0);
		contAdulto++;
	}
	//Metemos 1 final de la cola(ira decrementando en posiciones) en while
	adulto.push(1);

	//Cola Yema de tama�o diferencia con el padre
	while (contYema > 0) {
		yema.push(0);
		contYema--;
	}
	while (contTiempo < t) {
		//fronts adulto y Yema
		int primPosYe = yema.front();
		int primPosAd = adulto.front();
		
		adulto.push(primPosAd + primPosYe);

		//el 1 del adulto llega a prim posicion
		if (primPosAd != 0)contHongos += primPosAd;

		adulto.pop();
		yema.pop();
		//metemos la primPos del adulto final Yema
		yema.push(primPosAd);

		contTiempo++;
	}
	return contHongos;
}


// Indica el coste en funci�n de los par�metros del problema (N, M, T)
bool tratar_caso() {
	// Introduce aqu� el c�digo para tratar un caso de prueba.
	// Devuelve false si ya no hay m�s casos de prueba que leer,
	// true en caso contrario.
	int n, m, t;
	cin >> n >> m >> t;
	if (!cin)return false;
	cout << resolver(n, m, t)<<endl;
	return true;

}

//---------------------------------------------------------------
// No modificar por debajo de esta l�nea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}