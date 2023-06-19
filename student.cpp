#include"student.h"

//默认构造
Student::Student()
{

}

//有参构造
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_name = name;
	this->m_Pwd = pwd;

	//初始化机房容器
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum && ifs >> c.m_RemainNum)
	{
		vCom.push_back(c);
	}
	ifs.close();
}

//菜单界面
void Student::operMenu()
{
	cout << "欢迎学生代表：" << this->m_name << "登录！" << endl;
	cout << " -----------------------------------------" << endl;
	cout << "|                                         |" << endl;
	cout << "|      1、申请预约                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      2、查看自身预约                    |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      3、查看所有预约                    |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      4、取消预约                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      0、注销登录                        |" << endl;
	cout << "|                                         |" << endl;
	cout << " -----------------------------------------" << endl;
	cout << "请选择您的操作" << endl;
}

//申请预约
void Student::applyOrder()
{
	cout << "机房开放时间为周一到周五" << endl;
	cout << "请输入申请预约的时间" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;

	int date = 0;//日期
	int interval = 0;//时间段
	int room = 0;//机房编号
	int ComputerNumber;//需要的电脑数量

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "请输入申请预约时间段" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "请选择机房" << endl;
	cout << vCom[0].m_ComId << "号机房容量为：" << vCom[0].m_MaxNum << " 剩余可预约数：" << vCom[0].m_RemainNum << endl;
	cout << vCom[1].m_ComId << "号机房容量为：" << vCom[1].m_MaxNum << " 剩余可预约数：" << vCom[1].m_RemainNum << endl;
	cout << vCom[2].m_ComId << "号机房容量为：" << vCom[2].m_MaxNum << " 剩余可预约数：" << vCom[2].m_RemainNum << endl;

	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			cout << "请输入您要预约的电脑数量：" << endl;
			cin >> ComputerNumber;
			while (true)
			{
				if (vCom[room - 1].m_RemainNum >= ComputerNumber)
				{
					break;
				}
				if (vCom[room - 1].m_RemainNum < ComputerNumber)
				{
					cout << "抱歉，机房已满或容量不足，请重新选择容量或机房" << endl;
					cout << "是否返回上一步重新选择机房，不返回则重新选择预约数量" << endl;
					cout << "1、返回" << endl;
					cout << "2、重新选择预约数量" << endl;
					int tempSelect;
					cin >> tempSelect;
					if (tempSelect == 2)
					{
						cout << "请输入您要预约的电脑数量：" << endl;
						cin >> ComputerNumber;
					}
					else if (tempSelect == 1)
					{
						cout << "请选择机房" << endl;
						cout << vCom[0].m_ComId << "号机房容量为：" << vCom[0].m_MaxNum << " 剩余可预约数：" << vCom[0].m_RemainNum << endl;
						cout << vCom[1].m_ComId << "号机房容量为：" << vCom[1].m_MaxNum << " 剩余可预约数：" << vCom[1].m_RemainNum << endl;
						cout << vCom[2].m_ComId << "号机房容量为：" << vCom[2].m_MaxNum << " 剩余可预约数：" << vCom[2].m_RemainNum << endl;
						cin >> room;
						cout << "请输入您要预约的电脑数量：" << endl;
						cin >> ComputerNumber;
					}
				}

			}
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "预约成功！审核中" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "ReqNum:" << ComputerNumber << endl;
	ofs << "status:" << 1 << " ";


	ofs.close();

	system("pause");
	system("cls");
}

//查看自身预约
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		//string 转int 
		//string 利用  .c_str() 转const char*
		//再利用atoi(const char*) 转int 
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			cout << "预约日期: 周" << of.m_orderData[i]["date"];
			cout << " 时段:" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房:" << of.m_orderData[i]["roomId"];
			cout << " 预约数量:" << of.m_orderData[i]["ReqNum"];
			string status = "状态: ";//0取消的预约  1  审核中   2 预约成功  -1预约失败
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "预约失败";
			}
			else
			{
				status += "预约已取消";
			}
			cout << " " << status << endl;
		}
	}
	system("pause");
	system("cls");
}

//查看所有预约
void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、";

		cout << "预约日期： 周" << of.m_orderData[i]["date"];
		cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号：" << of.m_orderData[i]["stuId"];
		cout << " 姓名：" << of.m_orderData[i]["stuName"];
		cout << " 机房：" << of.m_orderData[i]["roomId"];
		cout << "预约数量：" << of.m_orderData[i]["ReqNum"];
		string status = "状态：";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << " " << status << endl;

	}
	system("pause");
	system("cls");
}

//取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;

	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";
				cout << " 预约日期：周" << of.m_orderData[i]["date"];
				cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房：" << of.m_orderData[i]["roomId"];
				string status = "状态：";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << " " << status << endl;
			}
		}
	}
	cout << "请输入取消的记录，0表示返回" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}
