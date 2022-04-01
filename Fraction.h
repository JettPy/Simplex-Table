#ifndef TABLES_FRACTION_H
#define TABLES_FRACTION_H
#include <string>


class Fraction {
private:
    int num;
    int den;

    static int greatest_common_divisor(int a, int b);

public:
    Fraction(int, int);
    explicit Fraction(std::string);
    ~Fraction();
    [[nodiscard]] double to_double() const;
    [[nodiscard]] std::string to_string() const;
    friend Fraction operator + (const Fraction&, const Fraction&);
    friend Fraction operator - (const Fraction&, const Fraction&);
    friend Fraction operator * (const Fraction&, const Fraction&);
    friend Fraction operator / (const Fraction&, const Fraction&);
};


#endif //TABLES_FRACTION_H
