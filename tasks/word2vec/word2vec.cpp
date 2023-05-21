#include "word2vec.h"

#include <climits>
#include <vector>

int64_t Scalar(const std::vector<int>& first_vector, const std::vector<int>& second_vector) {
    int64_t sum = 0;
    for (size_t i = 0; i < first_vector.size(); ++i) {
        sum += first_vector[i] * second_vector[i];
    }
    return sum;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<int64_t> scalars(words.size());
    int64_t max = Scalar(vectors[0], vectors[1]);
    int64_t max_count = 1;
    for (size_t i = 2; i < words.size(); ++i) {
        scalars[i] = Scalar(vectors[0], vectors[i]);
        if (scalars[i] > max) {
            max_count = 1;
            max = scalars[i];
        } else if (scalars[i] == max) {
            ++max_count;
        }
    }
    std::vector<std::string> selected_words(max_count);
    size_t index = 0;
    for (size_t i = 0; i < scalars.size(); ++i) {
        if (scalars[i] == max) {
            selected_words[index++] = words[i];
        }
    }
    return selected_words;
}
