#include <iostream>
#include "classMenu.hpp"
#include "classDB.hpp"
#include "classStudent.hpp"
#include "classMap.hpp"
#include "classMassive.hpp"
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

int main()
{
    initConsoleLocale();

    menu.addTitle("База данных студентов");
    menu.addOption("Просмотр/измение информации студента");
    menu.addOption("Добавить нового студента в БД");
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
            db.load();
            std::wcout << L"База данных загружена.\nНажмите любую клавише для продолжения...";
            _getch();
            break;
        case 3:
            db.save();
            std::wcout << L"База данных сохранена.\nНажмите любую клавише для продолжения...";
            _getch();
            break;
        default:
            return 0;
        }
    }
}