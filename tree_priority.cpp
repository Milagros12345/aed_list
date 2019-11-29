#include <iostream>
#include <vector>
#include <queue>
#include<Windows.h>
using namespace std;
template<class T>
bool Asc(T a, T b) {//1,2,3
	return a > b;
}
template<class T>
bool Desc(T a, T b) {//3,2,1
	return a < b;
}
template<class T>
class nodo {
public:
	T valor;
	nodo<T>* hijo[2]; // indices[0] y n elementos[2]
	nodo(T x) {
		valor = x;
		hijo[0] = NULL;
		hijo[1] = NULL;
	}
};
template<class T>
class tree {
public:
	nodo<T>* root;
	vector<nodo<T>*>m;
	queue<nodo<T>*>lis;

	tree() { root = NULL; }
	bool find(T x, nodo<T>**& p) {
		for (p = &root; *p && (*p)->valor != x; p = &((*p)->hijo[(*p)->valor < x]));
		return !!*p;//niego direccion y vuelvo a negar
	}
	bool insert(T x) {
		nodo<T>** p;
		if (find(x, p))//si encuentras el valor
			return 0;// sales xq en sin repeticion

		*p = new nodo<T>(x);// no requiere enlaca xeso no se crea un temp
		return 1;
	}
	nodo<T>** Rep(nodo<T>** r) {
		for (r = &((*r)->hijo[1]); (*r)->hijo[0]; r = &((*r)->hijo[0]))
			return r;
	}
	bool Remove(T x)
	{
		nodo<T>** p;//cout<<"entra"<<endl;
		if (!find(x, p)) return 0;
		if ((*p)->hijo[0] != 0 && (*p)->hijo[1] != 0)
		{
			nodo<T>** q = Rep(p); cout << "q: " << (*q)->valor << endl;
			(*p)->valor = (*q)->valor;
			p = q;
		}
		nodo<T>* t = *p;
		*p = (*p)->hijo[!(*p)->hijo[0]];
		delete t;
		return 1;
	}
	void niveles() {
		vector<nodo<T>*> lista;
		int len;
		lista.push_back(root);
		while (lista.size() != 0) {
			len = lista.size();
			for (int i = 0; i < len; i++) {
				if (lista[i]) {
					cout << "  " << lista[i]->valor;
					lista.push_back(lista[i]->hijo[0]);
					lista.push_back(lista[i]->hijo[1]);
				}
			}
			cout << endl;
			lista.erase(lista.begin(), lista.begin() + len);
		}
	}
	void nivel()
	{
		nodo<T>* p = root;
		lis.push(p);
		while (!lis.empty()) {
			p = lis.front();
			if (p->hijo[0])
				lis.push(p->hijo[0]);
			if (p->hijo[1]) {
				lis.push(p->hijo[1]);
			}
			cout << lis.front()->valor << "  ";
			lis.pop();
		}
	}
	bool find2(T x) {
		for (int i = 0; i < m.size(); i++) {
			if (m[i]->valor == x)
				return true;
		}
		return false;
	}
	bool insertar(T x,bool (*pf)(T, T)) {
		nodo<T>* tmp = new nodo<T>(x);
		nodo<T>* p=root;
		if (find2(x))return 0;
		else {
			if (m.empty()) {
				root = tmp;
				m.push_back(root);
			}
			else {
				int i = 0;
				while (true) {
					p = m[i];
					if (!p->hijo[0])
					{
						p->hijo[0] = tmp;
						m.push_back(p->hijo[0]);
						break;
					}
					else if (!p->hijo[1]) {
						p->hijo[1] = tmp;
						m.push_back(p->hijo[1]);
						break;
					}i++;
				}

			}
			//ordenando por niveles	
			priority(pf);
		}
	}
	void priority(bool (*pf)(T, T)) {
		int t = m.size() - 1;
		while (t >= 1 && (*pf)(m[t]->valor, m[(t - 1) / 2]->valor)) {
			swap(m[t]->valor, m[(t - 1) / 2]->valor);
			t = (t - 1) / 2;
		}
	}
	nodo<T>* padre() {
		int t = m.size();
		if (t == 1)
			return m[0];
		return m[(t / 2)-1];
	}
	void pop_(bool(*pf)(T, T)) {
		nodo<T>* p = padre();
		m[0]->valor = m[m.size() - 1]->valor;
		nodo<T>* tmp;
		if (p->hijo[1]) {
			tmp = p->hijo[1];
			p->hijo[1] = NULL;
			delete tmp;
		}
		else {
			tmp = p->hijo[0];
			p->hijo[0] = NULL;
			delete tmp;

		}
		m.pop_back();
		eliminar(1, pf);
	}
	void eliminar(int i,bool (*pf)(T,T)) {
		int left = 2 * i;//1
		int right = (2 * i + 1);//2
		int parent = i;//1 real 0
		if (left - 1 < m.size() && (*pf)(m[left - 1]->valor, m[parent - 1]->valor))//>
			parent = left;
		if (right - 1 < m.size() && (*pf)(m[right - 1]->valor, m[parent - 1]->valor))//>
			parent = right;
		if (parent != i)
		{
			swap(m[i - 1]->valor, m[parent - 1]->valor);
			eliminar(parent, pf);
		}
	}
	void heapsort(bool (*pf)(T, T)) {
		cout << "los eliminamos " << endl;
		for (unsigned int i = 1; i < m.size();) {
			cout << m[0]->valor << " ";
			pop_(pf);
		}
	}
};
void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
template<class T>
void mostrar(nodo<T>* a, int x, int y) {
	if (a != NULL) {
		gotoxy(x, y);
		cout << a->valor << endl;
		x = x - 3;
		y = y + 3;
		mostrar(a->hijo[0], x, y);
		x = x + 4;
		mostrar(a->hijo[1], x, y);
		y = y - 3;
	}
}
int main()
{
	tree<int>a;
	int n;
	
	do{
		cout << "opciones   :" << endl;
		cout << "1.  insertar " << endl;
		cout << "2.   borrar  " << endl;
		cout << "3.   headsort" << endl;
		cout << "4.   mostrar" << endl;
		cout << "5.   salir" << endl;
		cin >> n;
		if (n == 1) {
			int x; cout << "cuantos elementos va insertar " << endl;
			cin >> x;
			while (x--) {
				int dato;
				cout << "dato  ";
				cin >> dato;
				a.insertar(dato,Asc);
			
			}
		}
		if (n == 2) {
			a.pop_(Asc);
		}
		if (n == 3) {
			a.heapsort(Asc);
		}
		if (n == 4) {
			//a.niveles();
			mostrar(a.root,40,20);
			cout << endl;
			a.nivel();
		}
	} while (n != 5);
	return 0;

}

