#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QRandomGenerator>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    firstScreen();
    connect(&timer,&QTimer::timeout,this,&MainWindow::slotTimerAlarm);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_NewGame_clicked(){

    saniye=0;
    dakika=0;

    timer.stop();
    timer.start(1000);

    int r=ui->comboBox->currentIndex();

    if(r==0){
        rc=4;
        randomToArray(rc);
    }
    if(r==1){
        rc=6;
        randomToArray(rc);
    }
    if(r==2){
        rc=8;
        randomToArray(rc);
    }
    setGameEmptyCells();
}

void MainWindow::firstScreen(){

    QTableWidget *table_widget = ui->tableWidget;
    table_widget->setColumnCount(1);
    table_widget->setRowCount(1);
    table_widget->setItem(0,0,(new QTableWidgetItem("SELECT DIFFICULTY !")));
    table_widget->item(0,0)->setForeground(QBrush(QColor(255, 255, 255)));
    table_widget->item(0,0)->setBackground(Qt::blue);
    table_widget->item(0,0)->setTextAlignment(Qt::AlignCenter);
    table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::randomToArray(int rc){

    int v= rc*rc/2;
    int freq[v];

    for(int m=0;m<v;m++)
        freq[m]=0;

    for ( int i = 0; i < rc ; i++ ){
        for ( int j =0 ; j < rc ; j++ ){
            int r;
            int k;
            do{
                r = rand() % v;
                k =r+1;
            }while ( freq[r] >= 2 );

            freq[r]++;
            arr[i][j] =QString::number(k);
        }
    }
}

void MainWindow::setGameEmptyCells(){

    QTableWidget *table_widget = ui->tableWidget;
    table_widget->setColumnCount(rc);
    table_widget->setRowCount(rc);

    for ( int i = 0; i < rc; i++ ){
        for ( int j = 0; j < rc; j++ ){
            table_widget->setItem(i,j,new QTableWidgetItem("?"));
            table_widget->item(i,j)->setTextAlignment(Qt::AlignCenter);
           //////////////////////
            qDebug()<<arr[i][j];
        }
    }
    table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::slotTimerAlarm()
{
    saniye ++;
    if (saniye == 60)
    {
        saniye =0;
        dakika++;
    }
    qDebug()<<saniye;

    ui->label_2->setText("TIME = "+QString::number(dakika)+":"+QString::number(saniye));
}

void MainWindow::pairingControl(int row, int column){

    counter++;
    QTableWidget *table_widget = ui->tableWidget;

    if(counter%2==1){

        firstBox=arr[row][column];
        rf=row;
        cf=column;

        table_widget->item(row,column)->setText((arr[row][column]));
        table_widget->item(row,column)->setTextAlignment(Qt::AlignCenter);
    }
    if(counter%2==0){

        secondBox=arr[row][column];
        rs=row;
        cs=column;

        table_widget->item(row,column)->setText((arr[row][column]));
        table_widget->item(row,column)->setTextAlignment(Qt::AlignCenter);

        if(firstBox==secondBox){
            if(rf==rs && cf==cs){
                return;
            }
            pair++;
            table_widget->setDisabled(true);
            ui->tableWidget->item(rf,cf)->setBackground(Qt::green);
            ui->tableWidget->item(rs,cs)->setBackground(Qt::green);
            table_widget->setEnabled(true);
        }
        if(!(firstBox==secondBox)){

            table_widget->setDisabled(true);

            QEventLoop loop;
            QTimer::singleShot(500, &loop, &QEventLoop::quit);
            loop.exec();

            table_widget->setItem(rf,cf,new QTableWidgetItem("?"));
            table_widget->item(rf,cf)->setTextAlignment(Qt::AlignCenter);
            table_widget->setItem(rs,cs,new QTableWidgetItem("?"));
            table_widget->item(rs,cs)->setTextAlignment(Qt::AlignCenter);

            table_widget->setEnabled(true);
        }
    }
    if(pair==(rc*rc/2)){

        timer.stop();
        QString labelTime= ui->label_2->text();
        ui->label->setText("LAST RECORD "+labelTime);

        lastScreen();
        pair=0;
    }
}

void MainWindow::lastScreen(){

    QTableWidget *table_widget = ui->tableWidget;
    table_widget->setColumnCount(1);
    table_widget->setRowCount(1);
    table_widget->setItem(0,0,(new QTableWidgetItem("WELLDONE !")));
    table_widget->item(0,0)->setForeground(QBrush(QColor(255, 255, 255)));
    table_widget->item(0,0)->setBackground(Qt::blue);
    table_widget->item(0,0)->setTextAlignment(Qt::AlignCenter);
    table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column){

    if(ui->tableWidget->item(row,column)->text()=="?"){
        pairingControl(row, column);
    }
}
