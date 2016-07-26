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

#ifndef ORDERING_TOOLS_H
#define ORDERING_TOOLS_H

#include <vector>
#include <cstddef>
#include <string>

namespace OrderingTools
{
    void InitialOrderingMCQ(std::vector<std::vector<char>> const &adjacencyMatrix, std::vector<int> &vOrderedVertices, std::vector<int> &vColoring);
    void InitialOrderingMCR(std::vector<std::vector<char>> const &adjacencyMatrix, std::vector<int> &vOrderedVertices, std::vector<int> &vColoring, size_t &cliqueSize);
    void InitialOrderingMCR(std::vector<std::vector<int>> const &adjacencyArray, std::vector<int> &vOrderedVertices, std::vector<int> &vColoring, size_t &cliqueSize);

    void InitialOrderingMCQ(std::vector<std::vector<int>> const &adjacencyArray, std::vector<int> &vOrderedVertices, std::vector<int> &vColoring);

    void InitialOrderingMISQ(std::vector<std::vector<char>> const &adjacencyMatrix, std::vector<int> &vOrderedVertices, std::vector<int> &vColoring);

    void InitialOrderingMISR(std::vector<std::vector<int>> const &adjacencyArray, std::vector<int> &vOrderedVertices, std::vector<int> &vColoring, size_t &cliqueSize);

    void InitialOrderingMISR(std::vector<std::vector<char>> const &adjacencyMatrix, std::vector<int> &vOrderedVertices, std::vector<int> &vColoring, size_t &cliqueSize);

};

#endif //ORDERING_TOOLS_H
