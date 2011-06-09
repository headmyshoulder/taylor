/*
 * variable_generator.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: karsten
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


namespace tree_generators {

namespace proto = boost::proto;
namespace mpl = boost::mpl;

template< typename I > struct placeholder : I {};

proto::terminal< placeholder< mpl::size_t< 0 > > >::type const arg1 = {};
proto::terminal< placeholder< mpl::size_t< 1 > > >::type const arg2 = {};
proto::terminal< placeholder< mpl::size_t< 2 > > >::type const arg3 = {};


template< typename I >
std::ostream& operator<<( std::ostream &s , const placeholder< I > &p )
{
	s << "placeholder<" << I::value << ">";
	return s;
}


template< typename Index >
struct variable_transform : proto::transform< variable_transform< Index > >
{
	template< typename Expr , typename State , typename Data >
	struct impl : proto::transform_impl< Expr , State , Data >
	{
		typedef typename tree_nodes::variable_node< double > result_type;

		result_type operator ()(
				typename impl::expr_param expr ,
				typename impl::state_param state ,
				typename impl::data_param data ) const
		{
			typedef typename impl::expr expr_type;
			typedef typename expr_type::proto_args args_type;
			typedef typename args_type::child0 index_type;
			const size_t index = index_type::value;

			return result_type( index );
		}
	};
};

template< typename Which >
struct variable_generator : proto::when< proto::terminal< placeholder< Which > > , variable_transform< Which > > { };








} // namespace tree_generators



} // namespace odeint
} // namespace numeric
} // namespace boost

#endif /* VARIABLE_GENERATOR_HPP_ */
