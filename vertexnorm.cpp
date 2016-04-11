#include "vertexnorm.h"

VertexNorm::VertexNorm()
{
    m_pos    = QVector3D(0.0f, 0.0f, 0.0f);
    m_normal = QVector3D(0.0f, 0.0f, 0.0f);    
}

VertexNorm::VertexNorm(QVector3D pos, QVector3D normal)
{
    m_pos    = pos;
    m_normal = normal;
}

QVector3D VertexNorm::getPos()
{
    return m_pos;
}

QVector3D VertexNorm::getNormal()
{
    return m_normal;
}

void VertexNorm::setNormal(QVector3D inNormal)
{
    m_normal = inNormal;
}

void VertexNorm::setPos(QVector3D inPos)
{
    m_pos = inPos;
}
