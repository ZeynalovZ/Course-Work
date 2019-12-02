#ifndef COLOR_H
#define COLOR_H
#include <QColor>

class Color : public QColor
{
public:
    Color();
    Color (QColor C);
    Color(double R, double G, double B, int a);

    Color& operator=(const Color &rv);
    const Color operator+(const Color& rv) const;
    const Color operator-(const Color& rv) const;
    const Color operator*(const double src) const;
};

#endif // COLOR_H
