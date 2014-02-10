/*
 * ConnectedComponents.cpp
 *
 *  Created on: Dec 16, 2013
 *      Author: cls
 */

#include "ConnectedComponents.h"

#include <set>

namespace NetworKit {

ConnectedComponents::ConnectedComponents() {

}

ConnectedComponents::~ConnectedComponents() {

}

void ConnectedComponents::run(const Graph& G) {
	// calculate connected components by label propagation
	count z = G.numberOfNodes();
	this->component = std::vector<node>(z, none);

	G.parallelForNodes([&](node v){
		component[v] = v;
	});

	bool change = false;
	do {
		DEBUG("next iteration");
		change = false;
		G.balancedParallelForNodes([&](node u) {
			G.forNeighborsOf(u, [&](node v) {
				if (component[v] < component[u]) {
					component[u] = component[v];
					change = true;
				}
			});
			// minimum neighboring label assigned
		});
	} while (change);
}


std::vector<index> ConnectedComponents::getComponentData() {
	return this->component;
}

std::map<index, count> ConnectedComponents::getComponentSizes() {
	std::map<index, count> componentSize;
	for (node u = 0; u < component.size(); ++u) {
		if (component[u] != none) {
			componentSize[component[u]] += 1;
		}
	}
	return componentSize;
}


std::vector<node> ConnectedComponents::getComponent(index label) {
	std::vector<node> nodesOfComponent;
	for (node u = 0; u < component.size(); ++u) {
		if (this->component[u] == label) {
			nodesOfComponent.push_back(u);
		}
	}
	return nodesOfComponent;
}

count ConnectedComponents::numberOfComponents() {
	count nc = 0;
	std::set<index> componentLabels;
	for (index i = 0; i < component.size(); ++i) {
		index c = component[i];
		if ((componentLabels.find(c) == componentLabels.end()) && (c != none)) { // label not encountered yet
			componentLabels.insert(c);
			nc++;
		}
	}
	return nc;
}

count ConnectedComponents::componentOfNode(node u) {
	assert (component[u] != none);
	return component[u];
}

}

