#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include "mainwindow.h"
#include "UI/gridtemplatebutton.h"

#include "ui_mainwindow.h"
#include "ui_templateform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tf(new Ui::TemplateForm),
    currentColor(QColor("#000")),
    game(new GameWidget(this))
{
    ui->setupUi(this);

    QPixmap icon(16, 16);
    icon.fill(currentColor);
    ui->colorButton->setIcon( QIcon(icon) );

    connect(ui->startButton, SIGNAL(clicked()), game,SLOT(startGame()));
    connect(ui->stopButton, SIGNAL(clicked()), game,SLOT(stopGame()));
    connect(ui->clearButton, SIGNAL(clicked()), game,SLOT(clear()));
    connect(ui->iterInterval, SIGNAL(valueChanged(int)), game, SLOT(setInterval(int)));
    connect(ui->iterInterval, SIGNAL(valueChanged(int)), ui->intervalLabel, SLOT(setNum(int)));
    connect(ui->cellsControl, SIGNAL(valueChanged(int)), game, SLOT(setCellNumber(int)));
    connect(ui->cellsControl, SIGNAL(valueChanged(int)), ui->sizeLabel, SLOT(setNum(int)));
    connect(ui->colorButton, SIGNAL(clicked()), this, SLOT(selectMasterColor()));
    connect(ui->insertNewButton, SIGNAL(clicked()), this, SLOT(insertTemplateButton()));

    ui->mainLayout->setStretchFactor(ui->gameLayout, 8);
    ui->mainLayout->setStretchFactor(ui->setLayout, 2);
    ui->gameLayout->addWidget(game);

    settings.beginGroup("templatebuttons");
    for(QString name : settings.childKeys())
    {
        CellTemplateObject* newTemplate = CellTemplateObject::fromByteArray(settings.value(name).toByteArray());
        insertTemplateButton(newTemplate);
    }
    settings.endGroup();
}

MainWindow::~MainWindow()
{
    QList<GridTemplateButton *> buttons = ui->elements->findChildren<GridTemplateButton *>();
    settings.beginGroup("templatebuttons");
    for(GridTemplateButton * curr : buttons)
    {
        settings.setValue(curr->objectName(), QVariant(curr->getCellTemplate()->toByteArray()));
    }
    settings.endGroup();
    settings.sync();
    //for(QWidget : this->children());
    delete ui;
}

void MainWindow::selectMasterColor()
{
    QColor color = QColorDialog::getColor(currentColor, NULL, tr("Select color of figures"));
    if(!color.isValid())
        return;
    currentColor = color;
    game->setMasterColor(color);
    QPixmap icon(16, 16);
    icon.fill(color);
    ui->colorButton->setIcon( QIcon(icon) );
}

void MainWindow::insertTemplateButton(CellTemplateObject *cellTemplate)
{
    GridTemplateButton* curr = new GridTemplateButton(ui->templateButtons->parentWidget(), cellTemplate);
    curr->setMinimumSize(150, 150);
    curr->setMaximumSize(150, 150);
    curr->setObjectName("template" + QString::number(ui->templateButtons->count()));
    ui->templateButtons->addWidget(curr);
}
