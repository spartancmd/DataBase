#pragma once

#include <iostream>
#include <vector>
#include <string> 

template<typename DataType>
class DataBase {
    std::vector<DataType> slots;
    const char* filePath;

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
{ }

template <typename DataType>
DataBase<DataType>::DataBase(const char* path)
: filePath{path}
{
    load(filePath);
}

template <typename DataType>
DataBase<DataType>::DataBase(const std::string& path)
: filePath{path}
{
    load(path);
}

template <typename DataType>
DataBase<DataType>::DataBase(const DataBase& other)
: slots{other.slots}, filePath{other.filePath}
{
    
}

template <typename DataType>
DataBase<DataType>::DataBase(DataBase&& other)
: slots{std::move(other.slots)}, filePath{other.filePath}
{
}

template <typename DataType>
DataBase<DataType>::~DataBase()
{
    upload(filePath);
}

// ***** functionality methods ***** //


template <typename DataType>
inline size_t DataBase<DataType>::size() const
{
    return slots.size();
}

template <typename DataType>
inline DataType& DataBase<DataType>::getSlot(size_t idx)
{
    return slots[idx];
}

template <typename DataType>
inline DataType& DataBase<DataType>::operator[](size_t idx)
{
    return slots[idx];
}

template <typename DataType>
void DataBase<DataType>::load(const char* path)
{
    
}

template <typename DataType>
void DataBase<DataType>::load(const std::string& path)
{

}

template <typename DataType>
void DataBase<DataType>::upload(const char* path)
{

}

template <typename DataType>
void DataBase<DataType>::upload(const std::string& path)
{

}

// ***** for iteration ***** //


template <typename DataType>
inline auto DataBase<DataType>::begin() {
    return slots.begin();
}

template <typename DataType>
auto DataBase<DataType>::end() {
    return slots.end();
}

template <typename DataType>
template <typename... Args>
void DataBase<DataType>::addSlot(Args... args)
{
    slots.emplace_back(args...);
}
