#include"ros/ros.h"
#include"get_data.h"

string txt_id1 = "/home/wzw/workspace/txt_operate_ws/src/txt_operate/src/a.txt";
string txt_id2 = "/home/wzw/workspace/txt_operate_ws/src/txt_operate/src/result/a.txt";

int main()
{
	Txt A;
	A.setData(txt_id1);
	A.correctT();
	A.insertData(2);
	A.correctX(-7.0);
	A.correctY(-3.0);
	
	A.openFile(txt_id2);
	A.writeFile();
	
	cout << "txt operated!" << endl;
	return 0;
}
