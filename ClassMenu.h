#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;
template <typename T>

class ClassMenu
{
private:
    T choice;
public:
    do
    {
        void DrawStart()
        {
            cout << endl;
            cout << "+"; cout.width(50); cout.fill('-'); cout << "+" << endl;
            cout.width(50); cout.fill(' '); cout << left; cout << "|База данных студентов РТУ МИРЭА"; cout << "|" << endl;
            cout << internal; cout << "|"; cout.width(50); cout.fill('-'); cout << "|" << endl; cout.fill(' ');
            cout.width(50); cout << left; cout << "| Отобразить список студентов: '1'" << "|" << endl;
            cout.width(50); cout << left; cout << "| Добавить данные о студенте в БД: '2'" << "|" << endl;
            cout.width(50); cout << left; cout << "| Сохранить БД студентов в файл: '3'" << "|" << endl;
            cout.width(50); cout << left; cout << "| Выполнить вариант задания №82: '4'" << "|" << endl;
            cout.width(50); cout << left; cout << "| Выход: '0'" << "|" << endl;
            cout << internal; cout << "+"; cout.width(50); cout.fill('-'); cout << "+" << endl; cout.fill(' ');
        }
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                cout << endl;
                cout << "+"; cout.width(50); cout.fill('-'); cout << "+" << endl;
                cout.width(50); cout.fill(' '); cout << left; cout << "|База данных студентов РТУ МИРЭА"; cout << "|" << endl;
                cout << internal; cout << "|"; cout.width(50); cout.fill('-'); cout << "|" << endl; cout.fill(' ');

            }
            case 2:
            {

            }
            case 3:
            {

            }
            case 4:
            {

            }
            case 0:
                break;
            default:
                break;
        }

    } while (choice != 0);
};

int main()
{
    // SetConsoleCP(1251);
    // SetConsoleOutputCP(1251);

}
