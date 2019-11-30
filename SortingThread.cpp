#include "SortingThread.h"
#include "ChartHandling.h"

SortingThread::SortingThread(QObject *parent) : QThread(parent)
{
    m_eSortType = TYPE_BUBBLE;
    m_ulAnimationSpeed = DEF_ANIMATION_SPEED;
    m_nSizeArray = 0;
}

SortingThread::~SortingThread()
{
}

void SortingThread::run()
{
    switch (m_eSortType)
    {
    case TYPE_BUBBLE:
        bubbleSort();
        break;
    case TYPE_SELECTION:
        selectionSort();
        break;
    }

    for (int i = 0; i < m_nSizeArray; ++i)
    {
        m_mapColorHighLight[i] = COLOR_GREEN;
    }
    emit sortingFinished(m_listSortArray, m_mapColorHighLight);
}

void SortingThread::setSortType(eSORT_TYPE eSortType)
{
    m_eSortType = eSortType;
}

void SortingThread::setAnimationSpeed(unsigned long msecAnimationSpeed)
{
    m_ulAnimationSpeed = msecAnimationSpeed;
}

void SortingThread::generateArrayData()
{
    m_nSizeArray = 50;
    m_listSortArray.clear();
    m_mapColorHighLight.clear();

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < m_nSizeArray; ++i)
    {
        int number = rand() % 100 + 1; // 1 ~ 100
        m_listSortArray.append(number);
        m_mapColorHighLight[i] = COLOR_BLUE;
    }

    emit arrayDataChanged(m_listSortArray, m_mapColorHighLight);
}

void SortingThread::resetColor()
{
    m_mapColorHighLight.clear();
    for (int i = 0; i < m_nSizeArray; ++i)
    {
        m_mapColorHighLight[i] = COLOR_BLUE;
    }

    emit arrayDataChanged(m_listSortArray, m_mapColorHighLight);
}

void SortingThread::swap(int *varA, int *varB)
{
    int temp = *varA;
    *varA = *varB;
    *varB = temp;
}

void SortingThread::updateChart()
{
    emit arrayDataChanged(m_listSortArray, m_mapColorHighLight);
    this->usleep(m_ulAnimationSpeed);
}

void SortingThread::bubbleSort()
{
    for (int nParentLoop = 0; nParentLoop < m_nSizeArray - 1; ++nParentLoop)
    {
        bool bSwapped = false;

        // Last elements are already in place after every loop
        for (int nChildLoop = 0; nChildLoop < m_nSizeArray - 1 - nParentLoop; ++nChildLoop)
        {
            m_mapColorHighLight[nChildLoop] = COLOR_YELLOW;
            m_mapColorHighLight[nChildLoop+1] = COLOR_YELLOW;
            updateChart();

            if (m_listSortArray[nChildLoop] > m_listSortArray[nChildLoop+1])
            {
                m_mapColorHighLight[nChildLoop] = COLOR_RED;
                m_mapColorHighLight[nChildLoop+1] = COLOR_RED;
                updateChart();

                swap(&m_listSortArray[nChildLoop], &m_listSortArray[nChildLoop+1]);
                bSwapped = true;

                updateChart();
            }

            m_mapColorHighLight[nChildLoop] = COLOR_BLUE;
            m_mapColorHighLight[nChildLoop+1] = COLOR_BLUE;
            updateChart();
        }

        // Make last elements highlight with color because they are already in place
        m_mapColorHighLight[m_nSizeArray - 1 - nParentLoop] = COLOR_ORANGE;
        updateChart();

        // There is no number swapped, the array is sorted completely, break the loop
        if(bSwapped == false)
           break;
    }
}

void SortingThread::selectionSort()
{
    for (int nParentLoop = 0; nParentLoop < m_nSizeArray - 1; ++nParentLoop)
    {
        // Set current element as minimum value
        int minIndex = nParentLoop;

        m_mapColorHighLight[minIndex] = COLOR_RED;
        updateChart();

        // Search the rest of array to find the minimum value
        for (int nChildLoop = nParentLoop + 1; nChildLoop < m_nSizeArray; ++nChildLoop)
        {
            // Create effect of traversing current index
            m_mapColorHighLight[nChildLoop] = COLOR_YELLOW;
            updateChart();

            m_mapColorHighLight[nChildLoop] = COLOR_BLUE;
            updateChart();

            if (m_listSortArray[minIndex] > m_listSortArray[nChildLoop])
            {
                minIndex = nChildLoop;
            }
        }

        // If a minimum value is found, swap it with the current element
        if (minIndex != nParentLoop)
        {
            m_mapColorHighLight[minIndex] = COLOR_RED;
            updateChart();

            swap(&m_listSortArray[minIndex], &m_listSortArray[nParentLoop]);

            updateChart();

            m_mapColorHighLight[minIndex] = COLOR_BLUE;
            m_mapColorHighLight[nParentLoop] = COLOR_ORANGE;
            updateChart();
        }
        else
        {
            m_mapColorHighLight[nParentLoop] = COLOR_ORANGE;
            updateChart();
        }
    }
}
