#include "vertexfactory.h"

VertexFactory::VertexFactory()
{
}

Vertex *VertexFactory::MakeVertex(QVector3D inPos, QVector3D inNormal)
{
    return new Vertex(inPos, inNormal);
}

VertexCol *VertexFactory::MakeVertex(QVector3D inPos, QVector3D inNormal, QVector3D inColor)
{
    return new VertexCol(inPos, inNormal, inColor);
}

VertexTex *VertexFactory::MakeVertex(QVector3D inPos, QVector3D inNormal, QVector2D inTexCoord)
{
    return new VertexTex(inPos, inNormal, inTexCoord);
}
