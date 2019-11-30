#ifndef CHARTHANDLING_H
#define CHARTHANDLING_H

#include <QtCharts>

using namespace QtCharts;

#define COLOR_BLUE QColor(30, 144, 255, 255)
#define COLOR_RED QColor(220, 20, 60, 255)
#define COLOR_GREEN QColor(0, 128, 0, 255)
#define COLOR_YELLOW QColor(240, 230, 140, 255)
#define COLOR_ORANGE QColor(218, 165, 32, 255)

class ChartHandling
{
public:
    explicit ChartHandling(QWidget* pParent);

    static ChartHandling* getInstance();
    static void releaseInstance();

    void generateChartData(QList<int>& sortArray, std::map<int, QColor>& mapColorHighLight);
    void showChartView(int x, int y, int width, int height);

protected:
    ChartHandling();
    virtual ~ChartHandling();

private:
    QChartView* m_pChartView;
    QChart* m_pChart;
    static ChartHandling* _instanceChartHandling;
};

#endif // CHARTHANDLING_H
