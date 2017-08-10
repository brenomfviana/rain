#include "vec3.h"

/*!
 * TO COMMENT.
 */
inline std::istream& operator>>(std::istream& is, Vec3& v) {
    is >> v.e[Vec3::X] >> v.e[Vec3::Y] >> v.e[Vec3::Z];
    return is;
}

/*!
 * TO COMMENT.
 */
inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << "{ " << v.e[Vec3::X] << " "
               << v.e[Vec3::Y] << " "
               << v.e[Vec3::Z] << " }";
    return os;
}

/*!
 * TO COMMENT.
 */
inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[Vec3::X] + v2.e[Vec3::X],
                v1.e[Vec3::Y] + v2.e[Vec3::Y],
                v1.e[Vec3::Z] + v2.e[Vec3::Z]);
}

/*!
 * TO COMMENT.
 */
inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[Vec3::X] - v2.e[Vec3::X],
                v1.e[Vec3::Y] - v2.e[Vec3::Y],
                v1.e[Vec3::Z] - v2.e[Vec3::Z]);
}

/*!
 * TO COMMENT.
 */
inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[Vec3::X] * v2.e[Vec3::X],
                v1.e[Vec3::Y] * v2.e[Vec3::Y],
                v1.e[Vec3::Z] * v2.e[Vec3::Z]);
}

/*!
 * TO COMMENT.
 */
inline Vec3 operator/(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[Vec3::X] / v2.e[Vec3::X],
                v1.e[Vec3::Y] / v2.e[Vec3::Y],
                v1.e[Vec3::Z] / v2.e[Vec3::Z]);
}

/*!
 * TO COMMENT.
 */
inline Vec3 operator*(const Vec3& v, Vec3::ValueType t) {
    return Vec3(v.e[Vec3::X] * t,
                v.e[Vec3::Y] * t,
                v.e[Vec3::Z] * t);
}

/*!
 * TO COMMENT.
 */
inline Vec3 operator*(Vec3::ValueType t, const Vec3& v) {
    return Vec3(t * v.e[Vec3::X],
                t * v.e[Vec3::Y],
                t * v.e[Vec3::Z]);
}

/*!
 * TO COMMENT.
 */
inline Vec3 operator/(const Vec3& v, Vec3::ValueType t) {
    return Vec3(v.e[Vec3::X] / t,
                v.e[Vec3::Y] / t,
                v.e[Vec3::Z] / t);
}

/*!
 * TO COMMENT.
 */
inline Vec3::ValueType dot(const Vec3& v1, const Vec3& v2) {
    return (v1[Vec3::X] * v2[Vec3::X] +
            v1[Vec3::Y] * v2[Vec3::Y] +
            v1[Vec3::Z] * v2[Vec3::Z]);
}

/*!
 * TO COMMENT.
 */
inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
    return Vec3((v1[Vec3::Y] * v2[Vec3::Z] - v1[Vec3::Z] * v2[Vec3::Y]),
                (v1[Vec3::X] * v2[Vec3::Z] - v1[Vec3::Z] * v2[Vec3::X]),
                (v1[Vec3::X] * v2[Vec3::Y] - v1[Vec3::Y] * v2[Vec3::X]));
}

inline Vec3& Vec3::operator+=(const Vec3& v) {
    e[Vec3::X] += v.e[Vec3::X];
    e[Vec3::Y] += v.e[Vec3::Y];
    e[Vec3::Z] += v.e[Vec3::Z];
    return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& v) {
    e[Vec3::X] -= v.e[Vec3::X];
    e[Vec3::Y] -= v.e[Vec3::Y];
    e[Vec3::Z] -= v.e[Vec3::Z];
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3& v) {
    e[Vec3::X] *= v.e[Vec3::X];
    e[Vec3::Y] *= v.e[Vec3::Y];
    e[Vec3::Z] *= v.e[Vec3::Z];
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3& v) {
    e[Vec3::X] /= v.e[Vec3::X];
    e[Vec3::Y] /= v.e[Vec3::Y];
    e[Vec3::Z] /= v.e[Vec3::Z];
    return *this;
}

inline Vec3& Vec3::operator*=(const ValueType t) {
    e[Vec3::X] *= t;
    e[Vec3::Y] *= t;
    e[Vec3::Z] *= t;
    return *this;
}

inline Vec3& Vec3::operator/=(const ValueType t) {
    e[Vec3::X] /= t;
    e[Vec3::Y] /= t;
    e[Vec3::Z] /= t;
    return *this;
}

/*!
 * TO COMMENT.
 */
inline Vec3 unitVector(const Vec3& v) {
    return v / v.length();
}

/*!
 * TO COMMENT.
 */
inline void Vec3::makeUnitVector(void) {
    Vec3::ValueType k = (1 / sqrt(dot(*this, *this)));
    e[Vec3::X] *= k;
    e[Vec3::Y] *= k;
    e[Vec3::Z] *= k;
}

//================================[ vec3.inl ]================================//
