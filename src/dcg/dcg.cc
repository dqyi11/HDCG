/**
 * @file    dcg.cc
 * @author  Thomas M. Howard (tmhoward@csail.mit.edu)
 *          Matthew R. Walter (mwalter@csail.mit.edu)
 * @version 1.0
 *
 * @section LICENSE
 *
 * This file is part of h2sl.
 *
 * Copyright (C) 2014 by the Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see
 * <http://www.gnu.org/licenses/gpl-2.0.html> or write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * @section DESCRIPTION
 *
 * The implementation of a class used to represent a Distributed 
 *   Correspondence Graph
 */

#include <fstream>
#include <utility>

#include "h2sl/grounding_set.h"
#include "h2sl/region.h"
#include "h2sl/constraint.h"
#include "h2sl/object.h"
#include "h2sl_hdcg/spatial_function.h"
#include "h2sl_hdcg/dcg.h"

using namespace std;
using namespace h2sl_hdcg;

DCG::
DCG() : h2sl::DCG() {

}

DCG::
~DCG() {

}

DCG::
DCG( const DCG& other ) : h2sl::DCG( other ) {

}

DCG&
DCG::
operator=( const DCG& other ) {
  _search_spaces = other._search_spaces;
  _correspondence_variables = other._correspondence_variables;
  _solutions = other._solutions;
  _root = other._root;
  return (*this);
}

void
DCG::
fill_search_spaces( const h2sl::World* world ){
  for( unsigned int i = 0; i < _search_spaces.size(); i++ ){
    if( _search_spaces[ i ].second != NULL ){
      delete _search_spaces[ i ].second;
      _search_spaces[ i ].second = NULL;
    }
    _search_spaces.clear();
  }

  for( unsigned int i = 0; i < _correspondence_variables.size(); i++ ){
    _correspondence_variables[ i ].clear();
  }
  _correspondence_variables.clear();


  std::vector< unsigned int > binary_cvs;
  binary_cvs.push_back( h2sl::CV_FALSE );
  binary_cvs.push_back( h2sl::CV_TRUE );

  std::vector< unsigned int > ternary_cvs;
  ternary_cvs.push_back( h2sl::CV_FALSE );
  ternary_cvs.push_back( h2sl::CV_TRUE );
  ternary_cvs.push_back( h2sl::CV_INVERTED );

  _correspondence_variables.push_back( binary_cvs );
  _correspondence_variables.push_back( ternary_cvs );

  // add the NP groundings
  for( unsigned int i = 0; i < h2sl::NUM_REGION_TYPES; i++ ){
    if( i != h2sl::REGION_TYPE_UNKNOWN ){
      _search_spaces.push_back( pair< unsigned int, h2sl::Grounding* >( 0, new h2sl::Region( i, h2sl::Object() ) ) );
    }
    for( unsigned int j = 0; j < world->objects().size(); j++ ){
      _search_spaces.push_back( pair< unsigned int, h2sl::Grounding* >( 0, new h2sl::Region( i, *world->objects()[ j ] ) ) );
    }
  }

  // add objects
  for( unsigned int i = 0; i < world->objects().size(); i++ ) {
    _search_spaces.push_back( pair< unsigned int, h2sl::Grounding* >( 0, world->objects()[ i ] ) );
  }

  // add the PP groundings
  for( unsigned int i = 0; i < h2sl::NUM_REGION_TYPES; i++ ){
    if( i != h2sl::REGION_TYPE_UNKNOWN ){
      _search_spaces.push_back( pair< unsigned int, h2sl::Grounding* >( 0, new h2sl::Region( i, h2sl::Object() ) ) );
    }
    for( unsigned int j = 0; j < world->objects().size(); j++ ){
      _search_spaces.push_back( pair< unsigned int, h2sl::Grounding* >( 0, new h2sl::Region( i, *world->objects()[ j ] ) ) );
    }
  }

  // add the VP groundings
  for( unsigned int i = h2sl::CONSTRAINT_TYPE_INSIDE; i < h2sl::NUM_CONSTRAINT_TYPES; i++ ){
    for( unsigned int j = 0; j < world->objects().size(); j++ ){
      for( unsigned int k = 0; k < h2sl::NUM_REGION_TYPES; k++ ){
        for( unsigned int l = 0; l < world->objects().size(); l++ ){
          for( unsigned int m = 0; m < h2sl::NUM_REGION_TYPES; m++ ){
            if( ( j != l ) || ( k != m ) ){
              _search_spaces.push_back( pair< unsigned int, h2sl::Grounding* >( 1, new h2sl::Constraint( i, h2sl::Region( k, *world->objects()[ j ] ), h2sl::Region( m, *world->objects()[ l ] ) ) ) );
            }
          }
        }
      }
    }
  }

  std::vector< h2sl_hdcg::Spatial_Function* > child_avoid_funcs;
  for( unsigned int j = 0; j < world->objects().size(); j++ ) {
    std::vector< h2sl::Object > objects;
    objects.push_back( *( world->objects()[ j ] ) );
    for( unsigned int i = SPATIAL_FUNC_TYPE_LEFT_OF; i <= SPATIAL_FUNC_TYPE_BOTTOM_OF; i++ ){
      _search_spaces.push_back( pair< unsigned int, h2sl::Grounding* >( 1, new h2sl_hdcg::Spatial_Function( j, objects ) ) );
      child_avoid_funcs.push_back( new h2sl_hdcg::Spatial_Function( j, objects ) );
    }
  }
  for( unsigned int i = 0; i < world->objects().size(); i++ ) {
    for( unsigned int j = 0; j < i; j++ ) {
      std::vector< h2sl::Object > objects;
      objects.push_back( *( world->objects()[ i ] ) );
      objects.push_back( *( world->objects()[ j ] ) );
      _search_spaces.push_back( pair< unsigned int, h2sl::Grounding* >( 1, new h2sl_hdcg::Spatial_Function( SPATIAL_FUNC_TYPE_IN_BETWEEN, objects ) ) );
      child_avoid_funcs.push_back( new h2sl_hdcg::Spatial_Function( SPATIAL_FUNC_TYPE_IN_BETWEEN, objects ) );
    }
  }
  
  for( unsigned int i = 0; i < child_avoid_funcs.size(); i ++ ) {
    h2sl_hdcg::Spatial_Function* p_avoid_func = new h2sl_hdcg::Spatial_Function( SPATIAL_FUNC_TYPE_AVOID );
    p_avoid_func->set_child_function( child_avoid_funcs[ i ] );
    _search_spaces.push_back( pair< unsigned int, h2sl::Grounding* >( 1, p_avoid_func ) );
  }


  return;
}
  
namespace h2sl_hdcg {
  ostream&
  operator<<( ostream& out,
              const DCG& other ) {
    
    return out;
  }
}
