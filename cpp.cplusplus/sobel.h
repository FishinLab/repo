#include "opencv.h"
#include <iostream>

using namespace cv;
using namespace std;

class Sobel
{
	private:
		cv::Mat SobelCore;		
		
		int eigen;

	public: 
		void generateCore(int coreType);
	    void latitude(cv::Mat core);
		void matitude(cv::Mat core);

	    int getEigen(cv::Mat core);	
		Mat outMat();
};

class guassianCore
{
	private:
	  	Mat GuassianCore;

		int eigen;
	public:
		void generateCore(int coreType);
		int getEigen();
		Mat outMat();
};

class Canny
{
	public:
	  static void canny(IplImage* srcImg , IplImage* dstImg , int hold1 , int hold2 , int eigen);

};

class Smooth
{
	public:
	  static void smooth(IplImage* srcImg , IplImage* dstImg);
	  static void smThreshold(IplImage* srcImg , IplImage* dstImg , int th);
};
