#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "Course.cpp"

class ShortCourse : public Course
{
public:
    ShortCourse(const std::string &courseName, int id)
    {
        this->courseName = courseName;
        this->id = id;
    }
    std::string getType() const override
    {
        return "Short-Course";
    }
};
