#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
using namespace std;

class Student{
private:
	string S_user,S_password;                //�û���������
	string S_name;                           //ѧ������
	string S_sex;                             //�Ա�
	string S_major;                         //רҵ
	int S_class;                                    //�༶
	string S_id;                             //ѧ��
	string S_quarters;
	int S_bednum;                             //���Һ�
	string S_date;                  //����
	string S_time;                //ʱ��
	char S_sign;               //�������־
	bool Open_flag;                     //�ļ��Ƿ������־
	bool Alter_flag;                         //�޸ı�־
	bool Exit_flag;                       //�˳���־
	int Recond,U_count;                       //��¼ѧ����Ϣ�����û���
	int S_position;                                        //����ѧ����λ��
public:
	Student();
	virtual ~Student();                      //��������
	void Start(Student &L);                          //��������
	void Register(Student &L);               //ע��
	void Login(Student &L);                          //��½
	void Menu(Student &L);                   //�˵�
	void Load(Student &L);                           //��֤�Ƿ�������Ϣ
	void ReadFromFile(Student &L);           //���ļ��ж�������
	void Search(Student &L);                         //�������ݳ�Ա
	void Search_On_Name(Student &L);         //������������
	void Search_On_Id(Student &L);                   //����ѧ������
	void ModifyMember(Student &L);           //�޸ĳ�Ա����
	void DeleteMember(Student &L);                   //ɾ����Ա
	void PrintAll(Student &L);               //��ӡ��������
	void AddMember(Student &L);                       //��ӳ�Ա
	void SaveToFile(Student &L);              //�����ļ�
	void ReturnMenu(Student &L);                        //���ز˵�
	void S_exit(Student &L);                           //�˳�ϵͳ
	void Print(Student &L);                 //�����������Ϣ
	void SaveFile(Student &L);            //������������Ϣ
	void ReadFile(Student &L);            //��ȡ������ϵͳ
	void BackandOut(Student &L);          //������������Ϣ
};
//���캯��
Student::Student()
{
	Open_flag=false;
	Alter_flag=false;
	Exit_flag=true;
	Recond=U_count=0;
	S_position=-1;
}

Student stu[50];       //�������Ա-ѧ����Ϣ��
Student admin[50];       //�������Ա-����Ա����

Student::~Student(){}

//��ʼ�����溯��
void Student::Start(Student &L)
{
	system("cls");
	cout<<"\n\n\n\n\t\t\t\   *��ӭ���뻪��ʦ����ѧ�������ϵͳ*\n\n"<<endl;
    cout<<"\t\t1.�û�ע��";
    cout<<"\t\t2.�û���½";
    cout<<"\t\t0.�˳�ϵͳ "<<endl;
	cout<<"\n\n\t\t\t��ѡ����Ĳ����� ";
	int Key;
point:
	cin>>Key;
	switch(Key)
	{
	case 0:exit(0);break;
	case 1:L.Register(L);break;
	case 2:L.Login(L);break;
	default:
		{
			cout<<"\n�������������ѡ�� ";
			L.Start(L);
			goto point;break;
		}
	}
}

//ע�ắ��
void Student::Register(Student &L)
{
	system("cls");
	string _user,_password;
	ifstream infile;
	infile.open("administrator.txt",ios_base::in);
	if(!infile){
		cerr<<"��ʧ�ܣ�"<<endl;
		exit(1);
	}
	for(int i=0;!infile.eof();++i)
		{infile>>admin[i].S_user>>admin[i].S_password;U_count = i;}
	cout<<"\t\t\t    *��ӭʹ�û���ʦ����ѧ�������ϵͳ�����Ƚ���ע��!*"<<endl;
	cout<<"\n\n\n\t\t�������û��������Ȳ�����10λ���� ";
	cin>>_user;
	cout<<"\n\n\t\t���������루���볤��Ϊ6λ���� ";
	cin>>_password;
	for(int j=0;j<U_count;++j)
		if(admin[j].S_user==_user) {
			cout<<"\t\t*�û��Ѵ��ڣ�������ע�ᣡ*"<<endl;
			getch();
			L.Register(L);
		}
	cout<<"\t\tע��ɹ���\n";
	infile.close();
	U_count++;
	admin[U_count-1].S_user=_user;
	admin[U_count-1].S_password=_password;
	ofstream outfile;
	outfile.open("administrator.txt",ios::out);
	for(int k=0;k<U_count;k++)
	outfile<<admin[k].S_user<<" "<<admin[k].S_password<<endl;
	outfile.close();
	L.Start(L);
	system("cls");
}
//��¼��֤����
void Student::Login(Student &L)
{
	ifstream infile("administrator.txt",ios::in);
	if(!infile)  {
		cout<<"�ļ��޷���!"<<endl;
		exit(1);
	}
	for(int i=0;!infile.eof();++i)
		{infile>>admin[i].S_user>>admin[i].S_password;U_count = i;}
	char _user[10],_password[7];
	bool u=false,p=false;
	int c,t=1;
	do  {
		system("cls");
		cout<<endl<<endl<<endl<<endl<<endl<<endl;
		cout<<"\t\t\t    *��ӭʹ�û���ʦ����ѧ�������ϵͳ�����Ƚ��е�½!*"<<endl;
		cout<<endl<<endl<<endl<<endl<<endl<<endl;
		cout<<"\t\t\t�������û���:";
		fflush(stdin);
		gets(_user);
		cout<<endl<<"\t\t\t����������:";
		for(int i=0;i<6;i++){
			c=getch();
			if(c==13) break;
			if(i&&(c=='\b')){
				i-=2;
				cout<<'\b';
				cout<<' ';
				cout<<'\b';
			}
			else if(c=='\b')
				i--;
			else {
				_password[i]=c;
				cout<<"*";
			}
		}
		_password[6]='\0';
		getch();
		for(int j=0;j<=U_count;++j){
			if(admin[j].S_user==_user) {
				u=true;
				if(admin[j].S_password==_password) p=true;
			}
		}
		if(!u){
			cout<<"\n\t\t�û������ڣ������µ�½��"<<endl;
			getch();
			t++;
			continue;
		}
		else if(!p){
			cout<<"\n\t\t������������µ�½��"<<endl;
			getch();
			t++;
			continue;
		}
		else L.Menu(L);
	}while(t<=3);
	if(t>3){
		cout<<"\n\n\t\t����3�ε�½ʧ�ܣ�ϵͳ�Զ��ر�"<<endl;
		if(getch()=='\r') cout<<"\b";
		exit(1);
	}
	infile.close();
	system("cls");
}


//���˵�
void Student::Menu(Student &L)
{
	system("cls");
	cout<<"\n\n\n\n\t\t------------����ʦ����ѧ�������ϵͳ------------\n\n"<<endl;
	cout<<"\t*************************************************************"<<endl;
	cout<<"\t\t1����ʼ��ϵͳ  \t\t2�����ѧ����Ϣ"<<endl;
	cout<<"\t\t3����ѯѧ����Ϣ\t\t4���޸�ѧ����Ϣ"<<endl;
	cout<<"\t\t5��ɾ��ѧ����Ϣ\t\t6������ѧ����Ϣ"<<endl;
	cout<<"\t\t7�����ѧ����Ϣ\t\t8��������Ǽ�"<<endl;
	cout<<"\t\t9����������Ϣ\t\t0���˳�ϵͳ"<<endl;
	cout<<"\t*************************************************************"<<endl;
	cout<<"\n\n\t��ѡ���ܣ� ";
	int i;
point:
		cin>>i;
	switch(i)
	{
	case 1:L.ReadFromFile(L);break;
	case 2:L.AddMember(L);break;
	case 3:L.Search(L);break;
	case 4:L.ModifyMember(L);break;
	case 5:L.DeleteMember(L);break;
	case 6:L.SaveToFile(L);break;
	case 7:L.PrintAll(L);break;
	case 8:L.BackandOut(L);break;
	case 9:L.Print(L);break;
	case 0:exit(1);break;
	default:
		{
			cout<<"�����������������ѡ��";
			goto point;break;
		}
	}

}

//���ļ��ж�ȡ���ݳ�Ա����
void Student::ReadFromFile(Student &L)
{
	system("cls");
	ifstream file;
	file.open("Student.txt",ios_base::in);
	if(!file){
		cerr<<"can't open the file!"<<endl;
		exit(1);
	}
	cout<<endl;
	cout<<"*************************************************************"<<endl;
	for(int i=0;!file.eof();++i)
		{file>>stu[i].S_name>>stu[i].S_sex>>stu[i].S_major>>stu[i].S_class>>stu[i].S_id>>stu[i].S_quarters>>stu[i].S_bednum;Recond = --i;}
	Open_flag=true;
	cout<<"\t\t����������ϣ���ѡ�������"<<endl;
	cout<<"*************************************************************\n"<<endl;
	file.close();
	L.ReturnMenu (L);
}
void Student::ReadFile(Student &L)
{
	system("cls");
	ifstream file;
	file.open("BackandOut.txt",ios_base::in);
	if(!file){
		cerr<<"can't open the file!"<<endl;
		exit(1);
	}
	cout<<endl;
	cout<<"*************************************************************"<<endl;
	for(int i=0;!file.eof();++i)
		{file>>stu[i].S_name>>stu[i].S_sex>>stu[i].S_id>>stu[i].S_sign>>stu[i].S_date>>stu[i].S_time;Recond = --i;}
	Open_flag=true;
	cout<<"\t\t����������ϣ���ѡ�������"<<endl;
	cout<<"*************************************************************\n"<<endl;
	file.close();
	L.ReturnMenu (L);
}

//������Ϣ����
void Student::Load(Student &L)
{
	char load_temp;
	if(!Open_flag){
		cout<<"��δ������Ϣ�������Ƿ�������Ϣ��Y/N��?"<<endl;
		cin>>load_temp;
		if(load_temp=='Y'||load_temp=='y'){
			L.ReadFromFile(L);
		}
		else
			exit(1);
	}
}

//��ӡ��Ա����
void Student::PrintAll(Student &L)
{
	system("cls");
	L.Load(L);
	cout<<setw(6)<<"�� ��"<<setw(8)<<"�� ��"<<setw(10)<<"ר ҵ"<<setw(8)<<"�� ��"
		<<setw(11)<<"ѧ ��"<<setw(9)<<"���Һ�"<<setw(7)<<"����"<<endl;
	cout<<"*************************************************************"<<endl;
	for(int i=0;i<=Recond;i++){
		cout<<setw(6)<<stu[i].S_name<<setw(8)<<stu[i].S_sex<<setw(10)<<stu[i].S_major
			<<setw(6)<<stu[i].S_class<<setw(14)<<stu[i].S_id<<setw(6)<<stu[i].S_quarters<<setw(6)<<stu[i].S_bednum<<endl;
	}
	cout<<"*************************************************************"<<endl;
	cout<<"\n�����ϣ���ѡ�������"<<endl;
	L.ReturnMenu (L);
}
void Student::Print(Student &L)
{
	system("cls");
	L.Load(L);
	cout<<"  "<<"�� ��"<<"   "<<"�� ��"<<"    "<<"ѧ ��"
	    <<"     "<<"���/���"<<"     "<<"����"<<"       "<<"ʱ��"<<endl;
	cout<<"*************************************************************"<<endl;
	for(int i=0;i<=Recond;i++){
		cout<<" "<<stu[i].S_name<<"    "<<stu[i].S_sex<<"    "
		    <<stu[i].S_id<<"     "<<stu[i].S_sign<<"       "<<stu[i].S_date<<"     "<<stu[i].S_time<<endl;
	}
	cout<<"*************************************************************"<<endl;
	cout<<"\n�����ϣ���ѡ�������"<<endl;
	L.ReturnMenu (L);
}
//��ӳ�Ա����
void Student::AddMember(Student &L)
{
	system("cls");
	L.Load(L);
	Recond++;
	cout<<"������������"<<endl;
	cin>>stu[Recond].S_name;
	cout<<"�������Ա�"<<endl;
	cin>>stu[Recond].S_sex;
	cout<<"������רҵ��"<<endl;
	cin>>stu[Recond].S_major;
	cout<<"������༶"<<endl;
	cin>>stu[Recond].S_class;
	cout<<"������ѧ�ţ�"<<endl;
	cin>>stu[Recond].S_id;
	cout<<"���������Һţ�"<<endl;
	cin>>stu[Recond].S_quarters;
	cout<<"�����봲�ţ�"<<endl;
	cin>>stu[Recond].S_bednum;
	cout<<"\n�����Ϣ��ϣ���ѡ�������"<<endl;
	char temp;
	cout<<"�Ƿ񱣴�(Y/N)?"<<endl;
	cin>>temp;
	if(temp=='y'||temp=='Y'){
		L.SaveToFile(L);
	}
	else{
		cout<<"���ݲ����棬";
		L.ReturnMenu (L);
	}
}
void Student::BackandOut(Student &L)
{
	system("cls");
	L.Load(L);
	Recond++;
	cout<<"������������"<<endl;
	cin>>stu[Recond].S_name;
	cout<<"�������Ա�"<<endl;
	cin>>stu[Recond].S_sex;
	cout<<"������ѧ�ţ�"<<endl;
	cin>>stu[Recond].S_id;
	cout<<"�������B���������O��"<<endl;
	cin>>stu[Recond].S_sign;
	cout<<"���������ڣ�"<<endl;
	cin>>stu[Recond].S_date;
	cout<<"������ʱ�䣺"<<endl;
	cin>>stu[Recond].S_time;
	cout<<"\n�����Ϣ��ϣ���ѡ�������"<<endl;
	char temp;
	cout<<"�Ƿ񱣴�(Y/N)?"<<endl;
	cin>>temp;
	if(temp=='y'||temp=='Y'){
		L.SaveFile(L);
	}
	else{
		cout<<"���ݲ����棬";
		L.ReturnMenu (L);
	}
}
//��������
void Student::Search(Student &L)
{
	system("cls");
	L.Load(L);
	cout<<"����������"<<endl;
	cout<<"\t1������ \t 2��ѧ�� \t 0���˳�����"<<endl;
	int i;
	cin>>i;
	switch(i)
	{
	case 1:L.Search_On_Name(L);break;
	case 2:L.Search_On_Id(L);break;
	case 0:exit(1);break;
	default:
		{
			cout<<"����ʧ�ܣ�";
			L.ReturnMenu (L);
		}
	}
}

//������������
void Student::Search_On_Name(Student &L)
{
	cout<<"Ѱ�ҳ�Ա�� ";
	string _name;
	cin>>_name;
	for(int i=0;i<=Recond;i++){
		if(_name==stu[i].S_name)
			S_position=i;
	}
	if(S_position==-1){
		cout<<"����ʧ�ܣ�";
		L.ReturnMenu (L);
	}
	system("cls");
	cout<<setw(6)<<"�� ��"<<setw(8)<<"�� ��"<<setw(8)<<"ר ҵ"<<setw(8)<<"�� ��"
		<<setw(9)<<"ѧ ��"<<setw(10)<<"���Һ�"<<setw(8)<<"����"<<endl;
	cout<<"*************************************************************"<<endl;
	cout<<setw(5)<<stu[S_position].S_name<<setw(8)<<stu[S_position].S_sex<<setw(10)<<stu[S_position].S_major
			<<setw(6)<<stu[S_position].S_class<<setw(14)<<stu[S_position].S_id<<setw(6)<<stu[S_position].S_quarters<<setw(6)<<stu[S_position].S_bednum<<endl;
	cout<<"*************************************************************"<<endl;
	cout<<"\n�����ɹ���";
	L.ReturnMenu (L);
}

//����ѧ������
void Student::Search_On_Id(Student &L)
{
	cout<<"Ѱ�ҳ�Ա�� ";
	string _id;
	cin>>_id;
	for(int i=0;i<=Recond;i++){
		if(_id==stu[i].S_id)
			S_position=i;
	}
	if(S_position==-1){
		cout<<"����ʧ�ܣ��Ƿ񷵻ز˵�(Y/N)��";
			char temp;
	        cin>>temp;
			if(temp=='y'||temp=='Y'){
				L.Menu(L);
			}
			else
				exit(1);
	}
	system("cls");
	cout<<setw(6)<<"�� ��"<<setw(8)<<"�� ��"<<setw(8)<<"ר ҵ"<<setw(8)<<"�� ��"
		<<setw(9)<<"ѧ ��"<<setw(10)<<"���Һ�"<<setw(10)<<"����"<<endl;
	cout<<"*************************************************************"<<endl;
	cout<<setw(6)<<stu[S_position].S_name<<setw(8)<<stu[S_position].S_sex<<setw(10)<<stu[S_position].S_major
			<<setw(6)<<stu[S_position].S_class<<setw(14)<<stu[S_position].S_id<<setw(6)<<stu[S_position].S_quarters<<setw(6)<<stu[S_position].S_bednum<<endl;
	cout<<"*************************************************************"<<endl;
	cout<<"\n�����ɹ���";
	L.ReturnMenu (L);
	if(!Exit_flag) L.Menu(L);
}

//�޸ĳ�Ա����
void Student::ModifyMember(Student &L)
{
	system("cls");
	L.Load(L);
	int _point;
	Alter_flag=false;
	cout<<"�޸�ѧ����Ϣ:\n"<<endl;
	cout<<"*************************************************************"<<endl;
	for(int i=0;i<=Recond;i++)
		cout<<"\t"<<i<<"��"<<stu[i].S_name<<endl;
	cout<<"*************************************************************\n"<<endl;
	cin>>_point;
	cout<<"*************************************************************"<<endl;
	for(int i=0;i<=Recond;i++){
		if(_point==i){
			cout<<setw(6)<<stu[_point].S_name<<setw(8)<<stu[_point].S_sex<<setw(10)<<stu[_point].S_major
				<<setw(6)<<stu[_point].S_class<<setw(14)<<stu[_point].S_id<<setw(6)<<stu[_point].S_quarters<<setw(6)<<stu[_point].S_bednum<<endl;
			Alter_flag=true;
		}
	}
	if(!Alter_flag){
		cerr<<"�޸�ʧ�ܣ�";
		L.ReturnMenu (L);
	}
	cout<<"*************************************************************"<<endl;
	cout<<"�޸���Ϣ"<<endl;
	cout<<"1������\t2���Ա�\t3��רҵ\n4���༶\t5��ѧ��\t6�����Һ�7������"<<endl;
	int t;
	char second;
	char b;
point:
	cin>>t;
	switch(t)
	{
	case 1:
		{
			cout<<"������������";
			cin>>stu[_point].S_name;
			cout<<"�޸ĳɹ����Ƿ�Ҫ�޸ģ�Y/N��?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"�Ƿ񱣴��޸ģ�Y/N��?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		 }
	case 2:
		{
			cout<<"�������Ա�";
			cin>>stu[_point].S_sex;
			cout<<"�޸ĳɹ����Ƿ�Ҫ�޸ģ�Y/N��?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"�Ƿ񱣴��޸ģ�Y/N��?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		}
	case 3:
		{
			cout<<"������רҵ��";
			cin>>stu[_point].S_major;
			cout<<"�޸ĳɹ����Ƿ�Ҫ�޸ģ�Y/N��?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"�Ƿ񱣴��޸ģ�Y/N��?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		}
	case 4:
		{
			cout<<"������༶��";
			cin>>stu[_point].S_class;
			cout<<"�޸ĳɹ����Ƿ�Ҫ�޸ģ�Y/N��?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"�Ƿ񱣴��޸ģ�Y/N��?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		}
	case 5:
		{
			cout<<"������ѧ�ţ�";
			cin>>stu[_point].S_id;
			cout<<"�޸ĳɹ����Ƿ�Ҫ�޸ģ�Y/N��?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"�Ƿ񱣴��޸ģ�Y/N��?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		}
	case 6:
		{
			cout<<"���������Һţ�";
			cin>>stu[_point].S_quarters;
			cout<<"�޸ĳɹ����Ƿ�Ҫ�޸ģ�Y/N��?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"�Ƿ񱣴��޸ģ�Y/N��?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else L.Menu(L);
			}
			break;
		}
		case 7:
		{
			cout<<"�����봲�ţ�";
			cin>>stu[_point].S_bednum;
			cout<<"�޸ĳɹ����Ƿ�Ҫ�޸ģ�Y/N��?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"�Ƿ񱣴��޸ģ�Y/N��?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		 }
	default:
		{
			cerr<<"�޸�ʧ�ܣ�";
			L.ReturnMenu (L);
			if(!Exit_flag) L.Menu(L);
		}
	}
}

//ɾ����Ա����
void Student::DeleteMember(Student &L)
{
	system("cls");
	L.Load(L);
	cout<<"ɾ����Ա"<<endl;
	cout<<"*************************************************************\n"<<endl;
	for(int i=0;i<=Recond;i++)
		cout<<"\t"<<i<<"��"<<stu[i].S_name<<endl;
	cout<<"*************************************************************\n"<<endl;
	int _point;
	bool Del_flag;
	cin>>_point;
	cout<<"*************************************************************"<<endl;
	for(int i=0;i<=Recond;i++){
		if(_point==i){
			cout<<setw(6)<<stu[_point].S_name<<setw(8)<<stu[_point].S_sex<<setw(10)<<stu[_point].S_major
				<<setw(6)<<stu[_point].S_class<<setw(14)<<stu[_point].S_id<<setw(6)<<stu[_point].S_quarters<<setw(6)<<stu[_point].S_bednum<<endl;
			Del_flag=true;
		}
	}
	cout<<"*************************************************************"<<endl;
	if(Del_flag){
		cout<<"ȷ��Ҫɾ������Y/N��"<<endl;
		char _temp;
		cin>>_temp;
		if(_temp=='y'||_temp=='Y'){
			for(int j=_point;j<=Recond;j++){
				stu[j].S_name=stu[j+1].S_name;
				stu[j].S_sex=stu[j+1].S_sex;
				stu[j].S_major=stu[j+1].S_major;
				stu[j].S_class=stu[j+1].S_class;
				stu[j].S_id=stu[j+1].S_id;
				stu[j].S_quarters=stu[j+1].S_quarters;
				stu[j].S_bednum=stu[j+1].S_bednum;
			}
			Recond--;
			cout<<"ɾ���ɹ����Ƿ񱣴��޸�(Y/N)��"<<endl;
			char temp;
			cin>>temp;
			if(temp=='y'||temp=='Y'){
				L.SaveToFile(L);
			}
			else {
				cout<<"���ݲ�����,";
				L.ReturnMenu (L);
				if(!Exit_flag) L.Menu(L);
				}
		}
		else L.Menu(L);
	}
	else L.ReturnMenu(L);
	if(!Exit_flag) L.Menu(L);
}

//�����ļ�����
void Student::SaveToFile(Student &L)
{
	system("cls");
	L.Load(L);
	ofstream ofile;
	ofile.open("Student.txt",ios_base::out);
	for(int i=0;i<=Recond;i++)
	ofile<<stu[i].S_name<<' '<<stu[i].S_sex<<' '<<stu[i].S_major<<' '
		<<stu[i].S_class<<' '<<stu[i].S_id<<' '<<stu[i].S_quarters<<' '<<stu[i].S_bednum<<endl;
	ofile.close();
	cout<<"*************************************************************"<<endl;
	cout<<"\t\t��Ϣ������ϣ�"<<endl;
	cout<<"*************************************************************"<<endl;
	L.ReturnMenu (L);
	if(!Exit_flag) L.Menu(L);
}
void Student::SaveFile(Student &L)
{
	system("cls");
	L.Load(L);
	ofstream ofile;
	ofile.open("BackandOut.txt",ios_base::out);
	for(int i=0;i<=Recond;i++)
	ofile<<stu[i].S_name<<' '<<stu[i].S_sex<<' '
		 <<stu[i].S_id<<' '<<stu[i].S_date<<' '<<stu[i].S_time<<endl;
	ofile.close();
	cout<<"*************************************************************"<<endl;
	cout<<"\t\t��Ϣ������ϣ�"<<endl;
	cout<<"*************************************************************"<<endl;
	L.ReturnMenu (L);
	if(!Exit_flag) L.Menu(L);
}
//���ز˵�����
void Student::ReturnMenu (Student &L)
{
	cout<<"�Ƿ񷵻ز˵�(Y/N)?"<<endl;
	char temp;
	cin>>temp;
	if(temp=='y'||temp=='Y')
		L.Menu(L);
	else
		L.S_exit(L);
}

//�˳�ϵͳ����
void Student::S_exit(Student &L)
{
	cout<<"*************************************************************"<<endl;
	cout<<"ȷ���˳�ϵͳ(Y/N)?"<<endl;
	char temp;
	cin>>temp;
	if((temp=='y'||temp=='Y'))
		exit(0);
	else
		Exit_flag=false;
}

int main()
{
	Student L;
	L.Start(L);
	return 0;
}
