/*
 * eval_derivs_direct_static.hpp
 *
 *  Created on: Jun 17, 2011
 *      Author: karsten
 *
 *
 * Copyright Karsten Ahnert 2011.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EVAL_DERIVS_DIRECT_STATIC_HPP_
#define EVAL_DERIVS_DIRECT_STATIC_HPP_

#include <boost/fusion/include/at.hpp>

// debug includes
#include <iostream>
#include <typeinfo>
using namespace std;



namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {

namespace fusion = boost::fusion;

template< class Iteration , class System , class State , class Derivs , size_t Order >
struct eval_derivs_static
{
	typedef State state_type;
	typedef Derivs deriv_type;
	typedef typename Iteration::type iteration_type;

	System m_sys;
	const state_type &m_x;
	deriv_type &m_derivs;
	double m_dt_fac;


	eval_derivs_static( System sys , const State &x , deriv_type &derivs , double &dt_fac )
	: m_sys( sys ) , m_x( x ) , m_derivs( derivs ) , m_dt_fac( dt_fac ) { }

	template< class Index >
	void operator()( Index )
	{
		typedef typename fusion::result_of::at< System , Index >::type expr_type;

	 	expr_type expr = boost::fusion::at< Index >( m_sys );
	 	cout << typeid( expr ).name() << endl;

//	 	double deriv = 0.0;
//	 	double deriv = expr.eval< iteration_type , state_type , deriv_type >( iteration_type() , m_x , m_derivs );
	    double deriv = expr( iteration_type() , m_x , m_derivs );
	 	m_derivs[ Iteration::value ][ Index::value ] = m_dt_fac / double( Iteration::value + 1 ) * deriv;
	}
};

template< class Iteration , class System , class State , class Derivs , size_t Order >
eval_derivs_static< Iteration , System , State , Derivs , Order >
make_eval_derivs_static( System sys , const State &x , Derivs &derivs , double &dt_fac )
{
	return eval_derivs_static< Iteration , System , State , Derivs , Order >( sys , x , derivs , dt_fac );
}

} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost



#endif /* EVAL_DERIVS_DIRECT_STATIC_HPP_ */
