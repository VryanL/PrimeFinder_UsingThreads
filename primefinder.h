#ifndef PRIMEFINDER_H
#define PRIMEFINDER_H

#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QString>
#include <QDebug>

class PrimeFinder : public QObject, public QRunnable
{
    Q_OBJECT
public:
    PrimeFinder(QObject *parent = nullptr);
    ~PrimeFinder();

    void run();

    void setEditOutIndex(int index);
    void setStart(int s);
    void setEnd(int e);
    void requestStop();

signals:
    void sendMessage(int index, const QString &message);

private:
    int editOutIndex;
    int start;
    int end;
    bool stopRequesed;

    bool isPrime(int n);

};

#endif // PRIMEFINDER_H
