#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTableWidget>
#include "deldialog.h"
#include<QFile>
#include<QTextStream>
#include<QDir>
#include "studentinfodialog.h"
#include "updatestudentdialog.h"
#include "QApplication"

#include<QDebug>
#define TABLE_FLAG 33
#define DEBUG

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadFile();
    //connect(ui->tableWidget->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(test(QModelIndex,QModelIndex,QVector<int>)));
    ui->student_info_table->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->exit_button,&QPushButton::clicked,this,[=](){
        bool flag = false;
            DelDialog *dlg = new DelDialog(&flag,"您确定要退出吗？","是","否"); //创建对象时为什么会自动弹出弹窗
            dlg->exec();
            if(flag){
                saveFile();
                application_ptr->exit();
            }
    });
}

MainWindow::~MainWindow()
{

    for(Student* student : all_student_list){
        delete student;
    }
    for(Course* course : all_course_list){
        delete course;
    }
    delete ui;
}

void MainWindow::addStudent(const QString& student_id,Student* student)
{
    if(all_student_list.find(student_id)!=all_student_list.end()) return;
    all_student_list.insert(student_id, student);

    //在table中添加元素
    int index = all_student_list.size() - 1;
    student->row = index;
    ui->student_info_table->setRowCount(index + 1);//必须设置行数，否则无法显示新增信息

    ui->student_info_table->setItem(index,0,new QTableWidgetItem(student->getId()));
    ui->student_info_table->setItem(index,1,new QTableWidgetItem(student->getName()));
    ui->student_info_table->setItem(index,2,new QTableWidgetItem(student->getClass()));
    ui->student_info_table->setItem(index,3,new QTableWidgetItem(student->getPhone()));
    ui->student_info_table->setItem(index,4,new QTableWidgetItem(QString("%1-%2-%3").arg(student->getBirth().year()).arg(student->getBirth().month()).arg(student->getBirth().day())));
    ui->student_info_table->setItem(index,5,new QTableWidgetItem(student->getAddress()));

    //使单元格内容居中，设为不可编辑
    for(int i = 0; i<6; ++i){
        QTableWidgetItem* item = ui->student_info_table->item(index,i);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        item->setFlags((Qt::ItemFlags) TABLE_FLAG);
    }

    //添加显示选课信息的按钮
    ui->student_info_table->setCellWidget(index,6,student->student_button = new StudentButton(student,this));
    connect(student->student_button, &QPushButton::clicked,this,[=](){
        StudentInfoDialog* dlg = new StudentInfoDialog(student,this);
        dlg->show();
    });
}

void MainWindow::delStudent(const QString& student_id)
{
    delete all_student_list[student_id];
    all_student_list.remove(student_id);
}

void MainWindow::addCourse(const QString& course_id,Course* course)
{

}

void MainWindow::delCourse(const QString& course_id)
{

}

//在读文件时，尽管没有明确学生与课程的关系，但在输入数据时应本来自洽，利用名称索引可以找到关系
void MainWindow::loadFile()
{
    //读取学生信息（包括学生的选课情况及成绩）
    QFile student_file(QDir::currentPath() + "\\studentList.txt");
    student_file.open(QIODevice::ReadOnly);
    QByteArray content = student_file.readAll();
    QTextStream tstream(content);
    tstream.setCodec("utf-8");
    student_file.close();

    int s_size;
    tstream >> s_size;
    QString student_id,name,_class,phone,address;
    int year,month,day;
    QString choose_course;
    int course_amount,grade;
    Student* student;

    for(int i = 0 ; i < s_size ; ++i){
        tstream >> student_id >> name >>_class >> phone >> year >> month >> day >> address;
        addStudent(student_id,student = new Student(student_id,name,_class,phone,QDate(year,month,day),address));
        tstream >> course_amount;
        for(int j = 0; j < course_amount; ++j){
            tstream >> choose_course >> grade;
            student->addCourse(choose_course, grade);
        }
    }

    //读取课程信息（包括哪些学生选课，按成绩降序排列） 同时录入course_map<课程名称， 课程编号>

#ifdef DEBUG
    all_course_list.insert("A1", new Course("A1","数学2",6,"2021-spring","J8-401"));
    course_map.insert("数学2","A1");
    all_course_list.insert("数学", new Course("数学","数学",6,"2021-spring","J8-401"));
    course_map.insert("数学","数学");
    all_course_list.insert("物理", new Course("物理","物理",6,"2021-spring","J8-401"));
    course_map.insert("物理","物理");
#endif
}

void MainWindow::saveFile()
{
    QFile student_file(QDir::currentPath() + "\\studentListtest.txt");
    student_file.open(QIODevice::WriteOnly);
    QTextStream tstream(&student_file);
    tstream.setCodec("utf-8");

    int s_size = all_student_list.size();
    tstream << s_size << "\n";
    for(int i = 0; i < s_size; ++i){
        QString student_id = all_student_list.keys()[i];
        Student* student = all_student_list[student_id];
        tstream << student_id << " " << student->getName() << " " << student->getClass() << " " << student->getPhone() << " " \
                << student->getBirth().year() << " " << student->getBirth().month() << " " << student->getBirth().day() << " " << student->getAddress() << " ";
        int course_size = student->course_list.size();
        tstream << course_size << " ";
        for(QMap<QString, int>::Iterator iter = student->course_list.begin(); iter != student->course_list.end(); ++iter){
            tstream << iter.key() << " " <<iter.value() << " ";
        }
        tstream << "\n";
    }

    student_file.close();
}

void MainWindow::on_add_button_2_clicked()
{
    AddStudentDialog dlg(this);
    dlg.exec();
}

//删除所选行，当没有行被选中，应发出警报
void MainWindow::on_delete_button_2_clicked()
{
    int row = ui->student_info_table->currentRow();
    if(row < 0){
        QApplication::beep();
        return;
    }

    bool confirm = false;
    DelDialog dlg(&confirm);
    dlg.exec();

    if(confirm){
        delStudent(ui->student_info_table->item(row,0)->text());
        ui->student_info_table->removeRow(row);
    }
}

/////////////////////////////////////////////////////////////////////////////////



void MainWindow::closeEvent(QCloseEvent *event)
{
    bool flag = true;
    DelDialog dlg(&flag,"您确定要退出吗？","是","否");
    dlg.exec();
    if(!flag) event->ignore();
    else  saveFile();
}

void MainWindow::on_update_button_2_clicked()
{
    //获得currentrow上第一列（学生id)以获得该学生指针，传入修改对话框中，修改对话框初始值为学生当前信息，按ok则修改该学生内存中的信息并刷新界面上的信息，按取消放弃更改
    int row = ui->student_info_table->currentRow();
    if(row < 0){
        QApplication::beep();
        return;
    }

    Student* student = all_student_list[ui->student_info_table->item(row,0)->text()];
    UpdateStudentDialog dlg(student,this);
    dlg.exec();

    ui->student_info_table->setItem(row,0,new QTableWidgetItem(student->getId()));
    ui->student_info_table->setItem(row,1,new QTableWidgetItem(student->getName()));
    ui->student_info_table->setItem(row,2,new QTableWidgetItem(student->getClass()));
    ui->student_info_table->setItem(row,3,new QTableWidgetItem(student->getPhone()));
    ui->student_info_table->setItem(row,4,new QTableWidgetItem(QString("%1-%2-%3").arg(student->getBirth().year()).arg(student->getBirth().month()).arg(student->getBirth().day())));
    ui->student_info_table->setItem(row,5,new QTableWidgetItem(student->getAddress()));

    for(int i = 0; i<6; ++i){
        QTableWidgetItem* item = ui->student_info_table->item(row,i);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        item->setFlags((Qt::ItemFlags) TABLE_FLAG);
    }

}
