#include<bits/stdc++.h>
#include<cmath>
using namespace std;
#define N 10
#define M 10
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

double calculate(int sInputC1,int sInputC2,int dInputC1,int dInputC2,int weight){
    char grid[10][10];
    int i,j,roveri=5,roverj=5,totalDist=0,cost;
    for(i=0;i<10;i++){
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
    grid[roveri][roverj]='s';
    grid[sInputC1][sInputC2]='d';
    int rti=minDistance(grid);
    rti*=100;
    cout<<"\n Distance from Store House to source is: "<<rti<< " meteres. ";
     for(i=0;i<10;i++){
        for(j=0;j<10;j++)
        {
            grid[i][j]='*';
        }
    }
    grid[dInputC1][dInputC2]='s';
    grid[roveri][roverj]='d';
    int dtr=minDistance(grid);
    dtr*=100;
    cout<<"\n Distance from destination to Store House is: "<<dtr<< " meteres. ";
    totalDist=rti+resShortestPath+dtr;
    cout<<"\n Your total distance is: "<<totalDist<< " meteres. ";
    if(totalDist<=1000){
        cost=totalDist*0.5;
    }
    else if(totalDist>1000 && totalDist<=2000)
    {
        cost=5+(totalDist-1000)*0.75;
    }
    else if(totalDist>2000 && totalDist<=10000)
    {
        cost=5+(totalDist-1000)*0.85;
    }
    else
    {
        cost=-1;
    }
    return cost;
}
int main()
{
    int sInputC1,sInputC2,dInputC1,dInputC2,weight;
    double result;
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
        if(sInputC1<0 || sInputC1>9 || sInputC2<0 || sInputC2>9 || dInputC1<0 || dInputC1>9 || dInputC2<0 || dInputC2>9)
        {
            cout<<"\n Sorry we do not serve in this area.";
        }
        else if(sInputC1==dInputC1 && sInputC2==dInputC2)
        {
            cout<<"\n Source and Destination canot be same.";
        }
        else if(weight<0 || weight>10)
        {
            cout<<"\n Cannot deliver this much weight.";
        }
        else
        {
            result=calculate(sInputC1,sInputC2,dInputC1,dInputC2,weight);
            if(result<0)
            {
                cout<<"\n Sorry the delivery is not possible within this range.";
            }
            else
            {
                cout<<"\n The total cost you need to pay is : Rs "<<result;
            }
        }
        cout<<"\n Thank You for trusting us.";
        cout<<"\n Press y to enter again and any other key to exit: ";
        cin>>ch;
    }while(ch=='y' || ch=='Y');
    return 0;
}