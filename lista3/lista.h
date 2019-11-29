#pragma once
#include <iostream>
#include "nodo.h"
using namespace std;
template<class T>
class lista
{
public:

	nodo<T>* head = NULL;
	nodo<T>* tail = NULL;
	bool find(T dato, nodo<T>*& ptr) {
		ptr = NULL;
		for (nodo<T>* p = head; p && p->valor <= dato; ptr = p, p = p->next) {
			if (p->valor == dato)
				return true;
		}
		return false;
	}
	void add(T dato) {
		nodo<T>* pos;
		if (!find(dato, pos)) {
			if (!pos) {
				if (!head) {
					head = new nodo<T>(dato, head);
					tail = head;
				}
				else {
					head = new nodo<T>(dato, head);
					head->next->prev = head;
				}
				cout << "tail " << head->prev->valor << endl;
			}
			else {
				pos->next = new nodo<T>(dato, pos->next,pos);
				if (tail->valor < dato) {
					tail = pos->next;
				}

			}
		}

	}
	void erase(T dato) {
		nodo<T>* pos;
		if (find(dato, pos)) {
			if (!pos) {
				nodo <T>* tmp = head;
				head = head->next;
				delete tmp;
			}
			else {
				nodo<T>* tmp = pos->next;
				pos->next = pos->next->next;
				delete tmp;
			}
		}
	}
	void print() {
		nodo<T>* h = head;
		if (!h) { cout << "lista vacia" << endl; }
		else {
			while (h != NULL) {
				cout << h->valor << " ";
				h = h->next;
			}
		}
	}
};



