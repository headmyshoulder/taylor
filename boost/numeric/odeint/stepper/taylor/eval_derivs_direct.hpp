/*
 * eval_derivs_direct.hpp
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

#ifndef EVAL_DERIVS_DIRECT_HPP_
#define EVAL_DERIVS_DIRECT_HPP_

#include <boost/fusion/include/at.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {

namespace fusion = boost::fusion;

template< class System , class State , size_t Order >
struct eval_derivs
{
	typedef State state_type;
	typedef boost::array< State , Order > deriv_type;

	System m_sys;

	eval_derivs( System sys , const State &x , deriv_type &derivs , double &dt_fac , size_t which )
	: m_sys( sys ) { }

	template< class Index >
	void operator()( Index )
	{
		typedef typename fusion::result_of::at< System , Index >::type expr_type;

	// 	expr_type expr = boost::fusion::at< Index >( m_sys );

//		double deriv = taylor_transform()( expr , 0.0 , m_data );
//		m_data.derivs[ m_data.which ][ Index::value ] = m_data.dt_fac / double( m_data.which + 1 ) * deriv;
	}
};

template< class System , class State , size_t Order >
eval_derivs< System , State , Order > make_eval_derivs( System sys , const State &x , boost::array< State , Order > &derivs , double &dt_fac , size_t i )
{
	return eval_derivs< System , State , Order >( sys , x , derivs , dt_fac , i );
}

} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost



#endif /* EVAL_DERIVS_DIRECT_HPP_ */
