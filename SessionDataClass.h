#include <string>

using namespace std;

class SessionDataClass{
private:
    string name[10];
    int mark[10];
            // 0 - не зачтено
            // 1 - зачтено
            // 2, 3, 4, 5 - оценки
public:
    
    SessionDataClass(){
        for(int i = 0; i < 10; i++){
            name[i] = "";
            mark[i] = -1;
        }
    }

    void addRecord(string _name, int _mark){
        for(int i = 0; i < 10; i++){
            if (name[i] == "") {
                name[i] = _name;
                mark[i] = _mark;
                return;
            }
        }
    }
    
    string getRecord(int index){
        return "Предмет: " + name[index] + " Оценка: " + to_string(mark[index]);
    }

    string getRecord(string _name){
        string str = "";
        for(int i = 0; i < 10; i++){
            if (name[i] == _name){
                str += "Предмет: " + name[i] + " Оценка: " + to_string(mark[i]) + "\n";
            }
        }
        return str;
    }

    void updateRecord(string _oldName, string _newName){
        for(int i = 0; i < 10; i++){
            if (name[i] == _oldName){
                name[i] = _newName;
            }
        }
    }

    void updateRecord(string _name, int _oldMark, int _newMark){
        for(int i = 0; i < 10; i++){
            if (name[i] == _name && mark[i] == _oldMark){
                mark[i] = _newMark;
                return;
            }
        }
    }

    int getRating(){
        double sum = 0;
        double res;
        int elements = 0;
        for(int i = 0; i < 10; i++){
            sum += mark[i];
            elements++;
        }
        res = sum/elements;
        return res;
    }
};