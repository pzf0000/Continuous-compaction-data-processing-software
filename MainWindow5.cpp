#include "MainWindow5.h"
#include "ui_MainWindow5.h"
vector<Data> **numtable;
int **status;
QVector<double> Xf[20],Yf[20];
QStandardItemModel *model = new QStandardItemModel();
set<Data> st;
double allA = 0;
MainWindow5::MainWindow5(vector<Data> *Datavec_,double maxx,double maxy,double minx, double miny,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow5)
{
    ui->setupUi(this);
    this->Datavec = Datavec_;
    lenx = maxx - minx, leny = maxy - miny;
    stepx = 0.4,stepy = 0.4;
    xnum = lenx/stepx, ynum = leny/stepy;
    xsize = xnum + 1,ysize = ynum + 1;
    numtable = new vector<Data> *[xsize];
    for(int i = 0 ; i <= xnum ; i++)
        numtable[i] = new vector<Data>[ysize];
    status = new int*[xsize];
    for(int i = 0 ; i <= xnum ; i++)
        status[i] = new int[ysize];
    //numtable下标范围是0,0到xnum,ynum;
    Minx = minx,Miny = miny,Maxx = maxx,Maxy = maxy;
    //cout<<"startPaint--------------------\n------------------------------\n";
    paintNum();
    connect(pCustomPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(my_mouseMove(QMouseEvent*)));
    connect(pCustomPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(my_mouseMove(QMouseEvent*)));
    this->resize(1000,700);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    model->setColumnCount(2);

    ui->tableView->setModel(model);
}

MainWindow5::~MainWindow5()
{
    delete ui;
}

void MainWindow5::paintNum()
{
    for(int i = 0 ; i <= xnum  ; i++)
        for(int j = 0 ; j <= ynum  ; j++)
            numtable[i][j].clear(),status[i][j] = 0;

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
                    numtable[i][j].push_back(data);
            }
        lastleftx = leftx,lastlefty = lefty,lastrightx = rightx,lastrighty = righty;
    }

    //int num[11],sum = 0;
    //memset(num,0,sizeof(num));
    double cmvsum = 0;
    for(Data &data:*Datavec)
        cmvsum += data.GetCMV();
    size_t Size = (*Datavec).size();
        cmvsum /= Size;
        double cmvtmp = 0;
        for(Data &data:*Datavec)
            cmvtmp += (data.GetCMV()-cmvsum)*(data.GetCMV()-cmvsum);
        double scmv = sqrt(cmvtmp/Size);
    for(int i = 0 ; i <= xnum ; i++)
        for(int j = 0 ; j < ynum ; j++)
        {
            if(!numtable[i][j].empty())
                status[i][j] = 1;//有数据
            else{
                continue;
            }
            int keyinum = 0;
            for(auto data : numtable[i][j])
            {
                if(fabs(data.GetCMV() - cmvsum) > 3*scmv)
                {
                    keyinum++;
                }
            }
            if(numtable[i][j].size() == 1){
                if(keyinum == 1)
                    status[i][j] = 2;
            }else{
                if(keyinum == 1)
                    status[i][j] = 2;//真正的可疑
                else if(keyinum > 1){
                    status[i][j] = 3;//等待继续判断
                }
            }
        }


    for(int i = 0 ; i <= xnum; i++)
        for(int j = 0 ; j <= ynum ; j++)
        {
            if(status[i][j]>0)
            {
                if(status[i][j]<maxnum)
                {
                    Xf[status[i][j]].push_back(i);
                    Yf[status[i][j]].push_back(j);
                    //num[numtable[i][j]]++;
                }
                else
                {
                    Xf[maxnum].push_back(i);
                    Yf[maxnum].push_back(j);
                    //num[maxnum]++;
                }
                //sum++;
            }
        }

    QColor qcolor[20];
    qcolor[1] = QColor(255,255,255);//(215,173,210);
    qcolor[2] = QColor(248,173,186);
    qcolor[3] = QColor(96,96,96);
    qcolor[4] = QColor(238,145,22);
    qcolor[5] = QColor(91,114,176);
    qcolor[6] = QColor(115,184,223);
    qcolor[7] = QColor(192,67,14);
    qcolor[8] = QColor(31,97,22);
    qcolor[9] = QColor(205,10,11);
    qcolor[10] = QColor(71,3,91);

    this->pCustomPlot = new QCustomPlot(this);

    int GeometryX = 800;
    int GeometryY = 800*(leny/lenx);
    double d1 = GeometryX / 800.;
    double d2 = GeometryY / 600.;
    GeometryX /= max(d1,d2);
    GeometryY /= max(d1,d2);

    pCustomPlot->setGeometry(QRect(0,0,GeometryX,GeometryY));


    for(int i = 1 ; i <= maxnum ; i++)
        if(Xf[i].size() != 0)
        {
            QCPGraph *pGraph = pCustomPlot->addGraph();
            pGraph->setData(Xf[i],Yf[i]);
            pGraph->setPen(QPen(qcolor[i],4));
            pGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossSquare, 6));
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

    //拟合直线
    vector<double> result;
    LineFitLeastSquares(Datavec,result);
    allA = result[0];
    char s[100];
    sprintf(s,"CMV = %.7f * Time + (%.3f) \n r^2 = %.3f",result[0],result[1],result[2]);
    string res_str(s);
    ui->label_2->setText(QString::fromStdString(res_str));
}

void MainWindow5::on_pushButton_2_clicked()
{
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
}


void MainWindow5::my_mouseMove(QMouseEvent *event)
{
    if(pCustomPlot == nullptr) return;
    //获取鼠标坐标点
        double x_pos = event->pos().x();
        double y_pos = event->pos().y();

    // 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
    // coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
        double x_val = pCustomPlot->xAxis->pixelToCoord(x_pos);
        double y_val = pCustomPlot->yAxis->pixelToCoord(y_pos);
        if(x_val>=0&&x_val<=xnum){
            if(y_val>=0&&y_val<=ynum)
                ui->status->setText(QString::number(status[(int)x_val][(int)y_val]));
        }

}

void MainWindow5::LineFitLeastSquares(vector<Data> *vec,vector<double> &vResult)
{
    double A = 0.0;
    double B = 0.0;
    double C = 0.0;
    double D = 0.0;
    double E = 0.0;
    double F = 0.0;

    double mintime = 0x3f3f3f3f;
    for(auto data : (*Datavec))
        mintime = min(mintime,(double)data.GetTime());

    for (auto data : (*vec))
    {
        A += (data.GetTime() - mintime) * (data.GetTime() - mintime);
        B += (data.GetTime() - mintime);
        C += (data.GetTime() - mintime) * data.GetCMV();
        D += data.GetCMV();
    }

    // 计算斜率a和截距b
    double a, b, temp = 0;
    if( temp = ((*vec).size()*A - B*B) )// 判断分母不为0
    {
        a = ((*vec).size()*C - B*D) / temp;
        b = (A*D - B*C) / temp;
    }
    else
    {
        a = 1;
        b = 0;
    }

    // 计算相关系数r
    double Xmean, Ymean;
    Xmean = B / (*vec).size();
    Ymean = D / (*vec).size();

    double tempSumXX = 0.0, tempSumYY = 0.0;
    for (auto data : (*vec))
    {
        tempSumXX += ((data.GetTime() - mintime) - Xmean) * ((data.GetTime() - mintime) - Xmean);
        tempSumYY += (data.GetCMV() - Ymean) * (data.GetCMV() - Ymean);
        E += ((data.GetTime() - mintime) - Xmean) * (data.GetCMV() - Ymean);
    }
    F = sqrt(tempSumXX) * sqrt(tempSumYY);

    double r;
    r = E / F;
    vResult.push_back(a);
    vResult.push_back(b);
    vResult.push_back(r*r);
}

void MainWindow5::on_pushButton_clicked()
{
    QString fanwei = ui->lineEdit_2->text();
    bool flag = false;
    double fanweid = fanwei.toDouble(&flag);
    if(!flag) return;
    model->removeRows(0,model->rowCount());
    st.clear();
    int count = 0;

    for(int i = 0 ; i <= xnum ; i++)
        for(int j = 0 ; j <= ynum ; j++)
        {
            if(status[i][j] == 2){
                for(auto data : (numtable[i][j]))
                {
                    st.insert(data);
                }
            }else if(status[i][j] == 3){
                vector<double> result;
                LineFitLeastSquares(&numtable[i][j],result);
                if(fabs(result[0]-allA) > fabs(fanweid)){
                    for(auto data : (numtable[i][j]))
                    {
                        st.insert(data);
                    }
                }
            }
        }
    for(auto it = st.cbegin() ; it != st.cend() ; it++)
    {
        model->setItem(count++,0,new QStandardItem(QString::fromLocal8Bit(it->raw_value.c_str())));
    }

    ui->tableView->resizeColumnToContents(0);
}

void MainWindow5::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save File"),
            "",
            tr("CSV Files (*.csv)"));
    if(fileName.isNull()){
        return;
    }
    ofstream output(fileName.toStdString());
    output<<Data::title;
    for(auto it = st.cbegin() ; it != st.cend() ; it++)
    {
        output<<endl<<it->raw_value;
    }
    output.close();
    QMessageBox *message = new QMessageBox();
    message->setText("保存成功");
    message->show();
}
