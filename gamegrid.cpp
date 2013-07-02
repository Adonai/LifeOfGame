#include <QDebug>

#include "gamegrid.h"

GameGrid::GameGrid()
{
    mutex = new QMutex;
    memset(gridPoints, 0, sizeof(gridPoints));
}

GameGrid::~GameGrid()
{
    delete mutex;
}

// hmm does it look thread-safe?
// NO :(
void GameGrid::addCell(int x, int y, Team team)
{
    if(isAlive(x, y))
        return;

    mutex->lock();
    gridPoints[x][y] = team;
    gridCells.append(GameCell(x, y, team));
    mutex->unlock();
}

void GameGrid::removeCell(int x, int y)
{
    gridPoints[x][y] = 0;
    auto it = gridCells.begin();
    while(it != gridCells.end())
        if(it->x() == x && it->y() == y)
            it = gridCells.erase(it);
        else
            it++;
}

bool GameGrid::isAlive(quint32 x, quint32 y) const
{
    return gridPoints[x][y] > 0;
}

const QList<GameCell> &GameGrid::getCells() const
{
    return gridCells;
}

void GameGrid::clear()
{
    memset(gridPoints, 0, sizeof(gridPoints));
    gridCells.clear();
}
