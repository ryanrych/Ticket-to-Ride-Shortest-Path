#include <iostream>
#include <map>
#include <string>
#include "PriorityQueue.h"
#include "OutDegree.h"

using namespace std;

//add no repeating nodes and cumulative edge weights
vector<string> dijkstras(map<string,OutDegree> graph,tuple<string,OutDegree> s,tuple<string,OutDegree> e,vector<string> closedStations,vector<Edge> closedTracks){
    PriorityQueue q;
    map<string,string> parent;
    map<string,int> shortest;
    vector<string> closed;
    closed.push_back(get<0>(s));
    for (int i=0;i<closedStations.size();i++){
        closed.push_back(closedStations.at(i));
    }

    for (int i=0;i<get<1>(s).outDegree;i++){
        if ((find(closed.begin(),closed.end(),get<1>(s).out[i].destination)!=closed.end()) || (find(closedTracks.begin(),closedTracks.end(),get<1>(s).out[i])!=closedTracks.end())){
            continue;
        }
        q.insert(get<1>(s).out[i].destination,get<1>(s).out[i].weight);
        parent.insert(pair<string,string>(get<1>(s).out[i].destination,get<0>(s)));
        shortest.insert(pair<string,int>(get<1>(s).out[i].destination,get<1>(s).out[i].weight));
    }

    while (q.getSize()!=0){
        string best=q.getMinimumItem();
        Edge* bestOut=graph.at(best).out;
        for (int i=0;i<graph.at(best).outDegree;i++){
            if ((find(closed.begin(),closed.end(),bestOut[i].destination)!=closed.end()) || (find(closedTracks.begin(),closedTracks.end(),bestOut[i])!=closedTracks.end())){
                continue;
            }
            if (q.contains(bestOut[i].destination)){
                if (shortest.at(bestOut[i].destination)>shortest.at(best)+bestOut[i].weight){
                    q.setPriority(bestOut[i].destination,shortest.at(best)+bestOut[i].weight);
                    parent.find(bestOut[i].destination)->second=best;
                    shortest.find(bestOut[i].destination)->second=shortest.at(best)+bestOut[i].weight;
                }
            }else{
                q.insert(bestOut[i].destination,shortest.at(best)+bestOut[i].weight);
                parent.insert(pair<string,string>(bestOut[i].destination,best));
                shortest.insert(pair<string,int>(bestOut[i].destination,shortest.at(best)+bestOut[i].weight));
            }
        }
        if (best.compare(get<0>(e))==0){
            break;
        }
        cout<<best<<" "<<shortest.at(best)<<" "<<parent.at(best)<<endl;
        closed.push_back(best);
        q.deleteMinimum();
    }

    vector<string> path;
    string step=get<0>(e);
    while (step.compare(get<0>(s))!=0) {
        path.push_back(step);
        step=parent.at(step);
    }
    path.push_back(get<0>(s));
    cout<<shortest.at(get<0>(e))<<endl;
    return path;
}

int main() {
    map<string,OutDegree> board;

    board.insert(make_pair<string,OutDegree>("Vancouver",OutDegree(new Edge[2]{Edge("Seattle",1),Edge("Calgary",3)},2)));
    board.insert(make_pair<string,OutDegree>("Calgary",OutDegree(new Edge[4]{Edge("Vancouver",3),Edge("Seattle",4),Edge("Helena",4),Edge("Winnipeg",6)},4)));
    board.insert(make_pair<string,OutDegree>("Winnipeg",OutDegree(new Edge[4]{Edge("Calgary",6),Edge("Helena",4),Edge("Duluth",4),Edge("Sault St.Marie",6)},4)));
    board.insert(make_pair<string,OutDegree>("Sault St.Marie",OutDegree(new Edge[4]{Edge("Winnipeg",6),Edge("Duluth",3),Edge("Toronto",2),Edge("Montreal",5)},4)));
    board.insert(make_pair<string,OutDegree>("Montreal",OutDegree(new Edge[4]{Edge("Sault St.Marie",5),Edge("Toronto",3),Edge("Boston",2),Edge("New York",3)},4)));
    board.insert(make_pair<string,OutDegree>("Boston",OutDegree(new Edge[2]{Edge("Montreal",2),Edge("New York",2)},2)));
    board.insert(make_pair<string,OutDegree>("Seattle",OutDegree(new Edge[4]{Edge("Vancouver",1),Edge("Portland",1),Edge("Calgary",4),Edge("Helena",6)},4)));
    board.insert(make_pair<string,OutDegree>("Helena",OutDegree(new Edge[7]{Edge("Calgary",4),Edge("Seattle",6),Edge("Salt Lake City",3),Edge("Denver",4),Edge("Omaha",5),Edge("Duluth",6),Edge("Winnipeg",4)},7)));
    board.insert(make_pair<string,OutDegree>("Duluth",OutDegree(new Edge[6]{Edge("Winnipeg",4),Edge("Sault St.Marie",3),Edge("Toronto",6),Edge("Chicago",3),Edge("Omaha",2),Edge("Helena",6)},6)));
    board.insert(make_pair<string,OutDegree>("Toronto",OutDegree(new Edge[5]{Edge("Sault St.Marie",2),Edge("Duluth",6),Edge("Montreal",3),Edge("Pittsburgh",2),Edge("Chicago",4)},5)));
    board.insert(make_pair<string,OutDegree>("New York",OutDegree(new Edge[4]{Edge("Montreal",3),Edge("Boston",2),Edge("Pittsburgh",2),Edge("Washington",2)},4)));
    board.insert(make_pair<string,OutDegree>("Portland",OutDegree(new Edge[3]{Edge("Seattle",1),Edge("Salt Lake City",6),Edge("San Francisco",5)},3)));
    board.insert(make_pair<string,OutDegree>("Salt Lake City",OutDegree(new Edge[5]{Edge("Portland",6),Edge("San Francisco",5),Edge("Helena",3),Edge("Denver",3),Edge("Las Vegas",3)},5)));
    board.insert(make_pair<string,OutDegree>("Denver",OutDegree(new Edge[7]{Edge("Helena",4),Edge("Omaha",4),Edge("Kansas City",4),Edge("Oklahoma City",4),Edge("Santa Fe",2),Edge("Phoenix",5),Edge("Salt Lake City",3)},7)));
    board.insert(make_pair<string,OutDegree>("Omaha",OutDegree(new Edge[5]{Edge("Helena",5),Edge("Duluth",2),Edge("Kansas City",1),Edge("Denver",4),Edge("Chicago",4)},5)));
    board.insert(make_pair<string,OutDegree>("Kansas City",OutDegree(new Edge[4]{Edge("Omaha",1),Edge("Saint Louis",2),Edge("Oklahoma City",2),Edge("Denver",4)},4)));
    board.insert(make_pair<string,OutDegree>("Chicago",OutDegree(new Edge[5]{Edge("Duluth",3),Edge("Toronto",4),Edge("Pittsburgh",3),Edge("Saint Louis",2),Edge("Omaha",4)},5)));
    board.insert(make_pair<string,OutDegree>("Saint Louis",OutDegree(new Edge[5]{Edge("Kansas City",2),Edge("Chicago",2),Edge("Pittsburgh",5),Edge("Nashville",2),Edge("Little Rock",2)},5)));
    board.insert(make_pair<string,OutDegree>("Pittsburgh",OutDegree(new Edge[7]{Edge("Saint Louis",5),Edge("Chicago",3),Edge("Washington",2),Edge("New York",2),Edge("Nashville",4),Edge("Raleigh",2),Edge("Toronto",2)},7)));
    board.insert(make_pair<string,OutDegree>("Nashville",OutDegree(new Edge[5]{Edge("Atlanta",1),Edge("Saint Louis",2),Edge("Raleigh",3),Edge("Little Rock",3),Edge("Pittsburgh",4)},5)));
    board.insert(make_pair<string,OutDegree>("Washington",OutDegree(new Edge[3]{Edge("Pittsburgh",2),Edge("Raleigh",2),Edge("New York",2)},3)));
    board.insert(make_pair<string,OutDegree>("Raleigh",OutDegree(new Edge[5]{Edge("Nashville",3),Edge("Pittsburgh",2),Edge("Atlanta",2),Edge("Charleston",2),Edge("Washington",2)},5)));
    board.insert(make_pair<string,OutDegree>("Atlanta",OutDegree(new Edge[5]{Edge("Charleston",2),Edge("Raleigh",2),Edge("New Orleans",4),Edge("Nashville",1),Edge("Miami",5)},5)));
    board.insert(make_pair<string,OutDegree>("Charleston",OutDegree(new Edge[3]{Edge("Atlanta",2),Edge("Raleigh",2),Edge("Miami",4)},3)));
    board.insert(make_pair<string,OutDegree>("Miami",OutDegree(new Edge[3]{Edge("Charleston",4),Edge("Atlanta",5),Edge("New Orleans",6)},3)));
    board.insert(make_pair<string,OutDegree>("New Orleans",OutDegree(new Edge[4]{Edge("Houston",2),Edge("Miami",6),Edge("Atlanta",4),Edge("Little Rock",3)},4)));
    board.insert(make_pair<string,OutDegree>("Little Rock",OutDegree(new Edge[5]{Edge("Oklahoma City",2),Edge("Dallas",2),Edge("Nashville",3),Edge("Saint Louis",2),Edge("New Orleans",3)},5)));
    board.insert(make_pair<string,OutDegree>("Oklahoma City",OutDegree(new Edge[6]{Edge("Little Rock",2),Edge("Dallas",2),Edge("Kansas City",2),Edge("Denver",4),Edge("Santa Fe",3),Edge("El Paso",5)},6)));
    board.insert(make_pair<string,OutDegree>("Dallas",OutDegree(new Edge[4]{Edge("Oklahoma City",2),Edge("Little Rock",2),Edge("Houston",1),Edge("El Paso",4)},4)));
    board.insert(make_pair<string,OutDegree>("Houston",OutDegree(new Edge[3]{Edge("Dallas",1),Edge("New Orleans",2),Edge("El Paso",6)},3)));
    board.insert(make_pair<string,OutDegree>("El Paso",OutDegree(new Edge[6]{Edge("Santa Fe",2),Edge("Oklahoma City",5),Edge("Dallas",4),Edge("Houston",6),Edge("Los Angeles",6),Edge("Phoenix",3)},6)));
    board.insert(make_pair<string,OutDegree>("Santa Fe",OutDegree(new Edge[4]{Edge("Denver",2),Edge("El Paso",2),Edge("Phoenix",3),Edge("Oklahoma City",3)},4)));
    board.insert(make_pair<string,OutDegree>("Phoenix",OutDegree(new Edge[4]{Edge("Los Angeles",3),Edge("Denver",5),Edge("Santa Fe",3),Edge("El Paso",3)},4)));
    board.insert(make_pair<string,OutDegree>("Las Vegas",OutDegree(new Edge[2]{Edge("Salt Lake City",3),Edge("Los Angeles",2)},2)));
    board.insert(make_pair<string,OutDegree>("Los Angeles",OutDegree(new Edge[4]{Edge("San Francisco",3),Edge("Las Vegas",2),Edge("Phoenix",3),Edge("El Paso",6)},4)));
    board.insert(make_pair<string,OutDegree>("San Francisco",OutDegree(new Edge[3]{Edge("Portland",5),Edge("Los Angeles",3),Edge("Salt Lake City",5)},3)));

    string start="Vancouver";
    string end="Miami";
    vector<string> blockedStations={"Seattle","Helena","Omaha","Kansas City","Nashville","Atlanta","Duluth","Toronto","Raleigh","Charleston","Dallas","Santa Fe","Phoenix","Las Vegas"};
    vector<Edge> blockedTracks={Edge("New Orleans",3),Edge("El Paso",5)};

    vector<string> test=dijkstras(board,tuple<string,OutDegree>(start,board.at(start)),tuple<string,OutDegree>(end,board.at(end)),blockedStations,blockedTracks);

    for (int i=0;i<test.size();i++){
        cout<<test.at(i)<<endl;
    }

    return 0;
}