#include "DataBase.hpp"
#include "Field.hpp"

// Field operations
// contains operations (such as sort) for class DataBase when used with Type Field
namespace FieldOp {

    template<typename T>
    void swap(T& a, T& b);

    // looks if the first string is greater than the second (lower case the strings before giving as argument)
    bool strGreater(const std::string& str1, const std::string& str2);

    // makes the string lowercase
    std::string lowerCase(const std::string& str);

    bool is_number(const std::string& str);


// ***** search ***** //

    // returns all slots that include the given keyword
    std::vector<Field> searchFor(DataBase<Field>& db, const std::string& keyWord);

// ***** sort in increasing (A - Z) order ***** //

    void sort_firstName(DataBase<Field>& db);
    
    void sort_secondName(DataBase<Field>& db);

    void sort_schoolClass(DataBase<Field>& db);

    void sort_id(DataBase<Field>& db);

    void sort_age(DataBase<Field>& db);
      

// ***** sort in decreasing (Z - A) order ***** //

    void dSort_firstName(DataBase<Field>& db);
    
    void dSort_secondName(DataBase<Field>& db);

    void dSort_schoolClass(DataBase<Field>& db);

    void dSort_id(DataBase<Field>& db);

    void dSort_age(DataBase<Field>& db);
};

template<typename T>
void FieldOp::swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

bool FieldOp::strGreater(const std::string& str1, const std::string& str2) {
    size_t n1 = str1.length();
    size_t n2 = str2.length(); 

    for (size_t i = 0; (i < n1) && (i < n2); i++) {
        if (str1[i] > str2[i]) {
            return true;
        }
        else if (str1[i] < str2[i]) {
            return false;
        }
    }
    // if strings have different lenght:

    // if the first string is longer -> return true
    return n1 > n2;
}

std::string FieldOp::lowerCase(const std::string& str) {
    std::string res;

    size_t n = str.length();

    for (size_t i = 0; i < n; i++) {
        char ch = str[i];

        if (ch >= 'A' && ch <= 'Z') 
            ch += 'a' - 'A';

        res += ch;
    }

    return res;
}

bool FieldOp::is_number(const std::string& str)
{
    for (char it : str) {
        if (it < '0' || it > '9') {
            return false;
        }
    }

    return true;
}

// ***** search ***** //

std::vector<Field> FieldOp::searchFor(DataBase<Field>& db, const std::string& keyWord)
{
    std::vector<Field> res;

    // iterate through each field of db, and add to res if there's at least one element with variable == keyWord
    for (const Field& cur : db) {
        // if the keyword is a digit
        if(is_number(keyWord) && (cur.get_age() == stoi(keyWord) || cur.get_id() == stoi(keyWord))) {
            res.push_back(cur);
            continue;
        }
        // if the keyword is foundable in string variables
        if (std::string{cur.get_firstName()}.find(keyWord) != std::string::npos || std::string{cur.get_secondName()}.find(keyWord) != std::string::npos || std::string{cur.get_schoolClass()}.find(keyWord) != std::string::npos) {
            res.push_back(cur);
            continue;
        }
    }

    return res;
}

// ***** sort in increasing (A - Z) order ***** //

void FieldOp::sort_firstName(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (strGreater(lowerCase(db[j].get_firstName()), lowerCase(db[j + 1].get_firstName()))) {
                swap<Field>(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::sort_secondName(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (strGreater(lowerCase(db[j].get_secondName()), lowerCase(db[j + 1].get_secondName()))) {
                swap<Field>(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::sort_schoolClass(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (strGreater(lowerCase(db[j].get_schoolClass()), lowerCase(db[j + 1].get_schoolClass()))) {
                swap<Field>(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::sort_id(DataBase<Field>& db) {
    size_t n = db.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1 - i); j++) {
            if (db[j].get_id() > db[j + 1].get_id()) {
                swap<Field>(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::sort_age(DataBase<Field>& db) {
    size_t n = db.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1 - i); j++) {
            if (db[j].get_age() > db[j + 1].get_age()) {
                swap<Field>(db[j], db[j + 1]);
            }
        }
    }
}


// ***** sort in decreasing (Z - A) order ***** //

void FieldOp::dSort_firstName(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (!strGreater(lowerCase(db[j].get_firstName()), lowerCase(db[j + 1].get_firstName()))) {
                swap<Field>(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::dSort_secondName(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (!strGreater(lowerCase(db[j].get_secondName()), lowerCase(db[j + 1].get_secondName()))) {
                swap<Field>(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::dSort_schoolClass(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (!strGreater(lowerCase(db[j].get_schoolClass()), lowerCase(db[j + 1].get_schoolClass()))) {
                swap<Field>(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::dSort_id(DataBase<Field>& db) {
    size_t n = db.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1 - i); j++) {
            if (db[j].get_id() < db[j + 1].get_id()) {
                swap<Field>(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::dSort_age(DataBase<Field>& db) {
    size_t n = db.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1 - i); j++) {
            if (db[j].get_age() < db[j + 1].get_age()) {
                swap<Field>(db[j], db[j + 1]);
            }
        }
    }
}
