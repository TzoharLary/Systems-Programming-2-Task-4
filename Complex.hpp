// ID: 207492315
// Email: Tzohary1234@gmail.com
#include <iostream>
#include <string>

class Complex
{
    double real_, image_;

public:
    Complex(double real, double image);
    double getReal() const;
    double getImage() const;
    friend bool operator==(const Complex &a, const Complex &b)
    {
        return (a.getReal() == b.getReal() && a.getImage() == b.getImage());
    }
    friend std::ostream &operator<<(std::ostream &os, const Complex &c)
    {
        os << c.getReal() << " + " << c.getImage() << "i";
        return os;
    }
    bool operator>(const Complex &other) const;

};
