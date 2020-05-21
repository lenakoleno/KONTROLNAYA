#pragma warning (disable:4786)
#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

struct final
{
	char name[20];
	char surname[20];
	char patronym[20];
	int group;
	int id;
	int fgrade;
	int egrade;
};

void create_data()
{
	final student;
	cout << "Фамилия:" << endl;
	cin >> student.surname;
	cin.clear();
	cout << "Имя:" << endl;
	cin >> student.name;
	cin.clear();
	cout << "Отчество:" << endl;
	cin >> student.patronym;
	cin.clear();
	cout << "Группа:" << endl;
	cin >> student.group;
	cin.clear();
	cout << "Номер в группе:" << endl;
	cin >> student.id;
	cin.clear();
	cout << "Баллы по кр:" << endl;
	cin >> student.fgrade;
	if ((student.fgrade > 200) || (student.fgrade < 0))
	{
		cout << "Некорректный ввод! Попробуйте еще раз." << endl;
		create_data();
	}
	else
	{
		ofstream database;
		database.open("task2.txt", ios::app);
		if (!database.is_open())
			cout << "Ошибка сохранения! База данных недоступна." << endl;
		else
		{
			database << student.surname << " " << student.name << " " << student.patronym << endl
				<< student.group << endl << student.id << endl
				<< student.fgrade << endl;
			database.close();
			cout << "Информация о студенте сохранена в базу данных." << endl;
		}
	}
};

int count_students()
{
	ifstream database("task2.txt");
	if (database.is_open())
	{
		int temp = 0;
		string data;
		while (!database.eof())
		{
			getline(database, data);
			temp++;
		}
		database.close();
		int n;
		n = temp / 4;
		return n;
	}
	else return 0;
}

void delete_data()
{
	ifstream database("task2.txt");
	if (!database.is_open())
		cout << "База данных недоступна." << endl;
	else
	{
		int size;
		size = count_students();
		if (size == 0)
			cout << "База данных пуста." << endl;
		else
		{
			final *student = new final[size];
			string fix;
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].fgrade;
				getline(database, fix, '\n');
			}
			database.close();
			int delete_g, delete_i;
			cout << "Введите группу и номер в списке студента, информация о котором должна быть удалена." << endl;
			cout << "Группа:" << endl;
			cin >> delete_g;
			cin.clear();
			cout << "Номер в группе:" << endl;
			cin >> delete_i;
			cin.clear();
			int found = 2147483647;
			for (int i = 0; i < size; i++)
			{
				if ((student[i].group == delete_g) && (student[i].id == delete_i))
					found = i;
			}
			if (found == 2147483647)
			{
				cout << "Ошибка! Студент не найден.";
				cout << endl << "Попробуйте еще раз." << endl;
				delete_data();
			}
			else
			{
				ofstream newdatabase;
				newdatabase.open("task2.txt");
				if (!newdatabase.is_open())
					cout << endl << "Ошибка соххранения! База данных недоступна." << endl;
				else
				{
					for (int i = 0; i < found; i++)
					{
						newdatabase << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl
							<< student[i].group << endl << student[i].id << endl
							<< student[i].fgrade << endl;
					}
					for (int i = (found + 1); i < size; i++)
					{
						newdatabase << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl
							<< student[i].group << endl << student[i].id << endl
							<< student[i].fgrade << endl;
					}
					newdatabase.close();
					cout << "Информация была удалена" << endl;
				}
			}
			delete[] student;
		}
	}
}

void show_grade(int x, int y)
{
	ifstream database("task2.txt");
	if (!database.is_open())
		cout << "База данных недоступна." << endl;
	else
	{
		int size;
		size = count_students();
		if (size == 0)
			cout << "База данных пуста." << endl;
		else
		{
			final *student = new final[size];
			string fix;
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].fgrade;

			}
			database.close();
			int temp = 0;
			for (int i = 0; i < size; i++)
			{
				if ((student[i].fgrade >= x) && (student[i].fgrade <= y))
				{
					cout << student[i].group << " " << student[i].id << " "
						<< student[i].surname << " " << student[i].name << " " << student[i].patronym << endl;
					temp++;
				}
			}
			if (temp == 0)
				cout << "Таких студентов не найдено" << endl;
			delete[] student;
		}
	}
}

void show_data()
{
	cout << "Вывести студентов, у которых:" << endl << "1) 5;" << endl << "2) 4;" << endl
		<< "3) 3;" << endl << "4) 2." << endl;
	int start1;
	cin >> start1;
	cin.clear();
	switch (start1)
	{
	case 1:
	{
		show_grade(170, 200);
	}
	break;
	case 2:
	{
		show_grade(140, 169);
	}
	break;
	case 3:
	{
		show_grade(100, 139);
	}
	break;
	case 4:
	{
		show_grade(0, 99);
	}
	break;
	default:
	{
		cout << "Некорректный ввод! Попробуйте еще раз." << endl;
		show_data();
	}
	break;
	}
}

using namespace std;
int count_students();

struct exam
{
	string surname;
	int group;
	exam *next;
	exam *prev;
};

exam * make_head(string surname, int group)
{
	exam *head = new exam;
	head->surname = surname;
	head->group = group;
	head->next = NULL;
	head->prev = NULL;
	return head;
}

void add_student(string surname, int group, exam *head)
{
	exam *node = new exam;
	node->surname = surname;
	node->group = group;
	node->next = NULL;
	exam *temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = node;
	node->prev = temp;
}

void create_list(exam *&head, final *&student, int &size)
{
	ifstream database("task2.txt");
	if (!database.is_open())
		cout << "База данных недоступна." << endl;
	else
	{
		size = count_students();
		if (size == 0)
			cout << "База данных пуста." << endl;
		else
		{
			student = new final[size];
			string fix;
			for (int i = 0; i < size; i++)
			{
				database >> student[i].surname >> student[i].name >> student[i].patronym;
				database >> student[i].group >> student[i].id >> student[i].fgrade;
			}
			database.close();
			string temp;
			temp = student[0].surname;
			head = make_head(temp, student[0].group);
			temp.clear();
			for (int i = 1; i < size; i++)
			{
				temp = student[i].surname;
				add_student(temp, student[i].group, head);
				temp.clear();
			}
			exam *temp1 = head;
			for (int i = 0; i < size; i++)
			{
				cout << temp1->group << " " << temp1->surname << endl;
				temp1 = temp1->next;
			}
		}
	}
}

void grade_students(exam *head, final *&student, int size)
{
	if (head == NULL)
	{
		cout << "Вы должны для начала создать лист!" << endl;
	}
	else
	{
		bool check = false;
		cout << "Пожалуйста поставьте каждому студенту оценку (от 1 to 5)." << endl;
		exam *temp = head;
		for (int i = 0; i < size; i++)
		{
			cout << temp->group << " " << temp->surname << ":" << endl;

			cin >> student[i].egrade;
			cin.clear();
			temp = temp->next;
			if ((student[i].egrade <= 0) || (student[i].egrade > 5))
			{
				cout << "Некорректный ввод!";
				check = true;
				break;
			}

		}
		if (check != true)
		{
			ofstream database;
			database.open("task3.txt");
			if (!database.is_open())
				cout << endl << "Ошибка сохранения! База данных недоступна." << endl;
			else
			{
				for (int i = 0; i < size; i++)
				{
					database << student[i].surname << " " << student[i].name << " " << student[i].patronym << endl
						<< student[i].group << endl << student[i].id << endl
						<< student[i].egrade << endl;
				}
				database.close();
				cout << "Информация была сохранена." << endl;
			}
		}
	}
}

using namespace std;

void generate_test()
{
	srand(time(NULL));
	int var;
	var = rand() % 2 + 1;
	cout << "Вариант №" << var << "." << endl;
	const int size = 10;
	int pool[size];
	for (int i = 0; i < size; i++)
		pool[i] = rand() % 100;
	cout << "№1. У вас есть односвязный список из " << size << " элементов:" << endl;
	for (int i = 0; i < size; i++)
		cout << pool[i] << " ";
	int x, y;
	x = rand() % 11;
	cout << endl << "Объясните как вы:" << endl
		<< "a. вставите элемент с индексом " << x << ":" << endl;
	x = rand() % 10;
	cout << "b. удалите элемент с индексом " << x << ":" << endl;
	x = rand() % 10;
	y = rand() % 10;
	cout << "c. поменяете " << x << "ый и " << y << "ый элементы." << endl;
	for (int i = 0; i < size; i++)
		pool[i] = rand() % 100;
	cout << "№2. У вас есть двусвязный список из " << size << " элементов:" << endl;
	for (int i = 0; i < size; i++)
		cout << pool[i] << " ";
	x = rand() % 11;
	cout << endl << "Объясните как вы:" << endl
		<< "a. вставите элемент с индексом " << x << ":" << endl;
	x = rand() % 10;
	cout << "b. удалите элемент с индексом " << x << ":" << endl;
	x = rand() % 10;
	y = rand() % 10;
	cout << "c. поменяете " << x << "ый и " << y << "ый элементы." << endl;
	cout << "№3. У вас есть бинарное дерево поиска:" << endl;
	switch (var)
	{
	case 1:
	{
		ifstream tree("tree_ver1.txt");
		string temp;
		while (!tree.eof())
		{
			getline(tree, temp);
			cout << temp << endl;
		}
	}
	break;
	case 2:
	{
		ifstream tree("tree_ver2.txt");
		string temp;
		while (!tree.eof())
		{
			getline(tree, temp);
			cout << temp << endl;
		}
	}
	break;
	}
	cout << "a. проверьте правильность дерева. Если нет, отредактируйте дерево соответственно:" << endl;
	switch (var)
	{
	case 1:
	{
		cout << "b. объясните как вы удалите число 22 из дерева:" << endl
			<< "c. объясните как вы вставите это число обратно в дерево:" << endl;
	}
	break;
	case 2:
	{
		cout << "b. объясните как вы удалите число 9 из дерева:" << endl
			<< "c. объясните как вы вставите это число обратно в дерево:" << endl;
	}
	break;
    }
	cout << "№4. Вам дано постфиксное выражение:" << endl
		<< "y 8 - 3 * 4 - 4 / y -" << endl;
	cout << "Найдите результат, если y = ";
	switch (var)
	{
	case 1:
	{
		cout << "12" << endl;
	}
	break;
	case 2:
	{
		cout << "20" << endl;
	}
	break;
	}
}

void show_answers()
{
	ifstream answers("test_answers.txt");
	string temp;
	while (!answers.eof())
	{
		getline(answers, temp);
		cout << temp << endl;
	}
}



using namespace std;
//ЗАДАНИЕ 1
void generate_test();
void show_answers();
//ЗАДАНИЕ 2
void create_data();
void delete_data();
void show_data();
//ЗАДАНИЕ 3
struct final;
struct exam;
exam *head = NULL;
final *student;
int lsize = 0;
void create_list(exam *&head, final *&student, int &size);
void grade_students(exam *head, final *&student, int size);


void menu()
{
	cout << "КОНТРОЛЬНАЯ РАБОТА №1 ЕФРЕМОВОЙ СОФИИ 9893гр." << endl;
	cout << "Задание №1:" << endl
		<< "1) Генерация тестов;" << endl << "2) Ответы на тест." << endl;
	cout << "Задание №2:" << endl
		<< "3) Добавление информации о студенте;" << endl << "4) Удаление информации о студенте;" << endl
		<< "5) Вывод оценок." << endl;
	cout << "Задание №3:" << endl
		<< "6) Создание листа студентов, сдающих экзамен;" << endl
		<< "7) Оценка за экзамен." << endl;
	int start0;
	cin >> start0;
	cin.clear();
	switch (start0)
	{
	case 1:
	{
		generate_test();
		menu();
	}
	break;
	case 2:
	{
		show_answers();
		menu();
	}
	break;
	case 3:
	{
		create_data();
		menu();
	}
	break;
	case 4:
	{
		delete_data();
		menu();
	}
	break;
	case 5:
	{
		show_data();
		menu();
	}
	case 6:
	{
		create_list(head, student, lsize);
		menu();
	}
	case 7:
	{
		grade_students(head, student, lsize);
		menu();
	}
	break;
	default:
	{
		cout << "Некорректный ввод!";
	}
	break;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	
	menu();
	return 0;
}
