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

    board.insert(make_pair<string,OutDegree>("Vancouver",OutDegree(new Edge[2]{Edge("Vancouver","Seattle",1),Edge("Vancouver","Calgary",3)},2)));
    board.insert(make_pair<string,OutDegree>("Calgary",OutDegree(new Edge[4]{Edge("Calgary","Vancouver",3),Edge("Calgary","Seattle",4),Edge("Calgary","Helena",4),Edge("Calgary","Winnipeg",6)},4)));
    board.insert(make_pair<string,OutDegree>("Winnipeg",OutDegree(new Edge[4]{Edge("Winnipeg","Calgary",6),Edge("Winnipeg","Helena",4),Edge("Winnipeg","Duluth",4),Edge("Winnipeg","Sault St.Marie",6)},4)));
    board.insert(make_pair<string,OutDegree>("Sault St.Marie",OutDegree(new Edge[4]{Edge("Sault St.Marie","Winnipeg",6),Edge("Sault St.Marie","Duluth",3),Edge("Sault St.Marie","Toronto",2),Edge("Sault St.Marie","Montreal",5)},4)));
    board.insert(make_pair<string,OutDegree>("Montreal",OutDegree(new Edge[4]{Edge("Montreal","Sault St.Marie",5),Edge("Montreal","Toronto",3),Edge("Montreal","Boston",2),Edge("Montreal","New York",3)},4)));
    board.insert(make_pair<string,OutDegree>("Boston",OutDegree(new Edge[2]{Edge("Boston","Montreal",2),Edge("Boston","New York",2)},2)));
    board.insert(make_pair<string,OutDegree>("Seattle",OutDegree(new Edge[4]{Edge("Seattle","Vancouver",1),Edge("Seattle","Portland",1),Edge("Seattle","Calgary",4),Edge("Seattle","Helena",6)},4)));
    board.insert(make_pair<string,OutDegree>("Helena",OutDegree(new Edge[7]{Edge("Helena","Calgary",4),Edge("Helena","Seattle",6),Edge("Helena","Salt Lake City",3),Edge("Helena","Denver",4),Edge("Helena","Omaha",5),Edge("Helena","Duluth",6),Edge("Helena","Winnipeg",4)},7)));
    board.insert(make_pair<string,OutDegree>("Duluth",OutDegree(new Edge[6]{Edge("Duluth","Winnipeg",4),Edge("Duluth","Sault St.Marie",3),Edge("Duluth","Toronto",6),Edge("Duluth","Chicago",3),Edge("Duluth","Omaha",2),Edge("Duluth","Helena",6)},6)));
    board.insert(make_pair<string,OutDegree>("Toronto",OutDegree(new Edge[5]{Edge("Toronto","Sault St.Marie",2),Edge("Toronto","Duluth",6),Edge("Toronto","Montreal",3),Edge("Toronto","Pittsburgh",2),Edge("Toronto","Chicago",4)},5)));
    board.insert(make_pair<string,OutDegree>("New York",OutDegree(new Edge[4]{Edge("New York","Montreal",3),Edge("New York","Boston",2),Edge("New York","Pittsburgh",2),Edge("New York","Washington",2)},4)));
    board.insert(make_pair<string,OutDegree>("Portland",OutDegree(new Edge[3]{Edge("Portland","Seattle",1),Edge("Portland","Salt Lake City",6),Edge("Portland","San Francisco",5)},3)));
    board.insert(make_pair<string,OutDegree>("Salt Lake City",OutDegree(new Edge[5]{Edge("Salt Lake City","Portland",6),Edge("Salt Lake City","San Francisco",5),Edge("Salt Lake City","Helena",3),Edge("Salt Lake City","Denver",3),Edge("Salt Lake City","Las Vegas",3)},5)));
    board.insert(make_pair<string,OutDegree>("Denver",OutDegree(new Edge[7]{Edge("Denver","Helena",4),Edge("Denver","Omaha",4),Edge("Denver","Kansas City",4),Edge("Denver","Oklahoma City",4),Edge("Denver","Santa Fe",2),Edge("Denver","Phoenix",5),Edge("Denver","Salt Lake City",3)},7)));
    board.insert(make_pair<string,OutDegree>("Omaha",OutDegree(new Edge[5]{Edge("Omaha","Helena",5),Edge("Omaha","Duluth",2),Edge("Omaha","Kansas City",1),Edge("Omaha","Denver",4),Edge("Omaha","Chicago",4)},5)));
    board.insert(make_pair<string,OutDegree>("Kansas City",OutDegree(new Edge[4]{Edge("Kansas City","Omaha",1),Edge("Kansas City","Saint Louis",2),Edge("Kansas City","Oklahoma City",2),Edge("Kansas City","Denver",4)},4)));
    board.insert(make_pair<string,OutDegree>("Chicago",OutDegree(new Edge[5]{Edge("Chicago","Duluth",3),Edge("Chicago","Toronto",4),Edge("Chicago","Pittsburgh",3),Edge("Chicago","Saint Louis",2),Edge("Chicago","Omaha",4)},5)));
    board.insert(make_pair<string,OutDegree>("Saint Louis",OutDegree(new Edge[5]{Edge("Saint Louis","Kansas City",2),Edge("Saint Louis","Chicago",2),Edge("Saint Louis","Pittsburgh",5),Edge("Saint Louis","Nashville",2),Edge("Saint Louis","Little Rock",2)},5)));
    board.insert(make_pair<string,OutDegree>("Pittsburgh",OutDegree(new Edge[7]{Edge("Pittsburgh","Saint Louis",5),Edge("Pittsburgh","Chicago",3),Edge("Pittsburgh","Washington",2),Edge("Pittsburgh","New York",2),Edge("Pittsburgh","Nashville",4),Edge("Pittsburgh","Raleigh",2),Edge("Pittsburgh","Toronto",2)},7)));
    board.insert(make_pair<string,OutDegree>("Nashville",OutDegree(new Edge[5]{Edge("Nashville","Atlanta",1),Edge("Nashville","Saint Louis",2),Edge("Nashville","Raleigh",3),Edge("Nashville","Little Rock",3),Edge("Nashville","Pittsburgh",4)},5)));
    board.insert(make_pair<string,OutDegree>("Washington",OutDegree(new Edge[3]{Edge("Washington","Pittsburgh",2),Edge("Washington","Raleigh",2),Edge("Washington","New York",2)},3)));
    board.insert(make_pair<string,OutDegree>("Raleigh",OutDegree(new Edge[5]{Edge("Raleigh","Nashville",3),Edge("Raleigh","Pittsburgh",2),Edge("Raleigh","Atlanta",2),Edge("Raleigh","Charleston",2),Edge("Raleigh","Washington",2)},5)));
    board.insert(make_pair<string,OutDegree>("Atlanta",OutDegree(new Edge[5]{Edge("Atlanta","Charleston",2),Edge("Atlanta","Raleigh",2),Edge("Atlanta","New Orleans",4),Edge("Atlanta","Nashville",1),Edge("Atlanta","Miami",5)},5)));
    board.insert(make_pair<string,OutDegree>("Charleston",OutDegree(new Edge[3]{Edge("Charleston","Atlanta",2),Edge("Charleston","Raleigh",2),Edge("Charleston","Miami",4)},3)));
    board.insert(make_pair<string,OutDegree>("Miami",OutDegree(new Edge[3]{Edge("Miami","Charleston",4),Edge("Miami","Atlanta",5),Edge("Miami","New Orleans",6)},3)));
    board.insert(make_pair<string,OutDegree>("New Orleans",OutDegree(new Edge[4]{Edge("New Orleans","Houston",2),Edge("New Orleans","Miami",6),Edge("New Orleans","Atlanta",4),Edge("New Orleans","Little Rock",3)},4)));
    board.insert(make_pair<string,OutDegree>("Little Rock",OutDegree(new Edge[5]{Edge("Little Rock","Oklahoma City",2),Edge("Little Rock","Dallas",2),Edge("Little Rock","Nashville",3),Edge("Little Rock","Saint Louis",2),Edge("Little Rock","New Orleans",3)},5)));
    board.insert(make_pair<string,OutDegree>("Oklahoma City",OutDegree(new Edge[6]{Edge("Oklahoma City","Little Rock",2),Edge("Oklahoma City","Dallas",2),Edge("Oklahoma City","Kansas City",2),Edge("Oklahoma City","Denver",4),Edge("Oklahoma City","Santa Fe",3),Edge("Oklahoma City","El Paso",5)},6)));
    board.insert(make_pair<string,OutDegree>("Dallas",OutDegree(new Edge[4]{Edge("Dallas","Oklahoma City",2),Edge("Dallas","Little Rock",2),Edge("Dallas","Houston",1),Edge("Dallas","El Paso",4)},4)));
    board.insert(make_pair<string,OutDegree>("Houston",OutDegree(new Edge[3]{Edge("Houston","Dallas",1),Edge("Houston","New Orleans",2),Edge("Houston","El Paso",6)},3)));
    board.insert(make_pair<string,OutDegree>("El Paso",OutDegree(new Edge[6]{Edge("El Paso","Santa Fe",2),Edge("El Paso","Oklahoma City",5),Edge("El Paso","Dallas",4),Edge("El Paso","Houston",6),Edge("El Paso","Los Angeles",6),Edge("El Paso","Phoenix",3)},6)));
    board.insert(make_pair<string,OutDegree>("Santa Fe",OutDegree(new Edge[4]{Edge("Santa Fe","Denver",2),Edge("Santa Fe","El Paso",2),Edge("Santa Fe","Phoenix",3),Edge("Santa Fe","Oklahoma City",3)},4)));
    board.insert(make_pair<string,OutDegree>("Phoenix",OutDegree(new Edge[4]{Edge("Phoenix","Los Angeles",3),Edge("Phoenix","Denver",5),Edge("Phoenix","Santa Fe",3),Edge("Phoenix","El Paso",3)},4)));
    board.insert(make_pair<string,OutDegree>("Las Vegas",OutDegree(new Edge[2]{Edge("Las Vegas","Salt Lake City",3),Edge("Las Vegas","Los Angeles",2)},2)));
    board.insert(make_pair<string,OutDegree>("Los Angeles",OutDegree(new Edge[4]{Edge("Los Angeles","San Francisco",3),Edge("Los Angeles","Las Vegas",2),Edge("Los Angeles","Phoenix",3),Edge("Los Angeles","El Paso",6)},4)));
    board.insert(make_pair<string,OutDegree>("San Francisco",OutDegree(new Edge[3]{Edge("San Francisco","Portland",5),Edge("San Francisco","Los Angeles",3),Edge("San Francisco","Salt Lake City",5)},3)));

    string start="Helena";
    string end="Omaha";
    vector<string> blockedStations={"Duluth","Saint Louis","Denver","Winnipeg"};
    vector<Edge> blockedTracks={Edge("Helena","Omaha"),Edge("Duluth","Omaha"),Edge("Denver","Omaha"),Edge("Kansas City","Omaha")};
//    vector<string> blockedStations={};
//    vector<Edge> blockedTracks={};

    vector<string> test=dijkstras(board,tuple<string,OutDegree>(start,board.at(start)),tuple<string,OutDegree>(end,board.at(end)),blockedStations,blockedTracks);

    for (int i=0;i<test.size();i++){
        cout<<test.at(i)<<endl;
    }

    return 0;
}