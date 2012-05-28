/*
 * test_simple_system.cpp
 *
 *  Created on: Jun 16, 2011
 *      Author: karsten
 *
 *
 * Copyright Karsten Ahnert 2011.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <iostream>
#include <fstream>

#include <boost/numeric/odeint/stepper/taylor_proto.hpp>
#include <boost/numeric/odeint/stepper/taylor_direct_fixed_order.hpp>
#include <boost/numeric/odeint/stepper/taylor/placeholders.hpp>

#include <boost/fusion/include/make_vector.hpp>

template< typename T , size_t N >
std::ostream& operator<<( std::ostream& out , const boost::array< T , N > &x )
{
	if( !x.empty() ) out << x[0];
	for( size_t i=1 ; i<x.size() ; ++i ) out << "\t" << x[i];
	return out;
}

typedef boost::numeric::odeint::taylor_proto< 4 , 1 > taylor_type;
typedef boost::numeric::odeint::taylor_direct_fixed_order< 4 , 1 > taylor2_type;
typedef taylor_type::state_type state_type;
typedef taylor_type::derivs_type derivs_type;

namespace fusion = boost::fusion;

using namespace std;
using namespace boost::numeric::odeint;

using boost::numeric::odeint::arg1;
using boost::numeric::odeint::arg2;
using boost::numeric::odeint::arg3;

int main( int argc , char **argv )
{
	cout.precision( 14 );

	taylor_type stepper1;
	taylor2_type stepper2;

	state_type x1 = {{ 1.0 }} , x2 = {{ 1.0 }};

	double t = 0.0;
	double dt = 1.0;



	stepper1.do_step(
			fusion::make_vector( arg1 * arg1 * arg1 + 1.0 ) ,
			x1 , t , dt );
	clog << x1 << endl;

	stepper2.do_step(
				fusion::make_vector( arg1 * arg1 * arg1 + 1.0 ) ,
				x2 , t , dt );
	clog << x2 << endl;

	return 0;
}
