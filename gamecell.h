#ifndef GAMECELL_H
#define GAMECELL_H
#include <QPoint>

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
    quint32 x() const { return coordinates.x(); }
    quint32 y() const { return coordinates.y(); }
    const QPoint getCoords() const { return coordinates; }
    bool isAlive() { return state == ALIVE; }
private:
    LifeState state;
    Team team;
    QPoint coordinates;
};

#endif // GAMECELL_H
