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
#include <boost/numeric/odeint/stepper/taylor/placeholders.hpp>

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

const double a = 18.0;
const double b = 33.0;
const double m0 = 0.2;
const double m1 = 0.01;

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

	state_type x = {{ 1.0 , 1.0 , 1.0 }} ;

	double t = 0.0;
	double dt = 1.0;



//	ofstream fout( "chua.dat" );
	size_t count = 0;
	while( t < 100000.0 )
	{
		stepper.do_step(
				fusion::make_vector
				(
						a * ( m0 * arg1 - 1.0 / 3.0 * m1 * arg1 * arg1 * arg1 + arg2 ) ,
						arg1 - arg2 + arg3 ,
						-b * arg2
				) ,
				x , t , dt );

//		fout << t << "\t" << x << "\t" << dt << endl;
		++count;
	}
	clog << count << endl;

	return 0;
}


/*
chua clean:

t < 100000.0

real    0m10.141s
user    0m10.134s
sys     0m0.003s
 */


