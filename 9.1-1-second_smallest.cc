#include "std.h"

struct comparison_record {
  int smaller, larger;
};

int second_smallest(array A) {
  std::vector<comparison_record> matches;
  std::vector<int> current_bracket;
  for (size_t i = 1; i <= A.length; ++i)
    current_bracket.push_back(A[i]);

  while (current_bracket.size() != 1) {
    std::vector<int> next_stage;
    size_t i = 0;
    if (current_bracket.size() % 2 != 0) {
      i = 1;
      next_stage.push_back(current_bracket[0]);
    }
    for (; i < current_bracket.size(); i += 2) {
      int fst = current_bracket[i], snd = current_bracket[i + 1];
      if (fst < snd) {
        matches.push_back({ fst, snd });
        next_stage.push_back(fst);
      } else {
        matches.push_back({ snd, fst });
        next_stage.push_back(snd);
      }
    }
    current_bracket = next_stage;
  }

  bool second_smallest_not_set = true;
  int smallest = current_bracket[0], second_smallest_;

  for (size_t i = 0; i < matches.size(); ++i)
    if (matches[i].smaller == smallest)
      if (second_smallest_not_set || matches[i].larger < second_smallest_)
        second_smallest_ = matches[i].larger;

  return second_smallest_;
}

