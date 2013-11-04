#include <iostream>
#include <libusb.h>
#include <fstream>

using namespace std;
using std::cout;
using std::endl;


/*
	static const int controlOut = LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE;
	static const int controlIn = LIBUSB_ENDPOINT_IN|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE;

	static const int HID_GET_REPORT = 0x01;
	static const int HID_SET_REPORT = 0x09;
	static const int HID_REPORT_TYPE_IN = 0x01;
	static const int HID_REPORT_TYPE_OUT = 0x02;
	static const int HID_REPORT_TYPE_FEATURE = 0x03;

	static const int MAX_CONTROL_IN = 2;
	static const int MAX_CONTROL_OUT = 2;

	static const int TIMEOUT = 5000;
	static const int INTERFACE_NUMBER = 0;

void deviceOnIf()
{

	libusb_device **li;
	libusb_device *targetD = NULL;

	libusb_init(NULL);
	int res = libusb_get_device_list(NULL , &li);
	int i = 0;
	
	if(res <= 0)
	{
		cout<<"there is no usb device "<<endl;
		return;
	}

	for(;i<res;i++)
	{
		int addr = libusb_get_device_address(li[i]);

		if(addr == 5)
		{
			targetD = li[i];
		}
	}
	if(!targetD)
	{
		cout<<"warning:JLink is not on"<<endl;
		return;
	}
	cout<<"JLink is on"<<endl;

	libusb_device_descriptor *desc = new libusb_device_descriptor;
	memset(desc , 0 ,1024);

	libusb_get_device_descriptor(targetD, desc);
	cout<<"JLink vendor ID:"<<(int)(desc->idVendor)<<endl;
	cout<<"JLink product ID:"<<(int)(desc->idProduct)<<endl;
	cout<<"JLink class:"<<desc->bDeviceClass<<endl;
	delete desc;

	libusb_exit(NULL);
}

void dataTrans(libusb_device_handle* han)
{
	
	int recieved , sent;
	unsigned char dataIn[MAX_CONTROL_IN];
	unsigned char dataOut[MAX_CONTROL_OUT];
	int res = 0;

	for(int i = 0;i<MAX_CONTROL_OUT;++i)
	{
		dataOut[i] = i + 1;
	}

	sent = libusb_control_transfer(
		han,
//		controlOut,
		LIBUSB_RECIPIENT_INTERFACE,
		(HID_REPORT_TYPE_FEATURE<<8)|0x00,
		INTERFACE_NUMBER,
		0,
		dataOut,
		sizeof(dataOut),
		TIMEOUT
		);

	if(sent >= 0)
	{
		cout<<"data output succeed"<<endl;
		for(int i = 0;i<MAX_CONTROL_OUT;++i)
		{
			cout<<dataOut[i]<<endl;
		}
		recieved = libusb_control_transfer(
			han,
			controlIn,
			HID_GET_REPORT,
			(HID_REPORT_TYPE_FEATURE<<8)|0x00,
			0,
			dataIn,
			MAX_CONTROL_IN,
			TIMEOUT
			);
		if(recieved >= 0)
		{
			cout<<"receive succeed"<<endl;
			for(int i = 0;i<MAX_CONTROL_IN;++i)
			{
				cout<<dataIn[i]<<endl;
			}
		}
		else 
		{
			cout<<"warning: receiving data wrong"<<endl;
			libusb_close(han);
			return;
		}
	}
	else{
		cout<<"warning: sending data wrong"<<endl;
		cout<<"error: "<<sent<<endl;
		libusb_close(han);
		return;
	}

}


int main(int argc , const char* argv[])
{

	int deviceReadyF = -1;

	deviceOnIf();

	libusb_device **li;
	libusb_device *dev;

	libusb_init(NULL);
	
	int res = 0;
	res = libusb_get_device_list(NULL , &li);

	if(res <= 0)
	{
		cout<<"warning:No devices found"<<endl;
		return -1;
	}

	for(int i = 0;i<res;++i)
	{
		int addr = libusb_get_device_address(li[i]);
		if(addr == 5)
		{
			dev = li[i];
		}
	}

	libusb_device_descriptor* desc = new libusb_device_descriptor;
//	memset(desc , 0 ,  1024);

	libusb_get_device_descriptor(dev , desc);
	libusb_device_handle* han;

	han = libusb_open_device_with_vid_pid(NULL , desc->idVendor , desc->idProduct);
	if(!han)
	{
	  	cout<<"warning: No device handle found"<<endl;
		delete desc;
		libusb_exit(NULL);
		return -1;
	}
	
	libusb_detach_kernel_driver(han , INTERFACE_NUMBER);
	res = libusb_claim_interface(han , INTERFACE_NUMBER);

	if(res < 0)
	{
		cout<<"warning: Interface claim error"<<endl;
		libusb_close(han);
		delete desc;
		libusb_exit(NULL);
		return -1;
	}

	deviceReadyF = 1;

	if(deviceReadyF == 1)
	{
		dataTrans(han);

	}

	libusb_release_interface(han , INTERFACE_NUMBER);

	libusb_exit(NULL);
	libusb_close(han);

  	system("date");
	return 0;


}
*/


libusb_device_handle* discover(int vendor , int product)
{
	ofstream errorLog;
	libusb_device** li;

	libusb_init(NULL);

	int cnt = libusb_get_device_list(NULL , &li);
	for(int i = 0;i<cnt;++i)
	{
		libusb_device_descriptor* desc = new libusb_device_descriptor;
		memset(desc , 0 , 128);

		libusb_get_device_descriptor(li[i] , desc);
		cout<<"the "<<i<<" device:"<<endl;
		cout<<"device vendor id: "<<desc->idVendor<<"device product id: "<<desc->idProduct<<endl;

		delete desc;
	}

	libusb_device_handle* han;
	han = libusb_open_device_with_vid_pid(NULL , product , vendor);
	if(!han)
	{
		cout<<"warning:open device wrong"<<endl;
		libusb_free_device_list(li , 1);
		libusb_exit(NULL);

		string err = "error in line:245 , open device error\n";

		errorLog.open("/Developer/program_for_vim/testusb/errorlog.txt");
		errorLog.write(err.c_str() , strlen(err.c_str()));
		errorLog.close();

		return NULL;
	}
	libusb_free_device_list(li , 1);
	libusb_exit(NULL);

	return han;
}

void transData(libusb_device_handle* han)
{
	if(!han)
	{
		string err = "there is no device handle";
			
		cout<<err.c_str()<<endl;
		return ;
	}

	const int inFlag = LIBUSB_ENDPOINT_IN|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE;
	const int outFlag = LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE;

	const int getReport = 0x09;
	const int setReport = 0x19;
	const int reportTypeIn = 0x01;
	const int reportTypeOut = 0x02;
	const int reportTypeFeature = 0x03;

	const int maxIn = 1;
	const int maxOut = 1;

	const int interface = 0;
	const int timeOut = 5000;

	ofstream errorLog;
	int resFlag = -1;

	int ifSent , ifRevieved;
	unsigned char dataOut[maxOut];
	unsigned char dataIn[maxIn];

	libusb_init(NULL);

	libusb_detach_kernel_driver(han , interface);
	resFlag = libusb_claim_interface(han , interface);

	if(resFlag >= 0)
	{
		for(int i = 0;i<maxOut;++i)
		{
			dataOut[i] = 0x01 + i;
		}
		ifSent = libusb_control_transfer(
										han,    		//device handle
										outFlag, 		//Control retuest out flag
										setReport,
										(reportTypeFeature<<8)|0x00,
										0, 								//index
										dataOut,                     //transData
										sizeof(dataOut),
										timeOut
										);
		cout<<"sending data:"<<endl;
		if(ifSent >= 0)
		{
			cout<<"ifSent"<<endl;
		}
		else 
		{
			string err = "error in line: 308\n";

			errorLog.open("/Developer/program_for_vim/testusb/errorlog.txt");
			errorLog.write(err.c_str() , strlen(err.c_str()));
			errorLog.close();

			libusb_release_interface(han , interface);
			libusb_exit(NULL);
			
			return;
		}

		ifRevieved = libusb_control_transfer(
											han,
											inFlag,
											getReport,
											(reportTypeFeature<<8)|0x00,
											interface,
											dataIn,
											maxIn,   	   //when recieving data , make it big
											timeOut
											);
		if(ifRevieved > 0)
		{
			cout<<"ifRevieved"<<endl;
		}
		else
		{
			string err = "recieving data error";

			errorLog.open("/Developer/program_for_vim/testusb/errorlog.txt");
			errorLog.write(err.c_str() , strlen(err.c_str()));
			errorLog.close();

			libusb_release_interface(han , interface);
			libusb_exit(NULL);

			return;
		}
	}
	else 
	{
		cout<<"warning:usb interface wrong"<<endl;

		string err = "error in line 295 , usb interface error\n";

		errorLog.open("/Developer/program_for_vim/testusb/errorlog.txt");
		errorLog.write(err.c_str() , strlen(err.c_str()));
		errorLog.close();

		libusb_release_interface(han , interface);
		libusb_exit(NULL);
		return;
	}

	libusb_release_interface(han , interface);
	libusb_init(NULL);
}

int main(int argc , const char* argv[])
{
	libusb_init(NULL);

	int vendor = 0x2303;
	int product = 0x067b;

	libusb_device_handle* han;
	han = discover(vendor , product);
	transData(han);

	system("date");
	return 1;
}
