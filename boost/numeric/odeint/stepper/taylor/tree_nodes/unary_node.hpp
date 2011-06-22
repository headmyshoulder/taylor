/*
 * unary_node.hpp
 *
 *  Created on: Jun 16, 2011
 *      Author: karsten
 *
 *
 * Copyright Karsten Ahnert 2011.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#ifndef UNARY_NODE_HPP_
#define UNARY_NODE_HPP_

#include <ostream>
#include <string>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {



template< class Child , class Value = double >
struct unary_node
{
	unary_node( const Child &child )
	: m_child( child ) { }

	Child m_child;
};


template< class Child , class Value >
void print_unary_node( std::ostream &out , const unary_node< Child , Value > &node , const std::string name = "" , size_t indent = 0 )
{
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << name << " (\n";
	print_node( out , node.m_child , indent + 1 );
	out << "\n";
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << ")";
}



} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost



#endif /* UNARY_NODE_HPP_ */
