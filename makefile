
BUILD_DIR = build
SRC_DIR   = src
BIN_DIR   = bin

CFLAGS = -Winline -O2 -std=c++0x -g
#CFLAGS = -Winline -DDEBUG_MESSAGE -O0 -std=c++0x -g

SOURCES_TMP += MaxSubgraphAlgorithm.cpp
SOURCES_TMP += SparseIndependentSetColoringStrategy.cpp
SOURCES_TMP += MISS.cpp
SOURCES_TMP += StaticOrderMISS.cpp
SOURCES_TMP += MISR.cpp
SOURCES_TMP += MISQ.cpp
SOURCES_TMP += OrderingTools.cpp
SOURCES_TMP += MCS.cpp
SOURCES_TMP += StaticOrderMCS.cpp
SOURCES_TMP += MCR.cpp
SOURCES_TMP += MCQ.cpp
SOURCES_TMP += SparseCliqueColoringStrategy.cpp
SOURCES_TMP += IndependentSetColoringStrategy.cpp
SOURCES_TMP += CliqueColoringStrategy.cpp
SOURCES_TMP += CliqueTools.cpp
SOURCES_TMP += GraphTools.cpp
SOURCES_TMP += MemoryManager.cpp
SOURCES_TMP += Algorithm.cpp
SOURCES_TMP += DegeneracyTools.cpp
SOURCES_TMP += Tools.cpp

SOURCES=$(addprefix $(SOURCES_DIR)/, $(SOURCES_TMP))

OBJECTS_TMP=$(SOURCES_TMP:.cpp=.o)
OBJECTS=$(addprefix $(BUILD_DIR)/, $(OBJECTS_TMP))

DEPFILES_TMP:=$(SOURCES_TMP:.cpp=.d)
DEPFILES=$(addprefix $(BUILD_DIR)/, $(DEPFILES_TMP))

EXEC_NAMES = open-mcs

EXECS = $(addprefix $(BIN_DIR)/, $(EXEC_NAMES))

#DEFINE += -DDEBUG       #for debugging
#DEFINE += -DMEMORY_DEBUG #for memory debugging.

#some systems handle malloc and calloc with 0 bytes strangely.
DEFINE += -DALLOW_ALLOC_ZERO_BYTES# used by Eppstein and Strash (2011) 

VPATH = src

.PHONY : all

all: $(EXECS)

.PHONY : clean

clean: 
	rm -rf $(EXECS) $(BUILD_DIR) $(BIN_DIR)

$(BIN_DIR)/open-mcs: main.cpp ${OBJECTS} | ${BIN_DIR}
	g++ $(CFLAGS) ${DEFINE} ${OBJECTS} $(SRC_DIR)/main.cpp -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h $(BUILD_DIR)/%.d | $(BUILD_DIR)
	g++ $(CFLAGS) ${DEFINE} -c $< -o $@

$(BUILD_DIR)/%.d: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	g++ $(CFLAGS) -MM -MT '$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$<)' $< -MF $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

