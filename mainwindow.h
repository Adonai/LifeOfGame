#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QSettings>
#include "gamewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void selectMasterColor();
    void insertTemplateButton(CellTemplateObject* cellTemplate = new CellTemplateObject(QList<GameCell>()));

private:
    Ui::MainWindow *ui;
    QColor currentColor;
    GameWidget* game;
    QSettings settings;
};

#endif // MAINWINDOW_H
