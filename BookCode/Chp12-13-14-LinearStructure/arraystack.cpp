#include "testing/SimpleTest.h"
#include "arraystack.h"
#include <sstream>

PROVIDED_TEST("Test for stack arrary:") {
    ArrayStack<char> stack;
    stack.push('q');
    stack.push('m');
    EXPECT_EQUAL(stack.peek(), 'm');
    EXPECT_EQUAL(stack.pop(), 'm');
    EXPECT_EQUAL(stack.size(), 1);
    stack.pop();
    EXPECT_ERROR(stack.pop());
    stack.clear();
}

PROVIDED_TEST("Test for deep copy:") {
    ArrayStack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    ArrayStack<int> stack2(stack1);
    ArrayStack<int> stack3;
    stack3 = stack1;
    ArrayStack<int> stack4;

    EXPECT(stack1 == stack2);
    EXPECT(stack3 == stack2);
    EXPECT(stack1 != stack4);
}

PROVIDED_TEST("Test for output:") {
    ArrayStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::ostringstream os;
    os << stack;
    std::string output = os.str();

    EXPECT_EQUAL(output, "capacity: 10, size: 3  {1, 2, 3}");
}
