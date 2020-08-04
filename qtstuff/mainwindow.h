#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include    <QtDataVisualization>

using namespace QtDataVisualization;


namespace Ui {
class MainWindow;
}

class bars : public QBar3DSeries
{
    Q_OBJECT
public:
    explicit bars(QObject *parent = Q_NULLPTR);
    ~bars();
private:
    void breach(const QPoint& te);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *graphContainer;//图表的容器
    Q3DBars *graph3D;   //图表
    bars *series;   //序列
    int instore;
    int dealtwith;
    QBarDataArray *dataSet;
    QBarDataRow *dataRow, *dataRow2, *dataRow3;
    void    iniGraph3D();   //创建图表

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_chkBoxGrid_clicked(bool checked);

    void on_chkBoxSmooth_clicked(bool checked);

    void on_chkBoxReflection_clicked(bool checked);

    void on_chkBoxAxisTitle_clicked(bool checked);

    void on_chkBoxAxisBackground_clicked(bool checked);

    void on_chkBoxReverse_clicked(bool checked);

    void on_chkBoxBackground_clicked(bool checked);

    void on_spinFontSize_valueChanged(int arg1);

    void on_cBoxTheme_currentIndexChanged(int index);

    void on_btnBarColor_clicked();

    void on_btnYeah_clicked();   

    void on_chkBoxItemLabel_clicked(bool checked);

    void on_cBoxBarStyle_currentIndexChanged(int index);

    void on_cBoxSelectionMode_currentIndexChanged(int index);

    void on_comboCamera_currentIndexChanged(int index);

    void on_sliderH_valueChanged(int value);

    void on_sliderV_valueChanged(int value);

    void on_sliderZoom_valueChanged(int value);

    void onemore();
   
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
