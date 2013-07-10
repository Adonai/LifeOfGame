#include "celltemplateobject.h"

CellTemplateObject::CellTemplateObject(QList<GameCell> cells) : templateCells(cells)
{
    countBounds();
}

QListIterator<GameCell> CellTemplateObject::getPainter() const
{
    return QListIterator<GameCell>(templateCells);
}

const QByteArray CellTemplateObject::toByteArray() const
{
    QByteArray data;
    for(GameCell cell : templateCells)
        data.append(QString::number(cell.x()) + ";" + QString::number(cell.y()) + "#");

    return data;
}

CellTemplateObject* CellTemplateObject::fromByteArray(QByteArray source)
{
    QList<GameCell> cells;
    auto cellList = source.split('#');
    for(QByteArray coords : cellList)
    {
        if(coords.isEmpty())
            continue;

        QList<QByteArray> point = coords.split(';');
        cells.append(GameCell(point.at(0).toInt(), point.at(1).toInt()));
    }

    return new CellTemplateObject(cells);
}

void CellTemplateObject::countBounds()
{
    if(templateCells.isEmpty())
        return; // do not count bounds for empty templates

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
