/*
 * scalar_multiplies_node.hpp
 *
 *  Created on: Jun 22, 2011
 *      Author: karsten
 *
 *
 * Copyright Karsten Ahnert 2011.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SCALAR_MULTIPLIES_NODE_HPP_
#define SCALAR_MULTIPLIES_NODE_HPP_

#include <boost/numeric/odeint/stepper/taylor/tree_nodes/unary_node.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {



template< class Child , class Value = double >
struct scalar_multiplies_node : unary_node< Child , Value >
{
	scalar_multiplies_node( Child child , Value factor )
	: unary_node< Child , Value >( child , "Scalar multiplies" ) , m_factor( factor ) { }

	template< class Derivs >
	Value operator()( const Derivs &derivs , size_t which )
	{
		return m_child( derivs , which ) * m_factor;
	}

	template< class State , class Derivs >
	Value operator()( const State &x , const Derivs &derivs , size_t which )
	{
		return m_child( x , derivs , which ) * m_factor;
	}

	Value m_factor;
};

template< class Value , class Child >
scalar_multiplies_node< Child , Value > make_scalar_multiplies_node( const Child &child , Value factor )
{
	return scalar_multiplies_node< Child , Value >( child , factor );
}

template< class Child , class Value >
void print_node( std::ostream &out , const scalar_multiplies_node< Child , Value > &node , size_t indent = 0 )
{
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << node.m_name << " ( " << node.m_factor << " ,\n";
	print_node( out , node.m_child , indent + 1 );
	out << "\n";
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << ")";
}




} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* SCALAR_MULTIPLIES_NODE_HPP_ */
