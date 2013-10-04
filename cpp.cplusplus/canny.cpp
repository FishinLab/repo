#include <iostream>
#include "sobel.h"
#include "opencv.h"
#include <fstream>

using namespace cv;
using namespace std;

using std::cout;
using std::endl;
using std::ostringstream;
using std::ofstream;

void Canny::canny(IplImage* srcImg , IplImage* dstImg , int hold1 , int hold2 , int eigen)
{
	ofstream errorData;

	if((!srcImg)||(!dstImg))
	{	
		errorData.open("./errorLog.txt");

		string errD = "image loaded false";
		cout<<errD<<endl;

		errorData.write(errD.c_str() , strlen(errD.c_str()));
		errorData.close();
		if(srcImg)
		{
			cvReleaseImage(&srcImg);
		}
		if(dstImg)
		{
			cvReleaseImage(&dstImg);
		}


		
		return;
	}

	int chaS = srcImg->nChannels;
	int chaD = dstImg->nChannels;

	if((chaS != 1)||(chaD != 1))
	{
	  	errorData.open("./errorLog.txt");
		string errD = "the image channel number must be 1";
		errorData.write(errD.c_str() , strlen(errD.c_str()));
			
		errorData.close();

		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);
		
	}

	if(hold2 <= hold1)
	{
		errorData.open("./errorLog.txt");

		string errD = "the hold2 must larger than hold1";
		cout<<errD<<endl;

		errorData.write(errD.c_str() , strlen(errD.c_str()));
		errorData.close();
		
		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);

		return;
	}

	if(eigen != 3)
	{
		errorData.open("./errorLog.txt");

		string errD = "the eigen of the operator must be 3";
		cout<<errD<<endl;

		errorData.write(errD.c_str() , strlen(errD.c_str()));
		errorData.close();

		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);

		return;
	}

	CvScalar sca;
	Mat coreS , coreG;
	
	int width = srcImg->width;
	int height = srcImg->height;

	try{
		IplImage* resImg = cvCreateImage(cvGetSize(dstImg) , dstImg->depth , 1);

		coreS = cvCreateMat(eigen , eigen , CV_32F);
		coreG = cvCreateMat(eigen , eigen , CV_32F);

		coreS.ptr<float>(0)[0] = 1;
		coreS.ptr<float>(0)[1] = 3;
		coreS.ptr<float>(0)[2] = 1;
		coreS.ptr<float>(1)[0] = 0;
		coreS.ptr<float>(1)[1] = 0;
		coreS.ptr<float>(1)[2] = 0;
		coreS.ptr<float>(2)[0] = -1;
		coreS.ptr<float>(2)[1] = -3;
		coreS.ptr<float>(2)[2] = -1;

		coreG.ptr<float>(0)[0] = 0; 
		coreG.ptr<float>(0)[1] = 1; 
		coreG.ptr<float>(0)[2] = 0; 
		coreG.ptr<float>(1)[0] = 1; 
		coreG.ptr<float>(1)[1] = 4; 
		coreG.ptr<float>(1)[2] = 1; 
		coreG.ptr<float>(2)[0] = 0; 
		coreG.ptr<float>(2)[1] = 1; 
		coreG.ptr<float>(2)[2] = 0; 

		for(int i = 1;i<height - 1;++i)
		{
			for(int j = 1;j<width - 1;++j)
			{
					
				Mat tmp(eigen , 1 , CV_32F);
				
				sca = cvGet2D(srcImg , i , j);
				tmp.ptr<float>(1)[0] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(srcImg , i - 1 ,j);
				tmp.ptr<float>(0)[0] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(srcImg , i + 1 , j);
				tmp.ptr<float>(2)[0] = static_cast<float>(sca.val[0]);

				float s = tmp.ptr<float>(0)[0]*coreG.ptr<float>(0)[1] + 
				  		  tmp.ptr<float>(1)[0]*coreG.ptr<float>(1)[1] + 
						  tmp.ptr<float>(2)[0]*coreG.ptr<float>(2)[1];

				sca.val[0] = s;
				sca.val[1] = 0;
				sca.val[2] = 0;
				sca.val[3] = 0;

				cvSet2D(dstImg , i , j , sca);

			}
		}
		
		for(int i = 0;i<4;++i)
		{
			sca.val[i] = 0;
		}


		for(int i = 1;i<height - 1;++i)
		{
			for(int j = 1;j<width - 1;++j)
			{
			 	sca = cvGet2D(dstImg , i , j);
				float v = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i , j - 1);
				float before = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i , j + 1);
				float after = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i - 1 , j);
				float up = static_cast<float>(sca.val[0]);

				sca = cvGet2D(dstImg , i + 1 , j);
				float down = static_cast<float>(sca.val[0]);

				vector<float>around(4);
				around.push_back(up);
				around.push_back(down);
				around.push_back(before);
				around.push_back(after);

				//vector<float>::iterator a = around.begin();
				
				int k = 0;
				while(k < 4)
				{
					if(((int)abs(up - v) < hold2)||((int)abs(down - v) < hold2)||((int)abs(before - v) < hold2)||((int)abs(after - v) < hold2))
					{
						sca.val[0] = (up + down + after + before)/4;
					}
					else sca.val[0] = 0;
					k++;
				}

				cvSet2D(resImg , i , j , sca);
/*
				int k = 0;
				while(k < 4)
				{
					if((int)abs(*a - v) >= hold2)
					{
						sca.val[0] = 255;
						cvSet2D(resImg , i , j ,sca);
						k = 4;
					}
					else
					{
						sca.val[0] = 0;
						cvSet2D(resImg , i , j , sca);
					}
					a++;
					k++;
				}
*/
/*				
				do
				{
					if(abs(*a - v) >= hold2)
					{
						sca.val[0] = 255;
						cvSet2D(resImg , i , j , sca);
						a = around.end();
					}
					else{
						sca.val[0] = 0;
						cvSet2D(resImg , i  , j , sca);
					}
					a++;
				}
				while(a != around.end());
*/
/*
				while(a != around.end())
				{
					if(abs(*a - v) >= hold2)
					{
						sca.val[0] = 0;
						cvSet2D(resImg , i , j , sca);

					}
					a++;
				}
*/

			}
		}

		cvSaveImage("./resImg.jpg" , resImg);

		cvNamedWindow("canny_img.jpg" , 1);
		cvShowImage("canny_img.jpg" , resImg);

		cvWaitKey();

		cvDestroyWindow("canny_img.jpg");
		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);
		cvReleaseImage(&resImg);


	}
	catch(cv::Exception e)
	{
		errorData.open("./errorLog.txt");
		errorData.write(e.err.c_str() , strlen(e.err.c_str()));

		cout<<e.err.c_str()<<endl;

		errorData.close();
		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);
	}
	catch(std::exception e)
	{
		errorData.open("./errorLog.txt");
		errorData.write(e.what() , strlen(e.what()));

		cout<<e.what()<<endl;

		errorData.close();
		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);
	}

}

void Smooth::smooth(IplImage* srcImg , IplImage* dstImg)
{
  	ofstream errorLog;

	if((!srcImg)||(dstImg))
	{
		string errD = "the image is not loaded";
		cout<<errD<<endl;

		errorLog.open("./errorLog.txt");
		errorLog.write(errD.c_str() , strlen(errD.c_str()));

		errorLog.close();

		if(srcImg)
		{
			cvReleaseImage(&srcImg);
		}
		if(dstImg)
		{
			cvReleaseImage(&dstImg);
		}
		return;
	}

	if((srcImg->nChannels != 1)||(dstImg->nChannels != 1))
	{
		string errD = "the image channel is not 1";
		cout<<errD.c_str()<<endl;

		errorLog.open("./errorLog.txt");
		errorLog.write(errD.c_str() , strlen(errD.c_str()));

		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);
	}

	CvScalar sca;
	int width = srcImg->width;
	int height = srcImg->height;

	try{
		Mat tmp(3 , 3 , CV_32F);

		for(int i = 1;i<height - 1;++i)
		{
			for(int j = 1;j<width - 1;++j)
			{
				sca = cvGet2D(srcImg , i-1 , j-1);
				tmp.ptr<float>(0)[0] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(srcImg , i-1 , j);
				tmp.ptr<float>(0)[1] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(srcImg , i-1 , j+1);
				tmp.ptr<float>(0)[2] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(srcImg , i , j-1);
				tmp.ptr<float>(1)[0] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(srcImg , i , j);
				tmp.ptr<float>(1)[1] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(srcImg , i , j+1);
				tmp.ptr<float>(1)[2] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(srcImg , i+1 , j-1);
				tmp.ptr<float>(2)[0] = static_cast<float>(sca.val[0]);

				sca = cvGet2D(srcImg , i+1 , j);
				tmp.ptr<float>(2)[1] = static_cast<float>(sca.val[0]);
				
				sca = cvGet2D(srcImg , i+1 , j+1);
				tmp.ptr<float>(2)[2] = static_cast<float>(sca.val[0]);

				float mean = tmp.ptr<float>(0)[0] + 
				  			 tmp.ptr<float>(0)[1] +
				  			 tmp.ptr<float>(0)[2] +
				  			 tmp.ptr<float>(1)[0] +
				  			 tmp.ptr<float>(1)[1] +
				  			 tmp.ptr<float>(1)[2] +
				  			 tmp.ptr<float>(2)[0] +
				  			 tmp.ptr<float>(2)[1] +
				  			 tmp.ptr<float>(2)[2];

				sca = cvGet2D(srcImg , i , j);
				sca.val[0] = static_cast<double>(mean);

				cvSet2D(dstImg , i , j , sca);

			}
		}
/*

		Mat srcMat(height , width , CV_32F);
		cvarrToMat(srcImg , srcMat);

		for(int i = 1;i<height - 1;++i)
		{
			for(int j = 1;j<width - 1;++j)
			{
				float mean = srcMat.ptr<float>(i - 1)[j - 1] +
				  		   srcMat.ptr<float>(i - 1)[j] +
				  		   srcMat.ptr<float>(i - 1)[j + 1] +
				  		   srcMat.ptr<float>(i)[j - 1] +
				  		   srcMat.ptr<float>(i)[j] +
				  		   srcMat.ptr<float>(i)[j + 1] +
				  		   srcMat.ptr<float>(i + 1)[j - 1] +
				  		   srcMat.ptr<float>(i + 1)[j] +
				  		   srcMat.ptr<float>(i + 1)[j + 1];

				sca.val[0] = static_cast<float>(mean);
				cvSet2D(dstImg , i , j , sca);
			}
		}

*/

		cvSaveImage("./smooth_normal.jpg" , dstImg);
		cvNamedWindow("smooth" , 1);

		cvShowImage("smooth" , dstImg);

		cvWaitKey();

		cvDestroyWindow("smooth");
		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);


	}
	catch(cv::Exception e)
	{
		errorLog.open("./errorLog.txt");
		errorLog.write(e.err.c_str() , strlen(e.err.c_str()));
		errorLog.close();

		cout<<e.err.c_str();
		return;
	}
	catch(std::exception e)
	{
		errorLog.open("./errorLog.txt");
		errorLog.write(e.what() , strlen(e.what()));
		errorLog.close();

		cout<<e.what()<<endl;
		return;
	}
	
}

void Smooth::smThreshold(IplImage* srcImg , IplImage* dstImg , int th)
{
	ofstream errorLog;

	if((!srcImg)||(!dstImg))
	{
		string errD = "image is not loaded";
		cout<<errD.c_str()<<endl;

		errorLog.open("./errorLog.txt");
		errorLog.write(errD.c_str() , strlen(errD.c_str()));
		errorLog.close();

		if(srcImg)
		{
			cvReleaseImage(&srcImg);
		}
		if(dstImg)
		{
			cvReleaseImage(&dstImg);
		}
		return;
	}

	if(th <= 0)
	{
		string errD = "the threshold must larger than zero";
		cout<<errD.c_str()<<endl;

		errorLog.open("./errorLog.txt");
		errorLog.write(errD.c_str() , strlen(errD.c_str()));
		errorLog.close();

		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);

		return;
	}

	CvScalar sca;
	int width = srcImg->width;
	int height = srcImg->height;

	try{

/*
		for(int i = 1;i<height - 1;++i)
		{
			for(int j = 1;j<width - 1;++j)
			{
				Mat tmp(3 , 3, CV_32F);

				sca = cvGet2D(srcImg , i - 1 , j - 1);
				tmp.ptr<float>(i - 1)[j - 1] = static_cast<float>(sca.val[0]);
				
				sca = cvGet2D(srcImg , i - 1 , j);
				tmp.ptr<float>(i - 1)[j] = static_cast<float>(sca.val[0]);
				
				sca = cvGet2D(srcImg , i - 1 , j + 1);
				tmp.ptr<float>(i + 1)[j + 1] = static_cast<float>(sca.val[0]);
				
				sca = cvGet2D(srcImg , i , j - 1);
				tmp.ptr<float>(i)[j - 1] = static_cast<float>(sca.val[0]);
				
				sca = cvGet2D(srcImg , i , j);
				tmp.ptr<float>(i)[j] = static_cast<float>(sca.val[0]);
				
				sca = cvGet2D(srcImg , i , j + 1);
				tmp.ptr<float>(i)[j + 1] = static_cast<float>(sca.val[0]);
				
				sca = cvGet2D(srcImg , i + 1 , j - 1);
				tmp.ptr<float>(i + 1)[j - 1] = static_cast<float>(sca.val[0]);
				
				sca = cvGet2D(srcImg , i + 1 , j);
				tmp.ptr<float>(i + 1)[j - 1] = static_cast<float>(sca.val[0]);
				
				sca = cvGet2D(srcImg , i + 1 , j + 1);
				tmp.ptr<float>(i + 1)[j + 1] = static_cast<float>(sca.val[0]);
			
				int mean = 0;
				for(int p = 0;p<3;++p)
				{
					for(int k = 0;k<3;++k)
					{
						if(tmp.ptr<float>(p)[k] < th)
						{
							tmp.ptr<float>(p)[k] = 0;
						}

						mean = tmp.ptr<float>(p)[k] + mean;
					}
				}
				sca.val[0] = mean;
				sca.val[1] = 0;
				sca.val[2] = 0;
				sca.val[3] = 0;

			}
		}
*/


	  	Mat srcMat(height , width , CV_32F);
	 	srcMat = cvarrToMat(srcImg);

	  	for(int i = 1;i<height - 1;++i)
	  	{
	  		for(int j = 1;j<width - 1;++j)
		  	{
				int mean = 0;

				if(srcMat.ptr<float>(i - 1)[j - 1] >= th)
				{
					mean = mean + srcMat.ptr<float>(i - 1)[j - 1];
				}
				if(srcMat.ptr<float>(i - 1)[j] >= th)
				{
					mean = mean + srcMat.ptr<float>(i - 1)[j];
				} 
				if(srcMat.ptr<float>(i - 1)[j + 1] >= th)
				{
					mean = mean + srcMat.ptr<float>(i - 1)[j + 1];
				}
				if(srcMat.ptr<float>(i)[j - 1] >= th)
				{
					mean = mean + srcMat.ptr<float>(i)[j - 1];
				}
				if(srcMat.ptr<float>(i)[j] >= th)
				{
					mean = mean + srcMat.ptr<float>(i)[j];
				}
				if(srcMat.ptr<float>(i)[j + 1] >= th)
				{
					mean = mean + srcMat.ptr<float>(i)[j + 1];
				}
				if(srcMat.ptr<float>(i + 1)[j - 1] >= th)
				{
					mean = mean + srcMat.ptr<float>(i + 1)[j - 1];
				}
				if(srcMat.ptr<float>(i + 1)[j] >= th)
				{
					mean = mean + srcMat.ptr<float>(i + 1)[j];
				}
				if(srcMat.ptr<float>(i + 1)[j + 1] >= th)
				{
					mean = mean + srcMat.ptr<float>(i + 1)[j + 1];
				}

				sca.val[0] = mean;
				sca.val[1] = 0;
				sca.val[2] = 0;
				sca.val[3] = 0;
				cvSet2D(dstImg , i , j , sca);
			}
	  	}

		cvSaveImage("./smThreshold.jpg" , dstImg);
		cvNamedWindow("smThreshold" , 1);

		cvShowImage("smThreshold" , dstImg);
		
		cvWaitKey();

		cvDestroyWindow("smThreshold");
		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);

		srcMat.release();

	}
	catch(cv::Exception e)
	{
		errorLog.open("./errorLog.txt");
		errorLog.write(e.err.c_str() , strlen(e.err.c_str()));
		errorLog.close();

		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);
	}
	catch(std::exception e)
	{
		errorLog.open("./errorLog.txt");
		errorLog.write(e.what() , strlen(e.what()));
		errorLog.close();

		cvReleaseImage(&srcImg);
		cvReleaseImage(&dstImg);
	}

}
