#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QVector>
#include "qcustomplot.h"
#include <vector>
#include <ctime>
#include "data.h"
#include <fstream>
#include "MainWindow3.h"

namespace Ui
{
	class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow2(vector<Data> *Datavec_,QWidget *parent = 0);
		~MainWindow2();

	private:
		Ui::MainWindow2 *ui;
		vector<Data> *Datavec;
		void paintXY();
};

#endif // MAINWINDOW2_H
