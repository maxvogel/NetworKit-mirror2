/*
 * BottomUpBFS.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: cls
 */

#include <queue>
#include "BottomUpBFS.h"

namespace NetworKit {

BottomUpBFS::BottomUpBFS(const Graph& G, node source, bool storePaths, bool storeStack) : SSSP(G, source, storePaths, storeStack) {
}


void BottomUpBFS::run(node t) {
	edgeweight infDist = std::numeric_limits<edgeweight>::max();
	count z = G.upperNodeIdBound();
	distances.clear();
	distances.resize(z, infDist);

	std::vector<bool> frontier;	// reverses the direction of the search
	frontier.resize(z, false);

// 	if (storePaths) {
// 		previous.clear();
// 		previous.resize(z);
// 		npaths.clear();
// 		npaths.resize(z, 0);
// 		npaths[source] = 1;
// 	}
//
// 	if (storeStack) {
// 		std::stack<node> empty;
// 		std::swap(stack, empty);
// 	}
//
// 	std::queue<node> q;
// 	q.push(source);
// 	visited[source] = true;
// 	distances[source] = 0;
// 	bool breakWhenFound = (t != none);
// 	while (! q.empty()) {
// 		node u = q.front();
// 		q.pop();
//
// 		if (storeStack) {
// 			stack.push(u);
// 		}
// 		if (breakWhenFound && t == u) {
// 			break;
// 		}
//
// 		// TRACE("current node in BFS: " , u);
// //		TRACE(distances);
//
// 		// insert untouched neighbors into queue
// 		G.forNeighborsOf(u, [&](node v) {
// 			// TRACE("scanning neighbor ", v);
//
// 			if (!visited[v]) {
// 				q.push(v);
// 				visited[v] = true;
// 				distances[v] = distances[u] + 1;
// 				if (storePaths) {
// 					previous[v] = {u};
// 					npaths[v] = npaths[u];
// 				}
// 			} else if (storePaths && (distances[v] == distances[u] + 1)) {
// 				previous[v].push_back(u); 	// additional predecessor
// 				npaths[v] += npaths[u]; 	// all the shortest paths to u are also shortest paths to v now
// 			}
// 		});
// 	}
}

} /* namespace NetworKit */
