#ifndef CELLTEMPLATEOBJECT_H
#define CELLTEMPLATEOBJECT_H

#include "gamecell.h"
#include "gamewidget.h"

class CellTemplateObject
{
public:
    CellTemplateObject(QList<GameCell> cells);
    QListIterator<GameCell> getPainter() const;
private:
    void countBounds();
    QList<GameCell> templateCells;
    int width, height;
};

#endif // CELLTEMPLATEOBJECT_H
