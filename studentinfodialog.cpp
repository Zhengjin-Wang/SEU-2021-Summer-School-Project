#include "studentinfodialog.h"
#include "ui_studentinfodialog.h"
#include "QDebug"
#include "changegradedialog.h"
#include<QMessageBox>

StudentInfoDialog::StudentInfoDialog(Student* student, MainWindow *parent) :
    QDialog(nullptr),
    ui(new Ui::StudentInfoDialog)
{
    ui->setupUi(this);
    this->student = student;
    this->mainwindow = parent;

    this->setWindowTitle(student->getId()+student->getName()+"的选课信息");
    ui->info_table->setSelectionBehavior(QAbstractItemView::SelectRows);

    //将选课信息显示在table上
    int size = student->course_list.size();
    for(int i = 0; i < size; ++i){
        QString course_id = student->course_list.keys()[i];
        addCourseInView(course_id,i);
    }
}

StudentInfoDialog::~StudentInfoDialog()
{
    delete ui;
}

void StudentInfoDialog::addCourseInView(const QString& course_id,int index)
{
    if(!mainwindow->all_course_list.keys().contains(course_id)) return;
    //将加入的课程信息加入到表格中
    if(index < 0) index = student->course_list.size() - 1;
    ui->info_table->setRowCount(index + 1);//必须设置行数，否则无法显示新增信息

    Course *course = mainwindow->all_course_list[course_id];

    ui->info_table->setItem(index,0,new QTableWidgetItem(course->getId()));
    ui->info_table->setItem(index,1,new QTableWidgetItem(course->getName()));
    ui->info_table->setItem(index,2,new QTableWidgetItem(QString::number(course->getCredit())));
    ui->info_table->setItem(index,3,new QTableWidgetItem(course->getTerm()));
    ui->info_table->setItem(index,4,new QTableWidgetItem(course->getClassroom()));
    ui->info_table->setItem(index,5,new QTableWidgetItem(QString::number(course->student_list.size())));
    ui->info_table->setItem(index,6,new QTableWidgetItem(QString::number(student->course_list[course_id])));
    //使单元格内容居中
    for(int i = 0; i<7; ++i){
        QTableWidgetItem* item = ui->info_table->item(index,i);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        item->setFlags((Qt::ItemFlags) 33);
    }
}

void StudentInfoDialog::on_add_button_clicked()
{
    QString course_id = "";

    QList<QString> course_list =  student->course_list.keys(); //这是课程id
    QList<QString> valid_course_list;
    valid_course_list.reserve(mainwindow->course_map.size() - course_list.size());
    bool empty = true;

    for(QString& course_name : mainwindow->course_map.keys()){
        if(!course_list.contains(mainwindow->course_map[course_name])){
            if(empty) empty = false;
            valid_course_list.append(course_name);
        }
    }

    if(empty){
        QMessageBox::information(mainwindow,"提示","该学生已经没有可添加的课程");
    }
    else{
        AddCourseDialog dlg(student, mainwindow, &course_id, &valid_course_list);
        dlg.exec();
        addCourseInView(course_id);
    }
}

void StudentInfoDialog::on_del_button_clicked()
{
    int row = ui->info_table->currentRow();
    if(row < 0){
        QApplication::beep();
        return;
    }

    bool confirm = false;
    DelDialog dlg(&confirm);
    dlg.exec();

    if(confirm){
        QString course_id = ui->info_table->item(row,0)->text();
        if(!mainwindow->all_course_list[course_id]->delStudent(student)) student->delCourse(course_id);
        ui->info_table->removeRow(row);
    }
}

void StudentInfoDialog::on_change_button_clicked()
{   int row = ui->info_table->currentRow();
    if(row < 0){
         QApplication::beep();
         return;
    }

    QString course_id = ui->info_table->item(row,0)->text();
    int old_grade = student->course_list[course_id];
    int grade = old_grade;
    ChangeGradeDialog dlg(&grade);
    dlg.exec();

    if(grade == old_grade) return;
    else {
        student->course_list[course_id] = grade;
        mainwindow->updateStudentGrade(mainwindow->all_course_list[course_id],student);
        ui->info_table->item(row,6)->setText(QString::number(grade));
    }
}
