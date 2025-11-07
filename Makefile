CXX = g++
CXXFLAGS = -std=c++17

all:
	$(CXX) $(CXXFLAGS) -o src/output/main.exe src/main.cpp src/person.cpp src/RBTree/tree.cpp src/RBTree/node.cpp src/RBTree/rbforest.cpp src/RBTree/children_trees/bdtree.cpp src/RBTree/children_trees/idtree.cpp src/RBTree/children_trees/fntree.cpp src/RBTree/children_trees/lntree.cpp src/RBTree/children_trees/oritree.cpp src/RBTree/children_trees/destree.cpp src/BTree/btree.cpp src/BTree/bnode.cpp src/BTree/bforest.cpp src/BTree/children_trees/bdtree.cpp src/BTree/children_trees/idtree.cpp src/BTree/children_trees/fntree.cpp src/BTree/children_trees/lntree.cpp src/BTree/children_trees/oritree.cpp src/BTree/children_trees/destree.cpp