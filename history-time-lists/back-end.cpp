
#include "back-end.h"
#include "front-end.h"

/*
 * @brief Functions for checking that the given values are reliable
 * @param Whether the position is correct
 * @param Тhe number is true
 * @param String if there is anything in it
*/

/*bool isRealPosition(int* pos, int* counter) {
    if (*pos > *counter || *pos <= 0) {
        return false;
    }
    else {
        return true;
    }
}

bool isNumber(string num) {
    for (size_t i = 0; i < num.size(); i++) {
        if (num[i]<48||num[i]>57)
            return false;
    }
    return true;
}

bool checkEmptyString(string s)
{
    return s.size() == 0;
}*/

/*
 * @brief Function for inserting data as the last item in a linked list
*/

/*void newAfterNode(Node*& head, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description)
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
}*/

/*
 * @brief Function for inserting data as the first item in a linked list
*/

/*void newBeforeNode(Node*& head, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description)
{
    Node* newNode = new Node{ title, year, grayYear, participants, era, location, reason, result, description, head };

    head = newNode;
}*/

/*
 * @brief Function for inserting data on given position in a linked list
*/

/*void insertPos(Node** head, int pos, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description)
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

}*/

/*
 * @brief Function for edit data on a position in a linked list
*/

/*void editNode(Node** head, int pos) {
    Node* temp = *head;


    while (pos--) {
        if (pos == 0) {
            switch (choice) {
            case 1:
                temp->title = title;
                break;
            case 2:
                temp->grayYear = codeOfGrey(year);
                temp->year = year;
                break;
            case 3:
                temp->participants = participants;
                break;
            case 4:
                temp->era = era;
                break;
            case 5:
                temp->location = location;
                break;
            case 6:
                temp->reason = reason;
                break;
            case 7:
                temp->result = result;
                break;
            case 8:
                temp->description = description;
                break;
            }

        }
        temp = temp->next;
    }

    return;
}*/

/*
 * @brief Functions for order data on given position in a linked list
 * @param Getting a linked list
 * @param Take the last two elements and compare which one is bigger
 * @param Sort by size from bottom to top
*/
/*
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
*/

/*void frontBackSplit(Node* source, Node** frontRef, Node** backRef)
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
}*/

/*
 * @brief Functions for copy a linked list
*/

/*Node* clone(Node* list) {
    if (list == NULL) return NULL;

    Node* result = new Node;
    result->title = list->title;
    result->year = list->year;
    result->next = clone(list->next);
    return result;
}*/

/*
 * @brief Function for sorted years from beginning to end in a linked list
*/

/*void sortedFromToYears(Node* head) {

    Node* temp = clone(head);

    mergeSort(&temp, 2);

    int id = 0;
    while (temp)
    {
        temp = temp->next;
    }
}*/

/*
 * @brief Function for searching in a linked list
 * @param Searching by choice
 * @param Search for whether the word contains a letters
*/

/*void search(Node* node) {

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
        //cout << "\nSearch: ";
        //isStringEmpty(&str);

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


            temp = temp->next;
            searchIsOk = false;
        }
        cout << endl;

        break;
    case 2:
        //cout << "\nSearch year: ";
        cin >> num;

        tempNum = num;

        while (tempNum > 0 || tempNum != 0) {
            tempArr[tempCounter] = tempNum % 10;
            tempNum /= 10;
            tempCounter++;
        }

        while (temp)
        {
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
                /*cout << endl;
                cout << id << ".\n";
                cout << "Title: " << temp->title << "\n";
                cout << "Year: " << temp->year << "\n";
                cout << "Gray year: " << temp->grayYear << "\n";
                cout << "Participants: " << temp->participants << "\n";
                cout << "Era: " << temp->era << "\n";
                cout << "Location: " << temp->location << "\n";
                cout << "Reason: " << temp->reason << "\n";
                cout << "Result: " << temp->result << "\n";
                cout << "Description: " << temp->description << "\n";*/
                /* }
                 temp = temp->next;
                 searchIsOk = false;
             }
             break;
         }

     }*/

     /*
      * @brief Functions for remove data on given position in a linked list
     */

     /*void deleteNode(Node** head, int pos)
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
     }*/

     /*void deleteAllNodes(Node** head)
     {
         while (*head != NULL) {
             deleteNode(head, 1);
         }
     }*/

     /*
      * @brief Functions for save data in txt file
      * @param Function for auto save data
     */

     /*void saveNodes(Node** head) {
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
     }*/

     /*void writeFromFile(string autoSave) {
         ofstream data("AutoSaveNodes.txt");
         data << autoSave;
     }*/

     /*void autoSaveNodes(Node** head, string autoSave) {
         writeFromFile(autoSave);

         fstream data;
         data.open("AutoSaveNodes.txt", ios::in);
         if (data.is_open()) {

             if (tp == "yes") {
                 saveNodes(head);
             }
         }

         data.close();
     }*/

     /*void savedNodes(Node** head) {

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

     }*/

     /*
      * @brief Functions for conversion year in gray code
     */

     /*int codeOfGrey(int num)
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

         int dec_value = 0;
         int base = 1;
         int temp = gray;
         while (temp) {
             int last_digit = temp % 10;
             temp = temp / 10;

             dec_value += last_digit * base;

             base = base * 2;
         }

         return dec_value;
     }*/

     /*
      * @brief Set up linked list and going in other function by choice
     */

void setUpLink(Node*& myEvents) {
    string autoSave;

    /*savedNodes(&myEvents);

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
        //string title;
        //int year = 0;
        //int grayYear = 0;
        //string description;
        //string participants;
        //string era;
        //string location;
        //string reason;
        //string result;

        //int choice = 0;
        //int pos = itemCount;
        //int tempPos = 5;

        /*if (myEvents == NULL) {
            printf("List is empty.\n");
        }
        else {
            printf("The list has %d items.\n", itemCount);
        }*/
        //cout << "Do you want create after event - 1\n";
        //cout << "Do you want create before event - 2\n";
        //cout << "Do you want create position event - 3\n";
        //cout << "Do you want see events - 4\n";
        //cout << "Do you want edit event - 5\n";
        //cout << "Do you want search events - 6\n";
        //cout << "Do you want order events - 7\n";
        //cout << "Do you want order year from-to - 8\n";
        //cout << "Do you want delete event - 9\n";
        //cout << "Do you want delete all events - 10\n";
        //cout << "Do you want save all events - 11\n";
        //cout << "Do you want auto save all events - 12\n";
        //cout << "Gray code - 13\n";
        //cout << "Select number: ";

         //isNumber(&choice);


        /*witch (choice) {
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
             //print(myEvents);
             //cout << "\nPick position: ";
             //isNumber(&pos);
             //isRealPosition(&pos, &itemCount);
             itemCount++;
             inputData(&title, &year, &grayYear, &participants, &era, &location, &reason, &result, &description);
             insertPos(&myEvents, pos, title, year, grayYear, participants, era, location, reason, result, description);
             break;
         /*case 4:
             print(myEvents);
             break;*/
             /*case 5:
                 editNode(&myEvents, pos);
                 break;
             case 6:
                 search(myEvents);
                 break;
             case 7:
                 //cout << "\nTitle - 1\n";
                 //cout << "Year - 2\n";
                 //cout << "Participants - 3\n";
                 //cout << "Era - 4\n";
                 //cout << "Location - 5\n";
                 //cout << "What do you want to filter: ";
                 //cin >> choice;
                 //isRealPosition(&choice, &tempPos);

                 mergeSort(&myEvents, choice);
                 break;
             case 8:
                 sortedFromToYears(myEvents);
                 break;
             case 9:
                 //print(myEvents);
                 //cout << "\nPick position: ";
                 //isNumber(&pos);
                 //isRealPosition(&pos, &itemCount);
                 itemCount--;
                 deleteNode(&myEvents, pos);
                 break;
             case 10:
                 deleteAllNodes(&myEvents);
                 break;
             case 11:
                 saveNodes(&myEvents);
                 break;
             case 12:
                 //cout << "Do you want auto save? (yes/no): ";
                 //cin.ignore();
                 //getline(cin, autoSave, '\n');
                 autoSaveNodes(&myEvents, autoSave);
                 break;
             /*case 13:
                 cout << "Code on gray: ";
                 cin >> pos;
                 cout << "Code: " << codeOfGrey(pos) << endl;*/
                 /*}
             }*/
}
