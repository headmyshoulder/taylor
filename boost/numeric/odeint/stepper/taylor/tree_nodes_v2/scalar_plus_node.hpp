/*
 * scalar_plus_node.hpp
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

#ifndef SCALAR_PLUS_NODE_HPP_
#define SCALAR_PLUS_NODE_HPP_

#include <boost/numeric/odeint/stepper/taylor/unary_node.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {
namespace tree_nodes_v2 {


template< typename Child , typename Value = double >
struct scalar_plus_node : unary_node< Child , Value >
{
	scalar_plus_node( const Child &child , const Value &summand )
	: unary_node< Child , Value >( child , "Scalar plus" ) , m_summand( summand ) { }

	template< typename State , typename Derivs , typename Which >
	Value operator()( const State &x , const Derivs &derivs , Which )
	{
		return ( Which::value == 0 ) ? m_summand + m_child( x , derivs , Which() ) : m_child( x , derivs , Which() ) ;
	}

	Value m_summand;
};

template< typename Value , typename Child >
scalar_plus_node< Child , Value > make_scalar_plus_node( const Child &child , Value summand  )
{
	return scalar_plus_node< Child , Value >( child , summand );
}

} // namespace tree_nodes_v2

template< typename Child , typename Value >
void print_node( std::ostream &out , const tree_nodes_v2::scalar_plus_node< Child , Value > &node , size_t indent = 0 )
{
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << "Scalar plus" << " ( " << node.m_summand << " ,\n";
	print_node( out , node.m_child , indent + 1 );
	out << "\n";
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << ")";
}








} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* SCALAR_PLUS_NODE_HPP_ */
