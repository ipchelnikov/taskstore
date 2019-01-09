#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

int main() {
    // keep this function call here
    //cout << LongestWord(gets(stdin));
    std::cout << LongestWord("a confusing /:sentence:/[ this is not!!!!!!!~");
    return 0;

}