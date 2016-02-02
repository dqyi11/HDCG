# GENGETOPT FILES
set(GGOS
    feature_set_hdcg_demo.ggo
   )
 
# HEADER FILES
set(HDRS
    h2sl_hdcg/feature_spatial_function.h
    h2sl_hdcg/feature_spatial_function_matches_child.h
    h2sl_hdcg/feature_spatial_function_object_matches_child.h
    h2sl_hdcg/feature_product.h
    h2sl_hdcg/feature_set.h
   )

# QT HEADER FILES
set(QT_HDRS )

# SOURCE FILES
set(SRCS
    feature_spatial_function.cc
    feature_spatial_function_matches_child.cc
    feature_spatial_function_object_matches_child.cc
    feature_product.cc
    feature_set.cc
   )

# BINARY SOURCE FILES
set(BIN_SRCS
    feature_set_hdcg_demo.cc
   )

# LIBRARY DEPENDENCIES
set(DEPS h2sl-symbol-hdcg ${H2SL_LIBRARIES} ${LIBXML2_LIBRARIES})

# LIBRARY NAME
set(LIB h2sl-llm-hdcg)

# process the headers
process_hdrs(HDRS ${HDRS} QT_HDRS ${QT_HDRS})

# process the library
process_lib(LIB ${LIB} QT_HDRS ${QT_HDRS} SRCS ${SRCS} DEPS ${DEPS})

# process the binaries
process_bin_srcs(LIB ${LIB} BIN_SRCS ${BIN_SRCS} GGOS ${GGOS} DEPS ${DEPS})
