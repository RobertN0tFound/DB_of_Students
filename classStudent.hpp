﻿#include "classMenu.hpp"
#include "classDB.hpp"
#include "classStudentChange.hpp"
#include "classMassive.hpp"
#include "classMap.hpp"

class Student
{
private:
    DB_Students *db;

    bool isDigit(const std::wstring& str)
    {
        for (const auto& c : str)
        {
            if (!std::isdigit(c))
                return false;
        }
        return true;
    }

    bool isAlpha(std::wstring const &str)
    {
        for (const auto& c : str)
        {
            if (!iswalpha(c))
                return false;
        }
        return true;
    }

    bool checkSex(std::wstring const &str)
    {
        if (str.empty())
            return false;
        for (const auto& c : str)
        {
            if (!iswalpha(c) || str.length() != 1 || (c != L'М' && c != L'Ж'))
                return false;
        }
        return true;
    }

public:
    Student(DB_Students *_db)
    {
        db = _db;
    };

    void listStudentsRun()
    {
        Menu menu;
        int opt;
        Massive<IntStr> listOfStudents;
        Massive<IntInt> listMenu;
        int count;

        while (true)
        {
            count = 1;
            menu.clear();
            listOfStudents = db->getstudentListFIO();
            if (listOfStudents.size() == 0)
            {
                std::cout << "База студентов пустая. Выполните загрузку или введите нового студента." << std::endl;
                std::cout << "Нажмите любую клавишу для продолжения...";
                _getch();
                return;
            }

            menu.addTitle("Список студентов");
            menu.addOption("Вернуться в предыдущее меню");
            listMenu.pushBack({0, 0}); // для коррекции возврата выбранного пункта

            for (auto element : listOfStudents)
            {
                menu.addOption(element.second);
                listMenu.pushBack({count, element.first});
                count++;
            }

            opt = menu.run();
            if (opt == 0)
                return;
            {
                StudentChange student(db, listMenu[opt].first);
                student.run();
            }
        }
    }

    void newStudent()
    {
        std::wstring name;
        std::wstring surName;
        std::wstring middleName;
        std::wstring birthDate;
        std::wstring sex;
        std::wstring startYear;
        std::wstring departament;
        std::wstring facultet;
        std::wstring group;
        std::wstring numDoc;

        system("cls");
        std::wcout << L"Ввод данных нового студента:" << std::endl;

        while (true) 
        {
            std::wcout << L"Фамилия: ";
            std::getline(std::wcin, surName);
            std::wcin.ignore();
            if (!isAlpha(surName))
            {
                std::wcout << L"Некорректная фамилия. Фамилия должна состоять только из букв!" << std::endl;
            }
            else
                break;
        }

        while (true)
        {
            std::wcout << L"Имя: ";
            std::getline(std::wcin, name);
            std::wcin.ignore();
            if (!isAlpha(name))
            {
                std::wcout << L"Некорректное имя. Имя должно состоять только из букв!" << std::endl;
            }
            else
                break;
        }

        while (true)
        {
            std::wcout << L"Отчество: ";
            std::getline(std::wcin, middleName);
            std::wcin.ignore();
            if (!isAlpha(middleName))
            {
                std::wcout << L"Некорректное отчество. Отчество должно состоять только из букв!" << std::endl;
            }
            else
                break;
        }

        while (true)
        {
            std::wcout << L"Дата рождения: ";
            std::getline(std::wcin, birthDate);
            std::wcin.ignore();
            if (!isDigit(birthDate))
            {
                std::wcout << L"Некорректная дата рождения. Дата рождения должна состоять только из цифр!" << std::endl;
            }
            else
                break;
        }

        while (true)
        {
            std::wcout << L"Пол: ";
            std::getline(std::wcin, sex);
            std::wcin.ignore();
            if (!checkSex(sex))
            {
                std::wcout << L"Некорректный пол. Пол может быть 'М' или 'Ж'!" << std::endl;
            }
            else
                break;
        }

        std::wcout << L"Поступил: ";
        std::getline(std::wcin, startYear);
        std::wcin.ignore();

        std::wcout << L"Отделение: ";
        std::getline(std::wcin, departament);
        std::wcin.ignore();

        std::wcout << L"Факультет: ";
        std::getline(std::wcin, facultet);
        std::wcin.ignore();

        std::wcout << L"Группа: ";
        std::getline(std::wcin, group);
        std::wcin.ignore();

        std::wcout << L"Номер зачетки: ";
        std::getline(std::wcin, numDoc);
        std::wcin.ignore();

        if (db->addStudent(converter.to_bytes(name),
                        converter.to_bytes(middleName),
                        converter.to_bytes(surName),
                        converter.to_bytes(birthDate),
                        converter.to_bytes(sex),
                        converter.to_bytes(startYear),
                        converter.to_bytes(departament),
                        converter.to_bytes(facultet),
                        converter.to_bytes(group),
                        converter.to_bytes(numDoc)) >= 0)
        {
            std::wcout << L"Успешно добавлен.\n Нажмите любую клавишу для продолжения...";
            _getch();
        }
        else
        {
            std::wcout << L"Нажмите любую клавишу для продолжения...";
            _getch();
        }
    }
};