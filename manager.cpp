#include"manager.h"

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
	//初始化管理员信息
	this->m_name = name;
	this->m_Pwd = pwd;

	//初始化容器  获取到所有文件中老师，学生的信息
	this->initVector();

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
void Manager::operMenu()
{
	cout << "欢迎管理员：" << this->m_name << " 登录！ " << endl;
	cout << " -----------------------------------------" << endl;
	cout << "|                                         |" << endl;
	cout << "|      1、添加账号                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      2、查看账号                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      3、查看机房                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      4、清空预约                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      0、注销登录                        |" << endl;
	cout << "|                                         |" << endl;
	cout << " -----------------------------------------" << endl;
	cout << "请选择您的操作" << endl;
}

//初始化容器
void Manager::initVector()
{	//清空容器
	vStu.clear();
	vTea.clear();

	//读取学生文件中的信息
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}

	ifs.close();

	//读取老师文件中的信息
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	ifs.close();
}

//检测重复 参数：（传入id , 传入类型） 返回值：（true 代表有重复，false 代表无重复）
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}

		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}

		}
	}
	return false;
}

//添加账号
void Manager::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加教师" << endl;

	string fileName;//操作文件名
	string tip;		//提示id号
	string errorTip;//重复错误提示

	ofstream ofs;	//文件操作对象

	int select;
	cin >> select;//接收用户选项

	if (select == 1)
	{
		//添加的是学生

		fileName = STUDENT_FILE;
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入";
	}
	else
	{

		fileName = TEACHER_FILE;
		tip = "请输入职工编号：";
		errorTip = "职工号重复，请重新输入";
	}

	//利用追加的方式写文件
	ofs.open(fileName, ios::out | ios::app);

	int id;//学号/职工号
	string name; //姓名
	string pwd;  //密码

	cout << tip << endl;

	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}


	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;



	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;

	if (select == 1)
	{
		vStu.push_back(Student(id, name, pwd));

	}
	else
	{
		vTea.push_back(Teacher(id, name, pwd));
	}

	system("pause");
	system("cls");

	ofs.close();

}

void PrintStudent(Student& s)
{
	cout << "学号:" << s.m_Id << " 姓名:" << s.m_name << " 密码:" << s.m_Pwd << endl;
}

void PrintTeacher(Teacher& t)
{
	cout << "职工号:" << t.m_EmpId << " 姓名:" << t.m_name << " 密码:" << t.m_Pwd << endl;
}

//查看账号
void Manager::showPerson()
{
	cout << "请选择查看的内容" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//查看学生
		cout << "所有的学生信息如下" << endl;
		for_each(vStu.begin(), vStu.end(), PrintStudent);
	}
	else
	{
		//查看老师
		cout << "所有的老师信息如下" << endl;
		for_each(vTea.begin(), vTea.end(), PrintTeacher);
	}
	system("pause");
	system("cls");

}

//查看机房信息
void Manager::showComputer()
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

//清空预约记录
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功！" << endl;
	vCom[0].m_RemainNum = 20;
	vCom[1].m_RemainNum = 50;
	vCom[2].m_RemainNum = 100;
	ofstream ofsx(COMPUTER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < 3; i++)
	{
		ofsx << vCom[i].m_ComId << " " << vCom[i].m_MaxNum << " " << vCom[i].m_RemainNum << endl;
	}
	ofsx.close();
	system("pause");
	system("cls");

}