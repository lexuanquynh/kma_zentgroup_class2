#include <iostream>
#include <conio.h>
#include <stdlib.h>     /* malloc, free, rand */

using namespace std;

//Khai bao Node
typedef struct Node {
	int data;
	Node* next;
} Node;

//Khai bao List
typedef struct List {
	Node* pDau;
	Node* pCuoi;
} List;

//Tao 1 Node
Node* taoNode(int x) {
	Node* p = new Node;
	if (p == NULL)
		return NULL;

	p->data = x;
	p->next = NULL;

	return p;
}

//Tao 1 Node
Node* taoNode_c(int x) {
	Node* p = (Node*)malloc(sizeof(Node));
	
	if (p == NULL)
		return NULL;

	p->data = x;
	p->next = NULL;

	return p;
}

//Khoi tao list
void initList(List &l) {
	l.pDau = l.pCuoi= NULL;
}

// them vao dau List
void themDau(List &l, Node *p) {
	//Neu list rong
	if (l.pDau == NULL) {
		l.pDau = l.pCuoi = p;
	} else {
		p->next = l.pDau;
		l.pDau = p;
	}
}

void themCuoi(List &l, Node * p) {
	//Neu list rong
	if (l.pCuoi == NULL) {
		l.pDau = l.pCuoi = p;
	} else {
		l.pCuoi->next = p;
		l.pCuoi = p;
	}
}

int Length(const List &l) {
	int length = 0;

	for (Node* p = l.pDau; p != NULL; p = p->next) {
		length++;
	}

	return length;
}

void taoList(List &l, int sophantu) {
	initList(l);

	for (int i = 0; i < sophantu; i++)
	{
		int x;
		cout << "Nhap gia tri: ";
		cin >> x;
		
		//tao Node 
		Node* p = taoNode(x);
		themCuoi(l, p);
	}
}

void hienThiList(const List &l) {
	for (Node* p = l.pDau; p != NULL; p = p->next) {
		cout << p->data << " ";
	}
	cout << endl;
}

void giaiPhongList(List &l) {
	Node* p, *pNext;
	int count = 0;

	while (l.pDau != NULL) {
		p = l.pDau;
		pNext = p->next;

		//xoa ong dau tien
		delete p;

		//gan ong dau tien thanh ong thu 2
		l.pDau = pNext;
		count++;
	}

	cout << "Da giai phong xong "<< count <<" phan tu cua list" << endl;
}

void giaiPhongList_c(List &l) {
	Node* p, *pNext;
	int count = 0;

	while (l.pDau != NULL) {
		p = l.pDau;
		pNext = p->next;

		//xoa ong dau tien
		free(p);

		//gan ong dau tien thanh ong thu 2
		l.pDau = pNext;
		count++;
	}

	cout << "Da giai phong xong "<< count <<" phan tu cua list" << endl;
}

void insert(List &l, int k) {
	if (k < 1 || k > Length(l)) {
		cout << "Khong the them vao vi tri nay" << endl;
		return;
	}

	Node* px = new Node;

	//Tao node tu gia tri de them vao
	cout << "Nhap gia tri: ";
	cin >> px->data;
	px->next = NULL;

	//Kiem tra neu List rong thi them vao dau
	if (k == 1)
		themDau(l, px);
	else {
		int count = 1;

		//Chay toi vi tri k de them vao
		for (Node* p = l.pDau; p != NULL; p = p->next) {
			if (k == count) {
				px->next = p->next;
				p->next = px;
				break;;
			}

			count++;
		}
		
	}
}

int main()
{
	List l;
	int sophantu;

	cout<< "Nhap so phan tu cua danh sach: ";
	cin >> sophantu;

	taoList(l, sophantu);
	hienThiList(l);

	//chen vao phan tu thu k
	int k;

	cout<< "Nhap vi tri muon them: ";
	cin >> k;

	insert(l, k);
	hienThiList(l);

	giaiPhongList(l);

	getch();
	return 0;
}