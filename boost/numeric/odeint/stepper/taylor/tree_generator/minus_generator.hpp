/*
 * minus_generator.hpp
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

#ifndef MINUS_GENERATOR_HPP_
#define MINUS_GENERATOR_HPP_

#include <boost/numeric/odeint/stepper/taylor/tree_nodes/minus_node.hpp>

#include <boost/proto/proto.hpp>

namespace boost {
namespace numeric {
namespace odeint {


namespace tree_generators {

namespace proto = boost::proto;


template< typename Grammar >
struct minus_transform : proto::transform< minus_transform< Grammar > >
{
	template< typename Expr , typename State , typename Data >
	struct impl : proto::transform_impl< Expr , State , Data >
	{
		typedef typename impl::expr expr_type;
		typedef typename expr_type::proto_args args_type;
		typedef typename args_type::child0 left_type;
		typedef typename args_type::child1 right_type;

		typedef typename boost::result_of< Grammar( left_type ) >::type left_result;
		typedef typename boost::result_of< Grammar( right_type ) >::type right_result;

		typedef typename tree_nodes::minus_node< left_result , right_result > result_type;

		result_type operator ()(
				typename impl::expr_param expr ,
				typename impl::state_param state ,
				typename impl::data_param data ) const
		{
			return result_type( Grammar()( proto::left( expr ) ) , Grammar()( proto::right( expr ) ) );
		}
	};
};

template< typename Grammar >
struct minus_generator : proto::when< proto::minus< Grammar , Grammar > , minus_transform< Grammar > > { };



} // namespace tree_generators



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif /* MINUS_GENERATOR_HPP_ */
