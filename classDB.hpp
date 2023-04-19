#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "classMassive.hpp"
#include "classMap.hpp"
#include "json.hpp" //https://json.nlohmann.me/api/basic_json/is_number/#examples

using json = nlohmann::json;

class DB_Students
{
private:
    int id;                   // ид записи студента, указывает на следующего
    json db = json::object(); // database студентов

    // Проверяет наличие студента
    bool isStudentFound(std::string sid)
    {
        if (db.size() == 0) // нет студентов, бд пустая
            return false;

        for (auto &[key, val] : db.items()) // пройдем по ключам
        {
            if (sid == key)
                return true; // ключ найден
        }
        return false;
    }
    // проверяет наличие номера зачетки в БД, если есть то true
    bool isNumDoc(std::string numDoc)
    {
        if (db.size() == 0) // нет студентов, бд пустая
            return false;

        for (auto &[key, val] : db.items()) // пройдем по ключам
        {
            if (numDoc == val["Номер зачетки"])
                return true; // номер зачетки найден
        }
        return false;
    }

    // есть ли сессия для студента
    bool isSessionFound(std::string sid, std::string sessionId)
    {
        if (db.empty()) // нет студентов, бд пустая
            return false;
        if (!isStudentFound(sid))
            return false;

        try
        {
            return !db[sid]["Сессия"][sessionId].empty();
        }
        catch (json::exception &e)
        {
            // output exception information
            std::cerr << "message: " << e.what() << std::endl
                    << "exception id: " << e.id << std::endl;
            return false;
        }
    }

public:
    DB_Students()
    {
        id = 1;
    };

    ~DB_Students()
    {
        db.clear();
    }

    bool save(const std::string filename = "database.txt")
    {
        std::ofstream ofs(filename);
        if (ofs.is_open())
        {
            ofs << std::setw(2) << db;
            return true;
        }
        std::cerr << "Ошибка записи файла: " << filename << std::endl;
        return false;
    }

    bool load(const std::string filename = "database.txt")
    {
        std::ifstream ifs(filename);
        if (ifs.is_open())
        {
            ifs >> db;
            if (db.size() == 0) // нет студентов, бд пустая
                return false;

            int tmp;
            for (auto &[key, val] : db.items())
            {
                std::stringstream ss;
                ss << key;
                ss >> tmp;
                if (tmp > id)
                    id = tmp;
            }
            id++; // следущий студент
            return true;
        }
        std::cerr << "Ошибка чтения файла: " << filename << std::endl;
        return false;
    }

    int addStudent(const std::string &name, const std::string &middleName, const std::string &surName, const std::string birthDate,
                const std::string &sex, const std::string &startYear, const std::string &departament,
                const std::string &facultet, const std::string &group, const std::string &numDoc)
    {
        try
        {
            if (!isNumDoc(numDoc)) // проверяем наличие номера зачетки, если нет, то добавляем студента
            {
                std::string sid = std::to_string(id);
                db[sid]["Фамилия"] = surName;
                db[sid]["Имя"] = name;
                db[sid]["Отчество"] = middleName;
                db[sid]["Дата рождения"] = birthDate;
                db[sid]["Пол"] = sex;
                db[sid]["Поступил"] = startYear;
                db[sid]["Отделение"] = departament;
                db[sid]["Факультет"] = facultet;
                db[sid]["Группа"] = group;
                db[sid]["Номер зачетки"] = numDoc;
                db[sid]["Рейтинг"] = 0.0;
                id++; // следующий студент
            }
            else
            {
                std::cerr << "Ошибка. Номер зачетки:" << numDoc << " уже есть в базе." << std::endl;
                return -1;
            }
        }
        catch (json::exception &e)
        {
            // output exception information
            std::cerr << "message: " << e.what() << std::endl
                    << "exception id: " << e.id << std::endl;
            return -1;
        }
        return (id - 1); // вернем ID студента
    }

    bool setStudentAttr(int _id, std::string key, std::string val)
    {
        std::string sid = std::to_string(_id);
        if (!isStudentFound(sid))
            return false; // нет студента
        try
        {
            db[sid][key] = val;
        }
        catch (json::exception &e)
        {
            // output exception information
            std::cerr << "message: " << e.what() << std::endl
                    << "exception id: " << e.id << std::endl;
            return false;
        }
        return true;
    }

    // устанавливет (создаем или обновляет) экзамен для студента
    // studentId - int id студента в БД, можно получить поиском
    // sessionId - int id сессии в которую добавляем предмет и оценку
    bool setExamResult(const int studentId, const int sessionId, const std::string &examName, const int examMark)
    {
        std::string sid = std::to_string(studentId);
        if (!isStudentFound(sid))
            return false; // нет студента

        std::string sesId = std::to_string(sessionId);

        try
        {
            db[sid]["Сессия"][sesId][examName] = examMark;
        }
        catch (json::exception &e)
        {
            // output exception information
            std::cerr << "message: " << e.what() << std::endl
                    << "exception id: " << e.id << std::endl;
            return false;
        }
        return true;
    }

    // возвращает оценку по id студента, id сессии, ноименования предмета
    // если не найдено значение, то возврат будет < 0
    int getExamResult(const int studentId, const int sessionId, std::string examName)
    {

        std::string sid = std::to_string(studentId);
        std::string sesId = std::to_string(sessionId);

        if (!isStudentFound(sid)) // нет студента
            return -10;

        try
        {

            return db[sid]["Сессия"][sesId][examName];
        }
        catch (json::exception &e)
        {
            // output exception information
            std::cerr << "message: " << e.what() << std::endl
                    << "exception id: " << e.id << std::endl;
            return -1;
        }
        return -5; // сюда не должно попасть по логике, но на всякий случай, что видно было, что логика страдает
        ;
    }

    // обновим рейтинги студенов по всей БД, в рейтинге храним только два знака после запятой
    bool calculateAllRating()
    {
        if (db.size() == 0) // нет студентов, бд пустая
            return false;

        float rating;
        int count;
        for (auto &[key, val] : db.items())
        {                 // обход всех студентов
            rating = 0.0; // сбросим рейтинг для найденного студента
            count = 0;    // считаем кол-во сданных экзаменов
            for (json session : val["Сессия"].items())
            {                                              // Берем только сессию, остальные поля нам не интресны
                for (auto &[_key, _val] : session.items()) // скичем ключ и значение
                {
                    for (auto &[exam, mark] : _val.items()) // так как в значении у нас структуре предмет:оценка, то пройдемся по ней
                    {                                       // обход всех сданных экзаменов
                        rating += int(mark);                // приведение явно к типу int
                        count++;                            // считаем кол-во сданных экзменов
                    }
                }
            }
            if (count > 0) // если есть оценки, то вычислим среднее арифметическое значение рейтинга
            {
                db[key]["Рейтинг"] = round((rating / count) * 100) / 100; // оставим 2 знака после запятой
                // std::cout << "Рейтинг" << db[key]["Рейтинг"] << std::endl;
                // std::cout << key << std::endl;
            }
            else
                db[key]["Рейтинг"] = 0.0;
        }
        return true;
    };

    // возвращает id студента по ФИО
    // если не найден студент, то возврщаем < 0
    int getStudentId(const std::string name, const std::string middleName, const std::string surName)
    {
        if (db.size() == 0) // нет студентов, бд пустая
            return -100;

        for (auto &[key, val] : db.items())
        {
            if ((val["Имя"] == name) && (val["Отчество"] == middleName) && (val["Фамилия"] == surName))
            {
                int tmp;
                std::stringstream ss;
                ss << key;
                ss >> tmp;
                return tmp;
            }
        }
        return -1;
    };

    // возвращает id студента по номеру зачетки
    // если не найден студент, то возврщаем < 0
    int getStudentIdNumDoc(const std::string numDoc)
    {
        if (db.size() == 0) // нет студентов, бд пустая
            return -100;

        for (auto &[key, val] : db.items())
        {
            if (val["Номер зачетки"] == numDoc)
            {
                int tmp;
                std::stringstream ss;
                ss << key;
                ss >> tmp;
                return tmp;
            }
        }
        return -1;
    };

    // Возвращает массив ID студентов отсортированных по возрастанию рейтинга
    Massive<int> sortAsc()
    {
        Massive<int> ids;
        Massive<float> ratings;
        int int_tmp;
        float float_tmp;

        for (auto &[key, val] : db.items())
        {
            std::stringstream ss;
            ss << key;
            ss >> int_tmp;
            ids.pushBack(int_tmp);
            ratings.pushBack(val["Рейтинг"]);
        }

        // метод пузырька для сортировки
        bool isChange = true;
        while (isChange)
        {
            isChange = false; // если не будет изменений - выход
            for (int i = 0; i < ids.size() - 1; i++)
            {
                if (ratings[i] > ratings[i + 1])
                { // Если текущий больше следующего, то меняем местами
                    int_tmp = ids[i];
                    ids[i] = ids[i + 1];
                    ids[i + 1] = int_tmp;
                    float_tmp = ratings[i];
                    ratings[i] = ratings[i + 1];
                    ratings[i + 1] = float_tmp;
                    isChange = true; // было изменение
                }
            }
        }

        return ids; // возвращаем отсортированный по рейтингу массив ID студентов
    }

    // Возвращает массив ID студентов отсортированных по убыванию рейтинга
    Massive<int> sortDec()
    {
        Massive<int> ids;
        Massive<float> ratings;
        int int_tmp;
        float float_tmp;

        for (auto &[key, val] : db.items())
        {
            std::stringstream ss;
            ss << key;
            ss >> int_tmp;
            ids.pushBack(int_tmp);
            ratings.pushBack(val["Рейтинг"]);
        }

        // метод пузырька для сортировки
        bool isChange = true;
        while (isChange)
        {
            isChange = false; // если не будет изменений - выход
            for (int i = 0; i < ids.size() - 1; i++)
            {
                if (ratings[i] < ratings[i + 1])
                { // Если текущий больше следующего, то меняем местами
                    int_tmp = ids[i];
                    ids[i] = ids[i + 1];
                    ids[i + 1] = int_tmp;
                    float_tmp = ratings[i];
                    ratings[i] = ratings[i + 1];
                    ratings[i + 1] = float_tmp;
                    isChange = true; // было изменение
                }
            }
        }

        return ids; // возвращаем отсортированный по рейтингу массив ID студентов
    }

    std::string getStudentFIO(const int _id)
    {

        std::string sid = std::to_string(_id);

        if (!isStudentFound(sid)) // нет студента
            return "";

        std::string res;
        res = db[sid]["Фамилия"];
        res += " ";
        res += db[sid]["Имя"];
        res += " ";
        res += db[sid]["Отчество"];
        return res;
    }

    bool deleteStudent(const int _id)
    {
        std::string sid = std::to_string(_id);
        try
        {
            db.erase(sid);
        }
        catch (json::exception &e)
        {
            // output exception information
            std::cerr << "Delete message: " << e.what() << std::endl
                    << "exception id: " << e.id << std::endl;
            return false;
        }
        return true;
    }

    // возвращает атттрибуты студента
    Massive<StrStr> getStudentAttrList(const int _id)
    {
        Massive<StrStr> result;
        std::string sid = std::to_string(_id);

        if (!isStudentFound(sid)) // нет студента
            return result;

        for (auto &[key, val] : db[sid].items())
        {
            if (key != "Сессия")
            {
                // std::cout << key << ":" << val << std::endl;
                if (key == "Рейтинг")
                {
                    std::stringstream ss;
                    std::string str;
                    ss << val;
                    ss >> str;
                    result.pushBack({key, str});
                }
                else
                    result.pushBack({key, val});
            }
        }
        return result;
    }

    // возвращает экзамен и оценку
    Massive<StrInt> getSessionExamList(const int _id, const int _sessionId)
    {
        Massive<StrInt> result;
        std::string sid = std::to_string(_id);
        std::string sessionid = std::to_string(_sessionId);

        if (!isSessionFound(sid, sessionid)) // нет студента или сессии для него
            return result;

        for (json session : db[sid]["Сессия"][sessionid].items())
        {                                              // Берем только сессию, остальные поля нам не интресны
            for (auto &[exam, mark] : session.items()) // так как в значении у нас структуре предмет:оценка, то пройдемся по ней
            {                                          // обход всех сданных экзаменов
                result.pushBack({exam, mark});
            }
        }
        return result;
    }

    Massive<int> getSessionList(const int _id)
    {
        Massive<int> result;
        std::string sid = std::to_string(_id);
        int int_tmp;

        if (!isStudentFound(sid)) // нет студента
            return result;

        for (auto &[key, val] : db[sid]["Сессия"].items())
        { // Берем только сессии, остальные поля нам не интресны
            std::stringstream ss;
            ss << key;
            ss >> int_tmp;
            result.pushBack(int_tmp); // Добавим в массивt
        }
        return result;
    }

    Massive<IntStr> getstudentListFIO()
    {
        Massive<IntStr> results;
        int int_key;
        for (auto &[key, val] : db.items())
        {
            int_key = stol(key);
            results.pushBack({int_key, getStudentFIO(int_key)});
        }
        return results;
    }
};
/* Примеры использования
    db.load();
    int student1 = db.addStudent("Сергей", "Сергеевич", "Сергеев", "М", "2021", "ВТиА", "ИБ", "ИБ-2021-001", "202101008");
    int student2 = db.addStudent("Елена", "Петровна", "Умывайкина", "Ж", "2021", "ВТиА", "ИБ", "ИБ-2021-001", "202101009");
    // int i = db.getStudentId("Иван", "Иванович", "Иванов");
    if (student1 > 0)
    {
        db.setExamResult(student1, 0, "Математика", 1);
        db.setExamResult(student1, 0, "Физика", 5);
        db.setExamResult(student1, 1, "Биология", 5);
    }
    // i = db.getStudentId("Анна", "Петровна", "Иванова");
    if (student2 > 0)
    {
        db.setExamResult(student2, 0, "Основы биологии", 5);
        db.setExamResult(student2, 1, "Математика", 5);
        db.setExamResult(student2, 1, "Основы биологии", 5);
    }
    db.calculateAllRating();

    Massive<int> sorting = db.sortDec();

    for (int i = 0; i < sorting.size(); i++)
    {
        std::cout << sorting[i] << " :  " << db.getStudentFIO(sorting[i]) << std::endl;
    }

    std::cout << "Основы биологии: " << db.getExamResult(1, 0, "Основы биологии") << std::endl;

    std::cout << "Иван id: " << db.getStudentId("Иван", "Иванович", "Иванов") << std::endl;
    std::cout << "Анна id: " << db.getStudentIdNumDoc("202101003") << std::endl;

    // std::cout << std::setw(4) << db.db << std::endl;

    db.save();

*/
