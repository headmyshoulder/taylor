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



template< class Left , class Right , class Value = double >
struct plus_node : binary_node< Left , Right , Value >
{
	plus_node( Left left , Right right )
	: binary_node< Left , Right , Value >( left , right , "Plus" ) { }

	template< class Derivs >
	Value operator()( Derivs &derivs , size_t which ) const
	{
		return m_left( derivs , which ) + m_right( derivs , which );
	}
};

template< class Value , class Left , class Right >
plus_node< Left , Right , Value > make_plus_node( const Left &left , const Right &right )
{
	return plus_node< Left , Right , Value >( left , right );
}





} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* PLUS_NODE_HPP_ */
