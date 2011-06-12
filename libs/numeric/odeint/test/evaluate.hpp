/*
 * evaluate.hpp
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

#ifndef EVALUATE_HPP_
#define EVALUATE_HPP_

#include <iostream>
#include <tr1/array>

#include <boost/numeric/odeint/stepper/taylor/print_tree.hpp>

template< class Eq1 , class Eq2 >
void evaluate( const Eq1 &_eq1 , const Eq2 &_eq2 )
{
	Eq1 eq1 = _eq1;
	Eq2 eq2 = _eq2;

	print_tree( std::cout , eq1 );
	std::cout << "\n\n";
	print_tree( std::cout , eq2 );

	typedef std::tr1::array< double , 2 > state_type;
	typedef std::tr1::array< state_type , 10 > deriv_type;

	deriv_type derivs;
	derivs[0][0] = 0.25;
	derivs[0][1] = 0.75;

	for( size_t i=1 ; i<10 ; ++i )
	{
		derivs[i][0] = 1.0 / double( i ) * eq1( derivs , i - 1 );
		derivs[i][1] = 1.0 / double( i ) * eq2( derivs , i - 1 );
	}

	for( size_t i=0 ; i<10 ; ++i )
	{
		std::cout << i << "\t" << derivs[i][0] << "\t" << derivs[i][1] << "\n";
	}
}


#endif /* EVALUATE_HPP_ */
