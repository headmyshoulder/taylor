/*
 * multiplies_node.hpp
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

#ifndef MULTIPLIES_NODE_HPP_
#define MULTIPLIES_NODE_HPP_

#include <boost/numeric/odeint/stepper/taylor/tree_nodes/binary_node.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {



template< class Left , class Right , class Value = double >
struct multiplies_node : binary_node< Left , Right , Value >
{
	multiplies_node( Left left , Right right )
	: binary_node< Left , Right , Value >( left , right , "Multiplies" ) { }

	template< class Derivs >
	Value operator()( const Derivs &derivs , size_t which )
	{
		Value result = Value( 0.0 );
		for( size_t i=0 ; i<=which ; ++i )
		{
			result += m_left( derivs , i ) * m_right( derivs , which - i );
		}
		return result;
	}

	template< class State , class Derivs >
	Value operator()( const State &x , const Derivs &derivs , size_t which )
	{
		Value result = Value( 0.0 );
		for( size_t i=0 ; i<=which ; ++i )
		{
			result += m_left( x , derivs , i ) * m_right( x , derivs , which - i );
		}
		return result;
	}

};

template< class Value , class Left , class Right >
multiplies_node< Left , Right , Value > make_multiplies_node( const Left &left , const Right &right )
{
	return multiplies_node< Left , Right , Value >( left , right );
}



} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* MULTIPLIES_NODE_HPP_ */
