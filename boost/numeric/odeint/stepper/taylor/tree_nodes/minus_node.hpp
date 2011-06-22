/*
 * minus_node.hpp
 *
 *  Created on: Jun 17, 2011
 *      Author: karsten
 *
 *
 * Copyright Karsten Ahnert 2011.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MINUS_NODE_HPP_
#define MINUS_NODE_HPP_

#include <boost/numeric/odeint/stepper/taylor/tree_nodes/binary_node.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {



template< class Left , class Right , class Value = double >
struct minus_node : public binary_node< Left , Right , Value >
{
	minus_node( const Left &left , const Right &right )
	: binary_node< Left , Right , Value >( left , right ) { }

	template< class Derivs >
	Value operator()( const Derivs &derivs , size_t which )
	{
		return m_left( derivs , which ) - m_right( derivs , which );
	}

	template< class State , class Derivs >
	Value operator()( const State &x , const Derivs &derivs , size_t which )
	{
		return m_left( x , derivs , which ) - m_right( x , derivs , which );
	}
};

template< class Value , class Left , class Right >
minus_node< Left , Right , Value > make_minus_node( const Left &left , const Right &right )
{
	return minus_node< Left , Right , Value >( left , right );
}

template< class Left , class Right , class Value >
void print_node( std::ostream &out , const minus_node< Left , Right , Value > &node , size_t indent = 0 )
{
	print_binary_node( out , node , "Minus" , indent );
}



} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* MINUS_NODE_HPP_ */
