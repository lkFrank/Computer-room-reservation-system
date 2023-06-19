#include<iostream>
using namespace std;
#include"Identity.h"
#include<fstream>
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"

//�������Ա�Ӳ˵�����
void manaagerMenu(Identity*& manager)
{
	while (true)
	{
		//���ù���Ա�Ӳ˵�
		manager->operMenu();

		//������ָ��תΪ����ָ�룬��������������ӿ�
		Manager* man = (Manager*)manager;

		int select = 0;
		//�����û���ѡ��
		cin >> select;
		if (select == 1)
		{

			//����˺�
			man->addPerson();
		}
		else if (select == 2)
		{
			//�鿴�˺�
			man->showPerson();
		}
		else if (select == 3)
		{
			//�鿴������Ϣ
			man->showComputer();
		}
		else if (select == 4)
		{
			//���ԤԼ
			man->cleanFile();
		}
		else
		{
			delete manager;//���ٶ�������
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

//����ѧ���Ӳ˵�����
void studentMenu(Identity*& student)
{
	while (true)
	{
		//ѧ���˵�
		student->operMenu();

		Student* stu = (Student*)student;
		int select = 0;

		cin >> select;
		if (select == 1)//����ԤԼ
		{
			stu->applyOrder();
		}
		else if (select == 2)//�鿴����ԤԼ
		{
			stu->showMyOrder();
		}
		else if (select == 3)//�鿴����ԤԼ
		{
			stu->showAllOrder();
		}
		else if (select == 4)//ȡ��ԤԼ
		{
			stu->cancelOrder();
		}
		else
		{
			delete student;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//�����ʦ�Ӳ˵�����
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
			//�鿴����ԤԼ
			tea->showAllOrder();
		}
		else if (select == 2)
		{
			//���ԤԼ
			tea->validOrder();
		}
		else if (select == 3)
		{
			//�鿴������Ϣ
			tea->showComputer();
		}
		else
		{
			delete teacher;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

}

//��¼����  ����1  �����ļ��� ����2  �����������
void LoginIn(string fileName, int type)
{
	//����ָ�룬ָ���������
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//׼�������û�����Ϣ
	int id = 0;
	string name;
	string pwd;

	//�ж����
	if (type == 1)//ѧ�����
	{
		cout << "���������ѧ�ţ�" << endl;
		cin >> id;
	}
	if (type == 2)//��ʦ���
	{
		cout << "���������ְ���ţ�" << endl;
		cin >> id;
	}

	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//ѧ�������֤
		int fId;//�ļ��ж�ȡ��id��
		string fName; //�ļ��л�ȡ������
		string fPwd;  //�ļ��л�ȡ������
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//����ѧ����ݵ��Ӳ˵�
				studentMenu(person);

				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ�����֤
		int fId;//�ļ��ж�ȡ��id��
		string fName; //�ļ��л�ȡ������
		string fPwd;  //�ļ��л�ȡ������
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//�����ʦ��ݵ��Ӳ˵�
				teacherMenu(person);

				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա�����֤
		string fName; //�ļ��л�ȡ������
		string fPwd;  //�ļ��л�ȡ������
		while (ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if (fName == name && fPwd == pwd)
			{
				cout << "����Ա��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//�������Ա��ݵ��Ӳ˵�

				manaagerMenu(person);
				return;
			}
		}
	}

	cout << "��֤��¼ʧ�ܣ�" << endl;
	system("pause");
	system("cls");


}

//���������Ϊ���࣬������ѧ������ʦ������Ա

int main()
{

	int select = 0;//���ڽ����û���ѡ��

	while (true)
	{
		cout << "��ӭʹ�û���ԤԼϵͳ��" << endl;
		cout << " -----------------------------------------" << endl;
		cout << "|                                         |" << endl;
		cout << "|      1��ѧ����½                        |" << endl;
		cout << "|                                         |" << endl;
		cout << "|      2����ʦ��½                        |" << endl;
		cout << "|                                         |" << endl;
		cout << "|      3������Ա��½                      |" << endl;
		cout << "|                                         |" << endl;
		cout << "|      0���˳�                            |" << endl;
		cout << "|                                         |" << endl;
		cout << " -----------------------------------------" << endl;
		cout << "����������ѡ��" << endl;

		cin >> select;

		switch (select)//�����û�ѡ�� ʵ�ֲ�ͬ�ӿ�
		{
		case 1:	//	ѧ�����
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2: //  ��ʦ���
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3: //  ����Ա���
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0: //  �˳�ϵͳ 
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}




	system("pause");
	return 0;
}