#include "Initialize.h"
#include "RungeKutta.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Modeling.h"
#include <QMessageBox>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DSN='';DBQ=.//database/engine.mdb");


    qDebug() << db.drivers();
    qDebug() << db.open();
    if(!db.open())
    {

        QMessageBox::critical(this, "Ошибка открытия Базы Данных", db.lastError().text());

    }

    model = new QSqlTableModel(this,db);
    model->setTable("engine");
    model->select();
    ui->tableView->setModel(model);



    ui->widget->setBackground(QColor(20, 20, 20));
    ui->widget->xAxis->setBasePen(QPen(QColor(64,224,208), 1));
    ui->widget->yAxis->setBasePen(QPen(QColor(64,224,208), 1));
    ui->widget->xAxis->setTickLabelColor(QColor(64,224,208));
    ui->widget->yAxis->setTickLabelColor(QColor(64,224,208));
    ui->widget->xAxis->setBasePen(QPen(QColor(64,224,208), 1));
    ui->widget->yAxis->setBasePen(QPen(QColor(64,224,208), 1));
    ui->widget->xAxis->setTickPen(QPen(QColor(64,224,208), 1));
    ui->widget->yAxis->setTickPen(QPen(QColor(64,224,208), 1));
    ui->widget->xAxis->setSubTickPen(QPen(QColor(64,224,208), 1));
    ui->widget->yAxis->setSubTickPen(QPen(QColor(64,224,208), 1));

    ui->widget_4->setBackground(QColor(20, 20, 20));
    ui->widget_4->xAxis->setBasePen(QPen(QColor(64,224,208), 1));
    ui->widget_4->yAxis->setBasePen(QPen(QColor(64,224,208), 1));
    ui->widget_4->xAxis->setTickLabelColor(QColor(64,224,208));
    ui->widget_4->yAxis->setTickLabelColor(QColor(64,224,208));
    ui->widget_4->xAxis->setBasePen(QPen(QColor(64,224,208), 1));
    ui->widget_4->yAxis->setBasePen(QPen(QColor(64,224,208), 1));
    ui->widget_4->xAxis->setTickPen(QPen(QColor(64,224,208), 1));
    ui->widget_4->yAxis->setTickPen(QPen(QColor(64,224,208), 1));
    ui->widget_4->xAxis->setSubTickPen(QPen(QColor(64,224,208), 1));
    ui->widget_4->yAxis->setSubTickPen(QPen(QColor(64,224,208), 1));





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

        Fly_Time=ui->lineEdit->text().toDouble()*86400;
        Start_Orbit_Height=ui->lineEdit_4->text().toDouble();
        Start_Orbit_Inclination=ui->lineEdit_6->text().toDouble()*M_PI/180;
        Finally_Orbit_Height=ui->lineEdit_5->text().toDouble();
        Finally_Orbit_Inclination=ui->lineEdit_7->text().toDouble()*M_PI/180;
        Start_SC_Mass=ui->lineEdit_2->text().toDouble();
        Realitive_Construct_Mass=ui->lineEdit_12->text().toDouble();
        SSS_Realitive_Mass=ui->lineEdit_11->text().toDouble();
        Gas_Flow_Speed=ui->lineEdit_8->text().toDouble();
        Engine_Specific_Mass=ui->lineEdit_9->text().toDouble();
        Electro_Specific_Mass=ui->lineEdit_10->text().toDouble();
        EFFICIENCY=ui->lineEdit_3->text().toDouble();




        if (ui->radioButton->isChecked())
    {

        SdelatPizdato();
    }



    QSqlQuery query;

        if (ui->radioButton_2->isChecked())
    {

            query.exec("SELECT * FROM engine WHERE Код = " + SelectedEngine);
            while (query.next())
            {
              name = query.value(1).toString();
              Engines_Thrust = query.value(2).toDouble() * 0.001;
              Gas_Flow_Speed = query.value(3).toDouble() * 1000.0;
              Engines_Power =  query.value(4).toDouble() * 1000.0;
              EFFICIENCY = query.value(5).toDouble() * 0.01;
            }

            SdelatZaebumba();
            ui->lineEdit_23->setText(name);



    }


    double MAXIMUM_PAYLOAD_MASS=0;

    if (ui->radioButton_3->isChecked())
{
        for (int i = 1; i<=18; i++)
        {
        query.exec("SELECT * FROM engine WHERE Код = " + QString::number(i));
        while (query.next())
        {
          name = query.value(1).toString();
          Engines_Thrust = query.value(2).toDouble() * 0.001;
          Gas_Flow_Speed = query.value(3).toDouble() * 1000.0;
          Engines_Power =  query.value(4).toDouble() * 1000.0;
          EFFICIENCY = query.value(5).toDouble() * 0.01;
        }

        SdelatZaebumba();
        if (Payload_Mass > MAXIMUM_PAYLOAD_MASS)
        {
            MAXIMUM_PAYLOAD_MASS = Payload_Mass;
            EngineNumber=i;
            ui->lineEdit_23->setText(name);
        }
        }


        query.exec("SELECT * FROM engine WHERE Код = " + QString::number(EngineNumber));
        while (query.next())
        {
          name = query.value(1).toString();
          Engines_Thrust = query.value(2).toDouble() * 0.001;
          Gas_Flow_Speed = query.value(3).toDouble() * 1000.0;
          Engines_Power =  query.value(4).toDouble() * 1000.0;
          EFFICIENCY = query.value(5).toDouble() * 0.01;
        }
        SdelatZaebumba();
        ui->lineEdit_23->setText(name);

}

        foo = (Gas_Mass)/(3*M_PI);
        Tank_Radius=100*round(pow(foo,1/3));
        Tank_CTR = round(Tank_Radius*1.5);
        Body_lenght=round(500*pow(Construct_Mass,1/3));
        SP_Square =0.5* Engines_Power/(1.3*0.29*0.866);
        Payload_R=round(sqrt(Payload_Mass/(0.02*1.5*M_PI)));
        EnginesCount=round(Engines_Thrust);
        ui->lineEdit_3->setText(QString::number(EFFICIENCY));
        ui->lineEdit_8->setText(QString::number(Gas_Flow_Speed));
        ui->lineEdit_18->setText(QString::number(Electro_Mass));
        ui->lineEdit_22->setText(QString::number(Payload_Mass));
        ui->lineEdit_21->setText(QString::number(SSS_Mass));
        ui->lineEdit_19->setText(QString::number(Engines_Mass));
        ui->lineEdit_20->setText(QString::number(Construct_Mass));
        ui->lineEdit_17->setText(QString::number(Engines_Power/1000));
        ui->lineEdit_16->setText(QString::number(Engines_Thrust/9.81));
        ui->lineEdit_15->setText(QString::number(Gas_Mass));
        ui->lineEdit_14->setText(QString::number(Delta_velocity/1000));
        ui->lineEdit_13->setText(QString::number(Initial_Speed/1000));





        RK_STEPS =Fly_Time/100;
        INITIAL_ACCELERATION = Engines_Thrust/Start_SC_Mass;
        ANGLE_U = 0;
        RADIUS = Start_Orbit_Radius;
        VELOCITY=0;
        INCLINATION=Start_Orbit_Inclination;
        TIME = 0;

        QVector <double> RADIUS_ARRAY(0);
        QVector <double> INCLINATION_ARRAY(0);
        QVector <double> TIME_ARRAY(0);




       Runge_Kutta(&TIME_ARRAY,&RADIUS_ARRAY,&INCLINATION_ARRAY);

        ui->widget->xAxis->setRange(0,Fly_Time/86000);
        ui->widget->yAxis->setRange(180*Start_Orbit_Inclination/M_PI,180*Finally_Orbit_Inclination/M_PI);
        ui->widget->addGraph();
        ui->widget->graph(0)->setPen(QPen(QColor(64,224,208), 2));
        ui->widget->graph(0)->addData(TIME_ARRAY,INCLINATION_ARRAY);
        ui->widget->replot();
        ui->widget_4->xAxis->setRange(0,Fly_Time/86000);
        ui->widget_4->yAxis->setRange(Start_Orbit_Radius/1000.0,MAX_R/1000.0);
        ui->widget_4->addGraph();
        ui->widget_4->graph(0)->setPen(QPen(QColor(64,224,208), 2));
        ui->widget_4->graph(0)->addData(TIME_ARRAY,RADIUS_ARRAY);
        ui->widget_4->replot();

        RADIUS_ARRAY.clear();
        INCLINATION_ARRAY.clear();
        TIME_ARRAY.clear();

        ui->label_31->setText("Зависимость наклонения орбиты (град) от времени (сут). Конечное наклонение: " + QString::number(180*INCLINATION/M_PI) + " град");
        ui->label_32->setText("Зависимость радиуса орбиты (км) от времени (сут). Конечный радиус: " + QString::number(RADIUS/1000)+ " км");

        ExcelExport();
        QMessageBox::about(this, "Excel Export", "Данные занесены в таблицу data.csv");
}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    SelectedEngine = ui->tableView->model()->data(index).toString();
    ui->lineEdit_23->setText(name);
}

