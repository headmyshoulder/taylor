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

#include <boost/numeric/odeint/stepper/taylor/tree_nodes/binary_node.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {



template< class Left , class Right , class Value = double >
struct multiplies_node : binary_node< Left , Right , Value >
{
    template< class S , class D , class MaxOrder >
    struct adder
    {
        Value &m_result;
        Left &m_left;
        Right &m_right;
        const S &m_x;
        const D &m_derivs;


        adder( Value &result , Left &left , Right &right , const S &x , const D &derivs )
        : m_result( result ) , m_left( left ) , m_right( right ) , m_x( x ) , m_derivs( derivs ) { }

        template< class Which >
        void operator()( Which )
        {
            typedef typename mpl::minus< MaxOrder , Which >::type which2;
            m_result += m_left( m_x , m_derivs , Which() ) * m_right( m_x , m_derivs , which2() );
        }
    };

    template< class S , class D , class MaxOrder >
    static adder< S , D , MaxOrder > make_adder( Value &result , Left &left , Right &right , const S &x , const D &derivs )
    {
        return adder< S , D , MaxOrder >( result , left , right , x , derivs );
    }


	multiplies_node( const Left &left , const Right &right )
	: binary_node< Left , Right , Value >( left , right ) { }

	template< class Derivs >
	Value operator()( const Derivs &derivs , size_t which )
	{
		Value result = Value( 0.0 );
		for( size_t i=0 ; i<=which ; ++i )
		{
			result += m_left( derivs , i ) * m_right( derivs , which - i );
		}
		return result;
	}

	template< class State , class Derivs >
	Value operator()( const State &x , const Derivs &derivs , size_t which )
	{
		Value result = Value( 0.0 );
		for( size_t i=0 ; i<=which ; ++i )
		{
			result += m_left( x , derivs , i ) * m_right( x , derivs , which - i );
		}
		return result;
	}

	template< typename Which , class State , class Derivs >
	Value eval( const State &x , const Derivs &derivs )
	{
	    namespace mpl = boost::mpl;
	    Value result = Value( 0.0 );
	    static const size_t which = Which::value ;
	    mpl::for_each< mpl::range_c< size_t , 0 , which + 1 > >(
	            make_adder( result , this->m_left , this->m_right , x , derivs ) );
	    return result;
	}

};

template< class Value , class Left , class Right >
multiplies_node< Left , Right , Value > make_multiplies_node( const Left &left , const Right &right )
{
	return multiplies_node< Left , Right , Value >( left , right );
}

template< class Left , class Right , class Value >
void print_node( std::ostream &out , const multiplies_node< Left , Right , Value > &node , size_t indent = 0 )
{
	print_binary_node( out , node , "Mulitplies" , indent );
}



} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* MULTIPLIES_NODE_HPP_ */
