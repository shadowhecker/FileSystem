// FileSystem.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AllHeader.h"
//#include "command.h"
#include "MFD.h"
#include "operator.h"
using namespace std;
int cur_ID;
vector<MFD> UsrEntry;//用户列表
AFD *openfilelist=NULL;//已经打开文件的列表

MFD UsrInput;
UFD FileInput;

int num; //选项选择
int Headnum;
int curID;
using namespace std;
command_hand commandlist[9];

int main()
{
	commandlist[0].pname = "new_file";
	commandlist[0].handler = create_file;
	commandlist[1].pname = "open_file";
	commandlist[1].handler = open_file;
	commandlist[2].pname = "delete_file";
	commandlist[2].handler = delete_file;
	commandlist[3].pname = "close_file";
	commandlist[3].handler = close_file;
	commandlist[4].pname = "read_file";
	commandlist[4].handler = read_file;
	commandlist[5].pname = "write_file";
	commandlist[5].handler = write_file;
	commandlist[6].pname = "display_directory";
	commandlist[6].handler = display_directory;
	commandlist[7].pname = "display_file";
	commandlist[7].handler = display_file;
	commandlist[8].pname = "close_user";
	commandlist[8].handler = close_user;

	cout << "欢迎使用二级文件目录系统！" << endl;
	cout << "请输入需要建立的用户名" << endl;
	string s;
	getline(cin, s);
	stringstream stream(s);
	string usrname;
	string x;
	while (stream >> usrname)//建立用户主目录
	{
		MFD p(usrname);
		UsrEntry.push_back(p);
	}
	char if_next_usr = 'Y';//0代表no
	while (if_next_usr == 'Y')
	{
		print1();
		cout << endl;
		char find_usr = 'Y';
		x.clear();
		while (find_usr == 'Y')
		{
			cout << "请输入想选择的用户名:";
			string usr_info;
			cin >> usr_info;
			cout << endl;
			int find_people=0;
			for (cur_ID = 0; cur_ID != UsrEntry.size(); ++cur_ID)
			{
				find_people = 0;
				if (UsrEntry[cur_ID].usrname == usr_info)
				{
					find_people = 1;
					cout << "欢迎光临" << UsrEntry[cur_ID].usrname << endl;
					cout << "命令菜单:" << endl;
					cout << "1、new_file" << "  " << "2、open_file" << endl;
					cout << "3、delete_file" << "  " << "4、close_file" << endl;
					cout << "5、read_file" << "  " << "6、write_file" << endl;
					cout << "7、display_directory" << "  " << "8、dispaly_file" << endl;
					cout << "9、close_user" << "  " << "10、exit" << endl;
					while (1)
					{
						cout << "请输入你的命令:" << endl;
						cin >> x;
						if (x == "exit")
						{
							close_user();
							break;
						}
						else
						{
							cmd_in_parse(x);
							if (x == "close_user")
								break;
						}
					}
				}
				if (x == "exit"||x=="close_user")
					break;
			}
			if (!find_people)
			{
				cout << "查无此人，请重新输入" << endl;
				cout << "是否继续(Y/N):";
				cin >> find_usr;
			}
			if (x == "exit" || x == "close_user")
				break;
		}
		if (x == "exit")
			break;
	}
	cout << "byebye" << endl;
	system("pause");
	return 1;
}

