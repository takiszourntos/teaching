#include <QCoreApplication>
#include <QStringList>
#include <QDebug>

int main(int argc, char *argv[])
//int main()
{
    QCoreApplication a(argc, argv);
    QString winter = "December, January, February";
    QString spring = "March, April, May";

    QStringList list;
    list << winter;
    list += spring;

    qDebug() << "The Spring months are: " << list[1];

    QString allmonths = list.join(", ");
    qDebug() << allmonths;

    return a.exec();
    //return 0;
}
