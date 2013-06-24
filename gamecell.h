#ifndef GAMECELL_H
#define GAMECELL_H
#include <QPair>

enum LifeState
{
    DEAD,
    ALIVE
};

enum Team
{
    TEAM_1 = 1,
    TEAM_2
};

class GameCell
{
public:
    GameCell(quint32 x, quint32 y, Team cell_team = TEAM_1);
    quint32 x() const { return coordinates.first; }
    quint32 y() const { return coordinates.second; }
    const QPair<quint32, quint32> getCoords() const { return coordinates; }
    bool isAlive() { return state == ALIVE; }
private:
    LifeState state;
    Team team;
    QPair<quint32, quint32> coordinates;
};

#endif // GAMECELL_H
