#include "ChartHandling.h"

ChartHandling* ChartHandling::_instanceChartHandling = nullptr;

ChartHandling::ChartHandling(QWidget* pParent)
{    
    m_pChart = new QChart();
    m_pChart->setTheme(QChart::ChartThemeHighContrast);
    m_pChart->legend()->setVisible(false);

    m_pChartView = new QChartView(m_pChart, pParent);
    m_pChartView->setRenderHint(QPainter::Antialiasing);
    m_pChartView->hide();

    _instanceChartHandling = this;
}


ChartHandling::ChartHandling()
{
}

ChartHandling::~ChartHandling()
{
}

ChartHandling* ChartHandling::getInstance()
{
    if (_instanceChartHandling == nullptr)
        _instanceChartHandling = new ChartHandling();
    return _instanceChartHandling;
}

void ChartHandling::releaseInstance()
{
    if (_instanceChartHandling != nullptr)
    {
        delete _instanceChartHandling;
        _instanceChartHandling = nullptr;
    }
}

void ChartHandling::generateChartData(QList<int>& sortArray, std::map<int, QColor>& mapColorHighLight)
{
    int sizeArray = sortArray.size();

    if ( (sizeArray == 0) || (m_pChart == nullptr) )
        return;

    m_pChart->removeAllSeries();

    QBarSeries* barSeries = new QBarSeries();
    barSeries->setBarWidth(1);

    for (int i = 0; i < sizeArray; ++i)
    {
        QBarSet* barSet = new QBarSet("");
        barSet->setColor(mapColorHighLight[i]);
        *barSet << sortArray[i];

        barSeries->append(barSet);
    }

    m_pChart->addSeries(barSeries);
}

void ChartHandling::showChartView(int x, int y, int width, int height)
{
    if (m_pChartView)
    {
        m_pChartView->move(x, y);
        m_pChartView->resize(width, height);
        m_pChartView->show();
    }
}
