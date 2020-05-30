#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <graphwidget.h>
#include <QtMath>
#include <QFileDialog>
#include "node.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    test = new GraphWidget();
    setPos();
    setRestrictions();

    ui->gridLayout_2->addWidget(test);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete test;
}

void MainWindow::setPos()
{
    // a
    test->nodeSetPos(0, ui -> lineEdit->text().toFloat(), ui->lineEdit_2->text().toFloat());
    // b
    test->nodeSetPos(1, ui -> lineEdit_3->text().toFloat(), ui->lineEdit_4->text().toFloat());
    //c
    test->nodeSetPos(2, ui -> lineEdit_5->text().toFloat(), ui->lineEdit_6->text().toFloat());
    //d
    test->nodeSetPos(3, ui -> lineEdit_7->text().toFloat(), ui->lineEdit_8->text().toFloat());
    //e
    test->nodeSetPos(4, ui -> lineEdit_9->text().toFloat(), ui->lineEdit_10->text().toFloat());

    auto nodes = test->getNodes();
    nodes[0]->textX->setText(QString::number((int)ui->lineEdit->text().toFloat()));
    nodes[0]->textY->setText(QString::number((int)ui->lineEdit_2->text().toFloat()));
    ui->gridLayout->addWidget(nodes[0]->textX,2,1);
    ui->gridLayout->addWidget(nodes[0]->textY,2,2);



    nodes[1]->textX->setText(QString::number((int)ui->lineEdit_3->text().toFloat()));
    nodes[1]->textY->setText(QString::number((int)ui->lineEdit_4->text().toFloat()));
    ui->gridLayout->addWidget(nodes[1]->textX,4,1);
    ui->gridLayout->addWidget(nodes[1]->textY,4,2);


    nodes[2]->textX->setText(QString::number((int)ui->lineEdit_5->text().toFloat()));
    nodes[2]->textY->setText(QString::number((int)ui->lineEdit_6->text().toFloat()));
    ui->gridLayout->addWidget(nodes[2]->textX,5,1);
    ui->gridLayout->addWidget(nodes[2]->textY,5,2);



    nodes[3]->textX->setText(QString::number((int)ui->lineEdit_7->text().toFloat()));
    nodes[3]->textY->setText(QString::number((int)ui->lineEdit_8->text().toFloat()));
    ui->gridLayout->addWidget(nodes[3]->textX,6,1);
    ui->gridLayout->addWidget(nodes[3]->textY,6,2);

    nodes[4]->textX->setText(QString::number((int)ui->lineEdit_9->text().toFloat()));
    nodes[4]->textY->setText(QString::number((int)ui->lineEdit_10->text().toFloat()));
    ui->gridLayout->addWidget(nodes[4]->textX,7,1);
    ui->gridLayout->addWidget(nodes[4]->textY,7,2);

}
void MainWindow::setRestrictions()
{
    int maxLength;
    int minLength;
    if(ui -> lineEdit_12->text() !=""){
        maxLength = ui -> lineEdit_12->text().toFloat();
    }
    else{
        maxLength = -1;
    }
    if(ui -> lineEdit_11->text() !=""){
        minLength = ui -> lineEdit_11->text().toFloat();
    }
    else{
        minLength = -1;
    }
    qreal angelFrom = -1;
    qreal angelTo = -1;
    QRegExp rx("(\\:)");
    if(!ui->lineEdit_13->text().isEmpty()){
        QStringList query = ui->lineEdit_13->text().split(rx);

        if(!query[0].isEmpty()){
             angelFrom = query[0].toFloat();
        }
        if(!query[1].isEmpty()){
            angelTo = query[1].toFloat();
        }
    }

    test->setRestrictions(maxLength,minLength,angelFrom,angelTo);
}

double MainWindow::angle_point (QPoint *a, QPoint *b, QPoint *c)
{
    double x1 = a->x() - b->y();
    double x2 = c->x() - b->x();
    double y1 = a->y() - b->y(), y2 = c->y() - b->y();
    double d1 = sqrt (x1 * x1 + y1 * y1);
    double d2 = sqrt (x2 * x2 + y2 * y2);
    return acos ((x1 * x2 + y1 * y2) / (d1 * d2));
}

void MainWindow::on_pushButton_2_clicked()
{
   test->saveToJson();
    }


void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open widget params"), "",
                                                    tr("Widget params (*.json);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QList<NodeParams> nodes = test->readFromJson(fileName);
        // a
        test->nodeSetPos(0, nodes[0].x, nodes[0].y);
        // b
        test->nodeSetPos(1, nodes[1].x, nodes[1].y);
        //c
        test->nodeSetPos(2, nodes[2].x, nodes[2].y);
        //d
        test->nodeSetPos(3, nodes[3].x, nodes[3].y);
        //e
        test->nodeSetPos(4, nodes[4].x, nodes[4].y);
    }
}

void MainWindow::on_pushButton_clicked()
{
     auto nodes = test->getNodes();

    float x1 = nodes[0]->textX -> text().toFloat();
    float y1 = nodes[0]->textY -> text().toFloat();
    float x2 =  nodes[1]->textX -> text().toFloat();
    float y2 = nodes[1]->textY -> text().toFloat();
    float x3 = nodes[2]->textX -> text().toFloat();
    float y3 = nodes[2]->textY -> text().toFloat();
    float x4 = nodes[3]->textX -> text().toFloat();
    float y4 = nodes[3]->textY -> text().toFloat();
    float x5 = nodes[4]->textX -> text().toFloat();
    float y5 = nodes[4]->textY-> text().toFloat();

    if(ui -> lineEdit_11 -> text() != "" || ui -> lineEdit_12 -> text() != ""){
        float min = ui -> lineEdit_11 -> text().toFloat()+qreal(20.);
        float max = ui -> lineEdit_12 -> text().toFloat()+qreal(20.);
        double coner = ui -> lineEdit_13 -> text().toFloat();
        QRegExp rx("(\\:)");
        QStringList query ;
        if(! ui->lineEdit_13->text().isEmpty()){
            query = ui->lineEdit_13->text().split(rx);
        }
        QLineF line1(x1,y1, x2,y2);
        QLineF line2(x2,y2, x3,y3);
        QLineF line3(x3,y3, x4,y4);
        QLineF line4(x4,y4, x5,y5);

        if((line1.length()<=max && line2.length() <=max && line3.length() <= max && line4.length() <=max)
              && (line1.length() >= min && line2.length() >= min && line3.length() >= min && line4.length() >= min) )
        {

        }
        else
        {
            QMessageBox :: information (this,"ошибка","длина отрезка не соответствует ограничениям" );
            return;
        }

        if(!(query[0].isEmpty() && query[1].isEmpty())){
            auto anglePoint = angle_point(new QPoint(x1,y1), new QPoint(x2,y2), new QPoint(x3,y3));
            if (anglePoint >= query[0].toFloat() && anglePoint <=query[1].toFloat() )
            {

            }
            else
            {
                QMessageBox :: information (this,"ошибка","длина отрезка не соответствует ограничениям" );
                return;
            }

        }
        auto nodes = test->getNodes();
        // a
        test->nodeSetPos(0, nodes[0]->textX->text().toFloat(),nodes[0]->textY->text().toFloat());
        // b
        test->nodeSetPos(1, nodes[1]->textX->text().toFloat(),nodes[1]->textY->text().toFloat());
        //c
        test->nodeSetPos(2, nodes[2]->textX->text().toFloat(),nodes[2]->textY->text().toFloat());
        //d
        test->nodeSetPos(3, nodes[3]->textX->text().toFloat(),nodes[3]->textY->text().toFloat());
        //e
        test->nodeSetPos(4, nodes[4]->textX->text().toFloat(),nodes[4]->textY->text().toFloat());

        setRestrictions();
    }
}


