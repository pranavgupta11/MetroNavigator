#include <bits/stdc++.h>
using namespace std;

map<string,vector<pair<string,int>>> mpfinal;
map<string,string> info;
vector<string> shortest_path;
int short_distance;

void make_graph(){
    mpfinal.clear();
    fstream fin;
    fin.open("djikstra1.txt",ios::in);
    int edges=0;
    string src,dest;
    int wt;
    map<string,vector<pair<string,int>>> mp;
    while(!fin.eof()){
        fin>>src>>dest>>wt;
        for(int i=0;i<src.size();i++){
            if(src[i]=='_') continue;
            src[i]=tolower(src[i]);
        }
        for(int i=0;i<dest.size();i++){
            if(dest[i]=='_') continue;
            dest[i]=tolower(dest[i]);
        }
        mp[src].push_back({dest,wt});
        mp[dest].push_back({src,wt});
        edges++;
    }
    fin.close();
    for(auto i:mp){
        string node=i.first;
        //cout<<i.first<<"--> ";
        int j;
        set<pair<string,int>> st;
        for(j=0;j<i.second.size();j++){
            st.insert({i.second[j].first,i.second[j].second});
        }
        for(auto z:st){
            mpfinal[node].push_back({z.first,z.second});
        }
        //cout<<endl;
    }
}

void Dijkstra(string src,string destination){
    bool flagSrc=false,flagDest=false;
    map<string,string> parent;
    for(auto i:mpfinal){
        string node=i.first;
        if(node==src){
            flagSrc=true;
        }
        if(node==destination){
            flagDest=true;
        }
    }
    if(flagSrc==false || flagDest==false){
        cout<<"\nYou entered either wrong Source or destination, which is not part of our ecosystem.\n";
        return;
    }
    map<string,int> dist;
    for(auto i:mpfinal){
        string node=i.first;
        dist[node]=INT_MAX;
    }
    set<pair<int,string>> st;
    dist[src]=0;
    parent[src]="src";
    st.insert(make_pair(0,src)); // (wt,node) pair is stored in set
    while(!st.empty()){
        auto p=*(st.begin());
        string nodeParent=p.second; // parent node
        int nodeDistance=p.first; // parent distance
        st.erase(p);
        for(auto child:mpfinal[nodeParent]){
            if((nodeDistance+child.second) < dist[child.first]){
                string dest=child.first; // where to reach from current parent node
                auto f=st.find({dist[dest],dest}); // checking if current child node is present in set
                if(f!=st.end()){ // this will not get executed for first few times
                    st.erase({dist[dest],dest});
                }
                dist[dest]=(nodeDistance+child.second);
                parent[dest]=nodeParent;
                st.insert({dist[dest],dest});
            }
        }
    }
    if(dist[destination]==INT_MAX){
        cout<<"\nThese places are not connected to each other directly or indirectly\n";
        return;
    }
    cout<<"\n***********Printing shortest path*********\n\n";
    string finish=destination;

    while(finish!=parent[src]){
        shortest_path.push_back(finish);
        finish=parent[finish];
    }
    reverse(shortest_path.begin(),shortest_path.end());
    int i;
    for(i=0;i<shortest_path.size()-1;i++){
        cout<<shortest_path[i]<<"-->";
    }
    cout<<shortest_path[i]<<endl<<endl;
    cout<<"Number of stations you need to change is: "<<shortest_path.size()<<endl<<endl;
    for(auto d:dist){
        string element=d.first;
        short_distance=d.second;
        if(element==destination){
            cout<<"Shortest distance from "<<src<<" to "<<element<<" is: "<<short_distance<<endl;
            break;
        }
    }
}

/*Description about all metro stattions can be added in later statges
void describe(vector<string> v){
    info.clear();
    info["lorem"]="It is the place where you live. you have to start your jouney from home only.";
    info["ipsum"]="The Red Fort is a historic fort in the city of Delhi (in Old Delhi) in India. \nIt served as the main residence of the Mughal Emperor, Emperor Shah Jahan";
    info["got"]="Gurgaon is a city just southwest of New Delhi in northern India.\nIt’s known as a financial and technology hub.\nThe Kingdom of Dreams is a large complex for theatrical shows.";
    info["philanthrophy"]="Tajmahal is one of the seven wonders of the world.\nIt was commissioned in 1632 by the Mughal emperor Shah Jahan to house the tomb of his favourite wife, Mumtaz Mahal." ;
    info["lorem"]="Sanjay Van is a sprawling city forest area near Vasant Kunj and Mehrauli in Delhi, India.\nIt is one of the most haunted places in Delhi.";
    info["lorem"]="Jaypee Noida-62 is an IT based University located in noida sec-62.\nIt is one of the best university in india to pursue computer science.";
    info["ipsum"]="There are many malls near your location. few of them include Pacific mall, EDM and Ambience mall";
    info["not"]="Noida, stands for New Okhla Industrial Development Authority.\nIt is a planned city located in Gautam Buddh Nagar district of the Indian state of Uttar Pradesh.";
    info["delhi"]="Delhi, India’s capital territory, is a massive metropolitan area in the country’s north.\nThe distinguished city of Delhi is blessed with several gardens and botanical houses which are some one of the features for which delhi is famous.";
    info["loreem"]="Agra is a city on the banks of the Yamuna river in the Agra district of the Indian state of Uttar Pradesh.\n It is famous for Tajmahal.";
    info["ipsum"]="Gwalior is a city in the central Indian state of Madhya Pradesh.\nIt's known for its palaces and temples, including the Sas Bahu Ka Mandir intricately carved Hindu temple.";
    cout<<"\n\n*******************Description of the places you entered*********************\n\n";
    for(int i=0;i<v.size();i++){
        if(info[v[i]]==""){
            cout<<i+1<<". "<<"Sorry, Currently we do not have any information about "<<v[i]<<" "<<endl<<endl;
        }
        else{
            cout<<i+1<<". "<<info[v[i]]<<endl<<endl;
        }
    }
}*/
void navigate_helper(string src,map<string,bool>& visited,string dest){
    visited[src]=true;
    for(auto i:mpfinal[src]){
        string node=i.first;
        if(visited[node]==false){ // to avoid cycle in DFS tree
            navigate_helper(node,visited,dest);
        }
    }
    //return false;
}
bool navigate(string src,string dest){
    bool flagSrc=false,flagDest=false;
    for(auto i:mpfinal){
        string node=i.first;
        if(node==src){
            flagSrc=true;
        }
        if(node==dest){
            flagDest=true;
        }
    }
    if(flagSrc==false || flagDest==false){
        cout<<"\nYou have entered either wrong Source or Destination, which is not part of our ecosystem.\n";
        return false;
    }
    map<string,bool> visited;
    for(auto i:mpfinal){
        string node=i.first;
        visited[node]=false;
    }
    // iterate over all vertices
    navigate_helper(src,visited,dest);
    if(visited[dest]==false){
        return false;
    }
    map<string,string> parent;
    map<string,int> dist;
    for(auto i:mpfinal){
        string node=i.first;
        dist[node]=INT_MAX;
    }
    set<pair<int,string>> st;
    dist[src]=0;
    parent[src]="src";
    st.insert(make_pair(0,src)); // (wt,node) pair is stored in set
    while(!st.empty()){
        auto p=*(st.begin());
        string nodeParent=p.second; // parent node
        int nodeDistance=p.first; // parent distance
        st.erase(p);
        for(auto child:mpfinal[nodeParent]){
            if((nodeDistance+child.second) < dist[child.first]){
                string dest=child.first; // pahunchna kahan hai current parent node se
                auto f=st.find({dist[dest],dest}); // checking if current child node is present in set
                if(f!=st.end()){ // this will not get executed for first few times
                    st.erase({dist[dest],dest});
                }
                dist[dest]=(nodeDistance+child.second);
                parent[dest]=nodeParent;
                st.insert({dist[dest],dest});
            }
        }
    }
    cout<<"\nYou can follow the below described path to reach to your misplaced device\n\n";
    string finish=dest;
    vector<string> shortest_path;
    while(finish!=parent[src]){
        shortest_path.push_back(finish);
        finish=parent[finish];
    }
    reverse(shortest_path.begin(),shortest_path.end());
    int i;
    for(i=0;i<shortest_path.size()-1;i++){
        cout<<shortest_path[i]<<"-->";
    }
    cout<<shortest_path[i]<<endl<<endl;
    return true;
    //dfs_helper(src,visited);
}

void kthSmallest(string src,int k){
    priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>> pq;
    map<string,int> dist;
    map<string,string> parent;
    bool flagSrc=false;
    for(auto i:mpfinal){
        string node=i.first;
        if(node==src){
            flagSrc=true;
        }
    }
    if(flagSrc==false){
        cout<<"\nYou have entered wrong Source which is not part of our ecosystem.\n";
        return;
    }
    for(auto i:mpfinal){
        string node=i.first;
        dist[node]=INT_MAX;
    }
    set<pair<int,string>> st;
    dist[src]=0;
    parent[src]="src";
    st.insert(make_pair(0,src)); // (wt,node) pair is stored in set
    while(!st.empty()){
        auto p=*(st.begin());
        string nodeParent=p.second; // parent node
        int nodeDistance=p.first; // parent distance
        st.erase(p);
        for(auto child:mpfinal[nodeParent]){
            if((nodeDistance+child.second) < dist[child.first]){
                string dest=child.first; // pahunchna kahan hai current parent node se
                auto f=st.find({dist[dest],dest}); // checking if current child node is present in set
                if(f!=st.end()){ // this will not get executed for first few times
                    st.erase({dist[dest],dest});
                }
                dist[dest]=(nodeDistance+child.second);
                parent[dest]=nodeParent;
                st.insert({dist[dest],dest});
            }
        }
    }
    for(auto i:dist){
        string node=i.first;
        short_distance=i.second;
        pq.push({short_distance,node});
    }
    int li=k;
    priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>> pq1;
    pq1=pq;
    cout<<"Shortest distance from "<<src<<" to "<<"all places is as follows:\n\n";
    while(pq1.size()>0){
        if(pq1.top().first==INT_MAX || pq1.top().second==src){
            pq1.pop();
            continue;
        }
        cout<<pq1.top().second<<" -- "<<pq1.top().first<<endl;
        pq1.pop();
    }
    cout<<endl;
    while(k>0){
        pq.pop();
        k--;
    }
    cout<<"\n************Printing 'K'th minimum shortest path*************\n\n";
    string finish=pq.top().second;
    vector<string> shortest_path;
    while(finish!=parent[src]){
        shortest_path.push_back(finish);
        finish=parent[finish];
    }
    reverse(shortest_path.begin(),shortest_path.end());
    int i;
    cout<<"Among the above mentioned shortest distances, the places that lies at "<<li<<" "<<"minimum shortest distance from "<<src<<" is "<<pq.top().second<<" which is at a distance of: "<<pq.top().first<<endl<<endl;
    for(i=0;i<shortest_path.size()-1;i++){
        cout<<shortest_path[i]<<" --> ";
    }
    cout<<shortest_path[i]<<endl<<endl;
}

void calculateCost( string src,string dest){
    if(shortest_path.size()==0){
        cout<<"Please Enter the route before calculating the fair prices. We need some data to work upon:)\n\n";
        return;
    }
    if(shortest_path.size()<=2 || short_distance<=4){
        cout<<endl<<"Total cost of travelling from source to destination is: "<<10<<endl<<endl;
    }
    else if((shortest_path.size()>2 && shortest_path.size()<=5) || (short_distance>4 && short_distance<=8)){
        cout<<endl<<"Total cost of travelling from source to destination is: "<<20<<endl<<endl;
    }
    else if((shortest_path.size()>5 && shortest_path.size()<=8) || (short_distance>8 && short_distance<=14)){
        cout<<endl<<"Total cost of travelling from source to destination is: "<<30<<endl<<endl;
    }
    else if((shortest_path.size()>8 && shortest_path.size()<=13) || (short_distance>14 && short_distance<=20)){
        cout<<endl<<"Total cost of travelling from source to destination is: "<<40<<endl<<endl;
    }
    else{
        cout<<endl<<"Total cost of travelling from source to destination is: "<<50<<endl<<endl;
        cout<<"No of Stations Traversed : "<<shortest_path.size()<<" "<<endl;
        cout<<"Shortest Distance : "<<short_distance<<" "<<endl<<endl;
    }
}
void printGraph(){
    for(auto i:mpfinal){
        string node=i.first;
        cout<<node<<" -> ";
        for(auto j:mpfinal[node]){
            cout<<"("<<j.first<<","<<j.second<<")"<<" ";
        }
        cout<<endl;
    }
    cout<<"\n**************************************************************\n";
}

int main()
{
    cout<<"-----------------------------METRO MAP NAVIGATOR--------------------------------\n\n";
    cout<<"1. Compute the shortest route between your current place and Destination.\n"<<endl;
    cout<<"2. If you want to go to the place with 'K'th minimum shortest path from your current location, then choose this option.\n"<<endl;
    cout<<"3. Calculate fair prices for the entered route\n\n";
    cout<<"Note: The fair prices for metro are as follows: \n\n";
    cout<<"For atmost 2 station changes or distance traversed at most 4km- 10 Rs"<<endl<<endl;
    cout<<"For atmost 5 station changes or distance traversed at most 8km- 20 Rs"<<endl<<endl;
    cout<<"For atmost 8 station changes or distance traversed at most 14km- 30 Rs"<<endl<<endl;
     cout<<"For atmost 13 station changes or distance traversed at most 20km- 40 Rs"<<endl<<endl;
      cout<<"Max Fare :  50 Rs"<<endl<<endl;


    make_graph();
    cout<<"\n**********THE GRAPH FORMED BY THE PROVIDED DATA IS************\n\n";
    //printGraph();
    char ch;
    do{
        cout<<"\nEnter the option:\n";
        int choice,k;
        cin>>choice;
        string src,dest;
        switch(choice){
            case 1:{
                cout<<"\nEnter your current location:  ";
                cin>>src;
                cout<<"\nEnter the Destination:  ";
                cin>>dest;
                cout<<endl;
                Dijkstra(src,dest);
                break;
            }

            case 2:{
                cout<<"\nEnter your current location and k :  ";
                cin>>src>>k;
                kthSmallest(src,k);
                break;
            }

            case 3:{
                calculateCost(src,dest);
                break;
            }


            default:{
                cout<<"\nYou Entered the wrong option\n";
                break;
            }
        }
        cout<<"\nDo you want to continue(y/n)\n";
        cin>>ch;
    }while(ch=='y');
}
