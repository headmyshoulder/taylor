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

#ifndef MULTIPLIES_OPTIMIZED_NODE_HPP_
#define MULTIPLIES_OPTIMIZED_NODE_HPP_

#include <boost/array.hpp>
#include <boost/numeric/odeint/stepper/taylor/binary_node.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {
namespace tree_nodes_v1 {


template< class Left , class Right , class Value = double , size_t MaxIntermediates = 100 >
struct multiplies_optimized_node : binary_node< Left , Right , Value >
{
	multiplies_optimized_node( const Left &left , const Right &right )
	: binary_node< Left , Right , Value >( left , right ) , m_left_intermediates() , m_right_intermediates()  { }

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

	boost::array< Value , MaxIntermediates > m_left_intermediates;
	boost::array< Value , MaxIntermediates > m_right_intermediates;
};

template< class Value , class Left , class Right >
multiplies_optimized_node< Left , Right , Value > make_multiplies_optimized_node( const Left &left , const Right &right )
{
	return multiplies_optimized_node< Left , Right , Value >( left , right );
}

} // namespace tree_nodes_v1

template< class Left , class Right , class Value >
void print_node( std::ostream &out , const tree_nodes_v1::multiplies_optimized_node< Left , Right , Value > &node , size_t indent = 0 )
{
	print_binary_node( out , node , "Mulitplies optimized" , indent );
}



} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* MULTIPLIES_OPTIMIZED_NODE_HPP_ */
