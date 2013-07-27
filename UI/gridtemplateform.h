#ifndef GRIDTEMPLATEFORM_H
#define GRIDTEMPLATEFORM_H

#include <QWidget>
#include "ui_templateform.h"
#include "celltemplateobject.h"

class GridTemplateForm : public QWidget
{
    Q_OBJECT
public:
    explicit GridTemplateForm(QWidget *parent = 0, CellTemplateObject *cellTemplate = NULL);
    ~GridTemplateForm();
private:
    Ui::TemplateForm * tf;
    
signals:
    
public slots:
    
};

#endif // GRIDTEMPLATEFORM_H
