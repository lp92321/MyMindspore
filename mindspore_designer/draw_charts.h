/**
*****************************************************************************
*  Copyright (C), 2023-2032, GOSUN CL
*  @file    draw_charts.h
*  @brief   绘制折线图、柱状图的类
*  @author  刘鹏
*  @date    2023.12.25
*  @version V0.1
*----------------------------------------------------------------------------
*  @note 历史版本  修改人员    修改日期    修改内容
*  @note
*****************************************************************************
*/

#ifndef DRAW_CHARTS_H
#define DRAW_CHARTS_H

#include <QtCharts>
//#include <QtCharts/QLineSeries>

class LineCharts : public QChart
{
    Q_OBJECT
public:
    explicit LineCharts(QChart *parent = nullptr,QLineSeries *lineSeries=nullptr);

signals:

};

#endif // DRAW_CHARTS_H
