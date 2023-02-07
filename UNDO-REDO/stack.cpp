#include "stack.h"
#include <string>
#include <iostream>
using namespace std;

Stack* Create_Stack() //создание стека
{
	Stack *s = new Stack;
	s->top = nullptr; //заполнениe
	return s;
}

void Clean_Stack(Stack* s) //очистка стека
{
	Node* last = s->top;
	Node* second = nullptr;

	while (last != nullptr) 
	{
		second = last;
		last = last->next;
		delete second;
	}
}

void Push(Stack* s, Data& str) //+1
{
	Node* n = new Node;

	n->next = s->top;
	n->str = str;
	s->top = n;


}

void Pop(Stack* s) //-1
{
	Node* r = s->top;
	s->top = r->next;
	Data ret = r->str;
	delete r;
}

Data Top(Stack* s) //чтение
{
    Node* r = s->top;
	Data ret = r->str;
	return ret;
}