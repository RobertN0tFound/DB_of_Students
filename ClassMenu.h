#pragma once
#include "windows.h"
#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdio.h>
using namespace std;

void drawLineUP(int size) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string tmpString = " ";
    for (int i = 0; i < size; i++)
        tmpString += "_";
    SetConsoleTextAttribute(hConsole, 15);
    cout << tmpString << endl;
}

void drawLineDown(int size) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    string tmpString = "|";
    for (int i = 0; i < size - 1; i++)
        tmpString += "_";
    SetConsoleTextAttribute(hConsole, 15);
    tmpString += "|";
    cout << tmpString << endl;
}

class ClassMenu
{
private:
    int itemsCount;
    int titleItemCount;
    int selectedItem;
    string items[300][50];
    string TitelStrings[50][60];

    void draw() {
        Sleep(10);
        system("cls");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        int maxLength = getMaxLength();
        drawLineUP(maxLength + 6);
        for (int i = 0; i < titleItemCount; i++) {
            SetConsoleTextAttribute(hConsole, 15);
            string tmpString = "";
            tmpString = "|   ";
            tmpString = tmpString + TitelStrings[i]->c_str();
            while (tmpString.length() < maxLength + 7)
                tmpString += " ";
            tmpString += "|";
            cout << tmpString << endl;
        }
        drawLineDown(maxLength + 7);
        for (int i = 0; i < itemsCount; i++) {
            if (i == selectedItem) {

                SetConsoleTextAttribute(hConsole, 15);
                cout << "|";
                SetConsoleTextAttribute(hConsole, 13);
                cout << " * " << items[i]->c_str();
                SetConsoleTextAttribute(hConsole, 15);
                string tmpString = "";
                while (tmpString.length() < maxLength - items[i]->length() + 3)
                    tmpString += " ";
                tmpString += "|";
                cout << tmpString << endl;
            }
            else {
                SetConsoleTextAttribute(hConsole, 15);
                string tmpString = "";
                tmpString = "|   ";
                tmpString = tmpString + items[i]->c_str();
                while (tmpString.length() < maxLength + 7)
                    tmpString += " ";
                tmpString += "|";
                cout << tmpString << endl;
            }
        }
        drawLineDown(maxLength + 7);
        //cout << getMaxLength() <<  endl;
    }

    int getMaxLength() {
        int maxLength = 0;
        for (int i = 0; i < 300; i++)
            if (items[i]->length() > maxLength)
                maxLength = items[i]->length();
        for (int i = 0; i < 50; i++)
            if (TitelStrings[i]->length() > maxLength)
                maxLength = TitelStrings[i]->length();
        return maxLength;
    }


public:
    ClassMenu() {
        selectedItem = 0;
        itemsCount = 0;
        titleItemCount = 0;
    }
    int getItemsCount() {
        return itemsCount;
    }
    void eraseTitle() {
        titleItemCount = 0;
    }
    void eraseItem() {
        itemsCount = 0;
    }
    void eraseAll() {
        eraseTitle();
        eraseItem();
    }
    int getSelectedItem() {
        return selectedItem;
    }
    void addItem(string inString) {
        items[itemsCount]->assign(inString.c_str());
        itemsCount++;
    }
    void addTitleItem(string inString) {
        TitelStrings[titleItemCount]->assign(inString.c_str());
        titleItemCount++;
    }
    void setDown() {
        selectedItem++;
        if (selectedItem > itemsCount - 1)
            selectedItem = 0;
    }
    void setUp() {
        selectedItem--;
        if (selectedItem < 0)
            selectedItem = itemsCount - 1;
    }
    //ãäå <A> è <B> — øåñòíàäöàòåðè÷íûå öèôðû — ïåðâàÿ çàäàåò öâåò ôîíà, à âòîðàÿ — öâåò ïåðåäíåãî ïëàíà(öâåò øðèôòà).
    //    Çíà÷åíèÿ öèôð
    //    0 — ÷åðíûé
    //    1 — ñèíèé
    //    2 — çåëåíûé
    //    3 — ãîëóáîé
    //    4 — êðàñíûé
    //    5 — ëèëîâûé
    //    6 — æåëòûé
    //    7 — áåëûé
    //    8 — ñåðûé
    //    9 — ñâåëî - ñèíèé
    //    A — ñâåòëî - çåëåíûé
    //    B — ñâåòëî - ãîëóáîé
    //    Ñ — ñâåòëî - êðàñíûé
    //    E — ñâåòëî - æåëòûé
    //    F — ÿðêî - áåëûé
    //system("Color 15");

    void run() {
        char ch = ' ';
        draw();
        while (ch != 13) {
            Sleep(10);
            ch = _getch();
            //cout << endl << ch <<endl;
            if (ch == 80) {// âíèç
                setDown();
                draw();
            }
            if (ch == 72) {
                setUp();
                draw();
            }
        }
    }
    //friend class ClassEdit;
    friend  void drawLineUP(int size);
    friend  void drawLineDown(int size);
};