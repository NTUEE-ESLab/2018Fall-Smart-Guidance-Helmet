#include "widget.h"
#include <iostream>
#include <unistd.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
                    //以1000毫秒為周期起動定時器
    char buf[80];
    getcwd(buf, sizeof(buf));
    const QString str(buf);
    figDir = str;
    setWindowTitle(tr("eyegaze"));
    //myTimer = new QTimer(this);
    QRect module(0,0,1920,1080);
    check=0;
    label= new QLabel(this);
    label->setGeometry(module);
    label2 = new QLabel(this);
    label2->setGeometry(module);
    label2->lower();
    QPixmap p(figDir.relativeFilePath("img/DSC_0662.JPG"));
    label2->setPixmap(p.scaled(1920,1080,Qt::KeepAspectRatioByExpanding));

    myTimer2 = new QTimer(this);
    myTimer2->start(200);
    LoadOriginalPicture();

    setdata();
    displayImage();
    connect(myTimer2,SIGNAL(timeout()),this,SLOT(displayImage()));
    connect(myTimer2,SIGNAL(timeout()),this,SLOT(setdata()));
}

void Widget::setdata(){
    QFile file(figDir.relativeFilePath("coordinate.txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line);
        decidedirection(str.split(" ")[0].toInt(),str.split(" ")[1].toInt(),str.split(" ")[2].toInt(),str.split(" ")[3].toInt());
    }

}
void Widget::displayImage()
{

    if(check==0 | direction==-1){
        direction=oriImage;
        if(check==0) check++;
    }
    QString picture;
    picture = picturenames.at(direction);
    qDebug()<<direction<<endl;
    QImage image(picture);
    label->setPixmap(QPixmap::fromImage(image).scaled(1920,1080,Qt::KeepAspectRatioByExpanding));


}

void Widget::decidedirection(int pupil_x, int pupil_y, int eye_x, int eye_y){
    int thresholdleft=240,thresholdright=300;
    int result = 0;
    if(pupil_x == -1) result=oriImage;
    else if(pupil_x < thresholdleft ) { result = left; }
    else if(pupil_x >= thresholdleft && pupil_x < thresholdright) result = middle;
    else if(pupil_x >= thresholdright) result = right;
    else result = 3;
    direction = result;
}

void Widget::LoadOriginalPicture(){

    picturenames.append(figDir.relativeFilePath("img/DSC_0662_left.jpg"));
    picturenames.append(figDir.relativeFilePath("img/DSC_0662_middle.jpg"));
    picturenames.append(figDir.relativeFilePath("img/DSC_0662_right.jpg"));
    picturenames.append(figDir.relativeFilePath("img/DSC_0662.JPG"));

}


void Widget::LoadPictures(){

}
