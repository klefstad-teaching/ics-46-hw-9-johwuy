#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

// ✅ Test when words are adjacent (1 edit away)
TEST(IsAdjacentTest, AdjacentWords) {
    EXPECT_TRUE(is_adjacent("cat", "bat"));  // 1 substitution
    EXPECT_TRUE(is_adjacent("cat", "cot"));  // 1 substitution
    EXPECT_TRUE(is_adjacent("cat", "cats")); // 1 insertion
    EXPECT_TRUE(is_adjacent("cats", "cat")); // 1 deletion
}

// ✅ Test when words are not adjacent
TEST(IsAdjacentTest, NonAdjacentWords) {
    EXPECT_FALSE(is_adjacent("cat", "dog"));     // 3 substitutions
    EXPECT_FALSE(is_adjacent("cat", "cartoon")); // More than 1 edit
    EXPECT_FALSE(is_adjacent("cat", "ratting")); // More than 1 edit
}

// ✅ Test when words are identical (should return false)
TEST(IsAdjacentTest, IdenticalWords) {
    EXPECT_TRUE(is_adjacent("cat", "cat")); // Same word
    EXPECT_TRUE(is_adjacent("hello", "hello"));
}

// ✅ Test words with more than 1 length difference (should return false)
TEST(IsAdjacentTest, LengthDifferenceTooLarge) {
    EXPECT_FALSE(is_adjacent("cat", "cattle"));   // Length diff > 1
    EXPECT_FALSE(is_adjacent("play", "playing")); // Length diff > 1
}

// ✅ Edge Cases
TEST(IsAdjacentTest, EdgeCases) {
    EXPECT_TRUE(is_adjacent("a", "b"));  // 1 substitution
    EXPECT_TRUE(is_adjacent("a", "ab")); // 1 insertion
    EXPECT_TRUE(is_adjacent("ab", "a")); // 1 deletion
}

// ✅ Large Words Test
TEST(IsAdjacentTest, LargeWords) {
    EXPECT_TRUE(is_adjacent("abcdefgh", "abcdefg"));   // 1 deletion
    EXPECT_TRUE(is_adjacent("abcdefgh", "abcdxfgh"));  // 1 substitution
    EXPECT_FALSE(is_adjacent("abcdefgh", "abcdxygh")); // 2 substitutions
}

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
    EXPECT_EQ(levenshtein_distance("kitten", "sitting"),
              3); // Expected edits: k→s, e→i, +g
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
    EXPECT_EQ(levenshtein_distance("longwordwithmorecharacters",
                                   "longwordwithmorecharacters"),
              0);
}

TEST(LevenshteinDistanceTest, CaseSensitivity) {
    EXPECT_EQ(levenshtein_distance("Cat", "cat"), 1); // C → c
}

TEST(LevenshteinDistanceTest, ReversedStrings) {
    EXPECT_EQ(levenshtein_distance("abc", "cba"), 2); // b→c, a→b
}

TEST(LevenshteinDistanceTest, LongStringEdits) {
    EXPECT_EQ(levenshtein_distance("abcdefghijk", "abcxdefghyyz"),
              4); // c→x, h→y, +y, +z
}

TEST(PrintWordLadderTest, Empty) {
    print_word_ladder({});
}

TEST(PrintWordLadderTest, NonEmpty) {
    print_word_ladder({"awake","aware", "ware", "were" ,"wee", "see", "seep", "sleep"});
}

