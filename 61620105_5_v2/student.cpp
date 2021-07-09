#include "student.h"
#include "course.h"

Student::Student()
{

}

Student::Student(const QString& id, const QString& name, const QString& _class, const QString& phone, const QDate& birth, const QString& address)
{
    setId(id);
    setName(name);
    setClass(_class);
    setPhone(phone);
    setBirth(birth);
    setAddress(address);
}

Student::~Student()
{
    delete student_button;
}

int &Student::operator[](const QString &course_id)
{
    return this->course_list[course_id];
}

void Student::setId(const QString& id)
{
    this->id = id;
}

void Student::setName(const QString& name)
{
    this->name = name;
}

void Student::setClass(const QString& _class)
{
    this->_class = _class;
}

void Student::setPhone(const QString& phone)
{
    this->phone = phone;
}

void Student::setBirth(const QDate& birth)
{
    this->birth = birth;
}

void Student::setAddress(const QString& address)
{
    this->address = address;
}

void Student::addCourse(const QString &course_id, int grade)
{
    this->course_list.insert(course_id, grade);
}

void Student::delCourse(const QString &course_id)
{
    this->course_list.remove(course_id);
}

const QString& Student::getId() const
{
    return id;
}

const QString& Student::getName() const
{
    return name;
}

const QString& Student::getClass() const
{
    return _class;
}

const QString& Student::getPhone() const
{
    return phone;
}

const QDate& Student::getBirth() const
{
    return birth;
}
const QString& Student::getAddress() const
{
    return address;
}

StudentButton::StudentButton(Student* student, QWidget *parent) : QPushButton(parent)
{
    this->student = student;
    this->setText("详情");
}

