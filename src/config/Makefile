LIB_NAME=libconf.a
FILES = ConfigFile IParseSwitches ParseMainArgs MainArg IConfiguration

OBJECTS = $(FILES:%=%.o)

all: $(LIB_NAME)

$(OBJECTS) : %.o : %.cpp %.h
	$(CXX) -c $< -o $@ $(CXXFLAGS) 


$(LIB_NAME): $(OBJECTS)
	ar sr $@ $(OBJECTS)

clean:
	rm -f *.o *.a
