#ifndef _GLM_OS_
#define _GLM_OS_

#include <ios>
#include <iomanip>
#include <iostream>
#include <glm/glm.hpp>

/// Prints a column-major 4x4 matriz.
std::ostream& operator<<(std::ostream& os, const glm::mat4& m) {
    for (int i = 0; i < 4; i++) {
        os << "[ ";
        for (int j = 0; j < 4 ; j++)
            os << std::fixed << std::right << std::setw(6) <<
               std::setprecision(2) << m[j][i] << " ";
        os << "]\n";
    }
    return os;
}

/// Prints a 3D vector.
std::ostream& operator<<(std::ostream& os, const glm::vec3& v) {
    os << "[ ";
    for (int i = 0; i < 3 ; i++) {
        os << std::right << std::setw(6) <<
           std::setprecision(2) << v[i] << " ";
    }
    os << "]";
    return os;
}

/// Prints a 4D vector.
std::ostream& operator<<(std::ostream& os, const glm::vec4& v) {
    os << "[ ";
    for (int i = 0; i < 4 ; i++) {
        os << std::right << std::setw(6) <<
           std::setprecision(2) << v[i] << " ";
    }
    os << "]";
    return os;
}

#endif /* _GLM_OS_ */
