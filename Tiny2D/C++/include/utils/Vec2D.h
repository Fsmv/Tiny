#pragma once

namespace Tiny2D {
class Vec2D {
public:
    Vec2D(double x, double y) : x(x), y(y) {}
    double x, y;

    inline Vec2D& operator+=(const Vec2D& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    inline Vec2D& operator-=(const Vec2D& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    inline Vec2D& operator*=(const double rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    inline Vec2D& operator/=(const double rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    // double/vector doesn't make any sense, so disallow it
    inline Vec2D operator/(const double rhs) {
        Vec2D lhs(*this);
        lhs.x /= rhs;
        lhs.y /= rhs;
        return lhs;
    }

};

inline Vec2D operator+(Vec2D lhs, const Vec2D& rhs) {
    lhs += rhs;
    return lhs;
}

inline Vec2D operator-(Vec2D lhs, const Vec2D& rhs) {
    lhs -= rhs;
    return lhs;
}

/**
 * Dot product
 */
inline double operator*(const Vec2D& lhs, const Vec2D& rhs) {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

/**
 * Scalar multiplication
 */
inline Vec2D operator*(Vec2D lhs, const double rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}

inline Vec2D operator*(const double rhs, Vec2D& lhs) {
    return lhs * rhs;
}

}
