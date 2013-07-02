#include "gamecell.h"

GameCell::GameCell(int x, int y, Team cell_team) : state(ALIVE), team(cell_team)
{
    coordinates = QPoint(x, y);
}
