#ifndef _SPLIT_STR_
#define _SPLIT_STR_

#include <sstream>
#include <string>
#include <vector>

namespace utils {
    /*!
     * Split a string.
     *
     * @param str String
     * @param c Delimiter
     *
     * @return Splitted string
     */
    static const std::vector<std::string> split(const std::string& str, const char& c) {
        // Buffer
        std::string buff = "";
        // Splitted string
        std::vector<std::string> v;
        // Find tokens
        for (auto s : str) {
            // Check if the char is the delimiter
            if (s != c) {
                // Add to buffer
                buff += s;
            } else if (s == c && buff != "") {
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
} // namespace utils

#endif /* _SPLIT_STR_ */
