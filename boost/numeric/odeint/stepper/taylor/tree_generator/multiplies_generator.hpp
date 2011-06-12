/*
 * multiplies_generator.hpp
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

#ifndef MULTIPLIES_GENERATOR_HPP_
#define MULTIPLIES_GENERATOR_HPP_


#include <boost/numeric/odeint/stepper/taylor/tree_nodes/multiplies_node.hpp>

#include <boost/proto/proto.hpp>

namespace boost {
namespace numeric {
namespace odeint {


namespace tree_generators {

namespace proto = boost::proto;


template< typename Grammar >
struct multiplies_transform : proto::transform< multiplies_transform< Grammar > >
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

		typedef typename tree_nodes::multiplies_node< left_result , right_result > result_type;

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
struct multiplies_generator : proto::when< proto::multiplies< Grammar , Grammar > , multiplies_transform< Grammar > > { };



} // namespace tree_generators



} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* MULTIPLIES_GENERATOR_HPP_ */
