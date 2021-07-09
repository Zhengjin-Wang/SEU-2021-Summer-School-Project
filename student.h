#ifndef STUDENT_H
#define STUDENT_H

#include<QMap>
#include<QString>
#include<QDate>

class Course;
class StudentButton;

class Student
{
public:
    Student();
    Student(const QString& id, const QString& name, const QString& _class, const QString& phone, const QDate& birth, const QString& address);
    ~Student();
    Student& operator=(const Student& src);

    QMap<QString,int> course_list;//course数据的深拷贝
    StudentButton* student_button;
    int row;

    int& operator[](const QString& course_id);

    void setId(const QString& id);
    void setName(const QString& name);
    void setClass(const QString& _class);
    void setPhone(const QString& phone);
    void setBirth(const QDate& birth);
    void setAddress(const QString& address);
    void addCourse(const QString& course_id, int grade = 0);
    void delCourse(const QString& course_id);

    const QString& getId() const;
    const QString& getName() const;
    const QString& getClass() const;
    const QString& getPhone() const;
    const QDate& getBirth() const;
    const QString& getAddress() const;


private:
    QString id;
    QString name;
    QString _class;
    QString phone;
    QDate birth;
    QString address;

};

#include <QPushButton>

class StudentButton : public QPushButton
{
    Q_OBJECT
public:
    Student* student;
    explicit StudentButton(Student* student, QWidget *parent = nullptr);

signals:

};



#endif // STUDENT_H
