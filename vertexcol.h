#ifndef VERTEXCOL_H
#define VERTEXCOL_H

#include <QVector3D>

#include "vertexnorm.h"

class VertexCol : public VertexNorm
{
public:
    VertexCol();
    VertexCol(QVector3D inPos, QVector3D inColor);
    VertexCol(QVector3D inPos, QVector3D inNormal, QVector3D inColor);

    QVector3D getColor();

private:
    QVector3D m_color;

};

#endif // VERTEXCOL_H
