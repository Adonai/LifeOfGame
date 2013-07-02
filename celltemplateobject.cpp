#include "celltemplateobject.h"

CellTemplateObject::CellTemplateObject(QList<GameCell> cells) : templateCells(cells)
{
    countBounds();
}

QListIterator<GameCell> CellTemplateObject::getPainter() const
{
    return QListIterator<GameCell>(templateCells);
}

void CellTemplateObject::countBounds()
{
    QPoint leftUp = templateCells.front().getCoords(), rightDown = templateCells.back().getCoords();
    for(GameCell cell : templateCells)
    {
        if(leftUp.x() > cell.x())
            leftUp.setX(cell.x());

        if(leftUp.y() > cell.y())
            leftUp.setY(cell.y());

        if(rightDown.x() < cell.x())
            rightDown.setX(cell.x());

        if(rightDown.y() < cell.y())
            rightDown.setY(cell.y());
    }

    width = rightDown.x() - leftUp.x();
    height = rightDown.y() - leftUp.y();
}
