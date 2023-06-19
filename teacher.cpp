#include"teacher.h"



//默认构造
Teacher::Teacher()
{

}

//有参构造
Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
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
void Teacher::operMenu()
{
	cout << "欢迎教师：" << this->m_name << "登录！" << endl;
	cout << " -----------------------------------------" << endl;
	cout << "|                                         |" << endl;
	cout << "|      1、查看所有预约                    |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      2、审核预约                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      3、查看机房信息                    |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      0、注销登录                        |" << endl;
	cout << "|                                         |" << endl;
	cout << " -----------------------------------------" << endl;
	cout << "请选择您的操作" << endl;
}

//查看所有预约
void Teacher::showAllOrder()
{
	/*OrderFile of;
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
	system("cls");*/
	Student().showAllOrder();
}

//审核预约
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "待审核预约记录如下：" << endl;

	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{

		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << index++ << "、";
			cout << " 预约日期：周" << of.m_orderData[i]["date"];
			cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房：" << of.m_orderData[i]["roomId"];
			cout << " 预约人：" << of.m_orderData[i]["stuName"];
			cout << " 预约电脑数量：" << of.m_orderData[i]["ReqNum"];
			string status = "状态：审核中";
			cout << " " << status << endl;
		}

	}
	cout << "请输入要审核的记录，0表示返回" << endl;
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
				cout << "请输入审核情况：2表示通过，-1表示不通过" << endl;
				string newstatus;
				cin >> newstatus;
				of.m_orderData[v[select - 1]]["status"] = newstatus;
				of.updateOrder();//更新预约状态
				cout << "审核完毕！" << endl;
				//更新机房信息
				if (newstatus == "2")
				{
					int comNum = atoi(of.m_orderData[v[select - 1]]["roomId"].c_str());
					vCom[comNum - 1].m_RemainNum = vCom[comNum - 1].m_RemainNum - atoi(of.m_orderData[v[select - 1]]["ReqNum"].c_str());
					ofstream ofs(COMPUTER_FILE, ios::out | ios::trunc);
					for (int i = 0; i < 3; i++)
					{
						ofs << vCom[i].m_ComId << " " << vCom[i].m_MaxNum << " " << vCom[i].m_RemainNum << endl;
					}
					ofs.close();
				}
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}

//查看机房信息
void Teacher::showComputer()
{
	cout << "机房信息如下：" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout << " 机房编号:" << vCom[i].m_ComId << " 机房最大容量:" << vCom[i].m_MaxNum << " 机房剩余容量："
			<< vCom[i].m_RemainNum << endl;

	}
	system("pause");
	system("cls");
}