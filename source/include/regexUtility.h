#pragma once
#include <iterator>
#include <string>
#include <regex>
#include <vector>

namespace regexUtility {
    const std::regex trackRegex("spotify:track:[a-zA-z0-9]+");
    const std::regex albumRegex("spotify:album:[a-zA-z0-9]+");

    inline std::vector<std::string>executeRegex(std::regex pattern, std::string s) {
        std::vector<std::string> results;

        auto words_begin =
            std::sregex_iterator(s.begin(), s.end(), pattern);

        auto words_end = std::sregex_iterator();

        bool firstMatchCaught = false;

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            if (!firstMatchCaught) {
                firstMatchCaught = true;
                continue;
            }

            std::smatch match = *i;
            std::string match_str = match.str();
            results.push_back(match_str);
        }

        return results;
    }

    /*
    */
    inline std::string executeRegexString(std::regex pattern, std::string s) {
        auto words_begin =
            std::sregex_iterator(s.begin(), s.end(), pattern);

        auto words_end = std::sregex_iterator();

        std::smatch match = *words_begin;
        std::string match_str = match.str();

        return match_str;
    }

}