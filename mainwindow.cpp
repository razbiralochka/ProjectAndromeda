#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <math.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DSN='';DBQ=./engine.mdb");


    qDebug() << db.drivers();
    qDebug() << db.open();

    model = new QSqlTableModel(this,db);
    model->setTable("engine");
    model->select();
    ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}


void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::about(this, "О программе", "Самарский Университетет\n Кафедра космического машиностроения\n Разработчик: Хайруллин И.И.\n https://github.com/razbiralochka");
}


void MainWindow::on_pushButton_clicked()
{
    double const Gravitation_Param = 398600.44*1000000000;
    double Engine_Specific_Mass = 40;
    double SSS_Realitive_Mass = 0.07;
    double Realitive_Construct_Mass = 0.01;
    double Electro_Specific_Mass= 0.01;
    double Fly_Time=ui->lineEdit->text().toDouble()*86400;
    double Start_SC_Mass=ui->lineEdit_2->text().toDouble();
    double EFFICIENCY=ui->lineEdit_3->text().toDouble();
    double Gas_Flow_Speed=ui->lineEdit_4->text().toDouble();
    double Start_Orbit_Radius=ui->lineEdit_5->text().toDouble();
    double Finally_Orbit_Radius=ui->lineEdit_6->text().toDouble();
    double Start_Orbit_Inclination=ui->lineEdit_7->text().toDouble() * M_PI/180;
    double Finally_Orbit_Inclination=ui->lineEdit_8->text().toDouble()* M_PI/180;




    double Initial_Speed = sqrt(Gravitation_Param/Start_Orbit_Radius);
    double Delta_velocity = Initial_Speed*sqrt(1-2*sqrt(Start_Orbit_Radius/Finally_Orbit_Radius)*cos((M_PI/2)*(Finally_Orbit_Inclination-Start_Orbit_Inclination))+(Start_Orbit_Radius/Finally_Orbit_Radius));
    double Gas_Mass = Start_SC_Mass*(1-exp((-Delta_velocity)/Gas_Flow_Speed));
    double Engines_Thrust = (Gas_Flow_Speed*Gas_Mass)/(Fly_Time);
    double Engines_Power = (Engines_Thrust*Gas_Flow_Speed)/(2*EFFICIENCY);
    double Engines_Mass = Engine_Specific_Mass * Engines_Thrust;
    double Electro_Mass = Electro_Specific_Mass * Engines_Power;
    double Construct_Mass = Realitive_Construct_Mass * Start_SC_Mass;
    double SSS_Mass = SSS_Realitive_Mass * Gas_Mass;
    double Payload_Mass =Start_SC_Mass - Gas_Mass - Construct_Mass - SSS_Mass - Engines_Mass - Electro_Mass;
    ui->lineEdit_11->setText(QString::number(Delta_velocity));
    ui->lineEdit_12->setText(QString::number(Gas_Mass));
    ui->lineEdit_13->setText(QString::number(Engines_Thrust));
    ui->lineEdit_14->setText(QString::number(Engines_Power));
    ui->lineEdit_15->setText(QString::number(Electro_Mass));
    ui->lineEdit_16->setText(QString::number(Engines_Mass));
    ui->lineEdit_17->setText(QString::number(Construct_Mass));
    ui->lineEdit_18->setText(QString::number(SSS_Mass));
    ui->lineEdit_19->setText(QString::number(Payload_Mass));
}

