#include"student.h"

//Ĭ�Ϲ���
Student::Student()
{

}

//�вι���
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_name = name;
	this->m_Pwd = pwd;

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
void Student::operMenu()
{
	cout << "��ӭѧ������" << this->m_name << "��¼��" << endl;
	cout << " -----------------------------------------" << endl;
	cout << "|                                         |" << endl;
	cout << "|      1������ԤԼ                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      2���鿴����ԤԼ                    |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      3���鿴����ԤԼ                    |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      4��ȡ��ԤԼ                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      0��ע����¼                        |" << endl;
	cout << "|                                         |" << endl;
	cout << " -----------------------------------------" << endl;
	cout << "��ѡ�����Ĳ���" << endl;
}

//����ԤԼ
void Student::applyOrder()
{
	cout << "��������ʱ��Ϊ��һ������" << endl;
	cout << "����������ԤԼ��ʱ��" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;

	int date = 0;//����
	int interval = 0;//ʱ���
	int room = 0;//�������
	int ComputerNumber;//��Ҫ�ĵ�������

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "������������������" << endl;
	}
	cout << "����������ԤԼʱ���" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "������������������" << endl;
	}
	cout << "��ѡ�����" << endl;
	cout << vCom[0].m_ComId << "�Ż�������Ϊ��" << vCom[0].m_MaxNum << " ʣ���ԤԼ����" << vCom[0].m_RemainNum << endl;
	cout << vCom[1].m_ComId << "�Ż�������Ϊ��" << vCom[1].m_MaxNum << " ʣ���ԤԼ����" << vCom[1].m_RemainNum << endl;
	cout << vCom[2].m_ComId << "�Ż�������Ϊ��" << vCom[2].m_MaxNum << " ʣ���ԤԼ����" << vCom[2].m_RemainNum << endl;

	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			cout << "��������ҪԤԼ�ĵ���������" << endl;
			cin >> ComputerNumber;
			while (true)
			{
				if (vCom[room - 1].m_RemainNum >= ComputerNumber)
				{
					break;
				}
				if (vCom[room - 1].m_RemainNum < ComputerNumber)
				{
					cout << "��Ǹ�������������������㣬������ѡ�����������" << endl;
					cout << "�Ƿ񷵻���һ������ѡ�������������������ѡ��ԤԼ����" << endl;
					cout << "1������" << endl;
					cout << "2������ѡ��ԤԼ����" << endl;
					int tempSelect;
					cin >> tempSelect;
					if (tempSelect == 2)
					{
						cout << "��������ҪԤԼ�ĵ���������" << endl;
						cin >> ComputerNumber;
					}
					else if (tempSelect == 1)
					{
						cout << "��ѡ�����" << endl;
						cout << vCom[0].m_ComId << "�Ż�������Ϊ��" << vCom[0].m_MaxNum << " ʣ���ԤԼ����" << vCom[0].m_RemainNum << endl;
						cout << vCom[1].m_ComId << "�Ż�������Ϊ��" << vCom[1].m_MaxNum << " ʣ���ԤԼ����" << vCom[1].m_RemainNum << endl;
						cout << vCom[2].m_ComId << "�Ż�������Ϊ��" << vCom[2].m_MaxNum << " ʣ���ԤԼ����" << vCom[2].m_RemainNum << endl;
						cin >> room;
						cout << "��������ҪԤԼ�ĵ���������" << endl;
						cin >> ComputerNumber;
					}
				}

			}
			break;
		}
		cout << "������������������" << endl;
	}
	cout << "ԤԼ�ɹ��������" << endl;

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

//�鿴����ԤԼ
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		//string תint 
		//string ����  .c_str() תconst char*
		//������atoi(const char*) תint 
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			cout << "ԤԼ����: ��" << of.m_orderData[i]["date"];
			cout << " ʱ��:" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ����:" << of.m_orderData[i]["roomId"];
			cout << " ԤԼ����:" << of.m_orderData[i]["ReqNum"];
			string status = "״̬: ";//0ȡ����ԤԼ  1  �����   2 ԤԼ�ɹ�  -1ԤԼʧ��
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "ԤԼʧ��";
			}
			else
			{
				status += "ԤԼ��ȡ��";
			}
			cout << " " << status << endl;
		}
	}
	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "��";

		cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["date"];
		cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << " ѧ�ţ�" << of.m_orderData[i]["stuId"];
		cout << " ������" << of.m_orderData[i]["stuName"];
		cout << " ������" << of.m_orderData[i]["roomId"];
		cout << "ԤԼ������" << of.m_orderData[i]["ReqNum"];
		string status = "״̬��";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ��";
		}
		else
		{
			status += "ԤԼ��ȡ��";
		}
		cout << " " << status << endl;

	}
	system("pause");
	system("cls");
}

//ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;

	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "��";
				cout << " ԤԼ���ڣ���" << of.m_orderData[i]["date"];
				cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << " ������" << of.m_orderData[i]["roomId"];
				string status = "״̬��";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << " " << status << endl;
			}
		}
	}
	cout << "������ȡ���ļ�¼��0��ʾ����" << endl;
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
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "������������������" << endl;
	}
	system("pause");
	system("cls");
}
