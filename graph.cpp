#include<iostream>

#include<fstream>

using namespace std;

 

int main()

{

    int count = 0;

    string line;

 
//cout<<"ex min : "<<x<<"---"<<endl;
    /* Creating input filestream */ 

    ifstream file("/home/supriya/IIIT_Hyderabad/APS_assignment/Project/Comparison_Of_Algorithms/testcase1.cpp");

    while (getline(file, line))

        count++;

 

    cout << "Numbers of lines in the file : " << count << endl;

    return 0;

}