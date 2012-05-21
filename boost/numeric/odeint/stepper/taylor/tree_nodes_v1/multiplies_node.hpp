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

#ifndef MULTIPLIES_NODE_HPP_
#define MULTIPLIES_NODE_HPP_

#include <boost/numeric/odeint/stepper/taylor/binary_node.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

#include <iostream>
#define tab "\t"
using namespace std;

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {
namespace tree_nodes_v1 {


template< class Left , class Right , class Value = double >
struct multiplies_node : binary_node< Left , Right , Value >
{
	multiplies_node( const Left &left , const Right &right )
	: binary_node< Left , Right , Value >( left , right ) { }

	template< class State , class Derivs >
	Value operator()( const State &x , const Derivs &derivs , size_t which )
	{
		cout << "org" << endl;
		Value result = Value( 0.0 );
		for( size_t i=0 ; i<=which ; ++i )
		{
			Value l = m_left( x , derivs , i );
			Value r = m_right( x , derivs , which - i );
			result += l * r;
			cout << tab << i << tab << result << tab << l << tab << r << endl;
//			result += m_left( x , derivs , i ) * m_right( x , derivs , which - i );
		}
		cout << endl;
		return result;
	}
};

template< class Value , class Left , class Right >
multiplies_node< Left , Right , Value > make_multiplies_node( const Left &left , const Right &right )
{
	return multiplies_node< Left , Right , Value >( left , right );
}

} // namespace tree_nodes_v1

template< class Left , class Right , class Value >
void print_node( std::ostream &out , const tree_nodes_v1::multiplies_node< Left , Right , Value > &node , size_t indent = 0 )
{
	print_binary_node( out , node , "Mulitplies" , indent );
}



} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* MULTIPLIES_NODE_HPP_ */
