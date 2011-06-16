/*
 * binary_node.hpp
 *
 *  Created on: Jun 16, 2011
 *      Author: karsten
 *
 *
 * Copyright Karsten Ahnert 2011.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BINARY_NODE_HPP_
#define BINARY_NODE_HPP_

#include <ostream>
#include <string>

namespace boost {
namespace numeric {
namespace odeint {


namespace tree_nodes {

template< class Left , class Right , class Value = double >
struct binary_node
{
	binary_node( Left left , Right right , const std::string &name = std::string( "" ) )
	: m_left( left ) , m_right( right ) , m_name( name ) { }

	Left m_left;
	Right m_right;
	const std::string m_name;
};


template< class Left , class Right , class Value >
void print_node( std::ostream &out , const binary_node< Left , Right , Value > &node , size_t indent = 0 )
{
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << node.m_name << " (\n";
	print_node( out , node.m_left , indent + 1 );
	out << " ,\n";
	print_node( out , node.m_right , indent + 1 );
	out << "\n";
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << ")";
}



} // namespace tree_nodes



} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* BINARY_NODE_HPP_ */
