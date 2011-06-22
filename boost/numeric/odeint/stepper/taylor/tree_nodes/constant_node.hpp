/*
 * constant_node.hpp
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

#ifndef CONSTANT_NODE_HPP_
#define CONSTANT_NODE_HPP_

#include <ostream>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {



template< class Value = double >
struct constant_node
{
	constant_node( Value value )
	: m_value( value ) { }

	template< class Derivs >
	Value operator()( const Derivs &derivs , size_t which ) const
	{
		return ( which == 0 ) ? m_value : 0.0;
	}

	template< class State , class Derivs >
	Value operator()( const State &x , const Derivs &derivs , size_t which )
	{
		return ( which == 0 ) ? m_value : 0.0;
	}


	Value m_value;
};


template< class Value >
constant_node< Value > make_constant_node( const Value &value )
{
	return constant_node< Value >( value );
}

template< class Value >
void print_node( std::ostream &out , const constant_node< Value > &node , size_t indent = 0 )
{
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << "Constant ( " << node.m_value << " )";
}



} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* CONSTANT_NODE_HPP_ */
