#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "SortingThread.h"
#include "ChartHandling.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qRegisterMetaType<QList<int>>("QList<int>");
    qRegisterMetaType<std::map<int, QColor>>("std::map<int, QColor>");

    ui->setupUi(this);

    ChartHandling* ptrChartHandling = new ChartHandling(this);
    (void)ptrChartHandling;

    m_pSortingThread = new SortingThread(this);

    ui->cmbSortType->insertItem(0, "Bubble Sort", SortingThread::TYPE_BUBBLE);
    ui->cmbSortType->insertItem(1, "Selection Sort", SortingThread::TYPE_SELECTION);

    _bSortThreadStarted = false;

    connect(m_pSortingThread, SIGNAL(sortingFinished(QList<int>, std::map<int, QColor>)),
            this, SLOT(onSortingFinished(QList<int>, std::map<int, QColor>)));

    connect(m_pSortingThread, SIGNAL(arrayDataChanged(QList<int>, std::map<int, QColor>)),
            this, SLOT(onArrayDataChanged(QList<int>, std::map<int, QColor>)));

    m_pSortingThread->generateArrayData();

}

MainWindow::~MainWindow()
{
    ChartHandling::releaseInstance();

    if (m_pSortingThread)
        m_pSortingThread->quit();

    delete ui;
}

void MainWindow::onSortingFinished(QList<int> sortArray, std::map<int, QColor> mapColorHighLight)
{
    if (m_pSortingThread)
        m_pSortingThread->terminate();

    _bSortThreadStarted = false;
    ui->btnSortRun->setText("Run");
    ui->btnGenerateArray->setEnabled(true);

    ChartHandling::getInstance()->generateChartData(sortArray, mapColorHighLight);
    ChartHandling::getInstance()->showChartView(20, 80, 1600, 800);
}

void MainWindow::onArrayDataChanged(QList<int> sortArray, std::map<int, QColor> mapColorHighLight)
{
    ChartHandling::getInstance()->generateChartData(sortArray, mapColorHighLight);
    ChartHandling::getInstance()->showChartView(20, 80, 1600, 800);
}

void MainWindow::on_btnGenerateArray_clicked()
{
    if (m_pSortingThread)
        m_pSortingThread->generateArrayData();
}

void MainWindow::on_btnSortRun_clicked()
{
    if (!_bSortThreadStarted)
    {
        if (m_pSortingThread)
        {
            m_pSortingThread->resetColor();
            m_pSortingThread->start();
        }

        _bSortThreadStarted = true;
        ui->btnSortRun->setText("Stop");
        ui->btnGenerateArray->setEnabled(false);
    }
    else
    {
        if (m_pSortingThread)
        {
            m_pSortingThread->terminate();
            m_pSortingThread->wait();
        }

        _bSortThreadStarted = false;
        ui->btnSortRun->setText("Run");
        ui->btnGenerateArray->setEnabled(true);
    }
}

void MainWindow::on_cmbSortType_currentIndexChanged(int index)
{
    (void)index;

    if (m_pSortingThread)
        m_pSortingThread->setSortType(static_cast<SortingThread::eSORT_TYPE>(ui->cmbSortType->currentData().toInt()));
}

void MainWindow::on_sldAnimationSpeed_valueChanged(int value)
{
    unsigned long ulAnimationSpeed = static_cast<unsigned long>(DEF_ANIMATION_SPEED / value);

    if (m_pSortingThread)
        m_pSortingThread->setAnimationSpeed(ulAnimationSpeed);
}
