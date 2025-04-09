#include <iostream>
#include <vector>
#include <climits>
#include "DataBase.hpp"
#include "Field.hpp"
#include "FieldOp.hpp"



int main() {
    FILE* file = fopen("list.csv", "r");
    char* str1;
    int a = 0;
    char* str2;

    fscanf(file, "%s, %d, %s\n", str1, &a, str2);
    std::cout << str1 << ' ' << a << ' ' << str2 << std::endl;; 

    fclose(file);
    return 0;
}