#ifndef _UTILS_
#define _UTILS_

#include <algorithm>
#include <cctype>
#include <iomanip>
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
    static std::vector<std::string> split(const std::string& str, const char& c) {
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

    /*!
     * Convert a string to boolean.
     *
     * @param str String
     *
     * @param Return correspondent value
     */
    static bool to_bool(std::string str) {
        // Make lowercase
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        // To bool
        std::istringstream is(str);
        bool b;
        is >> std::boolalpha >> b;
        return b;
    }

    /*!
     * User-define literal to convert from degrees to radian.
     *
     * @param deg Degrees
     *
     * @return Number converted to radians
     */
    constexpr long double operator""_deg(long double deg) {
        return (deg * (3.141592 / 180));
    }
} // namespace utils

#endif /* _UTILS_ */
