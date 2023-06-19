#include"manager.h"

//Ĭ�Ϲ���
Manager::Manager()
{

}

//�вι���
Manager::Manager(string name, string pwd)
{
	//��ʼ������Ա��Ϣ
	this->m_name = name;
	this->m_Pwd = pwd;

	//��ʼ������  ��ȡ�������ļ�����ʦ��ѧ������Ϣ
	this->initVector();

	//��ʼ����������
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum && ifs >> c.m_RemainNum)
	{
		vCom.push_back(c);
	}
	ifs.close();

}


//�˵�����
void Manager::operMenu()
{
	cout << "��ӭ����Ա��" << this->m_name << " ��¼�� " << endl;
	cout << " -----------------------------------------" << endl;
	cout << "|                                         |" << endl;
	cout << "|      1������˺�                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      2���鿴�˺�                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      3���鿴����                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      4�����ԤԼ                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      0��ע����¼                        |" << endl;
	cout << "|                                         |" << endl;
	cout << " -----------------------------------------" << endl;
	cout << "��ѡ�����Ĳ���" << endl;
}

//��ʼ������
void Manager::initVector()
{	//�������
	vStu.clear();
	vTea.clear();

	//��ȡѧ���ļ��е���Ϣ
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}

	ifs.close();

	//��ȡ��ʦ�ļ��е���Ϣ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	ifs.close();
}

//����ظ� ������������id , �������ͣ� ����ֵ����true �������ظ���false �������ظ���
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

//����˺�
void Manager::addPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2����ӽ�ʦ" << endl;

	string fileName;//�����ļ���
	string tip;		//��ʾid��
	string errorTip;//�ظ�������ʾ

	ofstream ofs;	//�ļ���������

	int select;
	cin >> select;//�����û�ѡ��

	if (select == 1)
	{
		//��ӵ���ѧ��

		fileName = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errorTip = "ѧ���ظ�������������";
	}
	else
	{

		fileName = TEACHER_FILE;
		tip = "������ְ����ţ�";
		errorTip = "ְ�����ظ�������������";
	}

	//����׷�ӵķ�ʽд�ļ�
	ofs.open(fileName, ios::out | ios::app);

	int id;//ѧ��/ְ����
	string name; //����
	string pwd;  //����

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


	cout << "������������" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;



	//���ļ����������
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�" << endl;

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
	cout << "ѧ��:" << s.m_Id << " ����:" << s.m_name << " ����:" << s.m_Pwd << endl;
}

void PrintTeacher(Teacher& t)
{
	cout << "ְ����:" << t.m_EmpId << " ����:" << t.m_name << " ����:" << t.m_Pwd << endl;
}

//�鿴�˺�
void Manager::showPerson()
{
	cout << "��ѡ��鿴������" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴������ʦ" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//�鿴ѧ��
		cout << "���е�ѧ����Ϣ����" << endl;
		for_each(vStu.begin(), vStu.end(), PrintStudent);
	}
	else
	{
		//�鿴��ʦ
		cout << "���е���ʦ��Ϣ����" << endl;
		for_each(vTea.begin(), vTea.end(), PrintTeacher);
	}
	system("pause");
	system("cls");

}

//�鿴������Ϣ
void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout << " �������:" << vCom[i].m_ComId << " �����������:" << vCom[i].m_MaxNum << " ����ʣ��������"
			<< vCom[i].m_RemainNum << endl;

	}
	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "��ճɹ���" << endl;
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