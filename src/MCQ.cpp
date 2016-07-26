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

#include "MCQ.h"
#include "OrderingTools.h"

#include <cmath>
#include <iostream>

using namespace std;

MCQ::MCQ(vector<vector<char>> const &vAdjacencyMatrix)
: MaxSubgraphAlgorithm("mcq")
, m_AdjacencyMatrix(vAdjacencyMatrix)
, coloringStrategy(m_AdjacencyMatrix)
////, m_bInvert(0)
{
    R.reserve(m_AdjacencyMatrix.size());

    stackP.resize(m_AdjacencyMatrix.size() + 1);
    stackColors.resize(m_AdjacencyMatrix.size() + 1);
    stackOrder.resize(m_AdjacencyMatrix.size() + 1);
    stackEvaluatedHalfVertices.resize(m_AdjacencyMatrix.size() + 1);

    // don't reserve for 0-th vectors, they get std::move'd by InitialOrdering
    for (int index = 0; index < stackP.size(); ++index) {
        stackP[index].reserve(m_AdjacencyMatrix.size());
        stackColors[index].reserve(m_AdjacencyMatrix.size());
        stackOrder[index].reserve(m_AdjacencyMatrix.size());
    }
}

////void MCQ::SetInvert(bool const invert)
////{
////    m_bInvert = invert;
////}

void MCQ::InitializeOrder(std::vector<int> &P, std::vector<int> &vVertexOrder, std::vector<int> &vColors)
{
    OrderingTools::InitialOrderingMCQ(m_AdjacencyMatrix, P, vColors);
    vVertexOrder = P;
}

void MCQ::Color(std::vector<int> const &vVertexOrder, std::vector<int> &vVerticesToReorder, std::vector<int> &vColors)
{
    coloringStrategy.Color(m_AdjacencyMatrix, vVertexOrder/* evaluation order */, vVerticesToReorder /* color order */, vColors);
////    cout << "Colors:";
////    for (int const color : vColors) {
////        cout << color << " ";
////    }
////    cout << endl;
}

void MCQ::GetNewOrder(vector<int> &vNewVertexOrder, vector<int> &vVertexOrder, vector<int> const &P, int const chosenVertex)
{
////    cout << "OldP    :";
////    for (int const vertex : P) {
////        cout << vertex << " ";
////    }
////    cout << endl;

    vNewVertexOrder.resize(P.size());
    {
        size_t uNewIndex(0);
        for (int const candidate : P) {
////            if (!m_bInvert && m_AdjacencyMatrix[chosenVertex][candidate]) vNewVertexOrder[uNewIndex++] = candidate;
            if (m_AdjacencyMatrix[chosenVertex][candidate]) vNewVertexOrder[uNewIndex++] = candidate;
        }
        vNewVertexOrder.resize(uNewIndex);
    }

////    cout << "NewOrder:";
////    for (int const vertex : vNewVertexOrder) {
////        cout << vertex << " ";
////    }
////    cout << endl;

    R.push_back(chosenVertex);
}

void MCQ::ProcessOrderAfterRecursion(std::vector<int> &vVertexOrder, std::vector<int> &P, std::vector<int> &vColors, int const chosenVertex)
{
    if (chosenVertex != -1) R.pop_back();
}
