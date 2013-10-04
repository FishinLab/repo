#include "opencv.h"
#include <iostream>
#include "sobel.h"

using namespace std;
using namespace cv;

void Sobel::generateCore(int coreType)
{
  	int width , height;

	if(coreType == 1)
	{
		cout<<"generate core witch eigen is 1 has no means"<<endl;
		
		width = 1;
		height = 1;

		cv::Mat core(1 , 1 , CV_32F);

		core.ptr<int>(0)[0] = 1;
		
		SobelCore = core;
		eigen = 1;

		core.release();
		return;
	}
	else if(coreType == 3)
	{
		width = 3;
		height = 3;

		cv::Mat core(3 , 3 , CV_32F);
		
		core.ptr<int>(0)[0] = -1;
		core.ptr<int>(0)[1] = -2;
		core.ptr<int>(0)[2] = -1;
		core.ptr<int>(1)[0] = 0;
		core.ptr<int>(1)[1] = 0;
		core.ptr<int>(1)[2] = 0;
		core.ptr<int>(2)[0] = 1;
		core.ptr<int>(2)[1] = 2;
		core.ptr<int>(2)[2] = 1;

		SobelCore = core;
		eigen = 3;

		core.release();
		return;
	}
	else if(coreType == 5)
	{
	
	}
	else if(coreType == 7)
	{
	
	}
	else{
		cout<<"the core of sobel operator only in 1 , 3 , 5 , 7"<<endl;
		return;
	}
}

void Sobel::latitude(cv::Mat core)
{
	if(core.cols == 1)
	{
		cout<<"the core is 1 eigen , no need to get this transform"<<endl;
	}
	else if(core.cols == 3)
	{
		if(core.ptr<int>(1)[2] != 0)
		{
			int width = core.rows;
			int height = core.cols;

			Mat coreL(height , width , CV_32F);

			for(int i = 0;i<height;++i)
			{
				for(int j = 0;j<width;++j)
				{
					coreL.ptr<int>(j)[i] = core.ptr<int>(i)[j];
				}
			}

			SobelCore = coreL;
			eigen = 3;

			coreL.release();
			core.release();
		}
		else 
		{
			cout<<"the core is already latitude"<<endl;
		}

	}
}

void Sobel::matitude(cv::Mat core)
{
	if(core.cols == 1)
	{
		cout<<"here the core eigen is 1, no need this transform"<<endl;
		return;
	}
	else if(core.cols == 3)
	{
		if(core.ptr<int>(1)[2] == 0)
		{
			int width = core.rows;
			int height = core.cols;

			Mat coreM(height , width ,CV_32F);

			for(int i = 0;i<height;++i)
			{
				for(int j = 0;j<width;++j)
				{
					coreM.ptr<int>(j)[i] = core.ptr<int>(i)[j];
				}
			}
			
			SobelCore = coreM;
			eigen = 3;

			coreM.release();
			core.release();

		}
		else{
			cout<<"here the core is already matitude"<<endl;
			return;
		}
	}

}


int getEigen(Mat core)
{
	return core.rows;
}

Mat Sobel::outMat()
{
	return SobelCore;
}

void guassianCore::generateCore(int coreType)
{
	if(coreType != 3)
	{
		cout<<"core type is only 3"<<endl;
		return;
	}
	Mat core(coreType , coreType , CV_32F);
	
	core.ptr<int>(0)[0] = 0;
	core.ptr<int>(0)[1] = 1;
	core.ptr<int>(0)[2] = 0;
	core.ptr<int>(1)[0] = 1;
	core.ptr<int>(1)[1] = -4;
	core.ptr<int>(1)[2] = 1;
	core.ptr<int>(2)[0] = 0;
	core.ptr<int>(2)[1] = 1;
	core.ptr<int>(2)[2] = 0;
	
	GuassianCore = core;

	core.release();

}

int guassianCore::getEigen()
{
	return GuassianCore.cols;
}

Mat guassianCore::outMat()
{
	return GuassianCore;
}
