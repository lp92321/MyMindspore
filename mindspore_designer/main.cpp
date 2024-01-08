/**
*****************************************************************************
*  Copyright (C), 2023-2032, GOSUN CL
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

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
