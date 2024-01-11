/**
*****************************************************************************
*  Copyright (C) 2023 湖南大学机器人学院 All rights reserved
*  @file    main.cpp
*  @brief   主函数
*  @author  刘鹏
*  @date    2023.12.25
*  @version V0.1
*----------------------------------------------------------------------------
*  @note 历史版本  修改人员    修改日期    修改内容
*  @note
*****************************************************************************
*/

#include "flowchar_widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //有个bug,连接线移动中间的节点，不停的闪或者超过边界了
    //内存泄漏
    //视图放大时拖动图元有重影
    FlowCharWidget flowchar_widget;
    flowchar_widget.show();
    return a.exec();
}
