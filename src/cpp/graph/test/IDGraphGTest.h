/*
 * IDGraphGTest.h
 *
 *  Created on: 10.05.2014
 *      Author: Klara Reichard (klara.reichard@gmail.com), Marvin Ritter (marvin.ritter@gmail.com)
 */

#ifndef NOGTEST

#ifndef IDGRAPHGTEST_H_
#define IDGRAPHGTEST_H_

#include <gtest/gtest.h>

#include "../IDGraph.h"

namespace NetworKit {

template <typename T>
class IDGraphGTest : public testing::Test {
public:
	IDGraphGTest();
	virtual ~IDGraphGTest();
};

} /* namespace NetworKit */

#endif /* IDGRAPHGTEST_H_ */

#endif /*NOGTEST */
