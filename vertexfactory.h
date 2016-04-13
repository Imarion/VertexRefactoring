#ifndef VERTEXFACTORY_H
#define VERTEXFACTORY_H

#include <QVector3D>
#include <QVector2D>

#include "ivertexfactory.h"

class VertexFactory : public iVertexFactory
{
public:
    VertexFactory();

    Vertex     MakeVertex(QVector3D inPos, QVector3D inNormal);
    VertexCol  MakeVertex(QVector3D inPos, QVector3D inNormal, QVector3D inColor);
    VertexTex  MakeVertex(QVector3D inPos, QVector3D inNormal, QVector2D inTexCoord);
};

#endif // VERTEXFACTORY_H
