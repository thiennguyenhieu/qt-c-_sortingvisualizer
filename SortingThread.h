#ifndef SORTINGALGORITHM_H
#define SORTINGALGORITHM_H

#include <QThread>
#include <QColor>

#define DEF_ANIMATION_SPEED 400000 // usec

class SortingThread : public QThread
{
    Q_OBJECT
    Q_ENUMS(eSORT_TYPE)

public:
    enum eSORT_TYPE
    {
        TYPE_BUBBLE,
        TYPE_SELECTION
    };

    explicit SortingThread(QObject *parent = nullptr);
    ~SortingThread() override;

    void run() override;

    void setSortType(eSORT_TYPE eSortType);
    void setAnimationSpeed(unsigned long ulAnimationSpeed);
    void generateArrayData();
    void resetColor();

private:
    void swap(int* varA, int* varB);
    void updateChart();

    void bubbleSort();
    void selectionSort();

private:
   QList<int> m_listSortArray;
   std::map<int, QColor> m_mapColorHighLight;

   int m_nSizeArray;
   eSORT_TYPE m_eSortType;
   unsigned long m_ulAnimationSpeed;

signals:
   void sortingFinished(QList<int> sortArray, std::map<int, QColor> mapColorHighLight);
   void arrayDataChanged(QList<int> sortArray, std::map<int, QColor> mapColorHighLight);
};

#endif // SORTINGALGORITHM_H
