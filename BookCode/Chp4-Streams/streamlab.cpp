#include "streamlab.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "error.h"
using namespace std;

/* ****************************** *
 *          <iomanip>:
 * - setw(n), left, right
 * - setprecision(digit), fixed, scientific
 * - boolalpha
 * - skipws, ws
 * ****************************** */

const double PI = 3.141592653589793;
const double SPEED_OF_LIGHT = 2.99792458E+8;
const double FINE_STRUCTURE = 7.2573525E-3;

void printPrecisionTab() {
    cout << " prec |   pi   | speed of light | fine-structure" << endl;
    cout << "------+--------+----------------+----------------" << endl;
    for (int prec = 0; prec <= 6; prec += 2) {
        cout << setw(4) << prec << "  |";
        cout << " " << setw(6) << setprecision(prec) << PI << " |";
        cout << " " << setw(14) << setprecision(prec) << SPEED_OF_LIGHT << " |";
        cout << " " << setw(15) << setprecision(prec) << FINE_STRUCTURE << " |" << endl;
    }
}

void demo_iomanip() {
    cout << "Default format:" << endl << endl;
    printPrecisionTab();
    cout << endl << "Fixed format:" << fixed << endl << endl;
    printPrecisionTab();
    cout << endl << "Scientific format:" << scientific << endl << endl;
    printPrecisionTab();
}

/* ****************************** *
 *      stream classes
 * - stream.fail()
 * - stream.eof()
 * - stream.clear()
 * - stream.open(filename): filename is a c string  // file stream only
 * - stream.close()                                 // file stream only
 * - stream.get()  stream.put()
 * - stream.unget()
 * - getline(stream, str)
 * ****************************** */
// TODO: single character I/O
string promptUserForFile(ifstream& infile, string prompt = "Input file: ") {
    while (true) {
        cout << prompt;
        string filename;
        getline(cin, filename);
        infile.open(filename.c_str());
        if (!infile.fail()) {
            return filename;
        }
        infile.clear(); // reset status flags
        cout << "Unable to open that file, try again." << endl;
    }
}

void demo_iofile() {
    ifstream infile;
    promptUserForFile(infile, "Please input a filename: ");
    char ch;
    while (infile.get(ch)) {
        cout.put(ch);
    }
    infile.close();
}

// TODO: string stream
int myStringToInterger(string str) {
    istringstream is;
    int value;
    // accepts string like "123  ", "123" but not "  123"
    is >> value >> ws;

    // '>>' will triger the change of status flags of stream
    if (is.fail() || !is.eof()) {
        error("stringToInteger: Illegal integer format");
    }

    return value;
}

