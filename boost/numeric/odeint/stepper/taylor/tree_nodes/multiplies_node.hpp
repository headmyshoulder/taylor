/*
 * multiplies_node.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: karsten
 */

#ifndef MULTIPLIES_NODE_HPP_
#define MULTIPLIES_NODE_HPP_

#include <ostream>

namespace boost {
namespace numeric {
namespace odeint {


namespace tree_nodes {

template< class Left , class Right , class Value = double >
struct multiplies_node
{
	multiplies_node( Left left , Right right )
	: m_left( left ) , m_right( right ) { }

	template< class Derivs >
	Value operator()( Derivs &derivs , size_t which )
	{
		Value result = Value( 0.0 );
		for( size_t i=0 ; i<=which ; ++i )
		{
			result += m_left( derivs , i ) * m_right( derivs , which - i );
		}
		return result;
	}

	Left m_left;
	Right m_right;
};

template< class Value , class Left , class Right >
multiplies_node< Left , Right , Value > make_multiplies_node( const Left &left , const Right &right )
{
	return multiplies_node< Left , Right , Value >( left , right );
}

template< class Left , class Right , class Value >
void print_node( std::ostream &out , const multiplies_node< Left , Right , Value > &node , size_t indent = 0 )
{
	for( size_t i=0 ; i<indent ; ++i ) out << "  ";
	out << "Multiplies (\n";
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


#endif /* MULTIPLIES_NODE_HPP_ */
