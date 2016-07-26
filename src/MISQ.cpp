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

#include "MISQ.h"
#include "OrderingTools.h"
#include "Tools.h"

#include <cmath>
#include <iostream>

using namespace std;

MISQ::MISQ(vector<vector<char>> const &vAdjacencyMatrix)
: MaxSubgraphAlgorithm("misq")
, m_AdjacencyMatrix(vAdjacencyMatrix)
, coloringStrategy(m_AdjacencyMatrix)
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

void MISQ::InitializeOrder(std::vector<int> &P, std::vector<int> &vVertexOrder, std::vector<int> &vColors)
{
    OrderingTools::InitialOrderingMISQ(m_AdjacencyMatrix, P, vColors);
    vVertexOrder = P;
}

void MISQ::Color(std::vector<int> const &vVertexOrder, std::vector<int> &vVerticesToReorder, std::vector<int> &vColors)
{
    coloringStrategy.Color(m_AdjacencyMatrix, vVertexOrder/* evaluation order */, vVerticesToReorder /* color order */, vColors);
}

void MISQ::GetNewOrder(vector<int> &vNewVertexOrder, vector<int> &vVertexOrder, vector<int> const &P, int const chosenVertex)
{
    vNewVertexOrder.resize(P.size());
    {
        size_t uNewIndex(0);
        for (int const candidate : P) {
            if (chosenVertex == candidate) continue;
            if (!m_AdjacencyMatrix[chosenVertex][candidate]) vNewVertexOrder[uNewIndex++] = candidate;
        }
        vNewVertexOrder.resize(uNewIndex);
    }

    R.push_back(chosenVertex);
}

void MISQ::ProcessOrderAfterRecursion(std::vector<int> &vVertexOrder, std::vector<int> &P, std::vector<int> &vColors, int const chosenVertex)
{
////    cout << "MISQ::ProcessOrderAfterRecursion" << endl;
////    Color(vVertexOrder, P, vColors);
    if (chosenVertex != -1) R.pop_back();
}

