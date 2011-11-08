OBJS = factoring.o
CFLAGS += -Wall -g 
LDFLAGS += -lgmp -lgmpxx

all: factoring
 
factoring: $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -rf *.o *.d factoring

%.o : %.cpp %.h
	@$(CXX) -MM $(CFLAGS) $< > $*.d
	$(CXX) $(CFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)
