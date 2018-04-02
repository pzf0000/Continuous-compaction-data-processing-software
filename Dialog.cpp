#include "Dialog.h"
#include "ui_Dialog.h"

Dialog::Dialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);
	ui->line->setEnabled(false);
	ui->height->setEnabled(false);
	ui->track->setEnabled(false);
    ui->num_2->setEnabled(false);
    ui->num_3->setEnabled(false);
    ui->num_4->setEnabled(false);
	this->setFixedSize(400,250);
}

Dialog::~Dialog()
{
	delete ui;
}

void Dialog::on_open_clicked()
{
	QString filename = getfilename();
	if(filename == "") return;
	vector<Data> *Datavec = new vector<Data>;
	Datavec->clear();
	taskthread *t = new taskthread(filename,Datavec,maxx,minx,maxy,miny);
	QObject::connect(t,SIGNAL(updateinfo(int,int)),this,SLOT(updateinfo(int,int)),Qt::QueuedConnection);
	QObject::connect(t,SIGNAL(updateinfo2(int)),this,SLOT(updateinfo2(int)),Qt::QueuedConnection);
	QObject::connect(t,SIGNAL(updateinfo2(QString)),this,SLOT(updateinfo2(QString)),Qt::QueuedConnection);
	QObject::connect(t,SIGNAL(paintChart(vector<Data>*)),this,SLOT(paintChart(vector<Data>*)),Qt::QueuedConnection);
	t->start();
	ui->open->setEnabled(false);
	ui->baddata->setText(QString::fromLocal8Bit("读取数据..."));
	//m->show();
}

void Dialog::paintChart(vector<Data> *Datavec)
{
	ui->baddata->setText(QString::fromLocal8Bit("读取数据完成"));
	this->Datavec = Datavec;
	ui->line->setEnabled(true);
	ui->height->setEnabled(true);
	ui->track->setEnabled(true);
	ui->num_2->setEnabled(true);
    ui->num_3->setEnabled(true);
    ui->num_4->setEnabled(true);
}

void Dialog::updateinfo(int n, int usetime)
{
	ui->num->setText(QString::number(n));
	ui->usetime->setText(QString::number(usetime));
}

void Dialog::updateinfo2(int n)
{
	ui->usetime->setText(QString::number(n));
	ui->baddata->setText(QString::fromLocal8Bit("检查测量误差"));
}

QString getfilename()
{
	QString file = QFileDialog::getOpenFileName(
	                   0,
	                   "Choose",
	                   "/",
	                   QString("CSV Files(*.csv)")
	               );
	return file;
}

void Dialog::on_line_clicked()
{
	begin();
	MainWindow *m = new MainWindow(Datavec);
	m->show();
	line = false;
	end();
}

void Dialog::begin()
{
	ui->line->setEnabled(false);
	ui->height->setEnabled(false);
	ui->track->setEnabled(false);
	ui->num_2->setEnabled(false);
    ui->num_3->setEnabled(false);
    ui->num_4->setEnabled(false);
}

void Dialog::end()
{
	if(line)
		ui->line->setEnabled(true);
	if(track)
		ui->track->setEnabled(true);
	if(height)
		ui->height->setEnabled(true);
	if(num)
		ui->num_2->setEnabled(true);
    if(cmv)
        ui->num_3->setEnabled(true);
    if(save)
        ui->num_4->setEnabled(true);
}

void Dialog::on_height_clicked()
{
	begin();
	MainWindow3 *m = new MainWindow3(Datavec,maxx,maxy,minx,miny);
	m->show();
	height = false;
	end();
}

void Dialog::on_track_clicked()
{
	begin();
	MainWindow2 *m = new MainWindow2(Datavec);
	m->show();
	track = false;
	end();
}

void Dialog::on_num_2_clicked()
{
	begin();
    MainWindow4 *m = new MainWindow4(Datavec,maxx,maxy,minx,miny);
	m->show();
	num = false;
	end();
}

void Dialog::on_num_3_clicked()
{
    begin();
    MainWindow5 *m = new MainWindow5(Datavec,maxx,maxy,minx,miny);
    m->show();
    cmv = false;
    end();
}

void Dialog::on_num_4_clicked()
{
    begin();
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save File"),
            "",
            tr("CSV Files (*.csv)"));
    if(fileName.isNull()){
        end();
        return;
    }
    ofstream output(fileName.toStdString());
    output<<Data::title;
    for(auto &data : (*Datavec))
    {
        output<<endl<<data.raw_value;
    }
    output.close();
    QMessageBox *message = new QMessageBox();
    message->setText("保存成功");
    message->show();
    save = false;
    end();
}
