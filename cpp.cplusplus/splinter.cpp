#include <iostream>
#include "opencv.h"
#include "splinter.h"
#include <fstream>

using namespace cv;
using namespace std;

using std::cout;
using std::endl;
using std::ostringstream;
using std::ofstream;

void splinterImg(string filename)
{
	IplImage* srcImg = NULL;
	IplImage* dstImg = NULL;
	IplImage* resImg = NULL;

	ostringstream out;

	std::ofstream errorLog;
	vector<float> threshold(0 , 4);
	vector<CvScalar> summerize(255);
	
	threshold[0] = 0;
	threshold[1] = 128.0;
	threshold[2] = 192.0;
	threshold[3] = 255.0;

	CvScalar sca;
	Mat tmpB , tmpG , tmpR , rMat , gMat , bMat;

	int eigen = 3;

	try{
		srcImg = cvLoadImage(filename.c_str() , 1);

		dstImg = cvCreateImage(cvGetSize(srcImg) , srcImg->depth , srcImg->nChannels);
		resImg = cvCreateImage(cvGetSize(srcImg) , srcImg->depth , srcImg->nChannels);

		//cvCopy(srcImg , dstImg);

		int width = srcImg->width;
		int height = srcImg->height;	
		
		tmpB= cvCreateMat(eigen , eigen , CV_32F);
		tmpG = cvCreateMat(eigen , eigen , CV_32F);
		tmpR = cvCreateMat(eigen , eigen , CV_32F);

		bMat = cvCreateMat(height , width , CV_32F);
		gMat = cvCreateMat(height , width , CV_32F);
		rMat = cvCreateMat(height , width , CV_32F);

		for(int i = 0;i<height;++i)
		{
			for(int j = 0;j<width;++j)
			{
				sca = cvGet2D(srcImg , i , j);

				sca.val[1] = 0;
				sca.val[2] = 0;
				sca.val[3] = 0;
				
				cvSet2D(dstImg ,i , j , sca);
				bMat.ptr<float>(i)[j] = static_cast<float>(sca.val[0]);

			}
		}

		cvSaveImage("./splinterBImg.jpg" , dstImg);

		for(int i = 0;i<height;++i)
		{
			for(int j = 0;j<width;++j)
			{
				sca = cvGet2D(srcImg ,i , j);

				sca.val[0] = 0;
				sca.val[2] = 0;
				sca.val[3] = 0;

				cvSet2D(dstImg , i , j ,sca);
				gMat.ptr<float>(i)[j] = static_cast<float>(sca.val[1]);
			}
		}

		cvSaveImage("./splinterGImg.jpg" , dstImg);

		for(int i = 0;i<height;++i)
		{
			for(int j = 0;j<width;++j)
			{
				sca = cvGet2D(srcImg , i , j);

				sca.val[0] = 0;
				sca.val[1] = 0;
				sca.val[3] = 0;

				cvSet2D(dstImg , i , j ,sca);
				rMat.ptr<float>(i)[j] = static_cast<float>(sca.val[2]);

			}
		}

		cvSaveImage("./splinterRImg.jpg" , dstImg);

		//indeBGR:
		
		for(int i = 0;i<height;++i)
		{
			for(int j = 0;j<width;++j)
			{
				sca = cvGet2D(dstImg , i ,j);
/*
				int valB = static_cast<int>(sca.val[0]);
				int valG = static_cast<int>(sca.val[1]);
				int valR = static_cast<int>(sca.val[2]);
*/
				sca.val[3] = 0;

				int k = 0;
				while(k < 3)
				{
					if((sca.val[k] > 0)&&(sca.val[k] <= 64))
					{
						sca.val[k] = 64;
					}
					else if((sca.val[k] > 64)&&(sca.val[k] <= 128))
					{
						sca.val[k] = 128;
					}
					else if((sca.val[k] > 128)&&(sca.val[k] <= 192))
					{
						sca.val[k] = 192;
					}
					else if((sca.val[k] > 192)&&(sca.val[k] <= 255))
					{
						sca.val[k] = 255;
					}
					else 
					{
						sca.val[k] = 255;
					}
				}

				cvSet2D(resImg , i , j , sca);

				cvSaveImage("./indeBGR.jpg" , resImg);

			}
		}

	    //summerize:
	    
		vector<CvScalar>::iterator i = summerize.begin();
		CvScalar tmp;
		
		tmp.val[0] = 0;
		tmp.val[1] = 0;
		tmp.val[2] = 0;
		tmp.val[3] = 1;

		for(int i = 0;i<height;++i)
		{
			for(int j = 0;j<width;++j)
			{
				sca = cvGet2D(dstImg , i , j);
				
				int valB = static_cast<int>(sca.val[0]);
				int valG = static_cast<int>(sca.val[1]);
				int valR = static_cast<int>(sca.val[2]);
				sca.val[3] = 0;

				int index = 0;
				
				index = (valB + valG + valR)%255;
				
				if(summerize[index].val[3] > 1)
				{
					summerize[index].val[3] = summerize[index].val[3] + 1;
				}
				else if(summerize[index].val[3] == 1)
				{
					summerize[index].val[0] = sca.val[0];
					summerize[index].val[1] = sca.val[1];
					summerize[index].val[2] = sca.val[2];
				}

			}
		}
		
		ofstream outData;
		ostringstream out;

		outData.open("./outData.txt");

	    for(int i = 0;i<255;++i)
		{
		 	tmp.val[0] = 0;
			tmp.val[1] = 0;
			tmp.val[2] = 0;
			tmp.val[3] = 0;

			tmp = summerize[i];

			out<<"B: "<<tmp.val[0]<<"G: "<<tmp.val[1]<<"R: "<<tmp.val[2]<<"sum: "<<tmp.val[3]<<endl;
			
			string data = out.str();
			outData.write(data.c_str() , strlen(data.c_str()));
			data.clear();
		}
	
		outData.close();

/*
		for(int i = 1;i<height;++i)
		{
			for(int j = 1;j<width;++j)
			{
				float b = bMat.ptr<float>(i)[j];
				float g = gMat.ptr<float>(i)[j];
				float r = rMat.ptr<float>(i)[j];

				for(int p = 0;p<3;++p)
				{
					for(int k = 0;k<3;++k)
					{
					  	int row = p + i - 1;
						int col = k + j - 1;

						tmpB.ptr<float>(p)[k] = bMat.ptr<float>(row)[col];					
						tmpG.ptr<float>(p)[k] = gMat.ptr<float>(row)[col];					
						tmpR.ptr<float>(p)[k] = rMat.ptr<float>(row)[col];	

					}
				}						

			}
		}
*/

			

	}catch(std::exception e)
	{
		out<<e.what();
		
		errorLog.open("./errorLog.txt");
		errorLog.write(out.str().c_str() , 256);
		errorLog.close();

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
		if(rMat.empty() == false)
		{
			rMat.release();
		}
		if(gMat.empty() == false)
		{
			gMat.release();
		}
		if(bMat.empty() == false)
		{
			bMat.release();
		}
		return;
	}


}

