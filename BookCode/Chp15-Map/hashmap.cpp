#include "hashmap.h"
#include "testing/SimpleTest.h"

PROVIDED_TEST("Test for common operation of HashMap:") {
    HashMap<int, std::string> map;
    EXPECT(map.isEmpty());
    map.put(1, "qu");
    map.put(2, "min");
    map.put(3, "zhi");
    EXPECT_EQUAL(map.size(), 3);
    EXPECT_ERROR(map.remove(4));
    EXPECT_EQUAL(map.get(3), "zhi");
    map.remove(3);
    EXPECT_EQUAL(map.size(), 2);
}

PROVIDED_TEST("Test for stream overriding:") {
    HashMap<int, std::string> map;
    map.put(1, "qu");
    map.put(2, "min");
    map.put(3, "zhi");
    std::string output;
    std::ostringstream os;
    os << map;
    output = os.str();
    EXPECT_EQUAL(output, "nBucket: 5, count: 3, {<1, qu>, <2, min>, <3, zhi>}");
}

PROVIDED_TEST("Test for deep copy and equal operation:") {
    HashMap<int, std::string> m1;
    m1.put(1, "qu");
    m1.put(2, "min");
    m1.put(3, "zhi");
    HashMap<int, std::string> m2(m1);
    HashMap<int, std::string> m3;
    m3 = m1;
    HashMap<int, std::string> m4;
    m4.put(1, "qu");
    EXPECT(m1 == m2);
    EXPECT(m2 == m3);
    EXPECT(m3 != m4);
}

PROVIDED_TEST("Test for rehash():") {
    HashMap<int, std::string> map;
    EXPECT(map.isEmpty());
    map.put(1, "a");  // lambda = 0.2
    map.put(2, "b");  //          0.4
    map.put(3, "c");  //          0.6
    map.put(4, "d");  //          0.8
    map.put(5, "e");  // 0.8 > 0.7 => rehash() => 0.5
    std::string output;
    std::ostringstream os;
    os << map;
    output = os.str();
    EXPECT_EQUAL(output, "nBucket: 10, count: 5, {<5, e>, <1, a>, <2, b>, <3, c>, <4, d>}");
}
