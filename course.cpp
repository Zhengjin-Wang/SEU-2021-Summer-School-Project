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

}

void Course::delStudent(Student *student)
{

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

void Course::sort()
{

}

void Course::sort(int n)
{

}

void Course::sort(Student *student)
{

}

void Course::sort(const QString &student)
{

}
