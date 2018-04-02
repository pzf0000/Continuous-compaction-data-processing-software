#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "qcustomplot.h"
#include <vector>
#include <ctime>
#include "data.h"
#include <fstream>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(vector<Data> *Datavec_,QWidget *parent = 0);
		~MainWindow();

	private:
		Ui::MainWindow *ui;
		vector<Data> *Datavec;
		void work();
		void paintSpeed();
		void paintCMV();
		void paintXY();
		void dealFakeData();
};

#endif // MAINWINDOW_H
