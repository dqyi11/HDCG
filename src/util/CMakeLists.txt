# GENGETOPT FILES
set(GGOS
    llm_train_hdcg.ggo
    gui_demo_hdcg.ggo
    )

# HEADER FILES
set(HDRS
    )

# QT HEADER FILES
set(QT_HDRS 
    )

# SOURCE FILES
set(SRCS
    )

# BINARY SOURCE FILES
set(BIN_SRCS
    llm_train_hdcg.cc
    gui_demo_hdcg.cc
    )

# LIBRARY DEPENDENCIES
set(DEPS h2sl-symbol-hdcg h2sl-dcg-hdcg h2sl-llm-hdcg ${H2SL_LIBRARIES} ${QT_LIBRARIES} ${LIBXML2_LIBRARIES} ${Boost_LIBRARIES})

# LIBRARY NAME
set(LIB
#    h2sl-util-hdcg
    )

# process the headers
process_hdrs(HDRS ${HDRS} QT_HDRS ${QT_HDRS})

# process the library
#process_lib(LIB ${LIB} QT_HDRS ${QT_HDRS} SRCS ${SRCS} DEPS ${DEPS})

# process the binaries
process_bin_srcs(LIB ${LIB} BIN_SRCS ${BIN_SRCS} GGOS ${GGOS} DEPS ${DEPS})
