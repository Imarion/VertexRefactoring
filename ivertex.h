#ifndef IVERTEX_H
#define IVERTEX_H

#include <QVector3D>

class iVertex
{
public:
    iVertex();

    //virtual int size_of() = 0;
    virtual QVector3D getPos() = 0;
    virtual QVector3D getNormal() = 0;
};

#endif // IVERTEX_H
