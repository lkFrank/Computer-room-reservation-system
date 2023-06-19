#include"teacher.h"



//Ĭ�Ϲ���
Teacher::Teacher()
{

}

//�вι���
Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
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
void Teacher::operMenu()
{
	cout << "��ӭ��ʦ��" << this->m_name << "��¼��" << endl;
	cout << " -----------------------------------------" << endl;
	cout << "|                                         |" << endl;
	cout << "|      1���鿴����ԤԼ                    |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      2�����ԤԼ                        |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      3���鿴������Ϣ                    |" << endl;
	cout << "|                                         |" << endl;
	cout << "|      0��ע����¼                        |" << endl;
	cout << "|                                         |" << endl;
	cout << " -----------------------------------------" << endl;
	cout << "��ѡ�����Ĳ���" << endl;
}

//�鿴����ԤԼ
void Teacher::showAllOrder()
{
	/*OrderFile of;
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
	system("cls");*/
	Student().showAllOrder();
}

//���ԤԼ
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "�����ԤԼ��¼���£�" << endl;

	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{

		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << index++ << "��";
			cout << " ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ������" << of.m_orderData[i]["roomId"];
			cout << " ԤԼ�ˣ�" << of.m_orderData[i]["stuName"];
			cout << " ԤԼ����������" << of.m_orderData[i]["ReqNum"];
			string status = "״̬�������";
			cout << " " << status << endl;
		}

	}
	cout << "������Ҫ��˵ļ�¼��0��ʾ����" << endl;
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
				cout << "��������������2��ʾͨ����-1��ʾ��ͨ��" << endl;
				string newstatus;
				cin >> newstatus;
				of.m_orderData[v[select - 1]]["status"] = newstatus;
				of.updateOrder();//����ԤԼ״̬
				cout << "�����ϣ�" << endl;
				//���»�����Ϣ
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
		cout << "������������������" << endl;
	}
	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Teacher::showComputer()
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