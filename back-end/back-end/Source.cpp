#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct Node {
	string title;
	int year;
	Node* next;
};

void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

void inputData(string* title, int* year) {
	cout << endl;

	cout << "Title: ";

	cin.ignore();
	getline(cin, *title, '\n');

	cout << "Year: ";
	cin >> *year;
}

void print(Node* node)
{
	Node* temp = node;
	int id = 0;
	while (temp)
	{
		cout << endl;
		cout << ++id << ". ";
		cout << temp->title << "-";
		cout << temp->year << " ";
		cout << endl;
		temp = temp->next;
	}
	cout << endl;
}

void newAfterNode(Node*& head, string title, int year)
{
	Node* newNode = new Node{ title, year, NULL };

	if (head == NULL) {
		head = newNode;
		return;
	}

	Node* temp = head;
	while (temp)
	{
		if (temp->next == NULL)
		{
			temp->next = newNode;
			return;
		}
		else
		{
			temp = temp->next;
		}
	}
}

void newBeforeNode(Node*& head, string title, int year)
{
	Node* newNode = new Node{ title, year, head };

	head = newNode;
}

void insertPos(Node** head, int pos, string title, int year)
{
	while (pos--) {
		if (pos == 0) {

			Node* temp = new Node{ title, year, NULL };

			temp->next = *head;

			*head = temp;
		}
		else {
			head = &(*head)->next;
		}
	}

}

void editNode(Node** head, int pos, string title, int year) {

}

void deleteNode(Node** headRef, string key)
{

	Node* temp = *headRef;
	Node* prev = NULL;

	if (temp != NULL && temp->title == key)
	{
		*headRef = temp->next;
		delete temp;
		return;
	}

	else
	{
		while (temp != NULL && temp->title != key)
		{
			prev = temp;
			temp = temp->next;
		}

		if (temp == NULL)
			return;

		prev->next = temp->next;

		delete temp;
	}
}

int main()
{
	Node* myEvents = NULL;

	while (true) {
		string title;
		int year;

		int choice;
		int pos;

		cout << "Do you want create after event - 1\n";
		cout << "Do you want create before event - 2\n";
		cout << "Do you want create position event - 3\n";
		cout << "Do you want see events - 4\n";
		cout << "Do you want edit event - 5\n";
		cout << "Do you want delete event - 6\n";
		cout << "Select number: ";
		cin >> choice;

		switch (choice) {
		case 1:
			inputData(&title, &year);
			newAfterNode(myEvents, title, year);
			break;
		case 2:
			inputData(&title, &year);
			newBeforeNode(myEvents, title, year);
			break;
		case 3:
			print(myEvents);
			cout << "\nPick position: ";
			cin >> pos;
			inputData(&title, &year);
			insertPos(&myEvents, pos, title, year);
			break;
		case 4:
			print(myEvents);
			break;
		case 5:
			print(myEvents);
			cout << "\nPick position: ";
			cin >> pos;
			inputData(&title, &year);
			editNode(&myEvents, pos, title, year);
			break;
		case 6:
			print(myEvents);
			cout << "\nSelect title: ";
			string deleteThisTitle;
			cin.ignore();
			getline(cin, deleteThisTitle, '\n');
			deleteNode(&myEvents, deleteThisTitle);
			break;
		}

		string ready;
		cout << "Ready? - ";
		cin.ignore();
		getline(cin, ready, '\n');
		clear();

	}
	return 0;
}
