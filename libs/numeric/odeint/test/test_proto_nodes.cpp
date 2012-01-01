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

#include <boost/proto/proto.hpp>

#include <boost/numeric/odeint/stepper/taylor/tree_nodes/node_factory.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_generator/tree_generator.hpp>
#include <boost/numeric/odeint/stepper/taylor/placeholders.hpp>

#include "evaluate.hpp"

using namespace std;
using namespace std::tr1;
using namespace boost::numeric::odeint;
using namespace boost::numeric::odeint::taylor_detail;



template< class Eq1 , class Eq2 >
void evaluate_proto( const Eq1 &eq1 , const Eq2 &eq2 )
{
	boost::proto::display_expr( eq1 );
	boost::proto::display_expr( eq2 );
	evaluate( tree_generator< node_v1_factory >()( eq1 ) , tree_generator< node_v1_factory >()( eq2 ) );
}



int main( int argc , char **argv )
{
	evaluate(
		make_plus_node< double >( make_constant_node< double >( 1.0 ) , make_variable_node< 1 , double >( ) ) ,
		make_sin< double >( make_multiplies_node< double >( make_variable_node< 0 , double >() , make_variable_node< 1 , double >() ) )
	);


	cout << endl << endl;
	evaluate_proto( 1.0 + arg2 , 2.0 * sin( arg1 * arg2 ) );


	return 0;
}
