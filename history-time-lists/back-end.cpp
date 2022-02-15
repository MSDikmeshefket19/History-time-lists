// Made by Stas Uzunov

#include "back-end.h"
#include "front-end.h"


/*
 * @brief Function for inserting data as the last item in a linked list
*/

void newAfterNode(Node*& head, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description)
{
	Node* newNode = new Node{ title, year, grayYear, participants, era, location, reason, result, description, NULL };

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

/*
 * @brief Function for inserting data as the first item in a linked list
*/

void newBeforeNode(Node*& head, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description)
{
	Node* newNode = new Node{ title, year, grayYear, participants, era, location, reason, result, description, head };

	head = newNode;
}

/*
 * @brief Function for inserting data on given position in a linked list
*/

void insertPos(Node** head, int pos, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description)
{
	while (pos--) {
		if (pos == 0) {

			Node* temp = new Node{ title, year, grayYear, participants, era, location, reason, result, description, NULL };

			temp->next = *head;

			*head = temp;
		}
		else {
			head = &(*head)->next;
		}
	}

}

/*
 * @brief Function for edit data on a position in a linked list
*/

void editNode(Node** head, int pos, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description) {

	Node* temp = *head;

	while (pos--) {
		if (pos == 0) {
			temp->title = title;
			temp->year = year;
			temp->grayYear = codeOfGrey(year);
			temp->participants = participants;
			temp->era = era;
			temp->location = location;
			temp->reason = reason;
			temp->result = result;
			temp->description = description;
		}
		temp = temp->next;
	}
}

/*
 * @brief Functions for order data on given position in a linked list
 * @param Getting a linked list
 * @param Take the last two elements and compare which one is bigger
 * @param Sort by size from bottom to top
*/

void mergeSort(Node** headRef, int choice)
{
	Node* head = *headRef;
	Node* a;
	Node* b;

	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	frontBackSplit(head, &a, &b);

	mergeSort(&a, choice);
	mergeSort(&b, choice);
	*headRef = sortedMerge(a, b, choice);
}

Node* sortedMerge(Node* a, Node* b, int choice)
{
	Node* result = NULL;
	string str1;
	string str2;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	if (choice == 1) {
		str1 = a->title;
		str2 = b->title;
	}

	if (choice == 3) {
		str1 = a->participants;
		str2 = b->participants;
	}

	if (choice == 4) {
		str1 = a->era;
		str2 = b->era;
	}

	if (choice == 5) {
		str1 = a->location;
		str2 = b->location;
	}

	switch (choice) {
	case 1:
	case 3:
	case 4:
	case 5:
		if (str1 <= str2) {
			result = a;
			result->next = sortedMerge(a->next, b, choice);
		}
		else {
			result = b;
			result->next = sortedMerge(a, b->next, choice);
		}
		return (result);
		break;
	case 2:
		if (a->year <= b->year) {
			result = a;
			result->next = sortedMerge(a->next, b, choice);
		}
		else {
			result = b;
			result->next = sortedMerge(a, b->next, choice);
		}
		return (result);
		break;
	}

}


void frontBackSplit(Node* source, Node** frontRef, Node** backRef)
{
	Node* fast;
	Node* slow;
	slow = source;
	fast = source->next;
	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

/*
 * @brief Functions for copy a linked list
*/

Node* clone(Node* list) {
	if (list == NULL) return NULL;

	Node* result = new Node;
	result->title = list->title;
	result->year = list->year;
	result->next = clone(list->next);
	return result;
}

/*
 * @brief Function for searching in a linked list
 * @param Searching by choice
 * @param Search for whether the word contains a letters
*/

void searchFuct(Node* node, string str, int whoCanSee[100], int* whoCanSeeSize) {

	int events = 0;
	bool haveIt = false;
	string newStr = "";

	Node* temp = clone(node);

	while (temp) {

		newStr = temp->title + to_string(temp->year);
		for (size_t j = 0; j < newStr.size(); j++) {
			for (size_t i = 0; i < str.size(); i++) {
				if (str[i] == newStr[j]) {
					haveIt = true;
				}
			}
		}

		if (!haveIt) {
			++(*whoCanSeeSize);
			whoCanSee[(*whoCanSeeSize)] = events;
		}

		haveIt = false;
		++events;

		temp = temp->next;
	}
	++(*whoCanSeeSize);
}

/*
 * @brief Functions for remove data on given position in a linked list
*/

void deleteNode(Node** head, int pos)
{
	if (*head == NULL)
		return;

	Node* temp = *head;
	if (pos == 0) {

		*head = temp->next;

		free(temp);
		return;
	}

	for (int i = 0; temp != NULL && i < pos - 1; i++)
		temp = temp->next;

	if (temp == NULL || temp->next == NULL)
		return;

	Node* next = temp->next->next;

	free(temp->next); // Free memory

	temp->next = next;
}

void deleteAllNode(Node** head, int pos)
{
	Node* temp = *head;
	Node* prev = NULL;
	while (pos--) {
		if (pos == 0) {
			if (temp != NULL)
			{
				*head = temp->next;
				delete temp;
				return;
			}

			else
			{
				while (temp != NULL)
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
	}
}

void deleteAllNodes(Node** head)
{
	while (*head != NULL) {
		deleteAllNode(head, 1);
	}
}

/*
 * @brief Functions for save data in txt file
 * @param Function for auto save data
*/

void saveNodes(Node** head) {
	Node* temp = *head;
	ofstream data("SaveNodes.txt");
	while (temp) {
		data << temp->title << "\n";
		data << temp->year << "\n";
		data << temp->grayYear << "\n";
		data << temp->participants << "\n";
		data << temp->era << "\n";
		data << temp->location << "\n";
		data << temp->reason << "\n";
		data << temp->result << "\n";
		data << temp->description << "\n";
		temp = temp->next;
	}
	data.close();
}

void writeFromFile(string autoSave) {
	ofstream data("AutoSaveNodes.txt");
	data << autoSave;
}

void autoSaveNodes(Node** head, string autoSave) {
	writeFromFile(autoSave);

	fstream data;
	data.open("AutoSaveNodes.txt", ios::in);
	if (data.is_open()) {
		string tp;
		while (getline(data, tp)) {
			if (tp == "yes") {
				saveNodes(head);
			}
		}
	}

	data.close();
}

void savedNodes(Node** head) {

	fstream newfile;
	int counter = 0;

	string title;
	int year = 0;
	int grayYear = 0;
	string participants;
	string era;
	string location;
	string reason;
	string result;
	string description;

	newfile.open("SaveNodes.txt", ios::in);
	if (newfile.is_open()) {
		string tp;
		while (getline(newfile, tp)) {
			counter++;
			if (counter == 1) {
				title = tp;
			}

			if (counter == 2) {
				stringstream geek(tp);
				geek >> year;
			}

			if (counter == 3) {
				stringstream geek(tp);
				geek >> grayYear;
			}

			if (counter == 4) {
				participants = tp;
			}

			if (counter == 5) {
				era = tp;
			}

			if (counter == 6) {
				location = tp;
			}

			if (counter == 7) {
				reason = tp;
			}

			if (counter == 8) {
				result = tp;
			}

			if (counter == 9) {
				description = tp;
				newAfterNode(*head, title, year, grayYear, participants, era, location, reason, result, description);
				counter = 0;
			}
		}
		newfile.close();
	}

}

/*
 * @brief Functions for conversion year in gray code
*/

int codeOfGrey(int num)
{
	string binary;
	int i = 0;
	int tempNum;
	while (num > 0) {
		tempNum = num % 2;
		binary += to_string(tempNum);
		num = num / 2;
		i++;
	}

	int binaryNum;
	stringstream geek(binary);
	geek >> binaryNum;

	int a, b, gray = 0;
	i = 0;

	while (binaryNum != 0)
	{
		a = binaryNum % 10;
		binaryNum = binaryNum / 10;
		b = binaryNum % 10;

		if ((a && !b) || (!a && b))
			gray = gray + pow(10, i);
		i++;
	}

	int decValue = 0;
	int base = 1;
	int temp = gray;
	while (temp) {
		int lastDigit = temp % 10;
		temp = temp / 10;

		decValue += lastDigit * base;

		base = base * 2;
	}

	return decValue;
}

string removeSpecialChar(string backEnd, string frontEnd) {
	for (size_t i = 0; i < backEnd.size(); i++) {
		if ((backEnd[i] >= 'a' && backEnd[i] <= 'z') || (backEnd[i] >= 'A' && backEnd[i] <= 'Z') || (backEnd[i] >= '0' && backEnd[i] <= '9')) {
			frontEnd += backEnd[i];
		}
	}
	return frontEnd;
}

/*
 * @brief Set up linked list and going in other function by choice
*/

void setUpLink(Node*& myEvents, string po, string t, string y, string p, string e, string l, string rea, string res, string d, int choice) {

	string autoSave;

	string title = "";
	title = removeSpecialChar(title, t);
	int year = stoi(y);
	int grayYear = codeOfGrey(year);
	string participants = "";
	participants = removeSpecialChar(participants, p);
	string era = "";
	era = removeSpecialChar(era, e);
	string location = "";
	location = removeSpecialChar(location, l);
	string reason = "";
	reason = removeSpecialChar(reason, rea);
	string result = "";
	result = removeSpecialChar(result, res);
	string description = "";
	description = removeSpecialChar(description, d);
	int pos = 0;
	if (po != "_" && po != "")
		pos = stoi(po);

	switch (choice) {


	case 1:
		newAfterNode(myEvents, title, year, grayYear, participants, era, location, reason, result, description);
		break;

	case 2:
		newBeforeNode(myEvents, title, year, grayYear, participants, era, location, reason, result, description);
		break;
	case 3:
		insertPos(&myEvents, pos, title, year, grayYear, participants, era, location, reason, result, description);
		break;
	case 4:
		editNode(&myEvents, pos, title, year, grayYear, participants, era, location, reason, result, description);
		break;
	case 10:
		deleteAllNodes(&myEvents);
		break;

	}
}
