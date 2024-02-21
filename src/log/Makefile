LIB_NAME=liblog.a
FILES = LogConf Log
OBJECTS = $(FILES:%=%.o)

all: $(LIB_NAME)

$(OBJECTS) : %.o : %.cpp %.h
	$(CXX) -c $< -o $@ $(CXXFLAGS) -I..

$(LIB_NAME): $(OBJECTS)
	ar sr $@ $(OBJECTS)

clean:
	rm -f *.o *.a
