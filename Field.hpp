#pragma once

#include <string>
#include <vector>
#include <string_view> // view string without copying 

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

    Field();

    explicit Field(unsigned id_, const std::string& firstName_, const std::string& secondName_, const std::string& schoolClass_, short age_);

    // .csv parse constructor.
    // Creates an object by a string in .csv format
    explicit Field(const std::string& str, const char sep = ',');

    Field(Field&& other);

    Field(const Field& other);

    ~Field();

    // parses given string (in .csv format) and sets the object variables.
    // str should have this form: id,"first name","second name","schoolclass", age
    void parseFromCsv(const std::string& str, const char sep = ',');

    // returns the stored data as string seperated by ',' in this format: "id,"firstname","secondname","schoolclass",age"
    // With '\n' at the end
    std::string parseToCsv(const char sep = ',') const;

    // returns headers for table in csv-format
    static std::string headerCsv(const char sep = ' ');

// ******* get operators ******* //

    // returns the headline as std::string
    static std::string getHeadLine(const char sep = '\t');

    // return the headlines as a vector of std::strings
    static std::vector<std::string> getHeadVector();

    // returns the elements as a line
    std::string getRowLine(const char sep = '\t') const;

    
    unsigned getId() const;

    const char* getFirstName() const;

    const char* getSecondName() const;

    const char* getSchoolClass() const;

    short getAge() const;

// ******* set operators ******* //

    int setId(unsigned);

    int setFirstName(const std::string&);

    int setSecondName(const std::string&); 

    int setSchoolClass(const std::string&); 

    int setAge(short);

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

std::string Field::parseToCsv(const char sep) const {
    return std::to_string(id) + sep + '\"' + firstName + '\"' + sep + '\"' +  secondName + '\"' + sep + '\"' + schoolClass + '\"' + sep + std::to_string(age) + '\n';
}

std::string Field::headerCsv(const char sep) {
    return std::string{"Id"} + sep + "First name" + sep + "Second name" + sep + "School class" + sep +  "Age" + '\n';
}



// ******* get operators ******* //

std::string Field::getHeadLine(const char sep) {
    return std::string{"Id"} + sep + "First name" + sep + "Second name" + sep + "School class" + sep + "Age";
}

std::vector<std::string> Field::getHeadVector() {
    return {"Id", "First name", "Second name", "School class", "Age"};
}

std::string Field::getRowLine(const char sep) const {
    return std::to_string(id) + sep + firstName + sep +  secondName + sep + schoolClass + sep + std::to_string(age);
}

unsigned Field::getId() const {
    return id;
}

const char* Field::getFirstName() const {
    return firstName.c_str(); 
}

const char* Field::getSecondName() const {
    return secondName.c_str();
}

const char* Field::getSchoolClass() const {
    return schoolClass.c_str(); 
}

short Field::getAge() const {
    return age;
}

// ******* set operators ******* //

int Field::setId(unsigned newVal) {
    id = newVal;
    return 0;
}

int Field::setFirstName(const std::string& newVal) {
    firstName = newVal;
    return 0;
}

int Field::setSecondName(const std::string& newVal) {
    secondName = newVal;
    return 0;
}

int Field::setSchoolClass(const std::string& newVal) {
    schoolClass = newVal;
    return 0;
}

int Field::setAge(short newVal) {
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