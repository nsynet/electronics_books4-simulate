//-----------------------------------------------------------------
// 名称: FAT驱动程序头文件
//-----------------------------------------------------------------
#ifndef __FAT_H__
#define __FAT_H__
#include "mytype.h" 				//数据类型重定义，请根据目标平台进行定义 
#include "config.h" 				//FAT的配置文件
#include "cc_macro.h" 			//此头文件中定义了FAT中各种函数之间的以来关系，加之编译控制可实现功能函数的裁减，可减少程序存储器的使用量

#define MBR_SECTOR			(0)								//MBR扇区
#define DBR_MARK				{0xEB,0x58,0x90}	//DBR的标志码

#define FDI_NBYTES			(32)							//文件目录项所占字节数 
#define NFDI_PER_SEC		(16)							//每扇区的文件目录项数

#define FAT_BUF_SIZE		(512)							//FAT内部缓冲区大小 

#define SOC(c) (((c-2)*(pInitInfo->SectorsPerClust))+(pInitInfo->FirstDirSector)) //计算簇的开始扇区 Start Sector Of Cluster

#define NFATITEMBYTES			(4)							//FAT表项所占用的字节数
#define NITEMSINFATSEC		(128)						//FAT表一个扇区中包含的表项数

#define IS_END_CLU(cluster) ((0x0FFFFFFF)==(cluster)) //判断一个簇项的值是否是结束簇
#define IS_END_SEC_OF_CLU(sec,cluster) ((sec-SOC(cluster))==(pInitInfo->SectorsPerClust-1)) //判断是否是簇的最后一个扇区
#define LAST_SEC_OF_CLU(cluster) (SOC(cluster)+(pInitInfo->SectorsPerClust-1)) //簇的最后一个扇区的地址
#define IS_FAT32_TYPE(FST) (('F'==(FST[0])) && ('A'==(FST[1])) && ('T'==(FST[2])) && ('3'==(FST[3])) && ('2'==(FST[4]))) //检验文件系统是否FAT32 

#define CHK_ATTR_FILE(attr)	((!((attr&0x10)!=0x00)) && (0x0F!=attr) && (0x00!=attr) && (0x08!=attr)) //属性字节第4位为0，同时不是长名属性0x0F，空项或卷标 
#define CHK_ATTR_DIR(attr)	((attr&0x10)!=0x00) //属性字节第4位为1，则视其为目录
#define CHK_ATTR_LFN(attr)	(0x0F==attr) 		//属性字节为0x0F，则为长名项

#define Lower2Up(c)		((c>='a' && c<='z')?(c-32):c)
#define Upper2Low(C)	((C>='A' && C<='Z')?(C+32):C)
#define WLower2Up(c)	((c>=(u16)'a' && c<=(u16)'z')?(c-32):c)
#define WUpper2Low(C)	((C>=(u16)'A' && C<=(u16)'Z')?(C+32):C)
#define IS_ASC(c)			((c&0x80)==0)

#define MAKE_TIME(h,m,s)	((((u16)h)<<11)+(((u16)m)<<5)+(((u16)s)>>1))			//按时间的位段定义合成时间字
#define MAKE_DATE(y,m,d)	(((((u16)(y%100))+20)<<9)+(((u16)m)<<5)+((u16)d))	//按日期的位段定义合成日期字

#define BOOL_TRUE				(1) 
#define BOOL_FALSE			(0)
#define NUL_RET					(0)
#define NUL_PTR					((void *)0)
//-----------------------------------------------------------------
#define NSECPERTRACK		(63)
#define NHEADER					(255)
#define NSECPERCYLINDER	(((u32)NSECPERTRACK)*((u32)NHEADER))
//-----------------------------------------------------------------
// 以下函数用于从FLASHROM中读取相应类型的数据
//-----------------------------------------------------------------
#define GET_PGM_BYTE(u)		(PGM_BYTE_FUN(u))   
#define GET_PGM_WORD(u)		(PGM_WORD_FUN(u))  
#define GET_PGM_DWORD(u)	(PGM_DWORD_FUN(u))
//-----------------------------------------------------------------
// ERR 错误码
//-----------------------------------------------------------------
#define ERR_SUCC          					(0)
#define ERR_FAIL          					(1)
#define FSTYPE_NOT_FAT32  					(2)
#define ERR_NO_FILE       					(3)
#define ERR_NO_DIR        					(4)
#define ERR_FDI_ALREADY_EXISTING		(5)
#define ERR_FDI_NO_SPARE_SPACE  		(6)
#define ERR_NO_SPACE            		(7)
#define ERR_ILL_CHAR            		(8)
#define ERR_SFN_ILL_LEN    	    		(9)
#define ERR_SFN_DOT             		(10)
#define ERR_SFN_SPEC_CHAR       		(11)
#define ERR_SFN_ILL_LOWER       		(12)
#define ERR_DIR_ALREADY_EXISTING		(13)
#define ERR_FMT_TOO_LOW_VOLUME  		(14)
#define ERR_LFN_BUF_OUT         		(15)
#define ERR_OEM_CHAR_NOT_COMPLETE		(16)
#define ERR_FS_DIR               		(17)
#define ERR_DEVICE_IO            		(18)
#define ERR_MD_POS_OVER_FSIZE    		((u32)(-3))
#define ERR_OVER_FILE_MAX_SIZE   		((u32)(-2))
#define ERR_OVER_DISK_SPACE      		((u32)(-1))

//-----------------------------------------------------------------
// DPT:分区表记录结构如下
//-----------------------------------------------------------------
struct DPT_Item {
	u8 Active;      					//0x80表示此分区有效
	u8 StartHead;   					//分区的开始磁头
	u8 StartSect;   					//开始扇区
	u8 StartCyl;    					//开始柱面
	u8 PartType;    					//分区类型
	u8 EndHead;     					//分区的结束头
	u8 EndSect;     					//结束扇区
	u8 EndCyl;      					//结束柱面
	u8 StartLBA[4]; 					//分区的第一个扇区
	u8 Size[4];     					//分区的大小，总扇区数
};
//-----------------------------------------------------------------
//MBR扇区（绝对0扇区）定义如下
//-----------------------------------------------------------------
struct MBR {
	u8 PartCode[446]; //MBR的引导程序
	struct DPT_Item Part[4]; //4个分区记录
	u8 BootSectSig0;  //55
	u8 BootSectSig1;  //AA
};
//-----------------------------------------------------------------
//FAT中对DBR的定义如下  一共占用90个字节
//-----------------------------------------------------------------
struct DBR {
	u8 BS_jmpBoot[3];     		//跳转指令       				offset: 0
	u8 BS_OEMName[8];     		//OEM名称        				offset: 3
	u8 BPB_BytesPerSec[2];		//每扇区字节数   				offset:11
	u8 BPB_SecPerClus;    		//每簇扇区数     				offset:13
	u8 BPB_RsvdSecCnt[2]; 		//保留扇区数目   				offset:14
	u8 BPB_NumFATs;       		//此卷中FAT表数  				offset:16
	u8 BPB_RootEntCnt[2]; 		//FAT32为0       				offset:17
	u8 BPB_TotSec16[2];   		//FAT32为0       				offset:19
	u8 BPB_Media;         		//存储介质       				offset:21
	u8 BPB_FATSz16[2];    		//FAT32为0       				offset:22
	u8 BPB_SecPerTrk[2];  		//磁道扇区数     				offset:24
	u8 BPB_NumHeads[2];   		//磁头数         				offset:26
	u8 BPB_HiddSec[4];    		//FAT区前隐扇区数				offset:28
	u8 BPB_TotSec32[4];   		//该卷总扇区数   				offset:32
	u8 BPB_FATSz32[4];    		//一个FAT表扇区数				offset:36
	u8 BPB_ExtFlags[2];   		//FAT32特有      				offset:40
	u8 BPB_FSVer[2];      		//FAT32特有      				offset:42
	u8 BPB_RootClus[4];   		//根目录簇号     				offset:44
	u8 FSInfo[2];         		//保留扇区FSINFO扇区数		offset:48
	u8 BPB_BkBootSec[2];  		//通常为6        				offset:50
	u8 BPB_Reserved[12];  		//扩展用         				offset:52
	u8 BS_DrvNum;         		//               				offset:64
	u8 BS_Reserved1;      		//               				offset:65
	u8 BS_BootSig;        		//               				offset:66
	u8 BS_VolID[4];       		//               				offset:67
	u8 BS_FilSysType[11]; 		//	             				offset:71
	u8 BS_FilSysType1[8]; 		//"FAT32    "    				offset:82
};
//-----------------------------------------------------------------
//FAT中对文件目录项(振南叫它FDI)的定义如下  一共占用32个字节
//-----------------------------------------------------------------
struct FDI {
	u8 Name[8];     					//文件名，不足部分以空格补充
	u8 Extension[3];					//扩展名，不足部分以空格补充
	u8 Attributes;  					//文件属性
	u8 LowerCase;   					//0
	u8 CTime10ms;   					//创建时间的10毫秒位
	u8 CTime[2];    					//创建时间
	u8 CDate[2];    					//创建日期
	u8 ADate[2];    					//访问日期
	u8 HighClust[2];					//开始簇的高字
	u8 MTime[2];    					//最近的修改时间
	u8 MDate[2];    					//最近的修改日期
	u8 LowClust[2]; 					//开始簇的低字
	u8 FileSize[4]; 					//文件大小
};
//-----------------------------------------------------------------

//-----------------------------------------------------------------
struct LFN_FDI { 						//长名的文件目录项结构定义
	u8 AttrByte[1];						//属性字节
	u8 Name1[10];  						//第一部分长名
	u8 LFNSign[1]; 						//长名项标志
	u8 Resv[1];    						//保留
	u8 ChkVal[1];  						//检验值，与SFN的绑定校验
	u8 Name2[12];  						//第二部分长名
	u8 StartClu[2];						//取0
	u8 Name3[4];   						//第三部分长名
};
//-----------------------------------------------------------------
// FAT中对文件系统信息结构的定义
//-----------------------------------------------------------------
struct FSInfo {
	u8 Head[4]; //"RRaA"
	u8 Resv1[480];
	u8 Sign[4]; //"rrAa"
	u8 Free_Cluster[4]; //剩余空簇数
	u8 Next_Free_Cluster[4]; //下一空簇参考值
	u8 Resv2[14];
	u8 Tail[2]; //"55 AA"
};

struct FDIesInSEC
{
	struct FDI FDIes[NFDI_PER_SEC]; //扇区中的文件目录项数组
};

struct Date  //用于存储日期信息
{
	u16 year;
	u8 month;
	u8 day;
};

struct Time  //用于存储时间信息
{
	u8 hour;
	u8 min;
	u8 sec;
};

struct DateTime				//日期与时间
{
	struct Date date;		//日期
	struct Time time;		//时间
};

struct FAT_Item							//FAT中对FAT表项的结构定义
{
	u8 Item[NFATITEMBYTES]; //FAT32中FAT表项占用4个字节，即32位
};

struct FAT_Sec  //FAT中对FAT表扇区结构的定义
{
	struct FAT_Item items[NITEMSINFATSEC]; //FAT扇区包含128个FAT表项
	                                //FAT扇区的结构就是有128个FAT表项类型的数组
};

#define DATE_YEAR_BASE 			(1980)

#define TIME_HOUR_MARK 			(0x001F)
#define TIME_MIN_MARK  			(0x002F)
#define TIME_SEC_MARK  			(0x001F)

#define DATE_YEAR_MARK 			(0x007F)
#define DATE_MONTH_MARK			(0x000F)
#define DATE_DAY_MARK  			(0x001F) 

#define TIME_HOUR_NBITS 		(5)
#define TIME_MIN_NBITS  		(6)
#define TIME_SEC_NBITS  		(5)

#define DATE_YEAR_NBITS 		(7)
#define DATE_MONTH_NBITS		(4)
#define DATE_DAY_NBITS  		(5)
//-----------------------------------------------------------------
// FAT初始化时初始参数装入如下结构体中
//-----------------------------------------------------------------
struct FATInfo {
	u32 BPB_Sector_No;   					//BPB所在扇区号
	u32 Total_SizeKB;    					//磁盘的总容量，单位为KB
	u32 BytesPerSector;  					//每个扇区的字节数
	u32 FATsectors;      					//FAT表所占扇区数
	u32 SectorsPerClust; 					//每簇的扇区数
	u32 FirstFATSector;  					//第一个FAT表所在扇区
	u32 FirstDirSector;  					//第一个目录所在扇区
	u32 FSINFO_Sec;      					//FSINFO扇区所在的扇区
	u32 Free_nCluster;   					//空闲簇的个数
	u32 Next_Free_Cluster;				//下一空簇
};
//-----------------------------------------------------------------
// FAT中对文件信息集合的定义
//-----------------------------------------------------------------
struct FileInfo {
	char File_Name[13];      			//完整文件名（主文件名与扩展文件名）
	char File_Attr;          			//文件属性
	struct Time File_CTime;  			//文件创建时间
	struct Date File_CDate;   		//文件创建日期
	//struct Date File_ADate; 		//文件访问日期
	//struct Time File_MTime; 		//文件修改时间
	//struct Date File_MDate; 		//文件修改日期
	u32 File_StartClust;      		//文件开始簇
	u32 File_Size;           			//文件大小
	u32 File_CurClust;						//文件当前簇
	u32 File_CurSec;  						//文件当前扇区
	u16 File_CurPos;  						//文件当前扇区偏移量
	u8 File_IsEOF;     						//文件是否到达结束位置
	u32 File_CurOffset; 					//文件当前偏移量
	u32 FDI_Sec; 									//文件目录项所在的扇区
	u8 nFDI; 											//文件目录项在扇区中的索引

# ifdef USE_LFN 								//如果使用长名，则文件信息集合包含以下两项的下定义 
	u8 have_lfn; 									//表示此文件是否有长名
	u16 longname[MAX_LFN_LEN + 1]; //用于装载长名的UNICODE码，如果实际文件的长名长于MAX_LFN_LEN，则直接截断
#endif

	//----ACCCB相关变量定义-----
#ifndef RT_UPDATE_CLUSTER_CHAIN
# ifdef USE_ALONE_CCCB
	u32 acccb_buf[CCCB_LEN];			//ACCCB的缓冲区，以连续簇段的方式来记录簇链
	u8 acccb_counter;
	u32 acccb_curval;
#endif
#endif
	//----------------------------

# ifdef USE_EXCHANGE_BUFFER
# ifdef USE_ALONE_EXB
	u8 exb_buf[FAT_BUF_SIZE];
	u32 exb_cursec;
#endif
#endif
};
//-----------------------------------------------------------------
//以下是对用户可用的函数的声明
//-----------------------------------------------------------------
u8 FAT_Device_Init();		//存储设备初始化，底层驱动接口 
u8 FAT_Init(); 					//文件系统初始化 
u8 FAT_Select_Device(u8 devno,struct FATInfo * pinitinfo); //在多设备情况下用于选择某一个设备
u32 FAT_ReadData(struct FileInfo * pfi, u32 offset,u32 len, u8 * app_Buffer); //数据读取 
u32 FAT_ReadDataX(struct FileInfo * pfi, u32 offset,u32 len);
u8 FAT_Seek(struct FileInfo * pfi, u32 offset); //文件定位 
u8 FAT_Open_File(struct FileInfo * pfi, char * filepath, u32 n,u8 is_file); //文件打开 
u8 FAT_Create_File(struct FileInfo * pfi, char * pfn,struct DateTime * pdt); //创建文件 
u8 FAT_Create_Dir(char* pdp,struct DateTime * pdt); //创建目录 
u8 FAT_Delete_Dir(char* dirpath); //删除目录 
u8 FAT_Enter_Dir(char* dirpath, u32* pCluster, u32* pos); //进入目录 
u8 FAT_Delete_File(char* filepath); //删除文件 
u8 FAT_Format_FS(u32 tt_sec, u16 clu_sz); //格式化
u32 FAT_WriteData(struct FileInfo * pfi, u32 len, u8* pbuf); //写入数据 
u32 FAT_Modify_Data(struct FileInfo * pfi, u32 offset,u32 len, u8 * app_Buffer); //对文件数据进行修改
u8 FAT_Dump_Data(struct FileInfo * pfi, u32 offset); //截断文件数据
u8 FAT_Close_File(struct FileInfo * pfi); //关闭文件
u8 FAT_Flush_FS(void); //刷新文件系统相关信息
//-----------------------------------------------------------------

#endif