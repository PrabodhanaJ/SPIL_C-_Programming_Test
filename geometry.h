#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <string>

struct Point {
    double x, y;
};

std::vector<Point> parsePoints(const std::string& pointsStr);
int orientation(Point p, Point q, Point r);
bool onSegment(Point p, Point q, Point r);
bool doIntersect(Point p1, Point q1, Point p2, Point q2);
bool doesOverlap(const std::vector<Point>& points);
double calculateArea(const std::vector<Point>& points);

#endif // GEOMETRY_H
