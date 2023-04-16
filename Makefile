a.out: AVLTree.o AVLNode.o AVLPathTest.o
	clang++ AVLTree.o AVLNode.o AVLPathTest.o -o a.out

AVLTree.o: AVLTree.h AVLTree.cpp
	clang++ -c -Wall -O2 AVLTree.cpp

AVLNode.o: AVLNode.h AVLNode.cpp
	clang++ -c -Wall -O2 AVLNode.cpp

AVLPathTest.o: AVLPathTest.cpp
	clang++ -c -Wall -O2 AVLPathTest.cpp

clean:
		rm *.o a.out