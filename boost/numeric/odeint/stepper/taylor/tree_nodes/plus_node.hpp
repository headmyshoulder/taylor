/*
 * plus_node.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: karsten
 */

#ifndef PLUS_NODE_HPP_
#define PLUS_NODE_HPP_

#include <ostream>

namespace boost {
namespace numeric {
namespace odeint {


namespace tree_nodes {

template< class Left , class Right , class Value = double >
struct plus_node
{
	plus_node( Left left , Right right )
	: m_left( left ) , m_right( right ) { }

	template< class Derivs >
	Value operator()( Derivs &derivs , size_t which ) const
	{
		return m_left( derivs , which ) + m_right( derivs , which );
	}

	Left m_left;
	Right m_right;
};

template< class Value , class Left , class Right >
plus_node< Left , Right , Value > make_plus_node( const Left &left , const Right &right )
{
	return plus_node< Left , Right , Value >( left , right );
}


template< class Left , class Right , class Value >
void print_node( std::ostream &out , const plus_node< Left , Right , Value > &node , size_t indent = 0 )
{
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << "Plus (\n";
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


#endif /* PLUS_NODE_HPP_ */
