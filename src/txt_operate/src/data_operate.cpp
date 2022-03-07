#include"ros/ros.h"
#include"get_data.h"

//#define dt 0.100000
//#define dt 0.0333333

string txt_id_read = "/home/wzw/data/paper_data/ped_go_new/ped0_extract_fps10.txt";
string txt_id_write = "/home/wzw/data/paper_data/ped_go_new/ped0_extract_fps10_high.txt";

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
	A.addGaussian(0.0, 0.05, 1);
	A.addGaussian(0.0, 0.05, 2);
	A.addGaussian(0.0, 0.1, 3);
	A.addGaussian(0.0, 0.1, 4);

//	A.addGaussian(0.0, 0.03, 1);
//	A.addGaussian(0.0, 0.03, 2);
//	A.addGaussian(0.0, 0.08, 3);
//	A.addGaussian(0.0, 0.08, 4);
	
	//30
//	A.addGaussian(0.0, 0.06, 1, 7);
//	A.addGaussian(0.0, 0.06, 2, 7);
//	A.addGaussian(0.0, 0.1, 3, 4);
//	A.addGaussian(0.0, 0.1, 4, 4);

//	A.addGaussian(0.0, 0.08, 1, 7);
//	A.addGaussian(0.0, 0.08, 2, 7);
//	A.addGaussian(0.0, 0.11, 3, 5);
//	A.addGaussian(0.0, 0.11, 4, 5);
	
//	A.addGaussian_with_delay_change(0.0, 0.06, 1, 7);
//	A.addGaussian_with_delay_change(0.0, 0.06, 2, 7);
//	A.addGaussian_with_delay_change(0.0, 0.1, 3, 5);
//	A.addGaussian_with_delay_change(0.0, 0.1, 4, 5);
	
	A.writeFile(txt_id_write);
	
	cout << "txt operated!" << endl;
	return 0; 
}
