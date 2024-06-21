#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "PartTimeStudent.cpp"
#include "FullTimeStudent.cpp"
#include "Student.cpp"
#include "DataValidInput.cpp"

class StudentRepository
{
    virtual void addStudent(int id, std::string name, int type) = 0;

    virtual void updateStudent(int id) = 0;

    virtual void deleteStudent(int id) = 0;

    virtual void viewStudents() = 0;

    virtual void saveToFile(const std::string &filename) const = 0;

    virtual void loadFromFile(const std::string &filename) = 0;
};