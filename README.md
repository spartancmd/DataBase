# Simple Data Base
## About this project
This is my implementation of a simple Data Base in C++.
Made in context of school.
Written by Deniel

## TODO:
A list of what else I should/can do:
- [] Add a TUI
- [] Add input controlls to the methods
> [!WARNING]
> The consequence of giving over invalid arguments is undefined behaviour. The responsibility is on the user

## Technologies used
In the project I use some standard C++ libraries to make it near to modern programming on C++.
Thoose are:
- vector 
- string
- fstream

Everything else is written by me:
- DataBase.hpp _(The data base itself)_
- Field.hpp _(The data structure that is worked with in DataBase)_
- FieldOp.hpp _(Offers data structure related operations such as sorting)_
- main.cpp _(With its interface)_

## How to use
In this case there's TUI (Terminal User Interface) to work with the Data Base.
For a list of commands you should type "help" as the programm started.

### Work with data base manually
The data base is made to work with .csv files.

After initializing the data base you should manually load the file contant via `db.load(filePath)`

Then you can use the methods provided by the DataBase class, that you can look-up in the header file.
