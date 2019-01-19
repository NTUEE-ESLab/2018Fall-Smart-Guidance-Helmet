#ifndef WIDGET_H
#define WIDGET_H

#include <QTimer>
#include <QTime>
#include <QLCDNumber>
#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QThread>
#include <QDir>
#include <QString>

#define left 0
#define middle 1
#define right 2
#define oriImage 3

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    void decidedirection(int pupil_x,int pupil_y,int eye_x,int eye_y);
    void LoadPictures();
    void LoadOriginalPicture();

private:
    QDir figDir;
    QTimer *myTimer,*myTimer2;
    QLCDNumber *myLCDNumber;
    QLabel *label,*label2;
    QStringList picturenames ;
    bool temp=false;

    int check;
    int direction;


private slots:
    void displayImage();  //顯示時間的函式
    void setdata();
};

#endif // WIDGET_H
