# **Open MCS**: An open implementation of the MC family of clique solvers 

[![license](https://img.shields.io/badge/license-GPL%20v3.0-blue.svg)](http://www.gnu.org/licenses/)

The intent of this software is to provide an open, faithful, and competetive implementation of the
MC family of maximum clique algorithms, as described in the following papers.

###MCQ

DS/TODO: correct authors, which proceedigs, insert DOI.
*An efficient branch-and-bound algorithm for finding a maximum clique*,
**Etsuji Tomita and Tomokazu Seki**,
Proceedings of Discrete Mathematics and Theoretical Computer Science. LNCS 2731, pp. 278–289, 2003.
[doi:10.1007/3-540-45066-1_22](https://doi.org/10.1007/3-540-45066-1_22)

###MCR

*An efficient branch-and-bound algorithm for finding a maximum clique with computational experiments*,
**Etsuji Tomita and Toshikatsu Kameda**,
Journal of Global Optimization, *37*:95--111, 2007.
[doi:10.1007/s10898-006-9039-7](https://doi.org/10.1007/s10898-006-9039-7)

and

###MCS (including version with static vertex ordering)

*A simple and faster branch-and-bound algorithm for finding a maximum clique*,
**Etsuji Tomita, Yoichi Sutani, Takanori Higashi, Shinya Takahashi, and Mitsuo Wakatsuki**,
Proceedings of WALCOM 2010, LNCS 5942, pp. 191–203, 2010.
DS/TODO: update DOI.
[doi:10.1007/978-3-642-20662-7_31](https://doi.org/10.1007/978-3-642-20662-7_31)

##This package includes:

 - C++ code for implementations of MCQ, MCR, and MCS clique algorithms, and their independent set equivalents.
 - The 2nd DIMACS challenge instances used in the original experiments for these algorithms. (in ./data/)
 - A test script used to build and run all algorithms on all data sets (./test.sh)

Please feel free to contact me with any questions!

### Version
1.0

### Building

```sh
$ git clone https://github.com/darrenstrash/open-mcs.git
$ cd open-mcs
$ make
```

### Running
```sh
$ ./bin/open-mcs --input-file=<input graph> [--compute-independent-set] --algorithm=<mcq|mcr|static-order-mcs|mcs>
```

or

```sh
$ ./test_all.sh
```

to run MCS on all (dimacs) data sets

Should you not want to wait the day or so it takes to run all graphs, consider running
on a smaller subset, such as with the command

```sh
$ ./test_fast.sh
```

, which takes about 30 seconds.

### Graph Format

Current, the unweighted METIS format is expected:

<# vertices> <# edges> 1

followed by <#vertices> lines, where the i-th lines contains 
a list of space-separated neighbors of i. All vertices range from 1 to <# vertices>


### Data

data.tar.gz contains the data sets from the 2nd DIMACS Challenge..

Copyright
----

Copyright (c) 2016 Darren Strash.

License
----

This code is released under the GNU Public License (GPL) 3.0.

To read the GPL 3.0, read the file COPYING in this directory.

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

Contact
----

**Darren Strash** (first name DOT last name AT gmail DOT com)
