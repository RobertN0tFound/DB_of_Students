#pragma once
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <codecvt>
#include <locale>
#include "classList.hpp"

class Menu
{
private:
    LinkedList<std::wstring> title;
    LinkedList<std::wstring> options;

    void gotoxy(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

public:
    Menu()
    {
    }

    void clear()
    {
        title.clear();
        options.clear();
    }

    void addTitle(std::string _title)
    {
        title.pushBack(converter.from_bytes(_title));
    }

    void addOption(std::string _option)
    {
        options.pushBack(converter.from_bytes(_option));
    }

    void draw_menu(int current_option)
    {
        system("cls");
        std::wstring line_sim = L"════════════════════════════════════════════════════════════";

        std::wcout << L"╔" << line_sim << L"╗" << std::endl;
        // рисуем заголовок
        for (int i = 0; i < title.getSize(); i++)
        {
            std::wcout << L"║   " << title[i];
            gotoxy(61, 1 + i);
            std::wcout << L"║" << std::endl;
        }
        std::wcout << L"╠" << line_sim << L"╣" << std::endl;

        // рисуем опции в меню
        for (int i = 0; i < options.getSize(); i++)
        {
            std::wcout << L"║";
            if (current_option == i)
                std::wcout << L">> ";
            else
                std::wcout << L"   ";
            std::wcout << options[i];
            gotoxy(61, title.getSize() + i + 2);
            std::wcout << L"║" << std::endl;
        }

        std::wcout << L"╚" << line_sim << L"╝" << std::endl;
    }

    int run()
    {
        int option = 0;
        int key;

        while (true)
        {
            draw_menu(option);

            key = _getch();

            if (key == 224)
            {
                key = _getch();

                switch (key)
                {
                case 72:
                    option--;
                    if (option < 0)
                        option = options.getSize() - 1;
                    break;
                case 80:
                    option++;
                    if (option > options.getSize() - 1)
                        option = 0;
                    break;
                }
            }
            else if (key == 13)
            {
                return option;
            }
        }
    }
};
