#include "ladder.h"
#include <algorithm>
#include <utility>

void error(string word1, string word2, string msg) {}
bool edit_distance_within(const std::string &str1, const std::string &str2,
                          int d) {
    return false;
}
bool is_adjacent(const string &word1, const string &word2) { return false; }
vector<string> generate_word_ladder(const string &begin_word,
                                    const string &end_word,
                                    const set<string> &word_list) {
    return {};
}
void load_words(set<string> &word_list, const string &file_name) {}
void print_word_ladder(const vector<string> &ladder) {}
void verify_word_ladder() {}

int levenshtein_distance(const std::string &s1, const std::string &s2) {
    int s1_length = s1.length();
    int s2_length = s2.length();
    std::vector<int> prev(s2_length + 1);
    std::vector<int> curr(s2_length + 1);
    for (int i = 0; i <= s2_length; ++i) {
        prev[i] = i;
    }

    for (int i = 0; i < s1_length; ++i) {
        curr[0] = i + 1;

        for (int j = 0; j < s2_length; ++j) {
            int deletionCost = prev[j + 1] + 1;
            int insertionCost = curr[j] + 1;
            int substitutionCost;

            if (s1[i] == s2[j]) {
                substitutionCost = prev[j];
            } else {
                substitutionCost = prev[j] + 1;
            }

            curr[j + 1] =
                std::min({deletionCost, insertionCost, substitutionCost});
        }
        std::swap(prev, curr);
    }
    return prev[s2_length];
}