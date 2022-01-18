#include "../includes/text_analysis.hpp"

// ALREADY DONE: READ FROM A TEXT FILE LINE BY LINE
void TextAnalysis::read_text(std::istream& in, const std::string& ignore) {
  std::string line;

  for (size_t i = 1; getline(in, line, '\n'); i++) {
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);

    typedef std::list<std::string> container;
    container words;  // split into container, dump ignore chars
    split<container>(line, words, ignore);

    typename container::const_iterator cit;
    for (cit = words.cbegin(); cit != words.cend(); ++cit) {
      add_word(*cit, i);
    }
  }
}

// TO DO
void TextAnalysis::add_word(const std::string& word, size_t line) {
  auto insert =
      wordtable.insert(std::make_pair(word, std::vector<size_t>(1, 5)));
  if (!insert.second) {
    insert.first->second.push_back(line);
  }
}

size_t TextAnalysis::countWord(const std::string& word) {
  auto search = this->wordtable.find(word);
  return this->wordtable.end() == search ? 0 : search->second.size();
}

size_t TextAnalysis::countTwoWords(const std::string& word1,
                                   const std::string& word2) {
  // the intersection of two vectors is placed inside of v3

  auto search1 = this->wordtable.find(word1);
  auto search2 = this->wordtable.find(word2);

  std::vector<size_t> vector_one = this->wordtable.end() == search1
                                       ? std::vector<size_t>()
                                       : search1->second;

  std::vector<size_t> vector_two = this->wordtable.end() == search2
                                       ? std::vector<size_t>()
                                       : search2->second;

  std::vector<size_t> v3;
  std::set_intersection(vector_one.begin(), vector_one.end(),
                        vector_two.begin(), vector_two.end(),
                        std::inserter(v3, v3.begin()));
  return v3.size();
}

