#ifndef CELLTEMPLATEOBJECT_H
#define CELLTEMPLATEOBJECT_H

#include "gamecell.h"
#include "gamewidget.h"

class CellTemplateObject
{
public:
    CellTemplateObject(QList<GameCell> cells);
    QListIterator<GameCell> getPainter() const;
    void addCell(GameCell gc) { templateCells.append(gc); countBounds(); }
    void removeCell(GameCell gc) { templateCells.removeAll(gc); }
    const QByteArray toByteArray() const;
private:
    void countBounds();
    QList<GameCell> templateCells;
    int width, height;
};

#endif // CELLTEMPLATEOBJECT_H
