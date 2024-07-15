#include "geometry.h"
#include <algorithm> // for std::max and std::min
#include <cmath>
#include <sstream>

std::vector<Point> parsePoints(const std::string& pointsStr) {
    std::vector<Point> points;
    std::string trimmed = pointsStr.substr(1, pointsStr.size() - 2); // Remove the square brackets
    std::istringstream ss(trimmed);
    std::string pointStr;

    while (std::getline(ss, pointStr, ')')) { 
        if (pointStr.empty()) continue;
        if (pointStr[0] == ',') pointStr = pointStr.substr(1); // Remove first comma if present
        pointStr = pointStr.substr(1); // Remove the first '('

        std::istringstream pointStream(pointStr);
        std::string xCoordinate, yCoordinate;
        std::getline(pointStream, xCoordinate, ',');
        std::getline(pointStream, yCoordinate);

        // saving seperated x & y coordinates to vextor
        Point point;
        point.x = std::stod(xCoordinate);
        point.y = std::stod(yCoordinate);
        points.push_back(point);
    }

    return points;
}

// Helper function to check the orientation of three points (needed for intersection test)
int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (std::abs(val) < 1e-9) return 0;  // collinear
    return (val > 0) ? 1 : 2;  // clock or counterclockwise
}

// Helper function to check if point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r) {
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y)) {
        return true;
    }
    return false;
}

// Function to check if two segments p1q1 and p2q2 intersect
bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    // Find the four orientations needed for the general and special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4) return true;

    // Special cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;  // Doesn't fall in any of the above cases
}

// Function to check whether polygon is overlapping
bool doesOverlap(const std::vector<Point>& points) {
    int n = points.size();
    if (n < 3) return true;  // number of points must be >= 3

    // Check all pairs of edges for intersection, excluding adjacent edges
    for (int i = 0; i < n; i++) {
        for (int j = i + 2; j < n; j++) {
            // Avoid checking edges that share a vertex
            if ((i == 0 && j == n - 1) || (i + 1 == j)) continue;
            if (doIntersect(points[i], points[(i + 1) % n], points[j], points[(j + 1) % n])) {
                return true; // polygon overlaps
            }
        }
    }

    return false;  // No overlaps
}

// Function to calculate the area of a polygon using the Shoelace formula
double calculateArea(const std::vector<Point>& points) {
    int n = points.size();
    double area = 0.0;

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += points[i].x * points[j].y;
        area -= points[j].x * points[i].y;
    }

    area = std::abs(area) / 2.0;
    return area;
}
