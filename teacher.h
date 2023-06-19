#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include"orderFile.h"
#include<vector>
#include"student.h"



class Teacher :public Identity
{
public:
	//默认构造
	Teacher();

	//有参构造
	Teacher(int empId, string name, string pwd);

	//菜单界面
	void operMenu();

	//查看所有预约
	void showAllOrder();

	//审核预约
	void validOrder();

	//查看机房信息
	void showComputer();

	//职工号
	int m_EmpId;
	//机房容器
	vector<ComputerRoom>vCom;

};
