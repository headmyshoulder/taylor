/*
 * plus_node.hpp
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

#ifndef PLUS_NODE_HPP_
#define PLUS_NODE_HPP_

#include <boost/numeric/odeint/stepper/taylor/tree_nodes/binary_node.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {
namespace tree_nodes_v2 {


template< class Left , class Right , class Value = double >
struct plus_node : binary_node< Left , Right , Value >
{
	plus_node( const Left &left , const Right &right )
	: binary_node< Left , Right , Value >( left , right ) { }


	template< class State , class Derivs >
	Value operator()( const State &x , const Derivs &derivs , size_t which )
	{
		return m_left( x , derivs , which ) + m_right( x , derivs , which );
	}

};

template< class Value , class Left , class Right >
plus_node< Left , Right , Value > make_plus_node( const Left &left , const Right &right )
{
	return plus_node< Left , Right , Value >( left , right );
}

} // namespace tree_nodes_v2

template< class Left , class Right , class Value >
void print_node( std::ostream &out , const tree_nodes_v2::plus_node< Left , Right , Value > &node , size_t indent = 0 )
{
	print_binary_node( out , node , "Plus" , indent );
}





} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* PLUS_NODE_HPP_ */
