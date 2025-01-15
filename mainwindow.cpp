#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Prime Finder");
    resize(700,600);

    QWidget *main = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *inputLayout = new QHBoxLayout();
    QHBoxLayout *threadLayout = new QHBoxLayout();
    QHBoxLayout *threadLayoutLabel = new QHBoxLayout();

    startNum = new QSpinBox();
    startNum->setMinimum(0);
    startNum->setMaximum(1000000000);
    endNum = new QSpinBox();
    endNum->setMinimum(0);
    endNum->setMaximum(1000000000);
    nThreads = new QSpinBox();
    nThreads->setMinimum(1);
    nThreads->setMaximum(4);

    inputLayout->addWidget(new QLabel("Start Num"));
    inputLayout->addWidget(startNum);
    inputLayout->addWidget(new QLabel("End Number"));
    inputLayout->addWidget(endNum);
    inputLayout->addWidget(new QLabel("Number of Threads"));
    inputLayout->addWidget(nThreads);
    mainLayout->addLayout(inputLayout);

    QPushButton *startButton = new QPushButton("&Start");
    mainLayout->addWidget(startButton,0,Qt::AlignLeft);

    output1 = new QTextEdit();
    output1->setReadOnly(true);
    output2 = new QTextEdit();
    output2->setReadOnly(true);
    output3 = new QTextEdit();
    output3->setReadOnly(true);
    output4 = new QTextEdit();
    output4->setReadOnly(true);

    threadLayoutLabel->addWidget(new QLabel("Thread 1"),0,Qt::AlignCenter);
    threadLayoutLabel->addWidget(new QLabel("Thread 2"),0,Qt::AlignCenter);
    threadLayoutLabel->addWidget(new QLabel("Thread 3"),0,Qt::AlignCenter);
    threadLayoutLabel->addWidget(new QLabel("Thread 4"),0,Qt::AlignCenter);
    mainLayout->addLayout(threadLayoutLabel);

    threadLayout->addWidget(output1);
    threadLayout->addWidget(output2);
    threadLayout->addWidget(output3);
    threadLayout->addWidget(output4);

    mainLayout->addLayout(threadLayout);
    main->setLayout(mainLayout);
    setCentralWidget(main);

    outputList.append(output1);
    outputList.append(output2);
    outputList.append(output3);
    outputList.append(output4);

    connect(startButton, SIGNAL(clicked(bool)), this, SLOT(startThreads()));
}

MainWindow::~MainWindow() {}

void MainWindow::closeEvent(QCloseEvent *e)
{
    QMessageBox::information(this, "Closing", "Waiting for threads finish");
    for (PrimeFinder *p : fList)
        p->requestStop();
    QThreadPool::globalInstance()->waitForDone();
    e->accept();
}

void MainWindow::startThreads()
{
    output1->clear();
    output2->clear();
    output3->clear();
    output4->clear();

    int numThreads = nThreads->value();
    int start = startNum->value();
    int end = endNum->value();
    int range = (end - start + 1)/numThreads;

    for (int i = 0; i < numThreads; i++)
    {
        int s = start + i * range;
        int e = s + range - 1;

        if (i == numThreads-1)
            e = end;

        PrimeFinder *pFinder = new PrimeFinder();
        fList.append(pFinder);
        pFinder->setAutoDelete(true);
        pFinder->setEditOutIndex(i);
        pFinder->setStart(s);
        pFinder->setEnd(e);

        connect(pFinder, SIGNAL(sendMessage(int,QString)), this, SLOT(appendText(int,QString)));

        QThreadPool::globalInstance()->start(pFinder);

    }
}

void MainWindow::appendText(int index, const QString &message)
{
    if (index >= 0 && index < outputList.size())
    {
        outputList[index]->append(message);
    }
}
