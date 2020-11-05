//
//  main.cpp
//  kepfeldolgozas
//
//  Created by Geszti Bence on 2020. 09. 23..
//
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

void first();
void second();
void third();
void plotMat(Mat& m);
void historyEqualize();
void kuszoboloes();
void zajoskepJavitasKuszoboles();
void kivagas();
void demoDilation();
void demoErosion();
void demoOpening();
void demoClosing();
void kuszobolesWithClosing();
void diletacioMinusErosion();
void originMinusOpend();
void originMinusClosed();
void sharp();
void labda();

// CurrentPixelGroup 0 Blue 1 Green 2 Red

int main(int argc, const char * argv[]) {
//    first();
//    second();
//    third();
//    historyEqualize();
//    kuszoboloes();
//    zajoskepJavitasKuszoboles();
//    kivagas();
//    demoDilation();
//    demoErosion();
//    demoOpening();
//    demoClosing();
//    kuszobolesWithClosing();
//    diletacioMinusErosion();
//    originMinusOpend();
//    originMinusClosed();
//    sharp();
    labda();
    waitKey();
    return 0;
}

void first() {
    Mat img = imread("/Users/gesztibence/Downloads/IMG_3084.JPG");
    Mat blue(img.size(), CV_8UC3);

    for (int i = 0; i < img.rows ; i++ ) {
        for (int j = 0 ; j < img.cols ; j++) {
            Vec3b currentPixelGroup = img.at<Vec3b>(i,j);
            //currentPixelGroup[0] *= 0.65;  //Blue
            currentPixelGroup[1] = 0;  // Green
            currentPixelGroup[2] = 0; // Red

            blue.at<Vec3b>(i,j) = currentPixelGroup;
        }
    }
    
    imshow("blue", blue);
    
}

void second() {
    Mat img = imread("/Users/gesztibence/Downloads/IMG_3084.JPG");
    Mat darker(img.size(), CV_8UC3);

    for (int i = 0; i < img.rows ; i++ ) {
        for (int j = 0 ; j < img.cols ; j++) {
            Vec3b currentPixelGroup = img.at<Vec3b>(i,j);
            currentPixelGroup[0] *= 0.5;  //Blue
            currentPixelGroup[1] *= 0.5;  // Green
            currentPixelGroup[2] *= 0.5; // Red

            darker.at<Vec3b>(i,j) = currentPixelGroup;
        }
    }
    
    imshow("darker", darker);
}

void third() {
    Mat img = imread("/Users/gesztibence/Downloads/IMG_3084.JPG");
    Mat gray(img.size(), CV_8UC3);

    cvtColor(img, gray, COLOR_BGR2GRAY);
    
    imshow("gray", gray);
}

void plotMat(Mat& m) {
    imshow("proba", m);
    waitKey();
}

void historyEqualize() {
    Mat img = imread("/Users/gesztibence/Downloads/colored.jpeg"); // colored
    //Mat img = imread("/Users/gesztibence/Downloads/00FzkU-29347284.jpg"); // black and white
    // itt kell convertalni elvileg hsv re meg vissza majd rgb re
    Mat splitted[3], equalized[3];
    Mat result;
    split(img, splitted);
    equalizeHist(splitted[0], equalized[0]);
    equalizeHist(splitted[1], equalized[1]);
    equalizeHist(splitted[2], equalized[2]);
    
    std::vector<Mat> channels = {equalized[0],equalized[1],equalized[2]};
    merge(channels,result);
    
    imshow("historyeq", result);
    waitKey();
    
}

void kuszoboloes() {
    Mat img = imread("/Users/gesztibence/Downloads/IMG_3084.JPG");
    imshow("origin", img);
    
    Mat splited[3];
    split(img, splited);
    imshow("Splited",splited[1]);
    
    int thresh_value = 70;
    Mat thresh[5];
    threshold(splited[1], thresh[0], thresh_value, 255, THRESH_BINARY);
    imshow("Binary Green", thresh[0]);
    waitKey();
}

void zajoskepJavitasKuszoboles() {
    Mat img = imread("/Users/gesztibence/Downloads/noysi.jpg");
    imshow("origin", img);
    
//    Mat medianed(img.size(), CV_8UC3);
//    medianBlur(img, medianed, 13);
//    imshow("medianed", medianed);
    
    Mat gaussed(img.size(), CV_8UC3);
    GaussianBlur(img, gaussed, Size(23, 23), 0);
    imshow("gaussed", gaussed);
    
    int thresh_value = 120;
    Mat thresh[5];
    threshold(gaussed, thresh[0], thresh_value, 255, THRESH_BINARY);
    imshow("gaussed Tresholded", thresh[0]);
    
}

void kivagas() {
    Mat img = imread("/Users/gesztibence/Downloads/IMG_3084.JPG");
    imshow("origin", img);
    
    Mat splited[3];
    Mat cropped[3];
    
    split(img, splited);
    for (int i = 0; i < 3; i++) {
        cropped[i].create(200, 200, CV_8UC1);
        for (int x = 0; x < 200; x++) {
            for (int y = 0; y < 200; y++) {
                cropped[i].at<uchar>(x,y) = splited[i].at<uchar>( x+400,  y+400);
            }
        }
    }
    
    Mat output(Size(200,200), CV_8UC3);
    
    merge(cropped,3, output);
    
    imshow("cropd", output);
}

void demoDilation()
{
    Mat Img = imread("/Users/gesztibence/Documents/ImgProcLab/lab05/morp_test.png", 0);
    Mat kernel = Mat::ones(Size(5, 5), CV_8UC1);
    Mat dilated;

    dilate(Img, dilated, kernel);

    imshow("dilated",dilated);
    waitKey(0);

}

void demoErosion()
{
   Mat Img = imread("/Users/gesztibence/Documents/ImgProcLab/lab05/morp_test.png", 0);
   Mat kernel = Mat::ones(Size(3, 3), CV_8UC1);
   Mat eroded;

   erode(Img, eroded, kernel);

   imshow("eroded", eroded);
   waitKey(0);
}

void demoOpening()
{
   Mat Img = imread("/Users/gesztibence/Documents/ImgProcLab/lab05/morp_test_open.png", 0);
   Mat kernel = Mat::ones(Size(3, 3), CV_8UC1);
   Mat eroded,opened;

   erode(Img, eroded, kernel);
   dilate(eroded, opened, kernel);

   imshow("opened", eroded);
   waitKey(0);
}

void demoClosing()
{
    Mat Img = imread("/Users/gesztibence/Documents/ImgProcLab/lab05/morp_test_closed.png", 0);
    Mat kernel = Mat::ones(Size(7, 7), CV_8UC1);
    Mat dilated, closed;

    dilate(Img, dilated, kernel);
    erode(dilated, closed, kernel);

    imshow("closed", closed);
    waitKey(0);
}

void kuszobolesWithClosing() {
    Mat img = imread("/Users/gesztibence/Downloads/noysi.jpg");
    imshow("origin", img);
    
    Mat gaussed(img.size(), CV_8UC3);
    GaussianBlur(img, gaussed, Size(23, 23), 0);
    imshow("gaussed", gaussed);
    
    int thresh_value = 120;
    Mat thresh[5];
    threshold(gaussed, thresh[0], thresh_value, 255, THRESH_BINARY);
    imshow("gaussed Tresholded", thresh[0]);
    
//    Mat kernel = Mat::ones(Size(7, 7), CV_8UC1);
    Mat kernel = getStructuringElement( MORPH_CROSS, Size(3, 3));
    Mat dilated, closed;

    dilate(thresh[0], dilated, kernel);
    erode(dilated, closed, kernel);

    imshow("closed", closed);
}

void diletacioMinusErosion() {
    Mat img = imread("/Users/gesztibence/Downloads/00FzkU-29347284.jpg");
    imshow("origin", img);
    
    Mat kernel = Mat::ones(Size(3, 3), CV_8UC1);
    Mat dilated;

    dilate(img, dilated, kernel);
    imshow("dilated", dilated);
    Mat eroded;

    erode(img, eroded, kernel);
    imshow("eroded", eroded);
    Mat diff_im = dilated - eroded;
    
    
    imshow("diff", diff_im);
}

void originMinusOpend() {
    Mat img = imread("/Users/gesztibence/Downloads/1603266280358_file.jpg");
    imshow("origin", img);
    
    Mat eroded,opened;
    Mat kernel = Mat::ones(Size(9, 9), CV_8UC1);

    erode(img, eroded, kernel);
    
    dilate(eroded, opened, kernel);
    
    Mat diff_im = img - opened;
    imshow("diff", diff_im);
}

void originMinusClosed() {
    Mat img = imread("/Users/gesztibence/Downloads/1603266280358_file.jpg");
    imshow("origin", img);
    Mat kernel = Mat::ones(Size(7, 7), CV_8UC1);
    Mat dilated, closed;

    dilate(img, dilated, kernel);
    erode(dilated, closed, kernel);

    Mat diff_im = closed - img;
    imshow("diff", diff_im);
}

void sharp() {
    Mat img = imread("/Users/gesztibence/Downloads/1603266280358_file.jpg");
    imshow("origin", img);
    
    Mat gaussed(img.size(), CV_8UC1);
    GaussianBlur(img, gaussed, Size(23, 23), 0);
    imshow("gaussed", gaussed);
    
    Mat output;
    addWeighted(img, 1.5, gaussed, -0.5, 0, output);
    
    imshow("output", output);
}

void labda() {
    Mat img = imread("/Users/gesztibence/Downloads/65247333-orange-basketball-on-the-green-grass-.jpg");
    imshow("origin", img);
    
    Mat splited[3];
    split(img, splited);
    imshow("Splited",splited[2]);
    
    int thresh_value = 240;
    Mat thresh[5];
    threshold(splited[2], thresh[0], thresh_value, 255, THRESH_BINARY);
    imshow("mask", thresh[0]);
    
    Mat kernel = Mat::ones(Size(23, 23), CV_8UC1);
    Mat dilated, closed;

    dilate(thresh[0], dilated, kernel);
    erode(dilated, closed, kernel);
    imshow("closed", closed);
    
    Mat output;
    Mat bitwised[3];
    
    for (int i = 0; i<3; i++) {
        bitwise_and(splited[i], closed, bitwised[i]);
    }
    
    std::vector<Mat> toMerge = {bitwised[0],bitwised[1],bitwised[2]};
    merge(toMerge,output);
    imshow("output", output);
}
