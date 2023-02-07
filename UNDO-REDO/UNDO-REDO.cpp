#include <string>
#include <iostream>
#include "stack.h"

using namespace std;

void add(string& s, string& kom, Stack* UNDO) 
{
	string new_kom = "";

	for (int i = 4; i < size(kom); i++) 
	{
		new_kom += kom[i];
		s += kom[i];
	}

	new_kom = "del_" + to_string(size(new_kom));

	Data a;
	a.kom = new_kom;
	Push(UNDO, a);
}

void del(string& s, string& kom, Stack* UNDO) 
{
	string new_kom = "add_";
	string number_str = "";

	for (int i = 4; i < size(kom); i++)
		number_str += kom[i];

	int number_int = stoi(number_str);

	string new_s = "";
	for (int i = 0; i < size(s); i++)
		new_s += s[i];
	
	s = "";
	for (int i = 0; i < size(new_s) - number_int; i++) 
		s += new_s[i];

	for (int i = size(new_s) - number_int; i < size(new_s); i++)
		new_kom += new_s[i];

	Data a;
	a.kom = new_kom;
	Push(UNDO, a);
}

void undo(string& s, Stack* UNDO, Stack* REDO)
{
	string kom = Top(UNDO).kom;
	string new_kom = "";

	if (kom[0] == 'a')
	{
		add(s, kom, UNDO);
		new_kom = "del_";
		Pop(UNDO);
		new_kom += to_string(size(kom) - 5);
	}

	if (kom[0] == 'd')
	{
		new_kom = "add_";
		string number_str = "";

		for (int i = 4; i < size(kom); i++)
			number_str += kom[i];

		int number_int = stoi(number_str);

		for (int i = size(s) - number_int; i < size(s); i++)
			new_kom += s[i];

		del(s, kom, UNDO);
		Pop(UNDO);
	}

	Data a;
	a.kom = new_kom;
	Push(REDO, a);
	Pop(UNDO);
	//cout << UNDO->top->str->kom << " " <<  << endl;
}

void redo(string& s, Stack* UNDO, Stack* REDO)
{
	//cout << Top(UNDO).kom << " " << Top(REDO).kom << endl;
	string kom = Top(REDO).kom;
	string new_kom = "";

	if (kom[0] == 'a')
		add(s, kom, UNDO);

	if (kom[0] == 'd')
		del(s, kom, UNDO);
	
	//cout << Top(UNDO).kom << endl;
	Pop(REDO);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	string s = "";
	string kom = "";
	Stack* UNDO = Create_Stack();
	Stack* REDO = Create_Stack();

	while (kom[0] != 'e')
	{
		//cout << UNDO->top << " "<<REDO->top << endl;
		cout << "введите команду:" << endl;
		if (s == "" || UNDO->top==nullptr) 
		{
			cout << "add_строка (приписывание строки в конец)" << endl <<
				"end (завершение работы программы)" << endl;
		}
		else if (REDO->top==nullptr)
		{
			cout<<"add_строка (приписывание строки в конец)" << endl <<
				"del_число (удаление N символов с конца) !!число не больше "<<size(s)<<"!!"<<endl<<
				"undo (удаление предыдущей команды)"<<endl<<
				"end (завершение работы программы)" << endl;
		}
		else
		{
			cout << "add_строка (приписывание строки в конец)" << endl <<
				"del_число (удаление N символов с конца) !!число не больше " << size(s) << "!!" << endl <<
				"undo (отмена: удаление предыдущей команды)" << endl <<
				"redo (возврат)" << endl <<
				"end (завершение работы программы)" << endl;
		}

		cin >> kom;

		if (kom[0] == 'a') 
		{
			add(s, kom, UNDO);
			Clean_Stack(REDO);
		}

	    if (kom[0] == 'd') 
		{
			del(s, kom, UNDO);
			Clean_Stack(REDO);
		}

	    if (kom[0] == 'u') undo(s, UNDO, REDO);
		if (kom[0] == 'r') redo(s, UNDO, REDO);
		
		cout << "Результат обработки: " << s << endl<<endl;
	}
}