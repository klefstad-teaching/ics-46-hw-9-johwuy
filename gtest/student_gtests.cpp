#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(LevenshteinDistanceTest, NoEdit) {
    EXPECT_EQ(levenshtein_distance("cat", "cat"), 0);
}

TEST(LevenshteinDistanceTest, OneEditSub) {
    EXPECT_EQ(levenshtein_distance("cat", "fat"), 1);
}

TEST(LevenshteinDistanceTest, TwoEditSub) {
    EXPECT_EQ(levenshtein_distance("cat", "fak"), 2);
}

TEST(LevenshteinDistanceTest, OneEditInsert) {
    EXPECT_EQ(levenshtein_distance("cat", "cats"), 1);
}

TEST(LevenshteinDistanceTest, TwoEditInsert) {
    EXPECT_EQ(levenshtein_distance("cat", "catts"), 2);
}

TEST(LevenshteinDistanceTest, OneEditDelete) {
    EXPECT_EQ(levenshtein_distance("cats", "cat"), 1);
}

TEST(LevenshteinDistanceTest, TwoEditDelete) {
    EXPECT_EQ(levenshtein_distance("catts", "cat"), 2);
}

TEST(LevenshteinDistanceTest, MixedEdits) {
    EXPECT_EQ(levenshtein_distance("kitten", "sitting"), 3); // Expected edits: k→s, e→i, +g
}

TEST(LevenshteinDistanceTest, EmptyStrings) {
    EXPECT_EQ(levenshtein_distance("", ""), 0);
}

TEST(LevenshteinDistanceTest, OneEmptyString) {
    EXPECT_EQ(levenshtein_distance("", "test"), 4);
    EXPECT_EQ(levenshtein_distance("test", ""), 4);
}

TEST(LevenshteinDistanceTest, LargeDifference) {
    EXPECT_EQ(levenshtein_distance("abcdefg", "xyz"), 7);
}

TEST(LevenshteinDistanceTest, IdenticalLongStrings) {
    EXPECT_EQ(levenshtein_distance("longwordwithmorecharacters", "longwordwithmorecharacters"), 0);
}

TEST(LevenshteinDistanceTest, CaseSensitivity) {
    EXPECT_EQ(levenshtein_distance("Cat", "cat"), 1); // C → c
}

TEST(LevenshteinDistanceTest, ReversedStrings) {
    EXPECT_EQ(levenshtein_distance("abc", "cba"), 2); // b→c, a→b
}

TEST(LevenshteinDistanceTest, LongStringEdits) {
    EXPECT_EQ(levenshtein_distance("abcdefghijk", "abcxdefghyyz"), 4); // c→x, h→y, +y, +z
}
