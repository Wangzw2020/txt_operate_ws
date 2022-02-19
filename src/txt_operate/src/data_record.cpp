#include"ros/ros.h"
#include"get_data.h"

string txt_id = "/home/wzw/workspace/txt_operate_ws/src/txt_operate/src/b.txt";

int main(int argc, char** argv)
{
	ros::init(argc, argv, _NODE_NAME_);
	Get_data A;
	A.init();
	ros::spin();
	
	if (A.getAllData())
	{
		Txt B;
		B.openFile(txt_id);
		B.setData(A.getData());
		B.writeFile();
	}
	
	return 0;
}
