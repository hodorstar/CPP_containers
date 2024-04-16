# Copyright 2023 valeryje sallieam tcinthia hodorsta
#
# This file contains Original Code created by Alexander Alexanyan aka valeryje,
# Ksenia Alonceva aka hodorsta, Saveliy Karpushkin aka sallieam and Roman Nabiev
# aka tcinthia.
#
# The Original Code and all software developed in the process of participation
# on learning by experimental programming educational method. The whole
# methodology was developed and distributed by autonomous non-profit
# organization «School 21» (ANO «School 21»).
#
# Redistribution and use of this file, its parts, or entire project are
# permitted by confirmation of its original creator.

# ==============================================================================

# ----- VARIABLES AND PARAMETERS ----- #
CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17

TEST_FLAGS = -lgtest -lgtest_main -pthread
#TEST_FILES =	vector\
#							map\
#							set\
#							list\
#							stack\
#							queue\
#							array\
#							multiset
#GCOV_FLAGS = --exclude-unreachable-branches --exclude-noncode-lines --exclude-branches-by-pattern '.*throw std::out_of_range.*'
#--exclude-unreachable-branches - уменьшает количество бранчей на проверке

# ----- TASK GOALS ----- #

all: test 

clean:
	@clear
	@sleep 0.2
	@echo "Turning Cleaning Manager Mode on.."
	@-rm -rf binaries report
	@sleep 0.6
	@echo "Cleaning is complete"
	@sleep 0.2
	@echo "================================================================================"

test: clean
	@echo "Starting testing program.."
	@mkdir binaries 
	@-$(CXX) $(CXXFLAGS) $(TEST_FLAGS) tests/test_tree.cc -o binaries/tree.out
	@-./binaries/tree.out
	@-$(CXX) $(CXXFLAGS) $(TEST_FLAGS) tests/test_vector.cc -o binaries/vector.out
	@-./binaries/vector.out
	@-$(CXX) $(CXXFLAGS) $(TEST_FLAGS) tests/test_map.cc -o binaries/map.out
	@-./binaries/map.out
	@-$(CXX) $(CXXFLAGS) $(TEST_FLAGS) tests/test_set.cc -o binaries/set.out
	@-./binaries/set.out
	@-$(CXX) $(CXXFLAGS) $(TEST_FLAGS) tests/test_list.cc -o binaries/list.out
	@-./binaries/list.out
	@-$(CXX) $(CXXFLAGS) $(TEST_FLAGS) tests/test_stack.cc -o binaries/stack.out
	@-./binaries/stack.out
	@-$(CXX) $(CXXFLAGS) $(TEST_FLAGS) tests/test_queue.cc -o binaries/queue.out
	@-./binaries/queue.out
	@-$(CXX) $(CXXFLAGS) $(TEST_FLAGS) tests/test_array.cc -o binaries/array.out
	@-./binaries/array.out
	@-$(CXX) $(CXXFLAGS) $(TEST_FLAGS) tests/test_multiset.cc -o binaries/multiset.out
	@-./binaries/multiset.out
	@echo "================================================================================"
	
# ----- REVIEW GOALS ----- #
style:
	@sleep 0.2
	@echo "Copying .clang-format.."
	@-cp ../materials/linters/.clang-format .
	@sleep 0.5
	@echo "Applying Google Style.."
	@-clang-format -i -style=file */*.cc */*.h 
	@sleep 0.3
	@echo "Behold your pretty code, hooman"
	@-clang-format -n -style=file */*.cc */*.h 
	@-rm .clang-format
	@echo "================================================================================"

gcov_report: clean
# @for test_files in $(TEST_FILES);	do
# 	$(CXX) $(CXXFLAGS) --coverage $(TEST_FLAGS) test_$$test_files -o test_$$test_files.out
# 	./binariestest_$$test_files.out
# 	sleep 5
# @done
	@-mkdir binaries 
	@-$(CXX) $(CXXFLAGS) --coverage $(TEST_FLAGS) tests/test_tree.cc -o binaries/tree.out
	@-./binaries/tree.out
	@-$(CXX) $(CXXFLAGS) --coverage $(TEST_FLAGS) tests/test_vector.cc -o binaries/vector.out
	@-./binaries/vector.out
	@-$(CXX) $(CXXFLAGS) --coverage $(TEST_FLAGS) tests/test_map.cc -o binaries/map.out
	@-./binaries/map.out
	@-$(CXX) $(CXXFLAGS) --coverage $(TEST_FLAGS) tests/test_set.cc -o binaries/set.out
	@-./binaries/set.out
	@-$(CXX) $(CXXFLAGS) --coverage $(TEST_FLAGS) tests/test_list.cc -o binaries/list.out
	@-./binaries/list.out
	@-$(CXX) $(CXXFLAGS) --coverage $(TEST_FLAGS) tests/test_stack.cc -o binaries/stack.out
	@-./binaries/stack.out
	@-$(CXX) $(CXXFLAGS) --coverage $(TEST_FLAGS) tests/test_queue.cc -o binaries/queue.out
	@-./binaries/queue.out
	@-$(CXX) $(CXXFLAGS) --coverage $(TEST_FLAGS) tests/test_array.cc -o binaries/array.out
	@-./binaries/array.out
	@-$(CXX) $(CXXFLAGS) --coverage $(TEST_FLAGS) tests/test_multiset.cc -o binaries/multiset.out
	@-./binaries/multiset.out
	@-mkdir -p report
	@-gcovr . --exclude-unreachable-branches --html --html-details --html-details-syntax-highlighting -o report/report.html
	@-rm -rf test.info *.gc*
	@sleep 1
	@echo
	@echo "Opening coverage report.."
	@-open report/report.html
	@echo "================================================================================"

leaks:
	@echo "Checking your leaks with LEAKS utility.."
	@sleep 1
	#@-leaks -atExit -- ./binaries/tree.out
	#@-leaks -atExit -- ./binaries/vector.out
	#@-leaks -atExit -- ./binaries/map.out
	#@-leaks -atExit -- ./binaries/set.out
	#@-leaks -atExit -- ./binaries/list.out
	#@-leaks -atExit -- ./binaries/stack.out
	#@-leaks -atExit -- ./binaries/queue.out
	#@-leaks -atExit -- ./binaries/array.out
	#@-leaks -atExit -- ./binaries/multiset.out
	@sleep 1
	@echo "================================================================================"

# ----- SUPPORT GOALS ----- #
review: style gcov_report leaks
