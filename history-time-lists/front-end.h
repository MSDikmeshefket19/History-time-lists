
#pragma once

#include <SFML/Graphics.hpp> 
#include <iostream>
#include <sstream>
#include <windows.h>

using namespace std;
using namespace sf;

void backToMenu(int* ptr1, Event event, Text* textOne);

void backToMenuFromCreate(int* ptr1, Event event, Text* textOne, Text* textTwo);

void dropDown(RectangleShape* rectangle, int minY, int maxY);

void currentLocation(int* ptr, int n, Event event, Text* textOne);

void currentLocationDropDown(int* ptr, int n, Event event);

void textPosition(int* location, Event event, Text* text, int n, int minY, int maxY);

void setRectangleEventsTab(RectangleShape* rectangle, int posX, int posY);

void setRectangleDropDown(RectangleShape* rectangle, int posY);

void setMenuText(const string str, Text* text, int minusX, int posY);

void setDropDownMenuText(Text* text, int posY);

void setRectangleCreateMainOne(RectangleShape* rectangle, int plusLeft, int mulRight);

void addFromOrBack(RectangleShape* rectangle, int posY);

void addFromOrBackTwo(RectangleShape* rectangle, int posY);

void textFrontBackOrEditTab(Text* text, int posY);

void drowFrontBackOrEditTab(RectangleShape rectangle1, RectangleShape rectangle2, RectangleShape rectangle3, RectangleShape rectangle4, RectangleShape rectangle5, RectangleShape rectangle6, RectangleShape rectangle7,
	RectangleShape rectangle8, RectangleShape rectangle9, RectangleShape rectangle10, RectangleShape rectangle11, RectangleShape rectangle12, RectangleShape rectangle13, RectangleShape rectangle14, RectangleShape rectangle15, RectangleShape rectangle16);

void setUpMenu();

