#ifndef TXT_OPERATE_H
#define TXT_OPERATE_H
#include<iostream>
#include<fstream>
#include<vector>
#include"ros/ros.h"

using namespace std;

struct line_data{
	double time;
	double x;
	double y;
	double vx;
	double vy;
};

class Txt{
private:
	fstream txt_;
	std::vector<line_data> txt_data_;
public:
	Txt();
	~Txt();
	void openFile(string& file_position);
	void setData(std::vector<line_data> data);
	void writeFile();
	
	std::vector<line_data> getData() { return txt_data_; }
};

void Txt::openFile(string& file_position)
{
	txt_.open(file_position.c_str());
	if (!txt_)
		cout << "open " << file_position << " failed!" << endl;
}

Txt::Txt()
{

}

Txt::~Txt()
{
	txt_.close();
}

void Txt::setData(std::vector<line_data> data)
{
	txt_data_ = data;
}

void Txt::writeFile()
{
	for(int i=0; i<txt_data_.size(); ++i)
	{
		txt_ << txt_data_[i].time << " " << txt_data_[i].x << " " << txt_data_[i].y << " " 
			 << txt_data_[i].vx << " " << txt_data_[i].vy << " " << endl;
	}
}


#endif
