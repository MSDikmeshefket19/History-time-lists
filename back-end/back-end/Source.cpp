#include <iostream>
#include <string>

using namespace std;

struct Node {
	string title;
	int year;
	Node* next;
};

void print(Node* node)
{
	Node* temp = node;

	while (temp)
	{
		cout << temp->title << "\n";
		cout << temp->year << "\n";
		cout << endl;
		temp = temp->next;
	}
}

void newNode(Node *&head, string title, int year)
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

int main()
{
	Node* myEvents = NULL;

	while (true) {
		string title;
		int year;
		int choice;

		cout << "Do you want create event - 1\n";
		cout << "Do you want see events - 2\n";
		cin >> choice;
		if (choice == 1) {
			cout << "Title: ";

			cin.ignore();
			getline(cin, title, '\n');

			cout << "Year: ";
			cin >> year;

			newNode(myEvents, title, year);

			cout << "Ready!\n";
		}

		if (choice == 2) {

			print(myEvents);

			cout << "Ready!\n";
		}


	}
	return 0;
}
