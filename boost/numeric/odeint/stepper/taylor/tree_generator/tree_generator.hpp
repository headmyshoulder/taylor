/*
 * tree_generator.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: karsten
 */

#ifndef TREE_GENERATOR_HPP_
#define TREE_GENERATOR_HPP_

// mpl includes
#include <boost/mpl/size_t.hpp>

// proto includes
#include <boost/proto/proto.hpp>


#include <boost/numeric/odeint/stepper/taylor/tree_generator/plus_generator.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_generator/variable_generator.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_generator/constant_generator.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_generator/multiplies_generator.hpp>

namespace boost {
namespace numeric {
namespace odeint {


namespace tree_generators {

namespace proto = boost::proto;




struct tree_generator :
	proto::or_
	<
		variable_generator< proto::_ > ,
		constant_generator ,
		plus_generator< tree_generator > ,
		multiplies_generator< tree_generator >
	> { };


} // namespace tree_generators



} // namespace odeint
} // namespace numeric
} // namespace boost

#endif /* TREE_GENERATOR_HPP_ */
