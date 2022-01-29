#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <windows.h>
#include <vector>

using namespace std;

struct Node;
void inputData(string* title, int* year);
void print(Node* node);
void newAfterNode(Node*& head, string title, int year);
void newBeforeNode(Node*& head, string title, int year);
void insertPos(Node** head, int pos, string title, int year);
void editNode(Node** head, int pos);
void mergeSort(Node** headRef, int choice);
Node* sortedMerge(Node* a, Node* b, int choice);
void frontBackSplit(Node* source, Node** frontRef, Node** backRef);
void search(Node* node, int choice);
void deleteNode(Node** head, int pos);
void deleteAllNodes(Node** head);
void saveNodes(Node** head);
void autoSaveNodes(Node** head, string autoSave);

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

void editNode(Node** head, int pos) {
    Node* temp = *head;

    string title;
    int year;

    while (pos--) {
        if (pos == 0) {
            cout << "\nTitle - 1\n";
            cout << "Year - 2\n";
            cout << "What do you want to edit: ";
            int choice;
            cin >> choice;
            switch (choice) {
            case 1:
                cout << "Edit title: ";
                cin.ignore();
                getline(cin, title, '\n');
                temp->title = title;
                break;
            case 2:
                cout << "Edit year: ";
                cin >> year;
                temp->year = year;
                break;
            }
        }
        temp = temp->next;
    }

    return;
}

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

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    string str1 = a->title;
    string str2 = b->title;

    switch (choice) {
    case 1:
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

void search(Node* node, int choice) {

    string str;
    int num;


    Node* temp = node;

    string newTitle;
    int nTitle;
    bool searchIsOk = false;
    int id = 0;
    int n = 0;
    int mayBeCan = 0;

    int oldNum, oldCounter, oldArr[10];
    int tempNum, tempCounter = 0, tempArr[10];

    switch (choice) {
    case 1:
        cout << "\nWrite title: ";
        cin.ignore();
        getline(cin, str, '\n');

        while (temp)
        {
            ++id;
            n = str.length();
            newTitle = temp->title;
            nTitle = newTitle.length();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < nTitle; j++) {
                    if (str[i] + 32 == newTitle[j] || str[i] - 32 == newTitle[j] || str[i] == newTitle[j]) {
                        searchIsOk = true;
                    }
                    else {
                        ++mayBeCan;
                        if (mayBeCan == nTitle) {
                            searchIsOk = false;
                        }
                    }
                }
                mayBeCan = 0;
            }

            if (searchIsOk) {
                cout << endl;
                cout << id << ". ";
                cout << temp->title << "-";
                cout << temp->year << " ";
                cout << endl;
            }
            temp = temp->next;
            searchIsOk = false;
        }
        cout << endl;

        break;
    case 2:
        cout << "\nWrite year: ";
        cin >> num;

        tempNum = num;

        while (tempNum > 0 || tempNum != 0) {
            tempArr[tempCounter] = tempNum % 10;
            tempNum /= 10;
            tempCounter++;
        }

        while (temp)
        {
            ++id;
            oldNum = temp->year;
            oldCounter = 0;

            while (oldNum > 0 || oldNum != 0) {
                oldArr[oldCounter] = oldNum % 10;
                oldNum /= 10;
                oldCounter++;
            }

            for (int i = 0; i < tempCounter; i++) {
                for (int j = 0; j < oldCounter; j++) {
                    if (tempArr[i] == oldArr[j]) {
                        searchIsOk = true;
                    }
                    else {
                        ++mayBeCan;
                        if (mayBeCan == oldCounter) {
                            searchIsOk = false;
                        }
                    }
                }
                mayBeCan = 0;
            }

            if (searchIsOk) {
                cout << endl;
                cout << id << ". ";
                cout << temp->title << "-";
                cout << temp->year << " ";
                cout << endl;
            }
            temp = temp->next;
            searchIsOk = false;
        }

        cout << endl;
        break;
    }

}

void deleteNode(Node** head, int pos)
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
        deleteNode(head, 1);
    }
}

void saveNodes(Node** head) {
    Node* temp = *head;
    ofstream data("SaveNodes.txt");
    while (temp) {
        data << temp->title << "\n";
        data << temp->year << " ";
        data << endl;
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

void savedNodes(Node** head, int* itemCount) {

    fstream newfile;
    int counter = 0;
    string title;
    int year;

    newfile.open("SaveNodes.txt", ios::in);
    if (newfile.is_open()) {
        string tp;
        while (getline(newfile, tp)) {
            counter++;
            if (counter == 1) {
                title = tp;
            }

            if (counter == 2) {
                year = stoi(tp);
                ++* itemCount;
                newAfterNode(*head, title, year);
                counter = 0;
            }
        }
        newfile.close();
    }

}

int codeOfGrey(int num) {
    int n = 0;
    for (; g; g >>= 1)
        n ^= g;
    return n;
}

int main()
{
    Node* myEvents = NULL;
    int itemCount = 0;
    string autoSave;

    savedNodes(&myEvents, &itemCount);

    while (true) {

        fstream data;
        data.open("AutoSaveNodes.txt", ios::in);
        if (data.is_open()) {
            string tp;
            while (getline(data, tp)) {
                autoSave = tp;
            }
        }

        data.close();

        autoSaveNodes(&myEvents, autoSave);
        string title;
        int year;

        int choice;
        int pos;

        if (myEvents == NULL) {
            printf("List is empty.\n");
        }
        else {
            printf("The list has %d items.\n", itemCount);
        }

        cout << "Do you want create after event - 1\n";
        cout << "Do you want create before event - 2\n";
        cout << "Do you want create position event - 3\n";
        cout << "Do you want see events - 4\n";
        cout << "Do you want edit event - 5\n";
        cout << "Do you want search events - 6\n";
        cout << "Do you want order events - 7\n";
        cout << "Do you want delete event - 8\n";
        cout << "Do you want delete all events - 9\n";
        cout << "Do you want save all events - 10\n";
        cout << "Do you want auto save all events - 11\n";
        cout << "Select number: ";
        cin >> choice;

        switch (choice) {
        case 1:
            itemCount++;
            inputData(&title, &year);
            newAfterNode(myEvents, title, year);
            break;
        case 2:
            itemCount++;
            inputData(&title, &year);
            newBeforeNode(myEvents, title, year);
            break;
        case 3:
            itemCount++;
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
            editNode(&myEvents, pos);
            break;
        case 6:
            cout << "\nTitle - 1\n";
            cout << "Year - 2\n";
            cout << "What do you want to filter: ";
            cin >> choice;
            search(myEvents, choice);
            break;
        case 7:
            cout << "\nTitle - 1\n";
            cout << "Year - 2\n";
            cout << "What do you want to filter: ";
            cin >> choice;
            mergeSort(&myEvents, choice);
            break;
        case 8:
            itemCount--;
            print(myEvents);
            cout << "\nPick position: ";
            cin >> pos;
            deleteNode(&myEvents, pos);
            break;
        case 9:
            deleteAllNodes(&myEvents);
            break;
        case 10:
            saveNodes(&myEvents);
            break;
        case 11:
            cout << "Do you want auto save? (yes/no): ";
            cin.ignore();
            getline(cin, autoSave, '\n');

            autoSaveNodes(&myEvents, autoSave);
            break;
        case 12:
            cout << "Code on gray: ";
            cin >> pos;
            cout << "Code: " << codeOfGrey(pos) << endl;
        }

        string ready;
        cout << "Ready? - ";
        cin.ignore();
        getline(cin, ready, '\n');
        clear();

    }
    return 0;
}