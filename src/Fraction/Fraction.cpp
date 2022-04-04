#include <stdexcept>
#include "Fraction.h"

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

Fraction::Fraction(std::string value) {
    int a = 0;
    int b = 0;
    int k = 0;
    bool is_fraction = false;
    if (value[0] == '-') {
        k++;
    }
    for (int i = k; i < value.length(); i++) {
        if ('0' <= value[i] && value[i] <= '9') {
            a = a * 10 + (value[i] - '0');
        } else {
            b = a;
            a = 0;
            is_fraction = true;
        }
    }
    if (!is_fraction) {
        this->num = a;
        this->den = 1;
    } else {
        this->num = b;
        this->den = a;
    }
    if (k != 0) {
        this->num = -this->num;
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

double Fraction::to_double() const {
    return this->num * 1.0 / this->den;
}

std::string Fraction::to_string() const {
    if (this->num == 0) {
        return std::to_string(0);
    }
    if (this->den == 1) {
        return std::to_string(this->num);
    }
    return std::to_string(this->num) + "/" + std::to_string(this->den);
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