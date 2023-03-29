#include <iostream>
#include "StudentClass.h"
#include "SessionDataClass.h"

using namespace std;

struct Sort{
    StudentClass* stId;
    int rating = 0;
    struct Sort* prev = NULL;
    struct Sort* next = NULL;
};
struct Sort* headUnList = NULL;
struct Sort* headSoList = NULL;
class StudentSortClass{ // Нужно отсортировать по убыванию успеваемости за сессии
public:
    void addList(){
        Sort* tmp = headUnList;
        SessionDataClass rate;
        Sort* prev = NULL;
        Sort* next = NULL;
        if (headUnList == NULL){
            headUnList = new Sort;
            headUnList->stId = NULL;
            headUnList->rating = rate.getRating();
            headUnList->prev = NULL;
            headUnList->next = NULL;
        }
        else{
            while(tmp->next!= NULL){
                tmp = tmp->next;
            }
            tmp->next = new Sort;
            tmp->next->stId = NULL;
            tmp->next->rating = rate.getRating();
            tmp->next->prev = tmp;
            tmp->next->next = NULL;
        }
    }

    void sortList(){
        Sort* tmp = headUnList;
        headSoList = new Sort;
        while(){

        }
    }
};