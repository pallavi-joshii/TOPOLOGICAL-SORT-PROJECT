#include <bits/stdc++.h>
using namespace std;
class job
{
    public:
    char jobid;
    int finishtime;
    string preceding_job;
   
};
 
void creategraph(vector<vector<int>> &graph,vector<int> &degree,
                vector<job> data)
{
   
   for(int i=0;i<data.size();i++)
    {
        int temp =  (int)data[i].jobid % 65;
       
        if(data[i].preceding_job.length() > 1)
        {
            for(int k=0;k<data[i].preceding_job.length();k++){
                int temp2 = (int)data[i].preceding_job[k] % 65;
                graph[temp2][temp] = data[i].finishtime;
                degree[temp]++;
            }
        }        
        else
        {
            int temp2 = (int)data[i].preceding_job[0] % 65;
 
            if(temp == temp2)
                graph[temp2][temp]=data[i].finishtime;
 
            else
            {
                graph[temp2][temp] = data[i].finishtime;
                degree[temp]++;
            }            
        }
 
    }
   
}
 
void alltopologicalSortUtil(vector<vector<int>> & graph,vector<int> & degree,
                 int V,bool visited[], vector<char> & res)
{
    bool flag = false;
   
    for (int i = 0; i < V; i++)
    {
        //  If degree is 0 and not yet visited then
        //  only choose that vertex
        if (degree[i] == 0 && !visited[i])
        {
            //  reducing degree of adjacent vertices
            for (int j = 0; j < V; j++)
            {
                if(graph[i][j]>0 && i!=j)
                degree[j]--;
            }
 
            //  including in result
            res.push_back((char)i+65);
            visited[i] = true;
            alltopologicalSortUtil(graph,degree, V, visited, res);
 
            // resetting visited, res and degree for
            // backtracking
            visited[i] = false;
            res.erase(res.end() - 1);
            for (int j = 0; j < V; j++)
            {
                if(graph[i][j]>0  && i!=j)
                degree[j]++;
            }
 
            flag = true;
        }
    }
 
    //  We reach here if all vertices are visited.
    //  So we print the solution here
    if (!flag)
    {
        for (int i = 0; i < res.size(); i++)
            cout << res[i] << " ";
        cout << endl;
    }
}
 
void topologicalSort(vector<vector<int>> &graph,vector<int> &degree,int V)
{
    vector<char> res;
 
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    alltopologicalSortUtil(graph,degree, V, visited, res);
   
}
 
 
void criticalpath(vector<vector<int>> &graph,int n){
    int max_in_row=0;
    int sum = 0;
    int temp=0,temp1=0,temp2=0;
    int flag=0;
    vector<char> intermediate;
    set<char> answer;
   
    for(int i=0;i<n;i++)
    {
        max_in_row =0;
        for(int j=0;j<n;j++)
        {
            if(i==j && graph[i][j] > 0 )
            {
                if(flag == 0)
                {
                    flag=1;
                    sum+=graph[i][j];
                    answer.insert((char)i+65);
                    temp2=i;
                    temp1=graph[i][j];
                }
                else
                {
                    if(temp1 < graph[i][j])
                    {
                        intermediate.insert(intermediate.begin(),*answer.begin());
                        answer.erase(answer.begin());
                        answer.insert(answer.begin(),(char)j+65);
                        intermediate.insert(intermediate.begin(),*answer.begin());
                        sum-=temp1;
                        temp1=graph[i][j];                        
                        sum+=temp1;                          
                    }
                    else
                    {
                        intermediate.push_back(*answer.begin());
                        intermediate.push_back((char)j+65);
                    }
                }
               
            }
                 
            if(max_in_row < graph[i][j] && i!=j)
            {
                max_in_row = graph[i][j];
                temp=j;
            }
 
            else if( graph[i][j] > 0 && i!=j )
            {
                intermediate.push_back((char)temp+65);
                intermediate.push_back((char)j+65);
            }
           
 
        }
        answer.insert((char)temp+65);
    }
   
     for(auto i= answer.begin();i != answer.end();i++)
         cout<<*i<<" ";
 
     for(auto i= answer.begin();i != answer.end();i++)
     {
        int a = (int)*i%65;
        auto j = i;
       int b= (int)*(++j)%65;
        if(j!=answer.end())          
            sum= sum + graph[a][b];
           
    }
 
    cout<<"\n\nAssumption: More Labour is present (if required) to perform "
    <<"the Intermediate Jobs. Intermediate Jobs are those jobs which takes "<<
    "lesser time to finish than its simultaneously occuring Job.";
       
    cout<<"\n\nOptimal Finish Time of the Job Schedule is : "<<sum<<"\n";
 
    for(int i= 0;i < intermediate.size();i+=2){
        cout<<"\nIntermediate Jobs of "<<intermediate[i]<<"->"<<intermediate[i+1];}
   
}
 
int main()
{
    ONLINE_JUDGE
      freopen("input2.txt","r",stdin);
      // freopen("input1.txt","r",stdin);
      freopen("output2.txt","w",stdout);
      // freopen("output1.txt","w",stdout);
      // freopen("input2.txt","r",stdin);
      // freopen("output2.txt","w",stdout);
 
 
    int n;
    //Number of Jobs you have
    cin>>n;
    vector<job> data;
    vector<vector<int>> graph(n,vector<int>(n,0));
    vector<int> degree;
    vector<string> jobs_desc;
    string s;
 
    char jobid;
    int finishtime;
    string preceding_job;
 
    for(int i=0;i<n;i++)
        degree.push_back(0);
 
    for(int i=0;i<n;i++)
    {
        getline(cin>>ws,s);
        jobs_desc.push_back(s);
    }
 
    cout<<"Job Id & Event Description \n";
 
    for(int i=0;i<n;i++)
        cout<<jobs_desc[i]<<"\n";
 
    //JOBS DETAILS ACCORDINGLY  
 
    while(cin>>jobid && jobid != '0')
    {
        //Job Id
        //Finish Time of this job
        cin>>finishtime;
        //Preceding Job before this Job
        cin>>preceding_job;
        data.push_back({jobid,finishtime,preceding_job});
               
    }    
   
    cout<<"\nInput schedule is:\n";
   
    creategraph(graph,degree,data);
    cout<<"  ";
    for(int i=0;i<n;i++)
        cout<<(char)(i+65)<<" ";
 
    for(int i=0;i<n;i++)
    {
        cout<<"\n"<<(char)(i+65)<<" ";
        for(int j=0;j<n;j++){
            cout<<graph[i][j]<<" ";
        }
    }
 
    cout<<"\n\nDegree(Incoming Edges) of Each Vertex:\n";
    for(int i=0;i<n;i++)
        cout<<degree[i]<<" ";
 
    cout<<"\n\nAll Topological sorts:\n\n";
 
    topologicalSort(graph,degree,n);
    cout<<"\nCritical path for the job schedule is:\n";
    criticalpath(graph,n);
 
    return 0;
 
}
