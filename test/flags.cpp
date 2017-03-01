#include "gtest/gtest.h"

#include "Flags.h"

using namespace flags;

enum class TestFlags {
    Flag1 = 0x1,
    Flag2 = 0x2,
    Flag3 = 0x4
};

TEST(Flags, constructor) {
    Flags<TestFlags> f1;

    ASSERT_EQ(f1, Flags<TestFlags>());   
    ASSERT_EQ(f1.get_value(), 0x0);
    ASSERT_EQ(f1, Flags<TestFlags>::empty());

    Flags<TestFlags> f2 = TestFlags::Flag1;
    Flags<TestFlags> f3 = TestFlags::Flag3;
    ASSERT_NE(f2, f3);
    ASSERT_NE(f2, f1);
    ASSERT_EQ(f2.get_value(), 0x1);
    ASSERT_EQ(f3.get_value(), 0x4);

    Flags<TestFlags> f4 = {TestFlags::Flag1, TestFlags::Flag2, TestFlags::Flag3};
    ASSERT_EQ(f4.get_value(), 0x7);
    Flags<TestFlags> f5 = {TestFlags::Flag1, TestFlags::Flag3};
    ASSERT_NE(f4, f5);
    ASSERT_EQ(f5, f2 | f3);
    f5.set_flag(TestFlags::Flag2);
    ASSERT_EQ(f4, f5);
}

TEST(Flags, bitwise_ops) {
    Flags<TestFlags> all = {
        TestFlags::Flag1, TestFlags::Flag2, TestFlags::Flag3
    };

    Flags<TestFlags> f1;
    Flags<TestFlags> f2 = TestFlags::Flag2;
    ASSERT_EQ(f1 | f1, f1);
    ASSERT_EQ(f1 | TestFlags::Flag2, TestFlags::Flag2);
    ASSERT_EQ(f2 & TestFlags::Flag1, f1);

    f1 |= TestFlags::Flag3;
    ASSERT_NE(f2, f1);
    ASSERT_EQ(f1, TestFlags::Flag3);
    ASSERT_EQ(f1 | TestFlags::Flag3, f1);
    ASSERT_EQ(f1 & TestFlags::Flag3, f1);
    ASSERT_EQ(f1 & TestFlags::Flag1, Flags<TestFlags>::empty());

    Flags<TestFlags> f3 = {TestFlags::Flag1, TestFlags::Flag2};
    ASSERT_EQ(f3 | Flags<TestFlags>::empty(), f3);
    ASSERT_EQ(f3 & Flags<TestFlags>::empty(), Flags<TestFlags>::empty());
    ASSERT_EQ(f3 ^ Flags<TestFlags>::empty(), f3);
    Flags<TestFlags> f4 = {TestFlags::Flag1, TestFlags::Flag3};
    ASSERT_EQ(f4 | f3, all);
    Flags<TestFlags> f5 = {TestFlags::Flag2, TestFlags::Flag3};
    ASSERT_EQ(f4 ^ f3, f5);
    ASSERT_EQ(f4 & f3, TestFlags::Flag1);
}

TEST(Flags, flag_modifiers) {
    Flags<TestFlags> f1 = {TestFlags::Flag1, TestFlags::Flag3};
    Flags<TestFlags> f2 = f1;
    ASSERT_EQ(f1.get_value(), 0x5);
    f1.set_flag(TestFlags::Flag2);
    f1.clear_flag(TestFlags::Flag1);
    ASSERT_EQ(f1.get_value(), 0x6);

    f2.toggle_flag(TestFlags::Flag2);
    f2.toggle_flag(TestFlags::Flag2);
    f2.toggle_flag(TestFlags::Flag3);
    f2.toggle_flag(TestFlags::Flag3);
    f2.toggle_flag(TestFlags::Flag2);
    f2.toggle_flag(TestFlags::Flag1);
    ASSERT_EQ(f2, f1); 
    f2.set_flag(TestFlags::Flag2);
    ASSERT_EQ(f2, f1);
}

TEST(Flags, flag_test) {
    Flags<TestFlags> f1 = TestFlags::Flag2;
    ASSERT_TRUE(f1.has_flag(TestFlags::Flag2));
    ASSERT_FALSE(f1.has_flag(TestFlags::Flag1));
    ASSERT_FALSE(f1.has_flag(TestFlags::Flag3));

}
