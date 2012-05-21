/*
 * taylor_proto.hpp
 *
 *  Created on: May 17, 2012
 *      Author: karsten
 */

#ifndef TAYLOR_PROTO_HPP_
#define TAYLOR_PROTO_HPP_

#include <iostream>
#define tab "\t"
using namespace std;

#include <boost/numeric/odeint/stepper/taylor/placeholders.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_proto/transforms.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/max.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/int.hpp>

#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/vector.hpp>

#include <boost/array.hpp>

namespace boost {
namespace numeric {
namespace odeint {



template< size_t Order , size_t Dim , typename Value = double >
class taylor_proto
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

	taylor_proto( value_type rel_error = 1.0e-14 , value_type abs_error = 1.0e-14 )
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
		/*
		 * Then: Introduce temporaries externally!
		 */

		BOOST_STATIC_ASSERT(( boost::fusion::traits::is_sequence< System >::value ));
		BOOST_STATIC_ASSERT(( size_t( boost::fusion::result_of::size< System >::value ) == dim ));

		eval_derivs( sys , in , m_derivs , m_dt_fac );

		value_type max_error = 0.0;
		for( size_t i=0 ; i<dim ; ++i )
		{
			value_type error = std::abs( m_derivs[order_value-1][i] ) /
					( m_rel_error * std::abs( in[i] ) + m_abs_error );
			max_error = std::max( error , max_error );
		}

		dt = pow( 1.0 / max_error , 1.0 / value_type( order_value ) );

		for( size_t i=0 ; i<dim ; ++i )
		{
			value_type tmp = 0.0;
			for( size_t k=0 ; k<order_value ; ++k )
				tmp = dt * ( tmp + m_derivs[order_value-1-k][i] );
			out[i] = in[i] + tmp;
		}

		dt *= m_dt_fac;
		t += dt;

	}




	// A grammar which count the number of multiplies nodes
	// can be used like
	// static int const num_multiplies_nodes = boost::result_of< count_multiplies( expr1_type ) >::type::value;
	struct count_multiplies
	  : proto::or_<
	        // match a plus node, return 1
	        proto::when<
	        	proto::multiplies< count_multiplies , count_multiplies > ,
	        	mpl::plus< mpl::int_<1>() , mpl::plus< count_multiplies( proto::_left ) , count_multiplies( proto::_right ) >() >() > ,
	        proto::when<
	            proto::binary_expr< proto::_ , count_multiplies , count_multiplies > ,
	            mpl::plus< count_multiplies( proto::_left ) , count_multiplies( proto::_right ) >() > ,
	        proto::when<
	            proto::unary_expr< proto::_ , count_multiplies > ,
	            mpl::plus< mpl::int_< 0 >() , count_multiplies( proto::_child ) >() > ,
	        proto::when<
	            proto::_ ,
	            mpl::int_< 0 >() >
	    >
	{};

	template< typename Expr >
	struct num_of_mult
	{
		typedef typename boost::result_of< count_multiplies( Expr ) >::type type;
	};

//	template< typename V , typename Size >
//	struct temporary
//	{
//		boost::array< V , Size > val ;
//		size_t i;
//		void reset( void ) { i = 0; }
//	};
//
////	void reset( void ) { }
//
//	template< typename Sizes >
//	struct get_temporaries
//	{
//		typedef int type;
//
//	};

	template< size_t MaxMult , size_t MaxOrder >
	struct temporaries
	{
		boost::array< boost::array< boost::array< value_type , MaxMult > , MaxOrder + 1 > , dim > values_left , values_right;
		boost::array< size_t , dim > indices;
		void reset( void )
		{
			for( size_t i=0 ; i<dim ; ++i ) indices[i] = 0;
		}
	};


	template< class System >
	void eval_derivs( System sys , const state_type &in , derivs_type &der , value_type &dt_fac ) const
	{
		const value_type min_error = 1.0e-19;
		const value_type max_error = 1.0e19;
		const value_type min_fac = 1.5;
		const value_type max_fac = 0.6;

		// include taylor_context_new
		// move everything to value_type instead of double


		typedef typename fusion::result_of::at_c< System , 0 >::type expr1_type;
		static int const num_multiplies_nodes = num_of_mult< expr1_type >::type::value;
		cout << num_multiplies_nodes << endl;
		proto::display_expr( fusion::at_c< 0 >( sys ) );

		typedef typename mpl::transform< System , num_of_mult< mpl::_1 > >::type num_of_mults;
		typedef typename mpl::fold< num_of_mults , mpl::int_< -1 > , mpl::max< mpl::_1 , mpl::_2 > >::type max_mults;

		cout << num_of_mult< typename fusion::result_of::at_c< System , 0 >::type >::type::value << endl;
		cout << num_of_mult< typename fusion::result_of::at_c< System , 1 >::type >::type::value << endl;
		cout << num_of_mult< typename fusion::result_of::at_c< System , 2 >::type >::type::value << endl;
		cout << "Max mults : " << max_mults::type::value << endl;

		temporaries< size_t( max_mults::type::value ) , order_value > temp;

		for( size_t i=0 ; i<order_value ; ++i )
		{
			temp.reset();
			boost::mpl::for_each< boost::mpl::range_c< size_t , 0 , dim > >( taylor_detail::make_proto_eval_derivs< order_value >( sys , in , der , temp , dt_fac , i ) );

			while( true )
			{
				value_type err = 0.0;
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

	void scale_derivs( derivs_type &der , size_t order , value_type fac ) const
	{
		value_type scale = 1.0;
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


#endif /* TAYLOR_PROTO_HPP_ */
