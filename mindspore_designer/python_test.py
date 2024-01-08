# This Python file uses the following encoding: utf-8


import matplotlib.pyplot as plt
import cv2

def py_fun(a,b):
    print("py_fun运行成功！")

def py_fun2():
    plt.plot([1,2,1,2])
    plt.show()

def py_fun1(img_path):
    img = cv2.imread(img_path)
    cv2.imshow("img-show", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == '__main__':
    py_fun('C:/Users/lxm/Pictures/test.jpg')


