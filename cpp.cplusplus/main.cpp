#include "opencv.h"
#include <iostream>
#include "sobel.h"
#include "splinter.h"

using namespace cv;
using namespace std;

void sobelProcess(IplImage* srcImg , IplImage* dstImg , IplImage* resImg)
{

	try
	{
		int eigen = 3;
		cv::Mat core(eigen , eigen , CV_32F);

		::Sobel s;
		s.generateCore(eigen);
		
		core = s.outMat();
		
		int height = srcImg->height;
		int width = srcImg->width;

		Mat tmp(eigen , eigen , CV_32F);
		CvScalar sca;
		
		for(int i = 1;i<height - 3;++i)
		{
			for(int j = 1;j<width - 3;++j)
			{

				sca = cvGet2D(dstImg , i - 1 , j - 1);
				tmp.ptr<float>(i - 1)[j - 1] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i - 1 , j);
				tmp.ptr<float>(i - 1)[j] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i - 1 , j + 1);
				tmp.ptr<float>(i - 1)[j + 1] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i , j - 1);
				tmp.ptr<float>(i)[j - 1] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i , j);
				tmp.ptr<float>(i)[j] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i , j+1);
				tmp.ptr<float>(i)[j + 1] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i + 1 , j - 1);
				tmp.ptr<float>(i + 1)[j - 1] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i + 1 ,j);
				tmp.ptr<float>(i + 1)[j] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i + 1, j + 1);
				tmp.ptr<float>(i + 1)[j + 1] = static_cast<float>(sca.val[0]);

/*

				int k = 0;
				while(k < 3)
				{
				  	int row = i + k -1;
					int col = j + k -1;
					sca = cvGet2D(dstImg , row , col);
					tmp.ptr<int>(row)[col] = (int)sca.val[0];
					k++;
				}
*/				
				int k = 0;
				int res = 0;
				while(k < 3)
				{
					int t;
					t = (tmp.ptr<float>(1)[k])*(core.ptr<float>(k)[1]);
					
					t += res;
					k++;
				}

				sca.val[0] = res;

				k = 1;
				while(k < 4)
				{
					sca.val[k] = 0;
					k++;
				}

				cvSet2D(resImg , i , j , sca);
				
			}
		}

		cvSaveImage("./sobel_srcimg.jpg" , srcImg);
		cvSaveImage("./sobel_dstImg.jpg" , dstImg);
		cvSaveImage("./sobel_resImg.jpg" , resImg);

		cvNamedWindow("srcImg" , 1);
		cvNamedWindow("dstImg" , 1);
		cvNamedWindow("resImg" , 1);

		cvShowImage("srcImg" , srcImg);
		cvShowImage("dstImg" , dstImg);
		cvShowImage("resImg" , resImg);

		cvDestroyWindow("srcImg");
		cvDestroyWindow("dstImg");
		cvDestroyWindow("resImg");

		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);
		cvReleaseImage(&resImg);
		

	}
	catch(std::exception e)
	{
		cout<<e.what()<<endl;
		if(srcImg)
		{
			cvReleaseImage(&srcImg);
		}
		if(dstImg)
		{
			cvReleaseImage(&dstImg);
		}
		if(resImg)
		{
			cvReleaseImage(&resImg);
		}
		return;
	}
	catch(cv::Exception e)
	{
		cout<<e.err.c_str()<<endl;
		if(srcImg)
		{
			cvReleaseImage(&srcImg);
		}
		if(dstImg)
		{
			cvReleaseImage(&dstImg);
		}
		if(resImg)
		{
			cvReleaseImage(&resImg);
		}
		return;
	}

}

void guassianProcess(IplImage* srcImg , IplImage* dstImg , IplImage* resImg)
{
	int c_j = 0;
	int c_i = 0;
	int c_k = 0;

	try{
	  	int eigen = 3;
		CvScalar sca;
		Mat tmp(eigen , eigen , CV_32F);
		Mat core(eigen , eigen , CV_32F);

		int width = srcImg->width;
		int height = srcImg->height;
		
		for(int i = 0;i<3;++i)
		{
			for(int j = 0;j<3;++j)
			{
				core.ptr<float>(i)[j] = 0;
				tmp.ptr<float>(i)[j] = 0;
			}
		}

		core.ptr<float>(0)[1] = 1;
		core.ptr<float>(1)[0] = 1;
		core.ptr<float>(1)[1] = 4;
		core.ptr<float>(1)[2] = 1;
		core.ptr<float>(2)[1] = 1;
				
		for(int i = 1;i<height - 3;++i)
		{
			for(int j = 1;j<width - 3;++j)
			{
		  
				int k = 0;
				while(k < 3)
				{
					int row = i + k - 1;
					int col = j + k - 1;

					sca = cvGet2D(dstImg , row , col);
					tmp.ptr<float>(k)[0] = static_cast<float>(sca.val[0]);

					sca = cvGet2D(dstImg , row , col + 1);
					tmp.ptr<float>(k)[1] = static_cast<float>(sca.val[0]);

					sca = cvGet2D(dstImg , row , col + 2);
					tmp.ptr<float>(k)[2] = static_cast<float>(sca.val[0]);

					k++;
				}
				
/*
				sca = cvGet2D(srcImg , i - 1 , j - 1);
				tmp.ptr<float>(0)[0] = sca.val[0];
				
				sca = cvGet2D(srcImg , i - 1 , j);
				tmp.ptr<float>(0)[1] = sca.val[0];

				sca = cvGet2D(srcImg , i - 1 , j + 1);
				tmp.ptr<float>(0)[2] = sca.val[0];

				sca = cvGet2D(srcImg , i , j - 1);
				tmp.ptr<float>(1)[0] = sca.val[0];

				sca = cvGet2D(srcImg , i , j);while(k < 3)
				{
					int t;
					t = (tmp.ptr<float>(1)[k])*(core.ptr<float>(k)[1]);
					
					t += res;
					if(res >= 255)
					{
						res = 255;
					}
					k++;
				}

				tmp.ptr<float>(1)[1] = sca.val[0];

				sca = cvGet2D(srcImg , i , j + 1);
				tmp.ptr<float>(1)[2] = sca.val[0];

				sca = cvGet2D(srcImg , i + 1 , j - 1);
				tmp.ptr<float>(2)[0] = sca.val[0];

				sca = cvGet2D(srcImg , i + 1 , j);
				tmp.ptr<float>(2)[1] = sca.val[0];

				sca = cvGet2D(srcImg , i + 1 , j + 1);
				tmp.ptr<float>(2)[2] = sca.val[0];
*/

				int res = 0;
				k = 0;
				while(k < 3)
				{
					int t;
					t = (tmp.ptr<float>(1)[k])*(core.ptr<float>(k)[1]);
					
					res = res + t;
					k++;
				}
				//res = static_cast<int>(res/10);
				sca.val[0] = res;

				k = 1;
				while(k < 4)
				{
					sca.val[k] = 0;
					k++;
				}

				cvSet2D(resImg , i , j , sca);

				c_j = j;
				c_i = i;
				c_k = k;
			}
		}

		cvSaveImage("./guassian_srcimg.jpg" , srcImg);
		cvSaveImage("./guassian_dstImg.jpg" , dstImg);
		cvSaveImage("./guassian_resImg.jpg" , resImg);

		cvNamedWindow("srcImg" , 1);
		cvNamedWindow("dstImg" , 1);
		cvNamedWindow("resImg" , 1);

		cvShowImage("srcImg" , srcImg);
		cvShowImage("dstImg" , dstImg);
		cvShowImage("resImg" , resImg);

		cvWaitKey();

		cvDestroyWindow("srcImg");
		cvDestroyWindow("dstImg");
		cvDestroyWindow("resImg");

		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);
		cvReleaseImage(&resImg);
		

	}
	catch(std::exception e)
	{
		cout<<e.what()<<endl;
		if(srcImg)
		{
			cvReleaseImage(&srcImg);
		}
		if(dstImg)
		{
			cvReleaseImage(&dstImg);
		}
		if(resImg)
		{
			cvReleaseImage(&resImg);
		}
		return;
	}
	catch(cv::Exception e)
	{
	  	cout<<c_j<<" "<<c_i<<" "<<c_k<<" "<<endl;
		cout<<e.err.c_str()<<endl;
		if(srcImg)
		{
			cvReleaseImage(&srcImg);
		}
		if(dstImg)
		{
			cvReleaseImage(&dstImg);
		}
		if(resImg)
		{
			cvReleaseImage(&resImg);
		}
		return;
	}
}

void canImg(string filename , string storeP)
{
	IplImage* srcImg = NULL;
	IplImage* canImg = NULL;

	try{
	
		srcImg = cvLoadImage(filename.c_str() , 0);
		canImg = cvCreateImage(cvGetSize(srcImg) , srcImg->depth , 1);

		cvCanny(srcImg , canImg , 60 , 120 , 3);

		cvSaveImage(storeP.c_str() , canImg);

		cvNamedWindow("srcImg" , 1);
		cvNamedWindow("canImg" , 1);

		cvShowImage("srcImg" , srcImg);
		cvShowImage("canImg" , canImg);

		cvWaitKey();

		cvDestroyWindow("srcImg");
		cvDestroyWindow("canImg");

		cvReleaseImage(&srcImg);
		cvReleaseImage(&canImg);

	}catch(cv::Exception e)
	{
		cout<<e.err.c_str()<<endl;
		if(srcImg)
		{
			cvReleaseImage(&srcImg);
		}
		if(canImg)
		{
			cvReleaseImage(&canImg);
		}
		return;
	}
}

int main(int argc ,char* argv[])
{
  	IplImage* srcImg = NULL;
	IplImage* dstImg = NULL;
	IplImage* resImg = NULL;

	if(argv[1] == NULL)
	{
		string filename = "/Developer/program_for_vim/test_opencv/Lena.jpg";
		cout<<"using the default image"<<endl<<"Airplane"<<endl;
		srcImg = cvLoadImage(filename.c_str() , 1);
	}
	else
	{
		cout<<"using the input image"<<endl;
		srcImg = cvLoadImage(argv[1] , 1);
	}
	
	dstImg = cvCreateImage(cvGetSize(srcImg) , srcImg->depth , 1);
	resImg = cvCreateImage(cvGetSize(srcImg) , srcImg->depth , 1);

	cvCvtColor(srcImg , dstImg , CV_BGR2GRAY);
	cvCopy(dstImg , resImg);

	try{
/*
		guassianProcess(srcImg , dstImg , resImg);
		//sobelProcess(srcImg , dstImg , resImg);

		string file = "./guassian_resImg.jpg";
		string store = "./guassian_can_resImg.jpg";
		canImg(file , store);

		file = "./guassian_dstImg.jpg";
		store = "./normal_can.jpg";
		canImg(file , store);
*/
/*
		std::ostringstream f;
	    f<<argv[1];
		file = f.str();
	 	
		if(strlen(file.c_str()) <= 0)
		{
			cout<<"the image is wrong";
			return -1;
		}
*/
	  	string file = "./guassian_resImg.jpg";

//		splinterImg(file);

		IplImage* src = NULL;
		IplImage* res = NULL;
		
		src = cvLoadImage(file.c_str() , 0);
		res = cvCreateImage(cvGetSize(src) , src->depth , src->nChannels);
/*
		cvCvtColor(srcImg , src , CV_BGR2GRAY);
		cvCvtColor(srcImg , res , CV_BGR2GRAY);
*/
		int h1 = 30;
		int h2 = 180;

		Canny::canny(src , res , h1 , h2 , 3);

	}catch(std::exception e)
	{
		cout<<e.what()<<endl;
		
		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);
		cvReleaseImage(&resImg);

		return -1;
	}
	catch(cv::Exception e)
	{
		cout<<e.err.c_str()<<endl;

		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);
		cvReleaseImage(&resImg);

		return -1;
	}
	
	return 1;
}
