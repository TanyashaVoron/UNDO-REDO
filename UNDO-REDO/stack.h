#pragma once
#include <string>
#include <iostream>
using namespace std;

struct Data 
{
	string kom ;
};

struct Node 
{
	Data str;
	Node* next;
};

struct Stack 
{
	Node* top;
};

Stack* Create_Stack(); //�������

void Clean_Stack(Stack* s); //��������

void Push(Stack* s, Data& str); // +1

void Pop(Stack* s); // -1

Data Top(Stack* s); // ���������