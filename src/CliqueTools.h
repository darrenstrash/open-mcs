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

#ifndef CLIQUE_TOOLS_H
#define CLIQUE_TOOLS_H

#include <vector>
#include <list>
#include <set>

namespace CliqueTools
{
    bool IsMaximalClique(std::vector<std::vector<int>> &adjacencyArray, std::list<int> const&clique, bool const verbose);
    bool IsClique(std::vector<std::vector<char>> &adjacencyMatrix, std::list<int> const &clique, bool const verbose);
    bool IsIndependentSet(std::vector<std::vector<char>> &adjacencyMatrix, std::list<int> const &clique, bool const verbose);
    bool IsMaximalIndependentSet(std::vector<std::vector<int>> &adjacencyArray, std::list<int> const &vertexSet, bool const verbose);
    bool IsIndependentSet(std::vector<std::vector<int>> &adjacencyArray, std::list<int> const &vertexSet, bool const verbose);
};

#endif //CLIQUE_TOOLS_H
