#include "primefinder.h"

PrimeFinder::PrimeFinder(QObject *parent)
    : QObject(parent), stopRequesed(false)
{}

PrimeFinder::~PrimeFinder()
{}

void PrimeFinder::run()
{

    for (int i = start; i < end && !stopRequesed; i++)
    {
        if (isPrime(i))
            emit sendMessage(editOutIndex, QString::number(i));
    }
}

void PrimeFinder::setEditOutIndex(int index)
{
    editOutIndex = index;
}

void PrimeFinder::setStart(int s)
{
    start = s;
}

void PrimeFinder::setEnd(int e)
{
    end = e;
}

void PrimeFinder::requestStop()
{
    stopRequesed = true;
}

bool PrimeFinder::isPrime(int n)
{
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i <= std::sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}
