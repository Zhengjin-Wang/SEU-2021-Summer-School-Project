#include "courseinfodialog.h"
#include "ui_courseinfodialog.h"

CourseInfoDialog::CourseInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseInfoDialog)
{
    ui->setupUi(this);
}

CourseInfoDialog::~CourseInfoDialog()
{
    delete ui;
}
