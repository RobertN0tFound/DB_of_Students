#include <iostream>
#include "classMenu.hpp"
#include "classDB.hpp"
#include "classStudent.hpp"
#include "classMap.hpp"
#include "classMassive.hpp"
#include "classEncryption.hpp"
#include <windows.h>
#include <string>
#include <locale>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

DB_Students db; // database
Menu menu;      // класс отрисовки меню в терминале

void initConsoleLocale()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
    std::wcout << L"Консоль настроена на UTF-8" << std::endl
            << std::flush;
}

void swap_num(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    initConsoleLocale();

    menu.addTitle("База данных студентов");
    menu.addOption("Просмотр/изменение информации студента");
    menu.addOption("Добавить нового студента в БД");
    menu.addOption("Выполнить вариант задания №82");
    menu.addOption("Загрузить БД студентов");
    menu.addOption("Сохранить БД студентов");
    menu.addOption("Завершить программу");

    while (true)
    {

        int getOption = menu.run();

        // std::cout << "Получен выбор номер: " << getOption << std::endl;
        switch (getOption)
        {
        case 0:
        {
            Student student(&db);
            student.listStudentsRun();
        }
        break;
        case 1:
        {
            Student student(&db);
            student.newStudent();
        }
        break;
        case 2:
        {
            Massive<int> cntSess;
            Massive<int> birthCheck;
            class Menu smenu;
            // Student student(&db);
            Massive<int> sdb;
            std::wstringstream ss;
            std::wstringstream ssB;
            std::wstring lim;
            std::wstring limB;
            int min, max, minB, maxB;
            std::wcout << L"Введите диапазон для дат рождения (например, 1900 2004): ";
            std::getline(std::wcin, limB);
            std::wcin.ignore();
            ssB.str(limB);
            ssB >> minB >> maxB;
            if (minB > maxB)
            {
                swap_num(minB, maxB);
            }
            for (int i = minB; i <= maxB; i++)
            {
                birthCheck.pushBack(i);
            }
            std::wcout << L"Введите промежуток сессий за который нужно посчитать рейтинг (например, 3 9): ";
            std::getline(std::wcin, lim);
            std::wcin.ignore();
            ss.str(lim);
            ss >> min >> max;
            if (min > max)
            {
                swap_num(min, max);
            }
            for (int i = min; i <= max; i++)
            {
                cntSess.pushBack(i);
            }
            db.calculateAllRating(cntSess, birthCheck);
            sdb = db.sortDec();
            smenu.addTitle("Отсортированный список");
            smenu.addOption("Вернуться в предыдущее меню");
            for (int i : sdb)
            {
                int birthY = stol(db.getBirthYear(i));
                int rating = stol(db.getstudentRating(i));
                if (birthY >= minB && birthY <= maxB && rating != 0)
                {
                    std::string tmp;
                    tmp = db.getStudentFIO(i);
                    tmp += " | Рейтинг: "; 
                    tmp += db.getstudentRating(i);
                    smenu.addOption(tmp);
                }
            }
            smenu.run();
            break;
        }
        case 3:
            db.load();
            std::wcout << L"База данных загружена.\nНажмите любую клавише для продолжения...";
            _getch();
            break;
        case 4:
            db.save();
            std::wcout << L"База данных сохранена.\nНажмите любую клавише для продолжения...";
            _getch();
            break;
        default:
            class fileEnc fe;
            fe.Crypt();
            return 0;
        }
    }
}