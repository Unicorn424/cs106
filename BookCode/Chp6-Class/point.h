#ifndef POINT_H
#define POINT_H
#include <string>
#include <iostream>

class Point {
public:
    Point();
    Point(int x, int y);

    int getX();
    int getY();
    std::string toString();

    // if we want ot customize the output of the class
    // ex>
    //   using:      cout << "pt = " << pt << endl;
    //   instead of: cout << "pt = " << pt.toString() << endl;

    friend bool operator==(Point lhs, Point rhs);

private:
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& os, Point pt);
bool operator==(Point lhs, Point rhs);

#endif // POINT_H
