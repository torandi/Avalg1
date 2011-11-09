OBJS = factoring.o
CXXFLAGS += -Wall -g 
LDFLAGS += -lgmp -lgmpxx

all: factoring

genprime: genprime.o 
	$(CXX) genprime.o $(LDFLAGS) -o $@
	rm primes.h
	./genprime > primes.h


factoring: $(OBJS) primes.h
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -rf *.o *.d factoring

%.o : %.cpp %.h
	@$(CXX) -MM $(CXXFLAGS) $< > $*.d
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)
