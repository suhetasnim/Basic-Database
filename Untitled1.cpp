#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<vector>
#include<iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std ;

void printToken(vector<string> interToken)
{
    for(int i = 0 ; i < interToken.size() ; i++)
    {
        cout << interToken[i]<<" " ;

    }
    cout<<endl;
}
vector<string> spliter(string inputBuffer, char token)
{
    string intermediate;
    stringstream check(inputBuffer);
    vector<string> interToken;



    while (getline(check, intermediate, token))
    {
        intermediate.erase(remove(intermediate.begin(), intermediate.end(), '('), intermediate.end());
        intermediate.erase(remove(intermediate.begin(), intermediate.end(), ')'), intermediate.end());
        intermediate.erase(remove(intermediate.begin(), intermediate.end(), ';'), intermediate.end());
        if (intermediate.length() > 0)
        {
            interToken.push_back(intermediate);
        }
    }
    return interToken;
}
void where(vector<string> interToken)
{
    string col=interToken[5];
    string value=interToken[7];
    string t = interToken[3] ;
    string t2 = t + ".config" ;
    const char* fileNameC = t2.c_str() ;
    ifstream outfile;
    outfile.open(fileNameC);
    string line2;

    int in=0;
    while(getline(outfile,line2))
    {
        vector<string> q=spliter(line2,' ');
        if(q[0]==col)
        {
            cout<<in<<endl;
            break;
        }
        in++;//column number in config file


    }
    string temp = interToken[3] ;
    string ffile=temp+".data";
    const char* select_file=ffile.c_str();
    ifstream outfile3;
    outfile3.open(select_file);
    if(outfile3)
    {
        string line;
        while(getline(outfile3,line))
        {
            vector<string> z=spliter(line,'#');
            //printToken(z);
            for(int k=0; k<z.size(); k++)
            {
                if (interToken[6]=="=")
                {
                    if(z[in]==value)
                    {
                        printToken(z);
                        break;
                    }

                }
                else if(interToken[6]==">")
                {
                    int n1=stoi(z[in]);
                    int n2=stoi(value);

                    if(n1>n2)
                    {
                        printToken(z);
                        break;
                    }
                }
                else if(interToken[6]=="!=")
                {
                    int n1=stoi(z[in]);
                    int n2=stoi(value);

                    if(n1!=n2)
                    {
                        printToken(z);
                        break;
                    }
                }
                else
                {
                    int n1=stoi(z[in]);
                    int n2=stoi(value);

                    if(n1<n2)
                    {
                        printToken(z);
                        break;
                    }
                }
            }
            cout<<endl;
        }
    }


}


void selectCol(vector<string> interToken)
{
    string temp = interToken[3] ;
    string ffile=temp+".data";
    const char* select_file=ffile.c_str();//variable name of file
    ifstream outfile3; //read file
    outfile3.open(select_file);


    if(outfile3)
    {
        string line;
        while(getline(outfile3,line))
        {
            if(interToken[1][0]=='*')
            {
                for(int i=0; i<line.length(); i++)
                {
                    if(line[i]=='#')
                    {
                        cout<<" ";
                    }

                    else
                    {
                        cout<<line[i];
                    }
                }
                cout<<endl;
            }
            else if (interToken[1][0]!= '*')
            {
                vector<string> col = spliter(interToken[1],',');

                cout<<endl;
                //printToken(col);
                string t = interToken[3] ;
                string t2 = t + ".config" ;
                const char* fileNameC = t2.c_str() ;
                ifstream outfile;
                outfile.open(fileNameC);
                string line2;
                vector<int> index;
                int in=0;
                while(getline(outfile,line2)) //storing column names
                {
                    vector<string> q=spliter(line2,' ');
                    for(int i=0; i<col.size(); i++)
                    {
                        if(q[0]==col[i])
                        {
                            index.push_back(in);
                        }
                    }
                    in++;
                }



                vector<string> z=spliter(line,'#');
                for(int j=0; j<index.size(); j++)
                {

                    cout<<z[index[j]]<<" ";
                }
                cout<<endl;

                outfile.close();
            }
            else
            {
                cout<<"Error"<<endl;
            }
        }
        outfile3.close();

    }
    else
    {

        cout<<"There is no file"<<endl;
    }


}

void insertTable(vector<string> interToken)
{
    string temp = interToken[2] ;
    string dfile=temp+".data";
    const char* data_file_name=dfile.c_str();
    ofstream outfile2;
    outfile2.open(data_file_name,ios::app);
    for(int i=0; i<interToken[4].length(); i++)
    {
        if(interToken[4][i]==',')
        {
            outfile2<<'#';
            continue;
        }
        outfile2<<interToken[4][i];
    }

    outfile2<<endl;
    outfile2.close();

}

void createTable(vector<string> interToken)
{
    string temp = interToken[2] ;
    string temp2 = temp + ".config" ;
    const char* fileName = temp2.c_str() ;
    ofstream outfile;
    outfile.open(fileName);


    string dfile=temp+".data";
    const char* data_file_name=dfile.c_str();
    ofstream outfile2;
    outfile2.open(data_file_name);



    string buffer = "" ;

    for(int i = 3 ; i < interToken.size() ; i++)
    {
        buffer += interToken[i] ;
        int len = interToken[i].size() ;
        if(interToken[i][len-1] == ',')
        {
            buffer.erase(remove(buffer.begin(), buffer.end(), ','), buffer.end()) ;
            outfile << buffer << endl ;
            buffer = "" ;
            continue ;
        }
        buffer += " " ;
    }

    outfile << buffer << endl ;
    outfile.close() ;


    outfile2.close();


}
void parsing(string inputBuffer)
{
    string intermediate ;
    stringstream check(inputBuffer);
    char token = ' ' ;
    vector<string> interToken ;



    while(getline(check, intermediate, token))
    {
        intermediate.erase(remove(intermediate.begin(), intermediate.end(), '('), intermediate.end()) ;
        intermediate.erase(remove(intermediate.begin(), intermediate.end(), ')'), intermediate.end()) ;
        intermediate.erase(remove(intermediate.begin(), intermediate.end(), ';'), intermediate.end()) ;
        if(intermediate.length()>0)
        {
            interToken.push_back(intermediate) ;
        }
    }

    if(interToken[0] == "create")
    {
        if(interToken[1] == "table")
        {

            createTable(interToken) ;
        }



    }

    else if(interToken[0] == "insert")
    {
        if(interToken[1] == "into")
        {

            insertTable(interToken) ;
        }
        else
        {
            cout << "Syntax error" << endl ;
        }



    }

    else if(interToken[0] == "select")
    {
        if(interToken[2] == "from")
        {
            if(interToken[4] == "where")
            {

                where(interToken) ;

            }
            else
            {
                selectCol(interToken) ;
            }

        }
        else
        {
            cout << "Syntax error278" << endl ;
        }



    }
    else
    {
        cout << "Syntax error286" << endl ;
    }
}

int main()
{
    string inputBuffer = "";


    while(true)
    {
        string c ;
        getline(cin, c) ;
        inputBuffer += c ;
        int len = c.length() ;
        if(c[len-1] == ';')
            break ;
    }
    parsing(inputBuffer) ;
    return 0 ;
}
/*
select * from tutorials_tbl where tutorial_id = 102;
select * from tutorials_tbl where tutorial_id > 102;
select * from tutorials_tbl where tutorial_id < 102;
select * from tutorials_tbl where tutorial_title = CSE;

*/

