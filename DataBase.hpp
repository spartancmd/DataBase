#pragma once

#include <fstream>
#include <vector>
#include <string> 

template<typename DataType>
class DataBase {
    std::vector<DataType> slots;

public:
// ***** constructor & destructor ***** //

    // constructor without args
    DataBase();

    // constructor that loads content of the file
    explicit DataBase(const char* path);

    // constructor that instantly opens the file
    explicit DataBase(const std::string& path);

    // copy-constructor
    DataBase(const DataBase& other);

    // move-contructor
    DataBase(DataBase&& other);

    // destructor
    ~DataBase();

// ***** functionality methods ***** //
    
    // return the count of elements in the data base
    size_t size() const;

    // returns a reference of a slot at the given idx
    DataType& getSlot(size_t idx);

    // returns a reference of a slot at the given idx
    DataType& operator[](size_t idx);

    // creates a new slots with given arguments
    template<typename... Args>
    void addSlot(Args... args);

    // opens file by path and saves the slots
    void load(const char* path);
        
    // opens file by path and saves the slots
    void load(const std::string& path);

    // uploads the slots into the file
    void upload(const char* path);

    // uploads the slots into the file
    void upload(const std::string& path);

// ***** for iteration ***** //

    auto begin();

    auto end();
};

// ***** constructor & destructor ***** //

template <typename DataType>
DataBase<DataType>::DataBase()
{}

template <typename DataType>
DataBase<DataType>::DataBase(const char* path)
{
    load(path);
}

template <typename DataType>
DataBase<DataType>::DataBase(const std::string& path) 
{
    load(path);
}

template <typename DataType>
DataBase<DataType>::DataBase(const DataBase& other)
: slots{other.slots}
{}

template <typename DataType>
DataBase<DataType>::DataBase(DataBase&& other)
: slots{std::move(other.slots)}
{}

template <typename DataType>
DataBase<DataType>::~DataBase() 
{}

// ***** functionality methods ***** //


template <typename DataType>
inline size_t DataBase<DataType>::size() const {
    return slots.size();
}

template <typename DataType>
inline DataType& DataBase<DataType>::getSlot(size_t idx) {
    return slots[idx];
}

template <typename DataType>
inline DataType& DataBase<DataType>::operator[](size_t idx) {
    return slots[idx];
}

template <typename DataType>
void DataBase<DataType>::load(const char* path) {
    std::ifstream file{path};
    std::string line;

    while(std::getline(file, line)) {
        size_t strLen = line.length();
        // if the string is empty
        if (strLen == 0) {
            continue;
        }
        // if the string ends with '\n' -> remove '\n'
        if (line[strLen - 1] == '\n') {
            line.resize(strLen - 1);
        }

        slots.emplace_back(line, ',');
    }

    file.close();
}

template <typename DataType>
void DataBase<DataType>::load(const std::string& path) {
    std::ifstream file{path};
    std::string line;

    while(std::getline(file, line)) {
        size_t strLen = line.length();
        // if the string is empty
        if (strLen == 0) {
            continue;
        }
        // if the string ends with '\n' -> remove '\n'
        if (line[strLen - 1] == '\n') {
            line.resize(strLen - 1);
        }

        slots.emplace_back(line, ',');
    }

    file.close();
}

template <typename DataType>
void DataBase<DataType>::upload(const char* path) {
    std::ofstream file{path};

    for (const DataType& slot: slots) {
        file << slot.parseToCsv(',') << std::endl;
    }

    file.close();
}

template <typename DataType>
void DataBase<DataType>::upload(const std::string& path) {
    std::ofstream file{path};

    for (const DataType& slot : slots) {
        file << slot.parseToCsv(',') << std::endl;
    }

    file.close();
}

// ***** for iteration ***** //


template <typename DataType>
inline auto DataBase<DataType>::begin() {
    return slots.begin();
}

template <typename DataType>
inline auto DataBase<DataType>::end() {
    return slots.end();
}

template <typename DataType>
template <typename... Args>
void DataBase<DataType>::addSlot(Args... args) {
    slots.emplace_back(args...);
}
