#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include    <QSplitter>

#include <fstream>
#include <iostream>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <vector>
#include <execution>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <string>
#include <filesystem>
#include <QColorDialog>
#include <atomic>


std::vector<std::pair<std::string,int>> tfinal;

std::weak_ptr<std::atomic_int> com_r;
std::condition_variable com_cvp;
std::atomic<bool> com_tr, com_onemore;
std::mutex com_mx;
std::thread h, dest;

void brough(std::filesystem::path tf);
void dispatch(MainWindow *t);

void MainWindow::iniGraph3D()
{

    graph3D = new Q3DBars();
    graphContainer = QWidget::createWindowContainer(graph3D); //Q3DBars继承自QWindow
    graph3D->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFrontHigh); //设置视角

//创建坐标轴
    QStringList rowLabs;  //
    QStringList colLabs;

    rowLabs << "row1" << "row2"<<"row3";
    colLabs << "col1" << "col2" << "col3" << "col4"<<"col5";

    QValue3DAxis *axisV=new QValue3DAxis; //数值坐标
    axisV->setTitle("value");
    axisV->setTitleVisible(true);

    QCategory3DAxis *axisRow=new QCategory3DAxis;
    axisRow->setTitle("row axis");
    axisRow->setLabels(rowLabs);
//    m_yearAxis->setLabelAutoRotation(30.0f);
    axisRow->setTitleVisible(true);

    QCategory3DAxis *axisCol=new QCategory3DAxis;
    axisCol->setTitle("column axis");
    axisCol->setLabels(colLabs);
//    m_monthAxis->setLabelAutoRotation(30.0f);
    axisCol->setTitleVisible(true);

    graph3D->setValueAxis(axisV);
    graph3D->setRowAxis(axisRow);
    graph3D->setColumnAxis(axisCol);

//创建序列
    series = new bars();
    series->setMesh(QAbstract3DSeries::MeshCylinder); //MeshBar,MeshPyramid,MeshCylinder
    series->setItemLabelFormat("@seriesName : %d"); //项的标签显示格式
    graph3D->addSeries(series);
    series->setName("dh");
    dataSet = new QBarDataArray; //数据代理
    dataSet->reserve(rowLabs.count());

    series->dataProxy()->resetArray(dataSet);

    QFont font = graph3D->activeTheme()->font();
    font.setPointSize(32);
    graph3D->activeTheme()->setFont(font);
}



bars::bars(QObject *xwind ):
    QBar3DSeries(xwind)
{    
    connect(this, &QBar3DSeries::selectedBarChanged,
            this, &bars::breach);
};


bars::~bars()
{

};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    iniGraph3D(); //创建图表

    QSplitter   *splitter=new QSplitter(Qt::Horizontal);
    splitter->addWidget(ui->groupBox); //左侧控制面板
    splitter->addWidget(graphContainer);  //右侧图表
    this->setCentralWidget(splitter); //设置主窗口中心组建
    instore = 0;
    dealtwith = 0;
    connect(qApp, &QApplication::aboutToQuit, []{ if(com_tr) h.join(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onemore()
{
    instore = int(com_r.lock() ? *com_r.lock() : instore);
    instore = com_tr ? 25 /* max */ : instore;
    ui->progBarH->setValue(instore);
    std::unique_lock<std::mutex> lt(com_mx);
    if(dealtwith != tfinal.size())
    {
        std::sort(tfinal.begin(), tfinal.end(), [](auto e, auto k){ return e.first < k.first; });
        std::vector<std::pair<std::string,int>> tcopy(tfinal);
        lt.unlock();
        dataSet->clear();

        int a = 0;
        dataRow = new QBarDataRow;
        for(;a < std::min(5 , (int)tcopy.size()); a++) *dataRow << tcopy[a].second;
        dataSet->append(dataRow);

        dataRow2 = new QBarDataRow;
        for(;a < std::min(10, (int)tcopy.size()); a++) *dataRow2 << tcopy[a].second;
        dataSet->append(dataRow2);

        dataRow3 = new QBarDataRow;
        for(;a < std::min(15, (int)tcopy.size()); a++) *dataRow3 << tcopy[a].second;
        dataSet->append(dataRow3);

        series->dataProxy()->resetArray(dataSet);
        dealtwith = tcopy.size();
    }
}

void MainWindow::on_chkBoxGrid_clicked(bool checked)
{ //图表的网格
    graph3D->activeTheme()->setGridEnabled(checked);
}

void MainWindow::on_chkBoxSmooth_clicked(bool checked)
{ //柱状图的光滑性
    series->setMeshSmooth(checked);
//    graph3D->seriesList().at(0)->setMeshSmooth(checked);
}

void MainWindow::on_chkBoxReflection_clicked(bool checked)
{//反射
    graph3D->setReflection(checked);
}

void MainWindow::on_chkBoxAxisTitle_clicked(bool checked)
{//轴标题
    graph3D->valueAxis()->setTitleVisible(checked);
    graph3D->rowAxis()->setTitleVisible(checked);
    graph3D->columnAxis()->setTitleVisible(checked);
}

void MainWindow::on_chkBoxAxisBackground_clicked(bool checked)
{//轴标签背景
    graph3D->activeTheme()->setLabelBackgroundEnabled(checked);
}

void MainWindow::on_chkBoxReverse_clicked(bool checked)
{//Z轴反向
    graph3D->valueAxis()->setReversed(checked);
}

void MainWindow::on_chkBoxBackground_clicked(bool checked)
{//图表的背景
    graph3D->activeTheme()->setBackgroundEnabled(checked);
}

void MainWindow::on_spinFontSize_valueChanged(int arg1)
{//轴标签字体大小
    QFont font = graph3D->activeTheme()->font();
    font.setPointSize(arg1);
    graph3D->activeTheme()->setFont(font);
}

void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{//设置主题
    Q3DTheme *currentTheme = graph3D->activeTheme();
    currentTheme->setType(Q3DTheme::Theme(index));
}

void MainWindow::on_btnBarColor_clicked()
{ //设置序列柱状图的颜色
//    QBar3DSeries *series =graph3D->seriesList().at(0);
    QColor  color=series->baseColor();
    color=QColorDialog::getColor(color);
    if (color.isValid())
        series->setBaseColor(color);
}



void MainWindow::on_btnYeah_clicked()
{
    QString f = QFileDialog::getOpenFileName();
    std::filesystem::path w = f.toStdWString();
    h = std::thread(&brough, w);  
    dest = std::thread(&dispatch, this);
    ((QPushButton*)sender())->setEnabled(false);

}


void MainWindow::on_chkBoxItemLabel_clicked(bool checked)
{ //项的标签
 //   series->setItemLabelFormat("value at (@rowLabel,@colLabel): %.1f");
 //   series->setItemLabelVisible(checked);
}

void MainWindow::on_cBoxBarStyle_currentIndexChanged(int index)
{ //棒图的样式
//    QBar3DSeries *series =graph3D->seriesList().at(0);
    QAbstract3DSeries::Mesh aMesh;
    aMesh=QAbstract3DSeries::Mesh(index+1);
    series->setMesh(aMesh);
}

void MainWindow::on_cBoxSelectionMode_currentIndexChanged(int index)
{//选择模式
    graph3D->setSelectionMode(QAbstract3DGraph::SelectionFlags(index));
}

void MainWindow::on_comboCamera_currentIndexChanged(int index)
{ //变换视角
   Q3DCamera::CameraPreset  cameraPos=Q3DCamera::CameraPreset(index);
   graph3D->scene()->activeCamera()->setCameraPreset(cameraPos);
}

void MainWindow::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot =ui->sliderH->value();//水平
    int yRot=ui->sliderV->value(); //垂直
    int zoom=ui->sliderZoom->value(); //缩放
    graph3D->scene()->activeCamera()->setCameraPosition(xRot, yRot,zoom);
}

void MainWindow::on_sliderV_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}

void MainWindow::on_sliderZoom_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}


void bars::breach(const QPoint& te) 
{
    std::unique_lock<std::mutex> lt(com_mx);
    if( te != QBar3DSeries::invalidSelectionPosition() ) setName(tfinal[te.x()*5 + te.y()].first.c_str());
}


void brough(std::filesystem::path tf)
{
    std::ifstream b(tf);
    if(b.good() == false)
    {
        com_tr = !false;
        com_cvp.notify_one();
        dest.join();
        return;
    }
    std::shared_ptr<std::atomic_int> sp_tray = std::shared_ptr<std::atomic_int>(new std::atomic_int(0));
    std::vector<std::string> c;

    com_r = sp_tray;
    do{
        b >> *c.insert(c.end(),"");
    }while (!b.eof());

    auto t1 = std::chrono::system_clock::now();
    std::vector<std::string> t;

    int counter = 0;
    
    for(int ft = 0 ; ft < 15; ft++)
    {
        std::string torque;
        int rd = 0;
        std::mutex mtb;
        std::for_each(std::execution::par, c.begin(), c.end(), [&](auto a){ int wr = std::count(t.begin(), t.end(), a) == 0 ? std::count( c.begin(), c.end(), a) : 0;
        *sp_tray = 25.0*counter++/(15*c.size()); std::unique_lock<std::mutex> lb(mtb);  torque = wr > rd ? a : torque; rd = std::max(rd , wr); });
        t.insert(t.end(), torque);
        std::unique_lock<std::mutex> lt(com_mx);
        tfinal.insert(tfinal.end(), { torque , rd } );
        com_onemore = !false;
        com_cvp.notify_one();
    }
    std::cout << std::endl; 
    for(auto k : t)
        std::cout  << k << std::endl;

    auto t2 = std::chrono::system_clock::now();
    std::chrono::milliseconds f =  std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout  << f.count() << std::endl;
    
    com_tr = !false;
    com_cvp.notify_one();
    dest.join();

}

void dispatch(MainWindow *t)
{   
    std::mutex m_r;
    do {
        com_onemore = false;
        std::unique_lock<std::mutex> lk(m_r);
        com_cvp.wait_for(lk ,std::chrono::milliseconds(900) ,[] { return com_tr == !false||com_onemore == !false; }); 
        QMetaObject::invokeMethod(t, "onemore", Qt::QueuedConnection);
    }while(!com_tr);
}