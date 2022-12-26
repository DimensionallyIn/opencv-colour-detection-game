#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <stdlib.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/dnn.hpp>
#include <opencv2/opencv_modules.hpp>
#include<windows.h>
#include<winuser.h>
#include<istream>
#include<ostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/core/types.hpp>

using namespace std;
using namespace cv;
int hmin=0,smin=102,vmin=153;
int hmax =102, smax =255,vmax=255;
Mat img , mask,gray,imghsv;
vector<vector<int>> newPoints;
vector<vector<int>> colour {{0,102,153,102,255,255}};
vector<Scalar> mycolourvalue{{0,0,255}};





vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
Point getContours(Mat mask) {





	findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
	vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());


	Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;

		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}
	return myPoint;
}


vector<vector<int>> findcolour(Mat img)
{

         cvtColor(img,imghsv,COLOR_BGR2HSV);
         cvtColor(imghsv,gray,COLOR_HSV2RGB);
  for (int i=0;i<colour.size();i++)
       {

       // Scalar lower(colour[i][0],colour[i][1],colour[i][2]);
        //Scalar upper(colour[i][3],colour[i][4],colour[i][5]);
          Scalar lower(hmin,smin,vmin);
          Scalar upper(hmax,smax,vmax);
       inRange(gray ,lower,upper,mask);

        Mat kernal=getStructuringElement(MORPH_RECT,Size(3,3));
       dilate(mask,mask,kernal);
         //imshow(to_string(i),mask);
        Point myPoint = getContours(mask);

		if (myPoint.x != 0 )
            {
			newPoints.push_back({ myPoint.x,myPoint.y,i });
       }}

       return newPoints;
       }



void game(vector<vector<int>> newPoints,vector<Scalar>mycolourvalue){





       INPUT space = {0};


    space.type = INPUT_KEYBOARD;
      space.ki.wVk = VK_SPACE;




      SendInput(1,&space,sizeof(INPUT));




}
void goat(){


            INPUT space = {0};
        space.type = INPUT_KEYBOARD;
      space.ki.wVk = VK_SPACE;
      space.ki.dwFlags = KEYEVENTF_KEYUP;

         SendInput(1,&space,sizeof(INPUT));

}


int main()
{


   VideoCapture cap(0);
   if (!cap.isOpened()){
       return -1;
   }

  namedWindow("task",(600,250));
  createTrackbar ("hue hmin","task",&hmin,255);
  createTrackbar ("hue smin","task",&smin,255);
  createTrackbar ("hue vmin","task",&vmin,255);
  createTrackbar ("hue hmax","task",&hmax,255);
  createTrackbar ("hue smax","task",&smax,255);
Point pt1(256,256) , pt2(400,400);
system("start corona-runner//index.html");
while(1){
        cap.read(img);

       newPoints = findcolour(img);
       getContours(mask);

          rectangle(img,pt1,pt2,Scalar(0,69,0),10)   ;
           putText(img,"HERE",Point(290,330),FONT_HERSHEY_SIMPLEX,1,(0,255,25),LINE_4);

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);



         if(area >3000){

                game(newPoints,mycolourvalue);

         }

        else{

            goat();
        }

	}

        imshow("Winfdow",img);
        imshow("Winfow",mask);


        waitKey(2);
   }



    return 0;
}
