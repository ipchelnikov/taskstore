CXX=c++
RM=rm -f
CPPFLAGS=-g -Wall -std=c++1y
LDLIBS=-lpthread $(shell root-config --libs)

all: iothreads wptr promises algo

iothreads: iothreads.cpp
	$(CXX) $(CPPFLAGS) -o iothreads iothreads.cpp $(LDLIBS)
wptr: wptr.cpp
	$(CXX) $(CPPFLAGS) -o wptr wptr.cpp $(LDLIBS)
promises: promises.cpp
	$(CXX) $(CPPFLAGS) -o promises promises.cpp $(LDLIBS)
algo: algo.cpp
	$(CXX) $(CPPFLAGS) -o algo algo.cpp $(LDLIBS)
clean:
	$(RM) iothreads wptr promises algo
