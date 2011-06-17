/*
 * test_nodes.cpp
 *
 *  Created on: Jun 9, 2011
 *      Author: karsten
 *
 *
 * Copyright Karsten Ahnert 2011.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <iostream>

#include <tr1/array>

#include <boost/numeric/odeint/stepper/taylor/tree_nodes/constant_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes/variable_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes/plus_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes/multiplies_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes/sin_node.hpp>

#include "evaluate.hpp"

using namespace std;
using namespace std::tr1;
using namespace boost::numeric::odeint::tree_nodes;



int main( int argc , char **argv )
{
	evaluate(
		make_plus_node< double >( make_constant_node< double >( 1.0 ) , make_variable_node< double >( 1 ) ) ,
		make_sin< double >( make_multiplies_node< double >( make_variable_node< double >( 0 ) , make_variable_node< double >( 1 ) ) )
	);

	return 0;
}
