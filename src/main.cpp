/* 
    This program is free software: you can redistribute it and/or modify 
    it under the terms of the GNU General Public License as published by 
    the Free Software Foundation, either version 3 of the License, or 
    (at your option) any later version. 
 
    This program is distributed in the hope that it will be useful, 
    but WITHOUT ANY WARRANTY; without even the implied warranty of 
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
    GNU General Public License for more details. 
 
    You should have received a copy of the GNU General Public License 
    along with this program.  If not, see <http://www.gnu.org/licenses/> 
*/

// local includes
#include "ArraySet.h"
#include "Tools.h"
#include "CliqueTools.h"

// maximum clique algorithms
#include "MCQ.h"
#include "MCR.h"
#include "StaticOrderMCS.h"
#include "MCS.h"

// maximum independent set algorithms
#include "MISQ.h"
#include "MISR.h"
#include "StaticOrderMISS.h"
#include "MISS.h"


// system includes
#include <map>
#include <list>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*! \file main.cpp

    \brief Main entry point for quick cliques software. This is where we parse the command line options, read the inputs, and decide which clique method to run.

    \author Darren Strash (first name DOT last name AT gmail DOT com)

    \copyright Copyright (c) 2016 Darren Strash. This code is released under the GNU Public License (GPL) 3.0.

    \image html gplv3-127x51.png

    \htmlonly
    <center>
    <a href="gpl-3.0-standalone.html">See GPL 3.0 here</a>
    </center>
    \endhtmlonly
*/

bool isValidAlgorithm(string const &name)
{
    return (name == "mcq" || name == "mcr" || name == "static-order-mcs" || name == "mcs");
}

void ProcessCommandLineArgs(int const argc, char** argv, map<string,string> &mapCommandLineArgs)
{
    for (int i = 1; i < argc; ++i) {
////        cout << "Processing argument " << i << endl;
        string const argument(argv[i]);
////        cout << "    Argument is " << argument << endl;
        size_t const positionOfEquals(argument.find_first_of("="));
////        cout << "    Position of = " << positionOfEquals << endl;
        if (positionOfEquals != string::npos) {
            string const key  (argument.substr(0,positionOfEquals));
            string const value(argument.substr(positionOfEquals+1));
////            cout << "    Parsed1: " << key << "=" << value << endl;
            mapCommandLineArgs[key] = value;
        } else {
////            cout << "    Parsed2: " << argument << endl;
            mapCommandLineArgs[argument] = "";
        }
    }
}

void PrintDebugWarning()
{
    cout << "\n\n\n\n\n" << flush;
    cout << "#########################################################################" << endl << flush;
    cout << "#                                                                       #" << endl << flush;
    cout << "#    WARNING: Debugging is turned on. Don't believe the run times...    #" << endl << flush;
    cout << "#                                                                       #" << endl << flush;
    cout << "#########################################################################" << endl << flush;
    cout << "\n\n\n\n\n" << flush;
}

void PrintExperimentalWarning()
{
    cout << "NOTE: Open MCS v1.0." << endl << flush;
}

string basename(string const &fileName)
{
    string sBaseName(fileName);

    size_t const lastSlash(sBaseName.find_last_of("/\\"));
    if (lastSlash != string::npos) {
        sBaseName = sBaseName.substr(lastSlash+1);
    }

    size_t const lastDot(sBaseName.find_last_of("."));
    if (lastDot != string::npos) {
        sBaseName = sBaseName.substr(0, lastDot);
    }

    return sBaseName;
}

int main(int argc, char** argv)
{
    int failureCode(0);

    map<string,string> mapCommandLineArgs;

    ProcessCommandLineArgs(argc, argv, mapCommandLineArgs);

    bool   const bQuiet(mapCommandLineArgs.find("--verbose") == mapCommandLineArgs.end());
    bool   const bOutputLatex(mapCommandLineArgs.find("--latex") != mapCommandLineArgs.end());
    bool   const bOutputTable(mapCommandLineArgs.find("--table") != mapCommandLineArgs.end());
    string const inputFile((mapCommandLineArgs.find("--input-file") != mapCommandLineArgs.end()) ? mapCommandLineArgs["--input-file"] : "");
    string const algorithm((mapCommandLineArgs.find("--algorithm") != mapCommandLineArgs.end()) ? mapCommandLineArgs["--algorithm"] : "");
    bool   const bComputeIndependentSet(mapCommandLineArgs.find("--compute-independent-set") != mapCommandLineArgs.end());
    bool   const bPrintHeader(mapCommandLineArgs.find("--header") != mapCommandLineArgs.end());

    bool   const bTableMode(bOutputLatex || bOutputTable);

    if (!bTableMode) {
#ifdef DEBUG_MESSAGE
        PrintDebugWarning();
#endif //DEBUG_MESSAGE
    }

    if (inputFile.empty()) {
        cout << "ERROR: Missing input file " << endl;
        // ShowUsageMessage();
        // return 1; // TODO/DS
    }

    string name(algorithm);
    if (!bTableMode && algorithm.empty()) {
        cout << "NOTE: Missing algorithm name, using mcs." << endl;
        name = "mcs";
        // ShowUsageMessage();
        // return 1; // TODO/DS
    }

    if (argc <= 1 || !isValidAlgorithm(name)) {
        cout << "usage: " << argv[0] << " --input-file=<filename> [--compute-independent-set] --algorithm=<mcq|mcr|static-order-mcs|mcs [--latex] [--header]" << endl;
    }

    // algorithm for independent sets technically has different name.
    if (bComputeIndependentSet) {
        name = name.replace(name.size()-3,2, "mis");
    }

    Algorithm *pAlgorithm(nullptr);

    int n; // number of vertices
    int m; // 2x number of edges

    vector<list<int>> adjacencyList;
    if (inputFile.find(".graph") != string::npos) {
        if (!bTableMode) cout << "Reading .graph file format. " << endl << flush;
        adjacencyList = readInGraphAdjListEdgesPerLine(n, m, inputFile);
    } else {
        if (!bTableMode) cout << "Reading .edges file format. " << endl << flush;
        adjacencyList = readInGraphAdjList(n, m, inputFile);
    }

    bool const bComputeAdjacencyMatrix(adjacencyList.size() < 20000);
    bool const bShouldComputeAdjacencyMatrix(name == "mcq" || name == "mcr" || name == "static-order-mcs" || name == "mcs" || name == "misq" || name == "misr" || name == "static-order-miss" || name == "miss");

    bool const addDiagonals(name == "misq" || name == "misr" || name == "static-order-miss" || name == "miss");

    if (bShouldComputeAdjacencyMatrix && !bComputeAdjacencyMatrix) {
        cout << "ERROR: unable to compute adjacencyMatrix, since the graph is too large: " << adjacencyList.size() << endl << flush;
        exit(1);
    }

    vector<vector<char>> vAdjacencyMatrix;

    if (bComputeAdjacencyMatrix) {
        vAdjacencyMatrix.resize(n);

        for(int i=0; i<n; i++) {
            vAdjacencyMatrix[i].resize(n);
            for(int const neighbor : adjacencyList[i]) {
                vAdjacencyMatrix[i][neighbor] = 1; 
            }
            if (addDiagonals) {
                vAdjacencyMatrix[i][i] = 1;
            }
        }
    }

    adjacencyList.clear(); // does this free up memory? probably some...

    if (name == "mcq") {
        pAlgorithm = new MCQ(vAdjacencyMatrix);
    } else if (name == "mcr") {
        pAlgorithm = new MCR(vAdjacencyMatrix);
    } else if (name == "static-order-mcs") {
        pAlgorithm = new StaticOrderMCS(vAdjacencyMatrix);
    } else if (name == "mcs") {
        pAlgorithm = new MCS(vAdjacencyMatrix);
    } else if (name == "misq") {
        pAlgorithm = new MISQ(vAdjacencyMatrix);
    } else if (name == "misr") {
        pAlgorithm = new MISR(vAdjacencyMatrix);
    } else if (name == "static-order-miss") {
        pAlgorithm = new StaticOrderMISS(vAdjacencyMatrix);
    } else if (name == "miss") {
        pAlgorithm = new MISS(vAdjacencyMatrix);
    } else {
        cout << "ERROR: unrecognized algorithm name " << name << endl;
        return 1;
    }

    auto verifyCliqueMatrix = [&vAdjacencyMatrix](list<int> const &clique) {
        bool const isIS = CliqueTools::IsClique(vAdjacencyMatrix, clique, true /* verbose */);
        if (!isIS) {
            cout << "ERROR: Set " << (isIS ? "is" : "is not" ) << " a clique!" << endl;
        }
    };

    auto verifyIndependentSetMatrix = [&vAdjacencyMatrix](list<int> const &clique) {
        bool const isIS = CliqueTools::IsIndependentSet(vAdjacencyMatrix, clique, true /* verbose */);
        if (!isIS) {
            cout << "ERROR: Set " << (isIS ? "is" : "is not" ) << " an independent set!" << endl;
        }
    };

    auto printCliqueSize = [](list<int> const &clique) {
        cout << "Found clique of size " << clique.size() << endl << flush;
    };

////    pAlgorithm->AddCallBack(printCliqueSize);
////    pAlgorithm->AddCallBack(printClique);

    if (!bComputeAdjacencyMatrix) {
        assert(0);
    } else {
////        pAlgorithm->AddCallBack(verifyCliqueMatrix);
////        pAlgorithm->AddCallBack(verifyIndependentSetMatrix);
    }

    // Run algorithm
    list<list<int>> cliques;

    pAlgorithm->SetQuiet(bQuiet);

    RunAndPrintStats(pAlgorithm, cliques, bTableMode);

////    cout << "Last clique has size: " << cliques.back().size() << endl << flush;

    cliques.clear();

    vAdjacencyMatrix.clear();
    delete pAlgorithm; pAlgorithm = nullptr;

#ifdef DEBUG_MESSAGE
    PrintDebugWarning();
#endif

    return 0;
}
