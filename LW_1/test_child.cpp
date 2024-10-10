#include <gtest/gtest.h>
#include <string.h>

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

TEST(ReverseStringTest, BasicTest) {
    char test_str[] = "hello";
    reverse_string(test_str);
    EXPECT_STREQ(test_str, "olleh");
}

TEST(ReverseStringTest, EmptyString) {
    char test_str[] = "";
    reverse_string(test_str);
    EXPECT_STREQ(test_str, "");
}

TEST(ReverseStringTest, SingleCharacter) {
    char test_str[] = "a";
    reverse_string(test_str);
    EXPECT_STREQ(test_str, "a");
}

TEST(ReverseStringTest, EvenLength) {
    char test_str[] = "abcd";
    reverse_string(test_str);
    EXPECT_STREQ(test_str, "dcba");
}

TEST(ReverseStringTest, OddLength) {
    char test_str[] = "abcde";
    reverse_string(test_str);
    EXPECT_STREQ(test_str, "edcba");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
