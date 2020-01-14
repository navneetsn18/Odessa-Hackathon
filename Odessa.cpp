#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define N 10
#define M 10
int battery=9500;
int tempi=5;
int tempj=5;

class QItem { 
public: 
	int row; 
	int col; 
	int dist; 
	QItem(int x, int y, int w) 
		: row(x), col(y), dist(w) 
	{ 
	} 
}; 

int minDistance(char grid[N][M]) 
{   
	QItem source(0, 0, 0); 
	bool visited[N][M]; 
	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < M; j++) 
		{ 
			if (grid[i][j] == '0') 
				visited[i][j] = true; 
			else
				visited[i][j] = false;  
			if (grid[i][j] == 's') 
			{ 
			source.row = i; 
			source.col = j; 
			} 
		} 
	} 
    queue<QItem> q; 
	q.push(source); 
	visited[source.row][source.col] = true; 
	while (!q.empty()) { 
		QItem p = q.front(); 
		q.pop(); 
    	if (grid[p.row][p.col] == 'd') 
			return p.dist; 
	if (p.row - 1 >= 0 && 
			visited[p.row - 1][p.col] == false) { 
			q.push(QItem(p.row - 1, p.col, p.dist + 1)); 
			visited[p.row - 1][p.col] = true; 
		} 
		if (p.row + 1 < N && 
			visited[p.row + 1][p.col] == false) { 
			q.push(QItem(p.row + 1, p.col, p.dist + 1)); 
			visited[p.row + 1][p.col] = true; 
		} 
		if (p.col - 1 >= 0 && 
			visited[p.row][p.col - 1] == false) { 
			q.push(QItem(p.row, p.col - 1, p.dist + 1)); 
			visited[p.row][p.col - 1] = true; 
		} 
		if (p.col + 1 < M && 
			visited[p.row][p.col + 1] == false) { 
			q.push(QItem(p.row, p.col + 1, p.dist + 1)); 
			visited[p.row][p.col + 1] = true; 
		} 
	} 
	return -1; 
} 

float calculate(int sInputC1,int sInputC2,int dInputC1,int dInputC2,int weight,int roverCount){
    char grid[10][10];
    int i,j,totalDist=0;
    float cost;
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            grid[i][j]='*';
        }
    }
    grid[sInputC1][sInputC2]='s';
    grid[dInputC1][dInputC2]='d';
    int resShortestPath=minDistance(grid);
    resShortestPath*=100;
    cout<<"\n Distance from source to destination is: "<<resShortestPath<< " meteres. ";
     for(i=0;i<10;i++){
        for(j=0;j<10;j++)
        {
            grid[i][j]='*';
        }
    }
    grid[tempi][tempj]='s';
    grid[sInputC1][sInputC2]='d';
    int rti=minDistance(grid);
    rti*=100;
    //cout<<"\n Distance from Store House to source is: "<<rti<< " meteres. ";
     for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            grid[i][j]='*';
        }
    }
    grid[tempi][tempj]='s';
    grid[sInputC1][sInputC1]='d';
    int dtr=minDistance(grid);
    dtr*=100;
    // cout<<"\n Distance from destination to Store House is: "<<dtr<< " meteres. ";
    totalDist=rti+resShortestPath;
    cout<<"\n Your total distance is: "<<totalDist<< " meteres. ";
    if(totalDist<=1000){
        cost=(totalDist*0.005)*roverCount;
    }
    else if(totalDist>1000 && totalDist<=2000)
    {
        cost=(5+(totalDist-1000)*0.0075)*roverCount;
    }
    else if(totalDist>2000 && totalDist<=10000)
    {
        cost=(12.5+(totalDist-2000)*0.0085)*roverCount;
    }
    else
    {
        cost=-1;
    }
    battery=battery-totalDist-dtr ;
    if(battery<=0)
    {
        cout<<"\n Less charge left!";
        cost=-1;
    }
    else{
        cout<<"\n Battery for further distance: "<<battery;
    }
    return cost;
}

int main()
{
    int sInputC1,sInputC2,dInputC1,dInputC2,weight,roverCount;
    float result,dayCost;
    ofstream file;
    file.open("DayCost.txt",ios::app);
    char ch;
    do{
        cout<<"\n\t\t\t\t\t Welcome to Odessa Delivery Services";
        cout<<"\n------------------------------------------------------------------------------------------------------------------------------";
        cout<<"\n Enter the coordinates of source: ";
        cout<<"\n x:";
        cin>>sInputC1;
        cout<<"\n y:";
        cin>>sInputC2;
        cout<<"\n Enter the coordinates of destination: ";
        cout<<"\n x:";
        cin>>dInputC1;
        cout<<"\n y:";
        cin>>dInputC2;
        cout<<"\n Enter the weight to be delivered in kgs: ";
        cin>>weight;
        if(weight<=5)
        {
            roverCount=1;
            cout<<"\n You need only "<<roverCount<<" rover.";
        }
        else{
            roverCount=(weight/5)+1;
            cout<<"\n You need "<<roverCount<<" rovers.";
        }
        if(sInputC1<0 || sInputC1>9 || sInputC2<0 || sInputC2>9 || dInputC1<0 || dInputC1>9 || dInputC2<0 || dInputC2>9)
        {
            cout<<"\n Sorry we do not serve in this area.";
        }
        else if(sInputC1==dInputC1 && sInputC2==dInputC2)
        {
            cout<<"\n Source and Destination canot be same.";
        }
        else
        {
            result=calculate(sInputC1,sInputC2,dInputC1,dInputC2,weight,roverCount);
            if(result<0)
            {
                cout<<"\n Sorry the delivery is not possible within this range.";
            }
            else
            {
                dayCost+=result;
                cout<<"\n The total cost you need to pay is : Rs "<<result;
            }
        }

        if(!file)
        {
            cout<<"\n File creation unsucessful!";
        }
        else
        {
            file<<"\nSource: "<<sInputC1<<","<<sInputC2<<" Destination: "<<dInputC1<<","<<dInputC2<<" Weight: "<<weight<<" Cost: "<<result<<" Number of rovers used: "<<roverCount<<"\n";
        }
        tempi=dInputC1;
        tempj=dInputC2;
        cout<<"\n Thank You for trusting us.";
        cout<<"\n Press y to enter again and any other key to exit: ";
        cin>>ch;
    }while(ch=='y' || ch=='Y');
    file<<"\n Total cost of day = "<<dayCost;
    file.close();
    return 0;
}
