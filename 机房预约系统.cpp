#include<iostream>
using namespace std;
#include"Identity.h"
#include<fstream>
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"

//进入管理员子菜单界面
void manaagerMenu(Identity*& manager)
{
	while (true)
	{
		//调用管理员子菜单
		manager->operMenu();

		//将父类指针转为子类指针，调用子类的其他接口
		Manager* man = (Manager*)manager;

		int select = 0;
		//接收用户的选择
		cin >> select;
		if (select == 1)
		{

			//添加账号
			man->addPerson();
		}
		else if (select == 2)
		{
			//查看账号
			man->showPerson();
		}
		else if (select == 3)
		{
			//查看机房信息
			man->showComputer();
		}
		else if (select == 4)
		{
			//清空预约
			man->cleanFile();
		}
		else
		{
			delete manager;//销毁堆区对象
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

//进入学生子菜单界面
void studentMenu(Identity*& student)
{
	while (true)
	{
		//学生菜单
		student->operMenu();

		Student* stu = (Student*)student;
		int select = 0;

		cin >> select;
		if (select == 1)//申请预约
		{
			stu->applyOrder();
		}
		else if (select == 2)//查看自身预约
		{
			stu->showMyOrder();
		}
		else if (select == 3)//查看所有预约
		{
			stu->showAllOrder();
		}
		else if (select == 4)//取消预约
		{
			stu->cancelOrder();
		}
		else
		{
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//进入教师子菜单界面
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		teacher->operMenu();

		Teacher* tea = (Teacher*)teacher;
		int select = 0;

		cin >> select;
		if (select == 1)
		{
			//查看所有预约
			tea->showAllOrder();
		}
		else if (select == 2)
		{
			//审核预约
			tea->validOrder();
		}
		else if (select == 3)
		{
			//查看机房信息
			tea->showComputer();
		}
		else
		{
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

}

//登录功能  参数1  操作文件名 参数2  操作身份类型
void LoginIn(string fileName, int type)
{
	//父类指针，指向子类对象
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//准备接受用户的信息
	int id = 0;
	string name;
	string pwd;

	//判断身份
	if (type == 1)//学生身份
	{
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	if (type == 2)//老师身份
	{
		cout << "请输入你的职工号：" << endl;
		cin >> id;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//学生身份验证
		int fId;//文件中读取的id号
		string fName; //文件中获取的姓名
		string fPwd;  //文件中获取的密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//进入学生身份的子菜单
				studentMenu(person);

				return;
			}
		}
	}
	else if (type == 2)
	{
		//教师身份验证
		int fId;//文件中读取的id号
		string fName; //文件中获取的姓名
		string fPwd;  //文件中获取的密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入教师身份的子菜单
				teacherMenu(person);

				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员身份验证
		string fName; //文件中获取的姓名
		string fPwd;  //文件中获取的密码
		while (ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//进入管理员身份的子菜单

				manaagerMenu(person);
				return;
			}
		}
	}

	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");


}

//创建身份类为基类，子类有学生、教师、管理员

int main()
{

	int select = 0;//用于接收用户的选择

	while (true)
	{
		cout << "欢迎使用机房预约系统！" << endl;
		cout << " -----------------------------------------" << endl;
		cout << "|                                         |" << endl;
		cout << "|      1、学生登陆                        |" << endl;
		cout << "|                                         |" << endl;
		cout << "|      2、教师登陆                        |" << endl;
		cout << "|                                         |" << endl;
		cout << "|      3、管理员登陆                      |" << endl;
		cout << "|                                         |" << endl;
		cout << "|      0、退出                            |" << endl;
		cout << "|                                         |" << endl;
		cout << " -----------------------------------------" << endl;
		cout << "请输入您的选择：" << endl;

		cin >> select;

		switch (select)//根据用户选择 实现不同接口
		{
		case 1:	//	学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2: //  老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3: //  管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0: //  退出系统 
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择" << endl;
			system("pause");
			system("cls");
			break;
		}
	}




	system("pause");
	return 0;
}