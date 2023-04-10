#include <iostream>
#include <algorithm>
#include "StudentClass.h"

using namespace std;

struct Sort{
    StudentClass* stId;
    double rating = 0;
    bool isCopied = false;
    struct Sort* prev = NULL;
    struct Sort* next = NULL;
};

class StudentSortClass{ // Нужно отсортировать по убыванию успеваемости за сессии
private:
    struct Sort* headUnList;
    struct Sort* headSoList;
    int StudentCount;
    int SortedCount;

public:
    StudentSortClass(){
        headUnList = NULL;
        headSoList = NULL;
        StudentCount = 0;
        SortedCount = 0;
    }
    void populateList(StudentClass* head){
        StudentClass* temp = head;
        headUnList = new Sort;
        struct Sort* current = headUnList;
        StudentCount++;
        headUnList->stId = temp;
        for(int i = 0; i < 9; i++){
            headUnList->rating += temp->sessionData[i].getRating();
        }
        while (temp->getNext() != NULL){
            StudentCount++;
            temp = temp->getNext();
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new Sort;
            current->next->stId = temp;
            for(int i = 0; i < 9; i++){
                current->next->rating += temp->sessionData[i].getRating();
            }
            current->next->next = NULL;
            current->next->prev = current;
        }
    }

    void sortList(){
        struct Sort* tmp = headUnList;
        struct Sort* temp = headSoList;
        headSoList = {new Sort[StudentCount]};
        double* rate{new double[StudentCount]};
        int i = 0;
        while(tmp){
            rate[i] = tmp->rating;
            tmp = tmp->next;
            i++;
        }
        sort(rate, rate + StudentCount);
        for (i = 0; i < StudentCount; i++){
            tmp = headUnList;
            while(tmp->next != NULL){
                if(tmp->rating == rate[i] && tmp->isCopied == false){
                        headSoList[i].stId = tmp->stId;
                        headSoList[i].rating = tmp->rating;
                        tmp->isCopied = true;
                }
            tmp = tmp->next;
            }
        }
        SortedCount = StudentCount;
    }

    void sortList(string StartYear, string EndYear){
        struct Sort* tmp = headUnList;
        struct Sort* temp = headSoList;
        headSoList = {new Sort[StudentCount]};
        double* rate{new double[StudentCount]};
        int _StartYear = stoi(StartYear);
        int _EndYear = stoi(EndYear);
        SortedCount = 0;
        while(tmp){
            if (tmp->stId->getBirthYear() >= _StartYear && tmp->stId->getBirthYear() <= _EndYear){
                rate[SortedCount] = tmp->rating;
                SortedCount++;
            }
            tmp = tmp->next;
        }
        sort(rate, rate + SortedCount, greater<double>());
        for (int i = 0; i < SortedCount; i++){
            tmp = headUnList;
            while(tmp){
                if(tmp->rating == rate[i] && tmp->isCopied == false){
                        headSoList[i].stId = tmp->stId;
                        headSoList[i].rating = tmp->rating;
                        tmp->isCopied = true;
                        break;
                }
            tmp = tmp->next;
            }
        }
    }

    int getSortedCount(){
        return SortedCount;
    }

    Sort* getSortedList(){
        return headSoList;
    }
};