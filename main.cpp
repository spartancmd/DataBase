#include <iostream>
#include <cstdio>
#include <string>

#include "DataBase.hpp"
#include "Field.hpp"
#include "FieldOp.hpp"

namespace CommandOp {
    // possible commands to choose. For description look in README.md
    enum COMMAND {
        OPEN,
        VIEW_ALL,
        EXIT,
        ADD_SLOT,
        REMOVE_SLOT,
        SEARCH_FOR,
        SORT_AFTER,
        SORT_DECREASE_AFTER,
        UNKNOWN,
        HELP,
    };

    // writes the seperated input in source into target
    void parseInput(std::vector<std::string>& target, const std::string& source, const char sep = ' ');

    // returns the selected command as an enum, to be useable in switch-case
    COMMAND selectCommand(const std::string& option);

    // calls the choosen command
    void redirectCommand(const COMMAND opt, const std::vector<std::string>& input, DataBase<Field>& db);

    // all input commands

    // loads file into db
    void open(const std::vector<std::string>& input, DataBase<Field>& db);

    // prints the database into the terminal
    void view_all(const std::vector<std::string>& input, DataBase<Field>& db);

    // does last instructions before the programm ends
    void exit(const std::vector<std::string>& input, DataBase<Field>& db);

    // adds a slot to the db
    void add_slot(const std::vector<std::string>& input, DataBase<Field>& db);

    // removes a slot by given id
    void remove_slot(const std::vector<std::string>& input, DataBase<Field>& db);

    // prints the slots that contain the given keyword
    void search_for(const std::vector<std::string>& input, DataBase<Field>& db);

    // sorts the data base after the given element (in increasing order)
    void sort_after(const std::vector<std::string>& input, DataBase<Field>& db);

    // sorts the data base after the given element (in decreasing order)
    void sort_decrease_after(const std::vector<std::string>& input, DataBase<Field>& db);
    
    // prints possible commands
    void help(const std::vector<std::string>& input, DataBase<Field>& db);
}



int main(int argc, char* argv[]) {
    DataBase<Field> db;
    std::string input;
    std::vector<std::string> parsedInput; 
    CommandOp::COMMAND opt;

    // if there's a second arg, it should be a path
    if (argc > 1) {
        db.load(argv[1]);
        std::cout << "Loaded from file" << argv[1] << '\n' <<  std::endl;
    }

    do {
        std::cout << "> ";
        getline(std::cin, input);
        std::cout << std::endl;;
        CommandOp::parseInput(parsedInput, input);

        opt = CommandOp::selectCommand(parsedInput[0]);
        CommandOp::redirectCommand(opt, parsedInput, db);

    } while (opt != CommandOp::COMMAND::EXIT);

    if (db.fileLoaded()) 
        db.upload();

    return 0;
}

CommandOp::COMMAND CommandOp::selectCommand(const std::string& option) {
    if (option == "open")
        return COMMAND::OPEN;
    if (option == "view-all")
        return COMMAND::VIEW_ALL;
    if (option == "exit")
        return COMMAND::EXIT;
    if (option == "add-slot")
        return COMMAND::ADD_SLOT;
    if (option == "remove-slot")
        return COMMAND::REMOVE_SLOT;
    if (option == "search-for")
        return COMMAND::SEARCH_FOR;
    if (option == "sort-after")
        return COMMAND::SORT_AFTER;
    if (option == "sort-decrease-after")
        return COMMAND::SORT_DECREASE_AFTER;
    if (option == "help")
        return COMMAND::HELP;
    
    return COMMAND::UNKNOWN;
}

void CommandOp::redirectCommand(const COMMAND opt, const std::vector<std::string>& input, DataBase<Field>& db) {
    switch (opt) {
        case COMMAND::OPEN:
            CommandOp::open(input, db);
            break;
        case COMMAND::VIEW_ALL:
            CommandOp::view_all(input, db);
            break;
        case COMMAND::EXIT:
            CommandOp::exit(input, db);
            break;
        case COMMAND::ADD_SLOT:
            CommandOp::add_slot(input, db);
            break;
        case COMMAND::REMOVE_SLOT:
            CommandOp::remove_slot(input, db);
            break;
        case COMMAND::SEARCH_FOR:
            CommandOp::search_for(input, db);
            break;
        case COMMAND::SORT_AFTER:
            CommandOp::sort_after(input, db);
            break;
        case COMMAND::SORT_DECREASE_AFTER:
            CommandOp::sort_decrease_after(input, db);
            break;
        case COMMAND::HELP:
            CommandOp::help(input, db);
            break;
        default:
            std::cout << "Unknown command. Try \"help\" to get a list of possible commands.\n" << std::endl;
    }
}

void CommandOp::open(const std::vector<std::string>& input, DataBase<Field>& db) {
    if (input.size() == 1) {
        std::cout << "Path missing.\n" << std::endl;
        return;
    }

    db.load(input[1]);
    std::cout << "Loaded from file " << input[1] << '\n' << std::endl;
}

void CommandOp::view_all(const std::vector<std::string>& input, DataBase<Field>& db) {
    if (!db.fileLoaded()) {
        std::cout << "No file opened yet!\n" << std::endl;
        return;
    }

    std::cout << Field::getHeadLine('\t') << std::endl;

    for (const auto& it : db) {
        std::cout << it.getRowLine('\t') << std::endl;
    }
    std::cout << std::endl;
}

void CommandOp::exit(const std::vector<std::string>& input, DataBase<Field>& db) {
    if (input.size() == 1) {
        return;
    }

    std::cout << "Uploading to: " << input[1] << std::endl;
    db.upload(input[1]);
}

void CommandOp::add_slot(const std::vector<std::string>& input, DataBase<Field>& db) {
    if (!db.fileLoaded()) {
        std::cout << "No file opened yet!\n" << std::endl;
        return;
    }
    
    // if not enough args
    if (input.size() < 6) {
        std::cout << "Not all elements defined.\n" << std::endl;
        return;
    }

    // 1. and 5. indexes should be numbers
    if (!FieldOp::is_number(input[1])) {
        std::cout << "Type id as a decimal number\n" << std::endl;
        return;
    }
    if (!FieldOp::is_number(input[5])) {
        std::cout << "Type age as a decimal number\n" << std::endl;
        return;
    }

    db.addSlot(stoi(input[1]), input[2], input[3], input[4], stoi(input[5]));
}

void CommandOp::remove_slot(const std::vector<std::string>& input, DataBase<Field>& db) {
    if (!db.fileLoaded()) {
        std::cout << "No file opened yet!\n" << std::endl;
        return;
    }

    // if not enough args
    if (input.size() == 1) {
        std::cout << "No id given.\n" << std::endl;
        return;
    }    

    if (db.size() == 0) {
        std::cout << "Data base is empty.\n" << std::endl;
        return;
    }
    
    if (!FieldOp::is_number(input[1])) {
        std::cout << "Type id as a dezimal number\n" << std::endl;
        return;
    }

    unsigned targetId = stoi(input[1]);
    size_t n = db.size();

    for (size_t i = 0; i < n; i++) {
        if (db[i].get_id() == targetId) {
            db.removeSlot(i);
            return;
        }
    }

    std::cout << "No element with this the given id: " << targetId << '\n' << std::endl;
}

void CommandOp::search_for(const std::vector<std::string>& input, DataBase<Field>& db) {
    if (!db.fileLoaded()) {
        std::cout << "No file opened yet!\n" << std::endl;
        return;
    }
    
    // if not enough args
    if (input.size() == 1) {
        std::cout << "No keyword to search for.\n" << std::endl;
        return;
    }

    if (db.size() == 0) {
        std::cout << "Data base is empty.\n" << std::endl;
        return;
    }

    std::vector<Field> slots = FieldOp::searchFor(db, input[1]);

    std::cout << Field::getHeadLine() << std::endl;
    for (const auto& it : slots) {
        std::cout << it.getRowLine('\t') << std::endl;
    }
    std::cout << std::endl;
}

void CommandOp::sort_after(const std::vector<std::string>& input, DataBase<Field>& db) {
    if (!db.fileLoaded()) {
        std::cout << "No file opened yet!\n" << std::endl;
        return;
    }
    
    // if not enough args
    if (input.size() == 1) {
        std::cout << "No keyword to sort after for.\n" << std::endl;
        return;
    }

    if (db.size() == 0) {
        std::cout << "Data base is empty. Try to add slots.\n" << std::endl;
        return;
    }

    const std::string& sortTarget = input[1];

    std::cout << "Sorting after " << sortTarget << "..." << std::endl;
    if (sortTarget == "id") {
        FieldOp::sort_id(db);
    }
    else if (sortTarget == "first name") {
        FieldOp::sort_firstName(db);
    }
    else if (sortTarget == "second name") {
        FieldOp::sort_secondName(db);
    }
    else if (sortTarget == "class") {
        FieldOp::sort_schoolClass(db);
    }
    else if (sortTarget == "age") {
        FieldOp::sort_age(db);
    }
    else {
        std::cerr << "Element" << sortTarget << " does not exist!\n" << std::endl;
    }
}

void CommandOp::sort_decrease_after(const std::vector<std::string>& input, DataBase<Field>& db) {
    if (!db.fileLoaded()) {
        std::cout << "No file opened yet!\n" << std::endl;
        return;
    }
    
    if (input.size() == 1) {
        std::cout << "No keyword to sort after.\n" << std::endl;
        return;
    }
    
    if (db.size() == 0) {
        std::cout << "Data base is empty. Try to add slots.\n" << std::endl;
        return;
    }

    const std::string& sortTarget = input[1];

    std::cout << "Sorting in decreasing order after " << sortTarget << "..." << std::endl;
    if (sortTarget == "id") {
        FieldOp::dSort_id(db);
    }
    else if (sortTarget == "first name") {
        FieldOp::dSort_firstName(db);
    }
    else if (sortTarget == "second name") {
        FieldOp::dSort_secondName(db);
    }
    else if (sortTarget == "class") {
        FieldOp::dSort_schoolClass(db);
    }
    else if (sortTarget == "age") {
        FieldOp::dSort_age(db);
    }
    else {
        std::cerr << "Element" << sortTarget << " does not exist!\n" << std::endl;
    }
}

void CommandOp::help(const std::vector<std::string>& input, DataBase<Field>& db) {
    std::cout << "Commands to choose:\nopen <filePath>\nview-all \nexit (optional: <filePath>)\nadd-slot <id> <first name> <second name> <class> <age>\nremove-slot <id>\nsearch-for <keyword>\nsort-after id/\"first name\"/\"second name\"/class/age\nsort-decrease-after id/\"first name\"/\"second name\"/class/age\n" << std::endl;
}

void CommandOp::parseInput(std::vector<std::string>& target, const std::string& source, const char sep) {
    size_t n = source.length();
    std::string bfr;
    bool inQuotes = false;

    target.clear();
    for (size_t i = 0; i < n; i++) {
        while (i < n && (source[i] != sep || inQuotes) && source[i] != '\n') {
            if (source[i] == '\"') {
                inQuotes = !inQuotes;
                i++;
                continue;
            }

            bfr += source[i];
            i++;
        }

        target.push_back(bfr);
        bfr.clear();
    }
}
