#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Course {
    std::string number;
    std::string title;
    std::vector<std::string> prerequisites;
};

std::vector<Course> courses; // Global vector to hold the course data

// Function that loads course data from a CSV file
void loadDataStructure(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cout << "Failed to open the file: " << fileName << std::endl;
        return;
    }

    std::string line;
    std::getline(inputFile, line); // Skip the header line

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string courseNumber, courseTitle, prerequisites;

        // Parse the CSV line and extract course details
        std::getline(ss, courseNumber, ',');
        std::getline(ss, courseTitle, ',');
        std::getline(ss, prerequisites, ',');

        // Split prerequisites string into individual course codes
        std::vector<std::string> prerequisiteCourses;
        std::stringstream prerequisiteStream(prerequisites);
        std::string prerequisite;
        while (std::getline(prerequisiteStream, prerequisite, ' ')) {
            prerequisiteCourses.push_back(prerequisite);
        }

        // Create a new Course object and add it to the vector
        courses.push_back({ courseNumber, courseTitle, prerequisiteCourses });
    }

    inputFile.close();

    std::cout << "Data loaded successfully!" << std::endl;
}

// Function to print the list of all courses
void printCourseList() {
    if (courses.empty()) {
        std::cout << "No courses found. Please load data first." << std::endl;
        return;
    }

    std::cout << "Course List:" << std::endl;
    for (const auto& course : courses) {
        std::cout << course.number << " - " << course.title << std::endl;
    }
}

// Function to print information about a specific course
void printCourseInformation(const std::string& courseNumber) {
    if (courses.empty()) {
        std::cout << "No courses found. Please load data first." << std::endl;
        return;
    }

    auto it = std::find_if(courses.begin(), courses.end(), [&courseNumber](const Course& course) {
        return course.number == courseNumber;
        });

    if (it == courses.end()) {
        std::cout << "Course not found." << std::endl;
        return;
    }

    const Course& course = *it;

    std::cout << "Course Information:" << std::endl;
    std::cout << "Course Number: " << course.number << std::endl;
    std::cout << "Course Title: " << course.title << std::endl;

    if (course.prerequisites.empty()) {
        std::cout << "No prerequisites." << std::endl;
    }
    else {
        std::cout << "Prerequisites: ";
        for (const auto& prerequisite : course.prerequisites) {
            std::cout << prerequisite << " ";
        }
        std::cout << std::endl;
    }
}

// Function to display the menu options
void displayMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Load Data Structure" << std::endl;
    std::cout << "2. Print Course List" << std::endl;
    std::cout << "3. Print Course Information" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice (1-4): ";
}

int main() {
    std::string fileName = "ABCU_Advising_Program_Input.csv";
    loadDataStructure(fileName);

    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            loadDataStructure(fileName);
            break;
        case 2:
            printCourseList();
            break;
        case 3:
        {
            std::string courseNumber;
            std::cout << "Enter the course number: ";
            std::cin >> courseNumber;
            printCourseInformation(courseNumber);
            break;
        }
        case 4:
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            return 0;
        default:
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
        }
    }

    return 0;
}