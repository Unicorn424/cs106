#include "linkqueue.h"
#include "testing/SimpleTest.h"

PROVIDED_TEST("Test for common operation of LinkQueue:") {
    LinkQueue<int> que;
    EXPECT_ERROR(que.dequeue());
    que.enqueue(1);
    que.enqueue(2);
    que.enqueue(3);
    que.dequeue();
    EXPECT_EQUAL(que.size(), 2);
}

PROVIDED_TEST("Test for == and deepCopy:") {
    LinkQueue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    LinkQueue<int> q2(q1);
    LinkQueue<int> q3;
    q3 = q1;
    LinkQueue<int> q4;
    EXPECT(q1 == q2);
    EXPECT(q1 == q3);
    EXPECT(q1 != q4);
}

PROVIDED_TEST("Test for output overriding:") {
    LinkQueue<int> que;
    que.enqueue(1);
    que.enqueue(2);
    que.enqueue(3);
    std::ostringstream os;
    os << que;
    std::string output = os.str();
    EXPECT_EQUAL(output, "length = 3, {1, 2, 3}");

    LinkQueue<int> q2;
    std::ostringstream os2;
    os2 << q2;
    std::string output2 = os2.str();
    EXPECT_EQUAL(output2, "length = 0, {}");

}

