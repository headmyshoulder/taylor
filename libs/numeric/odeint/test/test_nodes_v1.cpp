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

#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v1/constant_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v1/variable_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v1/plus_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v1/multiplies_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v1/sin_node.hpp>

#include "evaluate.hpp"

using namespace std;
using namespace std::tr1;
using namespace boost::numeric::odeint::taylor_detail::tree_nodes_v1;



int main( int argc , char **argv )
{
	evaluate_v1(
		make_plus_node< double >( make_constant_node< double >( 1.0 ) , make_variable_node< 1 , double >() ) ,
		make_sin< double >( make_multiplies_node< double >( make_variable_node< 0 , double >() , make_variable_node< 1 , double >() ) )
	);

	return 0;
}
