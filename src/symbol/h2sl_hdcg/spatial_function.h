/**
 * @file    spatial_function.h
 * @author  Daqing Yi (daqing.yi@byu.edu)
 * @version 1.0
 * @section DESCRIPTION
 *
 * The interface for a class used to describe a spatial relation
 */

#ifndef H2SL_SPATIAL_FUNCTION_H
#define H2SL_SPATIAL_FUNCTION_H

#include <iostream>
#include <vector>

#include "h2sl/grounding.h"
#include "h2sl/object.h"

namespace h2sl_hdcg {
  typedef enum {
    SPATIAL_FUNC_TYPE_UNKNOWN,
    SPATIAL_FUNC_TYPE_IN_BETWEEN,
    SPATIAL_FUNC_TYPE_LEFT_OF,
    SPATIAL_FUNC_TYPE_RIGHT_OF,
    SPATIAL_FUNC_TYPE_TOP_OF,
    SPATIAL_FUNC_TYPE_BOTTOM_OF,
    SPATIAL_FUNC_TYPE_AVOID,
    NUM_SPATIAL_FUNC_TYPES
  } spatial_func_type_t;

  class Spatial_Function : public h2sl::Grounding {
  public:
    Spatial_Function( const unsigned int& type = 0, 
                      const std::vector< h2sl::Object >& objects  = std::vector< h2sl::Object >() );
    Spatial_Function( const spatial_func_type_t& type, 
                      const std::vector< h2sl::Object >& objects );
    virtual ~Spatial_Function();

    Spatial_Function( const Spatial_Function& other );
    Spatial_Function& operator=( const Spatial_Function& other );
    bool operator==( const Spatial_Function& other ) const;
    bool operator!=( const Spatial_Function& other ) const;
    virtual Grounding* dup( void ) const;
    
    static std::string type_to_std_string( const unsigned int& type );
    static unsigned int type_from_std_string( const std::string& type );
   
    virtual void to_xml( const std::string& filename ) const;
    virtual void to_xml( xmlDocPtr doc, xmlNodePtr root ) const;
    static void to_xml( xmlDocPtr doc, xmlNodePtr root, const Spatial_Function* p_func );

    virtual void from_xml( const std::string& filename );
    virtual void from_xml( xmlNodePtr root );
    static void from_xml( xmlNodePtr root, Spatial_Function* p_func );

    inline unsigned int& type( void ) { return _type; }; 
    inline const unsigned int& type( void ) const { return _type; };
    inline std::vector< h2sl::Object >&  objects( void ) { return _objects; };
    inline const std::vector< h2sl::Object >& objects(  void ) const { return _objects; };
    inline Spatial_Function* child_function( void ) { return _p_child_function; };
    inline Spatial_Function* child_function( void ) const { return _p_child_function; };

  protected:
    unsigned int _type;
    std::vector< h2sl::Object > _objects;
    Spatial_Function* _p_child_function;
  };
}

#endif /* H2SL_SPATIAL_FUNCTION_H */
