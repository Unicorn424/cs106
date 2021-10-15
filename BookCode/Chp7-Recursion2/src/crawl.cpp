#include "crawl.h"
#include "filelib.h"
#include "vector.h"

/*
 * Function: crawl
 * ------------------------------------
 * The function will crawl a given file/directory and output directory tree if there is.
 *
 * @param filename: the name of file to be crawled.
 * @param indentation: format output with indentation.
 *
 * Base case:
 *      if it's a file, then output its name.
 * Recursion:
 *      if it is a directory, then output its name and crawl each file under that directory.
 *
 * void crawlHelper(const string& filename, const string& indentation)
 *                                            ^
 * Why 'const string' works here, that's a reference?
 * Answer: each indentation is independable in its function stack.
 */
void crawlHelper(const string& filename, const string& indentation) {
    if (isFile(filename)) {
        cout << indentation << getTail(filename) << endl;
    }
    else {
        Vector<string> files = listDirectory(filename);
        cout << indentation << getTail(filename) << ":" << endl;
        for (string& file : files) {
            crawlHelper(filename + "/" + file, indentation + "    ");
        }
    }
}

void crawl(const string& filename) {
    crawlHelper(filename, "");
}

int main_crawl() {
    string filename = "/Users/minzhiqu/Desktop/Study/MIT/cs106/BookCode/Chp7-Recursion2";
    crawl(filename);

    return 0;
}
