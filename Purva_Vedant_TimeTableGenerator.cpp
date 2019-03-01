
#include<bits/stdc++.h>
#include<string.h>
using namespace std;
class teacher;
class sec
{
	public:
	static int class_count;
	int tt[5][6];
	string name;
	char t_code[6][3];				//teacher code of 6 teachers each of 3 char
    int i,j;
		sec()
		{
			class_count=0;
			for(i=0;i<5;i++)
			{
				for(j=0;j<6;j++)
				{
					tt[i][j]=6;
				}
			}
		}
		void prepare()
		{
			int i;
			class_count++;
			cout<<"\nEnter Name of class "<<class_count<<": ";
			cin>>name;
			cout<<"\nEnter all 6 course's faculty codes"<<endl;
			for(i=0;i<6;i++)
			{
				for(j=0;j<3;j++)
					cin>>t_code[i][j];
			}
		}
		void disp()
		{
			int i,j;
			cout<<"\nClass: "<<name<<endl;
			for(i=0;i<6;i++)
			{
				cout<<"Faculty "<<i<<" code: ";
				for(j=0;j<3;j++)
				{
					cout<<t_code[i][j];
				}
				cout<<endl;
			}
		}
		int check(int day,int slot)		//to check and allot slot if free
		{
			if(tt[day][slot]==6)
				{
					return 1;
				}
			return 0;
		}
		
		friend void called(sec s,teacher a,teacher b,teacher c,teacher d,teacher e,teacher f);
};
int sec::class_count;
class teacher{
		static int t_count;
	public:
		int no_classes,day,slot,i,j;
		char t_code[3],name[20];				//teacher code of 3 char
		int tt[5][6];
		
		teacher()
		{
			t_count=0;
			for(i=0;i<5;i++)
			{
				for(j=0;j<6;j++)
				{
					tt[i][j]=0;
				}
			}
		}
		
		void get()
		{
			t_count++;
			cout<<"\nEnter Name of the teacher "<<t_count<<": ";
			cin>>name;
			cout<<"Enter 3 charachtered teacher code: ";
			cin>>t_code;
			cout<<"Enter the no. of classes "<<name<<" will take: ";
			cin>>no_classes;
		}
		void not_free(int day, int slot);
		void busy_slots()
		{
			int f,i,busy;
			int count=30-4*no_classes;
			cout<<"\nYou can take leave on max "<<count<<" slots";
			cout<<"\nEnter days and slots on which you can't take class\nMon-Fri is day 1-5\n9-10:slot1; 10-11:slot2; 11-12:slot3; 1-2:slot4; 2-3:slot5; 3-4:slot6\n";
			cout<<"\nEnter the no. of slots you will be busy: ";
			cin>>busy;
			for(i=0;i<busy;i++)
			{
				cout<<"\nEnter day and slot: ";
				cin>>day>>slot;
				not_free(day,slot); 
			}
		}
		void disp()
		{
			for(i=0;i<5;i++)
			{
				for(j=0;j<6;j++)
				{
					cout<<tt[i][j]<<"\t";
				}
				cout<<endl;
			}
		}
		friend void called(sec s,teacher a,teacher b,teacher c,teacher d,teacher e,teacher f)
		{
			int tmp,i,j,x,k;
			teacher lect[6];
			lect[0]=a;
			lect[1]=b;
			lect[2]=c;
			lect[3]=d;
			lect[4]=e;
			lect[5]=f;
			int cnt;
			srand(time(NULL));
			for(i=0;i<6;i++)		//for each teacher
			{
				//cout<<"\n preparing tt for teacher "<<lect[i].name;
				cnt=0;
				for(j=0;j<5;j++)	//for each day
				{
					x=(rand()%7);
					if(x!=6)
					{
						if(lect[i].check(j,x) && s.check(j,x) && cnt<4)
						{
							s.tt[j][x]=i;
							lect[i].tt[j][x]=2;
							cnt++;
						//	cout<<"\n "<<cnt;
						}
					}
				}
				//cout<<"\n random was not successful "<<cnt;
				if(cnt<4)
				{
					int f_cnt=0;
					for(j=0;j<5;j++)
					{
						for(k=0;k<6;k++)
						{
							if(lect[i].check(j,k) && s.check(j,k))
							{
								s.tt[j][k]=i;
								lect[i].tt[j][k]=2;
							//	cout<<endl<<cnt;
								cnt++;
								if(cnt>=4)
								{
									f_cnt=1;
									break;
								}
							}
							if(f_cnt==1)
								break;
						}
						if(f_cnt==1)
							break;
					}
				}
			}	
			cout<<"\n\nTime table of class "<<s.name<<endl<<endl;
			cout<<"D/T |\t09-10\t10-11\t11-12\t12-01\t01-02\t02-03\t03-04"<<endl<<"____|_________________________________________________________"<<endl<<"    |"<<endl;
			for(i=0;i<5;i++)
			{
				if(i==0)
					cout<<"MON |\t";
				if(i==1)
					cout<<"TUE |\t";
				if(i==2)
					cout<<"WED |\t";
				if(i==3)
					cout<<"THU |\t";
				if(i==4)
					cout<<"FRI |\t";
				
				for(j=0;j<6;j++)
				{
					if(j==3)
					{
						if(i==0)
							cout<<"| B |\t";
						if(i==1)
							cout<<"| R |\t";
						if(i==2)
							cout<<"| E |\t";
						if(i==3)
							cout<<"| A |\t";
						if(i==4)
							cout<<"| K |\t";
					}
					if(s.tt[i][j]==6)
					{
						cout<<"---"<<"\t";
					}
					else
					{
						cout<<lect[s.tt[i][j]].t_code<<"\t";
					}
					
				}
				cout<<endl;
				cout<<"----|---------------------------------------------------------"<<endl;
			}
			fstream file;
			file.open("TimeTable1.txt", ios::app|ios::out);
			file<<"\n\nTime table of class "<<s.name<<endl<<endl;
			file<<"D/T |\t09-10\t10-11\t11-12\t12-01\t01-02\t02-03\t03-04"<<endl<<"____|_________________________________________________________"<<endl<<"    |"<<endl;
			for(i=0;i<5;i++)
			{
				if(i==0)
					file<<"MON |\t";
				if(i==1)
					file<<"TUE |\t";
				if(i==2)
					file<<"WED |\t";
				if(i==3)
					file<<"THU |\t";
				if(i==4)
					file<<"FRI |\t";
				
				for(j=0;j<6;j++)
				{
					if(j==3)
					{
						if(i==0)
							file<<"| B |\t";
						if(i==1)
							file<<"| R |\t";
						if(i==2)
							file<<"| E |\t";
						if(i==3)
							file<<"| A |\t";
						if(i==4)
							file<<"| K |\t";
					}
					if(s.tt[i][j]==6)
					{
						file<<"---"<<"\t";
					}
					else
					{
						file<<lect[s.tt[i][j]].t_code<<"\t";
					}
					
				}
				file<<endl;
				file<<"----|---------------------------------------------------------"<<endl;
			}
			file.close();
		}
	int check(int day,int slot)		//to check slot if free
	{
		if(tt[day][slot]==0)
			{
				return 1;
			}
		return 0;
	}
};
int teacher::t_count;
void teacher::not_free(int day,int slot)
{
	tt[day-1][slot-1]=1;
}
int main()
{
	fstream file;
	file.open("TimeTable1.txt", ios::app|ios::out);
	file<<"\t\t\t\tTimetable Generator\n";
	cout<<"\t\t\t\tTimetable Generator\n";
	cout<<"\n\tWhile giving inputs kindly provide ONLY what is asked for errorless execution!";
	cout<<"\n-------------------------------------------------------------------------------------------------------------------\n";
	int n,i,j,k;
	cout<<"\nEnter total number of teachers in school: ";
	cin>>n;
	teacher t[n];
	for(i=0;i<n;i++)
	{
		t[i].get();
		t[i].busy_slots();
		t[i].disp();
	}
	
	int num_class;
	cout<<"\nEnter total number of classes in the School: ";
	cin>>num_class;
	cout<<"\nEnter details of all the Classes "<<endl;
	sec cl[num_class];
	for(i=0;i<num_class;i++)
	{
		cl[i].prepare();
	}
	cout<<"\nClass and Faculty Details"<<endl;
	for(i=0;i<num_class;i++)
	{
			cl[i].disp();
	}
	//The loop starts for assigning time-table to section/class
	int z;
	for(z=0;z<num_class;z++)
	{
		int f=0,p=0;
		int arr[6];
		for(i=0;i<6;i++)
		{
			for(j=0;j<n;j++)
			{
				for(k=0;k<3;k++)
				{
					if((cl[z].t_code[i][k])==(t[j].t_code[k]))
					{
						f=1;
					}
					else
					{
						f=0;
						break;
					}
				}
				if(f==1)
					{
						arr[p++]=j;
					}
			}
			
		}
		
		//cout<<"\n Ready to call frnd func for "<<cl[z].name<<endl;
		called (cl[z],t[arr[0]],t[arr[1]],t[arr[2]],t[arr[3]],t[arr[4]],t[arr[5]]);
	}
	


