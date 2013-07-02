#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <QList>
#include <QMutex>
#include <memory.h>

#include "gamecell.h"

#define MAX_UNIVERSE_SIZE 1000

class GameWidget;

/**
 * @brief The GameGrid class
 * This class is used for fast search of alive cells
 */

class GameGrid
{
public:
    GameGrid();
    ~GameGrid();

    void addCell(int x, int y, Team team = TEAM_1);
    void removeCell(int x, int y);
    bool isAlive(quint32 x, quint32 y) const;
    const QList<GameCell>& getCells() const;
    void clear();
private:
    QMutex* mutex;
    quint8 gridPoints[MAX_UNIVERSE_SIZE][MAX_UNIVERSE_SIZE];
    //  could do it with pointers, but cells are really dying too fast.
    QList<GameCell> gridCells;
};

#endif // GAMEGRID_H
