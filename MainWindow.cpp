#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(vector<Data> *Datavec_,QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->Datavec = Datavec_;
	work();
	this->resize(800,600);
	setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
	setFixedSize(this->width(), this->height());
}

void MainWindow::work()
{
	dealFakeData();
	paintSpeed();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::dealFakeData()
{
	//移动到读取部分进行了
	/*double speedsum = 0,rmvsum = 0,cmvsum = 0,hzsum = 0;
	for(Data &data:*Datavec)
	    speedsum += data.GetSpeed(),rmvsum += data.GetRMV(),cmvsum == data.GetCMV(),hzsum = data.GetHz();
	size_t Size = (*Datavec).size();
	speedsum /= Size,rmvsum /= Size,cmvsum /= Size,hzsum /= Size;
	double sdtmp = 0,rmvtmp = 0,cmvtmp = 0,hztmp = 0;
	for(Data &data:*Datavec)
	    sdtmp += (data.GetSpeed()-speedsum)*(data.GetSpeed()-speedsum),
	    rmvtmp += (data.GetRMV()-rmvsum)*(data.GetRMV()-rmvsum),
	    cmvtmp += (data.GetCMV()-cmvsum)*(data.GetCMV()-cmvsum),
	    hztmp += (data.GetHz()-hzsum)*(data.GetHz()-hzsum);
	double sd = sqrt(sdtmp/Size),rmvsd = sqrt(rmvtmp/Size),cmvsd = sqrt(cmvtmp/Size),hzsd = sqrt(hztmp/Size);
	for(auto it = (*Datavec).begin() ; it != (*Datavec).end() ;)
	    if(fabs(it->GetSpeed()-speedsum)>3*sd||fabs(it->GetRMV()-rmvsum)>3*rmvsd||fabs(it->GetCMV()-cmvsum)>3*cmvsd||fabs(it->GetHz()-hzsum)>3*hzsd)
	        it = Datavec->erase(it);
	    else it++;*/
}

void MainWindow::paintSpeed()
{
	QCustomPlot *pCustomPlot = new QCustomPlot(this);
	pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	pCustomPlot->legend->setVisible(true);
	pCustomPlot->legend->setBrush(QBrush(QColor(255,255,255,150)));
	QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
	dateTicker->setDateTimeFormat("yy-MM-d HH:mm:ss");
	dateTicker->setTickCount(20);
	pCustomPlot->xAxis->setTicker(dateTicker);
	pCustomPlot->xAxis->setTickLabelRotation(60);
	pCustomPlot->setGeometry(QRect(0,0,800,600));

	// 可变数组存放绘图的坐标的数据，分别存放x和y坐标的数据
	QVector<double>  x;
	double Max = -0x3f3f3f3f,Min = 0x3f3f3f3f,Max2 = -0x3f3f3f3f;
	// 添加数据，这里演示y = x^3，为了正负对称，x从-10到+10
	{
		QVector<double>  y;
		double tmpy = 0;
		int num = 0;
		int lastminute = (*Datavec)[0].GetMinute();
		for(Data &data:*Datavec)
		{
			tmpy += data.GetSpeed();
			num++;
			if(data.GetMinute() != lastminute)
			{
				x.push_back(data.GetTime());
				y.push_back(tmpy/num);
				Max = max(Max,tmpy/num);
				Min = min(Min,tmpy/num);
				tmpy = 0;
				num = 0;
				lastminute = data.GetMinute();
			}
		}
		// 向绘图区域QCustomPlot添加一条曲线
		QCPGraph *pGraph = pCustomPlot->addGraph();
		pGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
		pGraph->setData(x,y);
		pGraph->setName("Speed");
		pGraph->setPen(QPen(QColor(32, 178, 170)));
	}

	{
		QVector<double>  y;
		double tmpy = 0;
		int num = 0;
		int lastminute = (*Datavec)[0].GetMinute();
		for(Data &data:*Datavec)
		{
			tmpy += data.GetCMV();
			num++;
			if(data.GetMinute() != lastminute)
			{
				y.push_back(tmpy/num);
				Max = max(Max,tmpy/num);
				Min = min(Min,tmpy/num);
				tmpy = 0;
				num = 0;
				lastminute = data.GetMinute();
			}

		}
		// 向绘图区域QCustomPlot添加一条曲线
		QCPGraph *pGraph = pCustomPlot->addGraph();
		pGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, 3));
		pGraph->setData(x,y);
		pGraph->setName("CMV");
		pGraph->setPen(QPen(QColor(178, 32, 170)));
	}
	double rato;
	{
		QVector<double>  y;
		double tmpy = 0;
		int num = 0;
		int lastminute = (*Datavec)[0].GetMinute();
		for(Data &data:*Datavec)
		{
			tmpy += data.GetRMV();
			num++;
			if(data.GetMinute() != lastminute)
			{
				y.push_back(tmpy/num);
				Max2 = max(Max2,tmpy/num);
				Min = min(Min,tmpy/num);
				tmpy = 0;
				num = 0;
				lastminute = data.GetMinute();
			}

		}
		rato = Max/Max2;
		for(auto &d : y)
			d *= rato;
		// 向绘图区域QCustomPlot添加一条曲线
		QCPGraph *pGraph = pCustomPlot->addGraph();
		pGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
		pGraph->setData(x,y);
		pGraph->setName("RMV");
		pGraph->setPen(QPen(QColor(170, 170, 32)));
	}

	{
		QVector<double>  y;
		double tmpy = 0;
		int num = 0;
		int lastminute = (*Datavec)[0].GetMinute();
		for(Data &data:*Datavec)
		{
			tmpy += data.GetHz();
			num++;
			if(data.GetMinute() != lastminute)
			{
				y.push_back(tmpy/num);
				Max2 = max(Max2,tmpy/num);
				Min = min(Min,tmpy/num);
				tmpy = 0;
				num = 0;
				lastminute = data.GetMinute();
			}

		}
		for(auto &d : y)
			d *= rato;
		// 向绘图区域QCustomPlot添加一条曲线
		QCPGraph *pGraph = pCustomPlot->addGraph();
		pGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
		pGraph->setData(x,y);
		pGraph->setName("Frequency");
		pGraph->setPen(QPen(QColor(170, 255, 32)));
	}


	// 设置坐标轴名称
	pCustomPlot->xAxis->setLabel("Time");
	pCustomPlot->yAxis->setLabel("Speed/CMV");
	pCustomPlot->yAxis2->setLabel("RMV/Frequency");

	// 设置背景色
	pCustomPlot->setBackground(QColor(50, 50, 50));



	// 设置x/y轴文本色、轴线色、字体等
	pCustomPlot->xAxis->setTickLabelColor(Qt::white);
	pCustomPlot->xAxis->setLabelColor(QColor(0, 160, 230));
	pCustomPlot->xAxis->setBasePen(QPen(QColor(32, 178, 170)));
	pCustomPlot->xAxis->setTickPen(QPen(QColor(128, 0, 255)));
	pCustomPlot->xAxis->setSubTickPen(QColor(255, 165, 0));
	QFont xFont = pCustomPlot->xAxis->labelFont();
	xFont.setPixelSize(20);
	pCustomPlot->xAxis->setLabelFont(xFont);

	pCustomPlot->yAxis->setTickLabelColor(Qt::white);
	pCustomPlot->yAxis->setLabelColor(QColor(0, 160, 230));
	pCustomPlot->yAxis->setBasePen(QPen(QColor(32, 178, 170)));
	pCustomPlot->yAxis->setTickPen(QPen(QColor(128, 0, 255)));
	pCustomPlot->yAxis->setSubTickPen(QColor(255, 165, 0));
	QFont yFont = pCustomPlot->yAxis->labelFont();
	yFont.setPixelSize(20);
	pCustomPlot->yAxis->setLabelFont(yFont);

	pCustomPlot->yAxis2->setVisible(true);
	pCustomPlot->yAxis2->setTickLabelColor(Qt::white);
	pCustomPlot->yAxis2->setLabelColor(QColor(0, 160, 230));
	pCustomPlot->yAxis2->setBasePen(QPen(QColor(32, 178, 170)));
	pCustomPlot->yAxis2->setTickPen(QPen(QColor(128, 0, 255)));
	pCustomPlot->yAxis2->setSubTickPen(QColor(255, 165, 0));
	QFont yFont2 = pCustomPlot->yAxis2->labelFont();
	yFont2.setPixelSize(20);
	pCustomPlot->yAxis2->setLabelFont(yFont2);

	// 设置坐标轴显示范围，否则只能看到默认范围
	pCustomPlot->xAxis->setRange(x[0], x[x.size()-1]);
	pCustomPlot->yAxis2->setRange(0,Max2+1);
	pCustomPlot->yAxis->setRange(0,Max+1);
}
