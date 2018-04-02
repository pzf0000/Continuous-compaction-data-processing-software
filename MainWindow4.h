#ifndef MAINWINDOW4_H
#define MAINWINDOW4_H

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
#include "Point.h"

namespace Ui
{
	class MainWindow4;
}

class MainWindow4 : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow4(vector<Data> *Datavec_,double maxx,double maxy,double minx, double miny,QWidget *parent = 0);
		~MainWindow4();

private slots:
    void on_pushButton_2_clicked();

private:
		Ui::MainWindow4 *ui;
        QCustomPlot *pCustomPlot = nullptr;
		void paintNum();
		vector<Data> *Datavec;
		double lenx,leny;
		const int xnum = 2000, ynum = 2000;
		const int xsize = xnum + 1, ysize = ynum + 1;
		double stepx,stepy;
		double Minx,Miny,Maxx,Maxy;
		const int inf = 0xffffffff;
		double maxh = -0xffffffff , minh = 0xffffffff;
		const int maxnum = 10;
};


#endif // MAINWINDOW4_H
