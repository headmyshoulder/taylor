/*
 * unary_generator.hpp
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

#ifndef UNARY_GENERATOR_HPP_
#define UNARY_GENERATOR_HPP_


#include <boost/numeric/odeint/stepper/taylor/tree_nodes/sin_node.hpp>

#include <boost/proto/proto.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {

namespace proto = boost::proto;

struct sin_tag {};
struct cos_tag {};
struct exp_tag {};
struct log_tag {};


struct sin_terminal : proto::terminal< sin_tag > {};
struct cos_terminal : proto::terminal< cos_tag > {};
struct exp_terminal : proto::terminal< exp_tag > {};
struct log_terminal : proto::terminal< log_tag > {};


const sin_terminal::type sin = {{}};
const cos_terminal::type cos = {{}};
const exp_terminal::type exp = {{}};
const log_terminal::type log = {{}};

template< class NodeFactory >
struct sin_op {
	template< class Child > struct result { typedef typename NodeFactory::template sin< Child >::type type; };
};

template< class NodeFactory >
struct cos_op {
    template< class Child > struct result { typedef typename NodeFactory::template cos< Child >::type type; };
};

template< class NodeFactory >
struct exp_op {
    template< class Child > struct result { typedef typename NodeFactory::template exp< Child >::type type; };
};

template< class NodeFactory >
struct log_op {
    template< class Child > struct result { typedef typename NodeFactory::template log< Child >::type type; };
};




template< typename Grammar , typename UnaryOp >
struct unary_transform : proto::transform< unary_transform< Grammar , UnaryOp > >
{
	template< typename Expr , typename State , typename Data >
	struct impl : proto::transform_impl< Expr , State , Data >
	{
		typedef typename impl::expr expr_type;
		typedef typename expr_type::proto_args args_type;
		typedef typename args_type::child1 child_type;
		typedef typename boost::result_of< Grammar( child_type ) >::type child_result;

		typedef typename UnaryOp::template result< child_result >::type result_type;

		result_type operator ()(
				typename impl::expr_param expr ,
				typename impl::state_param state ,
				typename impl::data_param data ) const
		{
			return result_type( Grammar()( proto::child_c<1>( expr ) ) );
		}
	};
};

template< typename Grammar , typename NodeFactory >
struct unary_generator : proto::or_<
	proto::when< proto::function< sin_terminal , Grammar > , unary_transform< Grammar , sin_op< NodeFactory > > > ,
	proto::when< proto::function< cos_terminal , Grammar > , unary_transform< Grammar , cos_op< NodeFactory > > > ,
	proto::when< proto::function< exp_terminal , Grammar > , unary_transform< Grammar , exp_op< NodeFactory > > > ,
	proto::when< proto::function< log_terminal , Grammar > , unary_transform< Grammar , log_op< NodeFactory > > >
> { };


std::ostream& operator<<( std::ostream &s , const sin_tag &tag ) {
	s << "sin";
	return s;
}

std::ostream& operator<<( std::ostream &s , const cos_tag &tag ) {
	s << "cos";
	return s;
}

std::ostream& operator<<( std::ostream &s , const exp_tag &tag ) {
	s << "exp";
	return s;
}

std::ostream& operator<<( std::ostream &s , const log_tag &tag ) {
	s << "log";
	return s;
}





} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif /* UNARY_GENERATOR_HPP_ */
