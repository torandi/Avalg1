OBJS = factoring.o
CXXFLAGS += -Wall -g 
LDFLAGS += -lgmp -lgmpxx

all: factoring
 
factoring: $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -rf *.o *.d factoring

%.o : %.cpp %.h
	@$(CXX) -MM $(CXXFLAGS) $< > $*.d
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)
