//============================================================================
// Name        : SeProject.cpp
// Author      : Mahmoud Eltobgy
// Version     : 1.0
// Copyright   : Your copyright notice
//============================================================================
#include "matrix.h"
#include <fstream> //waels
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>
bool IS_terminated(string s1)
{
	if(s1=="Exit" ||s1=="exit"||s1=="Terminate"||s1=="terminate")
	{
		return true;
	}
	return false;

}

void Error_message()
	{
	printf("You have Entered wrong matrix check your input and try again :)\nDo you wanna try again ? please enter y for => yes or anything else for => no \n");

	}

int main()
{
	ifstream input("C:\\Users\\hp\\Desktop\\phase 2\\rightformat.txt");   //waels
	string s1, s2, op,vName1,vName2;
	float** A, ** B, ** C;
	vector <float**> data;
	string str[]={" C'"," D'"," E'"," F'"," G'"," A'"," B'","H'","I'","J'","K'","S'","P'","L'","M'","N'"};
	map<string ,float**>mapped;
	int negative_flag=0;
	matrix M;

	printf("--------------------------Program Hints-------------------------------\n");
	printf("----------------------------------------------------------------------\n");
    printf("At Any time if you want to terminate the program type 'Exit' or 'Terminate' as an input \n");
	printf("-----------------------------------------------------------------------\n");
	printf("-----------------------------------------------------------------------\n");
	printf("the input is at file called (right format) in the required format\n");    //wael

	getline(input,s1,']');            //Farag
	getline(input,s2,']');

if(s1.substr(s1.length()-1,1) !="\\n"&&s1.substr(s1.length()-1,1) !=";")
    {
        s1+=";\n";
    }

    if(s2.substr(s2.length()-1,1) !="\\n"&&s2.substr(s2.length()-1,1) !=";")
    {
        s2+=";\n";
    }



while(s1.find("\n")!=-1)
{
    s1.erase(s1.find("\n"),1);
}
while(s2.find("\n")!=-1)
{
    s2.erase(s2.find("\n"),1);
}
    if(s1.substr(s1.length()-1)==";")
    s1.erase(s1.length()-1);

    if(s2.substr(s2.length()-1)==";")
	s2.erase(s2.length()-1);
	s1=s1+']';
	s2=s2+']';
string    T1=s1;
string    T2=s2;




	if(IS_terminated(s1))
		return 0;
	//

	while( s1 == ""  || s1.find("[") == -1)   // l goz2 da kol mara hy3ml return 0 ella lw dakhlt l input fl file b special order waels
	{
	Error_message();          //prints out to the screen error message
	getline(cin, s1);         // waelsdelete
	                          //input>>s1; //waels edit
	if (s1=="y"||s1=="yes"|| s1=="Y"||s1=="Yes")
	{
		printf("Please Re-enter the first matrix in the right form in order to coninue\n");
		getline(cin, s1);

	}
	else
        {
		return 0;
	    }

	}

    // op=op.substr(op.find("=")+1);
    //vName1 = s1.substr(0,s1.find("="));
    //  vName2 = s2.substr(0,s2.find("="));


	s1 = s1.substr(s1.find('['));
    int m1 = M.Getrows(s1);
	int n1 = M.Getcolumns(s1);
    //making sure the the matrix is not empty
	if( m1<=0)				// l goz2 da kol mara hy3ml return 0 ella lw dakhlt l input fl file b special order waels
	{
		Error_message();
		getline(cin, s1);  //waelsdelete
		input>>s1; //waels
		if (s1=="y"||s1=="yes"|| s1=="Y"||s1=="Yes")
		{
			//continue ;
		}

		else {
			return 0;
		}
	}

	//

	A = M.create_matrix(m1, n1);
	A = M.fill_matrix(s1, A, m1, n1);
    mapped[str[5]]=A;

	//cout << "Please Enter The second Matrix In The Right Format: \t" << "like B=[1 2; 3 4]" << endl;   //insert B
	//getline(cin, s2);    		 waelsdelete
	//checking if the user entered exit to terminate the program.
		if(IS_terminated(s2))
		{
			return 0;
		}

		while( s2 == ""  || s2.find("[") == -1) 	 // l goz2 da kol mara hy3ml return 0 ella lw dakhlt l input fl file b special order waels
	{
		Error_message();//prints out an error message
		getline(cin, s2);// waelsdelete
		//input>>s2; //waels
		if (s2=="y"||s2=="yes"|| s2=="Y"||s2=="Yes")
		{
			printf("Please Re-enter the second matrix in the right form in order to coninue\n");
			getline(cin, s2);
		}
		else {
			return 0;
		}

	}

	s2 = s2.substr(s2.find('['));
	int m2 = M.Getrows(s2);
	int n2 = M.Getcolumns(s2);
		//making sure the the matrix is not empty
	if( m2<=0)		// l goz2 da kol mara hy3ml return 0 ella lw dakhlt l input fl file b special order waels
	{
		Error_message();
		getline(cin, s2);// waels delete
		input>>s2; //waels
		if (s2=="y"||s2=="yes"|| s2=="Y"||s2=="Yes")
		{
			//continue ;
		}

		else {
			return 0;
		}
	}


	B = M.create_matrix(m2, n2);
	B = M.fill_matrix(s2, B, m2, n2);
    mapped[str[6]]=B;

	while(getline(input,op))
    {

	   op=op.substr(op.find("=")+1);
       vName1 = T1.substr(0,T1.find("="));
       vName2 = T2.substr(0,T2.find("="));
       if(op.find("+")==-1&&op.find("-")==-1&&op.find("*")==-1&&op.find("'")==-1
          &&op.find("/")==-1&&op.find("zeros")==-1&&op.find("ones")==-1 &&op.find("eye")==-1&&op.find("rand")==-1 && op.find("exp")==-1 && op.find("log")==-1 && op.find("log10")==-1 && op.find("sqrt")==-1 && op.find("^")==-1 &&  op.find("sin")==-1 &&  op.find("cos")==-1 &&op.find("tan")==-1&& op.find("log2")==-1 &&op!="exit")   //Farag
        continue;

		while(op.find("+")==-1&&op.find("-")==-1&&op.find("*")==-1&&op.find("'")==-1
          &&op.find("/")==-1&&op.find("zeros")==-1&&op.find("ones")==-1 &&op.find("eye")==-1&&op.find("rand")==-1 && op.find("exp")==-1 && op.find("log")==-1 && op.find("log10")==-1 && op.find("sqrt")==-1 && op.find("^")==-1&& op.find("sin")==-1 &&  op.find("cos")==-1 && op.find("tan")==-1 && op.find("log2")==-1 &&op!="exit")
		{

			// l goz2 da lazmlo ani adkhl l input fl file b special order waels
            printf("OOPS.,Sorry you have enterd not valid or wrong operation,please try again considering this format \nlike:C=A+B  or\nlike:C=A-B  or\nlike:C=A*B or\nlike:C=A' or\nlike:C=B'\n");
			getline(cin, op);
			input>>op; //waels edit
		}
	if(IS_terminated(op))
		return 0;



	if(mapped[op])
    {
        C=mapped[op];
        printf("The Transpose result=\n");
        C=M.Transpose_matrix(C,m1,n1);
        M.print_matrix(C,n1,m1);
    }


	else if ((op.find("+"))!=(-1) )                    // both matrices dimensions must be equal
	{

	try{
	    if ( ( m1 != m2) || (m1 ==0) || (n1 != n2))

	      throw("the dimensions are not the same ,so we can't perform summition");



		printf("The summation result=\n");
		C = M.sum_matrix(A, B, m1, n1);
		M.print_matrix(C, m1, n1);
        data.push_back(C);
        mapped[str[0]]=data[0];}

	catch(const char * x) { cout<<x<<endl;}


}


	else if (op.find("-")!=-1)               // both matrices dimensions must be equal
		{

		    try{
		    if (m1 != m2 || m1==0 || n1 != n2 )
            {


                throw("the dimensions are not the same ,can't perform subtracting");
            }
			printf("The subtraction result=\n");
			C = M.sub_matrix(A , B, m1, n1);
			M.print_matrix(C, m1, n1);
			data.push_back(C);
			mapped[str[1]]=data[1];
              }

              catch(const char *x ) {cout<<x<<endl;}
		}


	else if ( op.find("*") != -1 )                      // column of matrix A must be equal to row of matrix B
	{
	    try{
		if (n1 != m2)
            {
			    throw ("can't multiply the matrices because the number of columns of the first matrix not equal to the number of rows of the second matrix ");
		    }
                printf("The multiplication result=\n");
                C = M.multiply_matrix(A, B, m1, n2,n1);
                M.print_matrix(C, m1, n2);
                data.push_back(C);
                mapped[str[2]]=data[2];
	         }

	    catch(const char* x){cout<<x<<endl;}


	}
    else if(op.find("./") != -1)
    {

          printf("The division by one result=\n");
          C=M.division_By_One(A,m1,n1);
          M.print_matrix(C, m1, n2);


    }

    else if ( op.find("/") != -1 )
	{
	    try{

	    if (m1 != n1 ||m2!=n2||m1!=m2)
            {
                    throw("these two matrices can not be divided , the martix must be squared \n");

            }
                    printf("The division result=\n");
                    C=M.divide_matrix(A,B,m2,n2,n1);
                    M.print_matrix(C, m1, n2);
                    data.push_back(C);
                    mapped[str[3]]=data[3];

	    }
	    catch( const char *x ) {cout<<x<<endl;}
	}

	else if (op.find("zeros")!=-1)
		{
			printf("The Zeros result=\n");
			string T1 = op.substr(op.find('(')+1,1);
			string T2 = op.substr(op.find(')')-1,1);
			int t1 =atoi(T1.c_str());
			int t2 =atoi(T2.c_str());
			C = M.zeros_matrix(t1, t2);
			M.print_matrix(C, t1, t2);
			data.push_back(C);
			//mapped[str[1]]=data[1];

		}

	else if (op.find("ones")!=-1)
		{
			printf("The ones result=\n");
			string T1 = op.substr(op.find('(')+1,1);
			string T2 = op.substr(op.find(')')-1,1);
			int t1 =atoi(T1.c_str());
			int t2 =atoi(T2.c_str());
			C = M.ones_matrix(t1, t2);
			M.print_matrix(C, t1, t2);
			data.push_back(C);
			//mapped[str[1]]=data[1];

		}
		else if (op.find("eye")!=-1)
		{
			printf("The eye result=\n");
			string T1 = op.substr(op.find('(')+1,1);
			string T2 = op.substr(op.find(')')-1,1);
			int t1 =atoi(T1.c_str());
			int t2 =atoi(T2.c_str());
			C = M.eye_matrix(t1, t2);
			M.print_matrix(C, t1, t2);
			data.push_back(C);
			//mapped[str[1]]=data[1];

		}
		else if (op.find("rand")!=-1)
		{
			printf("The rand result=\n");
			string T1 = op.substr(op.find('(')+1,1);
			string T2 = op.substr(op.find(')')-1,1);
			int t1 =atoi(T1.c_str());
			int t2 =atoi(T2.c_str());
			C = M.rand_matrix(t1, t2);
			M.print_matrix(C, t1, t2);
			data.push_back(C);
			//mapped[str[1]]=data[1];

		}


		else if ( op.find("exp") != -1 )
	{
          printf("The exp result=\n");
          C=M.Exponential(A,m1,n1);
          M.print_matrix(C, m1, n2);

          data.push_back(C);
          mapped[str[7]]=data[7];
	}

	else if ( op.find("log10") != -1 )
	{
	    try{
          printf("The log base 10 result=\n");
          C=M.Log_Base10(A,m1,n1,negative_flag);
                     if (negative_flag==1)
               throw("Make sure that there is not any negative element in the matrix while performing log base 10 ");
          M.print_matrix(C, m1, n2);
          data.push_back(C);
          mapped[str[8]]=data[8];
	    }
	    catch(const char * x ){cout<<x<<endl;}
	}
	else if ( op.find("log2") != -1 )
	{
	    try{
          printf("The log base 2 result=\n");
          C=M.Log_Base2(A,m1,n1,negative_flag);
                     if (negative_flag==1)
               throw("Make sure that there is not any negative element in the matrix while performing log base 2 ");
          M.print_matrix(C, m1, n2);
          data.push_back(C);
          mapped[str[9]]=data[9];
	    }
	    catch (const char* x ){cout<<x<<endl;}
	}


    else if ( op.find("log") != -1 )  // log in matlab and c++ is the ln function
	{


try{
          printf("The ln result=\n");
          C=M.Natural_Log(A,m1,n1,negative_flag);
          if (negative_flag==1) {throw ("Make sure all elements are positive in order to perform ln");}
          M.print_matrix(C, m1, n2);
          data.push_back(C);
          mapped[str[10]]=data[10];
}

catch (const char * x){cout<<x<<endl;}
	}

//*********SquareRootFunction**************



	   else if ( op.find("sqrt") != -1 )  // waels
	{
	    try{
          printf("The sqrt result=\n");
          C=M.SquareRoot(A,m1,n1,negative_flag);
           if (negative_flag==1)
               throw("Make sure that there is not any negative element in the matrix while performing square root ");
          M.print_matrix(C, m1, n1);
          data.push_back(C);
          mapped[str[11]]=data[11];
	       }

	       catch (const char *x ){cout<<x<<endl;}
	}






//*********sineFunction**************


	   else if ( op.find("sin") != -1 )
	{
          printf("The sin result=\n");
          C=M.Sin_M(A,m1,n1);
          M.print_matrix(C, m1, n1);
          data.push_back(C);
          mapped[str[13]]=data[13];
	}


	//*********tanFunction**************


	   else if ( op.find("tan") != -1 )
	{
          printf("The tan result=\n");
          C=M.Tan_M(A,m1,n1);
          M.print_matrix(C, m1, n1);
          data.push_back(C);
          mapped[str[14]]=data[14];
	}

//*********cosFunction**************


	   else if ( op.find("cos") != -1 )  // waels
	{
          printf("The cos result=\n");
          C=M.Cos_M(A,m1,n1);
          M.print_matrix(C, m1, n1);
          data.push_back(C);
          mapped[str[15]]=data[15];
	}


//*********PowerFunction**************

	else if ( op.find("^") != -1 ) // waels
    {
        if (m1!=n1)
            {
                printf("this matrix can not be powered \n");
			    continue;}
        else{
                string p;
                p=op.substr(op.find("^")+1);
                stringstream ss;
                int power;
                ss<<p;
                ss>>power;
               C = M.createEmptyMatrix(m1,n1);

               for (int i = 0 ;i<m1;++i){
                for (int j = 0;j<n1;++j){
                    if (i==j)
                        C [i][j]=1;
                       // C[i][j]=1;
                    else
                        C [i][j]=0;
                        //C[i][j]=0;
                }
               }
		       printf("The power result=\n");
                //M.print_matrix(C, m1, n1);

		       for (int i=0;i<power;++i)
                C = M.multiply_matrix(A, C, m1,n1,n1);
                M.print_matrix(C, m1, n1);
                data.push_back(C);
                mapped[str[12]]=data[12];
	}}





	else
    {
        printf("Oh!! Error Good Bye\n");
    }

		printf("\n\n");

    }
	input.close();

	return 0;
}

