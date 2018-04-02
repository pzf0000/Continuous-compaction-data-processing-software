#include "MainWindow2.h"
#include "ui_MainWindow2.h"

MainWindow2::MainWindow2(vector<Data> *Datavec_,QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow2)
{
	ui->setupUi(this);
	this->Datavec = Datavec_;
	paintXY();
	setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
	setFixedSize(this->width(), this->height());
	this->resize(800,600);
	this->show();
}

MainWindow2::~MainWindow2()
{
	delete ui;
}

void MainWindow2::paintXY()
{
	QCustomPlot *pCustomPlot = new QCustomPlot(this);
	//pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
	dateTicker->setDateTimeFormat("yy-MM-d HH:mm:ss");
	dateTicker->setTickCount(20);
	//pCustomPlot->xAxis->setTicker(dateTicker);
	pCustomPlot->xAxis->setTickLabelRotation(60);
    pCustomPlot->setGeometry(QRect(0,0,800,600));


	// 可变数组存放绘图的坐标的数据，分别存放x和y坐标的数据，101为数据长度


	// 添加数据，这里演示y = x^3，为了正负对称，x从-10到+10
	double tmpy = 0;
	int num = 0;
	double xz = 0;
	double Max = -0x3f3f3f3f,Min = 0x3f3f3f3f;
	double Max2 = -0x3f3f3f3f,Min2 = 0x3f3f3f3f;

	for(Data &data:*Datavec)
	{
		Max = max(Max,data.Ry);
		Max = max(Max,data.Ly);
		Min = min(Min,data.Ry);
		Min = min(Min,data.Ly);
		Max2 = max(Max2,data.Rx);
		Max2 = max(Max2,data.Lx);
		Min2 = min(Min2,data.Rx);
		Min2 = min(Min2,data.Lx);
	}

	int lastminute = (*Datavec)[0].GetMinute();
	for(Data &data:*Datavec)
	{
		QVector<double>  x,y;
		if(true)//(data.GetMinute() != lastminute)
		{
			x.push_back(data.Lx);
			x.push_back(data.Rx);
			y.push_back(data.Ly);
			y.push_back(data.Ry);
		}
		QCPGraph *pGraph = pCustomPlot->addGraph();
		pGraph->setData(x,y);
		pGraph->setPen(QPen(QColor(139,101,8,100),5));
	}

	// 向绘图区域QCustomPlot添加一条曲线



	pCustomPlot->xAxis->setVisible(false);
	pCustomPlot->yAxis->setVisible(false);
	// 设置背景色
	pCustomPlot->setBackground(QColor(255, 222, 173));
//32,178,170
	pCustomPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossSquare, 1));




	// 设置坐标轴显示范围，否则只能看到默认范围
	pCustomPlot->xAxis->setRange(Min2, Max2);
	pCustomPlot->yAxis->setRange(Min, Max);


}
