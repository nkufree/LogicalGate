CXX=g++
CXXFLAGS_DEBUG=-std=c++17 -g -fno-omit-frame-pointer
CXXFLAGS_RELEASE=-std=c++17 -static -O2
SRC_PATH=./src
TEST_PATH=./unittest/testcase
INCLUDES=-I ./unittest/googletest/include
LIB_PATH=./unittest/googletest/lib
INCLUDES+=-I ./src/logical_gate/include
INCLUDES+=-I ./unittest/testcase/include
SRC=$(wildcard $(SRC_PATH)/**/*.cpp)
MAIN_SRC=$(wildcard $(SRC_PATH)/*.cpp)
TEST_SRC=$(wildcard $(TEST_PATH)/*.cpp)
LIBS=$(wildcard $(LIB_PATH)/*.a)

.PHONY: release debug test

release:
	$(CXX) -o main.exe $(SRC) $(MAIN_SRC) $(INCLUDES) $(CXXFLAGS_RELEASE)

debug:
	$(CXX) -o main.exe $(SRC) $(MAIN_SRC) $(INCLUDES) $(CXXFLAGS_DEBUG)

test:
	$(CXX) -o test.exe $(TEST_SRC) $(SRC) $(LIBS) $(INCLUDES) $(CXXFLAGS_RELEASE)