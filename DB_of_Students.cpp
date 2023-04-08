#include <iostream>
#include "StudentSortClass.h"

using namespace std;

SessionDataClass* sessionData;
StudentClass* student;
StudentSortClass* studentSort;

int main()
{
    StudentClass* temp;
    student = new StudentClass(0, "Куликов", "Дмитрий", "Олегович", "19.07.2004", 2022, "ИКБ", "КБ-1", "БББО-09-22", "22Б0182", 'M');
    student->addStudent(1, "Русаков", "Алексей", "Михайлович", "22.01.1992", 2022, "ИКБ", "КБ-2", "БББО-09-22", "18Б1893", 'M');
    student->addStudent(2, "Попова", "Алина", "Сергеевна", "20.01.2003", 2022, "ИКБ", "КБ-1", "БББО-09-22", "22Б3564", 'F');

    student->addSession();
    student->sessionData[0].addRecord("Физика", 1);
    student->sessionData[0].addRecord("Физика", 5);
    student->sessionData[0].addRecord("ЯП", 1);
    student->sessionData[0].addRecord("Мат. анализ", 5);
    student->addSession();
    student->sessionData[1].addRecord("ЛАиАГ", 5);
    student->sessionData[1].addRecord("Информатика", 5);
    student->sessionData[1].addRecord("Введение в проф. деятельность", 1);
    student->sessionData[1].addRecord("История", 4);
    student->editSession(0, "Физика", 1, 5);
    student->editSession(1, "История", 4, 5);
    temp = student;
    cout << temp->getBirthYear() << endl;
    while (temp->getNext() != NULL){
        temp = temp->getNext();
        cout << temp->getBirthYear() << endl;
    }
    studentSort = new StudentSortClass();
    studentSort->populateList(student);
    studentSort->sortList("2000", "3000");
    struct Sort* temp2;
    temp2 = studentSort->getSortedList();
    cout << "End";
}