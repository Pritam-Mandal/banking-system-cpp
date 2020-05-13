#include<iostream>
#include<fstream>
#include<string.h>
#include<ctype.h>
using namespace std;
bool checkAccNum(char*,int);	
class address
{
	char bldgNum[10],StreetName[50],City[20];
	int pin;
	public :void setaddr()	//setting address of a customer
			{
				cout<<"\nEnter Building Number ";
				fflush(stdin);
				gets(bldgNum);
				cout<<"\nEnter Street Name ";
				fflush(stdin);
				gets(StreetName);
				fflush(stdin);
				cout<<"\nEnter City ";
				fflush(stdin);
				gets(City);
				cout<<"\nEnter Pin";
				cin>>pin;
			}
			char* getbldgNum()
			{
				return bldgNum;
			}
			char* getStreetName()
			{
				return StreetName;
			}
			char* getCity()
			{
				return City;
			}
				int getpin()
			{
				return pin;
			}
			void dispaddress()  //method to display customer
			{
				cout<<"\nBuilding number "<<bldgNum;
				cout<<"\nStreet Name "<<StreetName;
				cout<<"\nCity "<<City;
				cout<<"\nPin "<<pin;
			}
};
class Customer
{ 
	float Balance;
	char Name[40],Phone[10];
	address Addr;
	public:
				Customer()
				{
					Balance=0.0;
				}
				void setCustomer() 	//setting details of customer
				{
					cout<<"\nEnter Name ";
					fflush(stdin);
					gets(Name);
					cout<<"\nEnter Home Address ";
					fflush(stdin);
					Addr.setaddr();
					fflush(stdin);
					cout<<"\nEnter Phone number";
					gets(Phone);
				}	
				char* getName()
				{
					return Name;
				}
				char* getCusbldgNum()
				{
					return Addr.getbldgNum();
				}
				char* getCusStreetName()
				{
					return Addr.getStreetName();
				}
				char* getCusCity()
				{
					return Addr.getCity();
				}
				int getCuspin()
				{
					return Addr.getpin();
				}
				char* getConPhone()
				{
					return Phone;
				}
				float getBalance()
				{
					return Balance;
				}
				void Deposit(float amt)		//function for depositing money
				{
					Balance+=amt;
				}
				void Withdrawal(float amt) //function for withdrawing money
				{
					if(Balance<amt)
					cout<<"\nInsufficient Balance";
					else
					Balance-=amt;
				}
				void dispCustomer() //function to display customer
				{
					cout<<"\nName ";
					cout<<Name;
					cout<<"\nPhone ";
					cout<<Phone;
					cout<<"\nBalance ";
					cout<<Balance;
					cout<<"\nAddress ";
					Addr.dispaddress();
				}
};
class SavAcc:public Customer
{
	char SAccNum[6];
	float CalcInterest()	//method to calculate interest
	{
		return (6*getBalance())/100;
	}	
	public:
		void setSavAcc()  // set information of savings account holder 
		{
			do
			{
			cout<<"\nEnter account 5 digit accout number starting with 'S' ";
			fflush(stdin);
			gets(SAccNum);
			}while(checkAccNum(SAccNum,1));
		}
		char* getSAccNum()
		{
			return SAccNum;
		}
		void ShowSavAcc()
		{
			cout<<"\nSavings account number ";
			cout<<SAccNum;
			cout<<"\nInterest ";
			cout<<CalcInterest();
		}
};
class CurAcc:public Customer
{
	char CAccNum[6];
	float OverDraftAmount()		//function to calculate overdraft amount
	{
		if(getBalance()<=500000)
			return 0;
		return (40*getBalance())/100;
	}
	public:
		void setCurAcc() // set information of current account holder 
		{ 	
			do
			{
			cout<<"\nEnter account 5 digit accout number starting with 'C' ";
			fflush(stdin);
			gets(CAccNum);
			}while(checkAccNum(CAccNum,2));
		}
		char* getCAccNum()
		{
			return CAccNum;
		}
		void ShowCurAcc()
		{
			cout<<"\nCurrent account number ";
			cout<<CAccNum;
			cout<<"\nOverdraft amount ";
			cout<<OverDraftAmount();
		}
};
void AddSAcc()		//method to add a new savings account
{ 
	
	ofstream fp("Savings_account.dat",ios::binary|ios::app);
	SavAcc c1;	
	c1.setSavAcc();
	c1.setCustomer();
	fp.write((char*)&c1,sizeof(SavAcc));
	fp.close();
}
void AddCAcc()	//method to add a new current account
{ 
	
	ofstream fp("Current_account.dat",ios::binary|ios::app);
	CurAcc c1;	
	c1.setCurAcc();
	c1.setCustomer();
	fp.write((char*)&c1,sizeof(CurAcc));
	fp.close();
}
void delSAcc() 	////method to delete a savings account
{
	int flag=0;
	ifstream fin("Savings_account.dat",ios::in|ios::binary);
	fstream fout("temp.dat",ios::out|ios::binary);
	SavAcc c1;
	char AccNum[6];
	cout<<"\n Enter account number to be deleted ";
	fflush(stdin);
	gets(AccNum);
	if(!fin)
	{
		cout<<"File not found";
		exit(1);
	}	
	while(fin.read((char*)&c1,sizeof(c1)))
	{
		if(strcmp(c1.getSAccNum(),AccNum))
		{
			fout.write((char*)&c1,sizeof(c1));
		}
		else
		{
			flag++;
			cout<<"\nAccount Deleted!!!!";
		}
	}
	if(flag==0)
		cout<<"\nAccoount not found";
	fin.close();
	fout.close();
	remove("Savings_account.dat");
	rename("temp.dat","Savings_account.dat");
}
void delCAcc()		//method to delete a current account
{
	int flag=0;
	ifstream fin("Current_account.dat",ios::in|ios::binary);
	fstream fout("temp.dat",ios::out|ios::binary);
	SavAcc c1;
	char AccNum[6];
	cout<<"\n Enter account number to be deleted ";
	fflush(stdin);
	gets(AccNum);
	if(!fin)
	{
		cout<<"File not found";
		exit(1);
	}	
	while(fin.read((char*)&c1,sizeof(c1)))
	{
		if(strcmp(c1.getSAccNum(),AccNum))
		{
			fout.write((char*)&c1,sizeof(c1));
		}
		else
		{
			flag++;
			cout<<"\nAccount Deleted!!!!";
		}
	}
	if(flag==0)
	cout<<"\nAccoount not found";
	fin.close();
	fout.close();
	remove("Current_account.dat");
	rename("temp.dat","Current_account.dat");
}
void DepSAcc()	//method to deposit money in savings account
{
	float amt;
	int flag=0;
	fstream fp("Savings_account.dat",ios::in|ios::out|ios::binary);
	SavAcc c1;
	char AccNum[6];
	cout<<"\nEnter Savings Account Number ";
	fflush(stdin);
	gets(AccNum);
	while(fp.read((char*)&c1,sizeof(c1)))
	{
		if(!strcmp(c1.getSAccNum(),AccNum))
		{
			cout<<"\nEnter the the amount to be deposited ";
			cin>>amt;
			c1.Deposit(amt);
			fp.seekp(-1*sizeof(c1),ios::cur);
			fp.write((char*)&c1,sizeof(c1));
			flag++;
		}
	}
	if(flag==0)
		cout<<"\nAccount not found please try again";
	fp.close();
}
void WithSAcc()		//method to withdraw money from a savings account
{
	float amt;
	int flag=0;
	fstream fp("Savings_account.dat",ios::in|ios::out|ios::binary);
	SavAcc c1;
	char AccNum[6];
	cout<<"\nEnter Savings Account Number ";
	fflush(stdin);
	gets(AccNum);
	while(fp.read((char*)&c1,sizeof(c1)))
	{
		if(!strcmp(c1.getSAccNum(),AccNum))
		{
			cout<<"\nEnter the the amount to be debited ";
			cin>>amt;
			c1.Withdrawal(amt);
			fp.seekp(-1*sizeof(c1),ios::cur);
			fp.write((char*)&c1,sizeof(c1));
		flag++;
		}
	}
	if(flag==0)
		cout<<"\nAccount not found please try again";
	fp.close();
}
void DepCAcc()		//method to deposit money in current account
{
	float amt;
	int flag=0;
	fstream fp("Current_account.dat",ios::in|ios::out|ios::binary);
	SavAcc c1;
	char AccNum[6];
	cout<<"\nEnter Savings Account Number ";
	fflush(stdin);
	gets(AccNum);
	while(fp.read((char*)&c1,sizeof(c1)))
	{
		if(!strcmp(c1.getSAccNum(),AccNum))
		{
			cout<<"\nEnter the the amount to be deposited ";
			cin>>amt;
			c1.Deposit(amt);
			fp.seekp(-1*sizeof(c1),ios::cur);
			fp.write((char*)&c1,sizeof(c1));
			flag++;
		}
	}
	if(flag==0)
		cout<<"\nAccount not found please try again";
	fp.close();
}
void WithCAcc()		//method to withdraw money from a current account
{
	float amt;
	int flag=0;
	fstream fp("Current_account.dat",ios::in|ios::out|ios::binary);
	CurAcc c1;
	char AccNum[6];
	cout<<"\nEnter Current Account Number ";
	fflush(stdin);
	gets(AccNum);
	while(fp.read((char*)&c1,sizeof(c1)))
	{
		if(!strcmp(c1.getCAccNum(),AccNum))
		{
			cout<<"\nEnter the the amount to be debited ";
			cin>>amt;
			c1.Withdrawal(amt);
			fp.seekp(-1*sizeof(c1),ios::cur);
			fp.write((char*)&c1,sizeof(c1));
			flag++;
		}
	}
	if(flag==0)
		cout<<"\nAccount not found please try again";
	fp.close();
}
void ViewSAcc()		//method to view a savings account
{
	int flag=0;
	SavAcc c1;
	char Accnum[6];
	cout<<"\nEnter the account number ";
	fflush(stdin);
	gets(Accnum);
	ifstream fin("Savings_account.dat",ios::in|ios::binary);
	if(!fin)
	{
		cout<<"\nCannot open file ";
		exit(1);
	}
	while(fin.read((char *)&c1, sizeof(SavAcc)))
	{
		if(!strcmp(Accnum,c1.getSAccNum()))
		{
			c1.ShowSavAcc();
			c1.dispCustomer();
			flag++;
		}
	}
	if(flag==0)
	cout<<"\n\tAccount not found!!!";
	fin.close();
}
void ViewCAcc()		//method to view a savings account
{
	int flag=0;
	CurAcc c1;
	char Accnum[6];
	cout<<"\nEnter the account number ";
	fflush(stdin);
	gets(Accnum);
	ifstream fin("Current_account.dat",ios::in|ios::binary);
	if(!fin)
	{
		cout<<"\nCannot open file ";
		return;
	}
	while(fin.read((char *)&c1, sizeof(CurAcc)))
	{
		if(!strcmp(Accnum,c1.getCAccNum()))
		{
			c1.ShowCurAcc();
			c1.dispCustomer();
			flag++;
		}
	}
	if(flag==0)
	cout<<"\n\tAccount not found!!!";
	fin.close();
}
int main()
{   char c=176;
	int opt;
	do
	{
		cout<<"\n\n1:Add Savings Account";
		cout<<"\n2:Add Current Account";
		cout<<"\n3:View Savings Account";
		cout<<"\n4:View Current Account";
		cout<<"\n5:Deposit in Savings Account";
		cout<<"\n6:Deposit in Current Account";		
		cout<<"\n7:Withdrawl From Savings Account";
		cout<<"\n8:Withdrawl From Current Account";
		cout<<"\n9:Delete Savings Account";
		cout<<"\n10:Delete Current Account";
		cout<<"\n0:Exit\n";
		cout<<c<<c<<"Enter your choice :- ";
		cin>>opt;
		switch (opt)
		{
			case 1:AddSAcc();
					break;
			case 2:AddCAcc();
					break;
			case 3:ViewSAcc();
					break;
			case 4:ViewCAcc();
					break;
			case 5:DepSAcc();
					break;
			case 6:DepCAcc();
					break;
			case 7:WithSAcc();
					break;
			case 8:WithCAcc();
					break; 
			case 9:delSAcc();
					break;
			case 10:delCAcc();
					break;
			case 0:cout<<"\n\n\t\t"<<c<<c<<" THANKS FOR USING BANKING SYSTEM "<<c<<c<<"\n";
					break;
			default:cout<<"\nEnter the correct option";
		}
	}while(opt);
	fflush(stdin);
	getchar();
	return 0;
}	
bool checkAccNum(char* AccNum,int j)	//method to check account number
{  
	int i;
	if(j==2)
	{
		if (*AccNum !='C')
			{
				cout<<"\n\nEnter Correct Account Number";
				return true;
			}
		CurAcc c;
		ifstream f1("Current_account.dat",ios::out|ios::binary);
		while(f1.read((char *)&c,sizeof(CurAcc)))
		{
			if(!strcmp(AccNum,c.getCAccNum()))
			{
			cout<<"\n\nAccNum Already Used Use a New One";
			f1.close();
			return true;
			}
		}
	}
	else if(j==1)
	{
		if(*AccNum!='S')
			{
				cout<<"\n\nEnter Correct Account Number";
				return true;
			}
		SavAcc c1;
		ifstream f2("Savings_account.dat",ios::out|ios::binary);
		while(f2.read((char *)&c1,sizeof(SavAcc)))
		{
			if(!strcmp(AccNum,c1.getSAccNum()))
			{
			cout<<"\n\nAccNum Already Used Use a New One";
	    	f2.close();
			return true;
			}
		}
	}
	i=strlen(AccNum);
	if (i!=6)
	{
		cout<<"\n\nEnter Correct Account Number";
		return true;
	}
	for(i=1;i<6;i++)
	{
		if(AccNum[i]<0&&AccNum[i]>9)
		{
			cout<<"\n\nEnter Correct Account Number";
			return true;
		}
	}
		
	return false;
}
