//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_ALGO_BASIC_OP
#define BOOST_MOVE_ALGO_BASIC_OP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/utility_core.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/detail/iterator_traits.hpp>

namespace boost {
namespace movelib {

struct forward_t{};
struct backward_t{};
struct three_way_t{};

struct move_op
{
   template <class SourceIt, class DestinationIt>
   void operator()(SourceIt source, DestinationIt dest)
   {  *dest = ::boost::move(*source);  }

   template <class SourceIt, class DestinationIt>
   DestinationIt operator()(forward_t, SourceIt first, SourceIt last, DestinationIt dest_begin)
   {  return ::boost::move(first, last, dest_begin);  }

   template <class SourceIt, class DestinationIt>
   DestinationIt operator()(backward_t, SourceIt first, SourceIt last, DestinationIt dest_last)
   {  return ::boost::move_backward(first, last, dest_last);  }

   template <class SourceIt, class DestinationIt1, class DestinationIt2>
   void operator()(three_way_t, SourceIt srcit, DestinationIt1 dest1it, DestinationIt2 dest2it)
   {
      *dest2it = boost::move(*dest1it);
      *dest1it = boost::move(*srcit);
   }
};

struct swap_op
{
   template <class SourceIt, class DestinationIt>
   void operator()(SourceIt source, DestinationIt dest)
   {  boost::adl_move_swap(*dest, *source);  }

   template <class SourceIt, class DestinationIt>
   DestinationIt operator()(forward_t, SourceIt first, SourceIt last, DestinationIt dest_begin)
   {  return boost::adl_move_swap_ranges(first, last, dest_begin);  }

   template <class SourceIt, class DestinationIt>
   DestinationIt operator()(backward_t, SourceIt first, SourceIt last, DestinationIt dest_begin)
   {  return boost::adl_move_swap_ranges_backward(first, last, dest_begin);  }

   template <class SourceIt, class DestinationIt1, class DestinationIt2>
   void operator()(three_way_t, SourceIt srcit, DestinationIt1 dest1it, DestinationIt2 dest2it)
   {
      typename ::boost::movelib::iterator_traits<SourceIt>::value_type tmp(boost::move(*dest2it));
      *dest2it = boost::move(*dest1it);
      *dest1it = boost::move(*srcit);
      *srcit = boost::move(tmp);
   }
};

}} //namespace boost::movelib

#endif   //BOOST_MOVE_ALGO_BASIC_OP
