#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include<fstream>
#include"globalFile.h"
#include<vector>
#include"student.h"
#include"teacher.h"
#include<algorithm>
#include"computerRoom.h"

class Manager :public Identity
{
public:
	//默认构造
	Manager();

	//有参构造
	Manager(string name, string pwd);

	//菜单界面
	void operMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void cleanFile();

	//初始化容器
	void initVector();

	//学生容器
	vector<Student>vStu;

	//教师容器
	vector<Teacher>vTea;

	//机房容器
	vector<ComputerRoom>vCom;

	//检测重复 参数：（传入id , 传入类型） 返回值：（true 代表有重复，false 代表无重复）
	bool checkRepeat(int id, int type);
};
