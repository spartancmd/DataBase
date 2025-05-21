#pragma once

#include <fstream>
#include <vector>
#include <string> 

template<typename DataType>
class DataBase {
    std::vector<DataType> slots; // containes the fields
    bool stateFileLoaded = false;    // the state if the file is already loaded
    std::string filePath;     // contains the filepath that we've loaded from

    // static void swap(DataType& a, DataType& b);

    // creates the file, if it doesn't exist yet
    static void createFile(const std::string& filePath);
    
public:
// ***** constructor & destructor ***** //

    DataBase();

    explicit DataBase(const std::string& path);

    DataBase(const DataBase& other);

    DataBase(DataBase&& other);

    ~DataBase();

// ***** functionality methods ***** //
    
    size_t size() const;

    DataType& slot(size_t idx);

    const DataType& slot(size_t idx) const;

    std::string getFilePath() const;

    bool fileLoaded() const;

    DataType& operator[](size_t idx);

    const DataType& operator[](size_t idx) const;

    // creates a new slots with given init arguments
    template<typename... Args>
    void addSlot(Args... args);

    // copies the already existing obj of DataType to a new slot in data base
    void addSlot(const DataType& other);

    void removeSlot(size_t idx);
        
    // opens file by path and saves the slots
    void load(const std::string& path);

    // saves slots into the file, we've loaded from
    void upload() const;

    // saves the slots into the file
    void upload(const std::string& path) const;

// ***** for iteration ***** //

    auto begin();

    auto begin() const;

    auto end();

    auto end() const;
};

// template <typename DataType>
// void DataBase<DataType>::swap(DataType& a, DataType& b) {
//     DataType tmp = a;
//     a = b;
//     b = tmp;
// }

template <typename DataType>
void DataBase<DataType>::createFile(const std::string& filePath) {
    std::ofstream(filePath, std::ios_base::app).close();
}

// ***** constructor & destructor ***** //



template <typename DataType>
DataBase<DataType>::DataBase()
{}

template <typename DataType>
DataBase<DataType>::DataBase(const std::string& path) {
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
DataBase<DataType>::~DataBase() {
    if (stateFileLoaded) {
        upload(filePath);
    }
}

// ***** functionality methods ***** //


template <typename DataType>
size_t DataBase<DataType>::size() const {
    return slots.size();
}

template <typename DataType>
DataType& DataBase<DataType>::slot(size_t idx) {
    return slots[idx];
}

template <typename DataType>
const DataType& DataBase<DataType>::slot(size_t idx) const {
    return slots[idx];
}

template <typename DataType>
std::string DataBase<DataType>::getFilePath() const {
    return filePath;
}

template <typename DataType>
bool DataBase<DataType>::fileLoaded() const {
    return stateFileLoaded;
}

template <typename DataType>
DataType& DataBase<DataType>::operator[](size_t idx) {
    return slots[idx];
}

template <typename DataType>
const DataType& DataBase<DataType>::operator[](size_t idx) const {
    return slots[idx];
}

template <typename DataType>
void DataBase<DataType>::load(const std::string& path) {
    createFile(path);
    std::ifstream file{path};
    std::string line;

    while(std::getline(file, line)) {
        
        if (line.empty()) {
            continue;
        }
        if (line.back() == '\n') {
            line.pop_back();
        }

        slots.emplace_back(line, ','); // why ','? It's a parameter sep in constructor of struct Field
    }

    file.close();
    stateFileLoaded = true;
    filePath = path;
}

template <typename DataType>
void DataBase<DataType>::upload() const {
    std::ofstream file{filePath};

    for (const DataType& slot: slots) {
        file << slot.parseToCsv(',');
    }

    file.close();
}

template <typename DataType>
void DataBase<DataType>::upload(const std::string& path) const {
    std::ofstream file{path};

    for (const DataType& slot: slots) {
        file << slot.parseToCsv(',');
    }

    file.close();
}

// ***** for iteration ***** //


template <typename DataType>
auto DataBase<DataType>::begin() {
    return slots.begin();
}

template <typename DataType>
auto DataBase<DataType>::begin() const {
    return slots.begin();
}

template <typename DataType>
auto DataBase<DataType>::end() {
    return slots.end();
}

template <typename DataType>
auto DataBase<DataType>::end() const {
    return slots.end();
}

template <typename DataType>
template <typename... Args>
void DataBase<DataType>::addSlot(Args... args) {
    slots.emplace_back(args...);
}

template<typename DataType>
void DataBase<DataType>::addSlot(const DataType& other) {
    slots.push_back(other);
}

template <typename DataType>
void DataBase<DataType>::removeSlot(size_t idx) {
    slots.erase(slots.begin() + idx);
}
