
#pragma once

// Libraries
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

// Structure
struct Node {
    string title;
    int year;
    int grayYear;
    string participants;
    string era;
    string location;
    string reason;
    string result;
    string description;

    Node* next;
};

<<<<<<< HEAD
// Functions
/*
bool isRealPosition(int* pos, int* counter);
bool isNumber(int* num);
bool checkEmptyString(const string& s); 
bool isStringEmpty(string* str);
void inputData(string* title, int* year, int* grayYear, string* participants, string* era, string* location, string* reason, string* result, string* description);
=======

void clear();

// Functions
void isRealPosition(int* pos, int* counter);
void isNumber(int* num);
bool checkEmptyString(const string& s);
void isStringEmpty(string* str);
void inputData(string* title, int* year, int *grayYear, string *participants, string *era, string *location, string *reason, string *result,string *description);
>>>>>>> 660670891a0c87d6563f3d452d2879da084888a5
void print(Node* node);

// in tab
void newAfterNode(Node*& head, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description);
void newBeforeNode(Node*& head, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description);
void insertPos(Node** head, int pos, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description);
void editNode(Node** head, int pos);

// in events
void mergeSort(Node** headRef, int choice);
Node* sortedMerge(Node* a, Node* b, int choice);
void frontBackSplit(Node* source, Node** frontRef, Node** backRef);
Node* clone(Node* list);
void sortedFromToYears(Node* head);
void search(Node* node);

// in tab
void deleteNode(Node** head, int pos);
void deleteAllNodes(Node** head, int* itemCount);
void saveNodes(Node** head);
void writeFromFile(string autoSave);
void autoSaveNodes(Node** head, string autoSave);
void savedNodes(Node** head, int* itemCount);

int codeOfGrey(int num);
*/
void setUpLink(Node*& myEvents);
