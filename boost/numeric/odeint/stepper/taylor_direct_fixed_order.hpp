/*
 * taylor_direct_fixed_order.hpp
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

#ifndef TAYLOR_DIRECT_FIXED_ORDER_HPP_
#define TAYLOR_DIRECT_FIXED_ORDER_HPP_

#include <cmath>
#include <iostream>

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

// fusion includes
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/at.hpp>

// mpl includes
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

// proto includes
#include <boost/proto/proto.hpp>

#include <boost/numeric/odeint/stepper/taylor/eval_derivs_direct.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_generator/tree_generator.hpp>
#include <boost/numeric/odeint/stepper/taylor/print_tree.hpp>


namespace boost {
namespace numeric {
namespace odeint {

template< size_t Order , size_t Dim , typename Value = double >
class taylor_direct_fixed_order
{
public:

	const static size_t order_value = Order;
	const static size_t dim = Dim;
	typedef Value value_type;
	typedef value_type time_type;
	typedef boost::array< value_type , dim > state_type;
	typedef state_type deriv_type;
	typedef size_t order_type;

	typedef boost::array< state_type , order_value > derivs_type;

	taylor_direct_fixed_order( value_type rel_error = 1.0e-14 , value_type abs_error = 1.0e-14 )
	: m_derivs() , m_dt_fac( 1.0 ) , m_rel_error( rel_error ) , m_abs_error( abs_error ) { }


	order_type order( void ) const
    {
    	return order_value;
    }

    order_type stepper_order( void ) const
    {
    	return order_value;
    }

    order_type error_order( void ) const
    {
    	return order_value - 1;
    }



	template< class System >
	void do_step( System sys , state_type &x , time_type &t , time_type &dt )
	{
		BOOST_STATIC_ASSERT(( boost::fusion::traits::is_sequence< System >::value ));
		BOOST_STATIC_ASSERT(( size_t( boost::fusion::result_of::size< System >::value ) == dim ));

		do_step( sys , x , t , x , dt );
	}

	template< class System >
	void do_step( System sys , const state_type &in , time_type &t , state_type &out , time_type &dt )
	{
		namespace mpl = boost::mpl;
		namespace fusion = boost::fusion;
		namespace proto = boost::proto;
		using namespace taylor_detail;

		BOOST_STATIC_ASSERT(( boost::fusion::traits::is_sequence< System >::value ));
		BOOST_STATIC_ASSERT(( size_t( boost::fusion::result_of::size< System >::value ) == dim ));

		typedef typename fusion::result_of::transform< const System , tree_generator >::type transformed_type;
		typedef typename fusion::result_of::as_vector< transformed_type const >::type tree_type;
		tree_type trees = fusion::as_vector( fusion::transform( sys , tree_generator() ) );

//		fusion::for_each( trees , print_tree( std::cout , 0 ) );
//		fusion::for_each( sys , proto::functional::display_expr() );


		eval_derivs( trees , in , m_derivs , m_dt_fac );

		value_type max_error = 0.0;
		for( size_t i=0 ; i<dim ; ++i )
		{
			value_type error = std::abs( m_derivs[ order_value - 1 ][i] ) /
					( m_rel_error * std::abs( in[i] ) + m_abs_error );
			max_error = std::max( error , max_error );
		}

		dt = pow( 1.0 / max_error , 1.0 / value_type( order_value ) );

		for( size_t i=0 ; i<dim ; ++i )
		{
			value_type tmp = 0.0;
			for( size_t k=0 ; k<order_value ; ++k )
				tmp = dt * ( tmp + m_derivs[ order_value - 1 - k ][i] );
			out[i] = in[i] + tmp;
		}

		dt *= m_dt_fac;
		t += dt;
	}

	template< class System >
	void eval_derivs( System sys , const state_type &in , derivs_type &der , value_type &dt_fac ) const
	{
		namespace mpl = boost::mpl;
		namespace fusion = boost::fusion;
		namespace proto = boost::proto;
		using namespace taylor_detail;

		const value_type min_error = 1.0e-19;
		const value_type max_error = 1.0e19;
		const value_type min_fac = 1.5;
		const value_type max_fac = 0.6;

		for( size_t i=0 ; i<order_value ; ++i )
		{
			boost::mpl::for_each< boost::mpl::range_c< size_t , 0 , dim > >(
					make_eval_derivs( sys , in , der , dt_fac , i )
			);

			while( true )
			{
				double err = 0.0;
				for( size_t j=0 ; j<dim ; ++j ) err += std::abs( der[i][j] );

				if( err < min_error )
				{
					scale_derivs( der , i , min_fac );
					dt_fac *= min_fac;
					continue;
				}
				if( err > max_error )
				{
					scale_derivs( der , i , max_fac );
					dt_fac *= max_fac;
					continue;
				}
				break;
			}

		}

	}

	void scale_derivs( derivs_type &der , size_t order , double fac ) const
	{
		double scale = 1.0;
		for( size_t i=0 ; i<=order ; ++i )
		{
			scale *= fac;
			for( size_t j=0 ; j<dim ; ++j )
				der[i][j] *= scale;
		}
	}

	const derivs_type& get_last_derivs( void ) const
	{
		return m_derivs;
	}



private:

	derivs_type m_derivs;
	time_type m_dt_fac;
	value_type m_rel_error;
	value_type m_abs_error;





};

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* TAYLOR_DIRECT_FIXED_ORDER_HPP_ */
