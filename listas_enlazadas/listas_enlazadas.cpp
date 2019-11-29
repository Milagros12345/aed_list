
#include <iostream>
using namespace std;
template<class T>
class nodo {
public:
	T m_x;
	nodo<T>* next;
	nodo(T x) { m_x = x; next = 0; }
};
template<class T>
class lista {
public:
	nodo<T>*head;
	lista() { head = 0; }
	bool find(T x, nodo<T>**& p) {
		for(p=&head;*p&&x>(*p)->m_x;p=&(*p)->next)
		{
			return *p && (*p)->m_x == x;
		}
	}
};

int main()
{
	nodo <int> node(9); nodo<int>* p;
	p->m_x = 15;
	p->next =node.m_x;
	cout << node.m_x << endl;
	
	
}
