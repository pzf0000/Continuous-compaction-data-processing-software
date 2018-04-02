#ifndef PROCESS_H
#define PROCESS_H
#include <QThread>
#include "MainWindow.h"

class process : public QThread
{
		Q_OBJECT
	public:
		explicit process(vector<Data> *Datavec,QObject *parent = 0)
			: QThread(parent)
		{
			moveToThread(this);
			this->Datavec = Datavec;
		}

	signals:


	private:
		vector<Data> *Datavec;
	public:
		virtual void run() Q_DECL_OVERRIDE;

};
#endif // PROCESS_H
