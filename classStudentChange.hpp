#include "classMassive.hpp"
#include "classMenu.hpp"
#include "classDB.hpp"
#include "classMap.hpp"
#include <locale>
#include <codecvt>

// std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

class StudentChange
{
private:
    Massive<std::string> title;
    Massive<std::string> options;
    int studentId;
    DB_Students *db;

public:
    StudentChange(DB_Students *_db, int _studentId)
    {
        db = _db;
        studentId = _studentId;
        title.pushBack("Выберите действие со студентом:");
        title.pushBack(db->getStudentFIO(studentId));
        options.pushBack("Вернуться в предыдущее меню");
        options.pushBack("Изменить данные студента");
        options.pushBack("Сессии");
        {
            std::string tmp = "Удаление студента ";
            tmp += db->getStudentFIO(studentId);
            options.pushBack(tmp);
        }
    };

    int run()
    {
        int opt;

        Menu *menu = new Menu();

        for (int i = 0; i < title.size(); i++)
        {
            menu->addTitle(title[i]);
        }

        for (int i = 0; i < options.size(); i++)
        {
            menu->addOption(options[i]);
        }

        while (true)
        {
            opt = menu->run();
            switch (opt)
            {
            case 0:
                return 0;
            case 1: // Изменить аттрибуты
                setAttribute();
                break;
            case 2: // Сессии
                setAttributeSession();
                break;

            case 3: // Удалить
                if (delStudent())
                {
                    return 0; // так как студента удалили, то более ничего с ним делать не можем
                };
            }
        }
    }

    bool delStudent()
    {
        bool res;
        std::wcout << L"Подтердите операцию удаления студента: "
                << converter.from_bytes(db->getStudentFIO(studentId))
                << L".\n Введите Y(д) - для удаления, либо N(н) для отмены: ";

        std::wstring tmp;
        std::getline(std::wcin, tmp);
        std::wcin.ignore();
        if (tmp != L"Д" && tmp != L"д" && tmp != L"Y" && tmp != L"y")
        {
            std::wcout << L"Отмена операции удаления." << std::endl;
            std::wcout << L"Нажмите клавишу для продолжения." << std::endl;
            _getch(); // Пользователь должне увидеть собщение об ошибке и подтвердить нажатимем клавиши
            return false;
        }

        res = db->deleteStudent(studentId);
        if (res)
        {
            std::wcout << L"Студент " << converter.from_bytes(db->getStudentFIO(studentId)) << L" удален!" << std::endl;
            std::wcout << L"Нажмите клавишу для продолжения." << std::endl;
            _getch(); // Пользователь должне увидеть собщение об ошибке и подтвердить нажатимем клавиши
            return true;
        }
        else
        {
            std::wcout << L"Ошибка удаления студента." << std::endl;
            std::wcout << L"Нажмите клавишу для продолжения." << std::endl;
            _getch(); // Пользователь должне увидеть собщение об ошибке и подтвердить нажатимем клавиши
            return false;
        }
    }

    void setAttribute()
    {
        Massive<StrStr> attributes;
        Massive<std::string> attr;
        Menu menu;

        int opt;

        std::string order[] = {"Фамилия", "Имя", "Отчество", "Дата рождения", "Пол", "Поступил", "Отделение", "Факультет", "Группа", "Номер зачетки"};
        while (true)
        {
            menu.clear();
            attr.clear();
            menu.addTitle("Просмотр/изменение атрибутов студента");
            menu.addTitle(db->getStudentFIO(studentId));
            menu.addOption("Возврат в предыдущее меню");
            attr.pushBack("Выход"); // для коррекции массива вывода опций
            Massive<StrStr> elem = db->getStudentAttrList(studentId);
            for (int i = 0; i < elem.size(); i++)
            {
                for (int j = 0; j < elem.size(); j++)
                {
                    if (elem[j].first == order[i])
                    {
                        menu.addOption(elem[j].first + ": " + elem[j].second);
                        attr.pushBack(elem[j].first);
                    }
                }
            }

            opt = menu.run();
            if (opt == 0)
            {
                return;
            }

            if (attr[opt] != "Рейтинг")
            {
                std::wstring val;
                std::wcout << L"  Введите значение для атрибута <" << converter.from_bytes(attr[opt]) << L">: ";
                std::getline(std::wcin, val);
                std::wcin.ignore();
                std::wcout << L"  Введено значение: " << val << std::endl;
                db->setStudentAttr(studentId, attr[opt], converter.to_bytes(val));
                std::wcout << L"  Значение: " << val << L" сохранено." << std::endl;
                std::wcout << L"  Нажмите любую клавишу для продолжения...";
                _getch();
            }
            else
            {
                std::wcout << L"Ошибка. Запрещено изменять <Рейтинг>." << std::endl;
                std::wcout << L"Рассчетная величина, показана справочно." << std::endl;
                std::wcout << L"Нажмите любую клавишу для продолжения...";
                _getch();
            }
        }
    }
    // изменить аттрибуты сессии
    void setAttributeSession()
    {
        Massive<int> sessionList;
        std::string session;
        std::string exam;
        std::string mark;

        while (true)
        {
            system("cls");
            sessionList.clear();
            sessionList = db->getSessionList(studentId); // получим все сессии для студента

            std::wcout << L"Просмотр/изменение значений сессиий студента: "
                    << converter.from_bytes(db->getStudentFIO(studentId)) << std::endl;
            for (int i = 0; i < sessionList.size(); i++) // выведем все оценки по сессиям
            {

                std::wcout << L"Сессия: " << converter.from_bytes(std::to_string(sessionList[i])) << std::endl;
                for (auto element : db->getSessionExamList(studentId, sessionList[i]))
                {
                    std::wcout << L"  " << converter.from_bytes(element.first)
                            << L": " << converter.from_bytes(std::to_string(element.second)) << std::endl;
                }
            }
            std::wcout << L"Введите номер сессии или ! для выхода: ";
            {
                std::wstring tmp;
                std::getline(std::wcin, tmp);
                std::wcin.ignore();
                session = converter.to_bytes(tmp);
            }
            if (session == "!")
                return;
            if (!std::all_of(session.begin(), session.end(), ::isdigit)) // проверим на число
            {
                std::wcout << L"Ошибка. Ожидалось число или !" << std::endl;
                continue;
            }
            if (std::find(std::begin(sessionList), std::end(sessionList), stol(session)) == std::end(sessionList))
            {
                std::wstring tmp;
                while (true)
                {
                    std::wcout << L"Введенной сессии нет, создать (д/н): ";
                    std::getline(std::wcin, tmp);
                    std::wcin.ignore();
                    if (tmp == L"Д" || tmp == L"д")
                        break;
                    if (tmp == L"Н" || tmp == L"н")
                        break;
                    std::wcout << L"Ошибка. только Д или Н" << std::endl;
                }
                if (tmp == L"Н" || tmp == L"н")
                    continue;
            }
            std::wcout << L"Введите предмет: ";
            {
                std::wstring tmp;
                std::getline(std::wcin, tmp);
                std::wcin.ignore();
                exam = converter.to_bytes(tmp);
            }
            while (true)
            {
                std::wcout << L"Введите оценку (0-незачет, 1-зачет, 2..5): ";
                {
                    std::wstring tmp;
                    std::getline(std::wcin, tmp);
                    std::wcin.ignore();
                    mark = converter.to_bytes(tmp);
                }
                if (!std::all_of(mark.begin(), mark.end(), ::isdigit)) // проверим на число
                {
                    std::wcout << L"Ошибка. Ожидалось число." << std::endl;
                    continue;
                }
                if (stol(mark) > 5 || stol(mark) < 0)
                {
                    std::wcout << L"Ошибка. Число в дипазоне 0..5" << std::endl;
                    continue;
                }
                break;
            }
            db->setExamResult(studentId, stol(session), exam, stol(mark));
        }
    }
};
