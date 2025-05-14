#pragma once
#include <cstring>

#include "DataBase.hpp"
#include "Field.hpp"

// Field operations
// contains operations (such as sort) for class DataBase when used with Type Field
namespace FieldOp {

    // template<typename T>
    // void swap(T& a, T& b);

    // looks if the first string is greater than the second (lower case the strings before giving as argument)
    bool strGreater(const std::string& str1, const std::string& str2);

    // makes the string lowercase
    std::string lowerCase(const std::string& str);

    bool is_number(const std::string& str);


// ***** search ***** //

    // returns all slots that include the given keyword
    std::vector<Field> searchFor(DataBase<Field>& db, const std::string& keyWord);

// ***** sort in increasing (A - Z) order ***** //

    void sortFirstName(DataBase<Field>& db);
    
    void sortSecondName(DataBase<Field>& db);

    void sortSchoolClass(DataBase<Field>& db);

    void sortId(DataBase<Field>& db);

    void sortAge(DataBase<Field>& db);
      

// ***** sort in decreasing (Z - A) order ***** //

    void dSortFirstName(DataBase<Field>& db);
    
    void dSortSecondName(DataBase<Field>& db);

    void dSortSchoolClass(DataBase<Field>& db);

    void dSortId(DataBase<Field>& db);

    void dSortAge(DataBase<Field>& db);
};

// template<typename T>
// void FieldOp::swap(T& a, T& b) {
//     T tmp = a;
//     a = b;
//     b = tmp;
// }

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
        res += std::tolower(str[i]);
    }

    return res;
}

bool FieldOp::is_number(const std::string& str) {
    for (const char sym : str) {
        if (sym < '0' || sym > '9') {
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
        if(is_number(keyWord) && (cur.getAge() == stoi(keyWord) || cur.getId() == stoi(keyWord))) {
            res.push_back(cur);
            continue;
        }
        // if the keyword is foundable in string variables
        if (std::string{cur.getFirstName()}.find(keyWord) != std::string::npos || std::string{cur.getSecondName()}.find(keyWord) != std::string::npos || std::string{cur.getSchoolClass()}.find(keyWord) != std::string::npos) {
            res.push_back(cur);
            continue;
        }
    }

    return res;
}

// ***** sort in increasing (A - Z) order ***** //

void FieldOp::sortFirstName(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (strGreater(lowerCase(db[j].getFirstName()), lowerCase(db[j + 1].getFirstName()))) {
                std::swap(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::sortSecondName(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (strGreater(lowerCase(db[j].getSecondName()), lowerCase(db[j + 1].getSecondName()))) {
                std::swap(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::sortSchoolClass(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (strGreater(lowerCase(db[j].getSchoolClass()), lowerCase(db[j + 1].getSchoolClass()))) {
                std::swap(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::sortId(DataBase<Field>& db) {
    std::sort(db.begin(), db.end(), [] (const Field& a, const Field& b) {
        return a.getId() < b.getId();
    });
}

void FieldOp::sortAge(DataBase<Field>& db) {
    std::sort(db.begin(), db.end(), [] (const Field& a, const Field& b) {
        return a.getAge() < b.getAge();
    });
}


// ***** sort in decreasing (Z - A) order ***** //

void FieldOp::dSortFirstName(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (!strGreater(lowerCase(db[j].getFirstName()), lowerCase(db[j + 1].getFirstName()))) {
                std::swap(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::dSortSecondName(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (!strGreater(lowerCase(db[j].getSecondName()), lowerCase(db[j + 1].getSecondName()))) {
                std::swap(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::dSortSchoolClass(DataBase<Field>& db) {
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < (n - i - 1); j++) {
            if (!strGreater(lowerCase(db[j].getSchoolClass()), lowerCase(db[j + 1].getSchoolClass()))) {
                std::swap(db[j], db[j + 1]);
            }
        }
    }
}

void FieldOp::dSortId(DataBase<Field>& db) {
    std::sort(db.begin(), db.end(), [] (const Field& a, const Field& b) {
        return b.getId() < a.getId();
    });
}

void FieldOp::dSortAge(DataBase<Field>& db) {
    std::sort(db.begin(), db.end(), [] (const Field& a, const Field& b) {
        return b.getAge() < a.getAge();
    });
}
