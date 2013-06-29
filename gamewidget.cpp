#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <QDateTime>
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureSynchronizer>

#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    universeSize(50),
    cameraMode(false)
{
    timer->setInterval(300);
    m_masterColor[0] = "#000";
    m_masterColor[1] = "#000";
    m_masterColor[2] = "#090";
    m_masterColor[3] = "#099";
    m_masterColor[4] = "#900";
    m_masterColor[5] = "#909";
    m_masterColor[6] = "#990";
    m_masterColor[7] = "#999";
    m_masterColor[8] = "#009";

    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
}

GameWidget::~GameWidget()
{
}

void GameWidget::startGame()
{
    timer->start();
}

void GameWidget::stopGame()
{
    timer->stop();
}

void GameWidget::clear()
{
    cellGrid.clear();
    update();
}

void GameWidget::setCellNumber(const int &s)
{
    universeSize = s;
    update();
}

void GameWidget::setInterval(int msec)
{
    timer->setInterval(msec);
}

quint8 GameWidget::checkPoint(quint32 x, quint32 y)
{
    if(x < 1 || x > MAX_UNIVERSE_SIZE || y < 1 || y > MAX_UNIVERSE_SIZE)
        return 0;

    quint8 power = 0;
    if(cellGrid.isAlive(x - 1, y - 1)) power ++;
    if(cellGrid.isAlive(x,     y - 1)) power ++;
    if(cellGrid.isAlive(x + 1, y - 1)) power ++;
    if(cellGrid.isAlive(x - 1, y    )) power ++;
    if(cellGrid.isAlive(x + 1, y    )) power ++;
    if(cellGrid.isAlive(x - 1, y + 1)) power ++;
    if(cellGrid.isAlive(x,     y + 1)) power ++;
    if(cellGrid.isAlive(x + 1, y + 1)) power ++;

    if (((cellGrid.isAlive(x, y)) && (power == 2)) || (power == 3))
           cellGridNext.addCell(x, y);
    return 0;
}

void GameWidget::newGeneration()
{
    qint64 current = QDateTime::currentDateTime().toMSecsSinceEpoch();
    const QList<GameCell> cells = cellGrid.getCells();
    qreal perThreadCount = cells.size() / (float) QThread::idealThreadCount();

    cellGridNext.clear();

    // let all CPU cores work
    QFutureSynchronizer<void> syncer;
    for(qreal startCell = 0; startCell < cells.size(); startCell += perThreadCount)
    {
        QFuture<void> partParser = QtConcurrent::run(this, &GameWidget::processPart, qRound(startCell), qRound(startCell + perThreadCount));
        syncer.addFuture(partParser);
    }
    // wait for all futures to finish
    syncer.waitForFinished();

    cellGrid = cellGridNext;
    qDebug() << QDateTime::currentDateTime().toMSecsSinceEpoch() - current << "  " << cellGrid.getCells().size();
    update();
}

// part processing procedure
void GameWidget::processPart(quint32 start, quint32 end)
{
    for(quint32 i = start; i < end; i++)
    {
        // check all fields around
        int x = cellGrid.getCells().at(i).x(), y = cellGrid.getCells().at(i).y();
        checkPoint(x - 1, y - 1);
        checkPoint(x, y - 1);
        checkPoint(x + 1, y - 1);

        checkPoint(x - 1, y);
        checkPoint(x + 1, y);

        checkPoint(x - 1, y + 1);
        checkPoint(x, y + 1);
        checkPoint(x + 1, y + 1);
    }
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton)
    {
        double cellWidth = (double)width()/universeSize;
        double cellHeight = (double)height()/universeSize;
        int x = floor((e->x() - edge.x())/cellWidth) + 1;
        int y = floor((e->y() - edge.x())/cellHeight) + 1;
        if(cellGrid.isAlive(x, y))
            cellGrid.removeCell(x, y);
        else
            cellGrid.addCell(x, y);
        update();
    }

    if(e->buttons() == Qt::RightButton)
    {
        cameraMode = true;
        mousePos = e->pos() - edge;
    }
}

void GameWidget::mouseMoveEvent(QMouseEvent *e)
{
    // сохраняем последнюю координату,
    // чтоб при колебаниях мыши в одном квадратике
    // он не инвертировался
    static QPair<int, int> lastCoords(0, 0);

    if(e->buttons() == Qt::LeftButton)
    {
        double cellWidth = (double)width()/universeSize;
        double cellHeight = (double)height()/universeSize;
        int x = floor((e->x() - edge.x())/cellWidth) + 1;
        int y = floor((e->y() - edge.y())/cellHeight) + 1;
        if(lastCoords != qMakePair(x, y))
        {
            if(cellGrid.isAlive(x, y))
                cellGrid.removeCell(x, y);
            else
                cellGrid.addCell(x, y);
            lastCoords = qMakePair(x, y);
        }
        update();
    }

    if(e->buttons() == Qt::RightButton)
    {
        edge = e->pos() - mousePos;
        update();
    }
}

void GameWidget::mouseReleaseEvent(QMouseEvent *e)
{
    cameraMode = false;
}

void GameWidget::wheelEvent(QWheelEvent *e)
{

}

void GameWidget::paintGrid(QPainter &p)
{
    QRect borders(0, 0, width() - 1, height() - 1); // borders of the universe
    QColor gridColor = m_masterColor[0]; // color of the grid
    gridColor.setAlpha(50); // must be lighter than main color
    p.setPen(gridColor);
    double cellWidth = (double)width()/universeSize; // width of the widget / number of cells at one row
    for(double x = cellWidth; x + edge.x() <= width(); x += cellWidth)
        p.drawLine(x + edge.x(), 0, x + edge.x(), height());
    double cellHeight = (double)height()/universeSize; // height of the widget / number of cells at one row
    for(double y = cellHeight; y + edge.y() <= height(); y += cellHeight)
        p.drawLine(0, y + edge.y(), width(), y + edge.y());
    p.drawRect(borders);
}

void GameWidget::paintUniverse(QPainter &p)
{
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    for(auto cell : cellGrid.getCells())
    { // if there is any sense to paint it
        qreal left = (qreal)(cellWidth*cell.x() - cellWidth); // margin from left
        qreal top  = (qreal)(cellHeight*cell.y() - cellHeight); // margin from top
        QRectF r(left + edge.x(), top + edge.y(), (qreal)cellWidth, (qreal)cellHeight);
        p.fillRect(r, QBrush(m_masterColor[0])); // fill cell with brush of main color
    }
}

QColor GameWidget::masterColor()
{
    return m_masterColor[0];
}

void GameWidget::setMasterColor(const QColor &color)
{
    m_masterColor[0] = color;
    update();
}
