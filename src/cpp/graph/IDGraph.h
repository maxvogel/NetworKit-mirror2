/*
 * IDGraph.h
 *
 *  Created on: 10.05.2014
 *      Author: Klara Reichard (klara.reichard@gmail.com), Marvin Ritter (marvin.ritter@gmail.com)
 */

#ifndef IDGRAPH_H
#define IDGRAPH_H

#include <limits>
#include <string>
#include <algorithm>

#include "IGraph.h"
#include "../Globals.h"
#include "../viz/Point.h"

namespace NetworKit {

/**
 * Interface for all directed graph classes. Every graph class has to implement all interface methods.
 */
class IDGraph : public virtual IGraph {

public:

	

	// TODO: structure for Edge (start, end, weight)?


	/** NODE PROPERTIES **/

	/**
	 * @return true if the node is isolated (= degree is 0)
	 */
	bool isIsolated(node v) const { return degreeIn(v) == 0 && degreeOut(v) == 0; }

	/**
	 * Return the number of neighbors for node v. For a Directed Graph return the number of outgoing neighbors for node v.
	 */
	virtual count degree(node v) const { return degreeOut(v); }

	/**
	 * Return the number of incoming edges to node v.
	 */
	virtual count degreeIn(node v) const = 0;

	/**
	 * Return the number of outgoing edges from node v.
	 */
	virtual count degreeOut(node v) const = 0;

	/**
	 * @return In-Volume of the node, which is the sum of all incoming edges.
	 */
	// virtual edgeweight volume(node v) const;


	/** NEIGHBORHOOD ITERATORS **/

	/**
	 * Iterate over all neighbors of a node and call handler (lamdba closure).
	 */
	template<typename L> void forNeighborsOf(node u, L handle) const { forOutNeighborsOf(u, handle); }

	/**
	 * Iterate over all adjacent nodes, which have an edge from u.
	 */
	template<typename L> void forOutNeighborsOf(node u, L handle) const;

	/**
	 * Iterate over all adjacent nodes, which have an edge to u.
	 */
	template<typename L> void forInNeighborsOf(node u, L handle) const;

	/**
	 * Iterate over all edge weights of a node and call handler (lamdba closure).
	 */
	template<typename L> void forWeightedNeighborsOf(node u, L handle) const { forWeightedOutNeighborsOf(u, handle); }

	/**
	 * Iterate over all outgoing edge weights of a node and call handler (lamdba closure).
	 */
	template<typename L> void forWeightedOutNeighborsOf(node u, L handle) const;
	
	/**
	 * Iterate over all incoming edge weights of a node and call handler (lamdba closure).
	 */
	template<typename L> void forWeightedInNeighborsOf(node u, L handle) const;

	/**
	 * Iterate over all incident edges of a node and call handler (lamdba closure).
	 */
	template<typename L> void forEdgesOf(node u, L handle) const { forOutEdgesOf(u, handle); }

	/**
	 * Iterate over all outgoing edges of the graph and call handler (lambda closure).
	 */
	template<typename L> void forOutEdgesOf(node u, L handle) const;
	
	/**
	 * Iterate over all incoming edges of the graph and call handler (lambda closure).
	 */
	template<typename L> void forInEdgesOf(node u, L handle) const;

	/**
	 * Iterate over all incident edges of a node and call handler (lamdba closure).
	 *
	 * Handle takes parameters (u, v, w) where w is the edge weight.
	 *
	 */
	template<typename L> void forWeightedEdgesOf(node u, L handle) const { forWeightedOutEdgesOf(u, handle); }
	
	/**
	 * Iterate over all incident edges from u and call handler (lamdba closure).
	 *
	 * Handle takes parameters (u, v, w) where w is the edge weight.
	 *
	 */
	template<typename L> void forWeightedOutEdgesOf(node u, L handle) const;

	/**
	 * Iterate over all incident edges from u and call handler (lamdba closure).
	 *
	 * Handle takes parameters (u, v, w) where w is the edge weight.
	 *
	 */
	template<typename L> void forWeightedInEdgesOf(node u, L handle) const;

};

} /* namespace NetworKit */

#endif /* IDGRAPH_H */