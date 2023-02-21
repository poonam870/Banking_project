#include<bits/stdc++.h>

using namespace std;
const int len=25;
int gen_account();

void header()
{
	for(int i=0;i<80;i++)
			cout<<"=";
	cout<<"\n\t\t   Bank Account Management Software"<<"\n\t\tDeveloped By Shubham, Poonam & Vaibhav"<<endl;
	for(int j=0;j<80;j++)
			cout<<"=";
}

void placeholder()
 {
		for(int i=0;i<80;i++)
			cout<<"*";
		cout<<"\tAccount No."<<"\tAccount Holder Name"<<"\t\tBalance"<<endl;	
		for(int j=0;j<80;j++)
			cout<<"*";	
 }	

class accounts
{
	int accno;
	char accholdername[len];
	float balance;
public:
	
	void setdata()
	{
		accno=gen_account();
		cout<<"\n\t\t\t\tAccount no.: "<<accno;
		cout<<"\n\t\t\t\tEnter Account holder's name:";
		gets(accholdername);
		balance=0.0;
	}

	void showdata();

	void modify()
	{
		cout<<"\n\n\t\t\tAccount number: "<<accno;
		cout<<"\n\t\t\tEnter the modified name: ";
		gets(accholdername);
	}

	int ret_accno()
	{
		return accno;
	}

	void money();
};

	void accounts::showdata()
	{
		cout<<"\n\t"<<accno<<"\t\t"<<accholdername<<"\t\t\t"<<balance<<endl;
		for(int i=0;i<80;i++)
			cout<<"_";
	}

int gen_account()
{
	unsigned long acc=200;
	fstream file;
	file.open("bank.dat",ios::binary|ios::in);
	accounts s1;
	file.read((char *)&s1,sizeof(s1));
	file.seekg(0,ios::end);
	int pos=file.tellg()/sizeof(s1);
	file.close();
	return acc+pos+1;
}


	void write_Account()
	{
		clrscr();
		header();
		ofstream fout;
		fout.open("bank.dat",ios::binary|ios::app);
		accounts a1;
		a1.setdata();
		fout.write((char *)&a1,sizeof(a1));
		fout.close();
	}


	void display_Account()
	{
		ifstream fin;
		fin.open("bank.dat",ios::binary);
		accounts a1;
		clrscr();
		header();
		placeholder();		
		while(fin.read((char*)&a1,sizeof(a1)))
		{
		a1.showdata();
		}
		fin.close();
		getch();
	}


	void search_Account()
	{
		int adm;
		clrscr();
		header();
		cout<<"\n\n\tEnter the Account no. whose info you want to see: ";
		cin>>adm;
		ifstream fin;
		fin.open("bank.dat",ios::binary);
		accounts a1;
		char found='n';
		while(fin.read((char*)&a1,sizeof(a1)))
		{
		if(a1.ret_accno()==adm)
		{
			placeholder();
			a1.showdata();
			found='f';
		}
		}
		if(found=='n')
			cout<<"\n\t\tAccount not found!!!!!!!!!!!!!!!";
		fin.close();
		getch();
	}


	void modify_Account()
	{
		int adm;
		char found='f';
		long pos;
		clrscr();
		header();
		cout<<"\n\n\t\tEnter the Account no. you want to modify: ";
		cin>>adm;
		accounts s;
		fstream fio("bank.dat",ios::in|ios::out|ios::binary);
		while(!fio.eof())
		{
			pos=fio.tellg();
			fio.read((char*)&s,sizeof(s));
			if(s.ret_accno()==adm)
			{
				placeholder();			
				s.showdata();
				s.modify();
				fio.seekg(pos);
				fio.write((char*)&s,sizeof(s));
				found='t';
				clrscr();
				header();
				placeholder();				
				s.showdata();
				break;
			}
		}
		if(found=='f')
		{
			cout<<"\n\t\tAccount not found!!!!!!!!!!!!!!!";
			getch();
		}
		fio.seekg(0);
		fio.close();

	}


	void delete_Account()
	{
	accounts a1;
	ifstream fio("bank.dat",ios::binary|ios::in);
	ofstream file("temp.dat",ios::binary|ios::out);
	int adm;
	char found='f',confirm='n';
	clrscr();
	header();
	cout<<"\n\n\t\tEnter the Account No. of the Account to be deleted.";
	cin>>adm;
	while(fio.read((char*)&a1,sizeof(a1)))
	{
		if(a1.ret_accno()==adm)
		{
			found='t';
			cout<<"\n\n\n\t\tAre you sure you want to delete this Account!!!(y/n): ";
			cin>>confirm;
			if(confirm=='n')
				file.write((char*)&a1,sizeof(a1));
		}
		else

			file.write((char*)&a1,sizeof(a1));
	}
	if(found=='f' || confirm=='n')
	{
		if(found=='f')
		{
			cout<<"\n\n\n\t\tAccount not found!!!!!!\n";
			getch();
		}
		if(confirm=='n')
		{
			cout<<"\n\n\n\t\t\tAction void!!!!!!!!!!\n";
			getch();
		}
	}
	else
	{
		cout<<"Account Deleted Successfully.......";
		getch();
	}
	fio.close();
	file.close();
	remove("bank.dat");
	rename("temp.dat","bank.dat");
	}
	
	
	void query_Account()
	{
		clrscr();
		header();
		fstream file;
		file.open("bank.dat",ios::binary|ios::in);
		accounts s1;
		char found='n';
		file.read((char *)&s1,sizeof(s1));
		file.seekg(0,ios::end);
		cout<<"\n\n\n\n\n\n\t\t\tTotal no. of Accounts is "<<file.tellg()/sizeof(s1);
		int rec;
		cout<<"\n\t\tEnter the Serial no. of account whose info you want to see.";
		cin>>rec;
		file.seekg(0,ios::beg);		
		while(file.read((char*)&s1,sizeof(s1)))
		{
			if(file.tellg()/sizeof(s1)==rec)
			{
				placeholder();
				s1.showdata();
				found='f';
			}
		}
		if(found=='n')
		{
			cout<<"\n\n\t\tPlease enter the valid no.";
			getch();
		}
		file.close();
		getch();
	}
	

	void dep_wit()
	{
		int adm;
		char found='f';
		long pos;
		cout<<"\t\tEnter the Account no.";
		cin>>adm;
		accounts  a1;
		fstream fio("bank.dat",ios::in|ios::out|ios::binary);
		while(!fio.eof())
		{
			pos=fio.tellg();
			fio.read((char*)&a1,sizeof(a1));
			if(a1.ret_accno()==adm)
			{
				a1.money();
				fio.seekg(pos);
				fio.write((char*)&a1,sizeof(a1));
				found='t';
				clrscr();
				header();
				a1.showdata();
				break;
			}
		}
		if(found=='f')
		{
			cout<<"\n\t\tAccount not found";
			cout<<"\n\t\tPlease Enter A Valid Account Number.";
			getch();
		}
		fio.seekg(0);
		fio.close();

	}


	void accounts::money()
	{
		float amount;
		clrscr();
		header();
		placeholder();
		showdata();
		cout<<"\n\n\n\n\n\t\tConsider the following menu:-";
		cout<<"\n\t\t\t1. Deposit";
		cout<<"\n\t\t\t2. Withdraw";
		cout<<"\n\t\t\t3. Exit\n\t\t\t\t";
		char c;
		cin>>c;
		switch (c)
		{
		case '1':{
			clrscr();
			header();
			cout<<"\n\t\tEnter the amount to be deposited:";
			cin>>amount;
			cout<<"\n\t\tDo you wish to proceed with the transaction(Y/N)";
			char s;
			cin>>s;
			if(toupper(s)=='Y')
			{
				balance+=amount;
				clrscr();
				header();
				cout<<"\n\n\tYour position after transaction:"<<endl<<endl; 
				placeholder();
				showdata();
				getch();
			}
			else
				cout<<"\n\t\tTransaction Void!!!!!!!!!!";
			break;
			}
		case '2':{
			clrscr();
			header();
			cout<<"\n\t\tEnter the amount to be withdrawn:";
			cin>>amount;
			if(balance<amount)
			{
				cout<<"\n\t\tYou don't have sufficient balance in your account";
				getch();
				break;
			}
			cout<<"\n\t\tDo you wish to proceed with the transaction(Y/N)";
			char s;
			cin>>s;
			if(toupper(s)=='Y')
			{
				balance-=amount;
				clrscr();
				header();
				cout<<"\n\n\tYour position after transaction:"<<endl<<endl; 
				placeholder();
				showdata();
				getch();
			}
			else
				cout<<"\n\t\tTransaction Void!!!!!!!!!!";
			break;
			}
		};
		
	}
		

	void acc_info()
	{
		ifstream fin;
		fin.open("bank.dat",ios::binary);
		accounts a1;
		clrscr();
		header();
		placeholder();		
		while(fin.read((char*)&a1,sizeof(a1)))
		{
		a1.showdata();
		}
		fin.close();
		getch();
		
	}
	
	void main_menu()
	{
		char c;
		do{
		clrscr();
		header();
		accounts a1;
		cout<<"\n\n\n\n\n\t\t\tConsider the following menu:-";
		cout<<"\n\t\t\t\t1. Add data";
		cout<<"\n\t\t\t\t2. See Account";
		cout<<"\n\t\t\t\t3. Search Account";
		cout<<"\n\t\t\t\t4. Modify Account";
		cout<<"\n\t\t\t\t5. Delete Account";
		cout<<"\n\t\t\t\t6. Query Account";
		cout<<"\n\t\t\t\t7. Exit\n\t\t\t\t";
		cin>>c;
		switch (c)
		{
		case '1':{
			write_Account();
			break;
			}
		case '2':{
			display_Account();
			break;
			}
		case '3':{
			search_Account();
			break;
			}
		case '4':{
			modify_Account();
			break;
			}
		case '5':{
			delete_Account();
			break;
			}
		case '6':{
			query_Account();
			break;
			}
		};
		}while(c!='7');
	}

	void get_pass()
	{
	clrscr();
	header();
	char ch[4];
	cout<<"\n\n\n\t\t\tEnter your 4 digit pin"<<"\n\tThis is required since you are dealing with confedential data"<<endl;
	cout<<"\n\n\n\t\t\t\t";
	for(int i=0;i<4;i++)
	{
		ch[i]=getch();
		cout<<"*";
	}
	int flag=1;
	char pass[4]={'1','2','3','4'};
	for(int j=0;j<4;j++)
	{
		if(ch[j]!=pass[j])
		{
			flag=0;
			break;
		}
	}
	if(flag==1)
		main_menu();
	else
	{
		cout<<"\n\t\tIncorrect Pin please try again some other time";
		getch();
		exit(0);
	}
	
	}
	 

int main()
{
		char c;
		do{
		clrscr();
		header();
		accounts a1;
		cout<<"\n\n\n\n\n\t\t\tConsider the following menu:-";
		cout<<"\n\t\t\t\t1. Generate/Modify/Delete an account";
		cout<<"\n\t\t\t\t2. Deposit/Withdraw";
		cout<<"\n\t\t\t\t3. Account Information";
		cout<<"\n\t\t\t\t4. Exit\n\t\t\t\t";
		cin>>c;
		switch (c)
		{
		case '1':{
			get_pass();
			break;
			}
		case '2':{
			dep_wit();
			break;
			}
		case '3':{
			acc_info();
			break;
			}

		};
		}while(c!='4');
return 0;
}

