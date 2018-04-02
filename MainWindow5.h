#ifndef MAINWINDOW5_H
#define MAINWINDOW5_H

#include <QMainWindow>

#include <QMainWindow>
#include <QVector>
#include <QDebug>
#include "qcustomplot.h"
#include <vector>
#include <ctime>
#include "data.h"
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <QDebug>
#include <set>
#include "Point.h"
namespace Ui
{
    class MainWindow5;
}

class MainWindow5 : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow5(vector<Data> *Datavec_,double maxx,double maxy,double minx, double miny,QWidget *parent = 0);
        ~MainWindow5();

private slots:
    void on_pushButton_2_clicked();
    void my_mouseMove(QMouseEvent* event);
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
        Ui::MainWindow5 *ui;
        void paintNum();
        vector<Data> *Datavec;
        double lenx,leny;
        int xnum = 2000, ynum = 2000;//没用 这里不是固定的 40cm一个格子
        int xsize = xnum + 1, ysize = ynum + 1;
        double stepx,stepy;
        double Minx,Miny,Maxx,Maxy;
        const int inf = 0xffffffff;
        double maxh = -0xffffffff , minh = 0xffffffff;
        QCustomPlot *pCustomPlot = nullptr;
        const int maxnum = 10;
        void LineFitLeastSquares(vector<Data> *vec,vector<double> &vResult) ;
};

#endif // MAINWINDOW5_H
