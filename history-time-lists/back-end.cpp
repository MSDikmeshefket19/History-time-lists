
#include "back-end.h"
//#include "front-end.h"

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

void isRealPosition(int *pos, int *counter) {
    while (true) {
        if (*pos > *counter || *pos <= 0) {
            cout << "Pick real position!\n";
            cout << "\nPick position: ";
            isNumber(pos);
        }
        else {
            break;
        }
    }
}

void isNumber(int* num) {
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {
            cin >> *num;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "\nPLEASE INSERT A VALID OPTION" << endl;
            cout << "Try again: ";
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);
}

bool checkEmptyString(const string& s)
{
    return s.size() == 0;
}

void isStringEmpty(string* str) {
    while (true) {

        getline(cin >> ws, *str, '\n');

        string copyStr = *str;

        if (copyStr[0] == ' ') {
            cout << "You can't place first letter with space";
        }
        else {
            if (checkEmptyString(*str)) {
                cout << "You can't stay string empty\n";
                cout << "Try again: ";
            }
            else {
                break;
            }
        }
    }
}

void inputData(string* title, int* year, int* grayYear, string* participants, string* era, string* location, string* reason, string* result, string* description) {
    cout << endl;

    cout << "Title: ";
    isStringEmpty(&*title);

    cout << "Year: ";
    isNumber(&*year);

    *grayYear = codeOfGrey(*year);

    cout << "Participants: ";
    isStringEmpty(&*participants);

    cout << "Era: ";
    isStringEmpty(&*era);

    cout << "Location: ";
    isStringEmpty(&*location);

    cout << "Reason: ";
    isStringEmpty(&*reason);

    cout << "Result: ";
    isStringEmpty(&*result);

    cout << "Description: ";
    isStringEmpty(&*description);
}

void print(Node* node)
{
    Node* temp = node;
    int id = 0;
    while (temp)
    {
        cout << endl;
        cout << ++id << ".\n";
        cout << "Title: " << temp->title << "\n";
        cout << "Year: " << temp->year << "\n";
        cout << "Gray year: " << temp->grayYear << "\n";
        cout << "Participants: " << temp->participants << "\n";
        cout << "Era: " << temp->era << "\n";
        cout << "Location: " << temp->location << "\n";
        cout << "Reason: " << temp->reason << "\n";
        cout << "Result: " << temp->result << "\n";
        cout << "Description: " << temp->description << "\n";

        temp = temp->next;
    }
    cout << endl;
}

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

void newBeforeNode(Node*& head, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description)
{
    Node* newNode = new Node{ title, year, grayYear, participants, era, location, reason, result, description, head };

    head = newNode;
}

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

void editNode(Node** head, int pos) {

    int tempPos = pos;
    print(*head);
    cout << "\nPick position: ";
    isNumber(&pos);
    isRealPosition(&pos, &tempPos);

    Node* temp = *head;

    string title;
    int year = 0;
    int grayYear = 0;
    string description;
    string participants;
    string era;
    string location;
    string reason;
    string result;

    while (pos--) {
        if (pos == 0) {
            cout << "\nTitle - 1\n";
            cout << "Year - 2\n";
            cout << "Participants - 3\n";
            cout << "Era - 4\n";
            cout << "Location - 5\n";
            cout << "Reason - 6\n";
            cout << "Result - 7\n";
            cout << "Description - 8\n";

            cout << "What do you want to edit: ";
            int choice;
            cin >> choice;

            tempPos = 8;

            isRealPosition(&choice, &tempPos);

            switch (choice) {
            case 1:
                cout << "Edit title: ";
                isStringEmpty(&title);
                temp->title = title;
                break;
            case 2:
                cout << "Edit year: ";
                isNumber(&year);
                temp->grayYear = codeOfGrey(year);
                temp->year = year;
                break;
            case 3:
                cout << "Edit participants: ";
                isStringEmpty(&participants);
                temp->participants = participants;
                break;
            case 4:
                cout << "Edit era: ";
                isStringEmpty(&era);
                temp->era = era;
                break;
            case 5:
                cout << "Edit location: ";
                isStringEmpty(&location);
                temp->location = location;
                break;
            case 6:
                cout << "Edit reason: ";
                isStringEmpty(&reason);
                temp->reason = reason;
                break;
            case 7:
                cout << "Edit result: ";
                isStringEmpty(&result);
                temp->result = result;
                break;
            case 8:
                cout << "Edit description: ";
                isStringEmpty(&description);
                temp->description = description;
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

Node* clone(Node* list) {
    if (list == NULL) return NULL;

    Node* result = new Node;
    result->title = list->title;
    result->year = list->year;
    result->next = clone(list->next);
    return result;
}

void sortedFromToYears(Node* head) {

    int from, to;
    cout << "Choice from : ";
    cin >> from;
    cout << "Choice to : ";
    cin >> to;

    Node* temp = clone(head);

    mergeSort(&temp, 2);

    int id = 0;
    while (temp)
    {
        if (from <= temp->year && to >= temp->year) {
            cout << endl;
            cout << ++id << ".\n";
            cout << "Title: " << temp->title << "\n";
            cout << "Year: " << temp->year << "\n";
            cout << "Gray year: " << temp->grayYear << "\n";
            cout << "Participants: " << temp->participants << "\n";
            cout << "Era: " << temp->era << "\n";
            cout << "Location: " << temp->location << "\n";
            cout << "Reason: " << temp->reason << "\n";
            cout << "Result: " << temp->result << "\n";
            cout << "Description: " << temp->description << "\n";
        }
        temp = temp->next;
    }
    cout << endl;
}

void search(Node* node) {

    int choice;
    cout << "\nTitle - 1\n";
    cout << "Year - 2\n";
    cout << "Participants - 3\n";
    cout << "Era - 4\n";
    cout << "Location - 5\n";
    cout << "What do you want to filter: ";
    cin >> choice;

    int tempPos = 5;

    isRealPosition(&choice, &tempPos);

    string str;
    int num;

    Node* temp = node;

    string newStr;
    size_t nStr;
    bool searchIsOk = false;
    int id = 0;
    size_t n = 0;
    int mayBeCan = 0;

    int oldNum, oldCounter, oldArr[10];
    int tempNum, tempCounter = 0, tempArr[10];

    switch (choice) {
    case 1:
    case 3:
    case 4:
    case 5:
        cout << "\nSearch: ";
        isStringEmpty(&str);

        while (temp)
        {
            ++id;
            n = str.length();
            if (choice == 1)
                newStr = temp->title;
            if (choice == 3)
                newStr = temp->participants;
            if (choice == 4)
                newStr = temp->era;
            if (choice == 5)
                newStr = temp->location;

            nStr = newStr.length();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < nStr; j++) {
                    if (str[i] + 32 == newStr[j] || str[i] - 32 == newStr[j] || str[i] == newStr[j]) {
                        searchIsOk = true;
                    }
                    else {
                        ++mayBeCan;
                        if (mayBeCan == nStr) {
                            searchIsOk = false;
                        }
                    }
                }
                mayBeCan = 0;
            }

            if (searchIsOk) {
                cout << endl;
                cout << id << ".\n";
                cout << "Title: " << temp->title << "\n";
                cout << "Year: " << temp->year << "\n";
                cout << "Gray year: " << temp->grayYear << "\n";
                cout << "Participants: " << temp->participants << "\n";
                cout << "Era: " << temp->era << "\n";
                cout << "Location: " << temp->location << "\n";
                cout << "Reason: " << temp->reason << "\n";
                cout << "Result: " << temp->result << "\n";
                cout << "Description: " << temp->description << "\n";
            }
            temp = temp->next;
            searchIsOk = false;
        }
        cout << endl;

        break;
    case 2:
        cout << "\nSearch year: ";
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
                cout << id << ".\n";
                cout << "Title: " << temp->title << "\n";
                cout << "Year: " << temp->year << "\n";
                cout << "Gray year: " << temp->grayYear << "\n";
                cout << "Participants: " << temp->participants << "\n";
                cout << "Era: " << temp->era << "\n";
                cout << "Location: " << temp->location << "\n";
                cout << "Reason: " << temp->reason << "\n";
                cout << "Result: " << temp->result << "\n";
                cout << "Description: " << temp->description << "\n";
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

void deleteAllNodes(Node** head, int* itemCount)
{
    while (*head != NULL) {
        --* itemCount;
        deleteNode(head, 1);
    }
}

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

void savedNodes(Node** head, int* itemCount) {

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
                ++* itemCount;
                newAfterNode(*head, title, year, grayYear, participants, era, location, reason, result, description);
                counter = 0;
            }
        }
        newfile.close();
    }

}

int codeOfGrey(int num) {
    int n = 0;
    for (; num; num >>= 1)
        n ^= num;
    return n;
}

void setUpLink() {

    // set up linked list
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
        int year = 0;
        int grayYear = 0;
        string description;
        string participants;
        string era;
        string location;
        string reason;
        string result;

        int choice = 0;
        int pos = itemCount;
        int tempPos = 5;

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
        cout << "Do you want order year from-to - 8\n";
        cout << "Do you want delete event - 9\n";
        cout << "Do you want delete all events - 10\n";
        cout << "Do you want save all events - 11\n";
        cout << "Do you want auto save all events - 12\n";
        cout << "Gray code - 13\n";
        cout << "Select number: ";

        isNumber(&choice);


        switch (choice) {
        case 1:
            itemCount++;
            inputData(&title, &year, &grayYear, &participants, &era, &location, &reason, &result, &description);
            newAfterNode(myEvents, title, year, grayYear, participants, era, location, reason, result, description);
            break;
        case 2:
            itemCount++;
            inputData(&title, &year, &grayYear, &participants, &era, &location, &reason, &result, &description);
            newBeforeNode(myEvents, title, year, grayYear, participants, era, location, reason, result, description);
            break;
        case 3:
            print(myEvents);
            cout << "\nPick position: ";
            isNumber(&pos);
            isRealPosition(&pos, &itemCount);
            itemCount++;
            inputData(&title, &year, &grayYear, &participants, &era, &location, &reason, &result, &description);
            insertPos(&myEvents, pos, title, year, grayYear, participants, era, location, reason, result, description);
            break;
        case 4:
            print(myEvents);
            break;
        case 5:
            editNode(&myEvents, pos);
            break;
        case 6:
            search(myEvents);
            break;
        case 7:
            cout << "\nTitle - 1\n";
            cout << "Year - 2\n";
            cout << "Participants - 3\n";
            cout << "Era - 4\n";
            cout << "Location - 5\n";
            cout << "What do you want to filter: ";
            cin >> choice;
            isRealPosition(&choice, &tempPos);

            mergeSort(&myEvents, choice);
            break;
        case 8:
            sortedFromToYears(myEvents);
            break;
        case 9:
            print(myEvents);
            cout << "\nPick position: ";
            isNumber(&pos);
            isRealPosition(&pos, &itemCount);
            itemCount--;
            deleteNode(&myEvents, pos);
            break;
        case 10:
            deleteAllNodes(&myEvents, &itemCount);
            break;
        case 11:
            saveNodes(&myEvents);
            break;
        case 12:
            cout << "Do you want auto save? (yes/no): ";
            cin.ignore();
            getline(cin, autoSave, '\n');
            autoSaveNodes(&myEvents, autoSave);
            break;
        case 13:
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
}
