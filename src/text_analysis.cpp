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
    // gracias --->
    // https://stackoverflow.com/questions/29312967/stl-unordered-map-inserting-into-a-vector
  }
}

// TO DO
size_t TextAnalysis::countWord(const std::string& word) {
  for (auto e : wordtable) {
    if (e.first == word) {
      return e.second.size();
    }
  }
  return 0;
}

// TO DO

void TextAnalysis::sanitizeVector(std::vector<size_t>& v) const {
  std::sort(v.begin(), v.end());  // make sure it is in numeric order
  v.erase(std::unique(v.begin(), v.end()), v.end());  // remove duplicate values
}

std::vector<size_t> TextAnalysis::findVector(const std::string& s) {
  for (auto element : wordtable) {
    if (element.first == s) {
      return element.second;
    }
  }
  std::vector<size_t> n;
  return n;
}

size_t TextAnalysis::countTwoWords(const std::string& word1,
                                   const std::string& word2) {
  // the intersection of two vectors is placed inside of v3
  std::vector<size_t> v1 = findVector(word1);
  std::vector<size_t> v2 = findVector(word2);
  std::vector<size_t> v3;
  sanitizeVector(v1);
  sanitizeVector(v2);
  std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                        std::inserter(v3, v3.begin()));
  return v3.size();
}

