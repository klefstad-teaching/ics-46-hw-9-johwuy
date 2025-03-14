#include "ladder.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

int levenshtein_distance(const std::string &str1, const std::string &str2,
                         int d) {
    int len_str1 = str1.length();
    int len_str2 = str2.length();
    std::vector<int> prev(len_str2 + 1);
    std::vector<int> curr(len_str2 + 1);
    for (int i = 0; i <= len_str2; ++i) {
        prev[i] = i;
    }

    for (int i = 0; i < len_str1; ++i) {
        curr[0] = i + 1;
        int min_in_row = curr[0];

        for (int j = 0; j < len_str2; ++j) {
            int deletionCost = prev[j + 1] + 1;
            int insertionCost = curr[j] + 1;
            int substitutionCost = str1[i] == str2[j] ? prev[j] : prev[j] + 1;

            curr[j + 1] =
                std::min({deletionCost, insertionCost, substitutionCost});

            min_in_row = std::min(
                min_in_row, curr[j + 1]); // Updates min_in_row as you traverse
        }
        std::swap(prev, curr);

        if (min_in_row > d) {
            return d +
                   1; // Early exit if the minimum value in the row exceeds n
        }
    }
    return prev[len_str2];
}

void error(string word1, string word2, string msg) {
    std::cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")"
              << endl;
}
bool edit_distance_within(const std::string &str1, const std::string &str2,
                          int d) {
    return levenshtein_distance(str1, str2, d) <= d;
    // int shortest_length = std::min(str1.length(), str2.length());
    // int diff_count = 0;
    // for (size_t i = 0; i < shortest_length; ++i) {
    //     if (str1[i] != str2[i]) {
    //         ++diff_count;
    //         if (diff_count > 1)
    //             return false;
    //     }
    // }
    // diff_count +=
    //     std::abs((int)str1.length() -
    //              (int)str2.length()); // Accounds for insert and delete
    // return diff_count <= d;
}
bool is_adjacent(const string &word1, const string &word2) {
    int len_diff = std::abs((int)word1.length() - (int)word2.length());
    // If the length difference is greater than 1, or the words are the same,
    // return false
    if (word1 == word2) {
        return true;
    }

    if (len_diff > 1) {
        return false;
    }
    return edit_distance_within(word1, word2, 1);
}

// TODO: Need to do optimization (Go to TA Office hours)
vector<string> generate_word_ladder(const string &begin_word,
                                    const string &end_word,
                                    const set<string> &word_list) {

    if (begin_word == end_word || !word_list.contains(end_word))
        return {};

    std::queue<std::vector<std::string>> ladder_queue;
    ladder_queue.push({begin_word});
    std::unordered_set<std::string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        std::vector<std::string> ladder = ladder_queue.front();
        ladder_queue.pop();
        std::string last_word = ladder.back();
        for (const std::string &word : word_list) {
            if (!visited.contains(word) && is_adjacent(last_word, word)) {
                visited.insert(word);
                std::vector<std::string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word)
                    return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }

    return {}; // Empty vector represents no word list found.
}
void load_words(set<string> &word_list, const string &file_name) {
    std::ifstream file(file_name);
    std::string word;

    if (!file) {
        std::cerr << "Error: Unable to open file: " << file_name << std::endl;
        return;
    }

    while (std::getline(file, word)) {
        word_list.insert(word);
    }
    file.close();
}
void print_word_ladder(const vector<string> &ladder) {
    if (ladder.size() == 0) {
        std::cout << "No word ladder found." << std::endl;
        return;
    }
    std::cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        std::cout << ladder[i] << " ";
    }
    std::cout << std::endl;
}

#define my_assert(e)                                                           \
    {                                                                          \
        std::cout << #e << ((e) ? " passed" : " failed") << std::endl;         \
    }
void verify_word_ladder() {
    std::set<std::string> word_list;
    load_words(word_list, "src/words.txt");
    assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    assert(generate_word_ladder("code", "data", word_list).size() == 6);
    assert(generate_word_ladder("work", "play", word_list).size() == 6);
    assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
