# 上手指南
## 开发前的配制要求
> 1. 计算机操作系统Windows 10及以上64bit，当前开发环境为Windows 10 64bit。
> 2. 计算机内存8G及以上。
## 安装步骤
> 1. 安装python（3.7.5-3.9）64位，当前开发环境python3.8.8 64位。
> 2. 通过python升级pip，安装mindspore ，具体安装指令见mindspore官网（https://www.mindspore.cn/install/）。
> 3. 安装好mindspore后，确认用于训练的数据文件MNIST_Data的路径，尝试运行mindspore_python.py，检验是否安装成功。
> 4. 安装Qt 5.12及以上版本，勾选MinG 64位编译器及所有的功能模块，当前开发环境Qt 5.12.12 MinG 64位。
> 5. 为Qt配制外部Python工具，确认能通过配制的Python运行mindspore_python.py。
> 6. 修改Qt项目.pro文件中libs、includepath、dependpath的路径，确认项目运行成功。
## 版本控制
> 当前版本 v0.1
