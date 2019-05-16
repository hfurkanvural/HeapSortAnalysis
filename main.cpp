//
//  main.cpp
//  algohw2
//
//  Created by Hasan Furkan Vural on 20.11.2018.
//  150140029
//  Copyright © 2018 H. Furkan Vural. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#define tot 1
#define perf 2
#define maxsize 888

using namespace std;

class Employee
{
    int empID;
    int totalnum;
    int posfb;
    int negfb;
    int score() {return (2 * totalnum) + posfb - negfb;};
public:
    void getID(string x){empID=stoi(x);};
    void gettotal(string x){totalnum=stoi(x);};
    void getpos(string x){posfb = stoi(x);};
    void getneg(string x){negfb=stoi(x);};
    
    Employee operator=( Employee&) ;
    
    int empidout(){return empID;};
    int totnumout(){return totalnum;};
    int posfbout(){return posfb;};
    int negfbout(){return negfb;};
    int scoreout(){return score();};
    
    Employee(){};
    Employee(int x, int y, int z, int k){empID=x;totalnum=y;posfb=z;negfb=k;};
};

void heapSort(Employee arr[], int n, int opt);
void max_heapify(Employee arr[], int n, int i, int opt);
void build_max_heap(Employee arr[], int n, int opt);
void insert(Employee arr[], int n, Employee Emp);
void increase_key(Employee arr[], int i, Employee Emp);
Employee extract_max(Employee arr[], int size, int opt);
Employee extract_min(Employee arr[], int size, int opt);

void num_heapSort(int arr[], int n);
void num_max_heapify(int arr[], int n, int i);
void num_build_max_heap(int arr[], int n);
void num_insert(int arr[], int n, int x);
void num_increase_key(int arr[], int i, int x);
int num_extract_max(int arr[], int size);



int main(int argc, const char * argv[]) {
    ifstream dataFile("dataset/day1.csv");
    int size = 800, i=0;
    int arrsize = size;
    
    Employee *empArr;
    empArr = new Employee[maxsize];
    
    if (dataFile.is_open())
    {
        while (i!=size)
        {
            string eid, tn, pfb, nfb;
            getline(dataFile, eid,',');
            getline(dataFile, tn, ',');
            getline(dataFile, pfb, ',');
            getline(dataFile, nfb, '\n');
            
            empArr[i].getID(eid);
            empArr[i].gettotal(tn);
            empArr[i].getpos(pfb);
            empArr[i].getneg(nfb);
            i++;
        }
        
        dataFile.close();
    }
    else
        cout<<"cannot open";

    build_max_heap(empArr, arrsize, tot);

    Employee *outArr;
    outArr = new Employee [maxsize];
    
    for (int x=0; x<=arrsize; x++)
    {
        outArr[x] = empArr[x];
    }
    cout<<"AFTER DAY-1 \nMAXIMUM CALLS    : ";
    cout<<extract_max(outArr, arrsize, tot).empidout()<<", ";
    arrsize -=1;
    cout<<extract_max(outArr, arrsize, tot).empidout()<<", ";
    arrsize -=1;
    cout<<extract_max(outArr, arrsize, tot).empidout()<<endl;
    arrsize +=2;
    
    build_max_heap(outArr, arrsize, perf);
    cout<<"BEST PERFORMANCE :";
    cout<<extract_max(outArr, arrsize, perf).empidout()<<", ";
    arrsize -=1;
    cout<<extract_max(outArr, arrsize, perf).empidout()<<", ";
    arrsize -=1;
    cout<<extract_max(outArr, arrsize, perf).empidout();
    arrsize +=2;
  
    for (int p = 2; p<=10; p++)
    {
        i=0;
        string fileloc = "dataset/day"+ to_string(p)+".csv";
        ifstream dataFile2(fileloc);
        if (dataFile2.is_open())
        {
            while (i!=size)
            {
                string eid, tn, pfb, nfb;
                getline(dataFile2, eid,',');
                getline(dataFile2, tn, ',');
                getline(dataFile2, pfb, ',');
                getline(dataFile2, nfb, '\n');

                Employee temp;

                temp.getID(eid);
                temp.gettotal(tn);
                temp.getpos(pfb);
                temp.getneg(nfb);
                int t=0;
                while (temp.empidout() != empArr[t].empidout())
                {
                    t++;
                    if (temp.empidout()== empArr[t].empidout()) {
      
                        increase_key(empArr, t, temp);
                        break;
                    }
                    else if ( t>= arrsize)
                    {
                        insert(empArr, arrsize, temp);
                        arrsize+=1;
                        break;
                    }
                }
                i++;
            }
            cout<<endl<<endl;

            dataFile.close();
        }
        else
            cout<<"cannot open";
        build_max_heap(empArr, arrsize, tot);
        

        for (int x=0; x<arrsize; x++)
        {
            outArr[x] = empArr[x];
        }
        
            cout<<"AFTER DAY-"<<p<<" \nMAXIMUM CALLS    : ";
            cout<<extract_max(outArr, arrsize, tot).empidout()<<", ";
            arrsize -=1;
            cout<<extract_max(outArr, arrsize, tot).empidout()<<", ";
            arrsize -=1;
            cout<<extract_max(outArr, arrsize, tot).empidout()<<endl;
            arrsize +=2;
        
            build_max_heap(outArr, arrsize, perf);
            cout<<"BEST PERFORMANCE : ";
            cout<<extract_max(outArr, arrsize, perf).empidout()<<", ";
            arrsize -=1;
            build_max_heap(outArr, arrsize, perf);
            cout<<extract_max(outArr, arrsize, perf).empidout()<<", ";
            arrsize -=1;
            cout<<extract_max(outArr, arrsize, perf).empidout();
            arrsize +=2;
            if (p==10) {

                cout<<" \nMINIMUM CALLS    : ";
                cout<<extract_min(outArr, arrsize, tot).empidout()<<", ";
                arrsize -=1;
                cout<<extract_min(outArr, arrsize, tot).empidout()<<", ";
                arrsize -=1;
                cout<<extract_min(outArr, arrsize, tot).empidout()<<endl;
                arrsize +=2;
                
                cout<<"WORST PERFORMANCE : ";
                cout<<extract_min(outArr, arrsize, perf).empidout()<<", ";
                arrsize -=1;
                cout<<extract_min(outArr, arrsize, perf).empidout()<<", ";
                arrsize -=1;
                cout<<extract_min(outArr, arrsize, perf).empidout()<<endl<<endl;
                arrsize+=2;

            }
    }
    i=0;
    int numbersize= 2000000;
    int numbarr [2000000];
    ifstream numFile("dataset/numbers.csv");
    if (numFile.is_open())
    {
        while (i!=numbersize)
        {
            string number;
            getline(numFile, number, '\n');
            numbarr[i] = stoi(number);
            i++;
        }
}
    numFile.close();
    num_build_max_heap(numbarr, numbersize);
    ofstream outp;
    outp.open("sorted.csv", ofstream::out);
    if(outp.is_open())
    {
    for (int t=0; t<10; t++)
    {
        clock_t begin = clock();
        int height = ceil(log2(numbersize + 1)) - 1;
        for (int n=0; n<200000; n++)
        {
            outp<<num_extract_max(numbarr, numbersize)<<"\n";
            numbersize-=1;
        }
        clock_t end = clock();
        double total_time = double(end - begin) / CLOCKS_PER_SEC;
        cout << "Time elapsed for "<<t+1<<". heap sort:    " << total_time << endl<<"Height of Heap   : " <<height<<endl<<endl;
       
    }
    
    }
    else
        cout<<"file cannot open..";
    
    
    
    return 0;
}

Employee Employee::operator=( Employee &x)
{
    empID = x.empID;
    totalnum = x.totalnum;
    posfb = x.posfb;
    negfb = x.negfb;
    
    return *this;
}


void heapSort(Employee arr[], int n, int opt)
{


    build_max_heap(arr, n, opt);

    for (int i=n-1; i>=0; i--)
    {
        Employee temp = arr[i];
        arr[i]=arr[0];
        arr[0] = temp;
   
        max_heapify(arr, i, 0, opt);
    }
}


void build_max_heap(Employee arr[], int n, int opt)
{
for (int i = n / 2 - 1; i >= 0; i--)
max_heapify(arr, n, i, opt);
}


void max_heapify(Employee arr[], int n, int i, int opt)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    
 if (opt == tot)
    {
        if (l < n && arr[l].totnumout() > arr[largest].totnumout())
            largest = l;
        
        if (r < n && arr[r].totnumout() > arr[largest].totnumout())
            largest = r;
        
        if (largest != i)
        {
            Employee temp = arr[i];
            arr[i]=arr[largest];
            arr[largest] = temp;

            
            max_heapify(arr, n, largest, opt);
        }
    }
    else if (opt == perf)
    {
        if (l < n && arr[l].scoreout() > arr[largest].scoreout())
            largest = l;
        
        if (r < n && arr[r].scoreout() > arr[largest].scoreout())
            largest = r;
        
        if (largest != i)
        {
            Employee temp = arr[i];
            arr[i]=arr[largest];
            arr[largest] = temp;

            
            max_heapify(arr, n, largest, opt);
        }
    }
}

void insert(Employee arr[], int n, Employee Emp)
{
    if (n == maxsize)
        cout<<"error??";
    else
    {
        Employee empty(Emp.empidout(),0,0,0);
        arr[n] = Emp;
        increase_key(arr, n, empty);
        n=n+1;
    }
    
}

void increase_key(Employee arr[], int i, Employee Emp)
{
   
    int tnum = arr[i].totnumout()+Emp.totnumout();
    int pfeedback = arr[i].posfbout()+Emp.posfbout();
    int nfeedback = arr[i].negfbout()+Emp.negfbout();
    Employee temp (Emp.empidout(),tnum,pfeedback,nfeedback);
    
    if (temp.empidout()<arr[i].empidout())
    {
        cout<<"error"<<endl;
    }
    else
    {
        arr[i] = temp;
        build_max_heap(arr, i, tot);
//        while(i>0 && arr[((i+1)/2)-1].empidout() < arr[i].empidout())
//        {
//            Employee change = arr[i];
//            arr[i]=arr[((i+1)/2)-1];
//            arr[((i+1)/2)-1] = change;
//            i = ((i+1)/2)-1;
//        }
    }
}
Employee extract_max(Employee arr[], int size, int opt)
{
    Employee ret;
    ret = arr[0];
    arr[0] = arr[size-1];
    arr[size-1] = ret;
    size -=1;
    max_heapify(arr, size, 0, opt);
    
    return ret;
}
Employee extract_min(Employee arr[], int size, int opt)
{
    Employee temp;
    heapSort(arr, size, opt);
    temp=arr[0];
    arr[0] = arr[size-1];
    arr[size-1] = temp;
    return temp;
}

void num_max_heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    
  
        if (l < n && arr[l] > arr[largest])
            largest = l;
        
        if (r < n && arr[r] > arr[largest])
            largest = r;
        
        if (largest != i)
        {
            int temp = arr[i];
            arr[i]=arr[largest];
            arr[largest] = temp;
            
            num_max_heapify(arr, n, largest);
        }
}
void num_build_max_heap(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        num_max_heapify(arr, n, i);
}

int num_extract_max(int arr[], int size)
{
    int ret;
    ret = arr[0];
    arr[0] = arr[size-1];
    arr[size-1] = ret;
    size -=1;
    num_max_heapify(arr, size, 0);
    
    return ret;
}
