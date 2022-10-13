#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	myCom=new SerialPortCom();
	connect(myCom,SIGNAL(readyRead(SerialPortCom*)),this,SLOT(ComReadyRead(SerialPortCom*)));
	connect(myCom,SIGNAL(abnormalReturn()),this,SLOT(errorget()));
	connect(myCom,SIGNAL(sendMsg(QByteArray)),this,SLOT(sendmsg(QByteArray)));

	connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(ComConnect()));
	connect(ui.pushButton_2,SIGNAL(clicked()),this,SLOT(DisConnect()));

	connect(ui.pushButton_3,SIGNAL(clicked()),this,SLOT(WriteTest()));
	connect(ui.pushButton_4,SIGNAL(clicked()),this,SLOT(WriteTest()));
	connect(ui.pushButton_5,SIGNAL(clicked()),this,SLOT(WriteTest()));
	connect(ui.pushButton_6,SIGNAL(clicked()),this,SLOT(WriteTest()));

	connect(ui.pushButton_7,SIGNAL(clicked()),this,SLOT(WriteTest()));
	connect(ui.pushButton_8,SIGNAL(clicked()),this,SLOT(WriteTest()));
	connect(ui.pushButton_9,SIGNAL(clicked()),this,SLOT(WriteTest()));
	connect(ui.pushButton_10,SIGNAL(clicked()),this,SLOT(WriteTest()));
}

MainWindow::~MainWindow()
{

}
void MainWindow::readMyCom()//读取缓冲的数据，每秒读一次
{
	QByteArray temp = myCom->ComGetMsg();
	if(temp.size()==0)
		return ;
	QDataStream out(&temp,QIODevice::ReadWrite);    //将字节数组读入
	ui.textBrowser->insertPlainText(QDateTime::currentDateTime().toString("\nyyyy-MM-dd hh:mm:ss") + " [recieve]");
	while(!out.atEnd())
	{
		qint8 outChar = 0;
		out>>outChar;   //每字节填充一次，直到结束
		//十六进制的转换
		QString str = QString("%1").arg(outChar&0xFF,2,16,QLatin1Char('0'));
		ui.textBrowser->insertPlainText(str.toUpper());//大写
		ui.textBrowser->insertPlainText(" ");//每发送两个字符后添加一个空格
		ui.textBrowser->moveCursor(QTextCursor::End);
	}
	ui.textBrowser->insertPlainText("\n");
}



void MainWindow::ComReadyRead(SerialPortCom* myCom)
{
	readMyCom();
	return ;
	//QString msg = myCom->ComGetMsg();
	QByteArray res=myCom->ComGetMsg();
	for(int i=0;i<res.size();i++)
	{
		qDebug()<<QString::number(res[i],16)<<" "<<(int)res[i];
	}

	ui.textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + " [recieve] ");
}

void MainWindow::ComConnect()
{
	myCom->setPortName(ui.lineEdit->text());
	if(myCom->ComOpen())
	{
		ui.textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + " [remind] PortOpen:" + ui.lineEdit->text() + "\n");
	}
	else
	{
		ui.textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + " [remind] PortOpenError\n");
	}
}

void MainWindow::DisConnect()
{
	myCom->ComClose();
	ui.textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + " [remind] PortClose\n");
}

void MainWindow::WriteTest()
{
	QObject *o=sender();
	QPushButton *p=(QPushButton *)o;
	if(p->objectName()=="pushButton_3")//速度控制例程
	{
		int station=ui.lineEdit_4->text().toInt(0,16);
		myCom->Get_RealTimeDate(station);
	}
	if(p->objectName()=="pushButton_4")//速度控制例程
	{
		int station=ui.lineEdit_4->text().toInt(0,16);
		int aSpeed=ui.lineEdit_5->text().toInt(0,10);
		int sSpeed=ui.lineEdit_5->text().toInt(0,10);
		int Speed=ui.lineEdit_9->text().toInt(0,10);
		myCom->SET_SpeedControl(station,aSpeed,sSpeed,Speed);
	}
	if(p->objectName()=="pushButton_5")//位置控制例程
	{
		int station=ui.lineEdit_4->text().toInt(0,16);
		int aSpeed=ui.lineEdit_5->text().toInt(0,10);
		int sSpeed=ui.lineEdit_5->text().toInt(0,10);
		int Speed=ui.lineEdit_9->text().toInt(0,10);
		int Location=ui.lineEdit_2->text().toInt(0,10);
		myCom->SET_GoPosition(station,Location,aSpeed,sSpeed,Speed);
	}
	if(p->objectName()=="pushButton_6")//回原点控制例程
	{
		int station=ui.lineEdit_4->text().toInt(0,16);
		myCom->SET_ReToPhotography(station);
	}
	if(p->objectName()=="pushButton_7")//绝对运动
	{
		int station=ui.lineEdit_4->text().toInt(0,16);
		myCom->Set_Position(station,GoPosition::Absolute);
	}
	if(p->objectName()=="pushButton_8")//相对运动
	{
		int station=ui.lineEdit_4->text().toInt(0,16);
		myCom->Set_Position(station,GoPosition::Relative);
	}
	if(p->objectName()=="pushButton_9")//启动
	{
		int station=ui.lineEdit_4->text().toInt(0,16);
		myCom->Ctl_Jogging(station,1);
	}
	if(p->objectName()=="pushButton_10")//停止
	{
		int station=ui.lineEdit_4->text().toInt(0,16);
		myCom->Ctl_Jogging(station,0);
	}
}

void MainWindow::errorget()
{
	ui.textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + " [errorGet]"+myCom->Get_LastErrorMsg()+"\n");
}

void MainWindow::sendmsg(QByteArray res)
{
	QByteArray temp =res;
	if(temp.size()==0)
		return ;
	QDataStream out(&temp,QIODevice::ReadWrite);    //将字节数组读入
	ui.textBrowser->insertPlainText(QDateTime::currentDateTime().toString("\nyyyy-MM-dd hh:mm:ss") + " [SEND] ");
	while(!out.atEnd())
	{
		qint8 outChar = 0;
		out>>outChar;   //每字节填充一次，直到结束
		//十六进制的转换
		QString str = QString("%1").arg(outChar&0xFF,2,16,QLatin1Char('0'));
		ui.textBrowser->insertPlainText(str.toUpper());//大写
		ui.textBrowser->insertPlainText(" ");//每发送两个字符后添加一个空格
		ui.textBrowser->moveCursor(QTextCursor::End);
	}
	ui.textBrowser->insertPlainText("\n");
}
