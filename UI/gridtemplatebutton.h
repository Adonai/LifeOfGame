#ifndef GRIDTEMPLATEBUTTON_H
#define GRIDTEMPLATEBUTTON_H

#include <QPushButton>
#include "celltemplateobject.h"

class GridTemplateButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GridTemplateButton(QWidget *parent = 0, CellTemplateObject* object = NULL);
    ~GridTemplateButton();

    const CellTemplateObject* getCellTemplate() const { return templateObject; }
    void setCellTemplate(CellTemplateObject* object) { delete templateObject; templateObject = object; }
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
    CellTemplateObject* templateObject;
    bool editable;

signals:
    
private slots:
    void paintGrid(QPainter &p);
    void paintUniverse(QPainter &p);
    void edit();
    void apply();
    
};

#endif // GRIDTEMPLATEBUTTON_H
