#pragma once
#include <algorithm> /* std::transform */
#include <iostream>
#include <list>
#include <set>
#include <string> /* not needed for Mac OSX */
#include <unordered_map>
#include <vector>

class TextAnalysis {
 public:
  TextAnalysis() = default;
  void add_word(const std::string&, size_t);  // IMPLEMENT BELOW
  size_t countWord(const std::string&);       // IMPLEMENT BELOW
  size_t countTwoWords(const std::string&,
                       const std::string&);  // IMPLEMENT BELOW
  void sanitizeVector(std::vector<size_t>& v) const;
  void read_text(std::istream&, const std::string&);  // ALREADY DONE
  std::vector<size_t> findVector(const std::string& s);

 private:
  std::unordered_map<std::string, std::vector<size_t> >
      wordtable;  // hash table with key=word and value=vector of page numbers
};

// ALREADY DONE: BREAK A LINE INTO A LIST OF WORDS
// Courtesy of Martin Broadhurst --
// http://www.martinbroadhurst.com/how-to-split-a-string-in-c.html
template <class Container>
void split(const std::string& str, Container& cont,
           const std::string& delims = " ") {
  std::size_t curr, prev = 0;
  curr = str.find_first_of(delims);

  while (curr != std::string::npos) {  // largest possible unsigned number
    cont.push_back(str.substr(prev, curr - prev));
    prev = curr + 1;
    curr = str.find_first_of(delims, prev);
  }

  cont.push_back(str.substr(prev, curr - prev));
}

