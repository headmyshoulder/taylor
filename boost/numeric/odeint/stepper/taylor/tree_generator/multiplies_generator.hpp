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


#include <boost/proto/proto.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {

namespace proto = boost::proto;

template< typename Grammar , typename NodeFactory >
struct multiplies_transform : proto::transform< multiplies_transform< Grammar , NodeFactory > >
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

		typedef typename NodeFactory::template multiplies< left_result , right_result >::type result_type;

		result_type operator ()(
				typename impl::expr_param expr ,
				typename impl::state_param state ,
				typename impl::data_param data ) const
		{
			return result_type( Grammar()( proto::left( expr ) ) , Grammar()( proto::right( expr ) ) );
		}
	};
};


// hier gehts weiter
template< typename Grammar , typename NodeFactory >
struct right_scalar_multiplies_transform : proto::transform< right_scalar_multiplies_transform< Grammar , NodeFactory > >
{
	template< typename Expr , typename State , typename Data >
	struct impl : proto::transform_impl< Expr , State , Data >
	{
		typedef typename impl::expr expr_type;
		typedef typename expr_type::proto_args args_type;
		typedef typename args_type::child0 left_type;
		typedef typename args_type::child1 right_type;

		typedef typename boost::result_of< Grammar( left_type ) >::type left_result;

		typedef typename NodeFactory::template scalar_multiplies< left_result >::type result_type;

		result_type operator ()(
				typename impl::expr_param expr ,
				typename impl::state_param state ,
				typename impl::data_param data ) const
		{
			return result_type( Grammar()( proto::left( expr ) ) , proto::value( proto::right( expr ) ) );
		}
	};
};

template< typename Grammar , typename NodeFactory >
struct left_scalar_multiplies_transform : proto::transform< left_scalar_multiplies_transform< Grammar , NodeFactory > >
{
	template< typename Expr , typename State , typename Data >
	struct impl : proto::transform_impl< Expr , State , Data >
	{
		typedef typename impl::expr expr_type;
		typedef typename expr_type::proto_args args_type;
		typedef typename args_type::child0 left_type;
		typedef typename args_type::child1 right_type;

		typedef typename boost::result_of< Grammar( right_type ) >::type right_result;

		typedef typename NodeFactory::template scalar_multiplies< right_result >::type result_type;

		result_type operator ()(
				typename impl::expr_param expr ,
				typename impl::state_param state ,
				typename impl::data_param data ) const
		{
			return result_type( Grammar()( proto::right( expr ) ) , proto::value( proto::left( expr ) ) );
		}
	};
};

template< typename Grammar , typename NodeFactory >
struct pure_multiplies_generator : proto::when< proto::multiplies< Grammar , Grammar > , multiplies_transform< Grammar , NodeFactory > > { };

template< typename Grammar , typename NodeFactory >
struct scalar_multiplies_generator : proto::or_<
	proto::when< proto::multiplies< Grammar , proto::terminal< double > > , right_scalar_multiplies_transform< Grammar , NodeFactory > > ,
	proto::when< proto::multiplies< proto::terminal< double > , Grammar > , left_scalar_multiplies_transform< Grammar , NodeFactory > >
> { };


template< typename Grammar , typename NodeFactory >
struct multiplies_generator : proto::or_<
		scalar_multiplies_generator< Grammar , NodeFactory > ,
		pure_multiplies_generator< Grammar , NodeFactory >
	> { };



} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* MULTIPLIES_GENERATOR_HPP_ */
