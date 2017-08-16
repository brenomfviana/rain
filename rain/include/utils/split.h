#ifndef _SPLIT_STR_
#define _SPLIT_STR_

#include <sstream>
#include <string>
#include <vector>

/**
 * Split a string.
 *
 * @param str String
 * @param c Symbol
 *
 * @return Splitted string
 */
const std::vector<std::string> split(const std::string& str, const char& c) {
    // Buffer
    std::string buff = "";
    // Splitted string
    std::vector<std::string> v;
    // Find tokens
    for (auto n : str) {
        // Check delimiter
        if (n != c) {
            // Add to buffer
            buff += n;
        } else if (n == c && buff != "") {
            // Add string to vector
            v.push_back(buff);
            // Reset buffer
            buff = "";
        }
    }
    // Check last string
    if (buff != "") {
        // Add string to vector
        v.push_back(buff);
    }
    return v;
}

#endif
