#include "Test1.h"

QDataStream &operator<<(QDataStream &out, const Test1Properties &p)
{
    out << p.check1 << p.check2 << p.radio1 << p.radio2;
    return out;
}

QDataStream &operator>>(QDataStream &in, Test1Properties &p)
{
    in >> p.check1;
    in >> p.check2;
    in >> p.radio1;
    in >> p.radio2;
    return in;
}

Test1::Test1()
{

}
