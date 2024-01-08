/**
*****************************************************************************
*  Copyright (C), 2023-2032, GOSUN CL
*  @file    mainwindow.cpp
*  @brief   定义主窗口类的方法
*  @author  刘鹏
*  @date    2023.12.25
*  @version V0.1
*----------------------------------------------------------------------------
*  @note 历史版本  修改人员    修改日期    修改内容
*  @note
*****************************************************************************
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cout<<"当前路径="<<QDir::currentPath();
    InitWidget();
    RunPythonAPI();

    // 创建 QLineSeries 对象
    QLineSeries *lineSeries = new QLineSeries();
    // 添加折线数据
    qsrand(QTime::currentTime().second());
    for(int i = 0; i <= 20; i++) {
        qreal x = i;
        qreal y = qrand()%100;
        lineSeries->append(x, y);
//        cout<<QPoint(x,y);
    }
    if(0 == DrawLinechart(lineSeries, ui->graphicsView))
    {
        cout<<" 折线图绘图成功";
    }




}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
*****************************************************************************
*  @brief       对窗口控件初始化
*  @param[in]
*  @return  void
*  @author  刘鹏
*----------------------------------------------------------------------------
*  @note 历史版本  修改人员    修改日期    修改内容
*  @note v0.1     刘鹏       2023-12-25   1.创建
*****************************************************************************
*/
int MainWindow::InitWidget()
{
    ui->menu_data->menuAction()->setVisible(false);
    ui->menu_designer->menuAction()->setVisible(true);
    ui->menu_train->menuAction()->setVisible(false);
    ui->toolBar_data->hide();
    ui->toolBar_designer->show();
    ui->toolBar_train->hide();

    ui->widget->show();
    ui->widget_2->show();
    ui->widget_3->show();
    return 0;
}

/**
*****************************************************************************
*  @brief       调用python的C API运行Python代码
*  @param[in]
*  @return  void
*  @author  刘鹏
*----------------------------------------------------------------------------
*  @note 历史版本  修改人员    修改日期    修改内容
*  @note v0.1     刘鹏       2023-12-25   1.创建
*****************************************************************************
*/
int MainWindow::RunPythonAPI()
{
    // 初始化
    Py_Initialize();
    //通过高层接口直接运行python代码，导入模块
    PyRun_SimpleString("import sys");
    //临时添加搜索路径
    PyRun_SimpleString("sys.path.append('../mindspore_designer')");
    PrintTime("ImportModule time1=");
    //加载mindspore_python.py模块
    PyObject* module =PyImport_ImportModule("mindspore_python");
    if(!module)
    {
        cout<<"Python file cant open!";
    }
    PrintTime("time2 ImportModule=");
    //获取mindspore_python.py模块中的py_fun函数
    PyObject* pFunc=PyObject_GetAttrString(module,"py_fun");
    if (!pFunc){
        cout<<"the Python function cant load!";
    }
    PrintTime("py_fun time3=");
    // C++数据转PyObject传入python
    PyObject* args_list =PyList_New(2);
    // 传入训练数据与测试数据路径
    args_list = Py_BuildValue("ss", "D:/MyGitLocalRepository/code_second/mindspore_designer/MNIST_Data/train",
                              "D:/MyGitLocalRepository/code_second/mindspore_designer/MNIST_Data/test");
    // 调用pFunc函数并传参
    PyObject* pRet = PyObject_CallObject(pFunc,args_list);
    // PyObject* pRet = PyObject_CallFunction(pFunc,NULL);
    int res = 0;
    //把返回值PyObject转换为C++类型
    PyArg_Parse(pRet, "i", &res);
    //释放返回值内存
    Py_DECREF(pRet);
    cout <<"py_fun返回值="<< res << endl;
    PrintTime("time4 py_fun=");
    //释放参数内存
    Py_DECREF(module);
    Py_CLEAR(pFunc);
    Py_CLEAR(args_list);
    Py_CLEAR(pRet);
    //结束，释放python
    Py_Finalize();
    PrintTime("time5 释放python=");
    return res;
}

/**
*****************************************************************************
*  @brief       打印当前时间，用于耗时确认
*  @param[in]     tip  对耗时事项的描述
*  @return  void
*  @author  刘鹏
*----------------------------------------------------------------------------
*  @note 历史版本  修改人员    修改日期    修改内容
*  @note v0.1     刘鹏       2023-12-25   1.创建
*****************************************************************************
*/
void MainWindow::PrintTime(QString tip)
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString(" yyyy.MM.dd hh:mm:ss.zzz ddd");
    qDebug()<<tip+current_date;
    return;
}

/**
*****************************************************************************
*  @brief   绘制折线图
*  @param[in]     lineSeries  折线数据
*  @param[in]    View      显示窗口
*  @return  int  成功返回0
*  @author  刘鹏
*----------------------------------------------------------------------------
*  @note 历史版本  修改人员    修改日期    修改内容
*  @note v0.1     刘鹏       2023-12-25   1.创建
*****************************************************************************
*/
int MainWindow::DrawLinechart(QLineSeries* lineSeries, QChartView* View)
{
    LineCharts* Mychart = new LineCharts(nullptr,lineSeries);
    // 需要将QGraphicsView页面提升为QChartView，再设置chart
    View->setChart(Mychart);  // histogramView--ui中已添加的QChartView
    View->setRenderHint(QPainter::Antialiasing); // 抗锯齿
    View->setVisible(true);
    return 0;
}

/**
*****************************************************************************
*  @brief       点击tabwidget页切换页面功能
*  @param[in]     index  页的序号
*  @return  void
*  @author  刘鹏
*----------------------------------------------------------------------------
*  @note 历史版本  修改人员    修改日期    修改内容
*  @note v0.1     刘鹏       2023-12-25   1.创建
*****************************************************************************
*/
void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(0 == index)
    {
        qDebug()<<"pag 设计器";
//        QMenu::menuAction()->setVisible(false)
        ui->menu_data->menuAction()->setVisible(false);
        ui->menu_designer->menuAction()->setVisible(true);
        ui->menu_train->menuAction()->setVisible(false);
        ui->toolBar_data->hide();
        ui->toolBar_designer->show();
        ui->toolBar_train->hide();

        ui->widget->show();
        ui->widget_2->show();
        ui->widget_3->show();
    }
    else if(1 == index)
    {
        qDebug()<<"page 数据";
        ui->menu_data->menuAction()->setVisible(true);
        ui->menu_designer->menuAction()->setVisible(false);
        ui->menu_train->menuAction()->setVisible(false);
        ui->toolBar_data->show();
        ui->toolBar_designer->hide();
        ui->toolBar_train->hide();

        ui->widget->hide();
        ui->widget_2->hide();
        ui->widget_3->hide();

    }
    else if(2 == index)
    {
        qDebug()<<"pag 训练";
        ui->menu_data->menuAction()->setVisible(false);
        ui->menu_designer->menuAction()->setVisible(false);
        ui->menu_train->menuAction()->setVisible(true);
        ui->toolBar_data->hide();
        ui->toolBar_designer->hide();
        ui->toolBar_train->show();

        ui->widget->hide();
        ui->widget_2->hide();
        ui->widget_3->hide();
    }


}

