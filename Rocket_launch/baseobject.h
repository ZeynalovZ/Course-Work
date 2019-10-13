#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "point3d.h"
// базвый объект имеет методы трансформирования и все прочие методы управления объектом

class BaseObject
{
public:
    BaseObject();

    void Move(void);

    void Rotatex(void);
    void Rotatey(void);
    void Rotatez(void);

    void Scale(void);

};

#endif // BASEOBJECT_H
