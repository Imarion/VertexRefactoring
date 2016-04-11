#include "vertextex.h"

VertexTex::VertexTex()
{
    m_tex    = QVector2D(1.0f, 1.0f);
}

VertexTex::VertexTex(QVector3D inPos, QVector2D inTex)
{
    setPos(inPos);
    m_tex = inTex;
}

VertexTex::VertexTex(QVector3D inPos, QVector3D inNormal, QVector2D inTex)
{
    setPos(inPos);
    setNormal(inNormal);
    m_tex = inTex;
}

QVector2D VertexTex::getTexCoord()
{
    return m_tex;
}

QVector3D VertexTex::getTangent()
{
    return m_tangent;
}

void VertexTex::setTangent(QVector3D inTangent)
{
    m_tangent = inTangent;
}
