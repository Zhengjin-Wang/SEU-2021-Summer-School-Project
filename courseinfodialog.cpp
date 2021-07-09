#include "courseinfodialog.h"
#include "ui_courseinfodialog.h"

CourseInfoDialog::CourseInfoDialog(Course *course, QWidget *parent) :
    QDialog(nullptr),
    ui(new Ui::CourseInfoDialog)
{
    ui->setupUi(this);
    this->course = course;
    this->mainwindow = dynamic_cast<MainWindow*>(parent);

    this->setWindowTitle(course->getId() + course->getName() + "的选课学生信息");
    init();
}


CourseInfoDialog::~CourseInfoDialog()
{
    delete ui;
}

void CourseInfoDialog::init()
{
    int size = course->student_list.size();
    ui->info_table->setRowCount(size);
    QString course_id = course->getId();

    for(int i = 0; i < size; ++i){
        Student *student = course->student_list[i];
        ui->info_table->setItem(i,0,new QTableWidgetItem(student->getId()));
        ui->info_table->setItem(i,1,new QTableWidgetItem(student->getName()));
        ui->info_table->setItem(i,2,new QTableWidgetItem(student->getClass()));
        ui->info_table->setItem(i,3,new QTableWidgetItem(QString::number((*student)[course_id])));
        ui->info_table->setItem(i,4,new QTableWidgetItem(QString::number(i+1)));

        for(int j = 0; j<5; ++j){
            QTableWidgetItem* item = ui->info_table->item(i,j);
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            item->setFlags((Qt::ItemFlags) 32);
        }
    }

}
