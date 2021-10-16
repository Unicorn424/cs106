#include "cqueue.h"
#include "testing/SimpleTest.h"

PROVIDED_TEST("Test for common operation of CQueue:") {
    CQueue<int> que;
    EXPECT_ERROR(que.dequeue());
    que.enqueue(1);
    que.enqueue(2);
    que.enqueue(3);
    EXPECT_EQUAL(que.size(), 3);
    que.dequeue();
    EXPECT_EQUAL(que.size(), 2);
    que.clear();
    EXPECT_ERROR(que.dequeue());
}

PROVIDED_TEST("Test for operator overriding:") {
    CQueue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    CQueue<int> q2(q1);
    CQueue<int> q3;
    q3 = q1;
    CQueue<int> q4;
    EXPECT(q1 == q2);
    EXPECT(q1 == q3);
    EXPECT(q1 != q4);
}

PROVIDED_TEST("Test for expandCapacity():") {
    CQueue<int> que;
    que.enqueue(1);
    que.enqueue(2);
    que.enqueue(3);
    que.enqueue(1);
    que.enqueue(2);
    que.enqueue(3);
    que.enqueue(1);
    que.enqueue(2);
    que.enqueue(3);
    que.enqueue(1);
    que.enqueue(2);
    que.enqueue(3);
    EXPECT_EQUAL(que.size(), 12);
}
