#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "Student.cpp"


class PartTimeStudent : public Student {
public:
    PartTimeStudent(const std::string& name, int id) {
        this->name = name;
        this->id = id;
    }
    std::string getType() const override {
        return "Part-Time";
    }
};

