#include "list.h"
#include "tree.h"
#include "graph.h"

#include <string>


int main() {

	graph<string> g;
	graph_node<string> node0(1, "Saucisse");
	graph_node<string> node1(2, "Knack");
	graph_node<string> node2(3, "Boudin");

	g.addNode(&node0);
	g.addNode(&node1);

	g.printBows();

	g.addBow(1, 2);

	g.printBows();

	g.addNode(&node2);

	g.addBow(3, 1);

	g.printBows();

	return 0;
}