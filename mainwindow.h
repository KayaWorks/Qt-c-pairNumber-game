#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qtimer.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int saniye = 0;
    int dakika = 0;

    int counter=0;// Counter for 2 Selected Cell
    int rc=0;     //Row and Column number
    int rf=0;     //First Selected Row
    int cf=0;     //First Selected Column
    int rs=0;     //Second Selected Row
    int cs=0;     //Second Selected Column
    int pair=0;   //Counter for pairs

    QString arr[8][8];
    QString firstBox;
    QString secondBox;
    QTimer timer;

    void firstScreen();
    void lastScreen();

    void randomToArray(int);
    void setGameEmptyCells();
    void pairingControl(int row, int column);

    void slotTimerAlarm();

private slots:

    void on_pushButton_NewGame_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
