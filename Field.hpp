#pragma once

#include <string>

// after following schema: id, first name, second name, class, age
class Field {
    unsigned id;
    std::string firstName;
    std::string secondName;
    std::string schoolClass;
    short age;

public:
// ******* constructors and destructors ******* //

    // Constructor without arguments.
    // Creates an object of the class without initialized fields
    Field();

    // Constructor with arguments.
    // Creates an object of the class with initialized fields
    explicit Field(unsigned id_, const std::string& firstName_, const std::string& secondName_, const std::string& schoolClass_, short age_);

    // Move-constructor (for the case if an rvalue of this class assigned)
    Field(Field&& other);

    // Copy-constructor (for the case if an lvalue of this class assigned)
    Field(const Field& other);

    // Destructor
    ~Field();

// ******* get operators ******* //

    // return the id of the current field
    unsigned get_id() const;

    // returns the first name of the current field
    const char* get_firstName() const;

    // return the second name of the current field
    const char* get_secondName() const;

    // return the class of the current field
    const char* get_schoolClass() const;

    // return the age of the current field
    short get_age() const;

// ******* set operators ******* //

    // sets id to given argument
    int set_id(unsigned);

    // sets first name to given argument (for the case if natural c-string was given)
    int set_firstName(const char*);

    // sets first name to given argument (for the case if the argument has type std::string was given)
    int set_firstName(const std::string&);

    // sets second name to given argument (for the case if natural c-string was given)
    int set_secondName(const char*); 

    // sets second name to given argument (for the case if the argument has type std::string was given)
    int set_secondName(const std::string&); 

    // sets school class to given argument (for the case if natural c-string was given)
    int set_schoolClass(const char*); 

    // sets school class to given argument (for the case if the argument has type std::string was given)
    int set_schoolClass(const std::string&); 

    // sets age to given argument
    int set_age(short);

// **** operators **** //

    Field& operator=(const Field& other);

    Field& operator=(Field&& other);
};

// ******************************* //
//    DEFINITIONS OF METHODS       //
// ******************************* // 

// ******* constructors and destructors ******* //

Field::Field() 
{}

Field::Field(unsigned id_, const std::string& firstName_, const std::string& secondName_, const std::string& schoolClass_, short age_)
: id{id_}, firstName{firstName_}, secondName{secondName_}, schoolClass{schoolClass_}, age{age_} 
{}

Field::Field(Field&& other)
{
    id = other.id;
    firstName = other.firstName;
    secondName = other.secondName;
    schoolClass = other.schoolClass;
    age = other.age;
}

Field::Field(const Field& other)
{
    id = other.id;
    firstName = std::move(other.firstName);
    secondName = std::move(other.secondName);
    schoolClass = std::move(other.schoolClass);
    age = other.age;
}

Field::~Field()
{}

// ******* get operators ******* //

unsigned Field::get_id() const {
    return id;
}

const char* Field::get_firstName() const {
    return firstName.c_str(); // c_str return the content as const char*
}

const char* Field::get_secondName() const {
    return secondName.c_str(); // c_str return the content as const char*
}

const char* Field::get_schoolClass() const {
    return schoolClass.c_str(); // c_str return the content as const char*
}

short Field::get_age() const {
    return age;
}

// ******* set operators ******* //

int Field::set_id(unsigned newVal) {
    id = newVal;
    return 0;
}

int Field::set_firstName(const char* newVal) {
    firstName = newVal;
    return 0;
}

int Field::set_firstName(const std::string& newVal) {
    firstName = newVal;
    return 0;
}

int Field::set_secondName(const char* newVal) {
    secondName = newVal;
    return 0;
}

int Field::set_secondName(const std::string& newVal) {
    secondName = newVal;
    return 0;
}

int Field::set_schoolClass(const char* newVal) {
    schoolClass = newVal;
    return 0;
}

int Field::set_schoolClass(const std::string& newVal) {
    schoolClass = newVal;
    return 0;
}

int Field::set_age(short newVal) {
    age = newVal;
    return 0;
}


// **** operators **** //

Field& Field::operator=(const Field& other) {
    unsigned id = other.id;
    std::string firstName = other.firstName;
    std::string secondName = other.secondName;
    std::string schoolClass = other.schoolClass;
    short age = other.age;

    return *this;
}

Field& Field::operator=(Field&& other) {
    unsigned id = other.id;
    std::string firstName = std::move(other.firstName);
    std::string secondName = std::move(other.secondName);
    std::string schoolClass = std::move(other.schoolClass);
    short age = other.age;

    return *this;
}