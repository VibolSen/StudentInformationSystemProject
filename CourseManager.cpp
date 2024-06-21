#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "ShortCourse.cpp"
#include "FullCourse.cpp"
#include "Course.cpp"
#include "DataValidInput.cpp"
#include "CourseRepository.cpp"

class CourseManager : public CourseRepository
{
private:
    std::vector<Course *> courses;

    Course *findCourseById(int id)
    {
        auto it = std::find_if(courses.begin(), courses.end(), [id](Course *course)
                               { return course->id == id; });
        return (it != courses.end()) ? *it : nullptr;
    }

    //  Function to print header
    void printHeader() const
    {
        const int width = 20; // Adjust this value as needed for proper spacing
        std::cout << std::left << std::setw(width) << "Course Name"
                  << std::left << std::setw(width) << "ID"
                  << std::left << std::setw(width) << "Type"
                  << std::endl;
    }

public:
    ~CourseManager()
    {
        for (auto course : courses)
        {
            delete course;
        }
    }

    void addCourse(int id, std::string courseName, int type)
    {

        if (type == 1)
        {
            courses.push_back(new ShortCourse(courseName, id));
        }
        else if (type == 2)
        {
            courses.push_back(new FullCourse(courseName, id));
        }
        else
        {
            throw std::invalid_argument("Invalid course type.");
        }

        std::cout << "Course added successfully.\n";
        std::cout << std::endl;
    }

    void updateCourse(int id)
    {
        Course *course = findCourseById(id);
        if (course == nullptr)
        {
            throw std::invalid_argument("Course not found");
            return;
        }

        printHeader();
        course->display();
        std::cout << std::endl;
        std::cout << "Which type do you want to update in course?\n";
        std::cout << "=============================================" << std::endl;
        std::cout << "1. Update ID\n";
        std::cout << "2. Update course Name\n";
        std::cout << "3. Update type\n";
        std::cout << "Please choose option you want to update 1-3: ";
        std::cout << std::endl;
        int choice = DataValidInput::getIntInput("");

        switch (choice)
        {
        case 1:
        {
            int newId;
            std::cout << "1. UPDATE ID\n";
            std::cout << "==============" << std::endl;
            std::cout << "Enter new ID: ";
            newId = DataValidInput::getIntInput("");
            DataValidInput::validateId(newId);
            course->id = newId;
            break;
        }
        case 2:
        {
            std::string newCourse;
            std::cout << "2. UPDATE COURSE NAME\n";
            std::cout << "=======================" << std::endl;
            std::cout << "Enter new course name: ";
            newCourse = DataValidInput::getStringInput("");
            course->courseName = newCourse;
            break;
        }
        case 3:
        {
            int newType;
            std::cout << "3. UPDATE TYPE\n";
            std::cout << "================" << std::endl;
            std::cout << "Enter 1 for Part-Time, 2 for Full-Time: ";
            newType = DataValidInput::getIntInput("");

            if (newType == 1)
            {
                course = new ShortCourse(course->courseName, course->id);
            }
            else if (newType == 2)
            {
                course = new FullCourse(course->courseName, course->id);
            }
            else
            {
                throw std::invalid_argument("Invalid course type.");
            }
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
            break;
        }

        std::cout << "Course updated successfully.\n";
    }

    void deleteCourse(int id)
    {

        Course *course = findCourseById(id);
        if (course == nullptr)
        {
            throw std::invalid_argument("Course not found");
        }

        printHeader();
        course->display(); // Display student details before confirming deletion
        std::cout << std::endl;
        char confirm = DataValidInput::getCharInput("Are you sure you want to delete this course? (Y/N): ");

        if (confirm == 'Y' || confirm == 'y')
        {
            auto it = std::remove_if(courses.begin(), courses.end(), [id](Course *course)
                                     {
            if (course->id == id) {
                delete course;
                return true;
            }
            return false; });

            if (it != courses.end())
            {
                courses.erase(it, courses.end());
                std::cout << "Course has been successfully deleted.\n";
            }
            else
            {
                throw std::invalid_argument("Course not found");
            }
        }
        else
        {
            std::cout << "Delete courset has been canceled.\n";
        }
    }

    void viewCourses()
    {
        if (courses.empty())
        {
            throw std::invalid_argument("No course available");
            return;
        }

        printHeader(); // Print the header once
        for (const auto &course : courses)
        {
            course->display();
        }
    }

    void searchCourse(int id)
    {
        Course *course = findCourseById(id);
        if (course)
        {
            printHeader();
            course->display();
        }
        else
        {
            throw std::runtime_error("Course not found");
        }
    }

    void sortCourses()
    {
        std::cout << "Sort courses by:\n";
        std::cout << "1. ID\n";
        std::cout << "2. Name Course\n";
        int choice = DataValidInput::getIntInput("Enter your choice: ");
        std::cout << std::endl;

        switch (choice)
        {
        case 1:
            std::sort(courses.begin(), courses.end(), [](Course *a, Course *b)
                      { return a->id < b->id; });
            std::cout << "Courses sorted by ID.\n";
            break;
        case 2:
            std::sort(courses.begin(), courses.end(), [](Course *a, Course *b)
                      { return a->courseName < b->courseName; });
            std::cout << "Courses sorted by name.\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }

    void saveToFile(const std::string &filename) const
    {
        std::ofstream outFile(filename);
        if (!outFile)
        {
            throw std::runtime_error("Cannot open file for writing");
        }
        for (const auto &course : courses)
        {
            outFile << course->id << " " << course->courseName << " " << course->getType() << std::endl;
        }
    }

    void loadFromFile(const std::string &filename)
    {
        std::ifstream inFile(filename);
        if (!inFile)
        {
            throw std::runtime_error("Cannot open file for reading");
        }

        courses.clear();
        int id;
        std::string name, type;
        bool hasCourses = false;

        while (inFile >> id >> name >> type)
        {
            if (type == "Short-Course")
            {
                courses.push_back(new ShortCourse(name, id));
                hasCourses = true;
            }
            else if (type == "Full-Course")
            {
                courses.push_back(new FullCourse(name, id));
                hasCourses = true;
            }
            else
            {
                throw std::runtime_error("Unknown course type in file");
            }
        }

        if (!hasCourses)
        {
            std::cout << "No courses available !\n";
        }
        else
        {
            std::cout << "List of all Courses:\n\n";
            printHeader();
            for (const auto &course : courses)
            {
                course->display();
            }
            std::cout << std::endl;
            std::cout << "Data loaded successfully" << std::endl;
        }
    }
};