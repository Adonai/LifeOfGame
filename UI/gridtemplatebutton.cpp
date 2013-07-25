#include "gridtemplatebutton.h"
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

#define buttonCellSize 40

GridTemplateButton::GridTemplateButton(QWidget *parent, CellTemplateObject *object) :
    QPushButton(parent), templateObject(object)
{

}

GridTemplateButton::~GridTemplateButton()
{
    delete templateObject;
}

void GridTemplateButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

void GridTemplateButton::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::RightButton)
    {
        QPushButton::mousePressEvent(e);

        double cellWidth = (double)width()/buttonCellSize;
        double cellHeight = (double)height()/buttonCellSize;
        int x = floor((e->x() - 10)/cellWidth) + 1;
        int y = floor((e->y() - 10)/cellHeight) + 1;

        auto iter = templateObject->getPainter();
        if(!iter.findNext(GameCell(x, y)))
            templateObject->addCell(GameCell(x, y));
        else
            templateObject->removeCell(GameCell(x,y));
        update();
    }
    if(e->buttons() == Qt::LeftButton)
    {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        mimeData->setData(QString("text/pointer"), QByteArray::number((qlonglong)templateObject));
        drag->setMimeData(mimeData);
        drag->exec();
    }
}

void GridTemplateButton::paintGrid(QPainter &p)
{
    QColor gridColor = "#000"; // color of the grid
    gridColor.setAlpha(50); // must be lighter than main color
    p.setPen(gridColor);
    double cellWidth = (double)width()/buttonCellSize; // width of the widget / number of cells at one row
    for(double x = 10; x <= width() - 10; x += cellWidth)
        p.drawLine(x, 10, x, height() - 10);
    double cellHeight = (double)height()/buttonCellSize; // height of the widget / number of cells at one row
    for(double y = 10; y <= height() - 10; y += cellHeight)
        p.drawLine(10, y, width() - 10, y);
}

void GridTemplateButton::paintUniverse(QPainter &p)
{
    double cellWidth = (double)width()/buttonCellSize;
    double cellHeight = (double)height()/buttonCellSize;
    auto iter = templateObject->getPainter();
    while(iter.hasNext())
    {
        GameCell cell = iter.next();
        qreal left = (qreal)(cellWidth*cell.x() - cellWidth); // margin from left
        qreal top  = (qreal)(cellHeight*cell.y() - cellHeight); // margin from top
        QRectF r(10 + left, 10 + top, (qreal)cellWidth, (qreal)cellHeight);
        p.fillRect(r, QBrush("#000")); // fill cell with brush of main color
    }
}
