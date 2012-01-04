/*
 * node_factory.hpp
 *
 *  Created on: Dec 25, 2011
 *      Author: karsten
 */

#ifndef NODE_FACTORY_HPP_
#define NODE_FACTORY_HPP_

#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v2/minus_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v2/plus_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v2/multiplies_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v2/scalar_multiplies_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v2/scalar_plus_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v2/variable_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v2/constant_node.hpp>
#include <boost/numeric/odeint/stepper/taylor/tree_nodes_v2/sin_node.hpp>


namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {
namespace tree_nodes_v2 {



struct node_factory
{
    typedef double value_type;

    template< typename Left , typename Right >
    struct minus
    {
        typedef minus_node< Left , Right , value_type > type;
    };


    template< typename Left , typename Right >
    struct plus
    {
        typedef plus_node< Left , Right , value_type > type;
    };


    template< typename Left , typename Right >
    struct multiplies
    {
        typedef multiplies_node< Left , Right , value_type > type;
    };


    template< typename Child >
    struct scalar_multiplies
    {
        typedef scalar_multiplies_node< Child , value_type > type;
    };


    template< typename Child >
    struct scalar_plus
    {
        typedef scalar_plus_node< Child , value_type > type;
    };


    struct constant
    {
        typedef constant_node< value_type > type;
    };


    template< size_t Index >
    struct variable
    {
        typedef variable_node< Index , value_type > type;
    };


    template< typename Child >
    struct sin
    {
        typedef sin_node< Child > type;
    };


    template< typename Child >
    struct cos
    {
        // ToDo : implement cos_node
        typedef sin_node< Child > type;
    };


    template< typename Child >
    struct exp
    {
        // ToDo : implement exp_node
        typedef sin_node< Child > type;
    };


    template< typename Child >
    struct log
    {
        // ToDo : implement log_node
        typedef sin_node< Child > type;
    };



};

} // namespace tree_nodes_v2
} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost

#endif /* NODE_FACTORY_HPP_ */
