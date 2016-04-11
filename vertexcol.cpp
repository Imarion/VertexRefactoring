#include "vertexcol.h"

VertexCol::VertexCol()
{
    m_color  = QVector3D(1.0f, 1.0f, 1.0f);
}

VertexCol::VertexCol(QVector3D inPos, QVector3D inColor)
{
    setPos(inPos);
    m_color = inColor;
}

VertexCol::VertexCol(QVector3D inPos, QVector3D inNormal, QVector3D inColor)
{
    setPos(inPos);
    setNormal(inNormal);
    m_color = inColor;
}

QVector3D VertexCol::getColor()
{
    return m_color;
}
