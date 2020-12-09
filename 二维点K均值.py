import numpy as np
import matplotlib.pyplot as plt
import math


def getpath():
    import tkinter as tk
    from tkinter import filedialog

    root = tk.Tk()
    root.withdraw()

    file_path = filedialog.askopenfilename()
    return file_path


def opentxt(path):#读取txt文件中的点
    f = open(path)
    p = f.read()
    a = p.split(",")
    k = []
    for c in a:
        k.append(c.split(" "))
    Point = [None] * len(k)
    for i in range(len(k)):
        Point[i] = [0] * 3
    for j in range(len(k)):
        Point[j][0] = int(k[j][0])
        Point[j][1] = int(k[j][1])
    print(Point)
    return Point


def PltShow(Point, MeansCenter):#可视化
    fmt = ["bo", "go", "co", "mo", "yo", "ko", "bv", "gv", "rv", "cv", "mv", "yv", "kv"]
    plt.figure()
    for i in range(len(Point)):
        plt.plot(Point[i][0], Point[i][1], fmt[Point[i][2]])
    for i in range(len(MeansCenter)):
        plt.plot(MeansCenter[i][0], MeansCenter[i][1], "ro")


def firstcenter(Point, c): #第一中心的计算
    MeansCenter = [None] * c
    for i in range(len(MeansCenter)):
        MeansCenter[i] = [0] * 7
    xx = []
    yy = []
    for i in range(len(Point)):
        xx.append(Point[i][0])
        yy.append(Point[i][1])
    Xmax = max(xx)
    Xmin = min(xx)
    Ymax = max(yy)
    Ymin = min(yy)
    Xcha = int((Xmax - Xmin) / c)
    Ycha = int((Ymax - Ymin) / c)
    xfir = Xcha + Xmin
    yfir = Ycha + Ymin
    for i in range(len(MeansCenter)):
        MeansCenter[i][0] = xfir
        MeansCenter[i][1] = yfir
        MeansCenter[i][2] = 0
        MeansCenter[i][3] = 0
        MeansCenter[i][4] = 0
        MeansCenter[i][5] = 0
        MeansCenter[i][6] = i
        xfir = xfir + Xcha
        yfir = yfir + Ycha
    print(MeansCenter)
    return MeansCenter


def KMeans(Point, MeansCenter, km):
    p = 3
    for k in range(0, km):
        for i in range(len(Point)):
            for c in range(len(MeansCenter)):
                #闵氏距离
                MeansCenter[c][2] = int((abs((Point[i][0] - MeansCenter[c][0]) ** p)
                                     + abs((Point[i][1] - MeansCenter[c][1]) ** p))**1/p)
                #欧式距离
                #MeansCenter[c][2] = ((Point[i][0] - MeansCenter[c][0]) ** 2
                                     #+ (Point[i][1] - MeansCenter[c][1]) ** 2)**0.5
                #曼哈顿距离
                #MeansCenter[c][2] = (abs(Point[i][0] - MeansCenter[c][0])
                                     #+ abs(Point[i][1] - MeansCenter[c][1]))

            def takeSecond(MeansCenter):
                return MeansCenter[2]

                # 排序

            MeansCenter.sort(key=takeSecond)
            Point[i][2] = MeansCenter[0][6]

            MeansCenter[0][3] = MeansCenter[0][3] + 1
            MeansCenter[0][4] = MeansCenter[0][4] + Point[i][0]
            MeansCenter[0][5] = MeansCenter[0][5] + Point[i][1]
        PltShow(Point, MeansCenter)
        for i in range(len(MeansCenter)):
            if MeansCenter[i][3] != 0:
                MeansCenter[i][0] = int(MeansCenter[i][4] / MeansCenter[i][3])
                MeansCenter[i][1] = int(MeansCenter[i][5] / MeansCenter[i][3])
        for i in range(len(MeansCenter)):
            for j in range(2, 6):
                MeansCenter[i][j] = 0
        print(MeansCenter)
    return Point


if __name__ == '__main__':
    path = getpath()
    Point = opentxt(path)
    plt.ion()
    classNum = int(input("类别数:"))
    DieNum = int(input("迭代次数"))
    MeansCenter = firstcenter(Point, classNum)
    Point1 = KMeans(Point, MeansCenter, DieNum)
    plt.ioff()
    plt.show()
