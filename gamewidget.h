#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QtOpenGL/QGLWidget>
#include <QThreadPool>

#include "gamegrid.h"
#include "celltemplateobject.h"

class CellTemplateObject;

class GameWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    void pasteObject(CellTemplateObject* obj, QPoint leftUpperEdge = QPoint());

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

signals:
    
public slots:
    void startGame(); // start
    void stopGame(); // finish
    void clear(); // clear
    void setCellNumber(const int &s); // set number of the cells in one row
    void setInterval(int msec); // set interval between generations

    QColor masterColor(); // color of the cells
    void setMasterColor(const QColor &color); // set color of the cells

private slots:
    void paintGrid(QPainter &p);
    void paintUniverse(QPainter &p);
    void newGeneration();

private:
    QColor m_masterColor[9];
    QTimer* timer;
    int universeSize;

    GameGrid cellGrid;
    GameGrid cellGridNext;

    QPoint edge, mousePos;
    bool cameraMode;

    quint8 checkPoint(quint32 x, quint32 y);
    void processPart(quint32 start, quint32 end);
};

#endif // GAMEWIDGET_H
