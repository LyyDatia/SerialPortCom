#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma execution_character_set("utf-8")

#include <QWidget>
#include<QDate>
#include "ui_mainwindow.h"
#include "win_qextserialport.h"
#include "serialportcom.h"


class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	SerialPortCom* myCom;

	QVector<SerialPortCom*>myComs;

private:
	Ui::MainWindow ui;

private slots:
	void ComReadyRead(SerialPortCom*);

	void ComConnect();
	void DisConnect();
	void WriteTest();
	void errorget();

	void sendmsg(QByteArray);
	void readMyCom();

};

#endif // MAINWINDOW_H
