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
	
	cout << "请输入需要新建的文件名:"<<endl;
	string c,s,x;
	getline(cin, c);//吃掉上一次输入后的回车
	getline(cin, s);
	stringstream stream(s);
	while (stream >> x)
	{
		UFD* p_file = UsrEntry[cur_ID].usrfiledir;
		UFD* p_file_pre = NULL;
		if (p_file == NULL)//该用户下文件为空
		{
			UFD* p_new = new UFD(x);
			UsrEntry[cur_ID].usrfiledir = p_new;
			cout << "文件" << x << "创建成功"<<endl;
		}
		else
		{
			while (p_file != NULL)
			{
				if (!p_file->filename.compare(x))//遇见了同名文件
				{
					cout << p_file->filename <<"文件已经创立" << endl;
					break;
				}
			}
			p_file= UsrEntry[cur_ID].usrfiledir;
			UFD* p_new = new UFD(x);
			p_new->next = p_file->next;
			p_file->next = p_new;
			cout << "文件" << x << "创建成功" << endl;
		}
	}
	cout << "文件建立完成" << endl;
}

void open_file()
{
	UFD* p_file = UsrEntry[cur_ID].usrfiledir;
	if (p_file == NULL)
	{
		cout << "该用户下无文件" << endl;
		return;
	}
	cout << "请输入需要打开的文件名:" << endl;
	string c, s, x;
	getline(cin, c);//吃掉上一次输入后的回车
	getline(cin, s);
	stringstream stream(s);
	int find_flag = 0;
	while (stream >> x)
	{
		find_flag = 0;
		p_file = UsrEntry[cur_ID].usrfiledir;
		while (p_file != NULL)
		{
			if (p_file->filename == x)//找到文件
			{
				find_flag = 1;
				if (openfilelist == NULL)//没有任何文件打开
				{
					openfilelist = new AFD(*p_file);
					openfilelist->next = NULL;
					openfilelist->modifyflag = 0;
					cout << "文件" << x << "打开成功" << endl;
					break;
				}
				else//文件打开链表不为空
				{
					AFD* p_search = openfilelist;
					AFD* p_search_pre = NULL;//用以存储尾部节点前一个节点
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
							cout << p_search->filename <<"文件已经打开" << endl;
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
						cout << "文件" << x << "打开成功" << endl;
					}
				}
			}
			p_file = p_file->next;
		}
		if (!find_flag)
		{
			cout << x << "文件未找到" << endl;
		}
	}
}

void close_file()
{
	if (openfilelist==NULL)
	{
		cout << "该用户没有打开文件" << endl;
		return;
	}
	cout << "请输入需要关闭的文件名:" << endl;
	string c, s, x;
	getline(cin, c);//吃掉上一次输入后的回车
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
			if (p_file_afd->filename == x)//打开列表中找到了文件
			{
				find_flag = 1;
				if (p_file_afd->modifyflag == 1)//表示文件有修改
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
					p_file_afd_pre->next = p_file_afd->next;//截除p_file_afd所指对象
				}
				else
				{
					openfilelist = p_file_afd->next;
				}
				p_file_afd->filerecord = NULL;
				p_file_afd->next = NULL;
				delete p_file_afd;
				p_file_afd = NULL;//文件关闭
				cout <<"文件"<<x<<"已经关闭" << endl;
				break;
			}
			p_file_afd_pre = p_file_afd;
			p_file_afd = p_file_afd->next;
		}
		if (!find_flag)
		{
			cout <<x<<"未打开或名称不正确" << endl;
		}
	}
}

void delete_file()
{
	cout << "请输入要删除的文件名称:";
	string x;//用户输入的文件名称
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
			if (p_file_afd->filename == x)//打开列表中找到了文件
			{
				if (p_file_afd_pre != NULL)
				{
					p_file_afd_pre->next = p_file_afd->next;//截除p_file_afd所指对象
				}
				if (p_file_afd->modifyflag == 1)//表示文件有修改
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
				p_file_afd = NULL;//文件关闭
				break;
			}
			p_file_afd_pre = p_file_afd;
			p_file_afd = p_file_afd->next;
		}
	}
	//以上部分确保文件被关闭
	p_file_ufd = UsrEntry[cur_ID].usrfiledir;
	while (p_file_ufd != NULL)
	{
		if (p_file_ufd->filename == x)//文件目录中找到文件
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
			cout << "文件已经删除" << endl;
			return;
		}
		p_file_ufd_pre = p_file_ufd;
		p_file_ufd = p_file_ufd->next;
	}
	cout << "未找到文件" << endl;
}

void write_file()
{
	cout << "请输入要写入的文件名称:"<<endl;
	string x;//用户输入的文件名称
	cin >> x;
	AFD* p_file_afd = openfilelist;
	if (openfilelist == NULL)
	{
		cout << "文件未打开" << endl;
		return;
	}
	else
	{
		while (p_file_afd != NULL)
		{
			if (p_file_afd->filename == x)//打开列表中找到文件
			{
				string n, s;
				cout << "请输入姓名和性别:";
				cin >> n >> s;
				FRD* p_frd_new = new FRD(n, s);
				FRD* p_frd = p_file_afd->filerecord;
				if (p_frd == NULL)
				{
					p_file_afd->filerecord = p_frd_new;
					p_file_afd->modifyflag = 1;//修改成功后置位
					++p_file_afd->filelength;
					cout << "文件写入成功" << endl;
					return;
				}
				p_frd_new->next = p_frd->next;
				p_frd->next = p_frd_new;
				p_file_afd->modifyflag = 1;//修改成功后置位
				++p_file_afd->filelength;
				cout << "文件写入成功" << endl;
				return;
			}
			p_file_afd = p_file_afd->next;
		}
		cout << "文件未打开" << endl;
	}
}

void read_file()
{
	cout << "请输入要读取的文件名称:";
	string x;//用户输入的文件名称
	cin >> x;
	AFD* p_file_afd = openfilelist;
	if (openfilelist == NULL)
	{
		cout << "文件未打开" << endl;
		return;
	}
	else
	{
		while (p_file_afd != NULL)
		{
			if (p_file_afd->filename == x)//打开列表中找到文件
			{
				FRD* p_frd = p_file_afd->filerecord;
				if (p_frd == NULL)
				{
					cout << "文件下无记录" << endl;
					return;
				}
				int Ri;
				cout << "请输入要查找的记录号:";
				cin >> Ri;
				int index = 1;
				while (p_frd!= NULL)
				{
					if (index == Ri)
					{
						cout << "记录" << Ri << ":姓名:" << p_frd->name << "   " << "性别:" << p_frd->sex << endl;
						return;
					}
					p_frd = p_frd->next;
					++index;
				}
				cout << "记录号有错" << endl;
				return;
			}
			p_file_afd = p_file_afd->next;
		}
		cout << "文件未打开" << endl;
	}
}

void print1()//显示主目录
{
	cout << "用户主目录如下:" << endl;
	int i = 0;
	for (i=0; i != UsrEntry.size(); ++i)//显示用户主目录
		cout << "用户" << i + 1 << ":" << UsrEntry[i] << "    ";
}

void display_directory()
{
	cout << "用户" << UsrEntry[cur_ID].usrname << "的文件目录如下:" << endl;
	int i = 0;
	UFD* p_file_ufd = UsrEntry[cur_ID].usrfiledir;
	if (p_file_ufd == NULL)
	{
		cout << "该用户下无文件" << endl;
		return;
	}
	while (p_file_ufd != NULL)
	{
		if (i % 3 == 0)
			cout << endl;
		cout << "文件" << i + 1 << ":" << p_file_ufd->filename << "     ";
		++i;
		p_file_ufd = p_file_ufd->next;
	}
	cout << endl;
}

void display_file()
{
	cout << "请输入要读取的文件名称:";
	string x;//用户输入的文件名称
	cin >> x;
	AFD* p_file_afd = openfilelist;
	if (openfilelist == NULL)
	{
		cout << "文件未打开" << endl;
		return;
	}
	else
	{
		while (p_file_afd != NULL)
		{
			if (p_file_afd->filename == x)//打开列表中找到文件
			{
				int Ri = 1;
				FRD* p_frd = p_file_afd->filerecord;
				if (p_frd == NULL)
				{
					cout << "文件下无记录" << endl;
					return;
				}
				while (p_frd!= NULL)
				{
					cout << "记录" << Ri << ":姓名:" << p_frd->name << "   " << "性别:" << p_frd->sex << endl;
					++Ri;
					p_frd = p_frd->next;
				}
				return;
			}
			p_file_afd = p_file_afd->next;
		}
		cout << "文件未打开" << endl;
	}
}

void close_user()
{
	delete openfilelist;
}
#endif