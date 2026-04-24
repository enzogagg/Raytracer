##
## EPITECH PROJECT, 2025
## Delivery
## File description:
## Makefile
##

## ------------------------------------ ##
##              VARIABLES               ##

CXX                 := g++

# OS Detection
UNAME_S := $(shell uname -s)

CXXFLAGS            := -Wall -Wextra -fPIC -std=c++20 -Wno-deprecated-declarations -Wno-return-type-c-linkage \
                       -I./include -I./include/core -I./include/images \
                       -I./include/interfaces -I./include/loader \
                       -I./include/plugins -I./include/plugins/lights \
                       -I./include/plugins/primitives \
                       -I./include/transformations -I./include/render \
                       -I./include/utilitaries -I./include/exceptions \
                       -I./include/materials

LDFLAGS             := -lconfig++ -ldl

ifeq ($(UNAME_S), Darwin)
    # macOS specific setup
    CXXFLAGS += -I/opt/homebrew/include
    LDFLAGS  += -L/opt/homebrew/lib
    PLUGIN_LDFLAGS := -shared -undefined dynamic_lookup
else
    # Linux specific setup
    LDFLAGS  += -rdynamic
    PLUGIN_LDFLAGS := -shared
endif

SFML_FLAGS          := -lsfml-graphics -lsfml-window -lsfml-system
DFLAGS              := -g3
TFLAGS				:= -lcriterion --coverage

EXECUTABLE          := raytracer
EXEC_ARGS			:= -help
TEST_EXECUTABLE     := unit_tests

OBJDIR              := obj
SRCDIR              := src
PLUGINSDIR          := src/plugins
PLUGINS_OUTDIR      := plugins
TESTDIR             := tests

SOURCES_FILES       := $(shell find $(SRCDIR) -name '*.cpp' ! \
						-path "$(PLUGINSDIR)/*")
OBJECTS_FILES       := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,\
						$(SOURCES_FILES))
PLUGIN_SOURCES      := $(shell find $(PLUGINSDIR) -name '*.cpp' )
PLUGIN_OBJECTS      := $(patsubst $(PLUGINSDIR)/%.cpp,$(PLUGINS_OUTDIR)/%.so,\
						$(PLUGIN_SOURCES))
TEST_SOURCES        := $(filter-out $(SRCDIR)/Main.cpp, $(SOURCES_FILES))
TEST_OBJECTS        := $(shell find $(TESTDIR) -name '*.cpp')

RESET               := \033[0m
GREEN               := \033[32m
BLUE                := \033[34m
CYAN                := \033[36m
RED                 := \033[31m

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CXXFLAGS += $(DFLAGS)
endif

## ------------------------------------ ##
##                RULES                 ##

all: $(EXECUTABLE) plugins
	@echo "$(GREEN)[✔] Compilation complete.$(RESET)"

$(EXECUTABLE): $(OBJECTS_FILES)
	@mkdir -p $(@D)
	@echo "$(CYAN)[➜] Linking$(RESET)"
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_FLAGS) $(LDFLAGS)
	@echo "$(GREEN)[✔] Executable created: $(EXECUTABLE)$(RESET)"

-include $(OBJECTS_FILES:.o=.d)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@echo "$(BLUE)[~] Compiling: $<$(RESET)"
	@$(CXX) $(CXXFLAGS) -MD -c $< -o $@

plugins: create_plugin_dirs $(PLUGIN_OBJECTS)
	@echo "$(GREEN)[✔] Plugins compiled and placed in \
	$(PLUGINS_OUTDIR).$(RESET)"

create_plugin_dirs:
	@mkdir -p $(PLUGINS_OUTDIR)
	@find $(PLUGINSDIR) -type d | sed "s|$(PLUGINSDIR)|$(PLUGINS_OUTDIR)|" \
	| xargs -I {} mkdir -p {}

$(PLUGINS_OUTDIR)/%.so: $(PLUGINSDIR)/%.cpp
	@echo "$(BLUE)[~] Compiling plugin: $<$(RESET)"
	@$(CXX) $(CXXFLAGS) $(PLUGIN_LDFLAGS) -o $@ $< $(LDFLAGS)
	@echo "$(GREEN)[✔] Plugin created: $@$(RESET)"

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(PLUGINS_OUTDIR)
	@rm -f $(TEST_EXECUTABLE)
	@rm -f *.gcno
	@rm -f *.gcda
	@rm -f vgcore.*
	@echo "$(RED)[✘] Objects, plugins, and coverage files removed.$(RESET)"

fclean: clean
	@rm -f $(EXECUTABLE) $(TEST_EXECUTABLE)
	@echo "$(RED)[✘] Executables removed.$(RESET)"

re: fclean
	@$(MAKE) all --no-print-directory

## ------------------------------------ ##
##              UNIT TESTS               ##

tests_run:
	@echo "$(CYAN)[➜] Linking tests$(RESET)"
	@$(CXX) $(CXXFLAGS) $(TEST_SOURCES) $(TEST_OBJECTS) \
	$(TFLAGS) -o $(TEST_EXECUTABLE) $(SFML_FLAGS) $(LDFLAGS)
	@echo "$(GREEN)[✔] Unit tests executable created: \
    $(TEST_EXECUTABLE)$(RESET)"
	@echo "$(CYAN)[➜] Running unit tests$(RESET)"
	@./$(TEST_EXECUTABLE)


coverage: tests_run
	@echo "$(CYAN)[➜] Generating code coverage report$(RESET)"
	@gcovr --exclude $(TESTDIR)

.PHONY: all clean fclean re tests_run coverage plugins create_plugin_dirs
