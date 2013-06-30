#ifndef CELLTEMPLATEOBJECT_H
#define CELLTEMPLATEOBJECT_H

#include "gamecell.h"
#include "gamewidget.h"

class CellTemplateObject
{
public:
    CellTemplateObject(QList<GameCell> cells);
    void pasteObject(GameGrid* grid);
private:
    QList<GameCell> templateCells;
};

#endif // CELLTEMPLATEOBJECT_H
