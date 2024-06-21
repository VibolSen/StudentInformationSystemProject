#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>

class Course
{
public:
    std::string courseName;
    int id;
    virtual std::string getType() const = 0;

    // Function to print header
    void printHeader()
    {
        const int width = 20; // Adjust this value as needed for proper spacing
        std::cout << std::left << std::setw(width) << "courseName"
                  << std::left << std::setw(width) << "ID"
                  << std::left << std::setw(width) << "Type"
                  << std::endl;
    }

    // Display student details without header
    virtual void display() const
    {
        const int width = 20; // Adjust this value as needed for proper spacing
        // Print the data
        std::cout << std::left << std::setw(width) << courseName
                  << std::left << std::setw(width) << id
                  << std::left << std::setw(width) << getType()
                  << std::endl;
    }
};