#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SortingThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void releaseInstanceSortArray();

public slots:
    void onSortingFinished(QList<int> sortArray, std::map<int, QColor> mapColorHighLight);
    void onArrayDataChanged(QList<int> sortArray, std::map<int, QColor> mapColorHighLight);

private slots:
    void on_btnGenerateArray_clicked();
    void on_btnSortRun_clicked();

    void on_cmbSortType_currentIndexChanged(int index);

    void on_sldAnimationSpeed_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    SortingThread* m_pSortingThread;
    bool _bSortThreadStarted;
};
#endif // MAINWINDOW_H
