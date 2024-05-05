//-----------------------------------------------------------------
// 名称: FAT驱动程序 (znFAT)
//-----------------------------------------------------------------
# include "fat.h"
# include "template.h"
# include "gb2uni.h"
# include "deviceio.h"
u8 tmpBuf[FAT_BUF_SIZE];
u8* FAT_Buffer = tmpBuf;
//-----------------------------------------------------------------
struct FATInfo *pInitInfo;
extern struct FAT_IO_Ctl ioctl;
u8 Dev_No = 0;
//-----------------------------------------------------------------
struct FileInfo *just_file = (struct FileInfo *)0;
# ifndef RT_UPDATE_CLUSTER_CHAIN 
# ifndef USE_ALONE_CCCB
u32 scccb_buf[CCCB_LEN];
u8 scccb_counter = 0;
u32 scccb_curval = 0;
u8 scccb_curdev = (u8)(-1);
#endif
#endif
# ifndef RT_UPDATE_CLUSTER_CHAIN
# ifndef USE_ALONE_CCCB
u32* pcccb_buf = scccb_buf;
u32* pcccb_curval = &scccb_curval;
u8* pcccb_counter = &scccb_counter;
u8* pcccb_curdev = &scccb_curdev;
struct FileInfo *pcccb_cur_oc = (struct FileInfo *)0;
struct FATInfo *pcccb_cur_initinfo = (struct FATInfo *)0;
#else
u32* pcccb_buf = (u32*)0;
u32* pcccb_curval = (u32*)0;
u8* pcccb_counter = (u8*)0;
#endif
u8 get_next_cluster_in_cccb = 0;
#endif
//------------------EXB相关变量定义-------------------------
# ifdef USE_EXCHANGE_BUFFER
# ifndef USE_ALONE_EXB
//#pragma udata directive
//#pragma udata SEXB_BUF
u8 sexb_buf[FAT_BUF_SIZE];
//#pragma udata
u8 sexb_cur_dev = (u8)(-1);
u32 sexb_cur_sec = 0;
struct FileInfo *psexb_cur_oc = (struct FileInfo *)0;
#endif
#endif

# ifdef USE_EXCHANGE_BUFFER

# ifndef USE_ALONE_EXB
u8* pexb_buf = sexb_buf;
#else
u8* pexb_buf = (u8*)0;
#endif

#endif
//----------------------------------------------------------
u8 Memory_Set(u8* pmem, u32 len, u8 value)
{
	u32 i = 0;
	for (i = 0; i < len; i++)
	{
		pmem[i] = value;
	}
	return 0;
}
u8 Memory_Compare(u8* psmem, u8* pdmem, u32 len)
{
	u32 i = 0;
	for (i = 0; i < len; i++)
	{
		if (psmem[i] != pdmem[i])
		{
			return 0;
		}
	}
	return 1;
}
u8* Memory_Copy(u8* pdmem, u8* psmem, u32 len)
{
	u32 i = 0;
	for (i = 0; i < len; i++)
	{
		pdmem[i] = psmem[i];
	}
	return pdmem;
}
char* StringCopy(char* dest_str, char* src_str)
{
	u8 i = 0;
	while ('\0' != src_str[i])
	{
		dest_str[i] = src_str[i]; i++;
	}
	dest_str[i] = '\0';
	return dest_str;
}

u32 StringLen(char* pstr)
{
	u32 len = 0;
	while ('\0' != pstr[len])
	{
		len++;
	}
	return len;
}

u32 WStringLen(u16* str)
{
	u32 i = 0;
	while (0 != str[i])
	{
		i++;
	}
	return i;
}

u8 PGM_BYTE_FUN(ROM_TYPE_UINT8* ptr)
{
	return *(ptr);
}

u16 PGM_WORD_FUN(ROM_TYPE_UINT16* ptr)
{
	return *(ptr);
}

u32 PGM_DWORD_FUN(ROM_TYPE_UINT32* ptr)
{
	return *(ptr);
}

u8* PGM2RAM(u8* pdmem, ROM_TYPE_UINT8* psmem, u32 len)
{
	u32 i = 0;
	for (i = 0; i < len; i++)
	{
		pdmem[i] = PGM_BYTE_FUN((psmem + i));
	}
	return pdmem;
}
//-----------------------------------------------------------------
// 选定一个存储设备
//-----------------------------------------------------------------
u8 FAT_Select_Device(u8 devno,struct FATInfo *pinitinfo) {
	pInitInfo = pinitinfo;
	Dev_No = devno;
	return 0;
}
//-----------------------------------------------------------------
// Bytes2Value
//-----------------------------------------------------------------
u32 Bytes2Value(u8* dat, u8 len)
{
	u32 temp = 0;
	if (len >= 1) temp |= ((u32)(dat[0]));
	if (len >= 2) temp |= ((u32)(dat[1])) << 8;
	if (len >= 3) temp |= ((u32)(dat[2])) << 16;
	if (len >= 4) temp |= ((u32)(dat[3])) << 24;
	return temp;
}
//-----------------------------------------------------------------
// 查找FSINFO扇区的物理地址
//-----------------------------------------------------------------
u8 Find_FSINFO_Sec(u32* fsinfosec)
{
	u32 iSec = 0;
	struct FSInfo *pfsinfo;
u8 head[4] = { 'R', 'R', 'a', 'A' };
u8 sign[4] = { 'r', 'r', 'A', 'a' };
for (iSec = (pInitInfo->BPB_Sector_No + 1); iSec < (pInitInfo->FirstFATSector); iSec++)
{
	FAT_Device_Read_Sector(iSec, FAT_Buffer);
	pfsinfo = ((struct FSInfo *)FAT_Buffer);
if (Memory_Compare(pfsinfo->Head, head, 4)
	&& Memory_Compare(pfsinfo->Sign, sign, 4))
{
	*fsinfosec = iSec;
	return ERR_SUCC;
}
	}
	return ERR_FAIL;
}
//-----------------------------------------------------------------
// 从FAT表的最头上开始查找可用的空簇，即找到第一个可用空簇
//-----------------------------------------------------------------
u8 Search_Free_Cluster_From_Start(u32* nFreeCluster)
{
	u32 iSec = 0;
	u8 iItem = 0;
	struct FAT_Sec *pFAT_Sec;
for (iSec = 0; iSec < pInitInfo->FATsectors; iSec++)
{
	FAT_Device_Read_Sector(pInitInfo->FirstFATSector + iSec, FAT_Buffer);
	pFAT_Sec = (struct FAT_Sec *)FAT_Buffer;
for (iItem = 0; iItem < NITEMSINFATSEC; iItem++)
{
	if ((0 == (((pFAT_Sec->items[iItem]).Item)[0])) && (0 == (((pFAT_Sec->items[iItem]).Item)[1])) &&
		 (0 == (((pFAT_Sec->items[iItem]).Item)[2])) && (0 == (((pFAT_Sec->items[iItem]).Item)[3])))
	{
		*nFreeCluster = ((iSec * NITEMSINFATSEC) + (u32)iItem);
		return ERR_SUCC;
	}
}
	}
	return ERR_FAIL;
}
//-----------------------------------------------------------------
// 更新FSINFO扇区参数
//-----------------------------------------------------------------
#ifdef UPDATE_FSINFO
u8 Update_FSINFO(void)
{
	struct FSInfo *pfsinfo;
FAT_Device_Read_Sector(pInitInfo->FSINFO_Sec, FAT_Buffer);
pfsinfo = ((struct FSInfo *)FAT_Buffer);
//写入剩余空簇数
pfsinfo->Free_Cluster[0] = (u8)(pInitInfo->Free_nCluster & 0X000000FF);
pfsinfo->Free_Cluster[1] = (u8)((pInitInfo->Free_nCluster & 0X0000FF00) >> 8);
pfsinfo->Free_Cluster[2] = (u8)((pInitInfo->Free_nCluster & 0X00FF0000) >> 16);
pfsinfo->Free_Cluster[3] = (u8)((pInitInfo->Free_nCluster & 0XFF000000) >> 24);
//写入下一空闲簇参考值，并无多大意义
pfsinfo->Next_Free_Cluster[0] = (u8)(pInitInfo->Next_Free_Cluster & 0X000000FF);
pfsinfo->Next_Free_Cluster[1] = (u8)((pInitInfo->Next_Free_Cluster & 0X0000FF00) >> 8);
pfsinfo->Next_Free_Cluster[2] = (u8)((pInitInfo->Next_Free_Cluster & 0X00FF0000) >> 16);
pfsinfo->Next_Free_Cluster[3] = (u8)((pInitInfo->Next_Free_Cluster & 0XFF000000) >> 24);
FAT_Device_Write_Sector(pInitInfo->FSINFO_Sec, FAT_Buffer);
return 0;
}
#endif
//-----------------------------------------------------------------
// FAT中的文件系统初始化函数
//-----------------------------------------------------------------
u8 FAT_Init()
{
	struct DBR *pdbr;
u8 dm[3] = DBR_MARK;
FAT_Device_Read_Sector(MBR_SECTOR, FAT_Buffer);
if (!(FAT_Buffer[0] == dm[0] && FAT_Buffer[1] == dm[1] && FAT_Buffer[2] == dm[2]))
{
	pInitInfo->BPB_Sector_No = Bytes2Value(((((struct MBR *)(FAT_Buffer))->Part[0]).StartLBA),4);
	}
	else
{
	pInitInfo->BPB_Sector_No = 0;
}
FAT_Device_Read_Sector((pInitInfo->BPB_Sector_No), FAT_Buffer);

pdbr = (struct DBR *)FAT_Buffer;
if (!IS_FAT32_TYPE((pdbr->BS_FilSysType1))) return FSTYPE_NOT_FAT32;
pInitInfo->BytesPerSector = Bytes2Value((pdbr->BPB_BytesPerSec), 2);
pInitInfo->FATsectors = Bytes2Value((pdbr->BPB_FATSz32), 4);
pInitInfo->SectorsPerClust = pdbr->BPB_SecPerClus;
pInitInfo->FirstFATSector = Bytes2Value((pdbr->BPB_RsvdSecCnt), 2) + pInitInfo->BPB_Sector_No;
pInitInfo->FirstDirSector = (pInitInfo->FirstFATSector) + (pdbr->BPB_NumFATs) * (pInitInfo->FATsectors);
pInitInfo->Total_SizeKB = Bytes2Value((pdbr->BPB_TotSec32), 4) / 2;
if (Find_FSINFO_Sec(&(pInitInfo->FSINFO_Sec)))
{
	return ERR_FAIL;
}
FAT_Device_Read_Sector((pInitInfo->FSINFO_Sec), FAT_Buffer);
pInitInfo->Free_nCluster = Bytes2Value(((struct FSInfo *)FAT_Buffer)->Free_Cluster,4);
if (0XFFFFFFFF == pInitInfo->Free_nCluster)
{
	pInitInfo->Free_nCluster = (((pInitInfo->Total_SizeKB * 2) - (pInitInfo->FirstDirSector)) / (pInitInfo->SectorsPerClust)) - 1;
}
if (Search_Free_Cluster_From_Start(&(pInitInfo->Next_Free_Cluster)))
{
	return ERR_FAIL;
}

# ifdef RT_UPDATE_FSINFO 
Update_FSINFO();
#endif

# ifndef RT_UPDATE_CLUSTER_CHAIN
# ifndef USE_ALONE_CCCB
Memory_Set((u8*)pcccb_buf, sizeof(u32) * CCCB_LEN, 0);
#endif
#endif

# ifdef USE_EXCHANGE_BUFFER
# ifndef USE_ALONE_EXB
Memory_Set(pexb_buf, 512, 0);
#endif
#endif
return ERR_SUCC;
}

#ifndef RT_UPDATE_CLUSTER_CHAIN

#ifdef USE_ALONE_CCCB
u8 CCCB_To_Alone(void)
{
	pcccb_buf = (just_file->acccb_buf);
	pcccb_curval = &(just_file->acccb_curval);
	pcccb_counter = &(just_file->acccb_counter);
	return 0;
}
#endif
//-----------------------------------------------------------------
// 获取下一簇
//-----------------------------------------------------------------
u32 CCCB_Get_Next_Cluster(u32 cluster)
{
	u32 pos = CCCB_LEN - 1;
	u32 i = 0, temp = 0;
	if (pcccb_buf == (u32*)0) return 0;
	if (0 == pcccb_buf[0]) return 0;
# ifndef USE_ALONE_CCCB
	if (Dev_No != (*pcccb_curdev)) return 0;
	if (just_file != pcccb_cur_oc) return 0;
#endif

	while (0 == pcccb_buf[pos]) pos--;
	if (cluster >= pcccb_buf[pos] && cluster <= (*pcccb_curval))
	{
		if (cluster == (*pcccb_curval)) return 0X0FFFFFFF;
		if (cluster == pcccb_buf[pos])
		{
			if (pcccb_buf[pos] == (*pcccb_curval)) return 0X0FFFFFFF;
		}
		return (cluster + 1);
	}

	temp = pos / 2;
	for (i = 0; i < temp; i++)
	{
		if (cluster >= pcccb_buf[2 * i] && cluster <= pcccb_buf[2 * i + 1])
		{
			if (cluster == pcccb_buf[2 * i + 1]) return pcccb_buf[2 * i + 2];
			if (cluster == pcccb_buf[2 * i])
			{
				if (pcccb_buf[2 * i] == pcccb_buf[2 * i + 1]) return pcccb_buf[2 * i + 2];
			}
			return (cluster + 1);
		}
	}
	return 0;
}
//-----------------------------------------------------------------
// 更新FAT表
//-----------------------------------------------------------------
u8 CCCB_Update_FAT()
{
	u32 i = 0, j = 0, temp = 0, temp1 = 0;
	u32 old_clu = 0, cur_clu = 0, clu_sec = 0;
# ifndef USE_ALONE_CCCB
	u8 old_devno = Dev_No;
	struct FATInfo *old_pinit_args = pInitInfo;
#endif

struct FAT_Sec *pFAT_Sec = (struct FAT_Sec *)FAT_Buffer;

if (pcccb_buf == (u32*)0) return 0;

if (0 == pcccb_buf[0]) return 0;

# ifndef USE_ALONE_CCCB
Dev_No = (*pcccb_curdev); pInitInfo = pcccb_cur_initinfo;
#endif

old_clu = cur_clu = pcccb_buf[0];
clu_sec = (old_clu / NITEMSINFATSEC);
FAT_Device_Read_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);

pcccb_buf[(*pcccb_counter)] = (*pcccb_curval);

temp1 = ((*pcccb_counter) + 1) / 2;
for (i = 0; i < temp1;)
{
	for (j = pcccb_buf[2 * i] + 1; j <= pcccb_buf[2 * i + 1]; j++)
	{
		cur_clu++;
		if (clu_sec != (old_clu / NITEMSINFATSEC))
		{
			FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
			FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);

			clu_sec = (old_clu / NITEMSINFATSEC);
			FAT_Device_Read_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
		}

		temp = (u8)(old_clu % NITEMSINFATSEC);
		(((pFAT_Sec->items)[temp]).Item)[0] = (u8)(cur_clu & 0X000000FF);
		(((pFAT_Sec->items)[temp]).Item)[1] = (u8)((cur_clu & 0X0000FF00) >> 8);
		(((pFAT_Sec->items)[temp]).Item)[2] = (u8)((cur_clu & 0X00FF0000) >> 16);
		(((pFAT_Sec->items)[temp]).Item)[3] = (u8)((cur_clu & 0XFF000000) >> 24);

		old_clu = cur_clu;
	}

	cur_clu = ((i == (temp1 - 1)) ? (0X0FFFFFFF) : (pcccb_buf[2 * i + 2]));

	if (clu_sec != (old_clu / NITEMSINFATSEC))
	{
		FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
		FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);

		clu_sec = (old_clu / NITEMSINFATSEC);
		FAT_Device_Read_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
	}

	temp = (u8)(old_clu % NITEMSINFATSEC);
	(((pFAT_Sec->items)[temp]).Item)[0] = (u8)(cur_clu & 0X000000FF);
	(((pFAT_Sec->items)[temp]).Item)[1] = (u8)((cur_clu & 0X0000FF00) >> 8);
	(((pFAT_Sec->items)[temp]).Item)[2] = (u8)((cur_clu & 0X00FF0000) >> 16);
	(((pFAT_Sec->items)[temp]).Item)[3] = (u8)((cur_clu & 0XFF000000) >> 24);

	old_clu = cur_clu;
	i++;
}
FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);

Memory_Set((u8*)pcccb_buf, sizeof(u32) * CCCB_LEN, 0);
(*pcccb_counter) = 0;

# ifndef USE_ALONE_CCCB
pcccb_cur_oc = (struct FileInfo *)0;
*pcccb_curdev = (u8)(-1);
pcccb_cur_initinfo = (struct FATInfo *)0;

Dev_No = old_devno; pInitInfo = old_pinit_args;
#endif

return 0;
}
#endif

//-----------------------------------------------------------------
// 获取下一簇
//-----------------------------------------------------------------
#ifdef GET_NEXT_CLUSTER 
u32 Get_Next_Cluster(u32 cluster)
{
	u32 clu_sec = 0;
	struct FAT_Sec *pFAT_Sec;
struct FAT_Item *pFAT_Item;

# ifndef RT_UPDATE_CLUSTER_CHAIN
u32 next_clu = 0;
#endif

# ifndef RT_UPDATE_CLUSTER_CHAIN 
if (0 != get_next_cluster_in_cccb)
{
	next_clu = CCCB_Get_Next_Cluster(cluster);
	if (0 != next_clu) return next_clu;
}
#endif

clu_sec = (cluster / NITEMSINFATSEC) + (pInitInfo->FirstFATSector);
FAT_Device_Read_Sector(clu_sec, FAT_Buffer);

pFAT_Sec = (struct FAT_Sec *)FAT_Buffer;

pFAT_Item = &((pFAT_Sec->items)[cluster % NITEMSINFATSEC]);

return Bytes2Value((u8*)pFAT_Item, NFATITEMBYTES);
}
#endif
//-----------------------------------------------------------------
// 文件数据定位
//-----------------------------------------------------------------
#ifdef FAT_SEEK
u8 FAT_Seek(struct FileInfo *pfi, u32 offset){
	u32 Cluster_Size = ((pInitInfo->SectorsPerClust) * (pInitInfo->BytesPerSector)); //计算簇的总字节数据，以免后面重复计算
	u32 temp = 0, temp1 = 0, temp2 = 0, len = 0, k = 0, ncluster = 0, have_read = 0;

	just_file = pfi;

# ifndef RT_UPDATE_CLUSTER_CHAIN
	get_next_cluster_in_cccb = 1;
# ifdef USE_ALONE_CCCB
	CCCB_To_Alone();
#endif
#endif

	if (offset < (pfi->File_Size))
	{
		pfi->File_IsEOF = BOOL_FALSE;
	}

	if (offset == (pfi->File_CurOffset)) return 0;

	if (offset < (pfi->File_CurOffset))
	{
		pfi->File_CurClust = pfi->File_StartClust;
		pfi->File_CurSec = SOC(pfi->File_CurClust);
		pfi->File_CurPos = 0;
		pfi->File_CurOffset = 0;
		pfi->File_IsEOF = BOOL_FALSE;
	}

	len = offset - (pfi->File_CurOffset);

	if (offset >= (pfi->File_Size))
	{
		len = (pfi->File_Size - pfi->File_CurOffset);
		pfi->File_IsEOF = BOOL_TRUE;
	}

	//=================================================================== 
	if ((pfi->File_CurOffset % Cluster_Size) != 0)
	{
		if (len <= (pInitInfo->BytesPerSector - pfi->File_CurPos))
		{
			if ((pInitInfo->BytesPerSector - pfi->File_CurPos) == len)
			{
				if (IS_END_SEC_OF_CLU(pfi->File_CurSec, pfi->File_CurClust))
				{
					if (!pfi->File_IsEOF)
					{
						pfi->File_CurClust = Get_Next_Cluster(pfi->File_CurClust);
					}
					pfi->File_CurSec = SOC(pfi->File_CurClust);
				}
				else
				{
					pfi->File_CurSec++;
				}
				pfi->File_CurPos = 0;
			}
			else
			{
				pfi->File_CurPos += ((u16)len);
			}
			pfi->File_CurOffset += len;

			return NUL_RET;
		}
		else
		{
			temp = (pInitInfo->BytesPerSector - pfi->File_CurPos);
			have_read += temp;
			if (!(IS_END_SEC_OF_CLU(pfi->File_CurSec, pfi->File_CurClust)))
			{
				pfi->File_CurSec++;
				pfi->File_CurPos = 0;

				temp2 = (len - have_read);
				temp1 = ((LAST_SEC_OF_CLU(pfi->File_CurClust) - (pfi->File_CurSec - 1)) * (pInitInfo->BytesPerSector));
				if (temp2 <= temp1)
				{
					temp = temp2 / (pInitInfo->BytesPerSector);
					have_read += ((pInitInfo->BytesPerSector) * temp);

					if (temp2 == temp1)
					{
						if (!pfi->File_IsEOF)
						{
							pfi->File_CurClust = Get_Next_Cluster(pfi->File_CurClust);
						}
						pfi->File_CurSec = SOC(pfi->File_CurClust);
						pfi->File_CurPos = 0;
					}
					else
					{
						pfi->File_CurSec += temp;
						pfi->File_CurPos = (u16)(len - have_read);
					}
					pfi->File_CurOffset += len;

					return NUL_RET;
				}
				else
				{
					temp = LAST_SEC_OF_CLU(pfi->File_CurClust) - (pfi->File_CurSec) + 1;
					have_read += ((pInitInfo->BytesPerSector) * temp);
				}
			}

			pfi->File_CurClust = Get_Next_Cluster(pfi->File_CurClust);
			pfi->File_CurSec = SOC(pfi->File_CurClust);
			pfi->File_CurPos = 0;
		}
	}

	if (len - have_read > 0)
	{
		ncluster = (len - have_read) / Cluster_Size;

		for (k = 0; k < ncluster; k++)
		{
			have_read += (Cluster_Size);
			if (!((len - have_read) == 0 && pfi->File_IsEOF))
			{
				pfi->File_CurClust = Get_Next_Cluster(pfi->File_CurClust);
			}
		}

		pfi->File_CurSec = SOC(pfi->File_CurClust);
		if (len - have_read > 0)
		{
			temp = (len - have_read) / (pInitInfo->BytesPerSector);
			have_read += ((pInitInfo->BytesPerSector) * temp);

			pfi->File_CurSec += temp;
			if (len - have_read > 0)
			{
				pfi->File_CurPos = (u16)(len - have_read);
			}
		}
	}

	pfi->File_CurOffset += len;

	return 0;
}
#endif
//-----------------------------------------------------------------
// 文件数据读取
//-----------------------------------------------------------------
# ifdef FAT_READDATA 
u32 FAT_ReadData(struct FileInfo *pfi, u32 offset, u32 len, u8 * app_Buffer){
	u32 Cluster_Size = 0, iClu = 0, next_clu = 0, start_clu = 0, end_clu = 0;
	u32 temp = 0, temp1 = 0, temp2 = 0, ncluster = 0, have_read = 0;

	just_file = pfi;

# ifndef RT_UPDATE_CLUSTER_CHAIN
	get_next_cluster_in_cccb = 1;
# ifdef USE_ALONE_CCCB
	CCCB_To_Alone();
#endif
#endif

	FAT_Seek(pfi, offset);

	if (0 == len) return 0;

	Cluster_Size = (pInitInfo->SectorsPerClust * pInitInfo->BytesPerSector);

	if ((pfi->File_CurOffset + len) >= (pfi->File_Size))
	{
		len = (pfi->File_Size - pfi->File_CurOffset);
		pfi->File_IsEOF = BOOL_TRUE;
	}
	if ((pfi->File_CurOffset % Cluster_Size) != 0)
	{
		FAT_Device_Read_Sector(pfi->File_CurSec, FAT_Buffer);

		temp = pInitInfo->BytesPerSector - pfi->File_CurPos;

		if (len <= temp)
		{
			Memory_Copy(app_Buffer, FAT_Buffer + (pfi->File_CurPos), len);
			if (temp == len)
			{
				if (IS_END_SEC_OF_CLU(pfi->File_CurSec, pfi->File_CurClust))
				{
					if (!pfi->File_IsEOF)
					{
						pfi->File_CurClust = Get_Next_Cluster(pfi->File_CurClust);
					}
					pfi->File_CurSec = SOC(pfi->File_CurClust);
				}
				else
				{
					pfi->File_CurSec++;
				}
				pfi->File_CurPos = 0;
			}
			else
			{
				pfi->File_CurPos += (u16)len;
			}
			pfi->File_CurOffset += len;

			return len;
		}

		else
		{
			temp = (pInitInfo->BytesPerSector - pfi->File_CurPos);

			Memory_Copy(app_Buffer, FAT_Buffer + (pfi->File_CurPos), temp);
			have_read += temp;

			if (!(IS_END_SEC_OF_CLU(pfi->File_CurSec, pfi->File_CurClust)))
			{
				pfi->File_CurSec++;
				pfi->File_CurPos = 0;

				temp2 = (len - have_read);
				temp1 = ((LAST_SEC_OF_CLU(pfi->File_CurClust) - (pfi->File_CurSec - 1)) * (pInitInfo->BytesPerSector));
				if (temp2 <= temp1)
				{
					temp = temp2 / (pInitInfo->BytesPerSector);

					FAT_Device_Read_nSector(temp, pfi->File_CurSec, app_Buffer + have_read);
					have_read += ((pInitInfo->BytesPerSector) * temp);

					if (temp2 == temp1)
					{
						if (!pfi->File_IsEOF)
						{
							pfi->File_CurClust = Get_Next_Cluster(pfi->File_CurClust);
						}
						pfi->File_CurSec = SOC(pfi->File_CurClust);
						pfi->File_CurPos = 0;
					}
					else
					{
						pfi->File_CurSec += temp;
						temp = len - have_read;

						FAT_Device_Read_Sector(pfi->File_CurSec, FAT_Buffer);
						Memory_Copy(app_Buffer + have_read, FAT_Buffer, temp);
						pfi->File_CurPos = (u16)temp;

					}
					pfi->File_CurOffset += len;

					return len;
				}
				else
				{
					temp = (LAST_SEC_OF_CLU(pfi->File_CurClust)) - (pfi->File_CurSec) + 1;

					FAT_Device_Read_nSector(temp, (pfi->File_CurSec), app_Buffer + have_read);
					have_read += ((pInitInfo->BytesPerSector) * temp);
				}
			}

			pfi->File_CurClust = Get_Next_Cluster(pfi->File_CurClust);
			pfi->File_CurSec = SOC(pfi->File_CurClust);
			pfi->File_CurPos = 0;
		}
	}

	temp1 = len - have_read;
	ncluster = temp1 / Cluster_Size;
	if (ncluster > 0)
	{

		start_clu = end_clu = pfi->File_CurClust;

		for (iClu = 1; iClu < ncluster; iClu++)
		{
			next_clu = Get_Next_Cluster(end_clu);
			if ((next_clu - 1) == end_clu)
			{
				end_clu = next_clu;
			}
			else
			{
				FAT_Device_Read_nSector(((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust)), SOC(start_clu), app_Buffer + have_read);
				have_read += ((end_clu - start_clu + 1) * Cluster_Size);
				start_clu = end_clu = next_clu;
			}
		}


		temp = temp1 % Cluster_Size;
		if (temp > 0)
		{
			temp = temp / (pInitInfo->BytesPerSector);



			next_clu = Get_Next_Cluster(end_clu);
			if ((next_clu - 1) == end_clu)
			{
				FAT_Device_Read_nSector(((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust) + temp), SOC(start_clu), app_Buffer + have_read);
				have_read += ((pInitInfo->BytesPerSector) * ((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust) + temp));
			}
			else
			{
				FAT_Device_Read_nSector(((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust)), SOC(start_clu), app_Buffer + have_read);
				have_read += (Cluster_Size * (end_clu - start_clu + 1));
				FAT_Device_Read_nSector(temp, SOC(next_clu), app_Buffer + have_read);
				have_read += (temp * (pInitInfo->BytesPerSector));
			}

			pfi->File_CurClust = next_clu;
			pfi->File_CurSec = (SOC(next_clu) + temp);

			temp = len - have_read;
			if (temp > 0)
			{
				FAT_Device_Read_Sector(pfi->File_CurSec, FAT_Buffer);
				Memory_Copy(app_Buffer + have_read, FAT_Buffer, temp);

				pfi->File_CurPos = (u16)temp;
			}

		}
		else
		{
			FAT_Device_Read_nSector(((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust)), SOC(start_clu), app_Buffer + have_read);

			pfi->File_CurClust = end_clu;
			if (!pfi->File_IsEOF)
			{
				pfi->File_CurClust = Get_Next_Cluster(end_clu);
			}
			pfi->File_CurSec = SOC(pfi->File_CurClust);
		}
	}
	else
	{
		temp = temp1 / (pInitInfo->BytesPerSector);
		FAT_Device_Read_nSector(temp, SOC(pfi->File_CurClust), app_Buffer + have_read);
		have_read += temp * (pInitInfo->BytesPerSector);

		pfi->File_CurSec += temp;

		temp = temp1 % (pInitInfo->BytesPerSector);
		if (temp > 0)
		{
			FAT_Device_Read_Sector(pfi->File_CurSec, FAT_Buffer);
			Memory_Copy(app_Buffer + have_read, FAT_Buffer, temp);

			pfi->File_CurPos = (u16)temp;
		}
	}
	pfi->File_CurOffset += len;

	return len;
}
#endif
//-----------------------------------------------------------------
// 文件数据读取+数据重定向 
//-----------------------------------------------------------------
# ifdef FAT_READDATAX 
u32 FAT_ReadDataX(struct FileInfo *pfi, u32 offset, u32 len) {
	u32 Cluster_Size = 0, iClu = 0, iSec = 0, next_clu = 0, start_clu = 0, end_clu = 0;
	u32 temp = 0, temp1 = 0, temp2 = 0, k = 0, ncluster = 0, have_read = 0;
	u32 i = 0;

	just_file = pfi;

# ifndef RT_UPDATE_CLUSTER_CHAIN
	get_next_cluster_in_cccb = 1;
# ifdef USE_ALONE_CCCB
	CCCB_To_Alone();
#endif
#endif

	FAT_Seek(pfi, offset);

	Cluster_Size = (pInitInfo->SectorsPerClust * pInitInfo->BytesPerSector);
	if ((pfi->File_CurOffset + len) >= (pfi->File_Size))
	{
		len = (pfi->File_Size - pfi->File_CurOffset);
		pfi->File_IsEOF = BOOL_TRUE;
	}

	if ((pfi->File_CurOffset % Cluster_Size) != 0)
	{
		FAT_Device_Read_Sector(pfi->File_CurSec, FAT_Buffer);

		temp = pInitInfo->BytesPerSector - pfi->File_CurPos;
		if (len <= temp)
		{
			for (i = 0; i < len; i++)
			{
				Data_Redirect(FAT_Buffer[i + (pfi->File_CurPos)]);
			}

			if (temp == len)
			{
				if (IS_END_SEC_OF_CLU(pfi->File_CurSec, pfi->File_CurClust))
				{
					if (!pfi->File_IsEOF)
					{
						pfi->File_CurClust = Get_Next_Cluster(pfi->File_CurClust);
					}
					pfi->File_CurSec = SOC(pfi->File_CurClust);
				}
				else
				{
					pfi->File_CurSec++;
				}
				pfi->File_CurPos = 0;
			}
			else
			{
				pfi->File_CurPos += (u16)len;
			}
			pfi->File_CurOffset += len;

			return len;
		}

		else
		{
			temp = (pInitInfo->BytesPerSector - pfi->File_CurPos);

			for (i = 0; i < temp; i++)
			{
				Data_Redirect(FAT_Buffer[i + (pfi->File_CurPos)]);
			}

			have_read += temp;

			if (!(IS_END_SEC_OF_CLU(pfi->File_CurSec, pfi->File_CurClust)))
			{
				pfi->File_CurSec++;
				pfi->File_CurPos = 0;

				temp2 = (len - have_read);
				temp1 = ((LAST_SEC_OF_CLU(pfi->File_CurClust) - (pfi->File_CurSec - 1)) * (pInitInfo->BytesPerSector));
				if (temp2 <= temp1)
				{
					temp = temp2 / (pInitInfo->BytesPerSector);

					for (iSec = 0; iSec < temp; iSec++)
					{
						FAT_Device_Read_Sector(pfi->File_CurSec + iSec, FAT_Buffer);
						for (i = 0; i < (pInitInfo->BytesPerSector); i++)
						{
							Data_Redirect(FAT_Buffer[i]);
						}
					}

					have_read += temp * (pInitInfo->BytesPerSector);

					if (temp2 == temp1)
					{
						if (!pfi->File_IsEOF)
						{
							pfi->File_CurClust = Get_Next_Cluster(pfi->File_CurClust);
						}
						pfi->File_CurSec = SOC(pfi->File_CurClust);
						pfi->File_CurPos = 0;
					}
					else
					{
						pfi->File_CurSec += temp;
						temp = len - have_read;

						FAT_Device_Read_Sector(pfi->File_CurSec, FAT_Buffer);
						for (i = 0; i < temp; i++)
						{
							Data_Redirect(FAT_Buffer[i]);
						}
						pfi->File_CurPos = (u16)temp;

					}
					pfi->File_CurOffset += len;

					return len;
				}
				else
				{
					temp = (LAST_SEC_OF_CLU(pfi->File_CurClust)) - (pfi->File_CurSec) + 1;

					for (iSec = 0; iSec < temp; iSec++)
					{
						FAT_Device_Read_Sector(pfi->File_CurSec + iSec, FAT_Buffer);
						for (i = 0; i < (pInitInfo->BytesPerSector); i++)
						{
							Data_Redirect(FAT_Buffer[i]);
						}
					}
					have_read += temp * (pInitInfo->BytesPerSector);
				}
			}
			pfi->File_CurClust = Get_Next_Cluster(pfi->File_CurClust);
			pfi->File_CurSec = SOC(pfi->File_CurClust);
			pfi->File_CurPos = 0;
		}
	}

	temp1 = len - have_read;
	ncluster = temp1 / Cluster_Size;

	if (ncluster > 0)
	{
		start_clu = end_clu = pfi->File_CurClust;

		for (iClu = 1; iClu < ncluster; iClu++)
		{
			next_clu = Get_Next_Cluster(end_clu);
			if ((next_clu - 1) == end_clu)
			{
				end_clu = next_clu;
			}
			else
			{
				temp = ((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust));
				for (iSec = 0; iSec < temp; iSec++)
				{
					FAT_Device_Read_Sector(SOC(start_clu) + iSec, FAT_Buffer);
					for (i = 0; i < (pInitInfo->BytesPerSector); i++)
					{
						Data_Redirect(FAT_Buffer[i]);
					}
				}
				have_read += temp * (pInitInfo->BytesPerSector);
				start_clu = end_clu = next_clu;
			}
		}

		temp = temp1 % Cluster_Size;
		if (temp > 0)
		{
			temp = temp / (pInitInfo->BytesPerSector);
			next_clu = Get_Next_Cluster(end_clu);
			if ((next_clu - 1) == end_clu)
			{
				temp2 = ((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust) + temp);
				for (iSec = 0; iSec < temp2; iSec++)
				{
					FAT_Device_Read_Sector(SOC(start_clu) + iSec, FAT_Buffer);

					for (i = 0; i < (pInitInfo->BytesPerSector); i++)
					{
						Data_Redirect(FAT_Buffer[i]);
					}
				}
			}
			else
			{
				temp2 = ((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust));
				for (iSec = 0; iSec < temp2; iSec++)
				{
					FAT_Device_Read_Sector(SOC(start_clu) + iSec, FAT_Buffer);

					for (i = 0; i < (pInitInfo->BytesPerSector); i++)
					{
						Data_Redirect(FAT_Buffer[i]);
					}
				}

				for (iSec = 0; iSec < temp; iSec++)
				{
					FAT_Device_Read_Sector(SOC(next_clu) + iSec, FAT_Buffer);

					for (i = 0; i < (pInitInfo->BytesPerSector); i++)
					{
						Data_Redirect(FAT_Buffer[i]);
					}
				}
			}

			have_read += ((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust) + temp) * (pInitInfo->BytesPerSector);

			pfi->File_CurClust = next_clu;
			pfi->File_CurSec = (SOC(next_clu) + temp);

			//----------------------------以上处理整扇区数据----------------------------------------
			temp = len - have_read;
			if (temp > 0)
			{
				FAT_Device_Read_Sector(pfi->File_CurSec, FAT_Buffer);

				for (i = 0; i < temp; i++)
				{
					Data_Redirect(FAT_Buffer[i]);
				}

				pfi->File_CurPos = (u16)temp;
			}
		}
		else
		{
			temp2 = ((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust));
			for (iSec = 0; iSec < temp2; iSec++)
			{
				FAT_Device_Read_Sector(SOC(start_clu) + iSec, FAT_Buffer);
				for (i = 0; i < (pInitInfo->BytesPerSector); i++)
				{
					Data_Redirect(FAT_Buffer[i]);
				}
			}

			pfi->File_CurClust = end_clu;
			if (!pfi->File_IsEOF)
			{
				pfi->File_CurClust = Get_Next_Cluster(end_clu);
			}
			pfi->File_CurSec = SOC(pfi->File_CurClust);
		}
	}
	else
	{
		temp = temp1 / (pInitInfo->BytesPerSector);
		for (iSec = 0; iSec < temp; iSec++)
		{
			FAT_Device_Read_Sector(SOC(pfi->File_CurClust) + iSec, FAT_Buffer);
			for (i = 0; i < (pInitInfo->BytesPerSector); i++)
			{
				Data_Redirect(FAT_Buffer[i]);
			}
		}

		pfi->File_CurSec += temp;

		temp = temp1 % (pInitInfo->BytesPerSector);
		if (temp > 0)
		{
			FAT_Device_Read_Sector(pfi->File_CurSec, FAT_Buffer);
			for (i = 0; i < temp; i++)
			{
				Data_Redirect(FAT_Buffer[i]);
			}

			pfi->File_CurPos = temp;
		}
	}

	pfi->File_CurOffset += len;
	return len;
}
#endif

//-----------------------------------------------------------------
// 检查文件名非法字符
//-----------------------------------------------------------------
# ifdef CHECK_ILLEGAL_CHAR
u8 Check_Illegal_Char(char* pfn)
{
	u32 i = 0;
	while (pfn[i])
	{
		if (('\\' == pfn[i]) || ('/' == pfn[i]) || (':' == pfn[i])
		 || /*('*'==pfn[i]) || ('?'==pfn[i]) ||*/ ('"' == pfn[i])
		 || ('<' == pfn[i]) || ('>' == pfn[i]) || ('|' == pfn[i]))
			return ERR_FAIL;
		i++;
	}
	return ERR_SUCC;
}
#endif

//-----------------------------------------------------------------
// 检查文件名特殊字符，+[],;=space
//-----------------------------------------------------------------
# ifdef CHECK_SFN_SPECIAL_CHAR
u8 Check_SFN_Special_Char(char* pfn)
{
	u32 i = 0;
	u32 pos = (StringLen(pfn) - 1);
	while (' ' == pfn[pos]) pos--;
	while (i <= pos)
	{
		if (('+' == pfn[i]) || ('[' == pfn[i])
		 || (']' == pfn[i]) || (',' == pfn[i])
		 || (' ' == pfn[i]) || (';' == pfn[i])
		 || ('=' == pfn[i]))
			return ERR_FAIL;
		i++;
	}
	return ERR_SUCC;
}
#endif
//-----------------------------------------------------------------
// 检查文件名中的.
//-----------------------------------------------------------------
# ifdef CHECK_SFN_DOT
u8 Check_SFN_Dot(char* pfn)
{
	u32 pos = (StringLen(pfn) - 1);
	u32 dot_counter = 0;
	if ('.' == pfn[0]) return ERR_FAIL;
	while (pos > 0)
	{
		if ('.' == pfn[pos])
		{
			dot_counter++;
		}
		pos--;
	}
	if (dot_counter > 1) return ERR_FAIL;
	else return ERR_SUCC;
}
#endif
//-----------------------------------------------------------------
// 检查文件名的大小写
//-----------------------------------------------------------------
# ifdef CHECK_SFN_ILLEGAL_LOWER
u8 Check_SFN_Illegal_Lower(char* pfn)
{
	u32 i = (StringLen(pfn) - 1);
	u8 flag1 = 2, flag2 = 2;
	while ('.' != pfn[i] && i > 0)
	{
		if (pfn[i] >= 'a' && pfn[i] <= 'z')
		{
			if (0 == flag1)
			{
				return (u8) - 1;
			}
			flag1 = 1;
		}
		if (pfn[i] >= 'A' && pfn[i] <= 'Z')
		{
			if (1 == flag1)
			{
				return (u8) - 1;
			}
			flag1 = 0;
		}
		i--;
	}

	if (0 == i) //如果没有.说明没有扩展名
	{
		if (pfn[0] >= 'a' && pfn[0] <= 'z')
		{
			if (0 == flag1)
			{
				return (u8) - 1;
			}
			flag1 = 1;
		}
		flag2 = flag1;
		flag1 = 0;
	}
	if ('.' == pfn[i])
	{
		i--;
	}
	while (i > 0)
	{
		if (pfn[i] >= 'a' && pfn[i] <= 'z')
		{
			if (0 == flag2)
			{
				return (u8) - 1;
			}
			flag2 = 1;
		}
		if (pfn[i] >= 'A' && pfn[i] <= 'Z')
		{
			if (1 == flag2)
			{
				return (u8) - 1;
			}
			flag2 = 0;
		}
		i--;
	}
	if (2 == flag2)
	{
		if (pfn[0] >= 'a' && pfn[0] <= 'z')
		{
			flag2 = 1;
		}
		if (pfn[0] >= 'A' && pfn[0] <= 'Z')
		{
			flag2 = 0;
		}
	}

	return (u8)((flag1 << 4) | (flag2));
}
#endif
//-----------------------------------------------------------------
// 检查文件名的长度
//-----------------------------------------------------------------
# ifdef CHECK_SFN_ILLEGAL_LENGTH
u8 Check_SFN_Illegal_Length(char* pfn)
{
	u8 dot_pos = 0, have_dot = 0, i = 0;
	u8 mainfn_len = 0, extfn_len = 0;
	u32 fn_len = StringLen(pfn);
	while (' ' == pfn[fn_len - 1]) fn_len--;
	if (fn_len > 12) return ERR_FAIL;
	for (i = (u8)(fn_len - 1); i > 0; i--)
	{
		if ('.' == pfn[i])
		{
			dot_pos = i;
			have_dot = 1;
			break;
		}
	}

	if (0 == have_dot)
	{
		mainfn_len = (u8)fn_len;
		extfn_len = 0;
		if ((mainfn_len > 0 && mainfn_len <= 8))
		{
			return ERR_SUCC;
		}
		else
		{
			return ERR_FAIL;
		}
	}
	else
	{
		mainfn_len = dot_pos;
		extfn_len = (u8)(((u8)fn_len) - (u8)(dot_pos + 1));
		if ((mainfn_len > 0 && mainfn_len <= 8)
		 && (/*extfn_len>=0  && */extfn_len <= 3))
		{
			return ERR_SUCC;
		}
		else
		{
			return ERR_FAIL;
		}
	}
}
#endif
//-----------------------------------------------------------------
// 将文件目录项前11字节转为文件名
//-----------------------------------------------------------------
# ifdef TO_FILE_NAME
u8 To_File_Name(char* name_in_fdi, char* pfileName)
{
	u8 i = 0, n = 7, m = 10;
	while (' ' == name_in_fdi[n])
	{
		n--;
	}
	n++;
	while (' ' == name_in_fdi[m] && m >= 8)
	{
		m--;
	}
	m -= 7;

	for (i = 0; i < n; i++)
	{
		pfileName[i] = name_in_fdi[i];
	}
	pfileName[i] = '.';

	for (i = 0; i < m; i++)
	{
		pfileName[n + i + 1] = name_in_fdi[8 + i];
	}

	if ('.' == pfileName[n + m]) pfileName[n + m] = 0;
	else pfileName[n + m + 1] = 0;

	return 0;
}
#endif

//-----------------------------------------------------------------
// 解析文件目录项
//-----------------------------------------------------------------
# ifdef ANALYSE_FDI
u8 Analyse_FDI(struct FileInfo *pfi,struct FDI *pFDI){
	u32 temp = 0, i = 0;
	just_file = pfi;
	To_File_Name((char*)pFDI, pfi->File_Name);
	temp = (StringLen(pfi->File_Name) - 1);
	while ('.' != (pfi->File_Name)[temp] && temp > 0)
	{
		if (((pFDI->LowerCase) & 0x10) != 0)
		{
			(pfi->File_Name)[temp] = (char)Upper2Low((pfi->File_Name)[temp]);
		}
		temp--;
	}
	if (((pFDI->LowerCase) & 0x08) != 0)
	{
		for (i = 0; i < temp; i++)
		{
			(pfi->File_Name)[i] = (char)Upper2Low((pfi->File_Name)[i]);
		}
	}

	temp = (StringLen(pfi->File_Name) - 1);
	if (CHK_ATTR_DIR(pFDI->Attributes))
	{
		(pfi->File_Name)[temp + 1] = '\0';
	}
	pfi->File_Attr = pFDI->Attributes;
	pfi->File_StartClust = Bytes2Value(pFDI->LowClust, 2) + Bytes2Value(pFDI->HighClust, 2) * 65536;
	pfi->File_Size = Bytes2Value(pFDI->FileSize, 4);

	//解析文件创建时间与日期
	temp = Bytes2Value(pFDI->CTime, 2);
	pfi->File_CTime.sec = (u8)((temp & TIME_SEC_MARK) * 2); temp >>= TIME_SEC_NBITS;
	pfi->File_CTime.min = (u8)(temp & TIME_MIN_MARK); temp >>= TIME_MIN_NBITS;
	pfi->File_CTime.hour = (u8)(temp & TIME_HOUR_MARK);
	pfi->File_CTime.sec += (u8)((u16)(pFDI->CTime10ms) / 100);

	temp = Bytes2Value(pFDI->CDate, 2);
	pfi->File_CDate.day = (u8)(temp & DATE_DAY_MARK); temp >>= DATE_DAY_NBITS;
	pfi->File_CDate.month = (u8)(temp & DATE_MONTH_MARK); temp >>= DATE_MONTH_NBITS;
	pfi->File_CDate.year = (u16)((temp & DATE_YEAR_MARK) + DATE_YEAR_BASE);

	pfi->File_CurClust = pfi->File_StartClust;
	pfi->File_CurSec = (pfi->File_CurClust) ? SOC(pfi->File_CurClust) : 0;
	pfi->File_CurPos = 0;
	pfi->File_CurOffset = 0;
	pfi->File_IsEOF = (u8)((pfi->File_StartClust) ? BOOL_FALSE : BOOL_TRUE);

	return 0;
}
#endif
//-----------------------------------------------------------------
// 检查文件名是否是通配名，通配名中含有*与?
//-----------------------------------------------------------------
# ifdef IS_WILDFILENAME
u8 Is_WildFileName(char* pfn)
{
	u8 i = 0;
	while ('\0' != pfn[i])
	{
		if ('*' == pfn[i] || '?' == pfn[i])
		{
			return 1;
		}
		i++;
	}
	return 0;
}
#endif
//-----------------------------------------------------------------
// 在一个字符串中查找一个子串
//-----------------------------------------------------------------
# ifdef FINDSUBSTR
u8 FindSubStr(char* str, char* substr, u8 pos)
{
	u8 i = pos, j = 0, lens = (u8)StringLen(str), lent = (u8)StringLen(substr);
	while (i < lens && j < lent)
	{
		if (str[i] == substr[j] || '?' == substr[j])
		{
			i++;
			j++;
		}
		else
		{
			i = (u8)(i - j + 1);
			j = 0;
		}
	}
	if (j == lent) return (u8)(i - lent);
	else return (u8)0XFF;
}
#endif
//-----------------------------------------------------------------
// 文件名匹配，支持*与?通配
//-----------------------------------------------------------------
# ifdef SFN_MATCH
u8 SFN_Match(char* t, char* s)
{
	u8 i = 0, j = 0, lens = (u8)StringLen(s);
	u8 lent = (u8)StringLen(t);
	char buf[20];
	u8 bufp = 0;
	//======================================================
	while (j < lent && '*' != t[j])
	{
		buf[bufp] = (char)Lower2Up(t[j]);
		bufp++;
		j++;
	}
	if ('\0' == t[j] && (lent != lens)) return ERR_FAIL;
	buf[bufp] = '\0';
	if (FindSubStr(s, buf, 0) != 0) return ERR_FAIL;
	i = bufp;
	while (1)
	{
		while (j < lent && '*' == t[j]) j++;
		if (j == lent) return ERR_SUCC;
		bufp = 0;

		while (j < lent && '*' != t[j])
		{
			buf[bufp] = (char)Lower2Up(t[j]);
			bufp++;
			j++;
		}
		buf[bufp] = '\0';
		if (j == lent)
		{
			if (FindSubStr(s, buf, i) != (lens - bufp)) return ERR_FAIL;
			return ERR_SUCC;
		}
		i = FindSubStr(s, buf, i);
		if (0XFF == i) return ERR_FAIL;
		i += bufp;
	}
}
#endif
//-----------------------------------------------------------------
// 修改FAT表表项
//-----------------------------------------------------------------
# ifdef MODIFY_FAT
u8 Modify_FAT(u32 cluster, u32 next_cluster)
{
	u32 temp1 = 0, temp2 = 0;
	if (0 == cluster || 1 == cluster) return ERR_FAIL;
	temp1 = pInitInfo->FirstFATSector + (cluster * 4 / pInitInfo->BytesPerSector);
	temp2 = ((cluster * 4) % pInitInfo->BytesPerSector);
	FAT_Device_Read_Sector(temp1, FAT_Buffer);
	FAT_Buffer[temp2 + 0] = (u8)(next_cluster & 0x000000ff);
	FAT_Buffer[temp2 + 1] = (u8)((next_cluster & 0x0000ff00) >> 8);
	FAT_Buffer[temp2 + 2] = (u8)((next_cluster & 0x00ff0000) >> 16);
	FAT_Buffer[temp2 + 3] = (u8)((next_cluster & 0xff000000) >> 24);
	FAT_Device_Write_Sector(temp1, FAT_Buffer);
	FAT_Device_Read_Sector(temp1 + pInitInfo->FATsectors, FAT_Buffer);
	FAT_Buffer[temp2 + 0] = (u8)(next_cluster & 0x000000ff);
	FAT_Buffer[temp2 + 1] = (u8)((next_cluster & 0x0000ff00) >> 8);
	FAT_Buffer[temp2 + 2] = (u8)((next_cluster & 0x00ff0000) >> 16);
	FAT_Buffer[temp2 + 3] = (u8)((next_cluster & 0xff000000) >> 24);
	FAT_Device_Write_Sector(temp1 + pInitInfo->FATsectors, FAT_Buffer);
	return ERR_SUCC;
}
#endif

//-----------------------------------------------------------------
// 对cluster簇进行清0
//-----------------------------------------------------------------
# ifdef CLEAR_CLUSTER
u8 Clear_Cluster(u32 cluster)
{
	FAT_Device_Clear_nSector((pInitInfo->SectorsPerClust), SOC(cluster));
	return 0;
}
#endif
//-----------------------------------------------------------------
// 更新下一空簇
//-----------------------------------------------------------------
# ifdef UPDATE_NEXT_FREE_CLUSTER
u8 Update_Next_Free_Cluster(void)
{
	u32 clu_sec, iItem, iSec;
	struct FAT_Sec *pFAT_Sec;

if (0 != pInitInfo->Free_nCluster)
{
	pInitInfo->Free_nCluster--;

	clu_sec = (pInitInfo->Next_Free_Cluster / NITEMSINFATSEC);
	FAT_Device_Read_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
	pFAT_Sec = (struct FAT_Sec *)FAT_Buffer;

for (iItem = ((pInitInfo->Next_Free_Cluster) % NITEMSINFATSEC) + 1; iItem < NITEMSINFATSEC; iItem++)
{
	if (0 == (((pFAT_Sec->items)[iItem]).Item)[0]
	&& 0 == (((pFAT_Sec->items)[iItem]).Item)[1]
	&& 0 == (((pFAT_Sec->items)[iItem]).Item)[2]
	&& 0 == (((pFAT_Sec->items)[iItem]).Item)[3])
	{
		pInitInfo->Next_Free_Cluster = (clu_sec * NITEMSINFATSEC) + iItem;
# ifdef RT_UPDATE_FSINFO
		Update_FSINFO();
#endif
		return ERR_SUCC;
	}
}

for (iSec = (clu_sec + 1); iSec < (pInitInfo->FATsectors); iSec++)
{
	FAT_Device_Read_Sector(iSec + (pInitInfo->FirstFATSector), FAT_Buffer);
	pFAT_Sec = (struct FAT_Sec *)FAT_Buffer;
for (iItem = 0; iItem < NITEMSINFATSEC; iItem++)
{
	if (0 == (((pFAT_Sec->items)[iItem]).Item)[0]
	&& 0 == (((pFAT_Sec->items)[iItem]).Item)[1]
	&& 0 == (((pFAT_Sec->items)[iItem]).Item)[2]
	&& 0 == (((pFAT_Sec->items)[iItem]).Item)[3])
	{
		pInitInfo->Next_Free_Cluster = (iSec * NITEMSINFATSEC) + iItem;
# ifdef RT_UPDATE_FSINFO
		Update_FSINFO();
#endif
		return ERR_SUCC;
	}
}
	}
	}
	pInitInfo->Next_Free_Cluster = 2;
return ERR_NO_SPACE;
}
#endif
//-----------------------------------------------------------------
// 判断文件名是否是长文件名
//-----------------------------------------------------------------
#ifdef IS_LFN
u8 Is_LFN(char* filename)
{
	u8 is_lfn = BOOL_FALSE;
	if (Check_SFN_Illegal_Length(filename)) is_lfn = BOOL_TRUE;
	if (Check_SFN_Dot(filename)) is_lfn = BOOL_TRUE;
	if (Check_SFN_Special_Char(filename)) is_lfn = BOOL_TRUE;
	if (((u8)(-1)) == Check_SFN_Illegal_Lower(filename)) is_lfn = BOOL_TRUE;
	return is_lfn;
}
#endif

//-----------------------------------------------------------------
// 从长名提取所含部分长名UNI码
//-----------------------------------------------------------------
# ifdef GET_PART_NAME
u8 Get_Part_Name(u16* lfn_buf,struct LFN_FDI *plfndi, u8 n) {
	u8 i = 0;
	u16 temp = 0;

	if ((plfndi->AttrByte[0]) & 0X40) Memory_Set(((u8*)lfn_buf), 2 * (MAX_LFN_LEN + 1), 0);

	for (i = 0; i < 5; i++)
	{
		if (n >= MAX_LFN_LEN) return ERR_LFN_BUF_OUT;
		temp = (((u16)(((plfndi->Name1) + i * 2)[0])) & 0X00FF) | ((((u16)(((plfndi->Name1) + i * 2)[1])) & 0X00FF) << 8);
		if (0 == temp)
		{
			lfn_buf[n] = 0;
			return 0;
		}
		else
		{
			lfn_buf[n] = temp; n++;
		}
	}

	for (i = 0; i < 6; i++) {
		if (n >= MAX_LFN_LEN) return ERR_LFN_BUF_OUT;
		temp = (((u16)(((plfndi->Name2) + i * 2)[0])) & 0X00FF) | ((((u16)(((plfndi->Name2) + i * 2)[1])) & 0X00FF) << 8);
		if (0 == temp)
		{
			lfn_buf[n] = 0;
			return 0;
		}
		else
		{
			lfn_buf[n] = temp; n++;
		}
	}

	for (i = 0; i < 2; i++) 	{
		if (n >= MAX_LFN_LEN) return ERR_LFN_BUF_OUT;
		temp = (((u16)(((plfndi->Name3) + i * 2)[0])) & 0X00FF) | ((((u16)(((plfndi->Name3) + i * 2)[1])) & 0X00FF) << 8);
		if (0 == temp)
		{
			lfn_buf[n] = 0;
			return 0;
		}
		else
		{
			lfn_buf[n] = temp; n++;
		}
	}

	n--;
	if ((plfndi->AttrByte[0]) & 0X40)
	{
		while (((u16)(0XFFFF)) == lfn_buf[n]) n--;
		lfn_buf[n + 1] = 0;
	}

	return 0;
}
#endif

//-----------------------------------------------------------------
// OEM码转为UNICODE码
//-----------------------------------------------------------------
# ifdef OEMTOUNI
u8 OEM2UNI(u16 oem_code, u16* uni_code) {
	u32 low = 0, high = MAX_UNI_INDEX - 1, mid;
	if (oem_code < GET_PGM_WORD(&(oem_uni[0][1]))) return ERR_FAIL;
	if (oem_code > GET_PGM_WORD(&(oem_uni[MAX_UNI_INDEX - 1][1]))) return ERR_FAIL;
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (oem_code == GET_PGM_WORD(&(oem_uni[mid][1])))
		{
			*uni_code = GET_PGM_WORD(&(oem_uni[mid][0]));
			return ERR_SUCC;
		}

		if (GET_PGM_WORD(&(oem_uni[mid][1])) > oem_code)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return ERR_FAIL;
}
#endif
//-----------------------------------------------------------------
// 将OEM编码字符串转为UNICODE编码字符串
//-----------------------------------------------------------------
# ifdef OEMSTRTOUNISTR
u8 oemstr2unistr(char* oemstr, u16* unistr) {
	u32 len = StringLen(oemstr);
	u32 i = 0, pos = 0;
	u8 res = 0;
	u16 temp = 0;

	for (i = 0; i < len; i++)
	{
		if (IS_ASC(oemstr[i]))
		{
			unistr[pos] = (u16)(((u16)oemstr[i]) & 0X00FF);
			pos++;
		}
# ifdef USE_OEM_CHAR
		else
		{
			temp = ((((u16)oemstr[i]) << 8) & 0xff00);
			temp |= (((u16)oemstr[i + 1]) & 0x00ff);
			res = OEM2UNI(temp, unistr + pos);
			if (res)
			{
				unistr[0] = 0;
				return ERR_OEM_CHAR_NOT_COMPLETE;
			}
			pos++; i++;
		}
#endif
		if (pos > MAX_LFN_LEN)
		{
			unistr[0] = 0;
			return ERR_LFN_BUF_OUT;
		}
	}

	unistr[pos] = 0;

	return ERR_SUCC;
}
#endif

//-----------------------------------------------------------------
// 对宽字符串进行子串查找
//-----------------------------------------------------------------
# ifdef WFINDSUBSTR
u32 WFindSubStr(u16* str, u16* substr, u32 pos) {
	u32 i = pos, j = 0, lens = WStringLen(str), lent = WStringLen(substr);
	while (i < lens && j < lent)
	{
		if (WLower2Up(str[i]) == substr[j] || (u16)'?' == substr[j])
		{
			i++; j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == lent) return i - lent; else return (u32) - 1;
}
#endif
//-----------------------------------------------------------------
// 对两个宽字符串进行匹配
//-----------------------------------------------------------------
# ifdef LFN_MATCH
u8 LFN_Match(u16* t, u16* s) {
	u32 i = 0, j = 0, lens = WStringLen(s), lent = WStringLen(t);
	u16 bufp = 0;

	u16 buf[MAX_LFN_LEN + 1];
	while (j < lent && (u16)'*' != t[j])
	{
		buf[bufp] = WLower2Up(t[j]);
		bufp++;
		j++;
	}

	if (0 == t[j] && (lent != lens)) return ERR_FAIL;

	buf[bufp] = 0;

	if (WFindSubStr(s, buf, 0) != 0) return ERR_FAIL;
	i = bufp;

	while (1)
	{
		while (j < lent && (u16)'*' == t[j]) j++;
		if (j == lent) return ERR_SUCC;
		bufp = 0;

		while (j < lent && (u16)'*' != t[j])
		{
			buf[bufp] = (u16)WLower2Up(t[j]);
			bufp++;
			j++;
		}
		buf[bufp] = 0;

		if (j == lent)
		{
			if (WFindSubStr(s, buf, i) != (lens - bufp)) return ERR_FAIL;
			return 0;
		}

		i = WFindSubStr(s, buf, i);
		if (((u32)(-1)) == i) return ERR_FAIL;
		i += bufp;
	}
}
#endif

//-----------------------------------------------------------------
// 从短名文件目录项获取绑定校验和
//-----------------------------------------------------------------
# ifdef GET_BINDING_SUMCHK
u8 Get_Binding_SumChk(struct FDI *pdi) {
	u8 i = 0, c = 0;
	for (i = 0; i < 11; i++)
	{
		c = (u8)(((c & 0X01) ? 0X80 : 0) + (c >> 1) + ((pdi->Name)[i]));
	}
	return c;
}
#endif
//-----------------------------------------------------------------
// ELF哈希算法
//-----------------------------------------------------------------
# ifdef	ELFHASH
u32 ELFHash(char* str) {
	u32 hash = 0;
	u32 x = 0;
	while (*str)
	{
		hash = (hash << 4) + (*str++);
		x = hash & 0xF0000000;
		if (0 != x)
		{
			hash ^= (x >> 24); hash &= ~x;
		}
	}
	return (hash & 0X7FFFFFFF);
}
#endif
//-----------------------------------------------------------------
// 将32位整形数转为16进制字符串
//-----------------------------------------------------------------
# ifdef HEX2STR_32B
u8 Hex2Str_32b(u32 hex, char* str) {
	u8 i = 0, temp = 0;
	for (i = 0; i < 8; i++)
	{
		temp = ((u8)((hex & (0X0000000F << (i * 4))) >> (i * 4)));
		str[7 - i] = (char)((temp >= 10) ? ('A' + temp - 10) : (temp + 0X30));
	}
	str[i] = 0;
	return 0;
}
#endif
//-----------------------------------------------------------------
// 由长名构造其对应的短名
//-----------------------------------------------------------------
# ifdef MAKE_SHORT_NAME
u8 Make_Short_Name(char* pfn, char* psfn) {
	u32 temp = ELFHash(pfn);
	Hex2Str_32b(temp, psfn);
	psfn[8] = '.';
	psfn[9] = psfn[10] = psfn[11] = 'A';
	psfn[12] = 0;
	return 0;
}
#endif
//-----------------------------------------------------------------
// 构造第n个长名项
//-----------------------------------------------------------------
# ifdef FILL_LFN_FDI
u8 Fill_LFN_FDI(u16* unifn,struct LFN_FDI *plfni, u8 ChkSum, u8 n) {
	u8 temp = (u8)(n * 13), i = 0, j = 0;
	u16 len = (u16)WStringLen(unifn + temp);
	(plfni->AttrByte[0]) = (u8)(n + 1);
	if (len <= 13) (plfni->AttrByte[0]) |= 0X40;
	(plfni->ChkVal[0]) = ChkSum;
	(plfni->LFNSign[0]) = 0X0F;

	(plfni->Resv[0]) = (plfni->StartClu[0]) = (plfni->StartClu[1]) = 0;
	for (i = 0; i < 10; i++) (plfni->Name1)[i] = 0XFF;
	for (i = 0; i < 12; i++) (plfni->Name2)[i] = 0XFF;
	for (i = 0; i < 4; i++) (plfni->Name3)[i] = 0XFF;
	for (i = 0; i < 5; i++)
	{
		(plfni->Name1)[2 * i] = (u8)(unifn[j + temp] & 0X00FF);
		(plfni->Name1)[2 * i + 1] = (u8)((unifn[j + temp] & 0XFF00) >> 8);
		j++;
		if (j >= len)
		{
			if (4 == i)
			{
				(plfni->Name2)[0] = (plfni->Name2)[1] = 0;
			}
			else
			{
				i++;
				(plfni->Name1)[2 * i] = (plfni->Name1)[2 * i + 1] = 0;
			}
			return ERR_SUCC;
		}
	}

	for (i = 0; i < 6; i++)
	{
		(plfni->Name2)[2 * i] = (u8)(unifn[j + temp] & 0X00FF);
		(plfni->Name2)[2 * i + 1] = (u8)((unifn[j + temp] & 0XFF00) >> 8);
		j++;
		if (j >= len)
		{
			if (5 == i)
			{
				(plfni->Name3)[0] = (plfni->Name3)[1] = 0;
			}
			else
			{
				i++;
				(plfni->Name2)[2 * i] = (plfni->Name2)[2 * i + 1] = 0;
			}
			return ERR_SUCC;
		}
	}

	for (i = 0; i < 2; i++)
	{
		(plfni->Name3)[2 * i] = (u8)(unifn[j + temp] & 0X00FF);
		(plfni->Name3)[2 * i + 1] = (u8)((unifn[j + temp] & 0XFF00) >> 8);
		j++;
		if (j >= len)
		{
			if (1 != i)
			{
				i++;
				(plfni->Name3)[2 * i] = (plfni->Name3)[2 * i + 1] = 0;
			}
			return ERR_SUCC;
		}
	}
	return ERR_SUCC;
}
#endif
//-----------------------------------------------------------------
// 向目录簇注册长名项及其对应短名项并返回短名项所在扇区与扇区内位置
//-----------------------------------------------------------------
# ifdef REGISTER_LFN_FDI
u8 Register_LFN_FDI(u32 cluster,struct FDI *pfdi, u16* unifn, u32 * psec, u8 * pn) {
	u32 temp_sec = 0, old_cluster = 0;
	u8 iClu = 0, iSec = 0, iFDI = 0, res = 0;
	struct FDIesInSEC *pitems;
struct FDI *pitem;
struct LFN_FDI *plfni;
u8 have_lfn = 0;
u8 is_lfn_buf_err = 0, cur_binding_sumchk = 0, flag = 0, chksum = Get_Binding_SumChk(pfdi);
u16 lfn_buf[MAX_LFN_LEN + 1];
struct LFN_FDI temp_lfni;

u16 len = (u16)WStringLen(unifn), xlen = 0;
u8 nclu = 0, nsec = 0, nlfni = (u8)(len / 13);
if (len % 13) nlfni++;
if (0 == pInitInfo->Free_nCluster) return ERR_NO_SPACE;
do
{
	temp_sec = SOC(cluster);
	for (iSec = 0; iSec < (pInitInfo->SectorsPerClust); iSec++)
	{
		FAT_Device_Read_Sector(temp_sec + (u32)iSec, FAT_Buffer);
		pitems = ((struct FDIesInSEC *)FAT_Buffer);

for (iFDI = 0; iFDI < NFDI_PER_SEC; iFDI++)
{
	pitem = &(pitems->FDIes[iFDI]);

	if ((0X08 != pitem->Attributes) && (0X0F != pitem->Attributes)
	&& (0XE5 != pitem->Name[0]) && ('.' != pitem->Name[0]))
	{
		if (have_lfn && !is_lfn_buf_err)
		{
			if (cur_binding_sumchk == Get_Binding_SumChk(pitem))
			{
				xlen = (u16)WStringLen(lfn_buf);
				if (xlen == len && Memory_Compare(((u8*)unifn), ((u8*)lfn_buf), 2 * ((u32)len)))
				{
					*psec = temp_sec + (u32)iSec;
					*pn = iFDI;
					return ERR_FDI_ALREADY_EXISTING;
				}
			}
		}
		if (is_lfn_buf_err) is_lfn_buf_err = 0;

		if (CHK_ATTR_LFN(pitem->Attributes) && (0XE5 != pitem->Name[0]))
		{
			have_lfn = 1;
			plfni = (struct LFN_FDI *)pitem;
cur_binding_sumchk = (plfni->ChkVal)[0];
res = Get_Part_Name(lfn_buf, plfni, (u8)((((plfni->AttrByte[0]) & 0XBF) - 1) * 13));
if (res) is_lfn_buf_err = 1; 
	}
	else
{
	have_lfn = 0;
}
if (0 == (pitem->Name)[0])
{
	flag = 1;
	if (nlfni > 0)
	{
		Fill_LFN_FDI(unifn, &temp_lfni, chksum, (u8)(nlfni - 1));
		Memory_Copy(((u8*)pitem), ((u8*)(&temp_lfni)), FDI_NBYTES);
		nlfni--;
	}
	else
	{
		*psec = temp_sec + (u32)iSec;
		*pn = iFDI;
		Memory_Copy(((u8*)pitem), ((u8*)pfdi), FDI_NBYTES);
		FAT_Device_Write_Sector(temp_sec + (u32)iSec, FAT_Buffer);
		return ERR_SUCC;
	}
}
	 }

	 if (flag)
{
	FAT_Device_Write_Sector(temp_sec + (u32)iSec, FAT_Buffer);
	flag = 0;
}
	}
	old_cluster = cluster;
cluster = Get_Next_Cluster(cluster);
	}while (!IS_END_CLU(cluster)) ;
//===========================================================
if (0 != pInitInfo->Free_nCluster)
{
	nsec = (u8)((nlfni + 1) / NFDI_PER_SEC);
	if ((nlfni + 1) % NFDI_PER_SEC) nsec++;

	nclu = (u8)(nsec / (pInitInfo->SectorsPerClust));
	if (nsec % (pInitInfo->SectorsPerClust)) nclu++;

	for (iClu = 0; iClu < nclu; iClu++)
	{
		Modify_FAT(old_cluster, pInitInfo->Next_Free_Cluster);
		Modify_FAT(pInitInfo->Next_Free_Cluster, 0X0FFFFFFF);
		Clear_Cluster(pInitInfo->Next_Free_Cluster);

		temp_sec = SOC(pInitInfo->Next_Free_Cluster);

		old_cluster = pInitInfo->Next_Free_Cluster;
		Update_Next_Free_Cluster();

		for (iSec = 0; iSec < (pInitInfo->SectorsPerClust); iSec++)
		{
			FAT_Device_Read_Sector(temp_sec + (u32)iSec, FAT_Buffer);
			pitems = ((struct FDIesInSEC *)FAT_Buffer);

for (iFDI = 0; iFDI < NFDI_PER_SEC; iFDI++)
{
	pitem = &(pitems->FDIes[iFDI]);

	if (nlfni > 0)
	{
		Fill_LFN_FDI(unifn, &temp_lfni, chksum, (u8)(nlfni - 1));
		Memory_Copy(((u8*)pitem), ((u8*)(&temp_lfni)), FDI_NBYTES);
		nlfni--;
	}
	else
	{
		*psec = temp_sec + (u32)iSec;
		*pn = iFDI;
		Memory_Copy(((u8*)pitem), ((u8*)pfdi), FDI_NBYTES);
		FAT_Device_Write_Sector(temp_sec + (u32)iSec, FAT_Buffer);
		return ERR_SUCC;
	}
}
FAT_Device_Write_Sector(temp_sec + (u32)iSec, FAT_Buffer);
			 }   
			}
			return ERR_SUCC;  
		}
		else
{
	return ERR_NO_SPACE;
} 
	}
#endif
//-----------------------------------------------------------------
// 打开文件
//-----------------------------------------------------------------
#ifdef FAT_OPEN_FILE 
u8 FAT_Open_File(struct FileInfo *pfi, char* filepath, u32 n, u8 is_file) {
	u8 result = 0, flag = 0;
	u32 sec_temp = 0, Cur_Cluster = 0, fn_pos = 0, item = 0;
	u32 iSec = 0, iFDI = 0;

	# ifdef USE_LFN
struct LFN_FDI *plfni;
u8 cur_binding_sumchk = 0;
u8 is_wfn = 0;
u16 temp_lfn[MAX_LFN_LEN + 1];
u8 is_lfn = 0;
u8 is_lfn_buf_err = 0;
#endif

char temp_filename[13];
char* filename;

struct FDIesInSEC *pitems;
struct FDI *pitem;

# ifdef USE_LFN
pfi->have_lfn = BOOL_FALSE;
#endif

just_file = pfi;

# ifndef RT_UPDATE_CLUSTER_CHAIN
get_next_cluster_in_cccb = 0;
# ifdef USE_ALONE_CCCB
CCCB_To_Alone();
Memory_Set((u8*)pcccb_buf, sizeof(u32) * CCCB_LEN, 0);
#endif
#endif

# ifdef USE_EXCHANGE_BUFFER
# ifdef USE_ALONE_EXB
//Memory_Set(just_file->exb_buf,512,0);
just_file->exb_cursec = 0;
#endif
#endif

result = FAT_Enter_Dir(filepath, &Cur_Cluster, &fn_pos);
if (result) return result;

filename = filepath + fn_pos;
if (Check_Illegal_Char(filename)) return ERR_ILL_CHAR;
if (!Is_WildFileName(filename))
{
# ifdef USE_LFN
	if (!Is_LFN(filename))
	{
#endif
		if (Check_SFN_Illegal_Length(filename)) return ERR_SFN_ILL_LEN;
		if (Check_SFN_Dot(filename)) return ERR_SFN_DOT;
		if (Check_SFN_Special_Char(filename)) return ERR_SFN_SPEC_CHAR;
		if (((u8)(-1)) == Check_SFN_Illegal_Lower(filename)) return ERR_SFN_ILL_LOWER;

# ifdef USE_LFN
	}
	else
	{
		is_lfn = 1;
		result = oemstr2unistr(filename, temp_lfn);
		if (result) return result;
	}
#endif
}
else
{
# ifdef USE_LFN
	is_wfn = 1;
	is_lfn = 1;
	result = oemstr2unistr(filename, temp_lfn);
	if (result) return result;
#endif
}

//================================================
do
{
	sec_temp = SOC(Cur_Cluster);
	for (iSec = 0; iSec < (pInitInfo->SectorsPerClust); iSec++)
	{
		FAT_Device_Read_Sector(sec_temp + (u32)iSec, FAT_Buffer);
		pitems = (struct FDIesInSEC *)FAT_Buffer;

for (iFDI = 0; iFDI < NFDI_PER_SEC; iFDI++)
{
	pitem = &(pitems->FDIes[iFDI]);
	if ((is_file ? CHK_ATTR_FILE(pitem->Attributes) : CHK_ATTR_DIR(pitem->Attributes))
	&& (0XE5 != pitem->Name[0]) && ('.' != pitem->Name[0]))
	{
		To_File_Name((char*)(pitem->Name), temp_filename);
# ifdef USE_LFN	
		if (!is_lfn || is_wfn)
#endif
		{
			if (!SFN_Match(filename, temp_filename))
			{
				if (n == item)
				{
					Analyse_FDI(pfi, pitem);
					pfi->FDI_Sec = sec_temp + iSec;
					pfi->nFDI = (u8)iFDI;

# ifdef USE_LFN
					if (!pfi->have_lfn) (pfi->longname)[0] = 0;
#endif

					return ERR_SUCC;
				}
				flag = 1;
			}
		}
# ifdef USE_LFN
		if (is_lfn && (pfi->have_lfn) && !is_lfn_buf_err)
		{
			if (cur_binding_sumchk == Get_Binding_SumChk(pitem))
			{
				if (!LFN_Match(temp_lfn, (pfi->longname)))
				{
					if (n == item)
					{
						Analyse_FDI(pfi, pitem);
						pfi->FDI_Sec = sec_temp + iSec;
						pfi->nFDI = (u8)iFDI;
						return ERR_SUCC;
					}
					flag = 1;
				}
			}
		}

		if (is_lfn_buf_err) is_lfn_buf_err = 0;
#endif
		if (flag) { item++; flag = 0; }
	}

# ifdef USE_LFN
	if ((CHK_ATTR_DIR(pitem->Attributes)) || (CHK_ATTR_FILE(pitem->Attributes)))
		if (is_lfn_buf_err) is_lfn_buf_err = 0;

	if (CHK_ATTR_LFN(pitem->Attributes) && (0XE5 != pitem->Name[0]) && is_lfn)
	{
		pfi->have_lfn = 1;
		plfni = (struct LFN_FDI *)pitem;
cur_binding_sumchk = (plfni->ChkVal)[0];
result = Get_Part_Name(pfi->longname, plfni, (u8)((((plfni->AttrByte[0]) & 0XBF) - 1) * 13));
if (result) is_lfn_buf_err = 1; 
				}
				else
{
	pfi->have_lfn = 0;
}
				#endif
			}
		}
		Cur_Cluster = Get_Next_Cluster(Cur_Cluster);
	}while (!IS_END_CLU(Cur_Cluster)) ;
return ERR_NO_FILE;
}
#endif
//-----------------------------------------------------------------
// 获取一个目录的开始簇
//-----------------------------------------------------------------
#ifdef GET_DIR_START_CLUSTER
u8 Get_Dir_Start_Cluster(char* dir_name, u32* pCluster)
{
	u32 sec_temp = 0;
	u8 iSec = 0, iFDI = 0;
	u32 Cur_Clust = *pCluster;
	# ifdef USE_LFN
	struct LFN_FDI *plfni;

u8 cur_binding_sumchk = 0, result = 0;
u16 temp_lfn[MAX_LFN_LEN + 1];
u16 lfn_buf[MAX_LFN_LEN + 1];
u8 is_lfn = 0;
u8 have_lfn = 0;
u8 is_lfn_buf_err = 0;
#endif

char temp_dirname[13];
struct FDIesInSEC *pitems;
struct FDI *pitem;

# ifndef RT_UPDATE_CLUSTER_CHAIN
get_next_cluster_in_cccb = 0;
#endif

if (Check_Illegal_Char(dir_name)) return ERR_ILL_CHAR;

# ifdef USE_LFN
if (!Is_LFN(dir_name))
{
#endif
	if (Check_SFN_Illegal_Length(dir_name)) return ERR_SFN_ILL_LEN;
	if (Check_SFN_Dot(dir_name)) return ERR_SFN_DOT;
	if (Check_SFN_Special_Char(dir_name)) return ERR_SFN_SPEC_CHAR;
	if (((u8)(-1)) == Check_SFN_Illegal_Lower(dir_name)) return ERR_SFN_ILL_LOWER;
# ifdef USE_LFN
}
else
{
	is_lfn = 1;
	result = oemstr2unistr(dir_name, temp_lfn);
	if (result) return result;
}
#endif

do
{
	sec_temp = SOC(Cur_Clust);
	for (iSec = 0; iSec < (pInitInfo->SectorsPerClust); iSec++)
	{
		FAT_Device_Read_Sector(sec_temp + (u32)iSec, FAT_Buffer);
		pitems = (struct FDIesInSEC *)FAT_Buffer;

for (iFDI = 0; iFDI < NFDI_PER_SEC; iFDI++)
{
	pitem = &(pitems->FDIes[iFDI]);

	if ((CHK_ATTR_DIR(pitem->Attributes)) && (0XE5 != pitem->Name[0]))
	{
		To_File_Name((char*)(pitem->Name), temp_dirname);
# ifdef USE_LFN
		if (!is_lfn)
#endif
		{
			if (!SFN_Match(dir_name, temp_dirname))
			{
				*pCluster = (Bytes2Value(pitem->LowClust, 2)) | (Bytes2Value(pitem->HighClust, 2) << 16);
				return ERR_SUCC;
			}
		}

# ifdef USE_LFN
		if (is_lfn && have_lfn && !is_lfn_buf_err)
		{
			if (cur_binding_sumchk == Get_Binding_SumChk(pitem))
			{
				if (!LFN_Match(temp_lfn, lfn_buf))
				{
					*pCluster = (Bytes2Value(pitem->LowClust, 2)) | (Bytes2Value(pitem->HighClust, 2) << 16);
					return ERR_SUCC;
				}
			}
		}
#endif

	}

# ifdef USE_LFN
	if ((CHK_ATTR_DIR(pitem->Attributes)) || (CHK_ATTR_FILE(pitem->Attributes)))
		if (is_lfn_buf_err) is_lfn_buf_err = 0;

	if (CHK_ATTR_LFN(pitem->Attributes) && (0XE5 != pitem->Name[0]) && is_lfn)
	{
		have_lfn = 1;
		plfni = (struct LFN_FDI *)pitem;
cur_binding_sumchk = (plfni->ChkVal)[0];
result = Get_Part_Name(lfn_buf, plfni, (u8)((((plfni->AttrByte[0]) & 0XBF) - 1) * 13));
if (result) is_lfn_buf_err = 1; 
	}
	#endif
	}
	}

	Cur_Clust = Get_Next_Cluster(Cur_Clust);
	}while (!IS_END_CLU(Cur_Clust)) ;

return ERR_NO_DIR; 
}
#endif
//-----------------------------------------------------------------
// 进入目录获取目录的开始簇
//-----------------------------------------------------------------
#ifdef FAT_ENTER_DIR
u8 FAT_Enter_Dir(char* dirpath, u32* pCluster, u32* pos)
{
	u8 index = 0, res = 0;
	u32 i = 1;
# ifndef USE_LFN
	char dirname[13];
#else
	char dirname[MAX_LFN_LEN + 1];
#endif

	*pos = 1;
	*pCluster = 2;

	if (('\\' == dirpath[0] || '/' == dirpath[0]) && '\0' == dirpath[1])
	{
		return ERR_SUCC;
	}

	while ('\0' != dirpath[i])
	{
		if ('\\' == dirpath[i] || '/' == dirpath[i])
		{
			dirname[index] = '\0';
			index = 0;

			res = Get_Dir_Start_Cluster(dirname, pCluster);
			if (res)
			{
				return res;
			}
			*pos = i + 1;
		}
		else
		{
			dirname[index] = dirpath[i];
			index++;
# ifndef USE_LFN
			if (index > 12)
			{
				return ERR_SFN_ILL_LEN;
			}
#else
			if (index > MAX_LFN_LEN)
			{
				return ERR_LFN_BUF_OUT;
			}
#endif
		}
		i++;
	}
	return ERR_SUCC;
}
#endif
//-----------------------------------------------------------------
// 由给定的短文件名及时间信息构造出文件目录项
//-----------------------------------------------------------------
# ifdef FILL_FDI
u8 Fill_FDI(struct FDI *pfdi, char* pfn,struct DateTime *pdt, u8 is_file){
	u8 dot_pos = 0, have_dot = 0, lowcase = 0;
	u8 i = 0, j = 0, fn_len = (u8)StringLen(pfn);
	u16 time = 0, date = 0;
	Memory_Set(((u8*)pfdi), FDI_NBYTES, 0);
	for (i = (u8)(fn_len - 1); i > 0; i--)
	{
		if ('.' == pfn[i])
		{
			dot_pos = i;
			have_dot = 1;
			break;
		}
	}

	if (have_dot)
	{
		for (i = 0; i < dot_pos; i++)
		{
			(pfdi->Name)[i] = (char)Lower2Up(pfn[i]);
		}
		for (; i < 8; i++)
		{
			(pfdi->Name)[i] = ' ';
		}
		for (i = (u8)(dot_pos + 1); i < fn_len; i++)
		{
			(pfdi->Extension)[j] = (u8)Lower2Up(pfn[i]);
			j++;
		}
		for (; j < 3; j++)
		{
			(pfdi->Extension)[j] = ' ';
		}
	}
	else
	{
		for (i = 0; i < fn_len; i++)
		{
			(pfdi->Name)[i] = (u8)Lower2Up(pfn[i]);
		}
		for (; i < 8; i++)
		{
			(pfdi->Name)[i] = ' ';
		}
		for (j = 0; j < 3; j++)
		{
			(pfdi->Extension)[j] = ' ';
		}
	}
	pfdi->Attributes = (u8)(is_file ? 0X20 : 0X30);
	lowcase = Check_SFN_Illegal_Lower(pfn);
	if ((lowcase & 0X0F) == 0X01)
	{
		pfdi->LowerCase |= 0X08;
	}
	if ((lowcase & 0XF0) == 0X10)
	{
		pfdi->LowerCase |= 0X10;
	}

	pfdi->CTime10ms = (u8)((((pdt->time).sec) % 2) ? 0X78 : 0X00);
	time = (u16)(MAKE_TIME((pdt->time).hour, (pdt->time).min, (pdt->time).sec));
	(pfdi->CTime)[0] = (u8)time;
	(pfdi->CTime)[1] = (u8)(time >> 8);
	date = (u16)(MAKE_DATE((pdt->date).year, (pdt->date).month, (pdt->date).day));
	(pfdi->CDate)[0] = (u8)date;
	(pfdi->CDate)[1] = (u8)(date >> 8);
	(pfdi->ADate)[0] = (u8)date;
	(pfdi->ADate)[1] = (u8)(date >> 8);
	(pfdi->MTime)[0] = (u8)time;
	(pfdi->MTime)[1] = (u8)(time >> 8);
	(pfdi->MDate)[0] = (u8)date;
	(pfdi->MDate)[1] = (u8)(date >> 8);
	if (!is_file)
	{
		pfdi->HighClust[0] = (u8)(((pInitInfo->Next_Free_Cluster) >> 16) & 0X000000FF);
		pfdi->HighClust[1] = (u8)(((pInitInfo->Next_Free_Cluster) >> 24) & 0X000000FF);
		pfdi->LowClust[0] = (u8)(((pInitInfo->Next_Free_Cluster)) & 0X000000FF);
		pfdi->LowClust[1] = (u8)(((pInitInfo->Next_Free_Cluster) >> 8) & 0X000000FF);
	}

	//文件大小字段暂置为0
	return 0;
}
#endif
//-----------------------------------------------------------------
// 构造好的文件目录项注册到目录簇
//-----------------------------------------------------------------
# ifdef REGISTER_FDI
u8 Register_FDI(u32 cluster,struct FDI *pfdi, u32* psec, u8 * pn) {
	u32 temp_sec = 0, old_cluster = 0;
	u8 iSec = 0, iFDI = 0;
	struct FDIesInSEC *pfdis;

if (0 == pInitInfo->Free_nCluster) return ERR_NO_SPACE;
do
{
	temp_sec = SOC(cluster);
	for (iSec = 0; iSec < (pInitInfo->SectorsPerClust); iSec++)
	{
		FAT_Device_Read_Sector(temp_sec + (u32)iSec, FAT_Buffer);
		pfdis = ((struct FDIesInSEC *)FAT_Buffer);
for (iFDI = 0; iFDI < NFDI_PER_SEC; iFDI++)
{
	if (Memory_Compare((u8*)((pfdis->FDIes) + iFDI), (u8*)pfdi, 11))  //比较文件名
	{
		*psec = temp_sec + (u32)iSec;
		*pn = iFDI;
		return ERR_FDI_ALREADY_EXISTING;
	}
	else
	{
		if (0 == ((((pfdis->FDIes)[iFDI]).Name)[0]))
		{
			*psec = temp_sec + (u32)iSec;
			*pn = iFDI;
			FAT_Device_Read_Sector(*psec, FAT_Buffer);
			Memory_Copy((u8*)((((struct FDIesInSEC *)FAT_Buffer)->FDIes)+*pn),(u8*)pfdi, FDI_NBYTES);
FAT_Device_Write_Sector(*psec, FAT_Buffer);
return ERR_SUCC;
		 }
			}
		 }
		}
		old_cluster = cluster;
cluster = Get_Next_Cluster(cluster);
	}while (!IS_END_CLU(cluster)) ;

if (0 != pInitInfo->Free_nCluster)
{
	Modify_FAT(old_cluster, pInitInfo->Next_Free_Cluster);
	Modify_FAT(pInitInfo->Next_Free_Cluster, 0X0FFFFFFF);
	Clear_Cluster(pInitInfo->Next_Free_Cluster);

	*psec = SOC(pInitInfo->Next_Free_Cluster);
	*pn = 0;

	FAT_Device_Read_Sector(*psec, FAT_Buffer);
	Memory_Copy((u8*)((((struct FDIesInSEC *)FAT_Buffer)->FDIes)),(u8*)pfdi, FDI_NBYTES);
FAT_Device_Write_Sector(*psec, FAT_Buffer);

Update_Next_Free_Cluster();

return ERR_SUCC;  
	}
	else
{
	return ERR_NO_SPACE;
} 
	}
	#endif
//-----------------------------------------------------------------
// 文件创建
//-----------------------------------------------------------------
#ifdef FAT_CREATE_FILE
u8 FAT_Create_File(struct FileInfo *pfi, char* pfn,struct DateTime *pdt) {
	u32 Cur_Cluster = 0, pos = 0, sec = 0;
	u8 res = 0, n = 0;
	struct FDI fdi;
char* filename;

# ifdef USE_LFN
u8 is_lfn = 0;
char temp_filename[13];
#endif

just_file = pfi;

# ifndef RT_UPDATE_CLUSTER_CHAIN
get_next_cluster_in_cccb = 0;
# ifdef USE_ALONE_CCCB
CCCB_To_Alone();
Memory_Set((u8*)pcccb_buf, sizeof(u32) * CCCB_LEN, 0);
#endif
#endif

# ifdef USE_EXCHANGE_BUFFER
# ifdef USE_ALONE_EXB
just_file->exb_cursec = 0;
#endif
#endif

res = FAT_Enter_Dir(pfn, &Cur_Cluster, &pos);
if (res)
{
	return res;
}

filename = pfn + pos;

if (Check_Illegal_Char(filename)) return ERR_ILL_CHAR;

# ifdef USE_LFN
if (!Is_LFN(filename))
{
#endif

	if (Check_SFN_Illegal_Length(filename)) return ERR_SFN_ILL_LEN;
	if (Check_SFN_Dot(filename)) return ERR_SFN_DOT;
	if (Check_SFN_Special_Char(filename)) return ERR_SFN_SPEC_CHAR;
	if (((u8)(-1)) == Check_SFN_Illegal_Lower(filename)) return ERR_SFN_ILL_LOWER;
# ifdef USE_LFN
}
else
{
	is_lfn = 1;
	res = oemstr2unistr(filename, pfi->longname);
	if (res) return res;
}

if (!is_lfn)
{
#endif
	Fill_FDI(&fdi, filename, pdt, BOOL_TRUE);
	res = Register_FDI(Cur_Cluster, &fdi, &sec, &n);

# ifdef USE_LFN
}
else
{
	Make_Short_Name(filename, temp_filename);
	Fill_FDI(&fdi, temp_filename, pdt, BOOL_TRUE);
	res = Register_LFN_FDI(Cur_Cluster, &fdi, (pfi->longname), &sec, &n);
}
#endif

if (!res)
{
# ifdef USE_LFN
	if (is_lfn)
	{
		StringCopy(pfi->File_Name, temp_filename);
		pfi->have_lfn = 1;
	}
	else
#endif
	{
		StringCopy(pfi->File_Name, filename);
	}
	pfi->File_Attr = 0X20;
	(pfi->File_CTime).hour = (pdt->time).hour;
	(pfi->File_CTime).min = (pdt->time).min;
	(pfi->File_CTime).sec = (pdt->time).sec;
	(pfi->File_CDate).year = (pdt->date).year;
	(pfi->File_CDate).month = (pdt->date).month;
	(pfi->File_CDate).day = (pdt->date).day;
	//(pfi->File_ADate).year=(pdt->date).year;
	//(pfi->File_ADate).month=(pdt->date).month;
	//(pfi->File_ADate).day=(pdt->date).day;
	//(pfi->File_MTime).hour=(pdt->time).hour;
	//(pfi->File_MTime).min=(pdt->time).min;
	//(pfi->File_MTime).sec=(pdt->time).sec;
	//(pfi->File_MDate).year=(pdt->date).year;
	//(pfi->File_MDate).month=(pdt->date).month;
	//(pfi->File_MDate).day=(pdt->date).day;

	pfi->File_StartClust = 0;
	pfi->File_Size = 0;

	pfi->File_CurClust = 0;
	pfi->File_CurSec = 0;
	pfi->File_CurPos = 0;

	pfi->File_CurOffset = 0;
	pfi->File_IsEOF = BOOL_TRUE;

	pfi->FDI_Sec = sec;
	pfi->nFDI = n;

	return ERR_SUCC;
}
else
{
	if (res == ERR_FDI_ALREADY_EXISTING)
	{
		FAT_Device_Read_Sector(sec, FAT_Buffer);
		Analyse_FDI(pfi, (((struct FDIesInSEC *)FAT_Buffer)->FDIes)+n);
pfi->FDI_Sec = sec;
pfi->nFDI = n;

# ifdef USE_LFN
if (is_lfn)
{
	pfi->have_lfn = 1;
}
else
{
	pfi->have_lfn = 0;
}
	 #endif 
	}
	return res;
	}
}
#endif
//-----------------------------------------------------------------
// 在一个目录中创建一个目录
//-----------------------------------------------------------------
#ifdef CREATE_DIR_IN_CLUSTER
u8 Create_Dir_In_Cluster(u32* cluster, char* pdn,struct DateTime *pdt){
	u8 res = 0, i = 0;
	u32 dummy = 0;
struct FDI fdi;

# ifdef USE_LFN
u8 is_lfn = 0;
u16 temp_lfn_buf[MAX_LFN_LEN + 1];
char temp_dirname[13];
#endif

# ifndef RT_UPDATE_CLUSTER_CHAIN
get_next_cluster_in_cccb = 0;
#endif

if (Check_Illegal_Char(pdn)) return ERR_ILL_CHAR;

# ifdef USE_LFN
if (!Is_LFN(pdn))
{
#endif
	if (Check_SFN_Illegal_Length(pdn)) return ERR_SFN_ILL_LEN;
	if (Check_SFN_Dot(pdn)) return ERR_SFN_DOT;
	if (Check_SFN_Special_Char(pdn)) return ERR_SFN_SPEC_CHAR;
	if (((u8)(-1)) == Check_SFN_Illegal_Lower(pdn)) return ERR_SFN_ILL_LOWER;
# ifdef USE_LFN
}
else
{
	is_lfn = 1;
	res = oemstr2unistr(pdn, temp_lfn_buf);
	if (res) return res;
}

if (!is_lfn)
{
#endif
	Fill_FDI(&fdi, pdn, pdt, BOOL_FALSE);
	res = Register_FDI(*cluster, &fdi, &dummy, &i);

# ifdef USE_LFN
}
else
{
	Make_Short_Name(pdn, temp_dirname);
	Fill_FDI(&fdi, temp_dirname, pdt, BOOL_FALSE);
	res = Register_LFN_FDI(*cluster, &fdi, temp_lfn_buf, &dummy, &i);
}
#endif

if (res)
{
	return res;
}

Modify_FAT(pInitInfo->Next_Free_Cluster, 0X0FFFFFFF);
Clear_Cluster(pInitInfo->Next_Free_Cluster);

fdi.Name[0] = '.';
for (i = 1; i < 11; i++)
{
	fdi.Name[i] = ' ';
}

Memory_Copy(FAT_Buffer, ((u8*)(&fdi)), FDI_NBYTES);
fdi.Name[1] = '.';
if (2 != (*cluster))
{
	fdi.HighClust[0] = (u8)(((*cluster) >> 16) & 0X000000FF);
	fdi.HighClust[1] = (u8)(((*cluster) >> 24) & 0X000000FF);
	fdi.LowClust[0] = (u8)(((*cluster)) & 0X000000FF);
	fdi.LowClust[1] = (u8)(((*cluster) >> 8) & 0X000000FF);
}
else
{
	fdi.HighClust[0] = fdi.HighClust[1] = fdi.LowClust[0] = fdi.LowClust[1] = 0;
}

Memory_Copy(FAT_Buffer + FDI_NBYTES, ((u8*)(&fdi)), FDI_NBYTES);

FAT_Device_Write_Sector(SOC(pInitInfo->Next_Free_Cluster), FAT_Buffer);

*cluster = (pInitInfo->Next_Free_Cluster);

Update_Next_Free_Cluster();

return ERR_SUCC;
}
#endif

//-----------------------------------------------------------------
// 创建目录
//-----------------------------------------------------------------
#ifdef FAT_CREATE_DIR
u8 FAT_Create_Dir(char* pdp,struct DateTime *pdt) {
	u32 Cur_Cluster = 0, i = 0;
	u8 index = 0, res = 0;

# ifndef USE_LFN
	u8 dirname[13];
#else
	u8 dirname[MAX_LFN_LEN + 1];
#endif

# ifndef RT_UPDATE_CLUSTER_CHAIN
	get_next_cluster_in_cccb = 0;
#endif

	if (FAT_Enter_Dir(pdp, &Cur_Cluster, &i))
	{
		while ('\0' != pdp[i])
		{
			if ('\\' == pdp[i] || '/' == pdp[i])
			{
				dirname[index] = '\0';
				index = 0;
				res = Create_Dir_In_Cluster(&Cur_Cluster, (char*)dirname, pdt);
				if (res)
				{
					return res;
				}
			}
			else
			{
				dirname[index] = pdp[i];
				index++;
# ifndef USE_LFN
				if (index > 12)
				{
					return ERR_SFN_ILL_LEN;
				}
#else
				if (index > MAX_LFN_LEN)
				{
					return ERR_LFN_BUF_OUT;
				}
#endif
			}
			i++;
		}

		return ERR_SUCC;
	}
	else
	{
		return ERR_DIR_ALREADY_EXISTING;
	}
}
#endif

//-----------------------------------------------------------------
// 销毁一个FAT簇链
//-----------------------------------------------------------------
# ifdef DESTROY_FAT_CHAIN
u8 Destroy_FAT_Chain(u32 cluster)
{
	u32 clu_sec = 0, temp1 = 0, temp2 = 0, old_clu = 0, nclu = 1;
	struct FAT_Sec *pFAT_Sec;
if (cluster < (pInitInfo->Next_Free_Cluster))
{
	pInitInfo->Next_Free_Cluster = cluster;
}
old_clu = cluster;
FAT_Device_Read_Sector((old_clu / NITEMSINFATSEC) + (pInitInfo->FirstFATSector), FAT_Buffer);
pFAT_Sec = (struct FAT_Sec *)FAT_Buffer;
cluster = Bytes2Value(((pFAT_Sec->items)[cluster % NITEMSINFATSEC]).Item, 4);
while (!IS_END_CLU(cluster))
{
	nclu++;
	clu_sec = cluster / NITEMSINFATSEC;

	temp1 = old_clu % NITEMSINFATSEC;
	temp2 = old_clu / NITEMSINFATSEC;

	((pFAT_Sec->items)[temp1]).Item[0] = 0;
	((pFAT_Sec->items)[temp1]).Item[1] = 0;
	((pFAT_Sec->items)[temp1]).Item[2] = 0;
	((pFAT_Sec->items)[temp1]).Item[3] = 0;

	if (temp2 != clu_sec)
	{
		FAT_Device_Write_Sector(temp2 + (pInitInfo->FirstFATSector), FAT_Buffer);
		FAT_Device_Write_Sector(temp2 + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);

		FAT_Device_Read_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
	}

	old_clu = cluster;
	cluster = Bytes2Value(((pFAT_Sec->items)[cluster % NITEMSINFATSEC]).Item, 4);
}

temp1 = old_clu % NITEMSINFATSEC;
temp2 = old_clu / NITEMSINFATSEC;

((pFAT_Sec->items)[temp1]).Item[0] = 0;
((pFAT_Sec->items)[temp1]).Item[1] = 0;
((pFAT_Sec->items)[temp1]).Item[2] = 0;
((pFAT_Sec->items)[temp1]).Item[3] = 0;
FAT_Device_Write_Sector(temp2 + (pInitInfo->FirstFATSector), FAT_Buffer);
FAT_Device_Write_Sector(temp2 + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);
pInitInfo->Free_nCluster += nclu;
return ERR_SUCC;
}
#endif
//-----------------------------------------------------------------
// 销毁文件目录项所对应整条簇链
//-----------------------------------------------------------------
#ifdef DESTROY_FDI
u8 Destroy_FDI(struct FDI *pitem) {
	u32 start_cluster = Bytes2Value(pitem->LowClust, 2) + Bytes2Value(pitem->HighClust, 2) * 65536;
	if (0 == start_cluster) return ERR_SUCC;
	Destroy_FAT_Chain(start_cluster);
	return ERR_SUCC;
}
#endif
//-----------------------------------------------------------------
// 搜索目录簇删除子目录项
//-----------------------------------------------------------------
# ifdef HAVE_ANY_SUBDIR_WITH_DEL_FOREFILE
u8 Have_Any_SubDir_With_Del_ForeFile(u32* cluster, u8 for_del_dir)
{
	u8 iSec = 0, iFDI = 0;
	u32 sec_temp = 0;
	u32 temp = *cluster;

 struct FDIesInSEC *pitems;
struct FDI *pitem;

# ifndef RT_UPDATE_CLUSTER_CHAIN
get_next_cluster_in_cccb = 0;
#endif

do
{
	sec_temp = SOC(temp);
	for (iSec = 0; iSec < (pInitInfo->SectorsPerClust); iSec++)
	{
		FAT_Device_Read_Sector(sec_temp + (u32)iSec, FAT_Buffer);
		pitems = (struct FDIesInSEC *)FAT_Buffer;

for (iFDI = 0; iFDI < NFDI_PER_SEC; iFDI++)
{
	pitem = &(pitems->FDIes[iFDI]);

	if ((CHK_ATTR_FILE(pitem->Attributes)) && (0XE5 != pitem->Name[0]))
	{
		Destroy_FDI(pitem);
		FAT_Device_Read_Sector(sec_temp + (u32)iSec, FAT_Buffer);

		pitem->Name[0] = 0XE5;
		pitem->HighClust[0] = pitem->HighClust[1] = 0;

		FAT_Device_Write_Sector(sec_temp + (u32)iSec, FAT_Buffer);
	}

	if ((CHK_ATTR_DIR(pitem->Attributes)) && (0XE5 != pitem->Name[0])
	 && ('.' != pitem->Name[0]))
	{
		if (!for_del_dir)
		{
			*cluster = Bytes2Value(pitem->LowClust, 2) + Bytes2Value(pitem->HighClust, 2) * 65536;
		}
		else
		{
			Destroy_FDI(pitem);
			FAT_Device_Read_Sector(sec_temp + (u32)iSec, FAT_Buffer);

			pitem->Name[0] = 0XE5;
			pitem->HighClust[0] = pitem->HighClust[1] = 0;

			FAT_Device_Write_Sector(sec_temp + (u32)iSec, FAT_Buffer);
		}
		return BOOL_TRUE;
	}
}
	}

	temp = Get_Next_Cluster(temp);
	}while (!IS_END_CLU(temp)) ;
return BOOL_FALSE;
}
#endif
//-----------------------------------------------------------------
// 进入最深的靠前目录
//-----------------------------------------------------------------
#ifdef ENTER_DEEP_AHEAD_DIR
u8 Enter_Deep_Ahead_Dir(u32* cluster)
{
	u32 dir_cluster = *cluster;
	while (Have_Any_SubDir_With_Del_ForeFile(&dir_cluster, BOOL_FALSE)) ;
	*cluster = dir_cluster;
	return ERR_SUCC;
}
#endif
//-----------------------------------------------------------------
// 获取目录上一级目录开始簇
//-----------------------------------------------------------------
# ifdef GET_UPPER_DIR
u8 Get_Upper_Dir(u32* cluster)
{
	struct FDIesInSEC *pitems;
struct FDI *pitem;

FAT_Device_Read_Sector(SOC(*cluster), FAT_Buffer);
pitems = (struct FDIesInSEC *)FAT_Buffer;

pitem = &(pitems->FDIes[1]);

if ('.' == pitem->Name[0] && '.' == pitem->Name[1])

	*cluster = Bytes2Value(pitem->LowClust, 2) + Bytes2Value(pitem->HighClust, 2) * 65536;
else
	return ERR_FS_DIR;

if (0 == (*cluster)) (*cluster) = 2;

return ERR_SUCC;
}
#endif
//-----------------------------------------------------------------
// 删除目录
//-----------------------------------------------------------------
#ifdef FAT_DELETE_DIR
u8 FAT_Delete_Dir(char* dirpath)
{
	u32 top_dir_first_cluster = 0, sub_dir_first_cluster = 0;
	u8 res = 0;

	struct FDIesInSEC *pitems;

struct FileInfo fi;

res = FAT_Open_File(&fi, dirpath, 0, BOOL_FALSE);

if (res) return res;

while (!res)
{
	top_dir_first_cluster = fi.File_StartClust;
	sub_dir_first_cluster = top_dir_first_cluster;
	Enter_Deep_Ahead_Dir(&sub_dir_first_cluster);
	while (sub_dir_first_cluster != top_dir_first_cluster)
	{
		Get_Upper_Dir(&sub_dir_first_cluster);
		Have_Any_SubDir_With_Del_ForeFile(&sub_dir_first_cluster, BOOL_TRUE);
		Enter_Deep_Ahead_Dir(&sub_dir_first_cluster);
	}
	FAT_Device_Read_Sector(fi.FDI_Sec, FAT_Buffer);
	pitems = (struct FDIesInSEC *)FAT_Buffer;

Destroy_FDI((pitems->FDIes) + fi.nFDI);

FAT_Device_Read_Sector(fi.FDI_Sec, FAT_Buffer);
(pitems->FDIes)[fi.nFDI].Name[0] = 0XE5;
(pitems->FDIes)[fi.nFDI].HighClust[0] = (pitems->FDIes)[fi.nFDI].HighClust[1] = 0;

FAT_Device_Write_Sector(fi.FDI_Sec, FAT_Buffer);

res = FAT_Open_File(&fi, dirpath, 0, BOOL_FALSE);
	}

	FAT_Close_File(&fi);

# ifdef RT_UPDATE_FSINFO
Update_FSINFO();
#endif

return ERR_SUCC; 
}
#endif
//-----------------------------------------------------------------
// 文件删除
//-----------------------------------------------------------------
#ifdef FAT_DELETE_FILE
u8 FAT_Delete_File(char* filepath)
{
	u8 res = 0;
	struct FileInfo fi;
struct FDIesInSEC *pitems;
struct FDI *pitem;
res = FAT_Open_File(&fi, filepath, 0, BOOL_TRUE);
if (res) return res;
while (!res)
{
	FAT_Device_Read_Sector(fi.FDI_Sec, FAT_Buffer);
	pitems = (struct FDIesInSEC *)FAT_Buffer;
pitem = (pitems->FDIes) + fi.nFDI;
if (0 != fi.File_StartClust) Destroy_FAT_Chain(fi.File_StartClust);
FAT_Device_Read_Sector(fi.FDI_Sec, FAT_Buffer);
pitem->Name[0] = 0XE5;
pitem->HighClust[0] = pitem->HighClust[1] = 0;
FAT_Device_Write_Sector(fi.FDI_Sec, FAT_Buffer);
res = FAT_Open_File(&fi, filepath, 0, BOOL_TRUE);
	}

	FAT_Close_File(&fi);
# ifdef RT_UPDATE_FSINFO
Update_FSINFO();
#endif
return ERR_SUCC; 
}
#endif
//-----------------------------------------------------------------
// 获取某磁盘容量下簇大小的推荐值
//-----------------------------------------------------------------
#ifdef GET_RECMD_SZCLU
u8 Get_Recmd_szClu(u32 nsec)
{
	if (nsec < (14336)) return 0;
	if ((nsec >= (14336)) && (nsec <= (32767))) return 0;
	if ((nsec >= (32768)) && (nsec <= (65535))) return 1;
	if ((nsec >= (65536)) && (nsec <= (131071))) return 1;
	if ((nsec >= (131072)) && (nsec <= (262143))) return 2;
	if ((nsec >= (262144)) && (nsec <= (524287))) return 4;
	if ((nsec >= (524288)) && (nsec <= (16777215))) return 8;
	if ((nsec >= (16777216)) && (nsec <= (33554431))) return 16;
	if ((nsec >= (33554432)) && (nsec <= (67108863))) return 32;
	if ((nsec >= (67108864)) && (nsec <= (4294967295UL))) return 64;
	return 0;
}
#endif
//-----------------------------------------------------------------
// 在磁盘上创建FAT32文件系统
//-----------------------------------------------------------------
# ifdef FAT_FORMAT_FS
u8 FAT_Format_FS(u32 tt_sec, u16 clu_sz)
{
	struct DBR      *pdbr;
struct FSInfo   *pfsinfo;
u32 temp = 0, temp1 = 0, temp2 = 0;

tt_sec /= (u32)(NSECPERCYLINDER);
tt_sec *= (u32)(NSECPERCYLINDER);
PGM2RAM(FAT_Buffer, _dbr, 512);
pdbr = (struct DBR *)FAT_Buffer;
pdbr->BPB_SecPerClus = (u8)(clu_sz / 512);
if (0 == pdbr->BPB_SecPerClus) pdbr->BPB_SecPerClus = Get_Recmd_szClu(tt_sec);
if (0 == pdbr->BPB_SecPerClus) return ERR_FMT_TOO_LOW_VOLUME;

temp1 = pdbr->BPB_SecPerClus;

pdbr->BPB_TotSec32[0] = (u8)((tt_sec) & 0X000000FF);
pdbr->BPB_TotSec32[1] = (u8)((tt_sec >> 8) & 0X000000FF);
pdbr->BPB_TotSec32[2] = (u8)((tt_sec >> 16) & 0X000000FF);
pdbr->BPB_TotSec32[3] = (u8)((tt_sec >> 24) & 0X000000FF);

temp = (tt_sec - 32) / (((u32)NITEMSINFATSEC) * ((u32)(pdbr->BPB_SecPerClus)));
if ((tt_sec - 32) % ((u32)NITEMSINFATSEC) * ((u32)pdbr->BPB_SecPerClus)) temp++;
temp2 = temp;

pdbr->BPB_FATSz32[0] = (u8)((temp) & 0X000000FF);
pdbr->BPB_FATSz32[1] = (u8)((temp >> 8) & 0X000000FF);
pdbr->BPB_FATSz32[2] = (u8)((temp >> 16) & 0X000000FF);
pdbr->BPB_FATSz32[3] = (u8)((temp >> 24) & 0X000000FF);

FAT_Device_Write_Sector(0, FAT_Buffer);

Memory_Set(FAT_Buffer, FAT_BUF_SIZE, 0);
PGM2RAM(FAT_Buffer, _fsinfo_1, 4);
PGM2RAM(FAT_Buffer + 484, _fsinfo_2, 28);
pfsinfo = (struct FSInfo *)FAT_Buffer;
temp = (tt_sec - 32 - 2 * temp) / ((u32)(temp1)) - 1;
pfsinfo->Free_Cluster[0] = (u8)((temp) & 0X000000FF);
pfsinfo->Free_Cluster[1] = (u8)((temp >> 8) & 0X000000FF);
pfsinfo->Free_Cluster[2] = (u8)((temp >> 16) & 0X000000FF);
pfsinfo->Free_Cluster[3] = (u8)((temp >> 24) & 0X000000FF);

FAT_Device_Write_Sector(1, FAT_Buffer);
FAT_Device_Clear_nSector(temp1, 32 + 2 * temp2);
FAT_Device_Clear_nSector(temp2 - 1, 33);
FAT_Device_Clear_nSector(temp2 - 1, 33 + temp2);

PGM2RAM(FAT_Buffer, _fatsec, 12);
FAT_Device_Write_Sector(32, FAT_Buffer);
FAT_Device_Write_Sector(32 + temp2, FAT_Buffer);
PGM2RAM(FAT_Buffer, _1stsec, 26);
FAT_Device_Write_Sector(32 + 2 * temp2, FAT_Buffer); ===
	return ERR_SUCC;
}  
#endif

//-----------------------------------------------------------------
// 更新文件的大小
//-----------------------------------------------------------------
#ifdef UPDATE_FILE_SIZE
u8 Update_File_Size(struct FileInfo *pfi) {
	struct FDI *pfdi;
just_file = pfi;
FAT_Device_Read_Sector(pfi->FDI_Sec, FAT_Buffer);
pfdi = (((struct FDIesInSEC *)FAT_Buffer)->FDIes)+(pfi->nFDI);
(pfdi->FileSize)[0] = (u8)((pfi->File_Size) & 0X000000FF);
(pfdi->FileSize)[1] = (u8)(((pfi->File_Size) & 0X0000FF00) >> 8);
(pfdi->FileSize)[2] = (u8)(((pfi->File_Size) & 0X00FF0000) >> 16);
(pfdi->FileSize)[3] = (u8)(((pfi->File_Size) & 0XFF000000) >> 24);
FAT_Device_Write_Sector(pfi->FDI_Sec, FAT_Buffer);
return 0;
}
#endif
//-----------------------------------------------------------------
// 更新文件的开始簇
//-----------------------------------------------------------------
#ifdef UPDATE_FILE_SCLUST
u8 Update_File_sClust(struct FileInfo *pfi, u32 clu) {
	struct FDI *pfdi;

just_file = pfi;

FAT_Device_Read_Sector(pfi->FDI_Sec, FAT_Buffer);

pfdi = (((struct FDIesInSEC *)FAT_Buffer)->FDIes)+(pfi->nFDI);
pfi->File_StartClust = clu;

(pfdi->HighClust)[0] = (u8)((clu & 0X00FF0000) >> 16);
(pfdi->HighClust)[1] = (u8)((clu & 0XFF000000) >> 24);
(pfdi->LowClust)[0] = (u8)((clu & 0X000000FF));
(pfdi->LowClust)[1] = (u8)((clu & 0X0000FF00) >> 8);

FAT_Device_Write_Sector(pfi->FDI_Sec, FAT_Buffer);

return 0; 
}
#endif
//-----------------------------------------------------------------
// 创建一条簇链
//-----------------------------------------------------------------
#ifdef CREATE_CLUSTER_CHAIN
u8 Create_Cluster_Chain(struct FileInfo *pfi, u32 cluster, u32 datalen){
	u32 iSec = 0, clu_sec = 0, old_clu = cluster, ncluster = 0, temp_ncluster = 0;
	u8 iItem = 0, temp = 0;
	struct FAT_Sec *pFAT_Sec = (struct FAT_Sec *)FAT_Buffer;

u32 Clu_Size = (pInitInfo->SectorsPerClust * pInitInfo->BytesPerSector);

just_file = pfi;

# ifndef RT_UPDATE_CLUSTER_CHAIN
# ifdef USE_ALONE_CCCB
CCCB_To_Alone();
#endif
#endif

ncluster = datalen / Clu_Size;
if (0 != datalen % Clu_Size) ncluster++;
temp_ncluster = ncluster;

if ((pInitInfo->Free_nCluster) < ncluster) return ERR_NO_SPACE;

# ifndef RT_UPDATE_CLUSTER_CHAIN
# ifndef USE_ALONE_CCCB
if (pfi != pcccb_cur_oc)
{
	CCCB_Update_FAT();
	pcccb_cur_oc = pfi;
	(*pcccb_curdev) = Dev_No;
	pcccb_cur_initinfo = pInitInfo;
}
#endif
	(*pcccb_curval) = cluster;
#endif
cluster = (pInitInfo->Next_Free_Cluster);

pfi->File_CurClust = pInitInfo->Next_Free_Cluster;
pfi->File_CurSec = SOC(pfi->File_CurClust);
ncluster--;
if (0 != old_clu)
{
	clu_sec = (old_clu / NITEMSINFATSEC);
	FAT_Device_Read_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);

# ifdef RT_UPDATE_CLUSTER_CHAIN
	temp = (u8)(old_clu % NITEMSINFATSEC);
	(((pFAT_Sec->items)[temp]).Item)[0] = (u8)(cluster & 0X000000FF);
	(((pFAT_Sec->items)[temp]).Item)[1] = (u8)((cluster & 0X0000FF00) >> 8);
	(((pFAT_Sec->items)[temp]).Item)[2] = (u8)((cluster & 0X00FF0000) >> 16);
	(((pFAT_Sec->items)[temp]).Item)[3] = (u8)((cluster & 0XFF000000) >> 24);
#else
	if (0 == (*pcccb_counter))
	{
		pcccb_buf[(*pcccb_counter)] = (*pcccb_curval);
		(*pcccb_counter)++;
	}

	if (cluster == ((*pcccb_curval) + 1))
	{
		(*pcccb_curval)++;
	}
	else
	{
		if (((*pcccb_counter) + 1) != CCCB_LEN)
		{
			pcccb_buf[(*pcccb_counter)] = (*pcccb_curval);

			(*pcccb_counter)++;
			pcccb_buf[(*pcccb_counter)] = cluster;
			(*pcccb_curval) = cluster;
			(*pcccb_counter)++;
		}
		else
		{
			CCCB_Update_FAT();
# ifndef USE_ALONE_CCCB
			pcccb_cur_oc = pfi;
			(*pcccb_curdev) = Dev_No;
			pcccb_cur_initinfo = pInitInfo;
#endif

			(*pcccb_counter) = 0;
			pcccb_buf[(*pcccb_counter)] = pcccb_buf[(*pcccb_counter) + 1] = (*pcccb_curval);
			pcccb_buf[(*pcccb_counter) + 2] = cluster;
			(*pcccb_curval) = cluster;
			(*pcccb_counter) += 3;
		}
	}
#endif
}
else
{
	clu_sec = (cluster / NITEMSINFATSEC);
	FAT_Device_Read_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);

# ifndef RT_UPDATE_CLUSTER_CHAIN
	(*pcccb_counter) = 0;
	pcccb_buf[(*pcccb_counter)] = cluster;
	(*pcccb_curval) = cluster;
	(*pcccb_counter)++;
#endif
}

# ifdef RT_UPDATE_CLUSTER_CHAIN
if (clu_sec == (cluster / NITEMSINFATSEC))
{
	if (0 == ncluster)
	{
		temp = (u8)(cluster % NITEMSINFATSEC);
		(((pFAT_Sec->items)[temp]).Item)[0] = 0XFF;
		(((pFAT_Sec->items)[temp]).Item)[1] = 0XFF;
		(((pFAT_Sec->items)[temp]).Item)[2] = 0XFF;
		(((pFAT_Sec->items)[temp]).Item)[3] = 0X0F;

		FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
		FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);
	}
}
else
{
	FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
	FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);

	clu_sec = (cluster / NITEMSINFATSEC);
	FAT_Device_Read_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);

	if (0 == ncluster)
	{
		temp = (u8)(cluster % NITEMSINFATSEC);

		(((pFAT_Sec->items)[temp]).Item)[0] = 0XFF;
		(((pFAT_Sec->items)[temp]).Item)[1] = 0XFF;
		(((pFAT_Sec->items)[temp]).Item)[2] = 0XFF;
		(((pFAT_Sec->items)[temp]).Item)[3] = 0X0F;

		FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
		FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);
	}
}
#endif

if (0 == ncluster)
{
	pInitInfo->Free_nCluster -= temp_ncluster;

	Update_Next_Free_Cluster();

# ifdef RT_UPDATE_FSINFO
	Update_FSINFO();
#endif

	return ERR_SUCC;
}

old_clu = cluster;

//=============================================================================================

clu_sec = (old_clu / NITEMSINFATSEC);

if (((u8)((cluster % NITEMSINFATSEC) + 1)) != ((u8)NITEMSINFATSEC))
{
	FAT_Device_Read_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);

	for (iItem = (u8)((cluster % NITEMSINFATSEC) + 1); iItem < NITEMSINFATSEC; iItem++)
	{
		cluster++;
		if (0 == (((pFAT_Sec->items)[iItem]).Item)[0]
		&& 0 == (((pFAT_Sec->items)[iItem]).Item)[1]
		&& 0 == (((pFAT_Sec->items)[iItem]).Item)[2]
		&& 0 == (((pFAT_Sec->items)[iItem]).Item)[3])
		{
# ifdef RT_UPDATE_CLUSTER_CHAIN
			temp = (u8)(old_clu % NITEMSINFATSEC);

			(((pFAT_Sec->items)[temp]).Item)[0] = (u8)(cluster & 0X000000FF);
			(((pFAT_Sec->items)[temp]).Item)[1] = (u8)((cluster & 0X0000FF00) >> 8);
			(((pFAT_Sec->items)[temp]).Item)[2] = (u8)((cluster & 0X00FF0000) >> 16);
			(((pFAT_Sec->items)[temp]).Item)[3] = (u8)((cluster & 0XFF000000) >> 24);
#else
			if (cluster == ((*pcccb_curval) + 1))
			{
				(*pcccb_curval)++;
			}
			else
			{
				if (((*pcccb_counter) + 1) != CCCB_LEN) //CCCB没有溢出
				{
					pcccb_buf[(*pcccb_counter)] = (*pcccb_curval);

					(*pcccb_counter)++;
					pcccb_buf[(*pcccb_counter)] = cluster;
					(*pcccb_curval) = cluster;
					(*pcccb_counter)++;
				}
				else
				{
					CCCB_Update_FAT();
# ifndef USE_ALONE_CCCB
					pcccb_cur_oc = pfi;
					(*pcccb_curdev) = Dev_No;
					pcccb_cur_initinfo = pInitInfo;
#endif

					(*pcccb_counter) = 0;
					pcccb_buf[(*pcccb_counter)] = pcccb_buf[(*pcccb_counter) + 1] = (*pcccb_curval);
					pcccb_buf[(*pcccb_counter) + 2] = cluster;
					(*pcccb_curval) = cluster;
					(*pcccb_counter) += 3;
				}
			}
#endif
			ncluster--;
			old_clu = cluster;
		}

		if (0 == ncluster)
		{
# ifdef RT_UPDATE_CLUSTER_CHAIN
			(((pFAT_Sec->items)[iItem]).Item)[0] = 0XFF;
			(((pFAT_Sec->items)[iItem]).Item)[1] = 0XFF;
			(((pFAT_Sec->items)[iItem]).Item)[2] = 0XFF;
			(((pFAT_Sec->items)[iItem]).Item)[3] = 0X0F;

			FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
			FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);
#endif
			pInitInfo->Free_nCluster -= temp_ncluster;
			pInitInfo->Next_Free_Cluster = cluster;

			Update_Next_Free_Cluster();

# ifdef RT_UPDATE_FSINFO
			Update_FSINFO();
#endif

			return ERR_SUCC;
		}
	}
}
# ifdef RT_UPDATE_CLUSTER_CHAIN
FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);
#endif
//=============================================================================================

for (iSec = (clu_sec + 1); iSec < (pInitInfo->FATsectors); iSec++)
{
	FAT_Device_Read_Sector(iSec + (pInitInfo->FirstFATSector), FAT_Buffer);

	for (iItem = 0; iItem < NITEMSINFATSEC; iItem++)
	{
		cluster++;

		if (0 == (((pFAT_Sec->items)[iItem]).Item)[0]
		&& 0 == (((pFAT_Sec->items)[iItem]).Item)[1]
		&& 0 == (((pFAT_Sec->items)[iItem]).Item)[2]
		&& 0 == (((pFAT_Sec->items)[iItem]).Item)[3])
		{
# ifdef RT_UPDATE_CLUSTER_CHAIN
			clu_sec = (old_clu / NITEMSINFATSEC);
			temp = (u8)(old_clu % NITEMSINFATSEC);

			if (iSec != clu_sec)
			{
				Modify_FAT(old_clu, cluster);

				FAT_Device_Read_Sector(iSec + (pInitInfo->FirstFATSector), FAT_Buffer);
			}
			else
			{
				(((pFAT_Sec->items)[temp]).Item)[0] = (u8)(cluster & 0X000000FF);
				(((pFAT_Sec->items)[temp]).Item)[1] = (u8)((cluster & 0X0000FF00) >> 8);
				(((pFAT_Sec->items)[temp]).Item)[2] = (u8)((cluster & 0X00FF0000) >> 16);
				(((pFAT_Sec->items)[temp]).Item)[3] = (u8)((cluster & 0XFF000000) >> 24);
			}
#else
			if (cluster == ((*pcccb_curval) + 1))
			{
				(*pcccb_curval)++;
			}
			else
			{
				if (((*pcccb_counter) + 1) != CCCB_LEN)
				{
					pcccb_buf[(*pcccb_counter)] = (*pcccb_curval);

					(*pcccb_counter)++;
					pcccb_buf[(*pcccb_counter)] = cluster;
					(*pcccb_curval) = cluster;
					(*pcccb_counter)++;
				}
				else
				{
					CCCB_Update_FAT();
# ifndef USE_ALONE_CCCB
					pcccb_cur_oc = pfi;
					(*pcccb_curdev) = Dev_No;
					pcccb_cur_initinfo = pInitInfo;
#endif

					(*pcccb_counter) = 0;
					pcccb_buf[(*pcccb_counter)] = pcccb_buf[(*pcccb_counter) + 1] = (*pcccb_curval);
					pcccb_buf[(*pcccb_counter) + 2] = cluster;
					(*pcccb_curval) = cluster;
					(*pcccb_counter) += 3;
				}
			}
#endif
			ncluster--;
			old_clu = cluster;
		}

		if (0 == ncluster)
		{
# ifdef RT_UPDATE_CLUSTER_CHAIN
			clu_sec = (old_clu / NITEMSINFATSEC);

			(((pFAT_Sec->items)[iItem]).Item)[0] = 0XFF;
			(((pFAT_Sec->items)[iItem]).Item)[1] = 0XFF;
			(((pFAT_Sec->items)[iItem]).Item)[2] = 0XFF;
			(((pFAT_Sec->items)[iItem]).Item)[3] = 0X0F;

			FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector), FAT_Buffer);
			FAT_Device_Write_Sector(clu_sec + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);
#endif
			pInitInfo->Free_nCluster -= temp_ncluster;
			pInitInfo->Next_Free_Cluster = cluster;

			Update_Next_Free_Cluster();

# ifdef RT_UPDATE_FSINFO
			Update_FSINFO();
#endif

			return ERR_SUCC;
		}
	}
# ifdef RT_UPDATE_CLUSTER_CHAIN
	FAT_Device_Write_Sector(iSec + (pInitInfo->FirstFATSector), FAT_Buffer);
	FAT_Device_Write_Sector(iSec + (pInitInfo->FirstFATSector + pInitInfo->FATsectors), FAT_Buffer);
#endif
}

return ERR_FAIL;
}
#endif

//-----------------------------------------------------------------
// 从文件整簇位置开始写入数据
//-----------------------------------------------------------------
#ifdef WRITEDATA_FROM_NCLUSTER
u32 WriteData_From_nCluster(struct FileInfo *pfi, u32 len, u8* pbuf){
	u32 CluSize = ((pInitInfo->BytesPerSector) * (pInitInfo->SectorsPerClust));
	u32 temp = len / CluSize;
	u32 iClu = 0, start_clu = 0, end_clu = 0, next_clu = 0;
	u32 temp1 = 0, temp2 = 0;
	u8 res = 0;

# ifdef USE_EXCHANGE_BUFFER
# ifndef USE_ALONE_EXB
	u8 old_devno = Dev_No;
#else
	pexb_buf = (pfi->exb_buf);
#endif
#endif

	just_file = pfi;

# ifndef RT_UPDATE_CLUSTER_CHAIN
	get_next_cluster_in_cccb = 1;
# ifdef USE_ALONE_CCCB
	CCCB_To_Alone();
#endif
#endif

	if (0 == len) return 0;
	if (0 == pfi->File_CurClust)
	{
		pfi->File_StartClust = pInitInfo->Next_Free_Cluster;
		Update_File_sClust(pfi, pInitInfo->Next_Free_Cluster);
	}

	res = Create_Cluster_Chain(pfi, pfi->File_CurClust, len);
	if (res) return res;
	if (0 == temp)
	{
		temp = len / (pInitInfo->BytesPerSector);
		FAT_Device_Write_nSector(temp, SOC(pfi->File_CurClust), pbuf);
		pfi->File_CurSec += temp;
		pbuf += (temp * (pInitInfo->BytesPerSector));

		temp = len % (pInitInfo->BytesPerSector);
		if (0 != temp)
		{
# ifndef USE_EXCHANGE_BUFFER
			Memory_Copy(FAT_Buffer, pbuf, temp);
			FAT_Device_Write_Sector(pfi->File_CurSec, FAT_Buffer);
#else
# ifndef USE_ALONE_EXB
			if (Dev_No != sexb_cur_dev)
			{
				if (0 != sexb_cur_sec)
				{
					Dev_No = sexb_cur_dev;
					FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);

					Dev_No = old_devno;
				}
			}
			else
			{
				if (sexb_cur_sec != (pfi->File_CurSec))
				{
					if (0 != sexb_cur_sec)
					{
						FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
					}
				}
			}
#endif

			Memory_Copy(pexb_buf, pbuf, temp);

# ifndef USE_ALONE_EXB
			sexb_cur_sec = pfi->File_CurSec;
			sexb_cur_dev = Dev_No;
			psexb_cur_oc = pfi;
#else
			just_file->exb_cursec = pfi->File_CurSec;
#endif
#endif

			pfi->File_CurPos = (u16)temp;
		}
	}
	else
	{
		start_clu = end_clu = pfi->File_CurClust;

		for (iClu = 1; iClu < temp; iClu++)
		{
			next_clu = Get_Next_Cluster(end_clu);

			if ((next_clu - 1) == end_clu)
			{
				end_clu = next_clu;
			}
			else
			{
				FAT_Device_Write_nSector(((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust)), SOC(start_clu), pbuf);
				pbuf += ((end_clu - start_clu + 1) * CluSize);
				start_clu = next_clu;
				end_clu = next_clu;
			}
		}

		temp1 = (len % CluSize) / (pInitInfo->BytesPerSector);
		temp2 = Get_Next_Cluster(end_clu);
		temp = (end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust);

		if (!IS_END_CLU(temp2))
		{
			if ((temp2 - 1) == end_clu)
			{
				FAT_Device_Write_nSector((temp + temp1), SOC(start_clu), pbuf);
				pbuf += ((temp + temp1) * (pInitInfo->BytesPerSector));
			}
			else
			{
				FAT_Device_Write_nSector(((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust)), SOC(start_clu), pbuf);
				pbuf += (temp * (pInitInfo->BytesPerSector));
				FAT_Device_Write_nSector(temp1, SOC(temp2), pbuf);
				pbuf += (temp1 * (pInitInfo->BytesPerSector));
			}

			pfi->File_CurClust = temp2;
			pfi->File_CurSec = (SOC(temp2) + temp1);
			//=======================================================================================
			temp = len % (pInitInfo->BytesPerSector);
			if (0 != temp)
			{
# ifndef USE_EXCHANGE_BUFFER
				Memory_Copy(FAT_Buffer, pbuf, temp);
				FAT_Device_Write_Sector(pfi->File_CurSec, FAT_Buffer);
#else
# ifndef USE_ALONE_EXB
				if (Dev_No != sexb_cur_dev)
				{
					if (0 != sexb_cur_sec)
					{
						Dev_No = sexb_cur_dev;
						FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
						Dev_No = old_devno;
					}
				}
				else
				{
					if (sexb_cur_sec != (pfi->File_CurSec))
					{
						if (0 != sexb_cur_sec)
						{
							FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
						}
					}
				}
#endif

				Memory_Copy(pexb_buf, pbuf, temp);

# ifndef USE_ALONE_EXB
				sexb_cur_sec = pfi->File_CurSec;
				sexb_cur_dev = Dev_No;
				psexb_cur_oc = pfi;
#else
				just_file->exb_cursec = pfi->File_CurSec;
#endif
#endif

				pfi->File_CurPos = (u16)temp;
			}
		}
		else
		{
			FAT_Device_Write_nSector(temp, SOC(start_clu), pbuf);
			pbuf += ((temp + temp1) * (pInitInfo->BytesPerSector));

			pfi->File_CurClust = end_clu;
			pfi->File_CurSec = SOC(end_clu);
		}
	}

# ifdef RT_UPDATE_FSINFO
	Update_FSINFO();
#endif

	pfi->File_CurOffset += len;

	return len;
}
#endif
//-----------------------------------------------------------------
// 向文件中写入数据
//-----------------------------------------------------------------
# ifdef FAT_WRITEDATA
u32 FAT_WriteData(struct FileInfo *pfi, u32 len, u8* pbuf) {
	u32 temp = 0, temp1 = 0, len_temp = len;
	u32 Cluster_Size = ((pInitInfo->BytesPerSector) * (pInitInfo->SectorsPerClust));
# ifdef USE_EXCHANGE_BUFFER
# ifndef USE_ALONE_EXB
	u8 old_devno = Dev_No;
#else
	pexb_buf = (pfi->exb_buf);
#endif
#endif

	just_file = pfi;
# ifndef RT_UPDATE_CLUSTER_CHAIN
	get_next_cluster_in_cccb = 1;
# ifdef USE_ALONE_CCCB
	CCCB_To_Alone();
#endif
#endif

	if (0 == len) return 0;
	if (len > (0XFFFFFFFF - pfi->File_Size)) return (u32) - 2;
	FAT_Seek(pfi, pfi->File_Size);
	if ((pfi->File_CurOffset % Cluster_Size) != 0)
	{
		temp = ((pInitInfo->BytesPerSector) - (pfi->File_CurPos)) +
				((LAST_SEC_OF_CLU(pfi->File_CurClust)) -
				(pfi->File_CurSec)) * (Cluster_Size);
		if (len > temp)
		{
			temp1 = (len - temp) / (Cluster_Size);
			if ((len - temp) % (Cluster_Size)) temp1++;
			if (temp1 > (pInitInfo->Free_nCluster)) return ((u32) - 1);
		}
	}
	else
	{
		temp1 = len / (Cluster_Size);
		if (len % (Cluster_Size)) temp1++;
		if (temp1 > (pInitInfo->Free_nCluster)) return ((u32) - 1);
	}
	//========================================================================
	temp = ((pInitInfo->BytesPerSector) - (pfi->File_CurPos));
	if ((pfi->File_CurOffset % Cluster_Size) != 0)
	{
		if (len <= temp)
		{
# ifndef USE_EXCHANGE_BUFFER
			FAT_Device_Read_Sector(pfi->File_CurSec, FAT_Buffer);
			Memory_Copy(FAT_Buffer + pfi->File_CurPos, pbuf, len);
			FAT_Device_Write_Sector(pfi->File_CurSec, FAT_Buffer);
#endif

			if (len == temp)
			{
# ifdef USE_EXCHANGE_BUFFER
				if (0 != pfi->File_CurPos)
				{
# ifndef USE_ALONE_EXB
					if (Dev_No != sexb_cur_dev)
					{
						if (0 != sexb_cur_sec)
						{
							Dev_No = sexb_cur_dev;
							FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
							Dev_No = old_devno;
						}
						FAT_Device_Read_Sector(pfi->File_CurSec, pexb_buf);
					}
					else
					{
						if (sexb_cur_sec != (pfi->File_CurSec))
						{
							if (0 != sexb_cur_sec)
							{
								FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
								FAT_Device_Read_Sector(pfi->File_CurSec, pexb_buf);
							}
						}
					}
#else
					if (0 == (just_file->exb_cursec))
					{
						FAT_Device_Read_Sector(pfi->File_CurSec, pexb_buf);
					}
#endif
					Memory_Copy(pexb_buf + pfi->File_CurPos, pbuf, len);
					FAT_Device_Write_Sector(pfi->File_CurSec, pexb_buf);
# ifndef USE_ALONE_EXB
					sexb_cur_sec = 0;
					sexb_cur_dev = (u8)(-1);
					psexb_cur_oc = (struct FileInfo *)0;
#else
(just_file->exb_cursec) = 0; 
				#endif
			}
			else
{
	FAT_Device_Write_Sector(pfi->File_CurSec, pbuf);
}
#endif

if (IS_END_SEC_OF_CLU(pfi->File_CurSec, pfi->File_CurClust))
{
	pfi->File_CurSec = SOC(pfi->File_CurClust);
}
else
{
	pfi->File_CurSec++;
}

pfi->File_CurPos = 0;
pfi->File_CurOffset += len;
pfi->File_Size += len;
# ifdef RT_UPDATE_FILESIZE
Update_File_Size(pfi);
#endif

return len;
			}
			else
{
# ifdef USE_EXCHANGE_BUFFER
# ifndef USE_ALONE_EXB
	if (Dev_No != sexb_cur_dev)
	{
		if (0 != sexb_cur_sec)
		{
			Dev_No = sexb_cur_dev;
			FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
			Dev_No = old_devno;
		}
		FAT_Device_Read_Sector(pfi->File_CurSec, pexb_buf);
	}
	else
	{
		if (sexb_cur_sec != (pfi->File_CurSec))
		{
			if (0 != sexb_cur_sec)
			{
				FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
				FAT_Device_Read_Sector(pfi->File_CurSec, pexb_buf);
			}
		}
	}
#else
	if ((0 == (just_file->exb_cursec)) && (0 != (pfi->File_CurPos)))
	{
		FAT_Device_Read_Sector(pfi->File_CurSec, pexb_buf);
	}
#endif
	Memory_Copy(pexb_buf + pfi->File_CurPos, pbuf, len);

# ifndef USE_ALONE_EXB
	sexb_cur_dev = Dev_No;
	sexb_cur_sec = pfi->File_CurSec;
	psexb_cur_oc = pfi;
#else
	(just_file->exb_cursec) = pfi->File_CurSec;
#endif
#endif
	//FAT_Device_Write_Sector(pfi->File_CurSec,ex_buf); 
	pfi->File_CurPos += (u16)len;
	pfi->File_CurOffset += len;
	pfi->File_Size += len;
# ifdef RT_UPDATE_FILESIZE
	Update_File_Size(pfi);
#endif
	return len;
}
		}
	else
{
# ifndef USE_EXCHANGE_BUFFER
	FAT_Device_Read_Sector(pfi->File_CurSec, FAT_Buffer);
	Memory_Copy(FAT_Buffer + pfi->File_CurPos, pbuf, temp);
	FAT_Device_Write_Sector(pfi->File_CurSec, FAT_Buffer);
#else
	if (0 != pfi->File_CurPos)
	{
# ifndef USE_ALONE_EXB
		if (Dev_No != sexb_cur_dev)
		{
			if (0 != sexb_cur_sec)
			{
				Dev_No = sexb_cur_dev;
				FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
				Dev_No = old_devno;
			}
			FAT_Device_Read_Sector(pfi->File_CurSec, pexb_buf);
		}
		else
		{
			if (sexb_cur_sec != (pfi->File_CurSec))
			{
				if (0 != sexb_cur_sec)
				{
					FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
					FAT_Device_Read_Sector(pfi->File_CurSec, pexb_buf);
				}
			}
		}
#else
		if (0 == (just_file->exb_cursec))
		{
			FAT_Device_Read_Sector(pfi->File_CurSec, pexb_buf);
		}
#endif

		Memory_Copy(pexb_buf + pfi->File_CurPos, pbuf, temp);
		FAT_Device_Write_Sector(pfi->File_CurSec, pexb_buf);
# ifndef USE_ALONE_EXB
		sexb_cur_sec = 0;
		sexb_cur_dev = (u8)(-1);
		psexb_cur_oc = (struct FileInfo *)0;
#else
(just_file->exb_cursec) = 0; 
		#endif
	}
	else
{
	FAT_Device_Write_Sector(pfi->File_CurSec, pbuf);
}
#endif

len_temp -= temp;
pbuf += temp;
if (!(IS_END_SEC_OF_CLU(pfi->File_CurSec, pfi->File_CurClust)))
{
	pfi->File_CurSec++;
	pfi->File_CurPos = 0;
	pfi->File_CurOffset += temp;
	temp = (LAST_SEC_OF_CLU(pfi->File_CurClust) -
			(pfi->File_CurSec) + 1) * (pInitInfo->BytesPerSector);
	if (len_temp <= temp)
	{
		temp1 = len_temp / (pInitInfo->BytesPerSector);
		FAT_Device_Write_nSector(temp1, pfi->File_CurSec, pbuf);
		pbuf += ((pInitInfo->BytesPerSector) * temp1);
		if (len_temp == temp)
		{
			pfi->File_CurSec = SOC(pfi->File_CurClust);
			pfi->File_CurPos = 0;
			pfi->File_CurOffset += len_temp;
			pfi->File_Size += len;
# ifdef RT_UPDATE_FILESIZE
			Update_File_Size(pfi);
#endif
			return len;
		}
		else
		{
			pfi->File_CurSec += temp1;
			pfi->File_CurPos = (u16)(len_temp % (pInitInfo->BytesPerSector));
			if (pfi->File_CurPos)
			{
# ifndef USE_EXCHANGE_BUFFER
				Memory_Copy(FAT_Buffer, pbuf, pfi->File_CurPos);
				FAT_Device_Write_Sector(pfi->File_CurSec, FAT_Buffer);
#else
# ifndef USE_ALONE_EXB
				if (Dev_No != sexb_cur_dev)
				{
					if (0 != sexb_cur_sec)
					{
						Dev_No = sexb_cur_dev;
						FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
						Dev_No = old_devno;
					}
				}
				else
				{
					if (sexb_cur_sec != (pfi->File_CurSec))
					{
						if (0 != sexb_cur_sec)
						{
							FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
						}
					}
				}
#endif
				Memory_Copy(pexb_buf, pbuf, pfi->File_CurPos);
# ifndef USE_ALONE_EXB
				sexb_cur_sec = pfi->File_CurSec;
				sexb_cur_dev = Dev_No;
				psexb_cur_oc = pfi;
#else
				just_file->exb_cursec = pfi->File_CurSec;
#endif
#endif
			}
			pfi->File_CurOffset += len_temp;
			pfi->File_Size += len;
# ifdef RT_UPDATE_FILESIZE
			Update_File_Size(pfi);
#endif
			return len;
		}
	}
	else
	{
		temp1 = temp / (pInitInfo->BytesPerSector);
		FAT_Device_Write_nSector(temp1, pfi->File_CurSec, pbuf);
		pbuf += temp;
		len_temp -= temp;
		pfi->File_CurSec = SOC(pfi->File_CurClust);
		pfi->File_CurPos = 0;
		pfi->File_CurOffset += temp;
	}
}
else //当前扇区是当前簇最后一个扇区
{
	pfi->File_CurSec = SOC(pfi->File_CurClust);
	pfi->File_CurPos = 0;
	pfi->File_CurOffset += temp;
}
	}
	}
	WriteData_From_nCluster(pfi, len_temp, pbuf);
pfi->File_Size += len;
# ifdef RT_UPDATE_FILESIZE
Update_File_Size(pfi);
#endif
return len;
}
#endif

//-----------------------------------------------------------------
// 文件数据截断
//-----------------------------------------------------------------
#ifdef FAT_DUMP_DATA
u8 FAT_Dump_Data(struct FileInfo *pfi, u32 offset) {
	just_file = pfi;

# ifndef RT_UPDATE_CLUSTER_CHAIN
# ifdef USE_ALONE_CCCB
	CCCB_To_Alone();
#endif
#endif

	if (offset >= (pfi->File_Size))
	{
		return ERR_FAIL;
	}

	FAT_Seek(pfi, offset);

# ifndef RT_UPDATE_CLUSTER_CHAIN 
# ifndef USE_ALONE_CCCB
	if (pfi == pcccb_cur_oc)
#endif
	{
		CCCB_Update_FAT();
	}
#endif

	Destroy_FAT_Chain(pfi->File_CurClust);

	if (offset > 0)
	{
		Modify_FAT(pfi->File_CurClust, 0X0FFFFFFF);
	}

	pfi->File_Size = offset;

# ifdef RT_UPDATE_FILESIZE
	Update_File_Size(pfi);
#endif

	if (0 == pfi->File_Size) Update_File_sClust(pfi, 0);

# ifdef RT_UPDATE_FSINFO
	Update_FSINFO();
#endif

	return ERR_SUCC;
}
#endif

# ifdef FAT_MODIFY_DATA
u32 FAT_Modify_Data(struct FileInfo *pfi, u32 offset, u32 len, u8 * app_Buffer) {
	u32 temp_len = 0, temp = 0, nsec = 0, iClu = 0, start_clu = 0, end_clu = 0, next_clu = 0, temp2 = 0, temp1 = 0;
	u32 Cluster_Size = ((pInitInfo->BytesPerSector) * (pInitInfo->SectorsPerClust));

	if (offset >= (pfi->File_Size)) return ERR_MD_POS_OVER_FSIZE;

	if ((offset + len) >= (pfi->File_Size))
	{
		len = (pfi->File_Size) - offset;
		(pfi->File_IsEOF) = 1;
	}

	temp_len = len;

	FAT_Seek(pfi, offset);

	just_file = pfi;

# ifndef RT_UPDATE_CLUSTER_CHAIN
	get_next_cluster_in_cccb = 1;
# ifdef USE_ALONE_CCCB
	CCCB_To_Alone();
#endif
#endif

	if (((pfi->File_CurOffset) % Cluster_Size) != 0)
	{
		if (((pfi->File_CurOffset) % (pInitInfo->BytesPerSector)) != 0)
		{
			if (len <= ((pInitInfo->BytesPerSector) - (pfi->File_CurPos)))
			{
# ifdef USE_EXCHANGE_BUFFER 
# ifndef USE_ALONE_EXB 
				if ((psexb_cur_oc == pfi) && (sexb_cur_dev == Dev_No) && (sexb_cur_sec == (pfi->File_CurSec)))
				{
					Memory_Copy(pexb_buf + (pfi->File_CurPos), app_Buffer, len);
				}
				else
				{
					FAT_Device_Read_Sector((pfi->File_CurSec), FAT_Buffer);
					Memory_Copy(FAT_Buffer + (pfi->File_CurPos), app_Buffer, len);
					FAT_Device_Write_Sector((pfi->File_CurSec), FAT_Buffer);
				}
#else
				if ((pfi->exb_cursec) == (pfi->File_CurSec))
				{
					Memory_Copy((pfi->exb_buf) + (pfi->File_CurPos), app_Buffer, len);
				}
				else
				{
					FAT_Device_Read_Sector((pfi->File_CurSec), FAT_Buffer);
					Memory_Copy(FAT_Buffer + (pfi->File_CurPos), app_Buffer, len);
					FAT_Device_Write_Sector((pfi->File_CurSec), FAT_Buffer);
				}

#endif
#else
				FAT_Device_Read_Sector((pfi->File_CurSec), FAT_Buffer);
				Memory_Copy(FAT_Buffer + (pfi->File_CurPos), app_Buffer, len);
				FAT_Device_Write_Sector((pfi->File_CurSec), FAT_Buffer);

#endif

				if (len < ((pInitInfo->BytesPerSector) - (pfi->File_CurPos)))
				{
					(pfi->File_CurOffset) += len;
					(pfi->File_CurPos) += len;
				}
				else
				if (len == ((pInitInfo->BytesPerSector) - (pfi->File_CurPos)))
				{
					if ((len + (pfi->File_CurOffset)) == (pfi->File_Size))
					{
						if (((pfi->File_Size) % Cluster_Size) == 0)
						{
							(pfi->File_CurOffset) += len;
							(pfi->File_CurPos) = 0;
							(pfi->File_CurSec) = SOC((pfi->File_CurClust));
						}
						else
						{
							(pfi->File_CurOffset) += len;
							(pfi->File_CurPos) = 0;
							(pfi->File_CurSec)++;
						}
					}
					else
					{
						if (((len + (pfi->File_CurOffset)) % Cluster_Size) == 0)
						{
							(pfi->File_CurOffset) += len;
							(pfi->File_CurPos) = 0;
							(pfi->File_CurClust) = Get_Next_Cluster((pfi->File_CurClust));
							(pfi->File_CurSec) = SOC((pfi->File_CurClust));
						}
						else
						{
							(pfi->File_CurOffset) += len;
							(pfi->File_CurPos) = 0;
							(pfi->File_CurSec)++;
						}
					}
				}
				return temp_len;
			}
			else
			{
				temp = (pInitInfo->BytesPerSector) - (pfi->File_CurPos);
				FAT_Device_Read_Sector((pfi->File_CurSec), FAT_Buffer);
				Memory_Copy(FAT_Buffer + (pfi->File_CurPos), app_Buffer, temp);
				FAT_Device_Write_Sector((pfi->File_CurSec), FAT_Buffer);
				len -= temp; app_Buffer += temp;
				(pfi->File_CurOffset) += temp;

				(pfi->File_CurPos) = 0;

				if (!IS_END_SEC_OF_CLU((pfi->File_CurSec), (pfi->File_CurClust)))
				{
					(pfi->File_CurSec)++;
				}
				else
				{
					(pfi->File_CurClust) = Get_Next_Cluster((pfi->File_CurClust));
					(pfi->File_CurSec) = SOC((pfi->File_CurClust));
				}
			}
		}

		if (((pfi->File_CurOffset) % (Cluster_Size)) != 0)
		{
			temp = (((SOC(pfi->File_CurClust)) + (pInitInfo->SectorsPerClust) - 1) - (pfi->File_CurSec) + 1) * (pInitInfo->BytesPerSector);

			if (len <= temp)
			{
				nsec = len / (pInitInfo->BytesPerSector);
				FAT_Device_Write_nSector(nsec, (pfi->File_CurSec), app_Buffer);
				temp = (nsec * (pInitInfo->BytesPerSector));
				len -= temp; app_Buffer += temp;

				(pfi->File_CurOffset) += temp;

				if (len == 0)
				{
					if ((pfi->File_CurOffset) == (pfi->File_Size))
					{
						(pfi->File_CurPos) = 0;
						(pfi->File_CurSec) = SOC((pfi->File_CurClust));
					}
					else
					{
						(pfi->File_CurClust) = Get_Next_Cluster((pfi->File_CurClust));
						(pfi->File_CurPos) = 0;
						(pfi->File_CurSec) = SOC((pfi->File_CurClust));
					}
				}
				else
				{
					(pfi->File_CurPos) = 0;
					(pfi->File_CurSec) += nsec;

# ifdef USE_EXCHANGE_BUFFER 
# ifndef USE_ALONE_EXB 
					if ((psexb_cur_oc == pfi) && (sexb_cur_dev == Dev_No) && (sexb_cur_sec == (pfi->File_CurSec)))
					{
						Memory_Copy(pexb_buf + (pfi->File_CurPos), app_Buffer, len);
					}
					else
					{
						FAT_Device_Read_Sector((pfi->File_CurSec), FAT_Buffer);
						Memory_Copy(FAT_Buffer + (pfi->File_CurPos), app_Buffer, len);
						FAT_Device_Write_Sector((pfi->File_CurSec), FAT_Buffer);
					}
#else
					if ((pfi->exb_cursec) == (pfi->File_CurSec))
					{
						Memory_Copy((pfi->exb_buf) + (pfi->File_CurPos), app_Buffer, len);
					}
					else
					{
						FAT_Device_Read_Sector((pfi->File_CurSec), FAT_Buffer);
						Memory_Copy(FAT_Buffer + (pfi->File_CurPos), app_Buffer, len);
						FAT_Device_Write_Sector((pfi->File_CurSec), FAT_Buffer);
					}

#endif
#else
					FAT_Device_Read_Sector((pfi->File_CurSec), FAT_Buffer);
					Memory_Copy(FAT_Buffer + (pfi->File_CurPos), app_Buffer, len);
					FAT_Device_Write_Sector((pfi->File_CurSec), FAT_Buffer);

#endif

					(pfi->File_CurOffset) += len;
					(pfi->File_CurPos) = len;
				}

				return temp_len;
			}
			else
			{
				//temp=(pInitInfo->BytesPerSector)-(pfi->File_CurPos);
				//FAT_Device_Read_Sector((pfi->File_CurSec),FAT_Buffer);
				//Memory_Copy(FAT_Buffer,app_Buffer,temp);
				//FAT_Device_Write_Sector((pfi->File_CurSec),FAT_Buffer);
				//len-=temp;app_Buffer+=temp;
				//(pfi->File_CurOffset)+=temp;
				//(pfi->File_CurSec)++;

				temp = (((SOC(pfi->File_CurClust)) + (pInitInfo->SectorsPerClust) - 1) - (pfi->File_CurSec) + 1);
				FAT_Device_Write_nSector(temp, (pfi->File_CurSec), app_Buffer); //向当前簇内要修改的整扇区数据部分写入数据
				temp *= (pInitInfo->BytesPerSector);
				len -= temp; app_Buffer += temp;

				(pfi->File_CurOffset) += temp;
				(pfi->File_CurClust) = Get_Next_Cluster((pfi->File_CurClust));
				(pfi->File_CurPos) = 0;
				(pfi->File_CurSec) = SOC((pfi->File_CurClust));
			}
		}
	}


	temp = (len / Cluster_Size);

	if (temp > 0)
	{
		start_clu = end_clu = (pfi->File_CurClust);

		for (iClu = 1; iClu < temp; iClu++)
		{
			next_clu = Get_Next_Cluster(end_clu);

			if ((next_clu - 1) == end_clu)
			{
				end_clu = next_clu;
			}
			else
			{
				FAT_Device_Write_nSector(((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust)), SOC(start_clu), app_Buffer);
				app_Buffer += ((end_clu - start_clu + 1) * Cluster_Size);
				start_clu = next_clu;
				end_clu = next_clu;
			}
		}

		temp2 = Get_Next_Cluster(end_clu);
		temp1 = (len - temp * Cluster_Size);

		if (temp1 == 0)
		{
			FAT_Device_Write_nSector(((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust)), SOC(start_clu), app_Buffer);

			if (!IS_END_CLU(temp2))
			{
				(pfi->File_CurClust) = end_clu;
			}
			else
			{
				(pfi->File_CurClust) = temp2;
			}

		 (pfi->File_CurOffset) += (temp * Cluster_Size);
			(pfi->File_CurPos) = 0;
			(pfi->File_CurSec) = SOC((pfi->File_CurClust));

			return temp_len;
		}
		else
		{
			if ((temp2 - 1) == end_clu)
			{
				temp = ((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust) + (temp1 / (pInitInfo->BytesPerSector)));
				FAT_Device_Write_nSector(temp, SOC(start_clu), app_Buffer);

				(pfi->File_CurOffset) += (temp * (pInitInfo->BytesPerSector));

				app_Buffer += (temp * (pInitInfo->BytesPerSector));
				len -= (temp * (pInitInfo->BytesPerSector));
			}
			else
			{
				temp = ((end_clu - start_clu + 1) * (pInitInfo->SectorsPerClust));
				FAT_Device_Write_nSector(temp, SOC(start_clu), app_Buffer);
				iClu = (temp * (pInitInfo->BytesPerSector));
				app_Buffer += iClu; len -= iClu;
				(pfi->File_CurOffset) += iClu;

				FAT_Device_Write_nSector((temp1 / (pInitInfo->BytesPerSector)), SOC(temp2), app_Buffer);
				iClu = ((temp1 / (pInitInfo->BytesPerSector)) * (pInitInfo->BytesPerSector));
				app_Buffer += iClu; len -= iClu;
				(pfi->File_CurOffset) += iClu;
			}

		 (pfi->File_CurClust) = temp2;
			(pfi->File_CurPos) = 0;
			(pfi->File_CurSec) = SOC(temp2) + (temp1 / (pInitInfo->BytesPerSector));
		}
	}
	else
	{
		temp = len / (pInitInfo->BytesPerSector);
		FAT_Device_Write_nSector(temp, (pfi->File_CurSec), app_Buffer);
		app_Buffer += (temp * (pInitInfo->BytesPerSector));
		len -= (temp * (pInitInfo->BytesPerSector));
		(pfi->File_CurOffset) += (temp * (pInitInfo->BytesPerSector));

		(pfi->File_CurSec) += temp;
	}

	if (len == 0)
	{
		return temp_len;
	}
	else
	{

# ifdef USE_EXCHANGE_BUFFER 
# ifndef USE_ALONE_EXB 
		if ((psexb_cur_oc == pfi) && (sexb_cur_dev == Dev_No) && (sexb_cur_sec == (pfi->File_CurSec)))
		{
			Memory_Copy(pexb_buf + (pfi->File_CurPos), app_Buffer, len);
		}
		else
		{
			FAT_Device_Read_Sector((pfi->File_CurSec), FAT_Buffer);
			Memory_Copy(FAT_Buffer + (pfi->File_CurPos), app_Buffer, len);
			FAT_Device_Write_Sector((pfi->File_CurSec), FAT_Buffer);
		}
#else
		if ((pfi->exb_cursec) == (pfi->File_CurSec))
		{
			Memory_Copy((pfi->exb_buf) + (pfi->File_CurPos), app_Buffer, len);
		}
		else
		{
			FAT_Device_Read_Sector((pfi->File_CurSec), FAT_Buffer);
			Memory_Copy(FAT_Buffer + (pfi->File_CurPos), app_Buffer, len);
			FAT_Device_Write_Sector((pfi->File_CurSec), FAT_Buffer);
		}

#endif
#else

		FAT_Device_Read_Sector((pfi->File_CurSec), FAT_Buffer);
		Memory_Copy(FAT_Buffer + (pfi->File_CurPos), app_Buffer, len);
		FAT_Device_Write_Sector((pfi->File_CurSec), FAT_Buffer);

#endif

		(pfi->File_CurOffset) += len;
		(pfi->File_CurPos) = len;

		return temp_len;
	}
}
#endif
//-----------------------------------------------------------------
// 关闭文件
//-----------------------------------------------------------------
# ifdef FAT_CLOSE_FILE
u8 FAT_Close_File(struct FileInfo *pfi)
{
# ifndef RT_UPDATE_FILESIZE
	Update_File_Size(pfi);
#endif

	just_file = pfi;

# ifndef RT_UPDATE_CLUSTER_CHAIN
# ifdef USE_ALONE_CCCB
	CCCB_To_Alone();
#endif
#endif

# ifndef RT_UPDATE_CLUSTER_CHAIN
# ifndef USE_ALONE_CCCB
	if (pfi == pcccb_cur_oc)
#endif
		CCCB_Update_FAT();
#endif

# ifndef RT_UPDATE_CLUSTER_CHAIN
# ifdef USE_ALONE_CCCB
	pcccb_buf = (u32*)0;
	pcccb_curval = (u32*)0;
	pcccb_counter = (u8*)0;
#endif
#endif

# ifdef USE_EXCHANGE_BUFFER
# ifndef USE_ALONE_EXB
	if (pfi == psexb_cur_oc && 0 != (sexb_cur_sec))
	{
		FAT_Device_Write_Sector(sexb_cur_sec, pexb_buf);
		sexb_cur_sec = 0;
		psexb_cur_oc = (struct FileInfo *)0;
sexb_cur_dev = (u8)(-1);
 }
 #else
 pexb_buf = pfi->exb_buf;
if (0 != pfi->exb_cursec)
{
	FAT_Device_Write_Sector(pfi->File_CurSec, pexb_buf);
}
pexb_buf = (u8*)0;
#endif
#endif

Memory_Set((u8*)pfi, (u32)sizeof(struct FileInfo),0);

just_file = (struct FileInfo *)0;

return ERR_SUCC;
}
#endif
//-----------------------------------------------------------------
// 刷新文件系统
//-----------------------------------------------------------------
#ifdef FAT_FLUSH_FS
u8 FAT_Flush_FS(void)
{
# ifndef RT_UPDATE_FSINFO
	Update_FSINFO();
#endif

	return ERR_SUCC;
}
#endif

