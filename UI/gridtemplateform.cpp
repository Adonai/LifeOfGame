#include "gridtemplateform.h"

GridTemplateForm::GridTemplateForm(QWidget *parent, CellTemplateObject *cellTemplate) :
    QWidget(parent), tf(new Ui::TemplateForm)
{
    tf->setupUi(this);
    tf->templateButton->setCellTemplate(cellTemplate);
    tf->applyButton->hide();
    tf->descriptionEdit->hide();
    tf->eraseButton->hide();
}

GridTemplateForm::~GridTemplateForm()
{
    delete tf;
}
