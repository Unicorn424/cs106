#include "arrayvector.h"
#include "testing/SimpleTest.h"

PROVIDED_TEST("Test for common operation on ArrayVector:") {
    ArrayVector<int> vec;
    EXPECT_ERROR(vec.remove(0));
    vec.add(1);
    vec.add(2);
    vec.add(3);
    vec.remove(2);
    EXPECT_EQUAL(vec.size(), 2);
}

PROVIDED_TEST("Test for operation overriding:") {
    ArrayVector<int> v1;
    v1.add(1);
    v1.add(1);
    v1.add(1);
    ArrayVector<int> v2(v1);
    ArrayVector<int> v3;
    v3 = v1;
    ArrayVector<int> v4(3, 1);
    ArrayVector<int> v5;
    EXPECT(v5.isEmpty());
    EXPECT(v1 == v2);
    EXPECT(v2 == v3);
    EXPECT(v3 == v4);
    EXPECT(v4 != v5);
}

PROVIDED_TEST("Test for expandCapacity():") {
    ArrayVector<int> vec(12, 1);
    EXPECT_EQUAL(vec.size(), 12);
}
