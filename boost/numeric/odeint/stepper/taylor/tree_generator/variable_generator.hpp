/*
 * variable_generator.hpp
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

#ifndef VARIABLE_GENERATOR_HPP_
#define VARIABLE_GENERATOR_HPP_

#include <ostream>

#include <boost/proto/proto.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/numeric/odeint/stepper/taylor/tree_nodes/variable_node.hpp>


namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {

namespace proto = boost::proto;
namespace mpl = boost::mpl;


template< typename I > struct placeholder : I {};


template< typename Index >
struct variable_transform : proto::transform< variable_transform< Index > >
{
	template< typename Expr , typename State , typename Data >
	struct impl : proto::transform_impl< Expr , State , Data >
	{
        typedef typename impl::expr expr_type;
        typedef typename expr_type::proto_args args_type;
        typedef typename args_type::child0 index_type;
		typedef variable_node< index_type::value , double > result_type;

		result_type operator ()(
				typename impl::expr_param expr ,
				typename impl::state_param state ,
				typename impl::data_param data ) const
		{
			return result_type();
		}
	};
};

template< typename Which >
struct variable_generator : proto::when< proto::terminal< placeholder< Which > > , variable_transform< Which > > { };

template< typename I >
std::ostream& operator<<( std::ostream &s , const placeholder< I > &p )
{
	s << "placeholder<" << I::value << ">";
	return s;
}







} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost

#endif /* VARIABLE_GENERATOR_HPP_ */
