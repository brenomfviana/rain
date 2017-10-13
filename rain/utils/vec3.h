#ifndef _VEC3_H_
#define _VEC3_H_

#include <cmath>
#include <iostream>
#include <cassert>
#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <iomanip>

namespace utils {

    /*!
     * This class represents a 3D vector, that might be used to represent points,
     * directions, vectors, colors, offset.
     */
    class Vec3 {

        public:
            // Aliases
            typedef float RealType;
            enum FieldType : int {X = 0, Y = 1, Z = 2,
                                  R = 0, G = 1, B = 2};

            // 3D vector
            RealType e[3];

            /*!
             * 3D vector constructor.
             *
             * @param e0 Element 0
             * @param e1 Element 1
             * @param e2 Element 2
             */
            explicit Vec3(RealType e0 = 0.f, RealType e1 = 0.f, RealType e2 = 0.f) :
                e{e0, e1, e2} { /* empty */ }

            /*!
             * Copy constructor.
             *
             * @param vector_ Vector
             */
            Vec3(const Vec3& vector) : e{vector[X], vector[Y], vector[Z]}
                { /* empty */ }

            /*!
             * Initializer list constructor.
             *
             * @param il_ Initializer list
             */
            Vec3(std::initializer_list<RealType> il) {
                assert(il.size() >= 3);
                std::copy(il.begin(), std::next(il.begin(), 3), std::begin(e));
            }

            /* --------------------- Access Operators ----------------------- */

            /*!
             * Get x value.
             *
             * @return X value
             */
            inline RealType x() const { return e[X]; }

            /*!
             * Get y value.
             *
             * @return Y value
             */
            inline RealType y() const { return e[Y]; }

            /*!
             * Get z value.
             *
             * @return Z value
             */
            inline RealType z() const { return e[Z]; }

            /*!
             * Get red value.
             *
             * @return Red value
             */
            inline RealType r() const { return e[R]; }

            /*!
             * Get green value.
             *
             * @return Green value
             */
            inline RealType g() const { return e[G]; }

            /*!
             * Get blue value.
             *
             * @return Blue value
             */
            inline RealType b() const { return e[B]; }

            /*!
             * Indexed access operator (rhs).
             *
             * @param idx Index
             */
            inline RealType operator[](size_t idx) const {
                return e[idx];
            }

            /*!
             * Indexed access operator (lhs).
             *
             * @param Index
             */
            inline RealType& operator[](size_t idx) {
                return e[idx];
            }

            /* ------------------- Algebraic Operators ---------------------- */

            /*!
             * Unary '+'.
             */
            inline const Vec3& operator+(void) const {
                return *this;
            }

            /*!
             * Unary '-'.
             */
            inline Vec3 operator-(void) const {
                return Vec3(-e[X], -e[Y], -e[Z]);
            }

            /*!
             * Sum operator.
             *
             * @param v Vector
             *
             * @return Vector resulting from the operation
             */
            inline Vec3& operator+=(const Vec3&);

            /*!
             * Subtraction operator.
             *
             * @param v Vector
             *
             * @return Vector resulting from the operation
             */
            inline Vec3& operator-=(const Vec3&);

            /*!
             * Product operator.
             *
             * @param v Vector
             *
             * @return Vector resulting from the operation
             */
            inline Vec3& operator*=(const Vec3&);

            /*!
             * Division operator.
             *
             * @param v Vector
             *
             * @return Vector resulting from the operation
             */
            inline Vec3& operator/=(const Vec3&);

            /*!
             * Scalar product operator.
             *
             * @param t RealType
             *
             * @return Vector resulting from the operation
             */
            inline Vec3& operator*=(const RealType);

            /*!
             * Scalar division operator.
             *
             * @param t RealType
             *
             * @return Vector resulting from the operation
             */
            inline Vec3& operator/=(const RealType);

            /* -------------------------------------------------------------- */

            /*!
             * Get vector length.
             *
             * @return Vector length
             */
            inline RealType length(void) const {
                return sqrt(squaredLength());
            }

            /*!
             * Get vector length squared.
             *
             * @return Vector length squared
             */
            inline RealType squaredLength(void) const {
                return (e[X]*e[X] + e[Y]*e[Y] + e[Z]*e[Z]);
            }

            /*!
             * Make this vector an unit vector.
             */
            inline void makeUnitVector(void);
    };

    typedef Vec3 RGB;
    typedef Vec3 Offset;
    typedef Vec3 Point3;

    #include "vec3.inl"

} // namespace utils

#endif /* _VEC3_H_ */
