#pragma once
template<class T>
class nodo
{
public:
	T valor;
	nodo* next;
	nodo* prev;
	nodo(T valor, nodo<T>* n = 0,nodo<T>*p = 0) {
		this->valor = valor;
		this->next = n;
		this->prev = p;
	}
};
