/**
 * @file    feature_set.cc
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
 * The implementation of a class used to describe a set of features
 */

#include "h2sl_hdcg/feature_set.h"

using namespace std;
using namespace h2sl_hdcg;

Feature_Set::
Feature_Set() : h2sl::Feature_Set() {

}

Feature_Set::
~Feature_Set() {

}

Feature_Set::
Feature_Set( const Feature_Set& other ) : h2sl::Feature_Set( other ) {

}

Feature_Set&
Feature_Set::
operator=( const Feature_Set& other ) {
  _feature_products = other._feature_products;
  return (*this);
}

void 
Feature_Set::
to_xml( const string& filename )const{
  xmlDocPtr doc = xmlNewDoc( ( xmlChar* )( "1.0" ) );
  xmlNodePtr root = xmlNewDocNode( doc, NULL, ( xmlChar* )( "root" ), NULL );
  xmlDocSetRootElement( doc, root );
  to_xml( doc, root );
  xmlSaveFormatFileEnc( filename.c_str(), doc, "UTF-8", 1 );
  xmlFreeDoc( doc );
  return;
}

void 
Feature_Set::
to_xml( xmlDocPtr doc, 
        xmlNodePtr root )const{
  xmlNodePtr node = xmlNewDocNode( doc, NULL, ( xmlChar* )( "feature_set" ), NULL );
  for( unsigned int i = 0; i < _feature_products.size(); i++ ){
    _feature_products[ i ]->to_xml( doc, node );
  }
  xmlAddChild( root, node );
  return;
}

void 
Feature_Set::
from_xml( const string& filename ){
  xmlDoc * doc = NULL;
  xmlNodePtr root = NULL;
  doc = xmlReadFile( filename.c_str(), NULL, 0 );
  if( doc != NULL ){
    root = xmlDocGetRootElement( doc );
    if( root->type == XML_ELEMENT_NODE ){
      xmlNodePtr l1 = NULL;
      for( l1 = root->children; l1; l1 = l1->next ){
        if( l1->type == XML_ELEMENT_NODE ){
          if( xmlStrcmp( l1->name, ( const xmlChar* )( "feature_set" ) ) == 0 ){
            from_xml( l1 );
          }
        }
      }
    }
    xmlFreeDoc( doc );
  }
  return;
} 

void 
Feature_Set::
from_xml( xmlNodePtr root ){
  for( unsigned int i = 0; i < _feature_products.size(); i++ ){
    if( _feature_products[ i ] != NULL ){
      delete _feature_products[ i ];
      _feature_products[ i ] = NULL; 
    }
  }
  _feature_products.clear();

  if( root->type == XML_ELEMENT_NODE ){
    xmlNodePtr l1 = NULL;
    for( l1 = root->children; l1; l1 = l1->next ){
      if( l1->type == XML_ELEMENT_NODE ){
        if( xmlStrcmp( l1->name, ( const xmlChar* )( "feature_product" ) ) == 0 ){
          _feature_products.push_back( new h2sl_hdcg::Feature_Product() );
          _feature_products.back()->from_xml( l1 );
        }
      }
    }
  }
  return;
}


namespace h2sl_cdcg {
ostream&
operator<<( ostream& out,
            const Feature_Set& other ) {
  return out;
}

}
