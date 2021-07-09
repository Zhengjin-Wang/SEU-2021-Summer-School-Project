#ifndef COURSE_H
#define COURSE_H

#include<QList>

class Student;
class CourseButton;

class Course
{
public:
    Course(const QString& id, const QString& name, int credit, const QString& term, const QString& classroom);
    ~Course();
    QList<Student*> student_list;
    Course& operator=(const Course& src);

    Student* operator[](int n);

    void setId(const QString& id);
    void setName(const QString& name);
    void setCredit(int credit);
    void setTerm(const QString& term);
    void setClassroom(const QString& classroom);

    void addStudent(Student* student); //课程的student_lsit和学生的course_list都要添加
    bool delStudent(Student* student); //删除应删除student_list的该学生，并删除该学生course_list的该course
    void updateStudent(Student* student);

    const QString& getId() const;
    const QString& getName() const;
    int getCredit() const;
    const QString& getTerm() const;
    const QString& getClassroom() const;

    int row;
    CourseButton* course_button;

private:
    QString id;
    QString name;
    int credit;
    QString term;
    QString classroom;
};
#include <QPushButton>

class CourseButton : public QPushButton
{

public:
    Course* course;
    explicit CourseButton(Course* course, QWidget *parent = nullptr);

signals:

};

#endif // COURSE_H
