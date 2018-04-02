#ifndef TASKTHREAD_H
#define TASKTHREAD_H
#pragma once
#include <QThread>
#include "readcvsutils.h"
#include "process.h"
#include "MainWindow.h"

class taskthread : public QThread
{
		Q_OBJECT
	public:
		explicit taskthread(QString filename,vector<Data> *Datavec,double &maxx,double &minx,double &maxy,double &miny,QObject *parent = 0)
			: QThread(parent)
		{
			moveToThread(this);
			this->Datavec = Datavec;
			this->filename = filename.toStdString();
			a = &maxx,b = &minx,c = &maxy,d = &miny;
		}

	signals:
		void updateinfo(int n,int usetime);

		void updateinfo2(int n);

		void paintChart(vector<Data> *Datavec);


	private:
		vector<Data> *Datavec;
		string filename;
		double *a,*b,*c,*d;
	public:
		virtual void run() Q_DECL_OVERRIDE;
		void static callback(int n,int usetime,void *w)
		{
			((taskthread*)w)->updateinfo(n,usetime);
		}
};

#endif // TASKTHREAD_H
