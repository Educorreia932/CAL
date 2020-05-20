#include "UserInterface.h"

#include <graphviewer.h>
#include <chrono>

void clearScreen() {
    #ifdef __unix__
        system("clear");
    #endif

    #ifdef _WIN32
        system("cls");
    #endif
}

void UserInterface::showMainMenu() {
    clearScreen();

    cout << "                MENU                " << endl
         << " ===================================" << endl
         << " Choose a tourist route         [1]" << endl
         << " Show the map                   [2]" << endl
         << " Adjust the settings            [3]" << endl    // Like disabling showing all of the edges and showing only those who are part of the route
         << " Exit                           [0]" << endl
         << endl;
}

void UserInterface::mainMenuSelection() {
    bool calculated = false;

    while (true) {
        chrono::steady_clock::time_point begin;
        chrono::steady_clock::time_point end;

        showMainMenu();

        int option = readOption(0, 3);

        switch (option) {
            case 1:
                if (!calculated) {
                    cout << endl
                         << "Calculating..." << endl
                         << endl;

                    begin = chrono::steady_clock::now();

                    graph->handleFloydWarshall("PORTO");

                    end = chrono::steady_clock::now();

                    cout << "The algorithm was completed in "
                         << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0
                         << " seconds."
                         << endl
                         << endl;

                    pause();

                    calculated = true;
                }

                POIsSelection();

                break;
            case 2:
                showGraph(res);
                break;
            case 3:
                settingsSelection();
                break;
            default:
                return;
        }
    }
}

ulli UserInterface::showPOIs(vector<ulli> toVisit) {
    clearScreen();
    int index = 0;

    // Printing the points of interest
    cout << "\t POINTS OF INTEREST \t" << endl;
    cout << "============================================" << endl;

    // Iterate over POIs
    for (pair<string, ulli> p : poiStorage->getMap()) {
        cout << left << setw(40) << p.first;

        // POI is already selected
        if (find(toVisit.begin(), toVisit.end(), p.second) != toVisit.end())
            cout << "[SELECTED]" << endl;

        else
            cout << "[" << index << "]" << endl;

        index++;
    }

    cout << left << setw(40) << "None" << "[" << index << "]" << endl;
    cout << endl;

    index = 0;
    int selected = readOption(0, poiStorage->getMap().size());

    for (pair<string, ulli> p : poiStorage->getMap()) {
        if (index == selected)
            return p.second;

        index++;
    }

    return -1;
}

void UserInterface::POIsSelection() {
    vector<ulli> toVisit = {};

    ulli selected;

    while ((selected = showPOIs(toVisit)) != -1)
        toVisit.push_back(selected);

    // Case there isn't sufficient POIs to visit, i.e 1 or 2, the program will go back to the MainMenu
    if (toVisit.empty() || toVisit.size() == 1) return;

    getchar();

    res = graph->trajectoryOrder(toVisit[0], toVisit);

    for (int i = 0 ; i < res.size(); i++)
        cout << res[i] << endl;
}

void UserInterface::showSettings() {
    clearScreen();

    cout << "                MENU                " << endl
         << " ===================================" << endl
         << " Show all? " << (showAll? "YES" : "NO ") <<  "                  [1]" << endl
         << " Exit                           [0]" << endl
         << endl;
}

void UserInterface::settingsSelection() {
    while (true) {
        showSettings();

        int selected = readOption(0, 1);

        switch (selected) {
            case 1:
                showAll = !showAll;
                break;
            case 0:
                return;
        }
    }
}

UserInterface::UserInterface(Graph *graph, PoiStorage *poiStorage) : graph(graph), poiStorage(poiStorage) {}

void UserInterface::showGraph(const vector<ulli> &res) {
    auto gv = new GraphViewer(900, 900, false);

    #ifdef __unix__
        gv->setBackground("../../data/map.png");
    #else
        gv->setBackground("../data/map.png");
    #endif
        gv->createWindow(900, 900);

    double min_lon = -8.6226691;
    double max_lon = -8.5989075;
    double min_lat = 41.1584432;
    double max_lat = 41.14049;

    gv->defineEdgeCurved(false);

    // Add nodes
    for (Vertex* v : graph->getVertexSet()) {
        gv->setVertexSize(v->getID(), 9);
        gv->setVertexColor(v->getID(), "YELLOW");

        if (showAll || (find(res.begin(), res.end(), v->getID()) != res.end())) {
            gv->addNode(
                    v->getID(),
                    (v->lon - min_lon) / (max_lon - min_lon) * 900,
                    (v->lat - min_lat) / (max_lat - min_lat) * 900
            );

            string poi_name;
        }
    }

    int edge_id = 0;

    // Add edges
    for (Vertex* v : graph->getVertexSet())
        for (const Edge &w : v->getAdj()) {
            if (showAll || (find(res.begin(), res.end(), v->getID()) != res.end() && find(res.begin(), res.end(), w.getDest()->getID()) != res.end()))
                gv->addEdge(edge_id, v->getID(), w.getDest()->getID(), EdgeType::UNDIRECTED);

            edge_id++;
        }

    int current_color = 0;

    // Customize
    for (ulli id : res) {
        gv->setVertexSize(id, 11);
        gv->setVertexColor(id, "RED");

        if (!poiStorage->findPOI(id).empty()) {
            gv->setVertexSize(id, 13);
            current_color++;
        }
    }

    gv->rearrange();
    cout << "Press a key to exit." << endl;
    getchar();
}

int readOption(int min, unsigned int max) {
    int option;

    while (true) {
        cout << "Your option: ";

        if (cin >> option && option >= min && option <= max) {
            cin.ignore(1000, '\n');
            return option;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cerr << endl
                 << "Invalid input. Please try again:" << endl
                 << endl;
        }
    }
}

void pause() {
    cout << "Press any key to continue ...";
    cin.get();
}

