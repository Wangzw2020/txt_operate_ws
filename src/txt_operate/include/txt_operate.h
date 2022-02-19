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
	void setData(string& file_position);
	void writeFile();
	
	void start_time_to_zero();
	void insertData(int num);
	void correctT();
	void correctX(double dx);
	void correctY(double dy);
	void correctVx(double dvx);
	void correctVy(double dvy);
	
	
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

void Txt::setData(string& file_position)
{
	ifstream file;
	string line;
	file.open(file_position.c_str());
	if(!file)
		cout << "open file failed" << endl;
	while(file.good())
	{
		line_data data;
		getline(file,line);
		if (line.length() == 0)
			break;
		std::stringstream ss(line);
		ss >> data.time >> data.x >> data.y >> data.vx >> data.vy;
		txt_data_.push_back(data);
	}
	file.close();
	cout << "initial data loaded!" << endl;
}

void Txt::insertData(int num)
{
	std::vector<line_data> temp_txt_data;
	for(int i=0; i<txt_data_.size()-1; ++i)
	{
		double dt = (txt_data_[i+1].time - txt_data_[i].time) / (num+1);
		double dx = (txt_data_[i+1].x - txt_data_[i].x) / (num+1);
		double dy = (txt_data_[i+1].y - txt_data_[i].y) / (num+1);
		double dvx = (txt_data_[i+1].vx - txt_data_[i].vx) / (num+1);
		double dvy = (txt_data_[i+1].vy - txt_data_[i].vy) / (num+1);
		temp_txt_data.push_back(txt_data_[i]);
		
		for(int j=0; j<num; ++j)
		{
			line_data data;
			data.time = txt_data_[i].time + dt*(j+1);
			data.x = txt_data_[i].x + dx*(j+1);
			data.y = txt_data_[i].y + dy*(j+1);
			data.vx = txt_data_[i].vx + dvx*(j+1);
			data.vy = txt_data_[i].vy + dvy*(j+1);
			temp_txt_data.push_back(data);
		}
	}
	txt_data_ = temp_txt_data;
}

void Txt::correctT()
{
	double t0 = txt_data_[0].time;
	for(int i=0; i<txt_data_.size(); ++i)
	{
		txt_data_[i].time = txt_data_[i].time - t0;
;	}
}

void Txt::correctX(double dx)
{
	for(int i=0; i<txt_data_.size(); ++i)
	{
		txt_data_[i].x = txt_data_[i].x + dx;
	}
}

void Txt::correctY(double dy)
{
	for(int i=0; i<txt_data_.size(); ++i)
	{
		txt_data_[i].y = txt_data_[i].y + dy;
	}
}

void Txt::correctVx(double dvx)
{
	for(int i=0; i<txt_data_.size(); ++i)
	{
		txt_data_[i].vx = txt_data_[i].vx + dvx;
	}
}

void Txt::correctVy(double dvy)
{
	for(int i=0; i<txt_data_.size(); ++i)
	{
		txt_data_[i].vy = txt_data_[i].vy + dvy;
	}
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
