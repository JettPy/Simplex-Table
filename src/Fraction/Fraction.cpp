#include <iostream>
#include "Fraction.h"

Fraction::Fraction() {
    this->num = 0;
    this->den = 1;
}

Fraction::Fraction(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("denominator can't be zero");
    }
    int gcd = Fraction::greatest_common_divisor(abs(a), abs(b));
    this->num = a / gcd;
    this->den = b / gcd;
    if (this->den < 0) {
        this->num = -this->num;
        this->den = -this->den;
    }
}

Fraction::~Fraction() = default;

int Fraction::greatest_common_divisor(int a, int b) {
    if (a % b == 0) {
        return b;
    }
    if (b % a == 0) {
        return a;
    }
    if (a > b) {
        return greatest_common_divisor(a % b, b);
    }
    return greatest_common_divisor(a, b % a);
}

Fraction operator + (const Fraction& a, const Fraction& b) {
    int num = a.num * b.den + b.num * a.den;
    int den = a.den * b.den;
    return Fraction(num, den);
}

Fraction operator - (const Fraction& a, const Fraction& b) {
    int num = a.num * b.den - b.num * a.den;
    int den = a.den * b.den;
    return Fraction(num, den);
}

Fraction operator * (const Fraction& a, const Fraction& b) {
    int num = a.num * b.num;
    int den = a.den * b.den;
    return Fraction(num, den);
}

Fraction operator / (const Fraction& a, const Fraction& b) {
    int num = a.num * b.den;
    int den = a.den * b.num;
    return Fraction(num, den);
}

bool operator > (const Fraction& a, const Fraction& b) {
    return a.num * b.den > b.num * a.den;
}

bool operator < (const Fraction& a, const Fraction& b) {
    return a.num * b.den < b.num * a.den;
}

bool operator == (const Fraction& a, const Fraction& b) {
    return a.num * b.den == b.num * a.den;
}
bool operator >= (const Fraction& a, const Fraction& b) {
    return a.num * b.den >= b.num * a.den;
}

bool operator <= (const Fraction& a, const Fraction& b) {
    return a.num * b.den <= b.num * a.den;
}

bool operator > (const int& a, const Fraction& b) {
    return a * b.den > b.num;
}

bool operator < (const int& a, const Fraction& b) {
    return a * b.den < b.num;
}

bool operator == (const int& a, const Fraction& b) {
    return a * b.den == b.num;
}

bool operator >= (const int& a, const Fraction& b) {
    return a * b.den >= b.num;
}

bool operator <= (const int& a, const Fraction& b) {
    return a * b.den <= b.num;
}

bool operator > (const Fraction& a, const int& b) {
    return a.num > b * a.den;
}

bool operator < (const Fraction& a, const int& b) {
    return a.num < b * a.den;
}

bool operator == (const Fraction& a, const int& b) {
    return a.num == b * a.den;
}

bool operator >= (const Fraction& a, const int& b) {
    return a.num >= b * a.den;
}

bool operator <= (const Fraction& a, const int& b) {
    return a.num <= b * a.den;
}

std::ostream& operator << (std::ostream& out, Fraction& a) {
    if (a.den == 1) {
        out << a.num;
    } else {
        out << std::to_string(a.num) + "/" + std::to_string(a.den);
    }
    return out;
}