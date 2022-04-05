#ifndef TABLES_FRACTION_H
#define TABLES_FRACTION_H


class Fraction {
private:
    int num;
    int den;

    static int greatest_common_divisor(int a, int b);

public:
    Fraction();
    Fraction(int, int);
    ~Fraction();
    friend Fraction operator + (const Fraction&, const Fraction&);
    friend Fraction operator - (const Fraction&, const Fraction&);
    friend Fraction operator * (const Fraction&, const Fraction&);
    friend Fraction operator / (const Fraction&, const Fraction&);
    friend bool operator > (const Fraction&, const Fraction&);
    friend bool operator < (const Fraction&, const Fraction&);
    friend bool operator == (const Fraction&, const Fraction&);
    friend bool operator >= (const Fraction&, const Fraction&);
    friend bool operator <= (const Fraction&, const Fraction&);
    friend bool operator > (const int&, const Fraction&);
    friend bool operator < (const int&, const Fraction&);
    friend bool operator == (const int&, const Fraction&);
    friend bool operator >= (const int&, const Fraction&);
    friend bool operator <= (const int&, const Fraction&);
    friend bool operator > (const Fraction&, const int&);
    friend bool operator < (const Fraction&, const int&);
    friend bool operator == (const Fraction&, const int&);
    friend bool operator >= (const Fraction&, const int&);
    friend bool operator <= (const Fraction&, const int&);
    friend std::ostream& operator << (std::ostream&, Fraction&);
};


#endif //TABLES_FRACTION_H
