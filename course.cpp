#include "course.h"
#include "student.h"

Course::Course(const QString& id, const QString& name, int credit, const QString& term, const QString& classroom)
{
    setId(id);
    setName(name);
    setCredit(credit);
    setTerm(term);
    setClassroom(classroom);
}

Course::~Course()
{
    delete this->course_button;
}

void Course::setId(const QString &id)
{
    this->id = id;
}

void Course::setName(const QString &name)
{
    this->name = name;
}

void Course::setCredit(int credit)
{
    this->credit = credit;
}

void Course::setTerm(const QString &term)
{
    this->term = term;
}

void Course::setClassroom(const QString &classroom)
{
    this->classroom = classroom;
}

void Course::addStudent(Student *student)
{
    if(student_list.contains(student)) student_list.removeOne(student); //判断是否已在列表，考虑是否多余
    int size = this->student_list.size();
    if(size == 0) {
        student_list.append(student);
        return;
    }
    //grade应当已事先录入
    int grade = (*student)[this->id];
    for(int i = 0; i < size; ++i){
        if(grade >= (*student_list[i])[this->id]){
            student_list.insert(i,student);
            return;
        }
    }
    //若排在最后，应当直接append
    student_list.append(student);

}

//课程和学生中的选课信息都会被删除
bool Course::delStudent(Student *student)
{
    if(!student_list.removeOne(student)) return false; //已经实现在student_list删除学生并判断是否成功删除
    student->course_list.remove(this->id);//student的course_list会发生动态变化，不要用foreach
    return true;
}

void Course::updateStudent(Student *student)
{
    addStudent(student);
}

const QString &Course::getId() const
{
    return id;
}

const QString &Course::getName() const
{
    return name;
}

int Course::getCredit() const
{
    return credit;
}

const QString &Course::getTerm() const
{
    return term;
}

const QString &Course::getClassroom() const
{
    return classroom;
}

CourseButton::CourseButton(Course* course, QWidget *parent) : QPushButton(parent){
    this->course = course;
    this->setText("详情");
}

