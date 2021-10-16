#include "linkstack.h"
#include "testing/SimpleTest.h"

PROVIDED_TEST("Test for stack arrary:") {
    LinkStack<char> stack;
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
    LinkStack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    LinkStack<int> stack2(stack1);
    LinkStack<int> stack3 = stack1;
    LinkStack<int> stack4;

    EXPECT(stack1 == stack2);
    EXPECT(stack3 == stack2);
    EXPECT(stack1 != stack4);
}


// Can't be true as allocated address in heap will change.
PROVIDED_TEST("Test for output:") {
    LinkStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::ostringstream os;
    os << stack;
    std::string output = os.str();

    // Always fail since allocated memory will change.
//    EXPECT_EQUAL(output, "output = count: 3, top: 0x7fd406ce3140; {data: 3, next: 0x7fd406cf39b0, data: 2, next: 0x7fd406cdc6a0, data: 1, next: 0x0}");
}
