#include "stdafx.h"
#include "opencv2/opencv.hpp"

#include <fstream>  
#include <string>  
#include <iostream>  
using namespace std;
using namespace cv;

int main()
{
	ifstream in("D:\\train_list.txt");
	ofstream outfile;
	outfile.open("record.txt"); //myfile.bat是存放数据的文件名  	
	string filename;
	string line;
	double sum[3] = { 0 };
	int count = 0;

	if (in) // 有该文件  
	{
		while (getline(in, line)) // line中不包括每行的换行符  
		{
			count++;
			cout << line << endl;
			IplImage* input_png;
			input_png=cvLoadImage(line.c_str(), -1);
			CvScalar s;;
			s=cvAvg(input_png);
			for (int i = 0; i < 3; i++) {
				sum[i] += s.val[i];
			}
			cvReleaseImage(&input_png);
			if(count%500==0)
				outfile << count<<" " << sum[0] << " " << sum[1] << " " << sum[2] << endl;    //message是程序中处理的数据  
		}
		if (count != 0) {
			for (int i = 0; i < 3; i++) {
				sum[i]=sum[i]/(double)count;
			}
		}
		cout << count << "pictures computed,the avg is," << sum[0] << " " << sum[1] << " " << sum[2] << " " << endl;
	}

	else // 没有该文件  
	{
		cout << "no such file" << endl;
	}
	outfile.close();

	return 0;
}
