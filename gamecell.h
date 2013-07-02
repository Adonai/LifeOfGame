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
    GameCell(int x, int y, Team cell_team = TEAM_1);
    int x() const { return coordinates.x(); }
    int y() const { return coordinates.y(); }
    const QPoint getCoords() const { return coordinates; }
    bool isAlive() { return state == ALIVE; }
private:
    LifeState state;
    Team team;
    QPoint coordinates;
};

#endif // GAMECELL_H
