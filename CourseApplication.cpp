#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "ShortCourse.cpp"
#include "FullCourse.cpp"
#include "CourseManager.cpp"
#include "DataValidInput.cpp"

class CourseApplication
{
private:
    static void displayMenu()
    {
        std::cout << "======================================" << std::endl;
        std::cout << "Course Manager Menu: (Version 1.1.0)\n";
        std::cout << "======================================" << std::endl;
        std::cout << "1. Add Course\n";
        std::cout << "2. View Course\n";
        std::cout << "3. Update Course\n";
        std::cout << "4. Delete Course\n";
        std::cout << "5. Search Courses\n";
        std::cout << "6. Sort Course\n";
        std::cout << "7. Save Data\n";
        std::cout << "8. Load Data\n";
        std::cout << "9. Back to Main Menu\n";
    }

public:
    static void run()
    {
        CourseManager manager;
        int choice;

        bool done = false;
        while (!done)
        {
            displayMenu();
            choice = DataValidInput::getIntInput("Enter your choice: ");
            std::cout << std::endl;
            try
            {
                switch (choice)
                {
                case 1:
                {

                    bool addMore = true; // Declaration of addMore
                    while (addMore)
                    {
                        std::string course;
                        int id;
                        int type;
                        std::cout << "=============" << std::endl;
                        std::cout << "1. ADD COURSE" << std::endl;
                        std::cout << "=============" << std::endl;
                        id = DataValidInput::getIntInput("Enter Course ID: ");
                        course = DataValidInput::getStringInput("Enter course name: ");
                        DataValidInput::validateId(id);
                        type = DataValidInput::getIntInput("Enter 1 Short-Course, 2 for Full-Course: ");
                        manager.addCourse(id, course, type);

                        // Ask user a question to add more or not
                        char more;
                        more = DataValidInput::getCharInput("Do you want to add more courses? (Y/N): ");
                        std::cout << std::endl;

                        if (more == 'N' || more == 'n')
                        {
                            addMore = false;
                        }
                    }

                    break;
                }
                case 2:
                    std::cout << "2. VIEW COURSE" << std::endl;
                    manager.viewCourses();
                    break;
                case 3:
                {
                    int id;
                    std::cout << "================" << std::endl;
                    std::cout << "3. UPDATE COURSE" << std::endl;
                    std::cout << "================" << std::endl;
                    std::cout << "Which course do you want to update?\n";
                    id = DataValidInput::getIntInput("Enter Course ID: ");
                    DataValidInput::validateId(id);

                    manager.updateCourse(id);
                    break;
                }
                case 4:
                {
                    int id;
                    std::cout << "================" << std::endl;
                    std::cout << "4. DELETE COURSE" << std::endl;
                    std::cout << "================" << std::endl;
                    std::cout << "Which course do you want to delete?\n";
                    id = DataValidInput::getIntInput("Enter Course ID: ");
                    DataValidInput::validateId(id);

                    manager.deleteCourse(id);
                    break;
                }
                case 5:
                {
                    int id;
                    std::cout << "================" << std::endl;
                    std::cout << "5. SEARCH COURSE" << std::endl;
                    std::cout << "================" << std::endl;
                    id = DataValidInput::getIntInput("Enter courses ID: ");
                    DataValidInput::validateId(id);

                    manager.searchCourse(id);
                    break;
                }
                case 6:
                {
                    std::cout << "===============" << std::endl;
                    std::cout << "6. SORT COURSES" << std::endl;
                    std::cout << "===============" << std::endl;
                    manager.sortCourses();
                    break;
                }
                case 7:
                {
                    std::cout << "===============" << std::endl;
                    std::cout << "7. SAVE COURSES" << std::endl;
                    std::cout << "===============" << std::endl;
                    manager.saveToFile("courses.txt");
                    std::cout << "Data saved successfully" << std::endl;
                    break;
                }
                case 8:
                {
                    std::cout << "===============" << std::endl;
                    std::cout << "8. LOAD COURSE" << std::endl;
                    std::cout << "===============" << std::endl;
                    manager.loadFromFile("courses.txt");
                    std::cout << std::endl;
                    break;
                }

                case 9:
                    done = true;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
};
