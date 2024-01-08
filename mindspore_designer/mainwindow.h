/**
*****************************************************************************
*  Copyright (C), 2023-2032, GOSUN CL
*  @file    mainwindow.h
*  @brief   主窗口类、函数
*  @author  刘鹏
*  @date    2023.12.25
*  @version V0.1
*----------------------------------------------------------------------------
*  @note 历史版本  修改人员    修改日期    修改内容
*  @note
*****************************************************************************
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDateTime>

#include "draw_charts.h"
#undef slots
#include <Python.h>
#define slots Q_SLOTS
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void PrintTime(const QString tip = "");

    int DrawLinechart(QLineSeries* lineSeries, QChartView* View);
    int RunPythonAPI();
    int InitWidget();
private slots:
    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
