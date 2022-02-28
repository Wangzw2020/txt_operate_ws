#ifndef TXT_OPERATE_H
#define TXT_OPERATE_H
#include <iostream>
#include <fstream>
#include <vector>
#include "ros/ros.h"
#include "tools.h"

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
	string save_position_;
	fstream txt_;
	std::vector<line_data> txt_data_;
	
public:
	Txt();
	~Txt();

	void setData(std::vector<line_data> data);
	void setData(string& file_position);
	void writeFile(string& file_position);
	
	void start_time_to_zero();
	void insertData(int num);
	void extractData(double time);
	void correctT();
	void correctX(double dx);
	void correctX(double dx, int start, int end);
	void correctY(double dy);
	void correctY(double dy, int start, int end);
	void correctVx(double dvx);
	void correctVx(double dvx, int start, int end);
	void correctVy(double dvy);
	void correctVy(double dvy, int start, int end);
	
	void addGaussian(double mean, double sigma, int column=-1,  int restrain_step = -1);
	
	std::vector<line_data> getData() { return txt_data_; }
};

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

void Txt::extractData(double time)
{
	std::vector<line_data> txt_data_tmp;
	int k=0;
	for(int i=0; i<txt_data_.size(); ++i)
	{
		if(txt_data_[i].time >= k * time)
		{
			txt_data_tmp.push_back(txt_data_[i]);
			++k;
		}
	}
	txt_data_ = txt_data_tmp;
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

void Txt::correctX(double dx, int start, int end)
{
	for(int i=start-1; i<end-1; ++i)
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

void Txt::correctY(double dy, int start, int end)
{
	for(int i=start-1; i<end-1; ++i)
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

void Txt::correctVx(double dvx, int start, int end)
{
	for(int i=start-1; i<end-1; ++i)
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

void Txt::correctVy(double dvy, int start, int end)
{
	for(int i=0; i<txt_data_.size(); ++i)
	{
		txt_data_[i].vy = txt_data_[i].vy + dvy;
	}
}

void Txt::addGaussian(double mean, double sigma, int column, int restrain_step)
{
	std::vector<line_data> txt_data_tmp;
	txt_data_tmp = txt_data_;
	
	double param;
	
	for(int i=0; i<txt_data_.size(); ++i)
	{
		if(i > restrain_step-1 || restrain_step == -1)
			param = 1.0;
		else
			param = pow(2,restrain_step - i);
		
		if(column == 1 || column == -1)
			txt_data_tmp[i].x += gaussian_noise(mean, sigma * param);
		if(column == 2 || column == -1)
			txt_data_tmp[i].y += gaussian_noise(mean, sigma * param);
		if(column == 3 || column == -1)
			txt_data_tmp[i].vx += gaussian_noise(mean, sigma * param);
		if(column == 4 || column == -1)
			txt_data_tmp[i].vy += gaussian_noise(mean, sigma * param);
	}
	txt_data_ = txt_data_tmp;
}

void Txt::writeFile(string& file_position)
{
	save_position_ = file_position.c_str();
	ofstream txt(save_position_,ios_base::out);
	txt.close();
	txt_.open(save_position_);
	if (!txt_)
		cout << "open " << file_position << " failed!" << endl;
	for(int i=0; i<txt_data_.size(); ++i)
	{
		txt_ << txt_data_[i].time << " " << txt_data_[i].x << " " << txt_data_[i].y << " " 
			 << txt_data_[i].vx << " " << txt_data_[i].vy << " " << endl;
	}
	txt_.close();
}













#endif
