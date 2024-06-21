#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "ShortCourse.cpp"
#include "FullCourse.cpp"
#include "Course.cpp"
#include "DataValidInput.cpp"

class CourseRepository{
    virtual void addCourse(int id, std::string subjects, int type) = 0;

    virtual void updateCourse(int id) = 0;

    virtual void deleteCourse(int id) = 0;

    virtual void viewCourses() = 0;
};