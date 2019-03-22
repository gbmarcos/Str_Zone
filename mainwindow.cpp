#include "mainwindow.h"
#include "colordetector.h"
#include "colordetectcontroller.h"
#include "ui_mainwindow.h"
#include "histog1d.h"
#include "buscadcont.h"
#include "morphofeatures.h"
#include "laplacianzc.h"
#include <QFileDialog>
#include <QColorDialog>
#include "imagecomparator.h"
#include "segmentadorws.h"
#include "buscalinea.h"
#include "vibe.h"
#include <QMessageBox>
using namespace cv;
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cantpix->setValidator(new QIntValidator(this));
    ui->Tx->setValidator(new QIntValidator(this));
    ui->Ty->setValidator(new QIntValidator(this));
    ui->Px->setValidator(new QIntValidator(this));
    ui->Py->setValidator(new QIntValidator(this));
    ui->Tx_2->setValidator(new QIntValidator(this));
    ui->Ty_2->setValidator(new QIntValidator(this));
    ui->Px_2->setValidator(new QIntValidator(this));
    ui->Py_2->setValidator(new QIntValidator(this));
    ui->comp->setValidator(new QDoubleValidator(this));
    ui->Tx_3->setValidator(new QIntValidator(this));
    ui->Ty_3->setValidator(new QIntValidator(this));
    ui->Px_3->setValidator(new QIntValidator(this));
    ui->Py_3->setValidator(new QIntValidator(this));

    ui->Px->setText("850");
    ui->Py->setText("250");
    ui->Tx->setText("20");
    ui->Ty->setText("20");


    colorRuido=QColor(255,255,255);
    QString colorName = QString("background : %1").arg(colorRuido.name());
    ui->pushButton_4->setStyleSheet(colorName);
    path="C:/Users/Markux/Desktop/my things/!!!!!!!!!Tesis/Para tesis";
    control=new ColorDetectController();

    colorBI=QColor(255,255,255);
    QString colorName1 = QString("background : %1").arg(colorBI.name());
    ui->pushButton_6->setStyleSheet(colorName1);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_2_clicked()
{

    colorRuido=QColor(255,255,255);
    QString colorName = QString("background : %1").arg(colorRuido.name());
    ui->pushButton_4->setStyleSheet(colorName);

    colorBI=QColor(255,255,255);
    QString colorName1 = QString("background : %1").arg(colorBI.name());
    ui->pushButton_6->setStyleSheet(colorName1);

    Reduc_factor=2;

    imagefileName = QFileDialog::getOpenFileName(this, tr("Open Image"),path , tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));

    if(!imagefileName.isEmpty())
    {
        image= cv::imread(imagefileName.toLatin1().data());
        path=imagefileName;
        QStringList lis=path.split('/');
        lis.removeLast();
        path= lis.join("/");
    }


    if(!image.empty()){
        control->setInputImage(imagefileName.toLatin1().data());
        cv::namedWindow("Image");
        cv::imshow("Image", image);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una imagen");
        msg.exec();

    }

    else{
        if(ui->hor->isChecked()&&ui->ver->isChecked()){
            cv::flip(image,image,-1);
            cv::namedWindow("Image");
            cv::imshow("Image", image);
            msg.setText("La imagen ha sido volteada correctamente de forma horizontal y vertical");
            msg.exec();
        }
        else if (ui->hor->isChecked()){
            cv::flip(image,image,0);
            cv::namedWindow("Image");
            cv::imshow("Image", image);
            msg.setText("La imagen ha sido volteada correctamente de forma horizontal");
            msg.exec();
        }
        else if (ui->ver->isChecked()){
            cv::flip(image,image,1);
            cv::namedWindow("Image");
            cv::imshow("Image", image);
            msg.setText("La imagen ha sido volteada correctamente de forma vertical");
            msg.exec();
        }
        else {

            msg.setText("Al menos una de las formas de voltear debe ser escogida");
            msg.exec();
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{

    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas tener una imagen para guardar")    ;
        msg.exec();
    }else{
        QString archsav=  QFileDialog::getSaveFileName(this, tr("Save File"),
                                                       ".",
                                                       tr("Images (*.png *.xpm *.jpg)"));
        if(!archsav.isEmpty()){
            cv::imwrite(archsav.toLatin1().data(),image);
        }
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    colorRuido=QColor(255,255,255);
    QString colorName = QString("background : %1").arg(colorRuido.name());
    ui->pushButton_4->setStyleSheet(colorName);

    colorBI=QColor(255,255,255);
    QString colorName1 = QString("background : %1").arg(colorBI.name());
    ui->pushButton_6->setStyleSheet(colorName1);
    cv::Mat mm;
    Im=mm.clone();
    Reduc_factor=2;
    if(!imagefileName.isEmpty()){
        image=cv::imread(imagefileName.toLatin1().data());
        cv::namedWindow("Image");
        cv::imshow("Image", image);
        QMessageBox msg;
        msg.setText("Las propiedades de la image han sido restablecidas");
        msg.exec();
    }
}

void MainWindow::on_ruidoo_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();

    }else if(ui->cantpix->text().isEmpty()){
        msg.setText("Debe seleccionar la cantidad de pixeles a modificar");
        msg.exec();

    }else if(ui->cantpix->text().toInt()>image.cols*image.rows){
        msg.setText("La cantidad de pixeles seleccionados es mayor que la de los pixeles que conforman la imagen");
        msg.exec();

    }else {
        salt(image,ui->cantpix->text().toInt());
        cv::namedWindow("Image");
        cv::imshow("Image", image);
    }
}
void MainWindow::salt(cv::Mat img,int n) {
    for (int k=0; k<n; k++) {

        int i= qrand()%img.cols;
        int j= qrand()%img.rows;

        if (img.channels() == 1) { // gray-level image
            img.at<uchar>(j,i)= colorRuido.red();
        } else if (img.channels() == 3) { // color image
            img.at<cv::Vec3b>(j,i)[0]= colorRuido.blue();
            img.at<cv::Vec3b>(j,i)[1]=colorRuido.green();
            img.at<cv::Vec3b>(j,i)[2]=colorRuido.red();

        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    colorRuido=QColorDialog::getColor();
    QString colorName = QString("background : %1").arg(colorRuido.name());
    ui->pushButton_4->setStyleSheet(colorName);
}

void MainWindow::on_pushButton_8_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();
    }else{
        image=variarcolor(64,image);
        cv::namedWindow("Image");
        cv::imshow("Image",image);

    }
}
cv::Mat MainWindow::variarcolor(int divv, cv::Mat ima)
{
    int div=divv;
    int nl= ima.rows;
    int nc= ima.cols * ima.channels();

    for (int j=0; j<nl; j++) {

        uchar* data= ima.ptr<uchar>(j);
        for (int i=0; i<nc; i++) {

            data[i] = data[i]/div*div+div/2;
        }
    }
    Reduc_factor=Reduc_factor+2;

    return ima;
}




void MainWindow::on_pushButton_9_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();
    }else{
        Saturar();
        image=result.clone();
        cv::namedWindow("Image");
        cv::imshow("Image",image);
        msg.setText("La imagen ha sido Saturada")    ;
        msg.exec();

    }

}
void MainWindow::Saturar(){
    // allocate if necessary
    result.create(image.size(), image.type());
    for (int j= 1; j<image.rows-1; j++) {

        const uchar* previous= image.ptr<const uchar>(j-1);
        const uchar* current=  image.ptr<const uchar>(j);
        const uchar* next= image.ptr<const uchar>(j+1);


        uchar* output= result.ptr<uchar>(j);

        for (int i=1; i<image.cols*image.channels()-1; i++) {
            *output++= cv::saturate_cast<uchar>(5*current[i]-current[i-1]-current[i+1]-previous[i]-next[i]);
        }
    }

    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols-1).setTo(cv::Scalar(0));


}

void MainWindow::on_pushButton_24_clicked()
{
    QString fileName_2 = QFileDialog::getOpenFileName(this,
                                                      tr("Open Image"), ".",
                                                      tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    auxiliar= cv::imread(fileName_2.toLatin1().data());
}

void MainWindow::on_pushButton_11_clicked()
{

    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();
    }else if(auxiliar.empty()){
        msg.setText("Necesitas Cargar un Logo")    ;
        msg.exec();

    }else{
        int c,r;

        if(ui->r1->isChecked()||ui->r3->isChecked())c=auxiliar.cols;
        else c=image.cols;

        if(ui->r1->isChecked()||ui->r2->isChecked())r=auxiliar.rows;
        else r=image.rows;

        Superponer(c,r);

        cv::namedWindow("Image");
        cv::imshow("Image",image);}

}
void MainWindow::Superponer(int c, int r){

    // define image ROI
    cv::Mat imageROI;
    imageROI= image(cv::Rect(c-auxiliar.cols,r-auxiliar.rows,auxiliar.cols,auxiliar.rows));
    // add logo to image
    cv::addWeighted(imageROI,1.0,auxiliar,0.3,0.,imageROI);

}

void MainWindow::on_pushButton_12_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();
    }else{
        detec_color();
        image=control->getLastResult();
        cv::namedWindow("Image");
        cv::imshow("Image",image);
        msg.setText("Las porciones de imagen mostradas en blanco representan el color detectado")    ;
        msg.exec();
    }



}


void MainWindow::detec_color(){


    control->setColorDistanceThreshold(ui->verticalSlider->value());


    control->process();


}

void MainWindow::on_pushButton_6_clicked()
{
    colorBI=QColorDialog::getColor() ;
    if(colorBI.isValid()){
        QString colorName = QString("background : %1").arg(colorBI.name());
        ui->pushButton_6->setStyleSheet(colorName);

        control->setTargetColor(colorBI.red(),colorBI.green(),colorBI.blue());
    }
}

void MainWindow::on_pushButton_10_clicked()
{

    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();
    }else{
        cv::cvtColor(image,result,ui->spinBox_5->value());
        image=result.clone();
        cv::namedWindow("Image");
        cv::imshow("Image",image);
        msg.setText("La imagen ha sido cambiada a escala de gris")    ;
        msg.exec();
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else{
        Histog1D a;

        cv::namedWindow("Histogram");

        cv::imshow("Histogram",a.getHistogramImage(image));

    }

}

void MainWindow::on_pushButton_7_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else{
        QString archsav=  QFileDialog::getSaveFileName(this, tr("Save File"),
                                                       ".",
                                                       tr("Images (*.png *.xpm *.jpg)"));
        if(!archsav.isEmpty()){
            Histog1D a;

            cv::imwrite(archsav.toLatin1().data(),a.getHistogramImage(image));
        }
    }


}

void MainWindow::on_pushButton_14_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else{

        cv::threshold(image,image,ui->Umb->value(),255,cv::THRESH_BINARY);

        cv::namedWindow("Umbral");

        cv::imshow("Umbral",image);

    }

}

void MainWindow::on_pushButton_15_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else{

        int dim(256);
        cv::Mat lut(1, &dim, CV_8U);

        for (int i=0; i<256; i++) {
            lut.at<uchar>(i)= 255-i;
        }
        Histog1D a;

        image=a.applyLookUp(cv::imread(imagefileName.toLatin1().data()),lut);


        cv::namedWindow("Umbral");

        cv::imshow("Umbral",image);

    }
}

void MainWindow::on_pushButton_16_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else{
        Histog1D a;
        image=a.stretch(image,0);

        cv::namedWindow("Contraste expandido");

        cv::imshow("Contraste Expandido",image);

    }
}

void MainWindow::on_pushButton_17_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else{
        Histog1D a;
        image=a.equalize(image);

        cv::namedWindow("Imagen Ecualizada");

        cv::imshow("Imagen Ecualizada",image);

    }
}

void MainWindow::on_pushButton_18_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else if(ui->Tx->text().isEmpty()||ui->Ty->text().isEmpty()||ui->Px->text().isEmpty()||ui->Py->text().isEmpty()){
        msg.setText("Debes llenar todos los campos")    ;
        msg.exec();

    }else if((ui->Px->text().toInt()+ui->Tx->text().toInt()>image.cols)||(ui->Py->text().toInt()+ui->Ty->text().toInt()>image.rows)){
        msg.setText("El área seleccionada se sale de la imagen")    ;
        msg.exec();
    }else{
        Histog1D a;

       // image=variarcolor(32,image);
        cv::Mat imageROI;
        imageROI= image(cv::Rect(ui->Px->text().toInt(),ui->Py->text().toInt(),ui->Tx->text().toInt(),ui->Ty->text().toInt()));

        cv::MatND histogramRIO=a.getHistogram(imageROI);

        float Minv=0;
        float Maxv=255;

        BuscadCont b;
        b.setHistogram(histogramRIO);
        b.setThreshold(0.05f);

        image= b.find(image,Minv,Maxv,image.channels());

        cv::namedWindow("Mapa de probabilicades");

        cv::imshow("Mapa de probabilicades",image);

    }
}

void MainWindow::on_pushButton_19_clicked()
{
    Prevsualizar(ui->Px->text(),ui->Py->text(),ui->Tx->text(),ui->Ty->text());
}

void MainWindow::on_pushButton_20_clicked()
{
    Prevsualizar(ui->Px_2->text(),ui->Py_2->text(),ui->Tx_2->text(),ui->Ty_2->text());
}

void MainWindow::Prevsualizar(QString px,QString py,QString tx,QString ty){
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else if(px.isEmpty()||
             py.isEmpty()||
             tx.isEmpty()||
             ty.isEmpty()){
        msg.setText("Debes llenar todos los campos")    ;
        msg.exec();

    }else if((px.toInt()+tx.toInt()>image.cols)||
             (py.toInt()+ty.toInt()>image.rows)){
        msg.setText("El área seleccionada se sale de la imagen")    ;
        msg.exec();
    }else{
        cv::Mat pre=cv::imread(imagefileName.toLatin1().data());




        cv::Rect rect (px.toInt(),
                       py.toInt(),
                       tx.toInt(),
                       ty.toInt());
        cv::rectangle(pre, rect, cv::Scalar(0,0,255));

        cv::namedWindow("Previsualizacion");

        cv::imshow("Previsualizacion",pre);

    }

}

void MainWindow::on_pushButton_21_clicked()
{
    QString newfln;



    newfln = QFileDialog::getOpenFileName(this,
                                          tr("Open Image"), path,
                                          tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    Im= cv::imread(newfln.toLatin1().data());
    if(!Im.empty()){

        cv::namedWindow("Image2");
        cv::imshow("Image2", Im);
    }

}

void MainWindow::on_pushButton_22_clicked()
{

    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else if(Im.empty()){
        msg.setText("Necesitas Cargar otra Imagen")    ;
        msg.exec();

    }else if(ui->Tx_2->text().isEmpty()||ui->Ty_2->text().isEmpty()||
             ui->Px_2->text().isEmpty()||ui->Py_2->text().isEmpty()){
        msg.setText("Debes llenar todos los campos")    ;
        msg.exec();

    }else if((ui->Px_2->text().toInt()+ui->Tx_2->text().toInt()>Im.cols)||
             (ui->Py_2->text().toInt()+ui->Ty_2->text().toInt()>Im.rows)){
        msg.setText("El área seleccionada se sale de la imagen")    ;
        msg.exec();
    }else{


        cv::Mat imageROI= image(cv::Rect(ui->Px_2->text().toInt(),
                                         ui->Py_2->text().toInt(),
                                         ui->Tx_2->text().toInt(),
                                         ui->Ty_2->text().toInt()));
        int minSat=65;

        Histog1D hc;

        cv::MatND colorhist= hc.getHueHistogram(imageROI,minSat);

        BuscadCont buscador;
        buscador.setHistogram(colorhist);

        cv::Mat hsv;
        cv::cvtColor(Im, hsv, CV_BGR2HSV);
        cv::Mat v[5];
        cv::split(hsv,v);

        cv::threshold(v[1],v[1],minSat,255,cv::THRESH_BINARY);

        cv::Mat rslt;
        rslt= buscador.find(hsv,0.0f,180.0f,1);
        cv::bitwise_and(rslt,v[1],rslt);

        cv::Rect rect(ui->Px_2->text().toInt(),
                      ui->Py_2->text().toInt(),
                      ui->Tx_2->text().toInt(),
                      ui->Ty_2->text().toInt());
        cv::rectangle(Im, rect, cv::Scalar(0,0,255));

        cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER,
                                  10,0.01);
        cv::meanShift(rslt,rect,criteria);


        cv::rectangle(Im, rect, cv::Scalar(0,255,0));

        cv::namedWindow("Image2");
        cv::imshow("Image2", Im);


    }





}

void MainWindow::on_pushButton_23_clicked()
{
    on_pushButton_21_clicked();
}

void MainWindow::on_pushButton_25_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else if(Im.empty()){
        msg.setText("Necesitas Cargar la Imagen a comparar")    ;
        msg.exec();

    }else{
        ImageComparator c;
        cv::Mat refer=variarcolor(c.getColorReduction(),image);

        c.setReferenceImage(refer);

        cv::Mat imCo=variarcolor(c.getColorReduction(),Im);

        double res=c.compare(imCo);
        QString x=QString::number(res);

        ui->comp->setText(x);

    }
}

void MainWindow::on_pushButton_27_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();
    }else{
        cv::erode(image,image,cv::Mat());
        cv::namedWindow("Imagen Erosionada");
        cv::imshow("Imagen Erosionada", image);
    }
}

void MainWindow::on_pushButton_26_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();
    }else{
        cv::dilate(image,image,cv::Mat());
        cv::namedWindow("Imagen Dilatada");
        cv::imshow("Imagen Dilatada", image);
    }
}

void MainWindow::on_pushButton_29_clicked()
{
    if(image.empty()){
        QMessageBox msg;
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();
    }else{

        cv::Mat elx(ui->spinBox_1->text().toInt(),ui->spinBox_2->text().toInt(),CV_8U,cv::Scalar(1));
        cv::morphologyEx(image,image,cv::MORPH_CLOSE,elx);
        cv::namedWindow("Imagen Abierta");
        cv::imshow("Imagen Abierta", image);
    }
}

void MainWindow::on_pushButton_28_clicked()
{
    if(image.empty()){
        QMessageBox msg;
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();
    }else{
        cv::Mat elx(ui->spinBox_1->text().toInt(),ui->spinBox_2->text().toInt(),CV_8U,cv::Scalar(1));
        cv::morphologyEx(image,image,cv::MORPH_OPEN,elx);
        cv::namedWindow("Imagen Cerrada");
        cv::imshow("Imagen Cerrada", image);
    }
}

void MainWindow::on_pushButton_33_clicked()
{
    if(image.empty()){
        QMessageBox msg;
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();
    }else{
        MorphoFeatures morpho;
        morpho.setThreshold(ui->barra_det_bor->value());

        image= morpho.getEdges(image);
        cv::namedWindow("Detección de Bordes");
        cv::imshow("Detección de Bordes", image);
    }
}

void MainWindow::on_pushButton_32_clicked()
{
    if(image.empty()){
        QMessageBox msg;
        msg.setText("Necesitas Cargar una imagen")    ;
        msg.exec();
    }else{
        MorphoFeatures morpho;
         morpho.setThreshold(ui->barra_det_bor->value());
        cv::Mat corners;
        corners= morpho.getCorners(image);
        morpho.drawOnImage(corners,image);
        cv::namedWindow("Esquinas de la imagen");
        cv::imshow("Esquinas de la imagen",image);
    }


}




void MainWindow::on_pushButton_31_clicked()
{
   Prevsualizar(ui->Px_3->text(),ui->Py_3->text(),ui->Tx_3->text(),ui->Ty_3->text());
}

void MainWindow::on_pushButton_34_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else if(ui->Tx_3->text().isEmpty()||ui->Ty_3->text().isEmpty()||ui->Px_3->text().isEmpty()||ui->Py_3->text().isEmpty()){
        msg.setText("Debes llenar todos los campos")    ;
        msg.exec();

    }else if((ui->Px_3->text().toInt()+ui->Tx_3->text().toInt()>image.cols)||(ui->Py_3->text().toInt()+ui->Ty_3->text().toInt()>image.rows)){
        msg.setText("El área seleccionada se sale de la imagen")    ;
        msg.exec();
    }else{
        cv::Rect rectangle(ui->Px_3->text().toInt(),
                           ui->Py_3->text().toInt(),
                           ui->Tx_3->text().toInt(),
                           ui->Ty_3->text().toInt());


       image=extraerForeground(rectangle);


        cv::namedWindow("Extración");
        cv::imshow("Extración",image);

    }
}

cv::Mat MainWindow::extraerForeground(cv::Rect rectangle)
{
    cv::Mat result;
    cv::Mat bgModel,fgModel;

    cv::grabCut(image, result, rectangle, bgModel, fgModel, 5, cv::GC_INIT_WITH_RECT);

    cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);

    cv::Mat foreground(image.size(),CV_8UC3, cv::Scalar(255,255,255));
    image.copyTo(foreground, result);
    return foreground;
}

void MainWindow::on_pushButton_35_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else {
        int size=ui->horizontalSlider->value();
       cv::blur(image,image,cv::Size(size,size));
       cv::namedWindow("Filtro de paso bajo");
       cv::imshow("Filtro de paso bajo",image);

    }
}

void MainWindow::on_pushButton_36_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else {
       cv::medianBlur(image,image,5);
       cv::namedWindow("Filtro de paso medio");
       cv::imshow("Filtro de paso medio",image);

    }
}

void MainWindow::on_pushButton_37_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else {
      int a=1;
      int b=0;
      if(ui->radioButton_2->isChecked()){
      a=0;
      b=1;
      }
      cv::Sobel(image,image,CV_8U,a,b,3,0.4,128);
       cv::namedWindow("Bordes");
       cv::imshow("Bordes",image);

    }
}

void MainWindow::on_pushButton_38_clicked()
{
     QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
    }else {
        LaplacianZC gen_lap;
         gen_lap.setAperture(ui->comboBox->currentText().toInt());
         cv::Mat flap= gen_lap.computeLaplacian(image);
         image= gen_lap.getLaplacianImage();
         cv::namedWindow("Imagen Laplaciana");
         cv::imshow("Imagen Laplaciana",image);
    }
}



void MainWindow::on_pushButton_39_clicked()
{
    QMessageBox msg;
   if(image.empty()){
       msg.setText("Necesitas Cargar una Imagen")    ;
       msg.exec();
   }else {

       for (int i = 0;i<4;i++){

           cv::medianBlur(image,image,5);
       }
       cv::Canny(image, image, 120,80);
       cv::threshold(image,image, 128, 255, cv::THRESH_BINARY_INV);
       deslin(image);
       cv::namedWindow("Resultado");
       cv::imshow("Resultado",image);
   }
}

void MainWindow::deslin(cv::Mat img)
{
    cv::Mat aux=img;
    for(int i=2;i<img.rows-1;i++)
    {
        for(int j=2;j<img.cols-1;j++)
        {
            int current=aux.at<uchar>(i,j);

           int nextN=aux.at<uchar>(i,j+2);

           int arr=img.at<uchar>(i-1,j);
           int aba=img.at<uchar>(i+1,j);

           if(current==0&&nextN==0)  img.at<uchar>(i,j+2)=255;
           if(arr==255&&aba==255)img.at<uchar>(i,j)=255;
        }
    }
}

void MainWindow::on_pushButton_40_clicked()
{
    QMessageBox msg;
   if(image.empty()){
       msg.setText("Necesitas Cargar una Imagen")    ;
       msg.exec();
   }else {
BuscaLinea finder;
cv::Mat aux;
finder.setLineLengthAndGap(100,20);
 finder.setMinVote(80);
 cv::Canny(image,aux,125,350);
 std::vector<cv::Vec4i> lines= finder.findLines(aux);
 finder.drawDetectedLines(image,cv::Scalar(0,0,255));
  cv::namedWindow("Lineas");
  cv::imshow("Lineas",image);
   }
}

void MainWindow::on_pushButton_41_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();

    }else {
        BuscaLinea finder;
        cv::Mat aux;
        finder.setLineLengthAndGap(100,80);
        finder.setMinVote(20);

        cv::Canny(image,aux,125,350);



        std::vector<cv::Vec4i> lines= finder.findLines(aux);


        for (int i=0;i<lines.size();i++){

            int x1=lines[i][0],
                    x2=lines[i][1],
                    y1=lines[i][2],
                    y2=lines[i][3];
          double p=(double)(y2-y1)/(x2-x1);


        }
/*if(ui->spinBox->value()>=int(lines.size())){
    msg.setText(QString("En la imagen solo se encontro %1 lineas").arg(lines.size()));
    msg.exec();
return;
}
        int n=ui->spinBox->value() ;*/

for (int i=0;i<lines.size();i++){
        cv::Mat oneline(aux.size(),CV_8U,cv::Scalar(0));

        cv::line(oneline,
                 cv::Point(lines[i][0],lines[i][1]),
                cv::Point(lines[i][2],lines[i][3]),
                cv::Scalar(255),
                5);


        cv::bitwise_and(aux,oneline,oneline);

        std::vector<cv::Point> points;

        for( int y = 0; y < oneline.rows; y++ ) {

            uchar* rowPtr = oneline.ptr<uchar>(y);
            for( int x = 0; x < oneline.cols; x++ ) {

                if (rowPtr[x]) {
                    points.push_back(cv::Point(x,y));
                }
            }
        }
        cv::Vec4f line;

        cv::fitLine(cv::Mat(points),line, CV_DIST_L2, 0,0.01,0.01);

        int x0= line[2];
        int y0= line[3];
        int x1= x0-200*line[0];
        int y1= y0-200*line[1];
        double p=(double)(y1-y0)/(x1-x0);
        int m=(x0+x1)/2;

if(y0>image.rows/3&&y1>image.rows/3){
    if((m>image.cols*3/5&&p>0)||(m<image.cols*2/5&&p<0)){
        cv::line(image,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar(0,255,0),3);
    }
}

}
        cv::namedWindow("Resultado");
        cv::imshow("Resultado",image);
    }
}



void MainWindow::on_pushButton_42_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();

    }else if(ui->spinBox_3->value() > ui->spinBox_4->value()){
        msg.setText("El límite inferior debe ser menor o igual al límite superior");
        msg.exec();
    }else{
    cv::Mat grayl;
    cv::cvtColor(image,grayl,7);

    cv::Mat bina;

cv::threshold(grayl,bina,80,255,cv::THRESH_BINARY_INV);

int ampl=6;

cv::Mat elx(ampl,ampl,CV_8U,cv::Scalar(1));
cv::morphologyEx(bina,bina,cv::MORPH_OPEN,elx);

cv::Mat elx2(6,6,CV_8U,cv::Scalar(1));
cv::morphologyEx(bina,bina,cv::MORPH_CLOSE,elx2);

std::vector<std::vector<cv::Point> > contours;
 cv::findContours(bina,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

 //Eliminar contornos muy grandes o muy pequeños

 int cmin= ui->spinBox_3->value();
  int cmax=ui->spinBox_4->value();
  std::vector<std::vector<cv::Point> >::
  iterator itc= contours.begin();
  /*while (itc!=contours.end()) {
  if (itc->size() < cmin || itc->size() > cmax)
  itc= contours.erase(itc);
  else
  ++itc;
  }*/




  cv::drawContours(image, contours, -1, cv::Scalar(0,0,255), 2);



  cv::namedWindow("Resultado");
  cv::imshow("Resultado",image);
    }

}

void MainWindow::on_pushButton_30_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
        return;
    }
    cv::Point pt1(image.cols/2,0);
    cv::Point pt2(image.cols/2,image.rows-1);
    cv::line( image, pt1, pt2, cv::Scalar(0,255,0));
    cv::line(image,cv::Point(0,image.rows/2),cv::Point(image.cols-1,image.rows/2),cv::Scalar(0,255,0));

    cv::namedWindow("Resultado");
    cv::imshow("Resultado",image);
}

void MainWindow::bordes(int x, int y){

    QMessageBox msg;

    if (image.at<uchar>(x,y)==1){

        msg.setText("blanco");
        msg.exec();

    }
    else {
        msg.setText("negro");
        msg.exec();
    }



}





void MainWindow::on_pushButton_43_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
        return;
    }
    cv::Mat resultado=image.clone();






    int Uphome= ApHome(image); //estimar la pocision del home
    cv::Mat imageRIO= image(cv::Rect(image.cols/3,Uphome,image.cols/3,30));
    int thr=OptimalHomeThres(imageRIO);//buscar un umbral optimo para detectar la pocision y dimensiones del HP
    int ajusteX=image.cols/3;
    int ajusteY=Uphome;


    //este vector de enteros es necesario para dibujar la zona de Strike
    std::vector<int> limitesHome= Home_Limit(imageRIO,thr); //deteccion de las dimenciones del HP {limite izquierdo del HP;limite derecho del HP;limite inferior del HP}


    // dibujar los limites laterales del HP en la imagen
    cv::line(image,cv::Point(limitesHome[0]+ajusteX,0),cv::Point(limitesHome[0]+ajusteX,limitesHome[2]+ajusteY),cv::Scalar(0,255,0),2);
    cv::line(image,cv::Point(limitesHome[1]+ajusteX,0),cv::Point(limitesHome[1]+ajusteX,limitesHome[2]+ajusteY),cv::Scalar(0,255,0),2);

    //ubicar los cajones de bateo y regiones de interés segun las dimensiones estipuladas

    int homeW=limitesHome[1]-limitesHome[0];
    int homeH=limitesHome[2]-limitesHome[3];
    int baterBoxW=round(homeW*2.700);
    int baterBoxH=round(homeW*4.631);
    int distHBB=round(homeW*0.234);
    int H_cintura= round(baterBoxH/6);


    cv::Rect cint_Izq(limitesHome[0]+ajusteX-distHBB-baterBoxW,limitesHome[2]+ajusteY-3*(baterBoxH)/6,baterBoxW,H_cintura*3);
    cv::Rect cint_Der(limitesHome[1]+ajusteX+distHBB,limitesHome[2]+ajusteY-3*(baterBoxH)/6,baterBoxW,H_cintura*3);


    std::vector<int> bat_pos=BaterDim(cint_Izq,cint_Der);


    if(bat_pos[0]==0) cv::rectangle(image,cv::Rect(limitesHome[0]+ajusteX-distHBB-baterBoxW,limitesHome[2]+ajusteY-baterBoxH,baterBoxW,baterBoxH),cv::Scalar(0,255,0));
    else cv::rectangle(image,cv::Rect(limitesHome[1]+ajusteX+distHBB,limitesHome[2]+ajusteY-baterBoxH,baterBoxW,baterBoxH),cv::Scalar(0,255,0));


    int cintura=cint_Der.y+bat_pos[1];

    cv::line(image,cv::Point(0,cintura),cv::Point(image.cols-1,cintura),cv::Scalar(0,0,255),1);//dibujar aproximacion a la cintura

    int suelo=(limitesHome[2]+ajusteY-(homeH*2));
    cv::line(image,cv::Point(0,suelo),cv::Point(image.cols-1,suelo),cv::Scalar(0,0,255),1);//dibujar aproximacion a la cintura

    int altRod= (suelo-cintura)/2;
    int ajusteRod=altRod/25;

    int posRod= suelo-altRod-ajusteRod;
    cv::line(image,cv::Point(0,posRod),cv::Point(image.cols-1,posRod),cv::Scalar(0,255,0),1);// dibujar limite inferior de la zona de strike

    int altCuello=(5*(altRod/4))+(suelo-cintura);

    int posCuello=suelo-altCuello;
    cv::line(image,cv::Point(0,posCuello),cv::Point(image.cols-1,posCuello),cv::Scalar(0,0,255),1);//dibujar aproximacion a la cintura

    int SZSuplim = cintura-(cintura-posCuello)/2;
    cv::line(image,cv::Point(0,SZSuplim),cv::Point(image.cols-1,SZSuplim),cv::Scalar(0,255,0),1);// dibujar limite superior de la zona de strike

    cv::namedWindow("pasos");
    cv::imshow("pasos",image);
    int SZWidth=(limitesHome[1]+ajusteX)-(limitesHome[0]+ajusteX);

    int SZHeigth=posRod-SZSuplim;
    cv::Rect StrikeZone(limitesHome[0]+ajusteX,SZSuplim,SZWidth,SZHeigth);

    cv::Mat Reg= resultado(StrikeZone);
   for(int i=0;i<Reg.rows;i++)
   {
       for(int j=0;j<Reg.cols;j++)
       {
           if((Reg.at<cv::Vec3b>(i,j)[0]+50)>255)Reg.at<cv::Vec3b>(i,j)[0]=255;
           else Reg.at<cv::Vec3b>(i,j)[0]+=50;
           if((Reg.at<cv::Vec3b>(i,j)[1]+50)>255)Reg.at<cv::Vec3b>(i,j)[1]=255;
           else Reg.at<cv::Vec3b>(i,j)[1]+=50;
           if((Reg.at<cv::Vec3b>(i,j)[2]+50)>255)Reg.at<cv::Vec3b>(i,j)[2]=255;
           else Reg.at<cv::Vec3b>(i,j)[2]+=50;

       }
   }



    cv::rectangle(resultado,StrikeZone,cv::Scalar(255,255,255));

    cv::namedWindow("Resultado");
    cv::imshow("Resultado",resultado);
}

std::vector<cv::Vec2f> MainWindow::lineas_diamante(cv::Mat img)
{
    // Apply Canny algorithm
    cv::Mat contours;
    cv::Canny(img,contours,125,350);// cv::Canny(image,contours,125,350);


    // Hough tranform for line detection
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(contours,lines,1,M_PI/180,200);




    std::vector<cv::Vec2f> lineas_guias;
    std::vector<cv::Vec2f>::const_iterator it= lines.begin();

    while (it!=lines.end()) {
        float rho= (*it)[0]; // first element is distance rho
        float theta= (*it)[1]; // second element is angle theta

        if ((theta > 0.35*M_PI && theta < 0.49*M_PI)||(theta > 0.51*M_PI && theta < 0.65*M_PI))
        {
            cv::Point pt1(0,rho/sin(theta));
            // point of intersection of the line with last column
            cv::Point pt2(img.cols,
                          (rho-img.cols*cos(theta))/sin(theta));
            // draw a white line
            int lim1=img.rows/4, lim2= 3*(img.rows/4);
           if(pt1.y<lim2&&pt1.y>lim1&&pt2.y<lim2&&pt2.y>lim1)
           {
              // cv::line(image, pt1, pt2, cv::Scalar(0,0,255), 1);
               lineas_guias.push_back(*it);
           }

        }

        ++it;

    }
    return lineas_guias;
}

std::vector<int> MainWindow::BaterDim(cv::Rect ri,cv::Rect rd)
{
    std::vector<int> dim;
    cv::Mat aux=image.clone();

    findForeground(aux);
    cv::Mat I= aux(ri);
    cv::Mat D= aux(rd);

int cant_PN_I=0,cant_PN_D=0;

for(int i=0;i<I.rows;i++)
{
    for(int j=0;j<I.cols;j++)
    {
      if(I.at<cv::Vec3b>(i,j)[0]==0&&I.at<cv::Vec3b>(i,j)[1]==0&&I.at<cv::Vec3b>(i,j)[2]==0)cant_PN_I++;
      if(D.at<cv::Vec3b>(i,j)[0]==0&&D.at<cv::Vec3b>(i,j)[1]==0&&D.at<cv::Vec3b>(i,j)[2]==0)cant_PN_D++;
    }
}

dim.push_back(cant_PN_I<cant_PN_D?0:1);

std::vector<cv::Point> bater= cant_PN_I<cant_PN_D?findBater(I):findBater(D);

int cint=cintura(bater,I.rows/3,dim[0]);
dim.push_back(cint);

cv::line(I,cv::Point(0,cint),cv::Point(I.cols-1,cint),cv::Scalar(0,255,0),1);
cv::line(D,cv::Point(0,cint),cv::Point(I.cols-1,cint),cv::Scalar(0,255,0),1);

cv::namedWindow("I");
cv::imshow("I",I);
cv::namedWindow("D");
cv::imshow("D",D);


return dim;
}

int MainWindow::cintura(std::vector<cv::Point> bater,int Limite_busqueda,int pos)
{
  std::vector<cv::Point> mayores;
  int mayor=pos==0?1000:0;
  std::vector<cv::Point>::iterator it= bater.begin();

  while(it!=bater.end())
  {
      cv::Point mp=(*it);
      if(mp.y<Limite_busqueda)
      {
          if(pos==0?mp.x<mayor:mp.x>mayor)
          {
              mayor=mp.x;
              mayores.clear();
              mayores.push_back((*it));
          }
          if(mp.x==mayor)
          {
              mayores.push_back((*it));
          }
      }
      it++;
  }

  it=mayores.begin();

  int superior=1000;
  int inferior=0;
  while(it!=mayores.end())
  {
       cv::Point mp=(*it);
      if(mp.y<superior) superior=mp.y;
       if(mp.y>inferior) inferior=mp.y;
      it++;
  }

  int intervalo=inferior-superior;

  int cint=superior+(intervalo/5);
  return cint;

}

void MainWindow::on_pushButton_44_clicked()
{
    Home_Limit(image,165);


  cv::namedWindow("Resultado");
  cv::imshow("Resultado",image);



}

cv::Point MainWindow::homePiont(std::vector<cv::Vec2f> guias)
{
    std::vector<cv::Vec2f>::const_iterator it1= guias.begin();

    std::vector<cv::Vec2f> crecientes;
    std::vector<cv::Vec2f> decrecientes;
    while (it1!=guias.end())
    {
        float th=(*it1)[1];
        if(th>M_PI/2.)decrecientes.push_back(*it1);
        else crecientes.push_back(*it1);

        it1++;
    }

    std::vector<cv::Vec2f>::const_iterator itc= crecientes.begin();


    int yc;
    int yd;


    cv::Point hP(0,0);
    cv::Point auxP(0,0);

    while (itc!=crecientes.end())
    {
       float rho_1=(*itc)[0];
       float theta_1=(*itc)[1];
       std::vector<cv::Vec2f>::const_iterator itd= decrecientes.begin();
       while (itd!=decrecientes.end())
       {
          float rho_2=(*itd)[0];
          float theta_2=(*itd)[1];

          for(int i=0;i<image.cols;i++)
          {
              yc = (rho_1-i*cos(theta_1))/sin(theta_1);
              yd = (rho_2-i*cos(theta_2))/sin(theta_2);

              if (yc==yd)
              {
              auxP=cv::Point(i,yc);
              break;
              }


          }
          if(auxP.y>hP.y) hP=cv::Point(auxP.x,auxP.y);

          itd++;

       }

       itc++;
    }
    return hP;
}

int MainWindow::OptimalHomeThres(cv::Mat imageRIO)
{

    cv::Mat binaRIO;
    cv::Mat RIO= imageRIO(cv::Rect(100,0,imageRIO.cols-200,imageRIO.rows));

    cv::cvtColor(RIO,binaRIO,7);

    cv::Mat_<uchar>::const_iterator it= binaRIO.begin<uchar>();

    uchar max=0;
    uchar min=255;

    while(it!=binaRIO.end<uchar>())
    {
        if((*it)>max)max=(*it);
        if((*it)<min)min=(*it);
        it++;
    }
    return ((max+max+min)/3);
}

std::vector<int> MainWindow::Home_Limit(cv::Mat img,int thr)
{
    QMessageBox msg;
    if(img.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();

    }else{
        cv::Mat grayl;
        cv::cvtColor(img,grayl,7);

        cv::Mat bina;

        cv::threshold(grayl,bina,thr,255,cv::THRESH_BINARY);






        std::vector<std::vector<cv::Point> > contours;
        std::vector<std::vector<cv::Point> > salida;
        cv::findContours(bina,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

        //Eliminar contornos muy grandes o muy pequeños, y otros filtros

        int cmin=90 ;
        int cmax=200;
        std::vector<std::vector<cv::Point> >::iterator itc= contours.begin();
        std::vector<cv::Point> con;
        std::vector<cv::Point>::iterator itp;
        int menor=10000;
        std::vector<int> lim;   // valores para dibujar los limites verticales de la SZ
        while (itc!=contours.end())
        {

            int max_x=0, max_y=0, min_x=img.cols, min_y=img.rows;
            con = *itc;
            itp=con.begin();

            while(itp!=con.end())
            {
                if(((cv::Point)*itp).x>max_x)max_x=((cv::Point)*itp).x;
                if(((cv::Point)*itp).x<min_x)min_x=((cv::Point)*itp).x;
                if(((cv::Point)*itp).y>max_y)max_y=((cv::Point)*itp).y;
                if(((cv::Point)*itp).y<min_y)min_y=((cv::Point)*itp).y;

                itp++;
            }

            int x=max_x-min_x;
            int y=max_y-min_y;
            if (x<6*y)
            {
               itc++;
            }
            else if (itc->size() < cmin || itc->size() > cmax)
                itc++;


            else if(max_y<menor)
            {
                menor=max_y;
               lim.clear();
               lim.push_back(min_x-1);
               lim.push_back(max_x+1);
               lim.push_back(max_y+1);
               lim.push_back(min_y-1);
               salida.clear();
               salida.push_back(con);
                itc++;

            }
            else itc++;
        }





        cv::drawContours(img, salida, -1, cv::Scalar(0,0,255), 1);

    return lim;
    }
}

int MainWindow::alineado( std::vector<cv::Point> con,cv::Mat img)
{

    std::vector<cv::Point>::iterator itp =con.begin();
    int linea =img.rows/2;
    while(itp!=con.end())
    {
        if(((cv::Point)*itp).y==linea)return 1;
        itp++;
    }
    return 0;
}

cv::Rect MainWindow::compressROI(cv::Mat frm, cv::Rect boundingBox, int padding)
{
    Rect returnRect = Rect(boundingBox.x, boundingBox.y, boundingBox.width, boundingBox.height - padding);
        if (returnRect.x < 0)returnRect.x = 0;
        if (returnRect.y < 0)returnRect.y = 0;
        if (returnRect.x+returnRect.width >= frm.cols)returnRect.width = frm.cols-returnRect.x;
        if (returnRect.y+returnRect.height >= frm.rows)returnRect.height = frm.rows-returnRect.y;
        return returnRect;
}

void MainWindow::on_pushButton_46_clicked()
 {
     QMessageBox msg;
     if(image.empty()){
         msg.setText("Necesitas Cargar una Imagen")    ;
         msg.exec();
         return;
     }

    Limpiar(image);

    cv::namedWindow("Resultado");
    cv::imshow("Resultado",image);

 }

void MainWindow::Limpiar(cv::Mat img)
 {


     for(int i=1;i<img.cols-1;i++)
      {
          for(int j=1;j<img.rows-1;j++)
          {
              if(isBackground(img.at<cv::Vec3b>(j,i)))
              {
                  img.at<cv::Vec3b>(j,i)={0,0,0};
              }
          }
      }

 }

bool MainWindow::isBackground(cv::Vec3b color)
{

    cv::Vec3b val('b','g','r');
    int pos,menor;

    for(int i=0;i<3;i++)
    {
        pos=i;
        menor=color[i];
        for(int j=i+1;j<3;j++)
        {
            if(color[j]<menor)
            {
                menor=color[j];
                pos=j;
            }
        }

        int aux= color[pos];
        color[pos]= color[i];
        color[i]=aux;

        aux=val[pos];
        val[pos]=val[i];
        val[i]=aux;


    }

   // if(color[2]<100)return true;//para borrar los colores oscuros
    if(val[2]=='b'&&(color[2]-color[0]<32||color[1]-color[0]<28))return false;//dejar los pixeles con el azul mas alto que los otros canales
    if((val[1]=='b')&&color[2]-color[1]<18)return false;
   // if(val[0]=='b')return true;

    return color[2]-color[0]>=15&&color[2]-color[0]<=100;

}

void MainWindow::on_pushButton_47_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
        return;
    }


   findForeground(image);
    cv::namedWindow("Resultado");
    cv::imshow("Resultado",image);
}

void MainWindow::findForeground(cv::Mat img)
 {

     cv::Mat ely(15,5,CV_8U,cv::Scalar(1));
     for (int i = 0;i<50;i++){
         if(i%9==0)cv::morphologyEx(img,img,cv::MORPH_OPEN,ely);
         cv::medianBlur(img,img,5);
     }

     Limpiar(img);
     cv::morphologyEx(img,img,cv::MORPH_OPEN,ely);
     cv::medianBlur(img,img,5);
 }

std::vector<cv::Point> MainWindow::findBater(cv::Mat img)
 {


         cv::Mat grayl;
         cv::cvtColor(img,grayl,7);

         cv::Mat bina;

         cv::threshold(grayl,bina,10,255,cv::THRESH_BINARY);
         std::vector<std::vector<cv::Point> > contours;
         cv::findContours(bina,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

         //buscar la mayor region


         std::vector<std::vector<cv::Point> >::iterator itc= contours.begin();
         std::vector<cv::Point> mCont;
         int mayor=0;

         while (itc!=contours.end())
         {
            if(itc->size()>mayor)
            {
             mayor=itc->size();
             mCont=*itc;
            }
            itc++;
         }


         contours.clear();
         contours.push_back(mCont);


         cv::drawContours(img, contours, -1, cv::Scalar(0,0,255), 1);

         return mCont;

 }

char MainWindow::wColor(cv::Vec3b color)
{

    cv::Vec3b val('b','g','r');
    int pos,menor;

    for(int i=0;i<3;i++)
    {
        pos=i;
        menor=color[i];
        for(int j=i+1;j<3;j++)
        {
            if(color[j]<menor)
            {
                menor=color[j];
                pos=j;
            }
        }

        int aux= color[pos];
        color[pos]= color[i];
        color[i]=aux;

        aux=val[pos];
        val[pos]=val[i];
        val[i]=aux;


    }

      //if (color[2]<60)return 'o';

      return val[2];

 }

void MainWindow::home_Limpiar(cv::Mat img)
{
    cv::Mat ely(20,1,CV_8U,cv::Scalar(1));

        cv::morphologyEx(img,img,cv::MORPH_OPEN,ely);



    for(int i=img.rows-1;i>=0;i--)
    {
        int r=0,g=0,b=0;

        char mayor1='r';
        int m1=0;

        for(int j=0;j<img.cols;j++)
        {
            if(wColor(img.at<cv::Vec3b>(i,j))=='r')
            {
                r++;
                if(r>m1){

                    m1=r;

                    mayor1='r';
                }
            }
            else if(wColor(img.at<cv::Vec3b>(i,j))=='g')
            {
                g++;
                if(g>m1){

                    m1=g;

                    mayor1='g';
                }
            }
            else if(wColor(img.at<cv::Vec3b>(i,j))=='b')
            {



                b++;
                if(b>m1){
                    m1=b;

                    mayor1='b';
                }
            }

        }
        if(mayor1=='g'&&m1>img.cols*0.6){
            for(int k=0;k<img.cols;k++)
            {
                img.at<cv::Vec3b>(i,k)={0,0,0};
            }
        }
    }
}

void MainWindow::on_pushButton_48_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen")    ;
        msg.exec();
        return;
    }


   home_Limpiar(image);
    cv::namedWindow("Resultado");
    cv::imshow("Resultado",image);
}

int MainWindow::ApHome(cv::Mat img)
{
   cv::Mat mimg=img.clone();
    home_Limpiar(mimg);
    std::vector<std::vector<int> > regiones;
    std::vector<int> aux;

    int a,b,c,d;
    //delimitar las regiones entre posible cesped
    for(int i=2;i<mimg.rows;i++)
    {
        aux.clear();

        if(mimg.at<cv::Vec3b>(i-1,0)[0]==0&&mimg.at<cv::Vec3b>(i-1,0)[1]==0&&mimg.at<cv::Vec3b>(i-1,0)[2]==0&&mimg.at<cv::Vec3b>(i-1,mimg.cols/2)[0]==0&&mimg.at<cv::Vec3b>(i-1,mimg.cols/2)[1]==0&&mimg.at<cv::Vec3b>(i-1,mimg.cols/2)[2]==0&&(mimg.at<cv::Vec3b>(i,0)[0]=0||mimg.at<cv::Vec3b>(i,mimg.cols/2)[0]!=0))
        {
            aux.push_back(i-1);
            cv::line(mimg,cv::Point(0,i-1),cv::Point(mimg.cols-1,i-1),cv::Scalar(0,0,255));
            for(;i<mimg.rows;i++)
            {
                if(mimg.at<cv::Vec3b>(i,0)[0]==0&&mimg.at<cv::Vec3b>(i,0)[1]==0&&mimg.at<cv::Vec3b>(i,0)[2]==0&&mimg.at<cv::Vec3b>(i,mimg.cols/2)[0]==0&&mimg.at<cv::Vec3b>(i,mimg.cols/2)[1]==0&&mimg.at<cv::Vec3b>(i,mimg.cols/2)[2]==0)
                {
                    cv::line(mimg,cv::Point(0,i-1),cv::Point(mimg.cols-1,i-1),cv::Scalar(255,0,0));
                    aux.push_back(i-1);
                    regiones.push_back(aux);

                    break;
                }
            }
        }
    }

 // encontrar la region mas cercana al centro horizontal de la imagen
    int menor =10000;
    int sup;
    int inf;
    std::vector<std::vector<int> >::iterator it=regiones.begin();
    while(it!=regiones.end()){
        int altura=(*it)[1]-(*it)[0];
        int medio=(*it)[1]-(altura/2);
        int distancia= medio-(mimg.rows/2);
        distancia*=distancia<0?-1:1;
        if(distancia<menor){
            menor=distancia;
            sup=(*it)[0];
            inf=(*it)[1];
        }
        it++;
    }
    if(menor!=10000)
    {
         cv::line(mimg,cv::Point(0,sup+1),cv::Point(mimg.cols-1,sup+1),cv::Scalar(0,255,0));
          cv::line(mimg,cv::Point(0,inf-2),cv::Point(mimg.cols-1,inf-2),cv::Scalar(0,255,0));
           a=(img.cols/3);
           b=sup+1;
           c=(img.cols/3);
           d=inf-sup-1;
          if(d>30)
          {
            int resto=d-30;
            b+=resto/2;
            d-=resto;
          }



    }
    return b;
}
void MainWindow::on_pushButton_49_clicked()
{
    QMessageBox msg;
    if(image.empty()){
        msg.setText("Necesitas Cargar una Imagen");
        msg.exec();
        return;
    }


   int pos= ApHome(image);
   cv::Mat imageRIO= image(cv::Rect(image.cols/3,pos,image.cols/3,30));
    cv::namedWindow("Resultado");
    cv::imshow("Resultado",imageRIO);
}
//--
//--
//Procesamiento de video
//--
//--
void MainWindow::on_pushButton_45_clicked()
{
    videofileName = QFileDialog::getOpenFileName(this, tr("Open Image"),path , tr("Image Files (*.avi *.mpg *.mp4)"));

    if(!videofileName.isEmpty()){
        cv::VideoCapture aux;

        aux.open(videofileName.toLatin1().data());
       video=aux;
    }

}

void MainWindow::on_pushButton_50_clicked()
{

    QMessageBox msg;
    if(!video.isOpened()){
        msg.setText("Necesitas Cargar un Video");
        msg.exec();
        return;
    }
   Mat frame;
  vector<Mat> im;
  int s=0;
    while(video.read(frame))
    {

            Mat y=frame.clone();
            im.push_back(y);


    }



   Mat a=VibeAlgoritm(im);

 restablecerVideo();
}

void MainWindow::restablecerVideo()
{
    cv::VideoCapture aux;

    aux.open(videofileName.toLatin1().data());
    video=aux;
}

Mat MainWindow::filter_image(Mat &img)
{
    int morph_size1 = 1;
        int morph_size2 = 1;
        Mat kernel = cv::getStructuringElement(MORPH_RECT, Size(2*morph_size1 +1, 2*morph_size2 +1));
        Mat filtered;

        // perform opeing
        erode(img, filtered, kernel);
        dilate(filtered, filtered, kernel);

        return filtered;
}

Mat MainWindow::VibeAlgoritm(vector<Mat> imgs)
{
    vector < vector < Point > >contours;
    vector<Vec4i> hierarchy;

    Mat fr=imgs[0];

    int w=fr.cols;
    int h=fr.rows;

    Vibe vibe(w,h);
    Mat res;
    vector<Mat>::iterator it =imgs.begin();
    int i=imgs.size()-1;
    while(it!=imgs.end())
    {
        res=imgs[i];

        Mat gray;
        Mat aux;
        cv::Mat ely(15,5,CV_8U,cv::Scalar(1));
        cv::morphologyEx(res,aux,cv::MORPH_OPEN,ely);
        medianBlur(aux, aux, 5);
        cvtColor(aux, gray, COLOR_BGR2GRAY);

        // size of the frame


        // get segmented image

        Mat seg;
        vibe.segment(gray,seg);

        // removal of noise by median filtering
        for(int i=0;i<7;i++)
        medianBlur(seg, seg, 5);


        // morphology


        dilate(seg, seg, Mat(15,15,CV_8U));
        for(int i=0;i<5;i++)
        medianBlur(seg, seg, 7);
        // define horizontal line parameters



        // find the contours

        findContours (seg, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

        std::vector<std::vector<cv::Point> >::iterator itc= contours.begin();


        cv::drawContours(res, contours, -1, cv::Scalar(0,0,255), 1);

        // show output frame
        cv::namedWindow("vibe");
         imshow("vibe",res);


        int k = waitKey(10);
        if ( k == ' ' ) vibe.clear();
        if ( k == 27  ) break;

        it++;
        i--;
    }
    return res;
}

Mat MainWindow::MOG2Algoritm(vector<Mat> imgs)
{
    const int nmixtures = 25;
        const bool bShadowDetection = true;
        const int history = 2000;
        BackgroundSubtractorMOG2 bg(history, nmixtures, bShadowDetection);

        vector < vector < Point > >contours;

        vector<Vec4i> hierarchy;


    Mat fgimg, res;
    vector<Mat>::iterator it =imgs.begin();
    int i=0;
    while(it!=imgs.end())
    {
        res=imgs[i];

        medianBlur(res, res, 5);
        Mat blur_out;
        GaussianBlur(res, blur_out, Size(1,1),0,0);

        // motion detection

        const double learningRate = -1;
        bg.operator()(blur_out, fgimg, learningRate);

        // smoothen the mask

        medianBlur(fgimg, fgimg, 5);

        GaussianBlur(fgimg, fgimg, Size(1,1),0,0);

        //Morphology operaitons

        fgimg = filter_image(fgimg);




        // morphology


        dilate(fgimg, fgimg, Mat(10,1,CV_8U));


        // find the contours

        findContours (fgimg, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
       int min=(res.cols*res.rows)/1000;
        std::vector<std::vector<cv::Point> >::
        iterator itc= contours.begin();
        while (itc!=contours.end()) {
          if (itc->size() < min)
          itc= contours.erase(itc);
          else
          ++itc;
           }
            drawContours(res,contours,-1,Scalar(0,255,0),1);

            cv::namedWindow("mog2");
             imshow("mog2",res);

            char k = (char)waitKey(30);
            if( k == 27 ) break;

        it++;
        i++;
    }
    return res;
}

Mat MainWindow::myAlgoritm(vector<Mat> imgs)
{
    Mat x=imgs[0];
    Mat y=imgs[1];



    Mat i0;
    Mat i1;

    cvtColor(x, i0, 7);
    cvtColor(y, i1, 7);


    for(int i=0;i<i0.rows;i++)
    {
        for(int j=0;j<i0.cols;j++)
        {

            int aux =i0.at<uchar>(i,j)-i1.at<uchar>(i,j);
            if(aux<0)
            {
                aux*=-1;

            }
            
            i0.at<uchar>(i,j)=aux;
        }
    }

    cv::namedWindow("mya");
    imshow("mya",i0);
}

void MainWindow::on_pushButton_51_clicked()
{


    QMessageBox msg;
    if(!video.isOpened()){
        msg.setText("Necesitas Cargar un Video");
        msg.exec();
        return;
    }
    Mat frame;
    vector<Mat> im;
    vector<Mat> pr;
    while(video.read(frame))
    {

        Mat y=frame.clone();
        im.push_back(y);


    }








    Mat a=myAlgoritm(im);

    restablecerVideo();
}



void MainWindow::on_pushButton_52_clicked()
{
    QUrl p(QString("http://sinternos.uci.cu/cortos_los_vengadores_unidos_-_thanos_triunfante.webm"));
    QMessageBox msg;
    cv::VideoCapture aux;
    aux.open(0);
if (aux.isOpened()) {


 for (;;) {
   //Input image.
   cv::Mat frame;

   //A frame is obtained and stored in "frame".
   aux >> frame;

   //If there are no more frames in the video, ends the program.
   if (frame.empty())
     break;

   //The frame is displayed.
   cv::imshow("Output", frame);

   //If key Esc is pressed, ends the program.
   if (cv::waitKey(20) == 27)
     break;
 }
}
else{

msg.setText("no se pudo");
msg.exec();

}

}
