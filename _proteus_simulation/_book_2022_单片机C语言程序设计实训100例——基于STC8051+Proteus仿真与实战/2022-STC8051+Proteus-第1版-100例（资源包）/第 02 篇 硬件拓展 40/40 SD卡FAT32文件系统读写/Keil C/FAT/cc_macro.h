//-----------------------------------------------------------------
// FATÇý¶¯³ÌÐò
//-----------------------------------------------------------------
#ifdef  FAT_CREATE_DIR
#define FAT_ENTER_DIR
#define GET_DIR_START_CLUSTER
#ifdef USE_LFN
#define IS_LFN
#define GET_BINDING_SUMCHK
#define LFN_MATCH
#define WFINDSUBSTR
#define OEMSTRTOUNISTR
#ifdef USE_OEM_CHAR
#define OEMTOUNI
#endif
#endif
#define CHECK_SFN_ILLEGAL_LENGTH
#define CHECK_SFN_DOT
#define CHECK_ILLEGAL_CHAR
#define CHECK_SFN_SPECIAL_CHAR
#define CHECK_SFN_ILLEGAL_LOWER
#define TO_FILE_NAME
#define SFN_MATCH
#define FINDSUBSTR
#define GET_NEXT_CLUSTER
#define CREATE_DIR_IN_CLUSTER
#ifdef USE_LFN
#define IS_LFN
#define REGISTER_LFN_FDI
#define GET_PART_NAME
#define GET_BINDING_SUMCHK
#define FILL_LFN_FDI
#define MAKE_SHORT_NAME
#define HEX2STR_32B
#define ELFHASH
#endif
#define CHECK_SFN_ILLEGAL_LENGTH
#define CHECK_SFN_DOT
#define CHECK_ILLEGAL_CHAR
#define CHECK_SFN_SPECIAL_CHAR
#define CHECK_SFN_ILLEGAL_LOWER
#define FILL_FDI
#define CHECK_SFN_ILLEGAL_LOWER
#define REGISTER_FDI
#define GET_NEXT_CLUSTER
#define MODIFY_FAT
#define UPDATE_FSINFO
#define CLEAR_CLUSTER
#define UPDATE_NEXT_FREE_CLUSTER
#define UPDATE_FSINFO
#define MODIFY_FAT
#define UPDATE_FSINFO
#define CLEAR_CLUSTER
#define UPDATE_NEXT_FREE_CLUSTER
#define UPDATE_FSINFO
#endif

#ifdef  FAT_CREATE_FILE
#ifdef USE_LFN
#define IS_LFN
#define REGISTER_LFN_FDI
#define GET_PART_NAME
#define GET_BINDING_SUMCHK
#define FILL_LFN_FDI
#define MAKE_SHORT_NAME
#define HEX2STR_32B
#define ELFHASH
#endif
#define FAT_ENTER_DIR
#define GET_DIR_START_CLUSTER
#ifdef USE_LFN
#define IS_LFN
#define GET_BINDING_SUMCHK
#define LFN_MATCH
#define WFINDSUBSTR
#define OEMSTRTOUNISTR
#ifdef USE_OEM_CHAR
#define OEMTOUNI
#endif
#endif
#define CHECK_SFN_ILLEGAL_LENGTH
#define CHECK_SFN_DOT
#define CHECK_ILLEGAL_CHAR
#define CHECK_SFN_SPECIAL_CHAR
#define CHECK_SFN_ILLEGAL_LOWER
#define TO_FILE_NAME
#define SFN_MATCH
#define FINDSUBSTR
#define GET_NEXT_CLUSTER
#define CHECK_SFN_ILLEGAL_LENGTH
#define CHECK_SFN_DOT
#define CHECK_ILLEGAL_CHAR
#define CHECK_SFN_SPECIAL_CHAR
#define CHECK_SFN_ILLEGAL_LOWER
#define FILL_FDI
#define CHECK_SFN_ILLEGAL_LOWER
#define REGISTER_FDI
#define ANALYSE_FDI
#define GET_NEXT_CLUSTER
#define MODIFY_FAT
#define UPDATE_FSINFO
#define CLEAR_CLUSTER
#define UPDATE_NEXT_FREE_CLUSTER
#define UPDATE_FSINFO
#endif

#ifdef  FAT_DELETE_DIR
#define FAT_OPEN_FILE
#ifdef USE_LFN
#define IS_LFN
#define OEMSTRTOUNISTR
#ifdef USE_OEM_CHAR
#define OEMTOUNI
#endif
#define GET_BINDING_SUMCHK
#define LFN_MATCH
#define WFINDSUBSTR
#endif
#define FAT_ENTER_DIR
#define GET_DIR_START_CLUSTER
#ifdef USE_LFN
#define IS_LFN
#define GET_BINDING_SUMCHK
#define LFN_MATCH
#define WFINDSUBSTR
#define OEMSTRTOUNISTR
#ifdef USE_OEM_CHAR
#define OEMTOUNI
#endif
#endif
#define CHECK_SFN_ILLEGAL_LENGTH
#define CHECK_SFN_DOT
#define CHECK_ILLEGAL_CHAR
#define CHECK_SFN_SPECIAL_CHAR
#define CHECK_SFN_ILLEGAL_LOWER
#define TO_FILE_NAME
#define SFN_MATCH
#define FINDSUBSTR
#define GET_NEXT_CLUSTER
#define IS_WILDFILENAME
#define ANALYSE_FDI
#define ENTER_DEEP_AHEAD_DIR
#define HAVE_ANY_SUBDIR_WITH_DEL_FOREFILE
#define GET_UPPER_DIR
#define HAVE_ANY_SUBDIR_WITH_DEL_FOREFILE
#define DESTROY_FDI
#define DESTROY_FAT_CHAIN
#define GET_NEXT_CLUSTER
#define MODIFY_FAT
#define UPDATE_FSINFO
#endif

#ifdef  FAT_DELETE_FILE
#define FAT_OPEN_FILE
#ifdef USE_LFN
#define IS_LFN
#define OEMSTRTOUNISTR
#ifdef USE_OEM_CHAR
#define OEMTOUNI
#endif
#define GET_BINDING_SUMCHK
#define LFN_MATCH
#define WFINDSUBSTR
#endif
#define FAT_ENTER_DIR
#define GET_DIR_START_CLUSTER
#ifdef USE_LFN
#define IS_LFN
#define GET_BINDING_SUMCHK
#define LFN_MATCH
#define WFINDSUBSTR
#define OEMSTRTOUNISTR
#ifdef USE_OEM_CHAR
#define OEMTOUNI
#endif
#endif
#define CHECK_SFN_ILLEGAL_LENGTH
#define CHECK_SFN_DOT
#define CHECK_ILLEGAL_CHAR
#define CHECK_SFN_SPECIAL_CHAR
#define CHECK_SFN_ILLEGAL_LOWER
#define TO_FILE_NAME
#define SFN_MATCH
#define FINDSUBSTR
#define GET_NEXT_CLUSTER
#define IS_WILDFILENAME
#define ANALYSE_FDI
#define DESTROY_FDI
#define DESTROY_FAT_CHAIN
#define GET_NEXT_CLUSTER
#define MODIFY_FAT
#define UPDATE_FSINFO
#endif

#ifdef  FAT_DUMP_DATA
#define FAT_SEEK
#define GET_NEXT_CLUSTER
#define DESTROY_FAT_CHAIN
#define GET_NEXT_CLUSTER
#define MODIFY_FAT
#define UPDATE_FSINFO
#define MODIFY_FAT
#define UPDATE_FSINFO
#define UPDATE_FILE_SIZE
#define UPDATE_FILE_SCLUST
#endif

#ifdef  FAT_OPEN_FILE
#ifdef USE_LFN
#define IS_LFN
#define OEMSTRTOUNISTR
#ifdef USE_OEM_CHAR
#define OEMTOUNI
#endif
#define GET_BINDING_SUMCHK
#define LFN_MATCH
#define WFINDSUBSTR
#define GET_PART_NAME
#endif
#define FAT_ENTER_DIR
#define GET_DIR_START_CLUSTER
#ifdef USE_LFN
#define IS_LFN
#define GET_BINDING_SUMCHK
#define LFN_MATCH
#define WFINDSUBSTR
#define OEMSTRTOUNISTR
#ifdef USE_OEM_CHAR
#define OEMTOUNI
#endif
#endif
#define CHECK_SFN_ILLEGAL_LENGTH
#define CHECK_SFN_DOT
#define CHECK_ILLEGAL_CHAR
#define CHECK_SFN_SPECIAL_CHAR
#define CHECK_SFN_ILLEGAL_LOWER
#define TO_FILE_NAME
#define SFN_MATCH
#define FINDSUBSTR
#define GET_NEXT_CLUSTER
#define IS_WILDFILENAME
#define ANALYSE_FDI
#endif 

#ifdef  FAT_SEEK
#define GET_NEXT_CLUSTER
#endif

#ifdef  FAT_WRITEDATA
#define FAT_SEEK
#define GET_NEXT_CLUSTER
#define UPDATE_FILE_SIZE
#define WRITEDATA_FROM_NCLUSTER
#define UPDATE_FILE_SCLUST
#define UPDATE_NEXT_FREE_CLUSTER
#define UPDATE_FSINFO
#define MODIFY_FAT
#define UPDATE_FSINFO
#define UPDATE_FSINFO
#define CREATE_CLUSTER_CHAIN
#endif

#ifdef FAT_FORMAT_FS
#define GET_RECMD_SZCLU
#endif

#ifdef FAT_READDATA
#define FAT_SEEK
#define GET_NEXT_CLUSTER
#define GET_NEXT_CLUSTER
#endif

#ifdef FAT_READDATAX
#define FAT_SEEK
#define GET_NEXT_CLUSTER
#define GET_NEXT_CLUSTER
#endif

#ifdef FAT_MODIFY_DATA
#define FAT_SEEK
#define GET_NEXT_CLUSTER
#endif

#ifdef FAT_CLOSE_FILE
#define UPDATE_FILE_SIZE
#endif

#ifdef FAT_FLUSH_FS
#define UPDATE_FSINFO
#endif



