/**
*****************************************************************************
*  Copyright (C), 2023-2032, GOSUN CL
*  @file    draw_charts.cpp
*  @brief   定义用于绘制折线图、柱状图的函数
*  @author  刘鹏
*  @date    2023.12.25
*  @version V0.1
*----------------------------------------------------------------------------
*  @note 历史版本  修改人员    修改日期    修改内容
*  @note
*****************************************************************************
*/

#include "draw_charts.h"

LineCharts::LineCharts(QChart *parent,QLineSeries *lineSeries) : QChart(parent)
{
    //设置标题
    this->setTitle("Line Chart");
    //将折线系列添加到图表中
    this->addSeries(lineSeries);

    // 创建 QValueAxis 对象作为 X 轴
    QValueAxis *axisX = new QValueAxis();
    // 设置标签格式
    axisX->setLabelFormat("%.0f");
    axisX->setTitleText("X Axis");
    axisX->setRange(0, 20); // 设置范围
    axisX->setTickCount(21); // 设置 tickCount，即标签数量为 21
    this->addAxis(axisX, Qt::AlignBottom); // 将 X 轴添加到图表中
    lineSeries->attachAxis(axisX); // 折线系列关联 X 轴

    // 创建 QValueAxis 对象作为 Y 轴
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Y Axis");
    axisY->setRange(0, 100); // 设置范围
    axisY->setTickCount(11); // 设置 tickCount，即标签数量为 11
    this->addAxis(axisY, Qt::AlignLeft); // 将 Y 轴添加到图表中
    lineSeries->attachAxis(axisY); // 折线系列关联 Y 轴

}
