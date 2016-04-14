#include "Triangle.h"

#include <QtGlobal>

#include <QDebug>
#include <QFile>
#include <QImage>
#include <QTime>

#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>

#include <cmath>
#include <cstring>

MyWindow::~MyWindow()
{
    if (mProgramCol   != 0)   delete   mProgramCol;
    if (mProgramNorm  != 0)   delete   mProgramNorm;
}

MyWindow::MyWindow() : currentTimeMs(0), currentTimeS(0)
{
    mProgramCol  = 0;

    setSurfaceType(QWindow::OpenGLSurface);
    setFlags(Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(4);
    format.setMinorVersion(3);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
    create();

    resize(800, 600);

    mContext = new QOpenGLContext(this);
    mContext->setFormat(format);
    mContext->create();

    mContext->makeCurrent( this );

    mFuncs = mContext->versionFunctions<QOpenGLFunctions_4_3_Core>();
    if ( !mFuncs )
    {
        qWarning( "Could not obtain OpenGL versions object" );
        exit( 1 );
    }
    if (mFuncs->initializeOpenGLFunctions() == GL_FALSE)
    {
        qWarning( "Could not initialize core open GL functions" );
        exit( 1 );
    }

    initializeOpenGLFunctions();

    QTimer *repaintTimer = new QTimer(this);
    connect(repaintTimer, &QTimer::timeout, this, &MyWindow::render);
    repaintTimer->start(1000/60);

    QTimer *elapsedTimer = new QTimer(this);
    connect(elapsedTimer, &QTimer::timeout, this, &MyWindow::modCurTime);
    elapsedTimer->start(1);
}

void MyWindow::modCurTime()
{
    currentTimeMs++;
    currentTimeS=currentTimeMs/1000.0f;
}

void MyWindow::initialize()
{
    mFuncs->glGenVertexArrays(1, &mVAO);
    mFuncs->glBindVertexArray(mVAO);

    CreateVertexBuffer();
    initShaders();

    mRotationMatrixLocation = mProgramCol->uniformLocation("RotationMatrix");

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void MyWindow::CreateVertexBuffer()
{  
    mVerticesCol[0] = vFactory.MakeVertex(QVector3D(-0.8f, -0.8f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f));
    mVerticesCol[1] = vFactory.MakeVertex(QVector3D(-0.2f, -0.8f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f));
    mVerticesCol[2] = vFactory.MakeVertex(QVector3D(-0.5f, -0.2f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f));

    glGenBuffers(1, &mVBOCol);

    glBindBuffer(GL_ARRAY_BUFFER, mVBOCol);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVerticesCol[0]) * 3, mVerticesCol, GL_STATIC_DRAW);

    mVerticesNorm[0] = vFactory.MakeVertex(QVector3D( 0.2f, -0.8f, 0.0f), QVector3D(1.0f, 1.0f, 0.0f));
    mVerticesNorm[1] = vFactory.MakeVertex(QVector3D( 0.8f, -0.8f, 0.0f), QVector3D(0.0f, 1.0f, 1.0f));
    mVerticesNorm[2] = vFactory.MakeVertex(QVector3D( 0.5f, -0.2f, 0.0f), QVector3D(1.0f, 0.0f, 1.0f));

    glGenBuffers(1, &mVBONorm);

    glBindBuffer(GL_ARRAY_BUFFER, mVBONorm);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVerticesNorm[0]) * 3, mVerticesNorm, GL_STATIC_DRAW);
}

void MyWindow::resizeEvent(QResizeEvent *)
{
    mUpdateSize = true;
}

void MyWindow::render()
{
    if(!isVisible() || !isExposed())
        return;

    if (!mContext->makeCurrent(this))
        return;

    static bool initialized = false;
    if (!initialized) {
        initialize();
        initialized = true;
    }

    if (mUpdateSize) {
        glViewport(0, 0, size().width(), size().height());
        mUpdateSize = false;
    }

    static float EvolvingVal = 0;
    EvolvingVal += 0.1f;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 RotationMatrix;

    RotationMatrix.rotate(EvolvingVal, QVector3D(0.0f, 0.0f, 0.1f));

    glBindBuffer(GL_ARRAY_BUFFER, mVBOCol);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    mFuncs->glBindVertexBuffer(0, mVBOCol, 0, sizeof(mVerticesCol[0]));
    mFuncs->glBindVertexBuffer(1, mVBOCol, 0, sizeof(mVerticesCol[0]));

    mFuncs->glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    mFuncs->glVertexAttribBinding(0, 0);

    mFuncs->glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, sizeof(mVerticesCol[0].getPos())+ sizeof(mVerticesCol[0].getNormal()));
    mFuncs->glVertexAttribBinding(1, 1);

    mProgramCol->bind();
    {
        glUniformMatrix4fv(mRotationMatrixLocation, 1, GL_FALSE, RotationMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
    mProgramCol->release();

    glBindBuffer(GL_ARRAY_BUFFER, mVBONorm);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    mFuncs->glBindVertexBuffer(0, mVBONorm, 0, sizeof(mVerticesNorm[0]));
    mFuncs->glBindVertexBuffer(1, mVBONorm, 0, sizeof(mVerticesNorm[0]));

    mFuncs->glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    mFuncs->glVertexAttribBinding(0, 0);

    mFuncs->glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, sizeof(mVerticesNorm[0].getPos()));
    mFuncs->glVertexAttribBinding(1, 1);

    mProgramNorm->bind();
    {
        glUniformMatrix4fv(mRotationMatrixLocation, 1, GL_FALSE, RotationMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
    mProgramNorm->release();

    mContext->swapBuffers(this);
}

void MyWindow::initShaders()
{
    QOpenGLShader vShader(QOpenGLShader::Vertex);
    QOpenGLShader fShader(QOpenGLShader::Fragment);    
    QFile         shaderFile;
    QByteArray    shaderSource;

    // Shader color
    shaderFile.setFileName(":/vshader_col.txt");
    shaderFile.open(QIODevice::ReadOnly);
    shaderSource = shaderFile.readAll();
    shaderFile.close();
    qDebug() << "vertex \"color\" compile: " << vShader.compileSourceCode(shaderSource);

    shaderFile.setFileName(":/fshader_col.txt");
    shaderFile.open(QIODevice::ReadOnly);
    shaderSource = shaderFile.readAll();
    shaderFile.close();
    qDebug() << "frag   \"color\" compile: " << fShader.compileSourceCode(shaderSource);

    mProgramCol = new (QOpenGLShaderProgram);
    mProgramCol->addShader(&vShader);
    mProgramCol->addShader(&fShader);
    qDebug() << "shader \"color\" link: " << mProgramCol->link();

    // Shader normal
    shaderFile.setFileName(":/vshader_norm.txt");
    shaderFile.open(QIODevice::ReadOnly);
    shaderSource = shaderFile.readAll();
    shaderFile.close();
    qDebug() << "vertex \"normal\" compile: " << vShader.compileSourceCode(shaderSource);

    shaderFile.setFileName(":/fshader_norm.txt");
    shaderFile.open(QIODevice::ReadOnly);
    shaderSource = shaderFile.readAll();
    shaderFile.close();
    qDebug() << "frag   \"normal\" compile: " << fShader.compileSourceCode(shaderSource);

    mProgramNorm = new (QOpenGLShaderProgram);
    mProgramNorm->addShader(&vShader);
    mProgramNorm->addShader(&fShader);
    qDebug() << "shader \"normal\" link: " << mProgramNorm->link();
}

void MyWindow::PrepareTexture(GLenum TextureTarget, const QString& FileName, GLuint& TexObject, bool flip)
{
    QImage TexImg;

    if (!TexImg.load(FileName)) qDebug() << "Erreur chargement texture";
    if (flip==true) TexImg=TexImg.mirrored();

    glGenTextures(1, &TexObject);
    glBindTexture(TextureTarget, TexObject);
    glTexImage2D(TextureTarget, 0, GL_RGB, TexImg.width(), TexImg.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, TexImg.bits());
    glTexParameterf(TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void MyWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_P:
            break;
        case Qt::Key_Up:
            break;
        case Qt::Key_Down:
            break;
        case Qt::Key_Left:
            break;
        case Qt::Key_Right:
            break;
        case Qt::Key_Delete:
            break;
        case Qt::Key_PageDown:
            break;
        case Qt::Key_Home:
            break;
        case Qt::Key_Z:
            break;
        case Qt::Key_Q:
            break;
        case Qt::Key_S:
            break;
        case Qt::Key_D:
            break;
        case Qt::Key_A:
            break;
        case Qt::Key_E:
            break;
        default:
            break;
    }
}


void MyWindow::printMatrix(const QMatrix4x4& mat)
{
    const float *locMat = mat.transposed().constData();

    for (int i=0; i<4; i++)
    {
        qDebug() << locMat[i*4] << " " << locMat[i*4+1] << " " << locMat[i*4+2] << " " << locMat[i*4+3];
    }
}
