#ifndef GET_DATA_H
#define GET_DATA_H
#include<iostream>
#include<fstream>
#include<vector>
#include"ros/ros.h"
#include"txt_operate.h"
#include <perception_msgs/Obstacle.h>
#include <perception_msgs/ObstacleArray.h>

#define _NODE_NAME_ "get_data"


class Get_data{
private:
	string target_topic_;
	ros::Subscriber sub_target_;
	double obstacle_array_time_, start_time_;
	std::vector<line_data> data_;
	bool get_all_data_;
public:
	bool init();
	
	void recordData(const perception_msgs::ObstacleArray::ConstPtr& obstacles);
	void writeFile();
	bool getAllData() { return get_all_data_; }
	std::vector<line_data> getData() { return data_; }
};

bool Get_data::init()
{
	ros::NodeHandle nh, nh_private("~");
	start_time_ = ros::Time::now().toSec();
	nh_private.param<std::string>("target_topic", target_topic_, "/obstacle_array");
	
	sub_target_ = nh.subscribe(target_topic_, 1, &Get_data::recordData, this);
	get_all_data_ = false;
	return true;
}

void Get_data::recordData(const perception_msgs::ObstacleArray::ConstPtr& obstacles)
{
	get_all_data_ = true;
	obstacle_array_time_ = ros::Time::now().toSec() - start_time_;
	if(obstacles->obstacles.size() == 0)
	{
		cout << "no objects!" << endl;
		return;
	}
	static double t,x,y,vx,vy;
	for(int i=0; i<obstacles->obstacles.size(); ++i)
	{
		const perception_msgs::Obstacle& obs = obstacles->obstacles[i];
		line_data A;
		A.time = obstacle_array_time_;
		A.x = obs.pose.position.x;
		A.y = obs.pose.position.y;
		A.vx = obs.vx;
		A.vy = obs.vy;
		data_.push_back(A);
	}
}
















#endif
