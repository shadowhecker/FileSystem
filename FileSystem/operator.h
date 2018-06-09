#pragma once
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "AllHeader.h"
#include "MFD.h"
using namespace std;
extern vector<MFD> UsrEntry;
extern int cur_ID;
extern AFD* openfilelist;
void create_file()
{
	
	cout << "��������Ҫ�½����ļ���:"<<endl;
	string c,s,x;
	getline(cin, c);//�Ե���һ�������Ļس�
	getline(cin, s);
	stringstream stream(s);
	while (stream >> x)
	{
		UFD* p_file = UsrEntry[cur_ID].usrfiledir;
		UFD* p_file_pre = NULL;
		if (p_file == NULL)//���û����ļ�Ϊ��
		{
			UFD* p_new = new UFD(x);
			UsrEntry[cur_ID].usrfiledir = p_new;
			cout << "�ļ�" << x << "�����ɹ�"<<endl;
		}
		else
		{
			while (p_file != NULL)
			{
				if (!p_file->filename.compare(x))//������ͬ���ļ�
				{
					cout << p_file->filename <<"�ļ��Ѿ�����" << endl;
					break;
				}
			}
			p_file= UsrEntry[cur_ID].usrfiledir;
			UFD* p_new = new UFD(x);
			p_new->next = p_file->next;
			p_file->next = p_new;
			cout << "�ļ�" << x << "�����ɹ�" << endl;
		}
	}
	cout << "�ļ��������" << endl;
}

void open_file()
{
	UFD* p_file = UsrEntry[cur_ID].usrfiledir;
	if (p_file == NULL)
	{
		cout << "���û������ļ�" << endl;
		return;
	}
	cout << "��������Ҫ�򿪵��ļ���:" << endl;
	string c, s, x;
	getline(cin, c);//�Ե���һ�������Ļس�
	getline(cin, s);
	stringstream stream(s);
	int find_flag = 0;
	while (stream >> x)
	{
		find_flag = 0;
		p_file = UsrEntry[cur_ID].usrfiledir;
		while (p_file != NULL)
		{
			if (p_file->filename == x)//�ҵ��ļ�
			{
				find_flag = 1;
				if (openfilelist == NULL)//û���κ��ļ���
				{
					openfilelist = new AFD(*p_file);
					openfilelist->next = NULL;
					openfilelist->modifyflag = 0;
					cout << "�ļ�" << x << "�򿪳ɹ�" << endl;
					break;
				}
				else//�ļ�������Ϊ��
				{
					AFD* p_search = openfilelist;
					AFD* p_search_pre = NULL;//���Դ洢β���ڵ�ǰһ���ڵ�
					if (p_search == NULL)
					{
						AFD* p_new_afd = new AFD(*p_file);
						p_search = p_new_afd;
						break;
					}
					while (p_search != NULL)
					{
						if (p_search->filename == p_file->filename)
						{
							cout << p_search->filename <<"�ļ��Ѿ���" << endl;
							break;
						}
						if (p_search->next == NULL)
							p_search_pre = p_search;
						p_search = p_search->next;
					}
					if (p_search == NULL)
					{
						AFD* p_new_afd = new AFD(*p_file);
						p_search_pre->next = p_new_afd;
						cout << "�ļ�" << x << "�򿪳ɹ�" << endl;
					}
				}
			}
			p_file = p_file->next;
		}
		if (!find_flag)
		{
			cout << x << "�ļ�δ�ҵ�" << endl;
		}
	}
}

void close_file()
{
	if (openfilelist==NULL)
	{
		cout << "���û�û�д��ļ�" << endl;
		return;
	}
	cout << "��������Ҫ�رյ��ļ���:" << endl;
	string c, s, x;
	getline(cin, c);//�Ե���һ�������Ļس�
	getline(cin, s);
	stringstream stream(s);
	AFD* p_file_afd = openfilelist;
	AFD* p_file_afd_pre = NULL;
	int find_flag = 0;
	while (stream >> x)
	{
		p_file_afd = openfilelist;
		find_flag = 0;
		while (p_file_afd != NULL)
		{
			if (p_file_afd->filename == x)//���б����ҵ����ļ�
			{
				find_flag = 1;
				if (p_file_afd->modifyflag == 1)//��ʾ�ļ����޸�
				{
					UFD* p_file_ufd = UsrEntry[cur_ID].usrfiledir;
					while (p_file_ufd != NULL)
					{
						if (p_file_ufd->filename == x)
						{
							p_file_ufd->filelength = p_file_afd->filelength;
							p_file_ufd->filerecord = p_file_afd->filerecord;
							break;
						}
						p_file_ufd = p_file_ufd->next;
					}
				}
				if (p_file_afd_pre != NULL)
				{
					p_file_afd_pre->next = p_file_afd->next;//�س�p_file_afd��ָ����
				}
				else
				{
					openfilelist = p_file_afd->next;
				}
				p_file_afd->filerecord = NULL;
				p_file_afd->next = NULL;
				delete p_file_afd;
				p_file_afd = NULL;//�ļ��ر�
				cout <<"�ļ�"<<x<<"�Ѿ��ر�" << endl;
				break;
			}
			p_file_afd_pre = p_file_afd;
			p_file_afd = p_file_afd->next;
		}
		if (!find_flag)
		{
			cout <<x<<"δ�򿪻����Ʋ���ȷ" << endl;
		}
	}
}

void delete_file()
{
	cout << "������Ҫɾ�����ļ�����:";
	string x;//�û�������ļ�����
	cin >> x;
	AFD* p_file_afd = openfilelist;
	AFD* p_file_afd_pre=NULL;
	UFD* p_file_ufd = UsrEntry[cur_ID].usrfiledir;
	UFD* p_file_ufd_pre=NULL;
	if (openfilelist=NULL)
	{
	}
	else
	{
		while (p_file_afd != NULL)
		{
			if (p_file_afd->filename == x)//���б����ҵ����ļ�
			{
				if (p_file_afd_pre != NULL)
				{
					p_file_afd_pre->next = p_file_afd->next;//�س�p_file_afd��ָ����
				}
				if (p_file_afd->modifyflag == 1)//��ʾ�ļ����޸�
				{
					while (p_file_ufd != NULL)
					{
						if (p_file_ufd->filename == x)
						{
							p_file_ufd->filelength = p_file_afd->filelength;
							p_file_ufd->filerecord = p_file_afd->filerecord;
							break;
						}
						p_file_ufd = p_file_ufd->next;
					}
				}
				p_file_afd->filerecord = NULL;
				p_file_afd->next = NULL;
				delete p_file_afd;
				p_file_afd = NULL;//�ļ��ر�
				break;
			}
			p_file_afd_pre = p_file_afd;
			p_file_afd = p_file_afd->next;
		}
	}
	//���ϲ���ȷ���ļ����ر�
	p_file_ufd = UsrEntry[cur_ID].usrfiledir;
	while (p_file_ufd != NULL)
	{
		if (p_file_ufd->filename == x)//�ļ�Ŀ¼���ҵ��ļ�
		{
			if (p_file_ufd_pre != NULL)
			{
				p_file_ufd_pre->next = p_file_ufd->next;
			}
			else
			{
				UsrEntry[cur_ID].usrfiledir = p_file_ufd->next;
			}
			p_file_ufd->next = NULL;
			delete p_file_ufd;
			p_file_ufd = NULL;
			cout << "�ļ��Ѿ�ɾ��" << endl;
			return;
		}
		p_file_ufd_pre = p_file_ufd;
		p_file_ufd = p_file_ufd->next;
	}
	cout << "δ�ҵ��ļ�" << endl;
}

void write_file()
{
	cout << "������Ҫд����ļ�����:"<<endl;
	string x;//�û�������ļ�����
	cin >> x;
	AFD* p_file_afd = openfilelist;
	if (openfilelist == NULL)
	{
		cout << "�ļ�δ��" << endl;
		return;
	}
	else
	{
		while (p_file_afd != NULL)
		{
			if (p_file_afd->filename == x)//���б����ҵ��ļ�
			{
				string n, s;
				cout << "�������������Ա�:";
				cin >> n >> s;
				FRD* p_frd_new = new FRD(n, s);
				FRD* p_frd = p_file_afd->filerecord;
				if (p_frd == NULL)
				{
					p_file_afd->filerecord = p_frd_new;
					p_file_afd->modifyflag = 1;//�޸ĳɹ�����λ
					++p_file_afd->filelength;
					cout << "�ļ�д��ɹ�" << endl;
					return;
				}
				p_frd_new->next = p_frd->next;
				p_frd->next = p_frd_new;
				p_file_afd->modifyflag = 1;//�޸ĳɹ�����λ
				++p_file_afd->filelength;
				cout << "�ļ�д��ɹ�" << endl;
				return;
			}
			p_file_afd = p_file_afd->next;
		}
		cout << "�ļ�δ��" << endl;
	}
}

void read_file()
{
	cout << "������Ҫ��ȡ���ļ�����:";
	string x;//�û�������ļ�����
	cin >> x;
	AFD* p_file_afd = openfilelist;
	if (openfilelist == NULL)
	{
		cout << "�ļ�δ��" << endl;
		return;
	}
	else
	{
		while (p_file_afd != NULL)
		{
			if (p_file_afd->filename == x)//���б����ҵ��ļ�
			{
				FRD* p_frd = p_file_afd->filerecord;
				if (p_frd == NULL)
				{
					cout << "�ļ����޼�¼" << endl;
					return;
				}
				int Ri;
				cout << "������Ҫ���ҵļ�¼��:";
				cin >> Ri;
				int index = 1;
				while (p_frd!= NULL)
				{
					if (index == Ri)
					{
						cout << "��¼" << Ri << ":����:" << p_frd->name << "   " << "�Ա�:" << p_frd->sex << endl;
						return;
					}
					p_frd = p_frd->next;
					++index;
				}
				cout << "��¼���д�" << endl;
				return;
			}
			p_file_afd = p_file_afd->next;
		}
		cout << "�ļ�δ��" << endl;
	}
}

void print1()//��ʾ��Ŀ¼
{
	cout << "�û���Ŀ¼����:" << endl;
	int i = 0;
	for (i=0; i != UsrEntry.size(); ++i)//��ʾ�û���Ŀ¼
		cout << "�û�" << i + 1 << ":" << UsrEntry[i] << "    ";
}

void display_directory()
{
	cout << "�û�" << UsrEntry[cur_ID].usrname << "���ļ�Ŀ¼����:" << endl;
	int i = 0;
	UFD* p_file_ufd = UsrEntry[cur_ID].usrfiledir;
	if (p_file_ufd == NULL)
	{
		cout << "���û������ļ�" << endl;
		return;
	}
	while (p_file_ufd != NULL)
	{
		if (i % 3 == 0)
			cout << endl;
		cout << "�ļ�" << i + 1 << ":" << p_file_ufd->filename << "     ";
		++i;
		p_file_ufd = p_file_ufd->next;
	}
	cout << endl;
}

void display_file()
{
	cout << "������Ҫ��ȡ���ļ�����:";
	string x;//�û�������ļ�����
	cin >> x;
	AFD* p_file_afd = openfilelist;
	if (openfilelist == NULL)
	{
		cout << "�ļ�δ��" << endl;
		return;
	}
	else
	{
		while (p_file_afd != NULL)
		{
			if (p_file_afd->filename == x)//���б����ҵ��ļ�
			{
				int Ri = 1;
				FRD* p_frd = p_file_afd->filerecord;
				if (p_frd == NULL)
				{
					cout << "�ļ����޼�¼" << endl;
					return;
				}
				while (p_frd!= NULL)
				{
					cout << "��¼" << Ri << ":����:" << p_frd->name << "   " << "�Ա�:" << p_frd->sex << endl;
					++Ri;
					p_frd = p_frd->next;
				}
				return;
			}
			p_file_afd = p_file_afd->next;
		}
		cout << "�ļ�δ��" << endl;
	}
}

void close_user()
{
	delete openfilelist;
}
#endif