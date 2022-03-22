/**
 * @file my_web_server.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <algorithm>
#include <string>

#include "web_code/web/my_web_server.h"

MyWebServer::MyWebServer() : routes(std::vector<RouteData>(0)),
                                    busses(std::vector<BusData>(0)) {
}

void MyWebServer::UpdateBus(const BusData& bData, bool deleted) {
    auto it = std::find_if(busses.begin(), busses.end(), [&](const BusData& b)
                           { return b.id == bData.id; });

    // Check whether the bus is found
    if (it != busses.end()) {
        // Check whether we need to delete the bus from the simulator
        if (deleted) {
            busses.erase(it);
            return;
        }

        int index = std::distance(busses.begin(), it);

        busses[index].id = bData.id;
        busses[index].position = bData.position;
        busses[index].num_passengers = bData.num_passengers;
        busses[index].capacity = bData.capacity;
        busses[index].color = bData.color;
    } else {
        busses.push_back(bData);
    }
}

void MyWebServer::UpdateRoute(const RouteData& rData, bool deleted) {
    auto it = std::find_if(routes.begin(), routes.end(), [&](const RouteData& r)
                           { return r.id == rData.id; });

    // Check whether the route is found
    if (it != routes.end()) {
        // Check whether we need to delete the route from the simulator
        if (deleted) {
            routes.erase(it);
            return;
        }

        int index = std::distance(routes.begin(), it);

        routes[index].id = rData.id;
        routes[index].stops = rData.stops;
    } else {
        routes.push_back(rData);
    }
}


