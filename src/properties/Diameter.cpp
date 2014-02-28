/*
 * Diameter.cpp
 *
 *  Created on: 19.02.2014
 *      Author: cls
 */

#include "Diameter.h"
#include "Eccentricity.h"
#include "../graph/BFS.h"
#include "../graph/Dijkstra.h"

namespace NetworKit {


count Diameter::exactDiameter(const Graph& G) {
	using namespace std;

	count diameter = 0;

	if (! G.isMarkedAsWeighted()) {
		G.forNodes([&](node v) {
			BFS bfs;
			vector<count> distances = bfs.run(G, v);
			for (auto distance : distances) {
				if (diameter < distance) {
					diameter = distance;
				}
			}
		});
	} else {
//		throw std::runtime_error("TODO: exact diameter for weighted graphs");
		 G.forNodes([&](node v) {
		 	Dijkstra dijkstra;
		 	vector<edgeweight> distances = dijkstra.run(G, v);
		 	for (auto distance : distances) {
		 		if (diameter < distance) {
		 			diameter = distance;
		 		}
		 	}
		 });
	}

	if (diameter == std::numeric_limits<count>::max()) {
		throw std::runtime_error("Graph not connected - diameter is infinite");
	}
	return diameter;
}





std::pair<count, count> Diameter::estimatedDiameterRange(const Graph& G, double error) {


	/* BFS that calls f with the visited edges and returns the node with largest distance from u. */
	/* Note: the function Graph::breadthFirstEdgesFrom that should
	 do the same has not been implemented! */
	auto bfs_edges = [&] (const Graph& G, node u, std::function<void(node, node)> f) -> node {
		std::queue<node> q;
		std::vector<bool> visited(G.numberOfNodes(), false);
		q.push(u);
		visited[u] = true;

		node x = u;
		while (!q.empty()) {
			x = q.front(); q.pop();
			G.forNeighborsOf(x, [&] (node y) {
						if (!visited[y]) {
							f(x, y);
							visited[y] = true;
							q.push(y);
						}
					});
		}
		return x;
	};

	/* Diameter estimate: lowerBounds <= diam(G) <= upperBound. */
	count lowerBound = 0;
	count upperBound = std::numeric_limits <count>::max();
	const count n = G.numberOfNodes();

	/* Nodes sorted decreasingly by degree. */
	std::vector<node> high_deg(n);
	std::iota(begin(high_deg), end(high_deg), 0);
	std::sort(begin(high_deg), end(high_deg), [&] (node u, node v) {
		return G.degree(u) > G.degree(v);
	});

	/* Random node. */
	static const std::default_random_engine random;
	auto random_node = std::bind(std::uniform_int_distribution<node>(0, n - 1), random);

	/* While not converged: update estimate. */
	count niter = 0;
	while ((upperBound - lowerBound) >= error * lowerBound && niter < n) {
		count ecc;

		/* ecc(u) <= diam(G) */
		node u = random_node();
		std::tie(std::ignore, ecc) = Eccentricity::getValue(G, u);
		lowerBound = std::max(lowerBound, ecc);

		/* diam(G) <= diam(BFS_Tree(v)) */
		node v = high_deg[niter];
		Graph bfs_tree(n);
		node w = bfs_edges(G, v, [&] (node a, node b) {
			bfs_tree.addEdge(a, b);
		});
		/* diam(T) = ecc_T(w) by problem 4. */
		std::tie(std::ignore, ecc) = Eccentricity::getValue(bfs_tree, w);
		upperBound = std::min(upperBound, ecc);

		niter++;
	}

	if ((lowerBound == std::numeric_limits<count>::max()) || (upperBound == std::numeric_limits<count>::max())) {
		throw std::runtime_error("Graph not connected - diameter is infinite");
	}

	return {lowerBound, upperBound};
}

} /* namespace NetworKit */
