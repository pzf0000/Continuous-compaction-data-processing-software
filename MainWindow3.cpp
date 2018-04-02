#include "MainWindow3.h"
#include "ui_MainWindow3.h"
double table[203][203];
double table2[203][203];
QVector<double> X[257],Y[257];
MainWindow3::MainWindow3(vector<Data> *Datavec_,double maxx,double maxy,double minx, double miny,QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow3)
{
	ui->setupUi(this);
	this->Datavec = Datavec_;
	lenx = maxx - minx, leny = maxy - miny;
	stepx = lenx / xnum,stepy = leny / ynum;
	Minx = minx,Miny = miny,Maxx = maxx,Maxy = maxy;
	paintHeight();
    this->resize(1000,600);
	setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
	setFixedSize(this->width(), this->height());
    connect(pCustomPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(my_mouseMove(QMouseEvent*)));
    connect(pCustomPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(my_mouseMove(QMouseEvent*)));
    setTexts();
}
void MainWindow3::setTexts()
{
    ui->x1->setText(QString::fromStdString(set1x));
    ui->x2->setText(QString::fromStdString(set2x));
    ui->x3->setText(QString::fromStdString(set3x));
    ui->x4->setText(QString::fromStdString(set4x));
    ui->y1->setText(QString::fromStdString(set1y));
    ui->y2->setText(QString::fromStdString(set2y));
    ui->y3->setText(QString::fromStdString(set3y));
    ui->y4->setText(QString::fromStdString(set4y));
}
void MainWindow3::s()
{
	memcpy(table,table2,sizeof(table));

	for(int i = 0 ; i <= xnum ; i++)
		table2[i][0] = table[i][0],
		               table2[i][xnum] = table[i][xnum],
		                                 table2[0][i] = table[0][i],
		                                         table2[xnum][i] = table[xnum][i];
	for(int i = 1 ; i < xnum ; i++)
		for(int j = 1 ; j < ynum ; j++)
		{
			if(table[i][j] > 0x3f3f3f3f)
			{
				int n = 0;
				double s = 0;
				if(table[i][j-1] < 0x3f3f3f3f) s = table[i][j-1],n++;
				double x = 0;
				if(table[i][j+1] < 0x3f3f3f3f) x = table[i][j+1],n++;
				double z = 0;
				if(table[i-1][j] < 0x3f3f3f3f) z = table[i-1][j],n++;
				double y = 0;
				if(table[i+1][j] < 0x3f3f3f3f) y = table[i+1][j],n++;
				if(n)
					table2[i][j] = (s+x+z+y)/n;
				else table2[i][j] = table[i][j];
			}
			else
			{
				table2[i][j] = table[i][j];
			}

		}
}

void MainWindow3::paintHeight()
{

	for(int i = 0 ; i <= xnum  ; i++)
		for(int j = 0 ; j <= ynum  ; j++)
			table[i][j] = 0xffffffff,
			              table2[i][j] = 0xffffffff;
	for(Data &data:*Datavec)
	{
		int indexx = -1,indexy = -1;
		for(int i = 1 ; i < xnum ; i++)
			if(data.Lx < Minx + stepx*i)
			{
				indexx = i;
				break;
			}
		if(indexx == -1) indexx = xnum;

		for(int i = 1 ; i < ynum ; i++)
			if(data.Ly < Miny + stepy*i)
			{
				indexy = i;
				break;
			}
		if(indexy == -1) indexy = ynum;

		table[indexx][indexy] = min(table[indexx][indexy],data.Lz);

		indexx = -1,indexy = -1;
		for(int i = 1 ; i < xnum ; i++)
			if(data.Rx < Minx + stepx*i)
			{
				indexx = i;
				break;
			}
		if(indexx == -1) indexx = xnum;

		for(int i = 1 ; i < ynum ; i++)
			if(data.Ry < Miny + stepy*i)
			{
				indexy = i;
				break;
			}
		if(indexy == -1) indexy = ynum;

		table[indexx][indexy] = min(table[indexx][indexy],data.Rz);

		indexx = -1,indexy = -1;
		for(int i = 1 ; i < xnum ; i++)
			if(data.X < Minx + stepx*i)
			{
				indexx = i;
				break;
			}
		if(indexx == -1) indexx = xnum;

		for(int i = 1 ; i < ynum ; i++)
			if(data.Y < Miny + stepy*i)
			{
				indexy = i;
				break;
			}
		if(indexy == -1) indexy = ynum;

		table[indexx][indexy] = min(table[indexx][indexy],data.Z);

	}
//----------------------------------------------


	/*Data data = (*Datavec)[0];
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
	            if(flag == 0){
	                s3 = gettrianglearea(leftx,lefty,lastleftx,lastlefty,i,j);
	                s4 = gettrianglearea(rightx,righty,lastrightx,lastrighty,i,j);
	            }else{
	                s3 = gettrianglearea(leftx,lefty,lastrightx,lastrighty,i,j);
	                s4 = gettrianglearea(rightx,righty,lastleftx,lastlefty,i,j);
	            }
	            double S1,S2;
	            if(flag == 0){
	                S1 = gettrianglearea(leftx,lefty,rightx,righty,lastleftx,lastlefty);
	                S2 = gettrianglearea(lastleftx,lastlefty,lastrightx,lastrighty,rightx,righty);
	            }else{
	                S1 = gettrianglearea(leftx,lefty,rightx,righty,lastrightx,lastrighty);
	                S2 = gettrianglearea(lastleftx,lastlefty,lastrightx,lastrighty,leftx,lefty);
	            }
	            if(fabs((s1+s2+s3+s4)-(S1+S2)) < 1e-1)
	                table[i][j] = min(table[i][j],data.Z);
	        }
	    lastleftx = leftx,lastlefty = lefty,lastrightx = rightx,lastrighty = righty;
	}*/

//----------------------------------------------


	for(int i = 0 ; i <= xnum ; i++)
		table2[i][0] = table[i][0],
		               table2[i][xnum] = table[i][xnum],
		                                 table2[0][i] = table[0][i],
		                                         table2[xnum][i] = table[xnum][i];

	for(int i = 1 ; i < xnum ; i++)
		for(int j = 1 ; j < ynum ; j++)
		{
			if(table[i][j] > 0x3f3f3f3f)
			{
				int n = 0;
				double s = 0;
				if(table[i][j-1] < 0x3f3f3f3f) s = table[i][j-1],n++;
				double x = 0;
				if(table[i][j+1] < 0x3f3f3f3f) x = table[i][j+1],n++;
				double z = 0;
				if(table[i-1][j] < 0x3f3f3f3f) z = table[i-1][j],n++;
				double y = 0;
				if(table[i+1][j] < 0x3f3f3f3f) y = table[i+1][j],n++;
				if(n)
					table2[i][j] = (s+x+z+y)/n;
				else table2[i][j] = table[i][j];
			}
			else
			{
				table2[i][j] = table[i][j];
			}

		}


	s();



	for(int i = 0 ; i <= xnum  ; i++)
		for(int j = 0 ; j <= ynum  ; j++)
			if(table[i][j]<0x3f3f3f3f)
				maxh = max(maxh,table2[i][j]),
				minh = min(minh,table2[i][j]);

    pCustomPlot = new QCustomPlot(this);
    int GeometryX = 800;
    int GeometryY = 800*(leny/lenx);cout<<GeometryX<<" "<<GeometryY<<endl;
    double d1 = GeometryX / 800.;
    double d2 = GeometryY / 600.;
    GeometryX /= max(d1,d2);
    GeometryY /= max(d1,d2);
    pCustomPlot->setGeometry(QRect(0,0,GeometryX,GeometryY));

	for(int i = 0 ; i <= 256 ; i++)
		X[i].clear(),Y[i].clear();
	for(int i = 0 ; i <= xnum; i++)
		for(int j = 0 ; j <= ynum ; j++)
		{
			if(table2[i][j]<0x3f3f3f3f)
			{
				setColorByHeight(table2[i][j],i,j);
				/*QCPGraph *pGraph = pCustomPlot->addGraph();
				pGraph->addData(i,j);
				pGraph->setPen(QPen(setColorByHeight(table2[i][j]),5));
				pGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossSquare, 4));*/
			}
		}
	int n = 0 ;
	int vis[260];
	memset(vis,0,sizeof(vis));
	srand(time(0));
	while(n < 256)
	{
		int i = rand()%257;
		if(vis[i]) continue;
		if(X[i].size() != 0)
		{
			double p = (double)i / 255;
			QCPGraph *pGraph = pCustomPlot->addGraph();
			pGraph->setData(X[i],Y[i]);
            pGraph->setPen(QPen(QColor(255*p,255*p,255*p),3));
            pGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossSquare, 3));
			pGraph->setLineStyle(QCPGraph::lsNone);
		}
		n++;
		vis[i] = 1;
	}
	// 向绘图区域QCustomPlot添加一条曲线

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
}

void MainWindow3::setColorByHeight(double h,int x, int y)
{
	double p = (maxh-h)/(maxh - minh);
	int index = p * 255;
	X[index].push_back(x);
	Y[index].push_back(y);
	//return QColor(255*p,255*p,255*p);
}

MainWindow3::~MainWindow3()
{
	delete ui;
}

void MainWindow3::my_mouseMove(QMouseEvent *event)
{
    if(pCustomPlot == nullptr) return;
    //获取鼠标坐标点
        double x_pos = event->pos().x();
        double y_pos = event->pos().y();

    // 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
    // coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
        double x_val = -pCustomPlot->xAxis->pixelToCoord(x_pos)*(Maxx - Minx)/200. + Maxx;
        double y_val = -pCustomPlot->yAxis->pixelToCoord(y_pos)*(Maxy - Miny)/200. + Maxy;
    {
            stringstream ss;
            ss<<fixed<<setprecision(3)<<x_val;
            string x_str;
            ss>>x_str;
            ui->xtip->setText(QString::fromStdString(x_str));
    }
    {
            stringstream ss;
            ss<<fixed<<setprecision(3)<<y_val;
            string y_str;
            ss>>y_str;
            ui->ytip->setText(QString::fromStdString(y_str));
    }


    if(event->button() == Qt::LeftButton)
    {string x_str,y_str;
        {
                stringstream ss;
                ss<<fixed<<setprecision(3)<<x_val;
                //string x_str;
                ss>>x_str;
                ui->xtip->setText(QString::fromStdString(x_str));
        }
        {
                stringstream ss;
                ss<<fixed<<setprecision(3)<<y_val;
                //string y_str;
                ss>>y_str;
                ui->ytip->setText(QString::fromStdString(y_str));
        }
        seted++;
        if(seted == 1){
            set1x = x_str;set1y = y_str;
        }else if(seted == 2){
            set2x = x_str;set2y = y_str;
        }else if(seted == 3){
            set3x = x_str;set3y = y_str;
        }else if(seted == 4){
            set4x = x_str;set4y = y_str;
        }
        setTexts();
    }

}

int MainWindow3::pnpoly(int npol, double *xp, double *yp, double x, double y)
    {
      int i, j, c = 0;
      for (i = 0, j = npol-1; i < npol; j = i++) {
        if ((((yp[i] <= y) && (y < yp[j])) ||
             ((yp[j] <= y) && (y < yp[i]))) &&
            (x < (xp[j] - xp[i]) * (y - yp[i]) / (yp[j] - yp[i]) + xp[i]))
          c = !c;
      }
      return c;
    }

void MainWindow3::on_pushButton_clicked()
{
    if(seted < 4){
        QMessageBox *message = new QMessageBox();
        message->setText("请继续选择");
        message->show();
        return;
    }
    QString fileName = getfilename();
    if(fileName.isNull()) return;
    cout<<"-------\n";
    double *x = new double[4];
    double *y = new double[4];
    stringstream sx;
    sx<<set1x<<" "<<set2x<<" "<<set3x<<" "<<set4x;
    cout<<sx.str();
    for(int i = 0 ; i < 4 ; i++)
        sx>>x[i];
    stringstream sy;
    sy<<set1y<<" "<<set2y<<" "<<set3y<<" "<<set4y;
    cout<<sy.str();
    for(int i = 0 ; i < 4 ; i++)
        sy>>y[i];
    ofstream output(fileName.toStdString());
    output<<Data::title;
    for(auto &data : (*Datavec))
    {
        if(pnpoly(4,x,y,data.X,data.Y))
            output<<endl<<data.raw_value;
    }
    output.close();
    delete[] x,delete[] y;
    QMessageBox *message = new QMessageBox();
    message->setText("保存成功");
    message->show();
}

QString MainWindow3::getfilename()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save File"),
            "",
            tr("CSV Files (*.csv)"));
    return fileName;
}

void MainWindow3::on_pushButton_2_clicked()
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
