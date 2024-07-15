#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "geometry.h"

void processShapes(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    // check file is opened
    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open file!" << std::endl;
        return; // stop program
    }

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);

        // dividing each line into to variables
        std::string shapeName, pointsStr; 
        std::getline(lineStream, shapeName, ',');
        std::getline(lineStream, pointsStr);

        std::cout << "\n##########################################################";
        std::cout << "\nShape Name: " << shapeName << std::endl;
        std::cout << "Points: " << pointsStr << std::endl;

        // store each point in a vector
        std::vector<Point> points = parsePoints(pointsStr);

        if (doesOverlap(points)) {
            std::cout << shapeName << ": Overlapping points, invalid shape (not a polygon)!!!" << std::endl; //
        }
        else {
            double area = calculateArea(points);
            std::cout << shapeName << ": Area = " << area << std::endl;
        }
    }
}

// main function
int main() {
    const std::string filename = "data.txt";
    processShapes(filename);
    return 0;
}
