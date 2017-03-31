#include "std.h"

struct comparison_record {
  int smaller, larger;
};

#if 0
int small_order_select(array A, size_t i) {
  if (i >= A.length / 2)
    return select(A, i);

  std::vector<comparison_record> matches;
  std::vector<int> current_bracket;
  for (size_t i = 1; i <= A.length; ++i)
    current_bracket.push_back(A[i]);

  while (current_bracket.size() != i) {
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

  std::vector<int> winning_matches_pairs;
  for (size_t j = 0; j < current_bracket.size(); ++j)
    for (size_t i = 0; i < matches.size(); ++i)
      if (matches[i].smaller == current_bracket[j]) {
        winning_matches_pairs.push_back(matches[i].smaller);
        winning_matches_pairs.push_back(matches[i].larger);
      }
  array winning_matches_pairs_array(winning_matches_pairs.size());
  size_t j = 1;
  for (size_t i = 0; i < winning_matches_pairs.size(); ++i)
    winning_matches_pairs_array[j++] = winning_matches_pairs[i];

  return select(winning_matches_pairs_array, i);
}
#endif

