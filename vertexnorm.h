#ifndef VERTEXNORM_H
#define VERTEXNORM_H

#include <QVector3D>

#include "ivertex.h"

class VertexNorm : iVertex
{
public:
    VertexNorm();
    VertexNorm(QVector3D inPos, QVector3D inNormal);

    QVector3D getPos();
    QVector3D getNormal();

    void setNormal(QVector3D inNormal);
    void setPos(QVector3D inPos);

private:
    QVector3D m_pos;
    QVector3D m_normal;
};

#endif // VERTEX_H
