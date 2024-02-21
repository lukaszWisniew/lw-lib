LIB_NAME=libmisc.a
FILES = Procedures
OBJECTS = $(FILES:%=%.o)

all: $(LIB_NAME)

$(OBJECTS) : %.o : %.cpp %.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(LIB_NAME): $(OBJECTS)
	ar sr $@ $(OBJECTS)

clean:
	rm -f *.o *.a
