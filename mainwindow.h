#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


#include "colordetectcontroller.h"
using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_ruidoo_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_32_clicked();



    void on_pushButton_31_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_38_clicked();



    void on_pushButton_39_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_41_clicked();



    void on_pushButton_42_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_44_clicked();



    void on_pushButton_46_clicked();



    void on_pushButton_47_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_49_clicked();

    void on_pushButton_45_clicked();

    void on_pushButton_50_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_52_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat image;
    cv::VideoCapture video;
    cv::Mat histog;
    cv::Mat result;
    QColor colorRuido;
    QColor colorBI;
    cv::Mat auxiliar;
    QString imagefileName;
    QString videofileName;
    QString path="F:/Marcos/Para tesis";
    cv::Mat Im;
    ColorDetectController *control;
    int Reduc_factor;
    void salt(cv::Mat img,int n);
    cv::Mat variarcolor(int divv, cv::Mat image);
    void Saturar();
    void bordes(int x, int y);
    cv::Point homePiont(std::vector<cv::Vec2f> guias);
    void Superponer(int c,int r);
    void Prevsualizar(QString px,QString py,QString tx,QString ty);
    void detec_color();
    int OptimalHomeThres(cv::Mat binaRIO);
    std::vector<int> Home_Limit(cv::Mat img, int thr);
    cv::Mat extraerForeground(cv::Rect rectangle);
    std::vector<int> BaterDim(cv::Rect ri,cv::Rect rd);
    bool isBackground(cv::Vec3b color);
    void Limpiar(cv::Mat img);
    void findForeground(cv::Mat img);
    std::vector<cv::Point> findBater(cv::Mat img);
    std::vector<cv::Vec2f> lineas_diamante(cv::Mat img);
    int cintura(std::vector<cv::Point> bater, int CH,int pos);
    char wColor(cv::Vec3b color);
    void home_Limpiar(cv::Mat img);
    void deslin(cv::Mat img);
    int ApHome(cv::Mat img);
    int alineado( std::vector<cv::Point> con,cv::Mat img);
    cv::Rect compressROI(cv::Mat frm, cv::Rect boundingBox, int padding);
    void restablecerVideo();
    Mat filter_image(Mat& img);

    Mat VibeAlgoritm(vector<Mat> imgs);
    Mat MOG2Algoritm(vector<Mat> imgs);

    Mat myAlgoritm(vector<Mat> imgs);
};

#endif // MAINWINDOW_H
