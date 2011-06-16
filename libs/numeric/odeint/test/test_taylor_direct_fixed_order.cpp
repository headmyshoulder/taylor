/*
 * test_taylor_direct_fixed_order.cpp
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

#include <boost/numeric/odeint/stepper/taylor_direct_fixed_order.hpp>
#include <boost/numeric/odeint/stepper/taylor/arguments.hpp>

#include <boost/fusion/include/make_vector.hpp>

template< typename T , size_t N >
std::ostream& operator<<( std::ostream& out , const boost::array< T , N > &x )
{
	if( !x.empty() ) out << x[0];
	for( size_t i=1 ; i<x.size() ; ++i ) out << "\t" << x[i];
	return out;
}

typedef boost::numeric::odeint::taylor_direct_fixed_order< 25 , 3 > taylor_type;
typedef taylor_type::state_type state_type;
typedef taylor_type::derivs_type derivs_type;

const double sigma = 10.0;
const double R = 28.0;
const double b = 8.0 / 3.0;




namespace fusion = boost::fusion;

using namespace std;
using namespace boost::numeric::odeint;

using boost::numeric::odeint::arg1;
using boost::numeric::odeint::arg2;
using boost::numeric::odeint::arg3;

int main( int argc , char **argv )
{
	cout.precision( 14 );

	taylor_type stepper;

	state_type x = {{ 10.0 , 10.0 , 10.0 }} ;

	double t = 0.0;
	double dt = 1.0;

	stepper.try_step(
			fusion::make_vector
			(
					sigma * ( arg2 - arg1 ) ,
					R * arg1 - arg2 - arg1 * arg3 ,
					arg1 * arg2 - b * arg3
			) ,
			x , t , dt );


//	ofstream fout( "lorenz.dat" );
//	size_t count = 0;
//	while( t < 5000.0 )
//	{
//		stepper.try_step(
//				fusion::make_vector
//				(
//						sigma * ( arg2 - arg1 ) ,
//						R * arg1 - arg2 - arg1 * arg3 ,
//						arg1 * arg2 - b * arg3
//				) ,
//				x , t , dt );
//
//		fout << t << "\t" << x << "\t" << dt << endl;
//		++count;
//	}
//	clog << count << endl;

	return 0;
}
