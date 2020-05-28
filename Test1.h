#ifndef TEST1_H
#define TEST1_H

//TODO: Was going to turn all of the Blocks into their own class instead of just tracking the
//      properties via a struct... I'll do that later...
#include <QWidget>
struct Test1Properties
{
    bool check1{false};
    bool check2{false};
    bool radio1{true};
    bool radio2{false};
};
Q_DECLARE_METATYPE(Test1Properties)
QDataStream &operator<<(QDataStream &out, const Test1Properties &p);
QDataStream &operator>>(QDataStream &in, Test1Properties &p);

class Test1
{
public:
    Test1();
};

#endif // TEST1_H
