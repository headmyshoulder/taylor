/*
 * variable_node.hpp
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

#ifndef VARIABLE_NODE_HPP_
#define VARIABLE_NODE_HPP_

#include <ostream>

namespace boost {
namespace numeric {
namespace odeint {


namespace tree_nodes {


template< class Value = double >
struct variable_node
{
	variable_node( size_t index )
	: m_index( index ) { }

	template< class Derivs >
	Value operator()( Derivs &derivs , size_t which ) const
	{
		return derivs[which][m_index];
	}

	size_t m_index;
};

template< class Value >
variable_node< Value > make_variable_node( size_t index )
{
	return variable_node< Value >( index );
}

template< class Value >
void print_node( std::ostream &out , const variable_node< Value > &node , size_t indent = 0 )
{
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << "Variable ( " << node.m_index << " )";
}



} // namespace tree_nodes



} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* VARIABLE_NODE_HPP_ */
