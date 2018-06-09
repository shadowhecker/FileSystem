#pragma once
#ifndef _MFD_H
#define _MFD_H

#include "AllHeader.h"
using namespace std;


class UFD;
class FRD;
class AFD;
class MFD
{
public:
	string usrname;
	UFD* usrfiledir;  //用户文件目录指针
	MFD() {}
	MFD(string s) :usrname(s) { usrfiledir = NULL; }//构造函数
	friend ostream& operator<<(ostream &os, const MFD& item)
	{
		os << item.usrname;
		return os;
	}
	virtual ~MFD() {}
};

class UFD
{
public:
	string filename;
	int filelength;
	FRD* filerecord;
	UFD* next;
	UFD() {}
	UFD(string s) :filename(s) { filelength = 0; filerecord = NULL; next = NULL; }
	UFD(UFD& s) :filename(s.filename), filelength(s.filelength) { filerecord = s.filerecord; next = NULL; }
	virtual ~UFD() {
		if (next)
			delete next;
	}
};

class FRD
{
public:
	string name;
	string sex;
	FRD* next;
	FRD() {}
	FRD(string n, string s) :name(n), sex(s) { next = NULL; }
	virtual ~FRD() {
		if (next)
			delete next;
	}
};

class AFD//文件打开链表类
{
public:
	string filename;
	int filelength;
	FRD* filerecord;
	AFD* next;
	int modifyflag;//0表示未修改，1表示已修改
	AFD() {}
	AFD(UFD& tmp) :filename(tmp.filename), filelength(tmp.filelength) { filerecord = tmp.filerecord; next = NULL; modifyflag = 0; }
	virtual ~AFD() {
		if (next)
			delete next;
	}
};


typedef void(*func)(void);
class command_hand
{
public:
	string pname;
	func handler;//函数指针
};

extern command_hand commandlist[];

void cmd_in_parse(string& s)
{

	int flag = 0;
	int j = 0;
	for (j = 0; j<9; ++j)
	{
		if (!commandlist[j].pname.compare(s))//找到了相应的命令
		{
			flag = 1;
			commandlist[j].handler();
			break;
		}
	}
	if (!flag)
		cout << "未找到命令" << endl;
}

#endif _MFD_H