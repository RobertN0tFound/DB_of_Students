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
        StudentCount++;
        headUnList->stId = temp;
        for(int i = 0; i < 10; i++){
            headUnList->rating += temp->sessionData[i].getRating();
        }
        while (temp->getNext() != NULL){
            struct Sort* tmp = new Sort;
            StudentCount++;
            temp = temp->getNext();
            tmp->stId = temp;
            for(int i = 0; i < 10; i++){
                tmp->rating += temp->sessionData[i].getRating();
            }
        }
    }

    void sortList(){
        struct Sort* tmp = headUnList;
        struct Sort* temp = headSoList;
        struct Sort* headSoList{new Sort[StudentCount]};
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
        struct Sort* headSoList{new Sort[StudentCount]};
        double* rate{new double[StudentCount]};
        int _StartYear = stoi(StartYear);
        int _EndYear = stoi(EndYear);
        SortedCount = 0;
        while(tmp){
            if (tmp->stId->getBirthYear() >= _StartYear && tmp->stId->getBirthYear() <= _EndYear){
                rate[SortedCount] = tmp->rating;
            }
            tmp = tmp->next;
            SortedCount++;
        }
        sort(rate, rate + SortedCount);
        for (int i = 0; i < SortedCount; i++){
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
    }

    int getSortedCount(){
        return SortedCount;
    }

    Sort* getSortedList(){
        return headSoList;
    }
};