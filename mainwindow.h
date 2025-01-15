#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QThreadPool>
#include <QCloseEvent>
#include <QMessageBox>
#include <QList>
#include "primefinder.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent *e) override;

private slots:
    void startThreads();
    void appendText(int index, const QString &message);

private:
    QSpinBox *startNum;
    QSpinBox *endNum;
    QSpinBox *nThreads;
    QTextEdit *output1;
    QTextEdit *output2;
    QTextEdit *output3;
    QTextEdit *output4;

    QList<QTextEdit*> outputList;
    QList<PrimeFinder*> fList;
};

#endif // MAINWINDOW_H
