#ifndef VERTEXTEX_H
#define VERTEXTEX_H

#include <QVector3D>
#include <QVector2D>

#include "vertex.h"

class VertexTex : public Vertex
{
public:
    VertexTex();
    VertexTex(QVector3D inPos, QVector2D inTex);
    VertexTex(QVector3D inPos, QVector3D inNormal, QVector2D inTex);

    QVector2D getTexCoord();
    QVector3D getTangent();

    void setTangent(QVector3D inTangent);

private:
    QVector2D m_tex;
    QVector3D m_tangent; // tangent for the TBN
};

#endif // VERTEXTEX_H
