#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

#include "DataBase.hpp"
#include "Field.hpp"
#include "FieldOp.hpp"

using namespace std;

void output(const DataBase<Field>& db) {
    std::cout << db[0].getHeadLine('\t') << std::endl;
    
    for (auto& it : db) {
        std::cout << it.getRowLine() << std::endl;
    }
}

int main() {
    
    DataBase<Field> db;
    db.load("list.csv");

    std::cout << "Size: " << db.size() << std::endl;
    output(db);
    std::cout << std::endl;
    FieldOp::sort_age(db);
    output(db);
    
    
    return 0;
}