.PHONY: all

CXX = g++
CXXFLAGS += -Wall -Wextra -std=c++17 -g

OBJDIR = ../obj
SRC_DIR = ..

TEST_UNITS = list
list_OBJ = 

all: test

test: $(TEST_UNITS)

.SECONDEXPANSION:
$(TEST_UNITS):  $$@.o $$(patsubst %, $(OBJDIR)/%, $$($$@_OBJ)) 
	$(CXX) $^ -o $@.test $(LDFLAGS)
	@echo "[$@] Test start"
	@./$@.test
	@echo "[$@] Test success"

$(OBJDIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(OBJDIR)/%.d: $(SRC_DIR)/%.cpp
	$(CXX) -MM $(CXXFLAGS) -o $@ $<
%.d: %.cpp
	$(CXX) -MM $(CXXFLAGS) -o $@ $<

include $(patsubst %.o, $(OBJDIR)/%.d, $(OBJ))
include $(patsubst %, %.d, $(TEST_UNITS))

clean:
	rm -rf $(TEST_UNITS) *.d *.o
