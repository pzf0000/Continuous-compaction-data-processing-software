#include "MainWindow4.h"
#include "ui_MainWindow4.h"
int numtable_[2003][2003];
QVector<double> Xf_[20],Yf_[20];
MainWindow4::MainWindow4(vector<Data> *Datavec_,double maxx,double maxy,double minx, double miny,QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow4)
{
	ui->setupUi(this);
	this->Datavec = Datavec_;
	lenx = maxx - minx, leny = maxy - miny;
	stepx = lenx / xnum,stepy = leny / ynum;
	Minx = minx,Miny = miny,Maxx = maxx,Maxy = maxy;
	paintNum();
    this->resize(1000,700);
	setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
}

MainWindow4::~MainWindow4()
{
	delete ui;
}

void MainWindow4::paintNum()
{
	for(int i = 0 ; i <= xnum  ; i++)
		for(int j = 0 ; j <= ynum  ; j++)
            numtable_[i][j] = 0;

	Data data = (*Datavec)[0];
	int lastleftx = -1 ,
	    lastlefty = -1,
	    lastrightx = -1,
	    lastrighty = -1;
	for(int i = 1 ; i < xnum ; i++)
		if(data.Lx < Minx + stepx*i)
		{
			lastleftx = i;
			break;
		}
	if(lastleftx == -1) lastleftx = xnum;

	for(int i = 1 ; i < ynum ; i++)
		if(data.Ly < Miny + stepy*i)
		{
			lastlefty = i;
			break;
		}
	if(lastlefty == -1) lastlefty = ynum;

	for(int i = 1 ; i < xnum ; i++)
		if(data.Lx < Minx + stepx*i)
		{
			lastrightx = i;
			break;
		}
	if(lastrightx == -1) lastrightx = xnum;

	for(int i = 1 ; i < ynum ; i++)
		if(data.Ly < Miny + stepy*i)
		{
			lastrighty = i;
			break;
		}
	if(lastrighty == -1) lastrighty = ynum;
	//int lastsec = data.GetMinute();
	for(Data &data:*Datavec)
	{
		int leftx = -1,
		    lefty = -1,
		    rightx = -1,
		    righty = -1;

		for(int i = 1 ; i < xnum ; i++)
			if(data.Lx < Minx + stepx*i)
			{
				leftx = i;
				break;
			}
		if(leftx == -1) leftx = xnum;

		for(int i = 1 ; i < ynum ; i++)
			if(data.Ly < Miny + stepy*i)
			{
				lefty = i;
				break;
			}
		if(lefty == -1) lefty = ynum;

		for(int i = 1 ; i < xnum ; i++)
			if(data.Rx < Minx + stepx*i)
			{
				rightx = i;
				break;
			}
		if(rightx == -1) rightx = xnum;

		for(int i = 1 ; i < ynum ; i++)
			if(data.Ry < Miny + stepy*i)
			{
				righty = i;
				break;
			}
		if(righty == -1) righty = ynum;

		int minxx = min(min(min(lastrightx,lastleftx),rightx),leftx);
		int minyy = min(min(min(lastrighty,lastlefty),righty),lefty);
		int maxxx = max(max(max(lastrightx,lastleftx),rightx),leftx);
		int maxyy = max(max(max(lastrighty,lastlefty),righty),lefty);

		int flag = 0;//0 ll 1 rl
		Point a,b,c,d;
		a.x = leftx,a.y = lefty;
		b.x = lastleftx,b.y = lastlefty;
		c.x = rightx,c.y = righty;
		d.x = lastrightx,d.y = lastrighty;
		if(detectIntersect(a,b,c,d))
			flag = 1;
		//qDebug("%");
		for(int i = minxx ; i <= maxxx ; i++)
			for(int j = minyy ; j <= maxyy ; j++)
			{
				double s1,s2,s3,s4;
				s1 = gettrianglearea(leftx,lefty,rightx,righty,i,j);
				s2 = gettrianglearea(lastleftx,lastlefty,lastrightx,lastrighty,i,j);
				if(flag == 0)
				{
					s3 = gettrianglearea(leftx,lefty,lastleftx,lastlefty,i,j);
					s4 = gettrianglearea(rightx,righty,lastrightx,lastrighty,i,j);
				}
				else
				{
					s3 = gettrianglearea(leftx,lefty,lastrightx,lastrighty,i,j);
					s4 = gettrianglearea(rightx,righty,lastleftx,lastlefty,i,j);
				}
				double S1,S2;
				if(flag == 0)
				{
					S1 = gettrianglearea(leftx,lefty,rightx,righty,lastleftx,lastlefty);
					S2 = gettrianglearea(lastleftx,lastlefty,lastrightx,lastrighty,rightx,righty);
				}
				else
				{
					S1 = gettrianglearea(leftx,lefty,rightx,righty,lastrightx,lastrighty);
					S2 = gettrianglearea(lastleftx,lastlefty,lastrightx,lastrighty,leftx,lefty);
				}
				if(fabs((s1+s2+s3+s4)-(S1+S2)) < 1e-1)
                    ++numtable_[i][j];
			}
		lastleftx = leftx,lastlefty = lefty,lastrightx = rightx,lastrighty = righty;
	}

	int num[11],sum = 0;
	memset(num,0,sizeof(num));

	for(int i = 0 ; i <= xnum; i++)
		for(int j = 0 ; j <= ynum ; j++)
		{
            if(numtable_[i][j]>0)
			{
                if(numtable_[i][j]<maxnum)
				{
                    Xf_[numtable_[i][j]].push_back(i);
                    Yf_[numtable_[i][j]].push_back(j);
                    num[numtable_[i][j]]++;
				}
				else
				{
                    Xf_[maxnum].push_back(i);
                    Yf_[maxnum].push_back(j);
					num[maxnum]++;
				}
				sum++;
			}
        }

	QColor qcolor[20];
	qcolor[1] = QColor(215,173,210);
	qcolor[2] = QColor(248,173,186);
	qcolor[3] = QColor(96,96,96);
	qcolor[4] = QColor(238,145,22);
	qcolor[5] = QColor(91,114,176);
	qcolor[6] = QColor(115,184,223);
	qcolor[7] = QColor(192,67,14);
	qcolor[8] = QColor(31,97,22);
	qcolor[9] = QColor(205,10,11);
	qcolor[10] = QColor(71,3,91);

    pCustomPlot = new QCustomPlot(this);
    int GeometryX = 800;
    int GeometryY = 800*(leny/lenx);
    double d1 = GeometryX / 800.;
    double d2 = GeometryY / 600.;
    GeometryX /= max(d1,d2);
    GeometryY /= max(d1,d2);

    pCustomPlot->setGeometry(QRect(0,0,GeometryX,GeometryY));


	for(int i = 1 ; i <= maxnum ; i++)
        if(Xf_[i].size() != 0)
		{
			QCPGraph *pGraph = pCustomPlot->addGraph();
            pGraph->setData(Xf_[i],Yf_[i]);
			pGraph->setPen(QPen(qcolor[i],1));
			pGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossSquare, 1));
			pGraph->setLineStyle(QCPGraph::lsNone);
		}

	pCustomPlot->xAxis->setVisible(false);
	pCustomPlot->yAxis->setVisible(false);
	pCustomPlot->setBackground(QColor(255, 222, 173));
	/*    // 设置背景色

	//32,178,170
	    pCustomPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossSquare, 1));



	*/
	// 设置坐标轴显示范围，否则只能看到默认范围
	pCustomPlot->xAxis->setRange(-5, xnum+5);
	pCustomPlot->yAxis->setRange(-5, ynum+5);

	ui->p1->setStyleSheet("background-color:#D7ADD2");
	ui->p1_2->setStyleSheet("background-color:#F8ADBA");
	ui->p1_3->setStyleSheet("background-color:#606060");
	ui->p1_4->setStyleSheet("background-color:#EE9116");
	ui->p1_5->setStyleSheet("background-color:#5B72B0");
	ui->p1_6->setStyleSheet("background-color:#73B8DF");
	ui->p1_7->setStyleSheet("background-color:#C0430E");
	ui->p1_8->setStyleSheet("background-color:#1F6116");
	ui->p1_9->setStyleSheet("background-color:#CD0A0B");
	ui->p1_10->setStyleSheet("background-color:#47035B");
	ui->label->setText(QString::fromStdString(to_string((double)num[1]*100/sum).substr(0,(double)num[1]*100/sum>10?5:4)+"%"));
	ui->label_2->setText(QString::fromStdString(to_string((double)num[2]*100/sum).substr(0,(double)num[2]*100/sum>10?5:4)+"%"));
	ui->label_3->setText(QString::fromStdString(to_string((double)num[3]*100/sum).substr(0,(double)num[3]*100/sum>10?5:4)+"%"));
	ui->label_4->setText(QString::fromStdString(to_string((double)num[4]*100/sum).substr(0,(double)num[4]*100/sum>10?5:4)+"%"));
	ui->label_5->setText(QString::fromStdString(to_string((double)num[5]*100/sum).substr(0,(double)num[5]*100/sum>10?5:4)+"%"));
	ui->label_6->setText(QString::fromStdString(to_string((double)num[6]*100/sum).substr(0,(double)num[6]*100/sum>10?5:4)+"%"));
	ui->label_7->setText(QString::fromStdString(to_string((double)num[7]*100/sum).substr(0,(double)num[7]*100/sum>10?5:4)+"%"));
	ui->label_8->setText(QString::fromStdString(to_string((double)num[8]*100/sum).substr(0,(double)num[8]*100/sum>10?5:4)+"%"));
	ui->label_9->setText(QString::fromStdString(to_string((double)num[9]*100/sum).substr(0,(double)num[9]*100/sum>10?5:4)+"%"));
	ui->label_10->setText(QString::fromStdString(to_string((double)num[10]*100/sum).substr(0,(double)num[10]*100/sum>10?5:4)+"%"));

	ui->p1->setAlignment(Qt::AlignCenter);
	ui->p1_2->setAlignment(Qt::AlignCenter);
	ui->p1_3->setAlignment(Qt::AlignCenter);
	ui->p1_4->setAlignment(Qt::AlignCenter);
	ui->p1_5->setAlignment(Qt::AlignCenter);
	ui->p1_6->setAlignment(Qt::AlignCenter);
	ui->p1_7->setAlignment(Qt::AlignCenter);
	ui->p1_8->setAlignment(Qt::AlignCenter);
	ui->p1_9->setAlignment(Qt::AlignCenter);
	ui->p1_10->setAlignment(Qt::AlignCenter);
	ui->label->setAlignment(Qt::AlignCenter);
	ui->label_2->setAlignment(Qt::AlignCenter);
	ui->label_3->setAlignment(Qt::AlignCenter);
	ui->label_4->setAlignment(Qt::AlignCenter);
	ui->label_5->setAlignment(Qt::AlignCenter);
	ui->label_6->setAlignment(Qt::AlignCenter);
	ui->label_7->setAlignment(Qt::AlignCenter);
	ui->label_8->setAlignment(Qt::AlignCenter);
	ui->label_9->setAlignment(Qt::AlignCenter);
	ui->label_10->setAlignment(Qt::AlignCenter);
}




void MainWindow4::on_pushButton_2_clicked()
{
    QString pixSize = ui->lineEdit->text();
    ui->lineEdit->setText("");
    bool flag = false;
    int newPixSize = pixSize.toInt(&flag);
    if(!flag) return;
    if(newPixSize < 1 || newPixSize > 8)
        return;
    for(int i = 0 ; i < pCustomPlot->graphCount() ; i++)
        pCustomPlot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossSquare, newPixSize));
    pCustomPlot->replot();
}
