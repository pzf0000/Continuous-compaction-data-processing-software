#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "taskthread.h"
#include "MainWindow2.h"
#include "MainWindow3.h"
#include "MainWindow4.h"
#include "MainWindow5.h"
#include <fstream>
using namespace std;

namespace Ui
{
	class Dialog;
}

class Dialog : public QDialog
{
		Q_OBJECT

	public:
		explicit Dialog(QWidget *parent = 0);
		~Dialog();

	private slots:
		void on_open_clicked();

		void updateinfo(int n,int usetime);

		void updateinfo2(int n);

		void paintChart(vector<Data> *Datavec);

		void on_line_clicked();

		void on_height_clicked();

		void on_track_clicked();

		void on_num_2_clicked();

        void on_num_3_clicked();

        void on_num_4_clicked();

private:
        bool line = true, track = true , height = true , num = true ,cmv = true, save = true;
		vector<Data> *Datavec;
		void begin();
		void end();
		double maxx,maxy,minx,miny;
	public:
		Ui::Dialog *ui;
};
QString getfilename();
#endif // DIALOG_H
