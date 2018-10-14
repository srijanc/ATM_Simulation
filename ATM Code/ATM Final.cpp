//////*******************************************************************************//////
//////******************************** ATM SIMULATOR *******************************//////
//////*****************************************************************************//////

//header files used//

#include<iostream>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<cstdlib>
#include<process.h>
#include<ctime>

using namespace std;

//global variables//

string pno = "";              //pin no.//
string name = "";             //account holder's name//
string ano = "";              //account no.//
string acct = "";             //account type//
string cno = "";              //card no.//
string amt = "";              //total balance available//
string pin_no = "";           //pin no.//
string pass="";               //account password//
int flag,flag2=0;             //on off variable//
long int a = 0;               //total amount to store the string value when converted into integer//
int at = 0;                   //amount for cash withdrawal//
char line[200];               //details of the given account//


class atm
{
      public:
        void trans();          //function to display last 10 transactions//


//***********************************************************//
//    FUNCTION FOR ENTERING THE AMOUNT TO BE WITHDRAWN      //
//*********************************************************//

void enter_w()
{
       ofstream out;
       out.open("temp1.txt",ios::app);                       //to open the file in which data is to be written in Append Mode//

       if(!out)
       {
	   cout<<"Cannot open the Record file!!!\n";
       return;
       }

	   out<<strtok(line,"*")<<"*";                         //As Above//
       for(int i=1;i<=4;i++)
       out<<strtok(NULL,"*")<<"*";

       char* p = strtok(NULL,"*");                         //tokenizing the balance amount which is in string//
       char* end;                                          //for containing the address of the tokenized string//
       a = strtol(p,&end,10);                              //function for conversion of string to long integer//


       //**********   CONDITIONS FOR WITHDRAWING THE AMOUNT    **********/////


       cout<<"\nEnter the amount in multiple of 100 only : \n"<<"Rs. : ";
       while(1)
       {
       cin>>at;

          if(!(at%100))
          {

                  if(at<a)
                  {

                          if(25000>=at)
                          {
                           a = a-at;
                           break;
                           }

                          else
                          {
                              cout<<"\nEntered Amount has exceeded the Withdrawal Limit\n";
                              cout<<"\nRe Enter the ammount :\n"<<"Rs. : ";
                          }
                  }

                  else
                  {
                  cout<<"\nEntered Amount is more than your available Balance\nAs your Available Balance is just : "<<a<<"\n";
                  cout<<"\nRe Enter the ammount :\n"<<"Rs. : ";
                  }
          }

          else
          {
          cout<<"\nEntered amount is Not In Multiple of 100\n";
          cout<<"\nRe Enter the ammount :\n"<<"Rs. : ";
          }
       }

       out<<a<<"*"<<endl;
       out.close();      //to close the temp file in which the data is copied//

       cout<<"\nYour Transaction Is In Process\n";
       return;
}



//***************************************************************************//
//           FUNCTION FOR DISPLAYING THE CURRENT ACCOUNT BALANCE            //
//*************************************************************************//

void balance()
{

 ifstream in;
 in.open("atm.txt");

 if(!in)
   {
    cout<<"\nRecord File not found...!!!!\n";
    return;
   }

   while(!in.eof())
    {
     in.getline(line,255);

     for(int i=0;i<4;i++)
      {
       if(line[i] == pass[i])
	   flag=0;

       else
	    {
	     flag=1;
	     break;
     	}
      }

      if(flag==0)
      break;
     }

  if(flag==0)
   {
     strtok(line,"*");

     for(int i=1;i<5;i++)
     strtok(NULL,"*");

     cout<<"\nYour Available Account Balance is : ";
     cout<<strtok(NULL,"*")<<"\n";
   }

     in.close();

}


//*****************************************************************************************************//
//          FUNCTION FOR DISPLAYING THE ACCOUNT DETAIL OF THE ACCOUNT RELATED TO ENTERED PIN          //
//***************************************************************************************************//


void search()
{

while(1)
{

ifstream in;
in.open("atm.txt");

if(!in)
   {
    cout<<"\nRecord File not found...!!!!\n";
    return;
   }

   while(!in.eof())
    {
     in.getline(line,255);

     for(int i=0;i<4;i++)
      {
       if(line[i] == pass[i])
	   flag=0;

       else
	    {
	     flag=1;
	     break;
     	}
      }

      if(flag==0)
      break;
     }

if(flag==0)                                        //if the entered pin no. matches with the pin no. in the record//
   {
     char *p;                                      //Character pointer for storing the tokenized value and the printing it//

       p=strtok(line,"*");                         //tokenizing and printing pin no.//
       cout<<"\nPIN NO    : "<<"****";

       p=strtok(NULL,"*");                         //tokenizing and printing account holder's name//
       cout<<"\nNAME      : "<<p;

       p=strtok(NULL,"*");                         //tokenizing and printing account no.//
       cout<<"\nAcc. No.  : "<<p;

       p=strtok(NULL,"*");
       cout<<"\nAcc. Type : "<<p;                  //tokenizing and printing type of account//

       p=strtok(NULL,"*");
       cout<<"\nCARD No.  : "<<p;                  //tokenizing and printing ATM card no.//

       p=strtok(NULL,"*");
       cout<<"\nTotal Bal.: "<<p;                  //tokenizing and printing available balance//

       break;

   }

in.close();

}
}


//*****************************************************************************************//
//               TO INPUT THE NEW PIN WHEN PASSWORD UPDATE IS REQUIRED                    //
//***************************************************************************************//


void input_p()
{
int count = 1;
cout<<"\n\nConfirm Pin No. : ";                  //for confirming the original pin no. of the account//

while(1)
{
char c = ' ';
pass = "";

while(c!=13)
{
c=getch();
if(c!=13)
{
pass+=c;
cout<<"*";
}
}

if(pin_no != pass)                               //if the pin entered while conforming does not match with the real pin no.//
{
                                                 //conditions for counting the maximum no. of times password can be entered//
     if(count<=3)
       {
       cout<<"\nWrong PIN\n";
       count++;

         if(count>3)
         {
         cout<<"\nNo. of trials for entering your PIN is over and YOUR CARD IS BLOCKED\n";
         getch();
         exit(0);
         }

       if(count == 3)
       cout<<"\n\nThis is the Last Attempt to enter your correct PIN otherwise : \n\n\t\t YOUR CARD WILL BE BLOCKED\n\n";

       cout<<"\nRe-Enter the Pin No. : ";

       }

      else
      break;

}

else                     //to get out of the main loop if the password is matched//
break;

}

 ifstream in;
 in.open("atm.txt");              //As Above//

 if(!in)
   {
    cout<<"\nRecord File not found...!!!!\n";
    return;
   }

while(1)
{

 while(!in.eof())
    {

    in.getline(line,255);

      for(int i=0;i<4;i++)
        {
         if(line[i] == pass[i])
	     flag=0;

         else
	      {
	       flag=1;
	       break;
     	  }

        }

        if(flag==0)
        break;

     }

if(flag==0)
     {

       string p = "";                        //to tokenise the pin no. and replace it with the new pin no//
       p=strtok(line,"*");

cout<<"\n\nEnter the new PIN of exactly 4 DIGITS else first 4 digits will only be valid\n\n";
cout<<"\nNew PIN : ";

int x = 0;
char c = ' ';
pass = "";

while(c!=13 && x<4)                 //to enter the new pin and to check that it should not exceed 4 digits//
{
c=getch();

x++;

if(c!=13)
{
pass+=c;
cout<<"*";
}
}

       pno = pass;                          //As Above//

       p=strtok(NULL,"*");
       name = p;

       p=strtok(NULL,"*");
       ano = p;

       p=strtok(NULL,"*");
       acct = p;

       p=strtok(NULL,"*");
       cno = p;

       p=strtok(NULL,"*");
       amt = p;

       break;

     }

     else
     return;

}
}

//***************************************************************************************//
//            FUNCTION TO UPDATE THE FILE WITH NEWLY ENTERED PASSWORD                    //
//***************************************************************************************//

void enter_p()
{
       ofstream out;
       out.open("atm.txt",ios::app);

       if(!out)
	   cout<<"Cannot open the Record file!!!\n";

       out<<"\n"<<pno<<"*"<<name<<"*"<<ano<<"*"<<acct<<"*"<<cno<<"*"<<amt<<"*"<<endl;
       out.close();

}

//*********************************************************************************//
//                          FUNCTION TO UPDATE THE PIN                            //
//*******************************************************************************//

void update()
{

ifstream in;
ofstream out;

in.open("atm.txt");                      //As Above//
out.open("temp.txt");

 while(!in.eof())
 {

  in.getline(line,255);

  for(int i=0;i<4;i++)
    {
       if(line[i] == pin_no[i])
	     flag=0;

       else
	   {
	     flag=1;
	     break;
	   }

    }

     if(flag==1)
            out<<line<<endl;

     else
       {
	     flag2=1;
         input_p();                      //calling the input function to enter new password//
         enter_p();                      //calling the enter function to update the new password//
       }
  }

  in.close();
  out.close();

  remove("atm.txt");
  rename("temp.txt","atm.txt");

  if(flag2==0)
   cout<<"\nNO RECORD FOUND!!!\n";

  else
   cout<<"\nYOUR PASSWORD UPDATED SUCCESSFULLY!!!\n";

}


void p_bal_update();    //function for updating the PIN in the bal.txt file //



//**********************************************************************//
//            FUNCTION FOR GICING THE INTRODUCTION                     //
//********************************************************************//

atm()                     //constructor used for the first introduction screen//
    {
	cout<<"\t\t\t  ATM";
	cout<<"\tSIMULATOR\n\n";

    cout<<"\n\nUnder The Guidance of Faculty :\n\n 1. Yogesh M.J. Sir \n 2. Pratibha B.S. Madam";
	cout<<"\n\nPROJECT MADE BY :\n\n 1. Srijan Chaudhary"<<endl;
    cout<<" 2. Rishabh Dubey"<<endl;
    cout<<" 3. Parmesh Ishaan"<<endl;
    cout<<" 4. Vipul N Jarmale"<<endl;
	cout<<"\n\n\nBranch : Computer Science and Engineering \n";
    cout<<"\nSEMESTER : IV";
	cout<<"\n\nCOLLEGE : The National Institute Of Engineering";
	cout<<endl<<endl<<"\n\nPress any key...";
	getch();
	system("cls");
	}
};           // class "atm" ends //



class atm1 : public atm                        //inheriting the base class "atm"//
{
      public:
             friend int bal_update();      //function for updating the balance when the transaction is complete//


//*********************************************************************************************//
//           FUNCTION FOR UPDATING THE BALANCE WHEN THE TRANSACTION IS COMPLETE               //
//*******************************************************************************************//


int bal_update()
{

 ifstream in;
 ofstream out;
 in.open("bal.txt");        //for reading the file//
 out.open("temp2.txt");     //for writing the file//


 while(!in.eof())           //As used above//
 {
  in.getline(line,255);

  for(int i=0;i<4;i++)
    {
       if(line[i] == pass[i])
	     flag=0;

       else
	   {
	     flag=1;
	     break;
	   }
    }

     if(flag==1)
       out<<line<<endl;      //for writing the detail whose password is not matched//

     else
       {
               out<<"\n"<<strtok(line,"*")<<"*"<<at<<"*"; //for writing the detail of the matched password by tokenizing//
               for(int i=0;i<9;i++)
               out<<strtok(NULL,"*")<<"*";
               out<<endl;
       }
  }

  in.close();                             //closing the opened file from which the data is read//
  out.close();                            //closing the temp. file in which the data is copied//
  remove("bal.txt");                      //removing the bal.txt//
  rename("temp2.txt","bal.txt");          //renaming the temp file in whic the data is copied and updated//
}



//*********************************************************//
//          FUNCTION FOR WITHDRAWING THE AMOUNT           //
//*******************************************************//

void withdrawl()
{
 int f = 0;

 ifstream in;
 ofstream out;
 in.open("atm.txt");
 out.open("temp1.txt");

 while(!in.eof())
 {

 in.getline(line,255);

  for(int i=0;i<4;i++)
    {

       if(line[i] == pass[i])
	     flag=0;

       else
	   {
	     flag=1;
	     break;
	   }

    }

     if(flag==1)
       out<<line<<endl;

     if(flag==0&&f==0)
     {
         out.close();
         enter_w();

         out.open("temp1.txt",ios::app);
         bal_update();

         f=1;
     }

  }

  in.close();                           //As Above//
  out.close();

  remove("atm.txt");
  rename("temp1.txt","atm.txt");

}


};     //******class "atm1" ends******//



//********************************************************************************************//
//                      FUNCTION TO DISPLAY RECORD OF LAST 10 TRANSACTIONS                   //
//******************************************************************************************//


void atm :: trans()
{
ifstream in;                           //statement for opening bal.txt file//
in.open("bal.txt");                   //bal.txt is file for keeping last 10 transaction record//
if(!in)
   {
    cout<<"\nRecord File not found...!!!!\n";
    return;
   }
   while(!in.eof())               //loop till the end of file to check each and every line//
    {
     in.getline(line,255);       //for reading one complete line from file//
     for(int i=0;i<4;i++)
    {
       if(line[i] == pass[i])    //loop for cheacking the password of the selected line//
	   flag=0;
       else
	    {
	     flag=1;
	     break;
     	}
    }
      if(flag==0)
      break;
}

if(flag==0)
   {                                 //"*" (star) is used as file tokenizing delemeter//
     strtok(line,"*");             //function for tokenizing the first token of the selected line from file//

      for(int i=1;i<=10;i++)
       cout<<"Rs. "<<strtok(NULL,"*")<<"\n"; //loop for tokenizing  rest of the line//
   }
    in.close();      //statement for closing the bal.txt file//
}


//********************************************************************************//
//            FUNCTION FOR UPDATING THE PASSWORD IN THE BAL.TXT FILE              //
//********************************************************************************//


void atm :: p_bal_update()
{

 ifstream in;
 ofstream out;

 in.open("bal.txt");
 out.open("temp2.txt");

 while(!in.eof())                             //As Above//
 {

  in.getline(line,255);

  for(int i=0;i<4;i++)
    {
       if(line[i] == pin_no[i])
	     flag=0;

       else
	   {
	     flag=1;
	     break;
	   }

    }

     if(flag==1)
       out<<line<<endl;

     else
       {
               strtok(line,"*");
               out<<"\n"<<pno<<"*";

               for(int i=0;i<10;i++)
               out<<strtok(NULL,"*")<<"*";

               out<<endl;
       }
  }

  in.close();
  out.close();

  remove("bal.txt");
  rename("temp2.txt","bal.txt");

}


//******************************************************************//
//             FUNCTION FOR TIME DELAY                             //
//****************************************************************//


void wait(int seconds)
{
  clock_t endwait;
  endwait = clock() + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait)
  {}
}


//**********************************************************************//
//              END OF THE FUNCTIONS OF THE PROJECT                    //
//********************************************************************//


//*********************************THE MAIN FUNCTION***************************//

int main()
{
    atm1 ob;                       //constructor is invoked//
    int n,i,count;

 cout<<"\n\nInsert Your Card\n";
 cout<<"\nVerifying...";

   for (i=1;i>0;i--)
     {
      wait(1);
     }

 cout<<"\n\nCard Accepted\n\n";

 count = 1;

//**************FOR CHECKIN THE PIN No. AND RISTRICTING THE No. OF ATTEMPTS***************//

while(1)
{

cout<<"\n\n\n\t\tENTER YOUR PIN: ";

char c= ' ';
pass="";

while(c!=13)
{
c=getch();

if(c!=13)
{
pass+=c;
cout<<"*";
}

}

ifstream in;
in.open("atm.txt");
//const char *str = pass;
//int sl = strlen(*str);
if(!in)
   {
    cout<<"\nRecord File not found...!!!!\n";
    exit(0);
   }

   while(!in.eof())
    {
     in.getline(line,255);

     for(int i=0;i<4;i++)
      {
       if(line[i] == pass[i])
	   flag=0;

       else
	    {
	     flag=1;
	     break;
     	}
      }

      if(flag==0)
      {
      flag2=1;
      break;
      }

     }

in.close();

     if(flag2==0)
     {

     if(count<=3)
       {
       cout<<"\n\nIncorrect PIN\n";
       count++;

         if(count>3)
         {
         cout<<"\n\nNo.of trials for entering the PIN is over and your card is now blocked"<<endl;
         getch();
         exit(0);
         }

         if(count == 3)
         cout<<"\n\nThis is the Last Attempt to enter your correct PIN otherwise : \n\n\t\t YOUR CARD WILL BE BLOCKED\n\n";

       }
      }
      else
      break;
}

    while(1)
    {
            pin_no = pass;                         //copying the pin no.//

            //**********************DISPLAY MENU************************//

            system("cls");
            cout<<"\n\n\t\t\t\tMAIN MENU"<<endl;
            cout<<"\n\n\n\t\t1. Balance\t\t2. Cash Withdrawal\n\n\t\t3. Mini Statement\t";
            cout<<"4. Account Details\n\n\t\t5. Change PIN\t\t6. Exit\n\n\nEnter your Choice : ";

            cin>>n;

            switch(n)
            {
            case 1:
                 system("cls");
                 ob.balance();

                 for(i=1;i>0;i--)
                 {
                  wait(5);
                 }
            break;

            case 2:
                 system("cls");
                 ob.withdrawl();

                 for(i=2;i>0;i--)
                 {
                  wait(3);
                 }
                 system("cls");

                 ob.balance();

                 for(i=2;i>0;i--)
                 {
                  wait(2);
                 }
                 system("cls");

            break;

            case 3:
                 system("cls");
                 cout<<"\nYour last 10 Transactions :\n\n";
                 ob.trans();

                 for(i=1;i>0;i--)
                 {
                  wait(5);
                 }

            break;

            case 4:
                 system("cls");
                 cout<<"Your Account details:\n";
                 ob.search();

                 for(i=1;i>0;i--)
                 {
                   wait(5);
                 }

            break;

            case 5:
                 system("cls");
                 ob.update();
                 ob.p_bal_update();

                 for(i=1;i>0;i--)
                 {
                  wait(5);
                 }

            break;

            case 6:
                 system("cls");
                 cout<<"Thank You for using the ATM simulator...";

                 int n;
                 for(i=1;i>0;i--)
                 {
                   wait(1);
                 }

                 cout<<"\n\nExiting...";

                 for(i=2;i>0;i--)
                 {
                  wait (1);
                 }
                 exit(0);

            break;

            default :
                    cout<<"\nInvalid Choice\n";

                    for(i=1;i>0;i--)
                    {
                     wait(1);
                    }

            }
    }

getch();

}       //MAIN ENDS//
