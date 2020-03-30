#include <iostream>
#include <map>
#include <string>
#include "PriorityQueue.h"
#include "OutDegree.h"

using namespace std;

//int* dijkstras(){
//
//}

int main() {
    map<string,OutDegree> board;
    board.insert(make_pair<string,OutDegree>("Vancouver",OutDegree(new Edge[2]{Edge("Seattle",1),Edge("Calgary",3)})));
    board.insert(make_pair<string,OutDegree>("Calgary",OutDegree(new Edge[4]{Edge("Vancouver",3),Edge("Seattle",4),Edge("Helena",4),Edge("Winnipeg",6)})));
    board.insert(make_pair<string,OutDegree>("Winnipeg",OutDegree(new Edge[4]{Edge("Calgary",6),Edge("Helena",4),Edge("Duluth",4),Edge("Sault St.Marie",6)})));
    board.insert(make_pair<string,OutDegree>("Sault St.Mary",OutDegree(new Edge[4]{Edge("Winnipeg",6),Edge("Duluth",3),Edge("Toronto",2),Edge("Montreal",5)})));
    board.insert(make_pair<string,OutDegree>("Montreal",OutDegree(new Edge[4]{Edge("Sault St.Marie",5),Edge("Toronto",3),Edge("Boston",2),Edge("New York",3)})));
    board.insert(make_pair<string,OutDegree>("Boston",OutDegree(new Edge[2]{Edge("Montreal",2),Edge("New York",2)})));
    board.insert(make_pair<string,OutDegree>("Seattle",OutDegree(new Edge[4]{Edge("Vancouver",1),Edge("Portland",1),Edge("Calgary",4),Edge("Helena",6)})));
    board.insert(make_pair<string,OutDegree>("Helena",OutDegree(new Edge[7]{Edge("Calgary",4),Edge("Seattle",6),Edge("Salt Lake City",3),Edge("Denver",4),Edge("Omaha",5),Edge("Duluth",6),Edge("Winnipeg",4)})));
    board.insert(make_pair<string,OutDegree>("Duluth",OutDegree(new Edge[6]{Edge("Winnipeg",4),Edge("Sault St.Marie",3),Edge("Toronto",6),Edge("Chicago",3),Edge("Omaha",2),Edge("Helena",6)})));
    board.insert(make_pair<string,OutDegree>("Toronto",OutDegree(new Edge[4]{Edge("Sault St.Marie",2),Edge("Duluth",6),Edge("Montreal",3),Edge("Pittsburgh",2)})));
    board.insert(make_pair<string,OutDegree>("New York",OutDegree(new Edge[4]{Edge("Montreal",3),Edge("Boston",2),Edge("Pittsburgh",2),Edge("Washington",2)})));
    board.insert(make_pair<string,OutDegree>("Portland",OutDegree(new Edge[3]{Edge("Seattle",1),Edge("Salt Lake City",6),Edge("San Francisco",5)})));
    board.insert(make_pair<string,OutDegree>("Salt Lake City",OutDegree(new Edge[5]{Edge("Portland",6),Edge("San Francisco",5),Edge("Helena",3),Edge("Denver",3),Edge("Las Vegas",3)})));
    board.insert(make_pair<string,OutDegree>("Denver",OutDegree(new Edge[7]{Edge("Helena",4),Edge("Omaha",4),Edge("Kansas City",4),Edge("Oklahoma City",4),Edge("Santa Fe",2),Edge("Phoenix",5),Edge("Salt Lake City",3)})));
    board.insert(make_pair<string,OutDegree>("Omaha",OutDegree(new Edge[5]{Edge("Helena",5),Edge("Duluth",2),Edge("Kansas City",1),Edge("Denver",4),Edge("Chicago",4)})));
    board.insert(make_pair<string,OutDegree>("Kansas City",OutDegree(new Edge[4]{Edge("Omaha",1),Edge("Saint Louis",2),Edge("Oklahoma City",2),Edge("Denver",4)})));
    board.insert(make_pair<string,OutDegree>("Chicago",OutDegree(new Edge[5]{Edge("Duluth",3),Edge("Toronto",4),Edge("Pittsburgh",3),Edge("Saint Louis",2),Edge("Omaha",4)})));
    board.insert(make_pair<string,OutDegree>("Saint Louis",OutDegree(new Edge[5]{Edge("Kansas City",2),Edge("Chicago",2),Edge("Pittsburgh",5),Edge("Nashville",2),Edge("Little Rock",2)})));
    board.insert(make_pair<string,OutDegree>("Pittsburgh",OutDegree(new Edge[7]{Edge("Saint Louis",5),Edge("Chicago",3),Edge("Washington",2),Edge("New York",2),Edge("Nashville",4),Edge("Raleigh",2),Edge("Toronto",2)})));
    board.insert(make_pair<string,OutDegree>("Nashville",OutDegree(new Edge[5]{Edge("Atlanta",1),Edge("Saint Louis",2),Edge("Raleigh",2),Edge("Little Rock",3),Edge("Pittsburgh",4)})));
    board.insert(make_pair<string,OutDegree>("Washington",OutDegree(new Edge[3]{Edge("Pittsburgh",2),Edge("Raleigh",2),Edge("New York",2)})));
    board.insert(make_pair<string,OutDegree>("Raleigh",OutDegree(new Edge[5]{Edge("Nashville",3),Edge("Pittsburgh",2),Edge("Atlanta",2),Edge("Charleston",2),Edge("Washington",2)})));
    board.insert(make_pair<string,OutDegree>("Atlanta",OutDegree(new Edge[5]{Edge("Charleston",2),Edge("Raleigh",2),Edge("New Orleans",4),Edge("Nashville",1),Edge("Miami",5)})));
    board.insert(make_pair<string,OutDegree>("Charleston",OutDegree(new Edge[3]{Edge("Atlanta",2),Edge("Raleigh",2),Edge("Miami",4)})));
    board.insert(make_pair<string,OutDegree>("Miami",OutDegree(new Edge[3]{Edge("Charleston",4),Edge("Atlanta",5),Edge("New Orlean",6)})));
    board.insert(make_pair<string,OutDegree>("New Orleans",OutDegree(new Edge[4]{Edge("Houston",2),Edge("Miami",6),Edge("Atlanta",4),Edge("Little Rock",3)})));
    board.insert(make_pair<string,OutDegree>("Little Rock",OutDegree(new Edge[5]{Edge("Oklahoma City",2),Edge("Dallas",2),Edge("Nashville",3),Edge("Saint Louis",2),Edge("New Orleans",3)})));
    board.insert(make_pair<string,OutDegree>("Oklahoma City",OutDegree(new Edge[6]{Edge("Little Rock",2),Edge("Dallas",2),Edge("Kansas City",2),Edge("Denver",4),Edge("Santa Fe",3),Edge("El Paso",5)})));
    board.insert(make_pair<string,OutDegree>("Dallas",OutDegree(new Edge[4]{Edge("Oklahoma City",2),Edge("Little Rock",2),Edge("Houston",1),Edge("El Paso",4)})));
    board.insert(make_pair<string,OutDegree>("Houston",OutDegree(new Edge[3]{Edge("Dallas",1),Edge("New Orleans",2),Edge("El Paso",6)})));
    board.insert(make_pair<string,OutDegree>("El Paso",OutDegree(new Edge[6]{Edge("Santa Fe",2),Edge("Oklahoma City",5),Edge("Dallas",4),Edge("Houston",6),Edge("Los Angeles",6),Edge("Phoenix",3)})));
    board.insert(make_pair<string,OutDegree>("Santa Fe",OutDegree(new Edge[4]{Edge("Denver",2),Edge("El Paso",2),Edge("Phoenix",3),Edge("Oklahoma City",3)})));
    board.insert(make_pair<string,OutDegree>("Phoenix",OutDegree(new Edge[4]{Edge("Los Angeles",3),Edge("Denver",5),Edge("Santa Fe",3),Edge("El Paso",3)})));
    board.insert(make_pair<string,OutDegree>("Las Vegas",OutDegree(new Edge[2]{Edge("Salt Lake City",3),Edge("Los Angeles",2)})));
    board.insert(make_pair<string,OutDegree>("Los Angeles",OutDegree(new Edge[4]{Edge("San Francisco",3),Edge("Las Vegas",2),Edge("Phoenix",3),Edge("El Paso",6)})));
    board.insert(make_pair<string,OutDegree>("San Francisco",OutDegree(new Edge[3]{Edge("Portland",5),Edge("Los Angeles",3),Edge("Salt Lake City",5)})));
    


    return 0;
}