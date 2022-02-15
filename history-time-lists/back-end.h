// Made by Stas Uzunov

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

// Functions

// in Create tab
void newAfterNode(Node*& head, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description);
void newBeforeNode(Node*& head, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description);
void insertPos(Node** head, int pos, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description);
void editNode(Node** head, int pos, string title, int year, int grayYear, string participants, string era, string location, string reason, string result, string description);
void deleteNode(Node** head, int pos);
void deleteAllNodes(Node** head);
void saveNodes(Node** head);
void writeFromFile(string autoSave);
void autoSaveNodes(Node** head, string autoSave);
void savedNodes(Node** head);
string removeSpecialChar(string backEnd, string frontEnd);
int codeOfGrey(int num);

// in Events
void mergeSort(Node** headRef, int choice);
Node* sortedMerge(Node* a, Node* b, int choice);
void frontBackSplit(Node* source, Node** frontRef, Node** backRef);
Node* clone(Node* list);
void searchFuct(Node* node, string str, int whoCanSee[100], int* whoCanSeeSize);


void setUpLink(Node*& myEvents, string pos, string title, string year, string participants, string era, string locationn, string reason, string result, string description, int choice);
