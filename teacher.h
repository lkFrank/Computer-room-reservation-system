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
	//Ĭ�Ϲ���
	Teacher();

	//�вι���
	Teacher(int empId, string name, string pwd);

	//�˵�����
	void operMenu();

	//�鿴����ԤԼ
	void showAllOrder();

	//���ԤԼ
	void validOrder();

	//�鿴������Ϣ
	void showComputer();

	//ְ����
	int m_EmpId;
	//��������
	vector<ComputerRoom>vCom;

};
