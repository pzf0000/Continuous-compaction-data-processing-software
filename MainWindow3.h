#ifndef MAINWINDOW3_H
#define MAINWINDOW3_H

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
#include <iomanip>
#include <QFileDialog>
#include <fstream>
#include "MainWindow4.h"

namespace Ui
{
	class MainWindow3;
}

class MainWindow3 : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow3(vector<Data> *Datavec_,double maxx,double maxy,double minx, double miny,QWidget *parent = 0);
		~MainWindow3();

	private:
		Ui::MainWindow3 *ui;
        void setTexts();
		void setColorByHeight(double h,int x,int y);
		vector<Data> *Datavec;
		void s();
		void paintHeight();
		double lenx,leny;
		const int xnum = 200, ynum = 200;
		const int xsize = xnum + 1, ysize = ynum + 1;
		double stepx,stepy;
		double Minx,Miny,Maxx,Maxy;
		const int inf = 0xffffffff;
		double maxh = -0xffffffff , minh = 0xffffffff;
        QString getfilename();
        int seted = 0;
        string set1x = "N/A";
        string set2x = "N/A";
        string set3x = "N/A";
        string set4x = "N/A";
        string set1y = "N/A";
        string set2y = "N/A";
        string set3y = "N/A";
        string set4y = "N/A";
        int pnpoly(int npol, double *xp, double *yp, double x, double y);
        QCustomPlot *pCustomPlot = nullptr;
    private slots:
        void my_mouseMove(QMouseEvent* event);
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
};


#endif // MAINWINDOW3_H
