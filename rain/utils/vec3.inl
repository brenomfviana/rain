#include "vec3.h"

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

inline Vec3& Vec3::operator*=(const Vec3::RealType t) {
    e[Vec3::X] *= t;
    e[Vec3::Y] *= t;
    e[Vec3::Z] *= t;
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3::RealType t) {
    e[Vec3::X] /= t;
    e[Vec3::Y] /= t;
    e[Vec3::Z] /= t;
    return *this;
}

/*!
 * Input operator.
 *
 * @param os Input stream
 * @param v Vector
 *
 * @return Input
 */
inline std::istream& operator>>(std::istream& is, Vec3& v) {
    is >> v.e[Vec3::X] >> v.e[Vec3::Y] >> v.e[Vec3::Z];
    return is;
}

/*!
 * Output operator.
 *
 * @param os Output stream
 * @param v Vector
 *
 * @return Output
 */
inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << "{ " << v.e[Vec3::X] << " "
               << v.e[Vec3::Y] << " "
               << v.e[Vec3::Z] << " }";
    return os;
}

/*!
 * Vector sum operator.
 *
 * @param v1 Vector
 * @param v2 Vector
 *
 * @return Vector resulting from the operation
 */
inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[Vec3::X] + v2.e[Vec3::X],
                v1.e[Vec3::Y] + v2.e[Vec3::Y],
                v1.e[Vec3::Z] + v2.e[Vec3::Z]);
}

/*!
 * Vector subtraction operator.
 *
 * @param v1 Vector
 * @param v2 Vector
 *
 * @return Vector resulting from the operation
 */
inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[Vec3::X] - v2.e[Vec3::X],
                v1.e[Vec3::Y] - v2.e[Vec3::Y],
                v1.e[Vec3::Z] - v2.e[Vec3::Z]);
}

/*!
 * Vector product operator.
 *
 * @param v1 Vector
 * @param v2 Vector
 *
 * @return Vector resulting from the operation
 */
inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[Vec3::X] * v2.e[Vec3::X],
                v1.e[Vec3::Y] * v2.e[Vec3::Y],
                v1.e[Vec3::Z] * v2.e[Vec3::Z]);
}

/*!
* Vector division operator.
*
* @param v1 Vector
* @param v2 Vector
*
* @return Vector resulting from the operation
 */
inline Vec3 operator/(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[Vec3::X] / v2.e[Vec3::X],
                v1.e[Vec3::Y] / v2.e[Vec3::Y],
                v1.e[Vec3::Z] / v2.e[Vec3::Z]);
}

/*!
 * Vector and scalar product operator.
 *
 * @param v Vector
 * @param t Scalar
 *
 * @return Vector resulting from the operation
 */
inline Vec3 operator*(const Vec3& v, Vec3::RealType t) {
    return Vec3(v.e[Vec3::X] * t,
                v.e[Vec3::Y] * t,
                v.e[Vec3::Z] * t);
}

/*!
 * Scalar and vector product operator.
 *
 * @param t Scalar
 * @param v Vector
 *
 * @return Vector resulting from the operation
 */
inline Vec3 operator*(Vec3::RealType t, const Vec3& v) {
    return Vec3(t * v.e[Vec3::X],
                t * v.e[Vec3::Y],
                t * v.e[Vec3::Z]);
}

/*!
 * Vector and scalar division operator.
 *
 * @param v Vector
 * @param t Scalar
 *
 * @return Vector resulting from the operation
 */
inline Vec3 operator/(const Vec3& v, Vec3::RealType t) {
    return Vec3(v.e[Vec3::X] / t,
                v.e[Vec3::Y] / t,
                v.e[Vec3::Z] / t);
}

/*!
 * Dot product.
 *
 * @param v1 Vector
 * @param v2 Vector
 *
 * @return Scalar resulting from the operation
 */
inline Vec3::RealType dot(const Vec3& v1, const Vec3& v2) {
    return (v1[Vec3::X] * v2[Vec3::X] +
            v1[Vec3::Y] * v2[Vec3::Y] +
            v1[Vec3::Z] * v2[Vec3::Z]);
}

/*!
 * Cross product.
 *
 * @param v1 Vector
 * @param v2 Vector
 *
 * @return Vector resulting from the operation
 */
inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
    return Vec3((v1[Vec3::Y] * v2[Vec3::Z] - v1[Vec3::Z] * v2[Vec3::Y]),
               -(v1[Vec3::X] * v2[Vec3::Z] - v1[Vec3::Z] * v2[Vec3::X]),
                (v1[Vec3::X] * v2[Vec3::Y] - v1[Vec3::Y] * v2[Vec3::X]));
}

inline void Vec3::makeUnitVector(void) {
    Vec3::RealType vDOTv = dot(*this, *this);
    assert(fabs(vDOTv - 0.f) > 0.000001);
    Vec3::RealType k = (1.f / sqrt(vDOTv));
    e[Vec3::X] *= k;
    e[Vec3::Y] *= k;
    e[Vec3::Z] *= k;
}

/*!
 * Get unit vector.
 *
 * @param v Vector
 *
 * @return Unit vector
 */
inline static Vec3 unitVector(const Vec3& v) {
    return v / v.length();
}

//================================[ vec3.inl ]================================//
