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

#include <boost/numeric/odeint/stepper/taylor/binary_node.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {
namespace tree_nodes_v2 {



template< typename Left , typename Right , typename Value = double >
struct minus_node : public binary_node< Left , Right , Value >
{
	minus_node( const Left &left , const Right &right )
	: binary_node< Left , Right , Value >( left , right ) { }

	template< typename State , typename Derivs , typename Which >
	Value operator()( const State &x , const Derivs &derivs , Which )
	{
		return m_left( x , derivs , Which() ) - m_right( x , derivs , Which() );
	}
};

template< typename Value , typename Left , typename Right >
minus_node< Left , Right , Value > make_minus_node( const Left &left , const Right &right )
{
	return minus_node< Left , Right , Value >( left , right );
}

} // namespace tree_nodes_v2


template< typename Left , typename Right , typename Value >
void print_node( std::ostream &out , const tree_nodes_v2::minus_node< Left , Right , Value > &node , size_t indent = 0 )
{
	print_binary_node( out , node , "Minus" , indent );
}



} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* MINUS_NODE_HPP_ */
