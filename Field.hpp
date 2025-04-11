#pragma once

#include <string>
#include <vector>

// after following schema: id, first name, second name, class, age
class Field {
    unsigned id;
    std::string firstName;
    std::string secondName;
    std::string schoolClass;
    short age;

    // returns the string without outern quotation marks(=symbol ")
    std::string removeQM(const std::string& str) const;
public:
// ******* constructors and destructors ******* //

    // Constructor without arguments.
    // Creates an object of the class without initialized fields
    Field();

    // Constructor with arguments.
    // Creates an object of the class with initialized fields
    explicit Field(unsigned id_, const std::string& firstName_, const std::string& secondName_, const std::string& schoolClass_, short age_);

    // .csv parse constructor.
    // Creates an object by a string in .csv format
    explicit Field(const std::string& str, const char sep = ',');

    // Move-constructor (for the case if an rvalue of this class assigned)
    Field(Field&& other);

    // Copy-constructor (for the case if an lvalue of this class assigned)
    Field(const Field& other);

    // Destructor
    ~Field();

    // parses given string (in .csv format) and sets the object variables.
    // str should have this form: id,"first name","second name","schoolclass", age
    void parseFromCsv(const std::string& str, const char sep = ',');

    // returns the stored data as string seperated by ',' in this format: "id,"firstname", "secondname", "schoolclass", age"
    // With '\n' at the end
    std::string parseToCsv(const char sep = ',') const;

    // returns headers for table in csv-format
    static std::string headerCsv(const char sep = ' ');

// ******* get operators ******* //

    static std::string getHeadLine(const char sep = '\t');

    // returns a line with elements
    std::string getRowLine(const char sep = '\t') const;

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

std::string Field::removeQM(const std::string &str) const {
    std::string res;

    for (size_t i = 1; i < str.length() - 1; i++) {
        res += str[i];
    }    
    
    return res;
}

// ******* constructors and destructors ******* //



Field::Field()
{}

Field::Field(unsigned id_, const std::string& firstName_, const std::string& secondName_, const std::string& schoolClass_, short age_)
: id{id_}, firstName{firstName_}, secondName{secondName_}, schoolClass{schoolClass_}, age{age_} 
{}

Field::Field(const std::string& str, const char sep)
{
    parseFromCsv(str, sep);
}

Field::Field(Field &&other)
{
    id = other.id;
    firstName = std::move(other.firstName);
    secondName = std::move(other.secondName);
    schoolClass = std::move(other.schoolClass);
    age = other.age;
}

Field::Field(const Field& other)
{
    id = other.id;
    firstName = other.firstName;
    secondName = other.secondName;
    schoolClass = other.schoolClass;
    age = other.age;
}

Field::~Field()
{}

void Field::parseFromCsv(const std::string& str, const char sep) {
    std::vector<std::string> elements; // should contain the elements that are in str

    size_t i = 0;
    size_t n = str.length();
    bool inQuotes = false;

    // append the the elements in the string to the vector elements
    while (i < n) {
        std::string cur;
        
        // iterate through the element until line break or next seperator. If there're quotes, they'll be ignored.
        while(i < n && (str[i] != sep || inQuotes) && str[i] != '\n') {
            if (str[i] == '\"') {
                inQuotes = !inQuotes; // inverting the bool-val of inQuotes
            }
            cur += str[i];
            i++;
        }

        elements.push_back(cur);

        i++;
    }

    // the extracted elements are put into our class variables
    id = std::stoi(elements[0]);
    firstName = removeQM(elements[1]);
    secondName = removeQM(elements[2]);
    schoolClass = removeQM(elements[3]);
    age = std::stoi(elements[4]);
}

inline std::string Field::parseToCsv(const char sep) const {
    return std::to_string(id) + sep + '\"' + firstName + '\"' + sep + '\"' +  secondName + '\"' + sep + '\"' + schoolClass + '\"' + sep + std::to_string(age) + '\n';
}

inline std::string Field::headerCsv(const char sep) {
    return std::string{"Id"} + sep + "First name" + sep + "Second name" + sep + "School class" + sep +  "Age" + '\n';
}



// ******* get operators ******* //

inline std::string Field::getHeadLine(const char sep)
{
    return std::string{"Id"} + sep + "First name" + sep + "Second name" + sep + "School class" + sep + "Age";
}

inline std::string Field::getRowLine(const char sep) const
{
    return std::to_string(id) + sep + firstName + sep +  secondName + sep + schoolClass + sep + std::to_string(age);
}

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
    
    id = other.id;
    firstName = other.firstName;
    secondName = other.secondName;
    schoolClass = other.schoolClass;
    age = other.age;

    return *this;
}

Field& Field::operator=(Field&& other) {
    id = other.id;
    firstName = std::move(other.firstName);
    secondName = std::move(other.secondName);
    schoolClass = std::move(other.schoolClass);
    age = other.age;

    return *this;
}