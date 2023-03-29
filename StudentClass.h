#include <string>
#include <iostream>
#include "SessionDataClass.h"

using namespace std;

class StudentClass{
private:
    int id;
    string surname;
    string name;
    string middleName;
    string birthDate;
    int entryYear;
    string faculty;
    string department;
    string group;
    string recordBook;
    char sex;
    int rating;
    SessionDataClass sessionData[9];
    int nextSessionData;
    StudentClass* prev;
    StudentClass* next;
    
public:
    StudentClass(int _id, string _surname, string _name, string _middleName, string _birthDate, int _entryYear,
    string _faculty, string _department, string _group, string _recordBook, char _sex, StudentClass* _prev){
        id = _id;
        surname = _surname;
        name = _name;
        middleName = _middleName;
        birthDate = _birthDate;
        entryYear = _entryYear;;
        faculty = _faculty;;
        department = _department;
        group = _group;;
        recordBook = _recordBook;
        sex = _sex;
        prev = _prev;
        next = NULL;
        nextSessionData = 0;
        rating = 0;
    }

    void addSession(){
        if (nextSessionData < 9){
            SessionDataClass* tmp;
            tmp = new SessionDataClass();
            sessionData[nextSessionData] = *tmp;
            nextSessionData++;
        }
        else{
            cout << "Достигнуто максимальное количество сессий" << endl;
        }
    }

    void editSession(int index, string _name, int _mark){ // Изменить оценку сессии
        if (index < nextSessionData){
            sessionData[index].updateRecord(_name, _mark);
        }
        else{
            cout << "Данной сессии не существует" << endl;
        }
    }

    void editSession(int index, string _name, string _newName){ // Изменить предмет сессии
        if (index < nextSessionData){
            sessionData[index].updateRecord(_name, _newName);
        }
        else{
            cout << "Данной сессии не существует" << endl;
        }
    }

    void addStudent(int _id, string _surname, string _name, string _middleName, string _birthDate, int _entryYear,
    string _faculty, string _department, string _group, string _recordBook, char _sex){
        StudentClass* tmp;
        tmp = new StudentClass(_id, _surname, _name, _middleName, _birthDate, _entryYear,
        _faculty, _department, _group, _recordBook, _sex,  this);
        this->next = tmp;
    }

    StudentClass* getNext(){
        return next;
    }
    
    StudentClass* getPrev(){
        return prev;
    }

    int getId(){
        return id;
    }

    string getBirthDate(){
        return birthDate;
    }
};
