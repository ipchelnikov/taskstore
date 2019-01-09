// Challenge from https://www.coderbyte.com/editor/guest:Longest%20Word:Cpp
//
// Have the function LongestWord(sen) take the sen parameter being passed and return the largest word in the string.
// If there are two or more words that are the same length, return the first word from the string with that length.
// Ignore punctuation and assume sen will not be empty.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

const std::string alphanum = "abcdefghijklmnopqrstuvwxyz"\
                             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"\
                             "1234567890";

std::string LongestWord(const std::string& sen) {

    std::vector<std::pair<size_t, size_t>> strings;
    size_t pos_first = 0, pos_last = 0;

    while((pos_first = sen.find_first_of(alphanum, pos_last)) != std::string::npos)
        if((pos_last = sen.find_first_not_of(alphanum, pos_first)) != std::string::npos)
            strings.emplace_back(pos_first, pos_last-pos_first);
        else
            strings.emplace_back(pos_first, sen.size()-pos_first);

    auto max = std::max_element(strings.begin(), strings.end(),
                                [] (std::pair<size_t, size_t> a, std::pair<size_t, size_t> b) {
                                    return a.second < b.second; });

    return sen.substr(max->first, max->second);
}

std::string LongestWordReg(const std::string& sen) {

    std::regex word_regex{"(\\w+)"};

    size_t max_word_size = 0;
    auto max_word = std::sregex_iterator();

    for(auto i = std::sregex_iterator(sen.begin(), sen.end(), word_regex); i != std::sregex_iterator(); ++i) {
        if ( i->str().size() > max_word_size )
        {
            max_word_size = i->str().size();
            max_word = i;
        }
    }

    return max_word->str();
}

int main() {
    // keep this function call here
    //cout << LongestWord(gets(stdin));
    //std::cout << LongestWord("a confusing /:sentence:/[ this is not!!!!!!!~");
    std::cout << LongestWordReg("a confusing /:sentence:/[ this is not!!!!!!!~");
    return 0;

}