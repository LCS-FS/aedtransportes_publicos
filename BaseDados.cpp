#include <cmath>
#include "BaseDados.h"
// O(|V|log|V|), where V = stops
map<Stop, double> BaseDados::nearStops(double lat, double lon, double radius) {

    map<Stop, double> nearStopsMap;
    map<int, Stop>::iterator iter;
    double distance;

    for (iter = stopMap.begin(); iter != stopMap.end(); iter++) {
        distance = haversine(lat, lon, iter->second.getLatitude(), iter->second.getLongitude());
        if (distance <= radius)
            nearStopsMap[iter->second] = distance;
    }

    return nearStopsMap;
}

// O(|V|log|V|), where V = stops
map<Stop, double> BaseDados::nearestStop(double lat, double lon) {
    map<Stop, double> nearestStopMap;
    map<int, Stop>::iterator iter = stopMap.begin();
    double distance = haversine(lat, lon, iter->second.getLatitude(), iter->second.getLongitude()), newDistance;
    Stop nearestStop;

    for (iter = stopMap.begin(); iter != stopMap.end(); iter++) {
        newDistance = haversine(lat, lon, iter->second.getLatitude(), iter->second.getLongitude());
        if (newDistance < distance) {
            nearestStop = iter->second;
            distance = newDistance;
        }
    }

    nearestStopMap[nearestStop] = distance;
    return nearestStopMap;
}

void BaseDados::onFootStops() {

    map<int, Stop>::iterator iter1;
    map<Stop, double>::iterator iter2;

    for (iter1 = stopMap.begin(); iter1 != stopMap.end(); iter1++) {
        map<Stop, double> onFootMap = nearStops(iter1->second.getLatitude(), iter1->second.getLongitude(), 0.15);

        for (iter2 = onFootMap.begin(); iter2 != onFootMap.end(); iter2++) {

            if (iter2->first.getLatitude() != iter1->second.getLatitude() && iter2->first.getLongitude() != iter1->second.getLongitude()) {

                pmGraph.addEdge(reverseStopMap[iter1->second.getCode()], reverseStopMap[iter2->first.getCode()],
                                iter2->second, "_PE", "Caminhar a pé.");

                if(iter2->first.getCode()[iter2->first.getCode().length() - 1] != 'M')

                    pdGraph.addEdge(reverseStopMap[iter1->second.getCode()],reverseStopMap[iter2->first.getCode()],
                                    iter2->second, "_PE", "Caminhar a pé.");

            }
        }
    }
}

//O(|L|*|V|log|E|) where L = lines, V = stops, E = edge(stop -> stop)
void BaseDados::loadAllLines() {
    ifstream lines;
    lines.open("../dataset/lines.csv");
    if(lines.is_open()){
        string throwaway, code, name, line;
        getline(lines, throwaway);

        while(getline(lines, line)){
            stringstream sep(line);
            getline(sep, code, ',');
            getline(sep, name, '\n');

            loadLine(code, name);
        }
        pmGraph = mGraph;
        pdGraph = dGraph;
    }
    else throw ("Lines.csv file not found in dataset folder!");
}

//O(|V|log|E|), where V = stops, E = edge(stop -> stop)
void BaseDados::loadLine(string code, string name) {
    ifstream line;
    int n, stopid, nextid;
    string stop, next;
    double weight;

    for (int i = 0; i < 2; i++){
        string rev = "";
        if(i == 1) rev = "_rev";
        if((code == "300" or code == "301" or code == "302" or code == "303") && i == 1) continue;
        line.open("../dataset/line_" + code + "_" + to_string(i) + ".csv");

        if(line.is_open()){
            line >> n;
            line >> stop;
            for (int j = 2; j <= n; j++){
                line >> next;

                stopid = reverseStopMap[stop];
                nextid = reverseStopMap[next];

                weight = haversine(stopMap[stopid].getLatitude(), stopMap[stopid].getLongitude(), stopMap[nextid].getLatitude(), stopMap[nextid].getLongitude());
                mGraph.addEdge(stopid, nextid, weight, code, name);
                if(code[code.length() - 1] != 'M') dGraph.addEdge(stopid, nextid, weight, code+rev, name);
                stop = next;
            }
        }
        else throw ("line_" + code + "_" + to_string(i) + ".csv not found in dataset folder!");
    }
}

//O(1)
double BaseDados::haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

BaseDados::BaseDados(Graph dGraph, Graph mGraph, Graph pdGraph, Graph pmGraph, map<int, Stop> stopMap, map<string, int> reverseStopMap) : dGraph(dGraph), mGraph(mGraph),
                                                                                                                                          pdGraph(pdGraph),
                                                                                                                                          pmGraph(pmGraph) {
    this->stopMap = stopMap;
    this->reverseStopMap = reverseStopMap;
}

map<string, int> BaseDados::getReverseStopMap() const{
    return reverseStopMap;
}

map<int, Stop> BaseDados::getStopMap() const {
    return stopMap;
}

Graph BaseDados::getDGraph() const {
    return dGraph;
}

Graph BaseDados::getMGraph() const {
    return mGraph;
}

const Graph &BaseDados::getPdGraph() const {
    return pdGraph;
}

const Graph &BaseDados::getPmGraph() const {
    return pmGraph;
}
