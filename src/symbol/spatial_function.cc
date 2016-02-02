/**
 * @file   spatial_func.cc
 * @author Daqing Yi (daqing.yi@byu.edu)
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The implementation of a class used to describe a spatial relation function
 */

#include <stdlib.h>
#include <sstream>
#include "h2sl_hdcg/spatial_function.h"

using namespace std;
using namespace h2sl_hdcg;

Spatial_Function::Spatial_Function( const unsigned int& type , const std::vector< h2sl::Object >& objects ) : _type( type ), _objects( objects ) {
}

Spatial_Function::Spatial_Function( const spatial_func_type_t& type, const std::vector< h2sl::Object >& objects ) : _type( type ), _objects( objects ) {
}
 
Spatial_Function::~Spatial_Function() {
}

Spatial_Function::Spatial_Function( const Spatial_Function& other ) : Grounding( other ),
                                                    _type( other._type ),
                                                    _objects( other._objects ) {

}

Spatial_Function& Spatial_Function::operator=( const Spatial_Function& other ) {
  _type = other._type;
  _objects = other._objects;
  return (*this);
}

bool Spatial_Function::operator==( const Spatial_Function& other ) const {
  if( _type != other._type ) {
    return false;
  } else if ( _objects.size() != other._objects.size() ) {
    return false;
  } else {
    for( unsigned int i = 0; i < _objects.size(); i ++ ) {
      if( _objects[ i ] != other._objects[ i ] ) {
        return false;
      }   
    }
    return true;
  }
}

bool Spatial_Function::operator!=( const Spatial_Function& other ) const {
  return !( *this == other );
}

h2sl::Grounding* Spatial_Function::dup( void ) const {
  return new Spatial_Function( *this );
}


std::string Spatial_Function::type_to_std_string( const unsigned int& type ) {
  switch( type ) {
  case( SPATIAL_FUNC_TYPE_UNKNOWN ):
  default:
    return "na";
  case( SPATIAL_FUNC_TYPE_IN_BETWEEN ):
    return "in_between";
  case( SPATIAL_FUNC_TYPE_LEFT_OF ):
    return "left_of";
  case( SPATIAL_FUNC_TYPE_RIGHT_OF ):
    return "right_of";
  case( SPATIAL_FUNC_TYPE_AVOID ):
    return "avoid";
  }
}

unsigned int Spatial_Function::type_from_std_string( const std::string& type ) {
  for( unsigned int i = 0; i < NUM_SPATIAL_FUNC_TYPES; i++ ) {
    if( type == type_to_std_string( i ) ) {
      return i;
    }
  }
  return SPATIAL_FUNC_TYPE_UNKNOWN;
}

void Spatial_Function::to_xml( const std::string& filename ) const {
  xmlDocPtr doc = xmlNewDoc( ( xmlChar* )( "1.0" ) );
  xmlNodePtr root = xmlNewDocNode( doc, NULL, ( xmlChar* )( "root" ), NULL );
  xmlDocSetRootElement( doc, root );
  to_xml( doc, root);
  xmlSaveFormatFileEnc( filename.c_str(), doc, "UTF-8", 1 );
  xmlFreeDoc( doc );
  return;
}

void Spatial_Function::to_xml( xmlDocPtr doc, xmlNodePtr root ) const {
  xmlNodePtr node = xmlNewDocNode( doc, NULL, ( const xmlChar* )( "spatial_function" ), NULL );
  xmlNewProp( node, ( const xmlChar* )( "type" ), ( const xmlChar* )( type_to_std_string( _type ).c_str() ) );
  for( unsigned int i = 0; i < _objects.size(); i ++ ) {
    _objects[ i ].to_xml( doc, node );
  }
  xmlAddChild( root, node );
  return;
}

void Spatial_Function::from_xml( const std::string& filename ) {
  xmlDoc * doc = NULL;
  xmlNodePtr root = NULL;
  doc = xmlReadFile( filename.c_str(), NULL, 0 );
  if( doc != NULL ) {
    root = xmlDocGetRootElement( doc );
    if( root->type == XML_ELEMENT_NODE ) {
      xmlNodePtr l1 = NULL;
      for( l1 = root->children; l1; l1 = l1->next ){
        if( l1->type == XML_ELEMENT_NODE ){
          if( xmlStrcmp( l1->name, ( const xmlChar* )( "spatial_function" ) ) == 0 ) {
            from_xml( l1 );
          }
        }
      }
    }
    xmlFreeDoc( doc );
  }
  return;
}

void Spatial_Function::from_xml( xmlNodePtr root ) {
  _type = SPATIAL_FUNC_TYPE_UNKNOWN;
  if( root->type == XML_ELEMENT_NODE ) {
    xmlChar* tmp = xmlGetProp( root, ( const xmlChar* )( "type" ) );
    if( tmp != NULL ) {
      string type_string = ( char* )( tmp );
      _type = type_from_std_string( type_string );
      xmlFree( tmp );
    }
    
    xmlNodePtr l1 = NULL;
    for( l1 = l1->children; l1; l1 = l1->next ) {
      if( l1->type == XML_ELEMENT_NODE ) {
        if( xmlStrcmp( l1->name, ( const xmlChar* )( "object" ) ) == 0 ) {
          h2sl::Object object;
          object.from_xml( l1 );
          _objects.push_back( object );
        }
      }
    }
  } 
  return;
}

namespace h2sl_hdcg {
  ostream&
  operator<<( ostream& out, const Spatial_Function& other ) {
    out << "Spatial_Function(";
    out << "type=\"" << Spatial_Function::type_to_std_string( other.type() ) << "\",";
    out << "objects="; 
    for( unsigned int i = 0; i < other.objects().size(); i ++ ){
      out << "secondary=" << other.objects()[ i ];
    }
    out << ")";
    return out;
  }
}