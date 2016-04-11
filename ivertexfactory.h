#ifndef IVERTEXFACTORY_H
#define IVERTEXFACTORY_H

#include <QVector3D>
#include <QVector2D>

#include "vertexnorm.h"
#include "vertexcol.h"
#include "vertextex.h"

class iVertexFactory
{
public:
    iVertexFactory();

    virtual VertexNorm *MakeVertex(QVector3D inPos, QVector3D inNormal) = 0;
    virtual VertexCol  *MakeVertex(QVector3D inPos, QVector3D inNormal, QVector3D inColor) = 0;
    virtual VertexTex  *MakeVertex(QVector3D inPos, QVector3D inNormal, QVector2D inTexCoord) = 0;
};

#endif // IVERTEXFACTORY_H
