#include "gamecell.h"

GameCell::GameCell(quint32 x, quint32 y, Team cell_team) : state(ALIVE), team(cell_team)
{
    coordinates = QPoint(x, y);
}
