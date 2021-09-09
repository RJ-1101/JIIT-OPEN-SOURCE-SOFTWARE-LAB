#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
class Contenders
{
    private:
        string name;
        ll doses;
        float vaccineperdose;
        ll vaccine;
        ll days;
        ll transcost;
        ll perdosecost;
        ll totalvaccine;
        ll medicost;
        ll totalcost;
    public:
        Contenders()
        {
          days = 0;
          totalvaccine=0;
        }
        void min_days(ll a[1000],ll n);
        void tvac(ll a[1000],ll n);
        void country_name(string n);
        void cal();
        void transport();
        void output();
        void final1();
};
Contenders c[26];
multimap<ll,string> m1,m2;
bool cmp(pair<ll,string>& a, pair<ll,string>& b) 
{ 
    return a.first < b.first; 
}
void sortmap(multimap<ll,string>& M) 
{
    vector<pair<ll,string> > m; 
    for (auto& it : M) 
    { 
        m.push_back(it); 
    } 
    sort(m.begin(), m.end(), cmp); 
} 
void Contenders::tvac(ll a[1000],ll n)
{
  ll i,pos=n;
  ll k = vaccine;
    for(i=0;i<n;i++)
    {
        if(a[i]>=(k+1)/2)
        {
            pos=i;
            break;
        }
      totalvaccine += k;
    }
    a[n+1]=INT_MAX;
    for(i=pos;i<n;)
    {
        if(a[i]<=k)
        {
            if(a[i+1]>k)
            {
                k = 2*a[i];
            }
            i++;
        }
        else
        {
            k = k*2 ;
        }
        totalvaccine += k;
    }
    medicost = (totalvaccine / vaccineperdose) * perdosecost;
}
void Contenders::output()
{
    cout<<"\n\nName: "<<name<<"\n";
    cout<<"Doses: "<<doses<<"\n";
    cout<<"Vaccine per Dose: "<<vaccineperdose<<"\n";
    cout<<"Vaccine: "<<vaccine<<"\n";
    cout<<"Min Number of Days: "<<days<<"\n";
    cout<<"Transportation Cost: "<<transcost<<"\n";
    cout<<"Cost per Dose: "<<perdosecost<<"\n";
    cout<<"Total Vaccine Supplied: "<<totalvaccine<<"\n";
    cout<<"Medical Cost: "<<medicost<<"\n";
    cout<<"Total Cost: "<<totalcost<<"\n";
    cout<<"\n";
}
void Contenders::min_days(ll arr[1000],ll n)
{
    ll i,j,x,pos=1;
    ll a[1000]={0};
    for(i=1;i<=n;i++)
    {
      a[i]=arr[i];
    }
    x = vaccine;
    if(a[n]<=x)
    {
        days += n;
    }
    else 
    {
      for(i=1;i<=n;i++)
      {
        if(x<a[i])
        {
          pos=i;
          break;
        }
      }
      for(i=1;i<pos;i++)
      {
        if(x==a[i])
        {
          x *=2;
          days++;
        }
        else
        {
          days++;
        }
        totalvaccine += x;
      }
      if(pos>1)
      {
        if((2*a[pos-1])>=x)
        {
          x = 2*a[pos-1];
        }   
      }
      for(i=pos;i<=n;i++)
      {
        if(a[i]!=0 && x>=a[i])
        {
          days++;
          x = 2*a[i];
          a[i]=0;
        }
        else if(x<a[i] && a[i]!=0)
        {
          while(2*(a[i]-x)>a[i])
          {
            days++;
            x = x*2;
          }
          if(2*(a[i]-x)==a[i])
          {
            days+=2;
            x = 2*a[i];
            a[i]=0;
          }
          if(a[i]!=0)
          {
            for(j=i+1;j<=n;j++)
            {
              if(2*(a[j]-x)>=a[j])
              {
                days++;
                x *=2;
                break;
              }
            }
            if(x>=a[i])
            {
              x = 2*a[i];
              a[i]=0;
              days++;
            }
            if(x<a[i])
            {
              while(a[i]!=0)
              {
                if(2*(a[i]-x)<a[i] && x<a[i])
                {
                  a[i] -= x;
                  a[i] *=2;
                  x = x*2;
                  days++;
                }
                else
                {
                  a[i]=0;
                  days++;
                }
              }
            }   
          }
        }
      }
    }
}
void Contenders::transport()
{
    ll z = totalvaccine/vaccineperdose;
    if(z<=1000)
    {
        transcost = z*50;
    }
    else if(z>1000 && z<=4000)
    {
        transcost = 100*z - 50000;
    }
    else if(z>4000 && z<=10000)
    {
        transcost = 150*z - 250000;
    }
    else
    {
        transcost = 180*z - 550000;
    }
    totalcost = transcost + medicost;
}
void Contenders::cal()
{
    ll x,z;
    float y;
    cin>>doses>>vaccineperdose>>perdosecost;
    vaccine = doses * vaccineperdose;
}
void Contenders::country_name(string n)
{
    name = n;
}
void Contenders::final1()
{
  m1.insert(pair<ll,string> (days,name));
  m2.insert(pair<ll,string> (totalcost,name));
}
void f1()
{  
  int rank1=0; 
  ll temp_days=0;
  cout<<"\n\n\t\t\tRanking of Contendars based on Minimum Number of Days\n\n";
  cout<<"\n\n\t\t\tRank"<<"\t\tContendar Name\t\t\t\tDays\n";
  for (auto itr = m1.begin(); itr != m1.end(); ++itr) 
  { 
     if(temp_days!=itr->first)
    {
      rank1++;
      temp_days=itr->first;
    }
    cout<<"\n\t\t\t"<<rank1<<"\t\t\t"<<itr->second<<":\t\t\t"<<itr->first<<"\n"; 
  }

}
void f2()
{
  int rank1=0;
  ll temp_cost=0; 
  cout<<"\n\n\t\t\tRanking of Contendars based on Minimum Cost\n\n";
   cout<<"\n\n\t\t\tRank"<<"\t\tContendar Name\t\t\t\tCost\n"; 
  for (auto itr = m2.begin(); itr != m2.end(); ++itr) 
  { 
      if(temp_cost!=itr->first)
    {
      rank1++;
      temp_cost=itr->first;
    }
    cout<<"\n\t\t\t"<<rank1<<"\t\t\t"<<itr->second<<":\t\t\t"<<itr->first<<"\n";
  } 
}
struct temp_contendar
{
string tname;
int tindex; 
};
bool comp(temp_contendar a, temp_contendar b)
{
  if(a.tindex!=b.tindex)
  {
    return a.tindex<b.tindex;
  }
  return 0; 
}
void f3()
{
  int k=0,i=0; ll temp_days;
  temp_days=m1.begin()->first;
  struct temp_contendar min[25];
  for(auto itr=m1.begin();itr !=m1.end(); ++itr)
   {
      if(temp_days!=itr->first)
    {
     break;
    }
      else
    {
     min[k].tname=itr->second;
     min[k].tindex=1;
     k++;
    }
   }
   int x;
  for(i=0;i<k;i++)
  {
    x=1;
  for (auto itr = m2.begin(); itr != m2.end(); ++itr) 
  { 
    if(itr->second==min[i].tname)
  {
    min[i].tindex=min[i].tindex + x;
    break;
  }
    x++;
  }
  } 
sort(min,min+k,comp);
cout<<"\n\n\t\t\tBest Contendar based on Minimum Cost & Minimum Number of Days\n\n";
for(i=0;i<k-1;i++)
{
  cout<<"\n\t\t\t\t"<<i+1<<"\t\t"<<min[i].tname<<"\n\n";
  if(min[i].tindex!=min[i+1].tindex)
  {
    break;
  }
}
}
void main1()
{ 
    ll n,i,x,y,z;
    ll a[1000];
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    c[1].country_name("A Pharma (Argentina)");
    c[2].country_name("B Pharma (Belgium)");
    c[3].country_name("C Pharma (Canada)");
    c[4].country_name("D Pharma (Denmark)");
    c[5].country_name("E Pharma (Estonia)");
    c[6].country_name("F Pharma (France)");
    c[7].country_name("G Pharma (Germany)");
    c[8].country_name("H Pharma (Hungary)");
    c[9].country_name("I Pharma (Italy)");
    c[10].country_name("J Pharma (Japan)");
    c[11].country_name("K Pharma (Korea)");
    c[12].country_name("L Pharma (Liberia)");
    c[13].country_name("M Pharma (Maldives)");
    c[14].country_name("N Pharma (Nigeria)");
    c[15].country_name("O Pharma (Oman)");
    c[16].country_name("P Pharma (Poland)");
    c[17].country_name("Q Pharma (Qatar)");
    c[18].country_name("R Pharma (Russia)");
    c[19].country_name("S Pharma (Serbia)");
    c[20].country_name("T Pharma (Turkey)");
    c[21].country_name("U Pharma (England");
    c[22].country_name("V Pharma (Vietnam");
    c[23].country_name("W Pharma (Württemberg)");
    c[24].country_name("Y Pharma (Yemen)");
    c[25].country_name("Z Pharma (Zembia)");
    for(i=1;i<=25;i++)
    {
      c[i].cal();
    }
    for(i=1;i<=25;i++)
    {
      c[i].tvac(a,n);
      c[i].min_days(a,n);
      c[i].transport();
      c[i].final1();
    }
    sortmap(m1);
    sortmap(m2);
}
struct details    //to save details of the user  
{ 
char uname[100]; 
int age; 
char password[100]; 
char email[100]; 
char mobile[10]; 
}; 

int flag = 1, i, j = 0, count = 0, f=0;
int caps = 0, small = 0, special = 0, numbers = 0; 
int success = 0, x, choice; 
char temp_name[100], temp_password1[100], temp_password2[100], temp_email[100], temp_mobile[100]; 
int search_choice, temp_age; 
struct details s[100];
void signup();
void account_check(); 
int validate(); 
void login();
int accounts=0;
 
int main() 
{ 
  freopen("input.txt", "r", stdin);
int y=1;
while(y)
{
cout<<"\n\n\n\t\tWelcome to COVI-TRANS STATISTICS: A TOOL FOR VACCINE DISTRIBUTION SOLUTION";
cout<<"\n\n\n1)-SIGNUP\n\n2)-LOGIN\n\n3)-EXIT\n\n"; 
cout<<"\n\nEnter your choice: "; 
cin>>choice; 
switch(choice) 
{ 
case 1: 
{ 
signup(); 
break; 
} 
case 2: 
{ 
login(); 
y=0;
break; 
} 
case 3: 
{ 
return 0; 
} 
default: 
{ 
cout<<"\nPlease Enter the valid choice!!\n"; 
break; 
} 
}
}
} 

void account_check()      //to check whether the email and password already exists 
{ 
for(i=0; i<100; i++) 
{ 
if(!(strcmp(temp_email, s[i].email) && strcmp(temp_password1, s[i].password))) 
{ 
cout<<"\n\n\t\t\tAccount Already Exist. Please Login!!"; 
main(); 
break; 
} 
} 
if(i==100) 
{ 
strcpy(s[j].uname, temp_name); 
s[j].age = temp_age; 
strcpy(s[j].password, temp_password1); 
strcpy(s[j].email, temp_email); 
strcpy(s[j].mobile, temp_mobile); 
j++; 
cout<<"\n\n\t\t\tAccount Successfully Created!!"; 
} 
}  

int validate()   //to check the validation of the data entered by the user to create account          
{  
for(i=0; temp_name[i] !='\0'; i++)      // To validate the name 
{ 
if(!((temp_name[i] >= 'a' && temp_name[i] <= 'z') || (temp_name[i] >= 'A' && temp_name[i] <= 'Z'))) 
{ 
cout<<"\nPlease enter Valid Name!!";    
flag = 0; 
break; 
} 
} 
if(flag==1) 
{ 
ll count = 0; 
for(i=0; temp_email[i] !='\0'; i++)          // To validate the Email ID
{ 
if(temp_email[i]=='@'|| temp_email[i]=='.') 
{
count++; 
}        
} 
if(count >=2 && strlen(temp_email) >=5) 
{ 
if(!strcmp(temp_password1,temp_password2))    //To validate the password and check it with confirm password
{ 
if(strlen(temp_password1) >=8 && strlen(temp_password1) <=12)
{ 
caps = 0;
small = 0; 
numbers = 0; 
special = 0; 
for(i =0; temp_password1[i] !='\0'; i++) 
{ 
if(temp_password1[i] >='A' && temp_password1[i] <='Z') 
caps++; 
else if(temp_password1[i] >='a' && temp_password1[i] <='z') 
small++; 
else if(temp_password1[i] >= '0' && temp_password1[i] <='9') 
numbers++; 
else if (temp_password1[i] == '@'|| temp_password1[i] == '&' || temp_password1[i] == '#'|| temp_password1[i] == '*') 
special++; 
}
if(caps >= 1 && small >= 1 && numbers >= 1 && special >= 1) 
{ 
if(temp_age != 0 && temp_age > 0)         // To validate the age 
{ 
if(strlen(temp_mobile) == 10)  // To validate the mobile number
{ 
for(i = 0; i < 10; i++) 
{ 
if(temp_mobile[i]>= '0' && temp_mobile[i] <= '9') 
{ 
success = 1; 
} 
else
{ 
cout<<"\nPlease Enter valid Mobile Number!!";
return 0; 
break; 
} 
} 
if(success == 1) 
return 1; 
} 
else 
{ 
cout<<"\nPlease Enter 10 Digit Mobile Number!!";
return 0; 
} 
} 
else 
{ 
cout<<"\nEnter Valid Age!!";
return 0; 
} 
} 
else 
{ 
cout<<"\n\nPlease Enter the strong password, Your password must contain atleast one uppercase, Lowercase, Number and special character\n\n"; 
return 0; 
} 
} 
else 
{ 
cout<<"\nYour Password is very short Length. Length must be between 8 to 12\n\n"; 
return 0; 
} 
} 
else 
{ 
cout<<"\nPassword Mismatch"; 
return 0; 
} 
} 
else 
{ 
cout<<"\nPlease Enter Valid E-Mail"; 
return 0;
} 
} 
return 0; 
}
void signup() //to create mew user account 
{ 
cout<<"\nEnter Your name: ";
cin>>temp_name;  
cout<<"\nEnter Your Age: "; 
cin>>temp_age; 
cout<<"\nEnter Your Email: "; 
cin>>temp_email; 
cout<<"\nEnter Password: "; 
cin>>temp_password1; 
cout<<"\nConfirm Password: "; 
cin>>temp_password2; 
cout<<"\nEnter Your Mobile Number: "; 
cin>>temp_mobile; 
x = validate(); 
if(x==1) 
account_check(); 
}
void login()  
{ 
int check1=0;
cout<<"\n\nLOGIN"; 
cout<<"\n\nEnter Your Email: "; 
cin>>temp_email; 
cout<<"\nEnter Your Password: "; 
cin>>temp_password1; 
for(f = 0; f<100; i++) 
{
if(!strcmp(s[f].email, temp_email)) 
{ 
if (!strcmp(s[f].password, temp_password1))
{ 
check1=1; 
} 
else 
{ 
cout<<"\nInvalid Password! Please Enter the correct password";  
} 
break;
}  
}
if(check1==0)
{
cout<<"\nAccount does not exist!!";
main();  
}
else 
{
main1();
while(1)
{
cout<<"\n\nWelcome "<<s[f].uname<<"!!"; 
cout<<"\n\n\t\t\tYou are successfully logged in";
cout<<"\n\n\nSelect from the following options"; 
cout<<"\n\n1)-Display Info about all Vaccine Contendars"; 
cout<<"\n\n2)-Display contendars based on Minimum cost";
cout<<"\n\n3)-Display contendars based on Minimum Number of days required to vaccinate the region";
cout<<"\n\n4)-Display contendars based on both the above factors";
cout<<"\n\n5)-Log Out";
cout<<"\n\nPlease Enter your choice: "; 
cin>>search_choice; 
switch (search_choice)
{ 
case 1: 
{
cout<<"\n\n\t\t\t\tInformation of All Bidding Contendars\n";
for(i=1;i<=25;i++)
{
c[i].output();
}           
break; 
} 
case 2: 
{
f2();
break; 
} 
case 3: 
{ 
f1();
break;
}
case 4:
{
f3();
break;
}
case 5: 
{
  cout<<"\n\n\t\t\tYou have been successfully Logged Out!!";
  return;
}
default: 
{ 
cout<<"\nPlease Enter the valid choice"; 
break; 
} 
}
}
}
}