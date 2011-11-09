OBJS = factoring.o
CXXFLAGS += -Wall -g 
LDFLAGS += -lgmp -lgmpxx

all: factoring

genprime: genprime.o 
	$(CXX) genprime.o $(LDFLAGS) -o $@

factoring: $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -rf *.o *.d factoring

%.o : %.cpp %.h
	@$(CXX) -MM $(CXXFLAGS) $< > $*.d
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)
