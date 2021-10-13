#include "point.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
#include <sstream>

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

int Point::getX() {
    return this->x;
}

int Point::getY() {
    return this->y;
}

std::string Point::toString() {
    return "(" + integerToString(x) + ", " + integerToString(y) + ")";
}

std::ostream& operator<<(std::ostream& os, Point pt) {
    return os << pt.toString();
}

// I'm the friend of the class Point
bool operator==(Point lhs, Point rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!=(Point lhs, Point rhs) {
    return !(lhs==rhs);
}

PROVIDED_TEST("Test for operator overriding:") {
    Point pt1(1, 2);
    Point pt2(1, 3);
    Point pt3;      // default constructor
    Point pt4(0, 0);

    std::stringstream ss;
    ss << "pt1 = " << pt1;
    std::string output = ss.str();

    EXPECT(pt1!=pt2);
    EXPECT(pt3==pt4);
    EXPECT_EQUAL(output, "pt1 = (1, 2)");
}
