#include"ros/ros.h"
#include"get_data.h"

//#define dt 0.100000
#define dt 0.0333333

string txt_id_read = "/home/wzw/data/paper_data/-40/ped0_extract_fps30.txt";
string txt_id_write = "/home/wzw/data/paper_data/-40/ped0_extract_fps30_addg.txt";

int main()
{
	Txt A;
	A.setData(txt_id_read);
	//A.correctT();
	//A.insertData(2);
	//A.correctX(-7.0);
	//A.correctY(-3.0);
	
//	A.extractData(dt);
	
	//10
//	A.addGaussian(0.0, 0.05, 1);
//	A.addGaussian(0.0, 0.05, 2);
//	A.addGaussian(0.0, 0.1, 3);
//	A.addGaussian(0.0, 0.1, 4);
	
	//30
	A.addGaussian(0.0, 0.06, 1, 7);
	A.addGaussian(0.0, 0.06, 2, 7);
	A.addGaussian(0.0, 0.1, 3, 4);
	A.addGaussian(0.0, 0.1, 4, 4);
	
	A.writeFile(txt_id_write);
	
	cout << "txt operated!" << endl;
	return 0; 
}
