#include "color.h"

Color::Color()
{

}

Color::Color(QColor C)
{
    this->setRed(C.red());
    this->setGreen(C.green());
    this->setBlue(C.blue());
    this->setAlpha(C.alpha());
}

Color::Color(double R, double G, double B, int a)
{
    this->setRed(R);
    this->setGreen(G);
    this->setBlue(B);
    this->setAlpha(a);
}

Color &Color::operator=(const Color &rv)
{
    if (this == &rv)
    {
        return *this;
    }
    this->setAlpha(255);
    this->setRed(rv.red());
    this->setBlue(rv.blue());
    this->setGreen(rv.green());
    return *this;
}

const Color Color::operator+(const Color &rv) const
{
    return Color(this->red() + rv.red(), this->green() + rv.green(), this->blue() + rv.blue(), 255);
}

const Color Color::operator-(const Color &rv) const
{
    return Color(this->red() - rv.red(), this->green() - rv.green(), this->blue() - rv.blue(), 255);
}

const Color Color::operator*(const double src) const
{
    return Color(this->red() * src, this->green() * src, this->blue() * src, 255);
}
